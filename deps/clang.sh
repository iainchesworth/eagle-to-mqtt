#!/bin/sh

# WARNING WARNING WARNING
# Editing this file under Windows will break "docker build..." if it is saved
# with the line endings changed to CRLF (vs. just LF).

cat /usr/src/eagle-to-mqtt/deps/clang/00-llvm.conf >> /etc/apt/sources.list
