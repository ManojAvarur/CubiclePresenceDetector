void loop(){
    float currentValue = USS->getCurrentValue()->inCentimeter();

    if(currentValue < CUBE_ENTRANCE){
        JsonDocument jsonData;
        String stringData;

        jsonData["currentValue"] = currentValue;
        jsonData["from"] = "IOT";

        jsonData.shrinkToFit();
        serializeJson(jsonData, stringData);

        webSocket.sendTXT(stringData);
    }

    Serial.println(USS->getCurrentValue()->inCentimeter());
    webSocket.loop();
}