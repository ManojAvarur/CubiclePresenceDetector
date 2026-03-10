void setup(){
  Serial.begin(19200);
  wifi_setup();

  Ws.onEvent(onEvent);
  Server.addHandler(&Ws);
  Server.begin();

  // Initlizes user Maps
  initUserMaps();

  // Use CPU cycle count as a seed for better randomness
  randomSeed(ESP.getCycleCount()); 
}