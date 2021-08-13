# The new base image to contain runtime dependencies
#-----------------------------------------------------------------------------------------------------------------------

FROM ubuntu:21.04 AS base

RUN apt-get update
RUN DEBIAN_FRONTEND=noninteractive apt-get dist-upgrade -y
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y libssl1.1 libicu67

# The first stage will install build dependencies on top of the
# runtime dependencies, and then compile
#-----------------------------------------------------------------------------------------------------------------------

FROM base AS builder

# Prepare for building of the application and its dependencies
COPY ./deps /usr/src/eagle-to-mqtt/deps

RUN DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends ca-certificates cmake curl file gcc-11 g++-11 git gnupg2 ninja-build pkg-config libssl-dev make tar unzip zip
RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-11 11
RUN update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-11 11

# Configure vcpkg (and other submodules) ready for the build process 
ENV VCPKG_DEFAULT_TRIPLET x64-linux
RUN /usr/src/eagle-to-mqtt/deps/vcpkg/bootstrap-vcpkg.sh 
RUN /usr/src/eagle-to-mqtt/deps/vcpkg/vcpkg integrate install

# The second stage ....
#-----------------------------------------------------------------------------------------------------------------------

FROM builder as appbuilder

# Build and install the application
COPY . /usr/src/eagle-to-mqtt
 
RUN cmake -G Ninja -S /usr/src/eagle-to-mqtt -B /usr/src/eagle-to-mqtt/build -DCMAKE_MAKE_PROGRAM=ninja -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_TOOLCHAIN_FILE=/usr/src/eagle-to-mqtt/deps/vcpkg/scripts/buildsystems/vcpkg.cmake
RUN cmake --build /usr/src/eagle-to-mqtt/build --config RelWithDebInfo --target install

# The third stage ....
#-----------------------------------------------------------------------------------------------------------------------

FROM base AS runtime

COPY --from=appbuilder /usr/local/bin /usr/local/bin
COPY --from=appbuilder /usr/local/lib /usr/local/lib
COPY --from=appbuilder /usr/src/eagle-to-mqtt/app/app_entrypoint.sh /app_entrypoint.sh

RUN ["chmod", "+x", "/app_entrypoint.sh"]

ENV LD_LIBRARY_PATH /usr/local/lib:${LD_LIBRARY_PATH}

ENTRYPOINT [ "/app_entrypoint.sh" ]

# Configure the application (and runtime values)
EXPOSE 3000/tcp
CMD ["eagle-to-mqtt"]
