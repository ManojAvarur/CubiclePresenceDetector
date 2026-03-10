#include "secrets.h"

const IPAddress allowedIPs[] = ALLOWED_IPS;

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
  switch (type) {
    case WS_EVT_CONNECT: {
      Serial.printf("WebSocket client trying to connect #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());

      if (!isIPAllowed(client->remoteIP())) {
        client->close();
        break;
      }

      ClientInfoStruct* clientInfo = new ClientInfoStruct();
      clientInfo->id = client->id();
      clientInfo->type = ClientTypes::UNKNOWN;
      clientInfo->ip = client->remoteIP();

      // ClientTypeToClientInfoMap[ClientTypes::UNKNOWN].push_back(clientInfo);
      ClientIdToClientMap[client->id()] = clientInfo;

      Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());

      break;
    }

    case WS_EVT_DISCONNECT: {
      removeClientFromMaps(client->id());
      Serial.printf("WebSocket client #%u disconnected\n", client->id());
      break;
    }

    case WS_EVT_DATA: {
      handleWebSocketMessage(client, arg, data, len);
      Serial.printf("\n\n-- WebSocket client #%u connected from %s data process completed --\n", client->id(), client->remoteIP().toString().c_str());
      break;
    }

    case WS_EVT_PONG:
    case WS_EVT_ERROR:
    break;
  }
}

void handleWebSocketMessage(AsyncWebSocketClient *client, void *arg, uint8_t *data, size_t len){
  Serial.printf("\n\n-- WebSocket client #%u connected from %s is trying to send data --\n", client->id(), client->remoteIP().toString().c_str());
  AwsFrameInfo *info = (AwsFrameInfo*)arg;

  if (!info->final || info->index != 0 || info->len != len || info->opcode != WS_TEXT) {
    Serial.println("\tSending Failed!");
    return;
  }

  data[len] = 0;
  String message = (char*)data;
  Serial.printf("\t%s\n", message);

  JsonDocument jsonData;
  DeserializationError error = deserializeJson(jsonData, message);

  if (error) {
    Serial.print("\tdeserializeJson() failed: ");
    Serial.println(error.c_str());
    return;
  }

  ClientInfoStruct *clientInfo = ClientIdToClientMap[client->id()];
  Serial.printf("\t%s Client Type\n", String(clientInfo->type));

  if(!checkAndAssignClientType(jsonData, clientInfo)){
    return;
  }

  if(clientInfo->type == ClientTypes::IOT){
    Serial.println("\tTransmitting Data");
    transmitSensorData(message);
  }
}

void transmitSensorData(String data){
  for(std::map<uint32_t, ClientInfoStruct*>::iterator itr = ClientIdToClientMap.begin(); itr != ClientIdToClientMap.end(); ++itr) {
    ClientInfoStruct *itrClient = itr->second;

    if(itrClient->type == ClientTypes::IOT){
      continue;
    } 

    Serial.print("\tTransmitting Data For: ");
    Serial.println(itrClient->id);
    Ws.text(itrClient->id, data);
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
