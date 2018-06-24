#include "ESP8266_multipart.h"

ESP8266_multipart::ESP8266_multipart() {
  ESP8266_multipart::init("127.0.0.1", 80);
}
ESP8266_multipart::ESP8266_multipart(String host) {
  ESP8266_multipart::init(host.c_str(), 80);
}
ESP8266_multipart::ESP8266_multipart(const char* host) {
  ESP8266_multipart::init(host, 80);
}
void ESP8266_multipart::init(const char* host, int port) {
  this->host = host;
  this->port = port;
}
int ESP8266_multipart::sendFile(String path, File file) {
  return sendFile(path.c_str(), file);
}
void ESP8266_multipart::setPort(int port) {
  this->port = port;
}
void ESP8266_multipart::setHost(String host) {
  ESP8266_multipart::setHost(host.c_str());
}
void ESP8266_multipart::setHost(const char* host) {
  this->host = host;
}
int ESP8266_multipart::sendFile(const char* path, File file) {
  WiFiClient client;
  if(client.connect(this->host, this->port)) {
    client.print(F("POST ")); client.print(path); client.print(F(" HTTP/1.1\r\n"));
    client.print(F("Host: ")); client.print(this->host); client.print(F("\r\n"));
    client.print(F("User-Agent: esp8266_multipart/1.0\r\n"));
    client.print(F("Accept: */*\r\n"));
    client.print(F("Connection: close\r\n"));
    client.print(F("Content-Type: multipart/form-data; boundary=X-ESP8266_MULTIPART\r\n"));
    String tmpFront = "--X-ESP8266_MULTIPART\r\nContent-Disposition: form-data; name=\"";
    tmpFront += file.name();
    tmpFront += "\"\r\n\r\n";
    String tmpBack = "\r\n--X-ESP8266_MULTIPART--\r\n\r\n";
    int dataLength = tmpFront.length() + tmpBack.length() + file.size();
    client.print(F("Content-Length: ")); client.print(dataLength); client.print(F("\r\n\r\n"));
    client.print(tmpFront);
    int tempPos = file.position();
    file.seek(0, SeekSet);
    while(file.available()) {
      while(file.position() < file.size()) {
        String dataBuffer = file.readStringUntil('\n');
        client.print(dataBuffer);
        client.print("\n");
      }
    }
    client.print(tmpBack);
    file.seek(tempPos, SeekSet);
    client.flush();
  } else {
    return 0;
  }
  String tmpRes = "";
  while(client.connected()) {
    while(client.available()) {
      char c = client.read();
      tmpRes += c;
    }
  }
  int status = -1;
  if(!client.connected()) {
    int firstSpace = tmpRes.indexOf(" ");
    tmpRes.remove(0, firstSpace +1);
    status = tmpRes.substring(0,3).toInt();
    client.stop();
  }
  return status;
}


