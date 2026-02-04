// -- Main Declaration --
#include <ESP8266WiFi.h>          // ESP8266 Package (i.e. WIFI etc..)
#include <ESPAsyncTCP.h>          // HTTP Server and Websockets(https://randomnerdtutorials.com/esp8266-nodemcu-websocket-server-sensor/  )
#include <ESPAsyncWebServer.h>    // HTTP Server and Websockets
#include <AsyncWebSocket.h>
#include <Hash.h>                 // Hasing Functions
#include <vector>
#include <map>
#include "ArduinoJson-v7.4.2.h"

// -- Enums --
enum ClientTypes {
  IOT, 
  DESKTOP, 
  ANDROID,
  UNKNOWN
};

// -- Structs --
struct ClientInfoStruct {
  ClientTypes type;
  uint32_t id;
  IPAddress ip;

  bool operator==(const ClientInfoStruct& other) const {
    return id == other.id;
  }
};

// -- Global Variables --
// std::map<ClientTypes, std::vector<ClientInfoStruct*>> ClientTypeToClientInfoMap;
std::map<uint32_t, ClientInfoStruct*> ClientIdToClientMap;

// Create AsyncWebServer object on port 80
AsyncWebServer Server(80);

// Create a WebSocket object
AsyncWebSocket Ws("/ws");


// -- Function Declaration --
void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len);
bool isIPAllowed(IPAddress ip); 
void initUserMaps();
void removeClientFromMaps();
void handleWebSocketMessage(AsyncWebSocketClient *client, void *arg, uint8_t *data, size_t len);
bool checkAndAssignClientType(JsonDocument jsonData, ClientInfoStruct* clientInfo);
void transmitSensorData(String data);

