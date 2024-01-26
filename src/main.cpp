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
// #include <Servo.h>
// #include <WiFiMDNSResponder.h>
#include "RestServer.h"
#include "index_html.h"
#include "script_html.h"

#include "arduino_secrets.h"
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID; // your network SSID (name)
char pass[] = SECRET_PASS; // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;          // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;

int fullValue = 500;
int emptyValue = 10;

WiFiServer server(80);

RestServer rest(server);
char mdnsName[] = "MoccaMaster";
// Create a MDNS responder to listen and respond to MDNS name requests.
// WiFiMDNSResponder mdnsResponder;
// Servo myservo;

void full(char *params = "")
{

  rest.addData(HTTP_JSON_HEADER);

  fullValue = analogRead(0) - 15;

  // Serial.println("full");
  rest.addData("{");
  rest.addData("value", fullValue);
  rest.addData("fullValue", fullValue);
  rest.addData("emptyValue", emptyValue);

  rest.addData("\"status\":\"full\"");
  rest.addData("}");
}

void empty(char *params = "")
{
  rest.addData(HTTP_JSON_HEADER);
  // Serial.println("emty");
  emptyValue = analogRead(0) + 15;
  rest.addData("{");
  rest.addData("value", emptyValue);
  rest.addData("fullValue", fullValue);
  rest.addData("emptyValue", emptyValue);

  rest.addData("\"status\":\"empty\"");

  rest.addData("}");
}

void favicon(char *params = "")
{
  rest.addData(HTTP_REDIRECTION_HEADER);

  // rest.addData("HTTP/1.1 302 Moved Permanently ");
  rest.addData("Location: http://172.19.76.107/static/img/tentacle-32x32.png");

  //  Serial.println("favicon.ico");
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



void coffeePotStatus(char *params = "")
{
  rest.addData(HTTP_JSON_HEADER);

  // Serial.println("CofeePotStatus");

  //String s = INDEX_page; // Read HTML contents
                         // server.send(200, "text/html", s); //Send web page
  // rest.addData( INDEX_page);
  // rest.addData("<!DOCTYPE html> <html lang=\"en\"> <head>\n<title>Bootstrap Example</title>\n<meta charset=\"utf-8\">\n<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/css/bootstrap.min.css\">\n<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js\"></script>\n<script src=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/js/bootstrap.min.js\"></script> \n </head>\n <body>  <div class=\"container\"><h2>Responsive Embed</h2><p>Create a responsive video and scale it nicely to the parent element with an 16:9 aspect ratio</p><div class=\"embed-responsive embed-responsive-16by9\"><iframe class=\"embed-responsive-item\" src=\"https://www.youtube.com/embed/tgbNymZ7vqY\"> </iframe> \n </div>\n</div>\n</body> \n</html>");

  int value = analogRead(0);

  rest.addData("{");
  rest.addData("value", value);
  rest.addData("fullValue", fullValue);
  rest.addData("emptyValue", emptyValue);
  if (value >= fullValue)
  {
    rest.addData("\"status\":\"full\"");
  }
  else if (value <= emptyValue)
  {
    rest.addData("\"status\":\"empty\"");
  }
  else
  {
    rest.addData("\"status\":\"in-between\"");
  }
  rest.addData("}");
}

void printWiFiStatus()
{
  Serial.begin(9600);
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

void setup()
{
  // Initialize serial and wait for port to open:
  Serial.begin(9600);

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD)
  {
    // Serial.println("WiFi shield not present");
    //  don't continue:
    while (true)
      ;
  }

  // attempt to connect to WiFi network:
  while (status != WL_CONNECTED)
  {
    //  Serial.print("Attempting to connect to SSID: ");
    // Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(3000);
  }
  server.begin();
  // you're connected now, so print out the status:
 // printWiFiStatus();

  rest.addRoute(ANY, "/full", full);
  rest.addRoute(ANY, "/empty", empty);
  rest.addRoute(ANY, "/script.js", script);
  // delay(500);
  // endpoitn for cofeepotstatus
  rest.addRoute(ANY, "/status", coffeePotStatus);

  rest.addRoute(ANY, "/favicon.ico", favicon);
  rest.addRoute(ANY, "/", index);

}

void loop()
{
  // delay(100);
  rest.run();
}
