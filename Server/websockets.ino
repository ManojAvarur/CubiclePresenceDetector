#include "secrets.h"

const IPAddress allowedIPs[] = ALLOWED_IPS;

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
  
  switch (type) {
    case WS_EVT_CONNECT:
      if (!isIPAllowed(client->remoteIP())) {
        client->text("Forbidden");
        client->close();
      }
      
      Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
    break;

    case WS_EVT_DISCONNECT:
      Serial.printf("WebSocket client #%u disconnected\n", client->id());
    break;

    case WS_EVT_DATA:
      Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
    break;

    case WS_EVT_PONG:
    case WS_EVT_ERROR:
    break;
  }
}

bool isIPAllowed(IPAddress ip) {
  for (IPAddress allowed : allowedIPs) {
    if (ip == allowed){
      return true;
    } 
  }
  return false;
}
