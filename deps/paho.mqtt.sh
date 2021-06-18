#!/bin/sh

# WARNING WARNING WARNING
# Editing this file under Windows will break "docker build..." if it is saved
# with the line endings changed to CRLF (vs. just LF).

git clone https://github.com/eclipse/paho.mqtt.c.git 
cd paho.mqtt.c
git checkout v1.3.8
cmake -Bbuild -H. -DPAHO_WITH_SSL=TRUE 
cmake --build build/ --target install
cd ..

git clone https://github.com/eclipse/paho.mqtt.cpp
cd paho.mqtt.cpp
cmake -Bbuild -H. -DPAHO_WITH_SSL=TRUE
cmake --build build/ --target install
cd ..

ldconfig
