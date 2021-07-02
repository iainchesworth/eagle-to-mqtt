#!/bin/sh

# WARNING WARNING WARNING
# Editing this file under Windows will break "docker build..." if it is saved
# with the line endings changed to CRLF (vs. just LF).

echo "Installing Boost 1.76 binary and development dependencies..."
apt install /usr/src/eagle-to-mqtt/deps/boost/boost-build_1.76.0_amd64.deb

