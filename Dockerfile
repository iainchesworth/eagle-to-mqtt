# The new base image to contain runtime dependencies
#-----------------------------------------------------------------------------------------------------------------------

FROM ubuntu:20.04 AS base

RUN apt-get update
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y libssl1.1

# The first stage will install build dependencies on top of the
# runtime dependencies, and then compile
#-----------------------------------------------------------------------------------------------------------------------

FROM base AS builder

# Prepare for building of the application and its dependencies
COPY ./deps /usr/src/eagle-to-mqtt/deps

RUN DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends ca-certificates curl gnupg2 
RUN /usr/src/eagle-to-mqtt/deps/clang.sh
RUN APT_KEY_DONT_WARN_ON_DANGEROUS_USAGE=1 curl -fsSL https://apt.llvm.org/llvm-snapshot.gpg.key | apt-key add -
RUN apt-get update
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends clang-12 lld-12
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends cmake doxygen git libssl-dev make

RUN update-alternatives --install /usr/bin/clang clang /usr/bin/clang-12 100 --slave /usr/bin/clang++ clang++ /usr/bin/clang++-12 --slave /usr/bin/lld lld /usr/bin/lld-12
RUN update-alternatives --install /usr/bin/cc cc /usr/bin/clang 100 --slave /usr/bin/c++ c++ /usr/bin/clang++ --slave /usr/bin/ld ld /usr/bin/lld

# Build and install the various dependencies 
RUN /usr/src/eagle-to-mqtt/deps/boost.latest.sh
RUN /usr/src/eagle-to-mqtt/deps/paho.mqtt.sh

# Build and install the application
COPY . /usr/src/eagle-to-mqtt
RUN cd /usr/src/eagle-to-mqtt && cmake -Bbuild -H. && cmake --build build/ --target install

# The second stage will already contain all dependencies, just copy
# the compiled executables
#-----------------------------------------------------------------------------------------------------------------------

FROM base AS runtime

COPY --from=builder /usr/local/bin /usr/local/bin
COPY --from=builder /usr/local/lib /usr/local/lib
COPY --from=builder /usr/src/eagle-to-mqtt/app/app_entrypoint.sh /app_entrypoint.sh

ENV LD_LIBRARY_PATH /usr/local/lib:${LD_LIBRARY_PATH}

ENTRYPOINT [ "/app_entrypoint.sh" ]

# Configure the application (and runtime values)
EXPOSE 3000/tcp
CMD ["eagle-to-mqtt"]
