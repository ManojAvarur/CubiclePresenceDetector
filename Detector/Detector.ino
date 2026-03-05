#include <ESP8266WiFi.h>          // ESP8266 Package (i.e. WIFI etc..)
#include <WebSocketsClient.h>
#include "UltraSonicSensorHandler.h"
#include "ArduinoJson-v7.4.2.h"

int TRIGGER_PIN = D0;
int ECHO_PIN = D1;

WebSocketsClient webSocket;

UltraSonicSensor *USS;
float PREV_USS_VAL;
float CUBE_ENTRANCE = 175; // Anything measurement below will inform the clients

// void wifi_setup();
// bool isWifiConnected();

