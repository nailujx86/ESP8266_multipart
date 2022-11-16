#include<ESP32_multipart.h>

ESP32_multipart multipart("myexampleserver.com"); // Sets the host to myexampleserver.com and the port to 80
multipart.setPort(8772); // Sets the port to 8772
int status = multipart.sendFile("/path/to/send/data/to", fileObject);
/**
 * status == 0 -> couldn't connect to server
 * status != 0 -> HTTP Status Code returned by server
 */