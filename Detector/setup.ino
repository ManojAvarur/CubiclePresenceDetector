#include "secrets.h"

void setup(){
  Serial.begin(19200);
  wifi_setup();

  webSocket.begin(DOMAIN, PORT, ENDPOINT); 

  USS = new UltraSonicSensor(TRIGGER_PIN, ECHO_PIN);

  webSocket.begin(DOMAIN, PORT, ENDPOINT);
  webSocket.setReconnectInterval(5000);
}