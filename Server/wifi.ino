#include "secrets.h"

short overall_wait_time = 6;
short delay_timer = 1;

bool wifi_setup(){
	Serial.println("Connecting");

	short while_counter = 0;
	WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

	while(!isWifiConnected() && (while_counter <= overall_wait_time)) {
		Serial.print(".");
    while_counter++;
		delay(delay_timer * 1000);
	}

	Serial.println("");
	Serial.print("Connected to WiFi network with IP Address: ");
	Serial.println(WiFi.localIP());
	
	return isWifiConnected();
}

bool isWifiConnected(){
	return WiFi.status() == WL_CONNECTED;
}