#!/bin/bash
export DEBVERSION=1.76.0
if [ ! -d "boost_1_76_0" ]; then
    wget "https://boostorg.jfrog.io/artifactory/main/release/1.76.0/source/boost_1_76_0.tar.bz2" -O boost-all_1.76.0.orig.tar.bz2
    tar xjvf boost-all_1.76.0.orig.tar.bz2
fi
cd boost_1_76_0

#Build DEB
rm -rf debian
mkdir -p debian

#Use the LICENSE file from nodejs as copying file
touch debian/copying

#Create the changelog (no messages needed)
dch --create -v $DEBVERSION --package boost-all ""

#Create copyright file
touch debian

#Create control file
cat > debian/control <<EOF
Source: boost-all
Maintainer: None <none@example.com>
Section: libs
Priority: optional
Build-Depends: debhelper-compat (= 12), dpkg-dev (>= 1.16.1~), dctrl-tools, chrpath,
 zlib1g-dev, libbz2-dev, liblzma-dev, libzstd-dev, libicu-dev (>= 63.1), mpi-default-dev [!i386],
 bison, flex, docbook-to-man, help2man, xsltproc, doxygen,
 docbook-xsl, docbook-xml, texlive-latex-base, ghostscript,
 dh-python,
 clang-12,
 python3, python3-all-dev (>= 3.1), python3-numpy [!i386]
Build-Depends-Indep: graphviz
Build-Conflicts: libopenmpi-dev (= 1.3.2-2)
Vcs-Browser: https://salsa.debian.org/debian/boost
Vcs-Git: https://salsa.debian.org/debian/boost.git
Standards-Version: 4.5.1

Package: boost-all
Architecture: amd64
Section: libdevel
Depends: \${shlibs:Depends}, \${misc:Depends}, libstdc++-dev, boost-all (= $DEBVERSION)
Description: Boost library, version $DEBVERSION (shared libraries)
Conflicts: libboost1.42-dev, libboost1.46-dev, libboost1.48-dev, libboost1.49-dev, libboost1.50-dev, libboost1.52-dev, libboost1.53-dev, libboost1.54-dev, libboost1.55-dev, libboost1.57-dev, libboost1.58-dev, libboost1.60-dev, libboost1.61-dev, libboost1.62-dev, libboost1.63-dev, libboost1.65-dev, libboost1.67-dev, libboost1.70-dev, libboost1.71-dev, libboost1.74-dev

Package: libboost-all-dev
Architecture: any
Depends: boost-all (= $DEBVERSION)
Description: Boost library, version $DEBVERSION (development files)

Package: boost-build
Architecture: any
Depends: \${misc:Depends}
Description: Boost Build v2 executable
EOF

#Create rules file
cat > debian/rules <<EOF 
#!/usr/bin/make -f
%:
	dh \$@
override_dh_auto_configure:
	./bootstrap.sh --with-toolset=clang
override_dh_auto_build:
	./b2 link=static,shared -j 1 --prefix=`pwd`/debian/boost-all/usr/local/
override_dh_auto_test:
override_dh_usrlocal:
override_dh_auto_install:
	mkdir -p debian/boost-all/usr/local debian/boost-all-dev/usr/local debian/boost-build/usr/local/bin
	./b2 link=static,shared --prefix=`pwd`/debian/boost-all/usr/local/ install
	mv debian/boost-all/usr/local/include debian/boost-all-dev/usr/local/
	cp b2 debian/boost-build/usr/local/bin
	./b2 install --prefix=`pwd`/debian/boost-build/usr/local/ install
EOF

#Create some misc files
mkdir -p debian/source
echo "3.0 (quilt)" > debian/source/format

#Build the package
nice -n19 ionice -c3 debuild -b 
