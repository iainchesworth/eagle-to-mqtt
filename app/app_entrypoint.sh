#!/bin/bash

echo "Starting Eagle-to-MQTT Application..."

# WARNING WARNING WARNING
# Editing this file under Windows will break "docker build..." if it is saved
# with the line endings changed to CRLF (vs. just LF).

if [[ -z ${MQTT_HOST} ]] ; then echo "WARNING: MQTT_HOST is not set" && exit -1; fi;

EP_APP_PARAMS="--mqtt-host $MQTT_HOST"

# Include any MQTT _optional_ parameters
if [[ -v MQTT_PORT ]] ; then EP_MQTT_PORT=" --mqtt-port $MQTT_PORT" ; fi
if [[ -v MQTT_TOPIC ]] ; then EP_MQTT_TOPIC=" --mqtt-topic $MQTT_TOPIC" ; fi
if [[ -v MQTT_USER ]] ; then EP_MQTT_USER=" --mqtt-username $MQTT_USER" ; fi
if [[ -v MQTT_PASS ]] ; then EP_MQTT_PASS=" --mqtt-password $MQTT_PASS" ; fi

EP_APP_PARAMS="$EP_APP_PARAMS $EP_MQTT_PORT $EP_MQTT_TOPIC $EP_MQTT_USER $EP_MQTT_PASS"

# Include any HTTP _optional_ parameters
if [[ -v HTTP_HOST ]] ; then EP_HTTP_HOST=" --http-host $HTTP_HOST" ; fi
if [[ -v HTTP_PORT ]] ; then EP_HTTP_PORT=" --http-port $HTTP_PORT" ; fi

EP_APP_PARAMS="$EP_APP_PARAMS $EP_HTTP_HOST $EP_HTTP_PORT"
exec "$@" $EP_APP_PARAMS
