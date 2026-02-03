void setup(){
  Serial.begin(19200);
  wifi_setup();

  ws.onEvent(onEvent);

  // Use CPU cycle count as a seed for better randomness
  randomSeed(ESP.getCycleCount()); 
}