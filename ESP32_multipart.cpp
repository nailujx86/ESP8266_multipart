#include "ESP32_multipart.h"

ESP32_multipart::ESP32_multipart() {
  ESP8266_multipart::init("127.0.0.1", 80);
}
ESP32_multipart::ESP32_multipart(String host) {
  ESP8266_multipart::init(host.c_str(), 80);
}
ESP32_multipart::ESP32_multipart(const char* host) {
  ESP8266_multipart::init(host, 80);
}
void ESP32_multipart::init(const char* host, int port) {
  this->host = host;
  this->port = port;
  this->binary = false;
}
int ESP32_multipart::sendFile(String path, File file) {
  return sendFile(path.c_str(), file);
}
void ESP32_multipart::setPort(int port) {
  this->port = port;
}
void ESP32_multipart::setHost(String host) {
  ESP8266_multipart::setHost(host.c_str());
}
void ESP32_multipart::setHost(const char* host) {
  this->host = host;
}
void ESP32_multipart::setBinary(bool binary) {
  this->binary = binary;
}

int ESP32_multipart::sendFile(const char* path, File file) {
  WiFiClient client;
  if(client.connect(this->host, this->port)) {
    client.print(F("POST ")); client.print(path); client.print(F(" HTTP/1.1\r\n"));
    client.print(F("Host: ")); client.print(this->host); client.print(F("\r\n"));
    client.print(F("User-Agent: esp8266_multipart/1.0\r\n"));
    client.print(F("Accept: */*\r\n"));
    client.print(F("Connection: close\r\n"));
    client.print(F("Content-Type: multipart/form-data; boundary=X-ESP8266_MULTIPART\r\n"));
    String tmpFront = "--X-ESP8266_MULTIPART\r\nContent-Disposition: form-data; name=\"file\"; filename=\"";
    tmpFront += file.name();
    tmpFront += "\"\r\n";
    if(this->binary) {
      tmpFront += "Content-Type: application/octet-stream\r\n";
    }
    tmpFront += "\r\n";
    String tmpBack = "\r\n--X-ESP8266_MULTIPART--\r\n\r\n";
    int dataLength = tmpFront.length() + tmpBack.length() + file.size();
    client.print(F("Content-Length: ")); client.print(dataLength); client.print(F("\r\n\r\n"));
    client.print(tmpFront);
    int tempPos = file.position();
    file.seek(0, SeekSet);
    if(this->binary) {
      uint8_t dataBuffer[128];
      while(file.available()) {
        while(file.position() < file.size()) {
          size_t len = file.readBytes((char *)dataBuffer, sizeof(dataBuffer));
          client.write(dataBuffer, len);
        }
      }
    } else {
      while(file.available()) {
        while(file.position() < file.size()) {
          String dataBuffer = file.readStringUntil('\n');
          client.print(dataBuffer);
          client.print("\n");
        }
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


