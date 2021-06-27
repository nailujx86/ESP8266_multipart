# ESP8266_multipart
[![Buy us a tree](https://img.shields.io/badge/Treeware-%F0%9F%8C%B3-lightgreen?style=for-the-badge)](https://plant.treeware.earth/nailujx86/ESP8266_multipart)
## License
This package is [Treeware](https://treeware.earth). If you use it in production, then we ask that you [**buy the world a tree**](https://plant.treeware.earth/nailujx86/ESP8266_multipart) to thank us for our work. By contributing to the Treeware forest you’ll be creating employment for local families and restoring wildlife habitats.
## Installation
### PlatformIO
Add the line below to your lib_deps or search for "ESP8266_multipart" in the PlatformIO Library Browser.  
```lib_deps = nailujx86/ESP8266_multipart @ ^1.0.1```  
See more at: https://platformio.org/lib/show/12469/ESP8266_multipart
### Arduino
Search for "ESP8266_multipart" in the Arduino Library Browser  
or  
Download this repository as a zip file and extract it to your arduino library folder. https://github.com/nailujx86/ESP8266_multipart/archive/master.zip  
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
