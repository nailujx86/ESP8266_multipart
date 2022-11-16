#include "WiFi.h"
#include "FS.h"

class ESP32_multipart {
  public:
    ESP32_multipart();
    ESP32_multipart(String host);
    ESP32_multipart(const char* host);
    int sendFile(String path, File file);
    int sendFile(const char* path, File file);
    void setPort(int port);
    void setHost(String host);
    void setHost(const char* host);
    void setBinary(bool binary);
  private:
    const char* host;
    int port;
    bool binary;
    void init(const char* host, int port);
};


