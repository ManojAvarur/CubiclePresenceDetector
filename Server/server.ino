// -- Main Declaration --
#include <ESP8266WiFi.h>          // ESP8266 Package (i.e. WIFI etc..)
#include <ESPAsyncTCP.h>          // HTTP Server and Websockets(https://randomnerdtutorials.com/esp8266-nodemcu-websocket-server-sensor/  )
#include <ESPAsyncWebServer.h>    // HTTP Server and Websockets
#include <AsyncWebSocket.h>
#include <Arduino_JSON.h>         // JSON Parsing
#include <Hash.h>                 // Hasing Functions
#include <vector>
#include <map>

// -- Enums --
enum ClientType {
  IOT = 0, 
  DESKTOP = 1, 
  ANDROID = 2
};

// -- Structs --
struct ClientInfo {
  ClientType type;
  uint32_t id;
  IPAddress ip;
};

// -- Global Variables --
std::map<ClientType, std::vector<ClientInfo>> usersTypeMap;

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

// Create a WebSocket object
AsyncWebSocket ws("/ws");


// -- Function Declaration --
void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len);
bool isIPAllowed(IPAddress ip); 
