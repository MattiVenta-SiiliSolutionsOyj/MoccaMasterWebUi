#ifndef restserver_h
#define restserver_h
#define N_LOG

// Include Arduino header
#include "Arduino.h"
#include "Log.h"
#include <WiFi101.h>
#include <stdio.h>
#include "RestSettings.h"

struct Routes {
  char * method;
  char * name;
  void (*callback)(char * params);
};

class RestServer {
public:
  RestServer(WiFiServer& client);
  
  void run();
  
  void addRoute(char * method, char * route, void (*f)(char *));
  
  void addData(char* name, String& value);
  void addData(char* name, uint16_t value);
  void addData(char* name, int value);
  void addData(char* name, float value);
  void addData(char* name, char* value);
  void addData(char* value);
private:
  Routes routes_[ROUTES_TOTAL];
  uint8_t routesIndex_;
  char buffer_[OUTPUT_BUFFER_SIZE];
  uint16_t bufferIndex_;
  
  WiFiServer& server_;
  WiFiClient client_;
  
  void check();
  void reset();
  void addToBuffer(char * value);
  void send(uint8_t chunkSize, uint8_t delayTime);
};

#endif