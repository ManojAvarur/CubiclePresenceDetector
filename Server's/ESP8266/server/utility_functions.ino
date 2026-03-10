String generateNonce() {
  String token = "";
  for(int i = 0; i < 32; i++) {
    token += String(random(0xFFFFFF), HEX);
  }
  return token;
}

bool checkAndAssignClientType(JsonDocument jsonData, ClientInfoStruct* clientInfo){
  if(clientInfo->type != ClientTypes::UNKNOWN){
    return true;
  }

  String type = String(jsonData["from"]);
  if(type == "IOT"){
    clientInfo->type = ClientTypes::IOT;
    return true;
  }
  
  if(type == "DESKTOP"){
    clientInfo->type = ClientTypes::DESKTOP;
    return true;
  }
  
  if(type == "ANDROID"){
    clientInfo->type = ClientTypes::ANDROID;
    return true;
  }

  return false;
}

void initUserMaps(){
  // ClientTypeToClientInfoMap = {
  //   { ClientTypes::ANDROID, std::vector<ClientInfoStruct*>{} },
  //   { ClientTypes::DESKTOP, std::vector<ClientInfoStruct*>{} },
  //   { ClientTypes::IOT,     std::vector<ClientInfoStruct*>{} },
  //   { ClientTypes::UNKNOWN, std::vector<ClientInfoStruct*>{} }
  // };

  ClientIdToClientMap = {};
}

void removeClientFromMaps(uint32_t id){
  if(ClientIdToClientMap.count(id) == 0){
    return;
  }

  ClientInfoStruct *clientInfo = ClientIdToClientMap[id];
  ClientTypes clientType = clientInfo->type;
  // std::vector<ClientInfoStruct*> tempClientsList = ClientTypeToClientInfoMap[clientType];

  // Removing the CLient from vector
  // tempClientsList.erase(std::remove(tempClientsList.begin(), tempClientsList.end(), clientInfo), tempClientsList.end());

  // ClientTypeToClientInfoMap[clientType] = tempClientsList;
  ClientIdToClientMap.erase(id);
  delete clientInfo;
}