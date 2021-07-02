# Rainforest Eagle-to-MQTT bridge
This application listens to your Rainforest Automation RFA-Z109 or EAGLE-200 device and translates publishes its data to
MQTT.  This enables direct integration with MQTT-capable services/software such as HomeKit via [mqttthing-homebridge] 
(https://github.com/arachnetech/homebridge-mqttthing), [HomeAssistant] (https://www.home-assistant.io/), and many others.  
Releases are available as Docker containers on [Docker Hub] (https://hub.docker.com/r/ichesworth/eagle-to-mqtt).

## Configuring and Running

TODO

### Configuring Your EAGLE with a Custom Upload destination

Before anything will work, you need to connect your Rainforest Automation device's uploader to connect and publish to the
application or container.  This is done via the device's UI or Rainforest Automation's website. If you want to tweak any
of the parameters, you can also directly POST the configuration to the API via [Swagger] (https://api.rainforestcloud.com/swagger)
or by using CURL.  An example payload can be found below:
```
{
   "command":"uploader",
   "parameters":{
      "name":"uploader_add",
      "description":"MQTT Bridge - Real Time (PROD:RT)",
      "provider":"eagle-to-mqtt",
      "format":"XML:RAW",
      "hostname":"192.168.1.173",
      "port":3000,
      "url":"/upload",
      "uploadSize":0,
      "uploadPeriod":0,
      "protocol":"http",
      "x-header1":"",
      "x-header2":"",
      "x-header3":""
   }
}
```

### Running the application directly

TODO

### Running via a Docker Container

Settings are passed through to the application via environment variables

* **MQTT_HOST=<MQTT.broker.address> - REQUIRED - Hostname or IP address of the MQTT broker.**
* MQTT_TOPIC=eagle - Base MQTT topic for published messages, default is `eagle`.
* MQTT_USER=username - MQTT username, if authentication is required.
* MQTT_PASS=password - MQTT password, if authentication is required.
* HTTP_HOST=0.0.0.0 - HTTP interface on which the bridge will listen; default is `0.0.0.0`.
* HTTP_PORT=3000 - HTTP port on which the bridge will listen, default is `3000`.
