/*
  WiFi Web Server

 A simple web server that shows the value of the analog input pins.
 using a WiFi shield.

 This example is written for a network using WPA encryption. For
 WEP or WPA, change the WiFi.begin() call accordingly.

 Circuit:
 * WiFi shield attached
 * Analog inputs attached to pins A0 through A5 (optional)

 created 13 July 2010
 by dlf (Metodo2 srl)
 modified 31 May 2012
 by Tom Igoe

 */

#include <SPI.h>
#include <WiFi101.h>
#include <sstream>
// #include <Servo.h>
// #include <WiFiMDNSResponder.h>
#include "RestServer.h"
#include "index_html.h"
#include "script_html.h"
#include "PubSubClient.h"

#include "arduino_secrets.h"
#include <Stream.h>

///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID; // your network SSID (name)
char pass[] = SECRET_PASS; // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;          // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;

int fullValue = 500;
int emptyValue = 10;
int coffeemqttinterval = 1000;
int lastMillis = 0;

IPAddress ip;
int analogPin = 6;
WiFiServer server(80);

// pu
WiFiClient wifiClient;
// pubsubclient
PubSubClient client(wifiClient);
const char *mqtt_server = "172.19.76.103";

RestServer rest(server);
char mdnsName[] = "MoccaMaster";
// Create a MDNS responder to listen and respond to MDNS name requests.
// WiFiMDNSResponder mdnsResponder;
// Servo myservo;

void full(char *params = "")
{

  rest.addData(HTTP_JSON_HEADER);

  
  rest.addData("{");
  rest.addData("fullValue", fullValue);
  rest.addData("}");
}

void empty(char *params = "")
{
  rest.addData(HTTP_JSON_HEADER);
  LOG("getEmty");
  rest.addData("{");
  rest.addData("emptyValue", emptyValue);
  rest.addData("}");
}

void favicon(char *params = "")
{
  rest.addData(HTTP_REDIRECTION_HEADER);
  rest.addData("Location: http://172.19.76.107/static/img/tentacle-32x32.png");
}

void index(char *params = "")
{
  rest.addData(HTTP_COMMON_HEADER);
  String s = INDEX_page;
  rest.addData(INDEX_page);
}

void script(char *params = "")
{
  rest.addData(HTTP_COMMON_HEADER);
  String s = SCRIPT_page;
  rest.addData(SCRIPT_page);
}

// get coffee pot status const char* getCoffeePotStatus()
char *getCoffeePotStatus()
{
  int value = analogRead(analogPin);
  if (value > fullValue)
  {
    return "\"full\"";
  }
  else if (value < emptyValue)
  {
    return "\"empty\"";
  }
  else
  {
    return "\"inbetween\"";
  }
}

void coffeePotStatus(char *params = "")
{
  rest.addData(HTTP_JSON_HEADER);

  int value = analogRead(analogPin);

  // make new  c styele string for status add "status":  prefix to getcoffeepotstatus


  const char *statusPrefix = "\"status\":";
  

  size_t prefixLen = strlen(statusPrefix);

  const char *cofeepotStatus = getCoffeePotStatus();

  size_t statusLen = strlen(cofeepotStatus);

  // adde status preifx to statusString
  char statusString[prefixLen + statusLen + 1];
  strcpy(statusString, statusPrefix);
  strcat(statusString, cofeepotStatus);

  rest.addData("{");
  rest.addData("value", value);
  rest.addData("fullValue", fullValue);
  rest.addData("emptyValue", emptyValue);

  rest.addData(statusString);




  rest.addData("}");
}
String IpAddress2String(const IPAddress &ipAddress)
{
  return String(ipAddress[0]) + String(".") +
         String(ipAddress[1]) + String(".") +
         String(ipAddress[2]) + String(".") +
         String(ipAddress[3]);
}

void reconnect()
{
  // Loop until we're reconnected
  while (!client.connected())
  {

    // Create a random client ID
    String clientId = "MoccaMasster-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str()))
    {

      LOG("MQTT connected");
      // suvscribe to topics
      client.subscribe("coffeepot/fullLimitValue");
      client.subscribe("coffeepot/emptyLimitValue");

      client.publish("coffeepot/ip", IpAddress2String(ip).c_str());
      LOG("published ip");
      LOG(IpAddress2String(ip));
    }
    else
    {

      // Wait 5 seconds before retrying
      delay(2000);
    }
  }
}

void printWiFiStatus()
{
  // Serial.begin(9600);
  LOG("SSID: ");
  LOG(WiFi.SSID());

  // print your WiFi shield's IP address:
  ip = WiFi.localIP();
  LOG("IP Address: ");
  LOG(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  LOG("signal strength (RSSI):");
  LOG(rssi);
  LOG(" dBm");

  // define char array for ip address

  // convert ip to char array

  // giv ip.ptintto pointer to ipc array

  // reconnect();
}

void callback(char *topic, byte *payload, unsigned int length)
{

  LOG("Message arrived [");
  LOG(topic);
  LOG("] ");
  // change payload to String exluding null terminator
  String payloadString = String((char *)payload).substring(0, length);
  // check if topici is "coffeepot/fullLimitValue"
  if (strcmp(topic, "coffeepot/fullLimitValue") == 0)
  {

    // convert payloadString to int
    fullValue = payloadString.toInt();
  }
  // check if topici is "coffeepot/emptyLimitValue"
  if (strcmp(topic, "coffeepot/emptyLimitValue") == 0)
  {
    // convert payloadString to int
    emptyValue = payloadString.toInt();
  }
}

int lastPublisheSensorValue = 0;
void setup()
{
  // Initialize serial and wait for port to open:
  LOG_SETUP();

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD)
  {
    // LOG("WiFi shield not present");
    //  don't continue:
    while (true)
      ;
  }

  // attempt to connect to WiFi network:
  while (status != WL_CONNECTED)
  {

    status = WiFi.begin(ssid, pass);

    delay(3000);
  }
  server.begin();
  // you're connected now, so print out the status:
  printWiFiStatus();

  rest.addRoute(ANY, "/full", full);
  rest.addRoute(ANY, "/empty", empty);
  rest.addRoute(ANY, "/script.js", script);

  // endpoitn for cofeepotstatus
  rest.addRoute(ANY, "/status", coffeePotStatus);

  rest.addRoute(ANY, "/favicon.ico", favicon);
  rest.addRoute(ANY, "/", index);

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

int lastPublishedSensorValue = 0;
void sendSensorValue()
{
  reconnect();

  int value = analogRead(analogPin);
  LOG(value);
  String valueString = String(value);

  client.publish("coffeepot/value", String(value).c_str());

  // check if sensor value has changed more thren 5
  if (abs(value - lastPublishedSensorValue) > 5)
  {
    lastPublishedSensorValue = value;
    client.publish("coffeepot/value", String(value).c_str());
    client.publish("coffeepot/status", getCoffeePotStatus());
  }
}

void loop()
{

  // call send sensor value ewry 1000ms definer on  coffeemqttinterval
  if (millis() - lastMillis > coffeemqttinterval)
  {
   
    sendSensorValue();
    lastMillis = millis();
  }

  client.loop();

  // delay(100);
  rest.run();
}
