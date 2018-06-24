# ESP8266_multipart
## Installation
(Arduino IDE) Download this repository as a zip file and extract it to your arduino library folder. https://github.com/nailujx86/ESP8266_multipart/archive/master.zip  
Now don't forget to include the header file in your includes.
## Usage
``` cpp
// Header include
#include<ESP8266_multipart.h>

// Code
ESP8266_multipart multipart("myexampleserver.com"); // Sets the host to myexampleserver.com and the port to 80
multipart.setPort(8772); // Sets the port to 8772
int status = multipart.sendFile("/path/to/send/data/to", fileObject);
/**
 * status == 0 -> couldn't connect to server
 * status != 0 -> HTTP Status Code returned by server
 */
```