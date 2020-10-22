# ESP8266_multipart
[![Buy us a tree](https://img.shields.io/badge/Treeware-%F0%9F%8C%B3-lightgreen?style=for-the-badge)](https://plant.treeware.earth/nailujx86/ESP8266_multipart)
## License
This package is [Treeware](https://treeware.earth). If you use it in production, then we ask that you [**buy the world a tree**](https://plant.treeware.earth/nailujx86/ESP8266_multipart) to thank us for our work. By contributing to the Treeware forest you’ll be creating employment for local families and restoring wildlife habitats.
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
