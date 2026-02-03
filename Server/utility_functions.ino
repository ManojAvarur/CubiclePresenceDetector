String generateNonce() {
  String token = "";
  for(int i = 0; i < 32; i++) {
    token += String(random(0xFFFFFF), HEX);
  }
  return token;
}