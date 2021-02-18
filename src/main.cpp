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
//#include <Servo.h>
//#include <WiFiMDNSResponder.h>
#include "RestServer.h"


#include "arduino_secrets.h" 
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;                 // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;


WiFiServer server(80);

RestServer rest(server);
char mdnsName[] = "wifiAuto"; 
// Create a MDNS responder to listen and respond to MDNS name requests.
//WiFiMDNSResponder mdnsResponder;
//Servo myservo;

void digital(char * params = "") {

  rest.addData(HTTP_COMMON_HEADER);
  rest.addData("hello", "didiiidid");
  rest.addData("lorem", "ipsum");
    Serial.println("digital");

}

void analog(char * params = "") {
  rest.addData(HTTP_COMMON_HEADER);
  rest.addData("random-text", "tötum");
  rest.addData("test", (int)1);
  rest.addData("lorem", "ipsum");
  Serial.println("analog");


}
void favicon(char * params = "") {
  rest.addData(HTTP_REDIRECTION_HEADER);



 // rest.addData("HTTP/1.1 302 Moved Permanently ");
  rest.addData("Location: http://octopi.local/static/img/tentacle-32x32.png");
  
  Serial.println("favicon.ico");
}



void printWiFiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}



void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }

  // attempt to connect to WiFi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);

  }
  server.begin();
  // you're connected now, so print out the status:
  printWiFiStatus();




 

  rest.addRoute(ANY, "/digital", digital);
  rest.addRoute(ANY, "/analog", analog);
  rest.addRoute(ANY, "/favicon.ico", favicon);


  
}


void loop() {


rest.run();

 
}


