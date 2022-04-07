#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>



#define STASSID "SSID"
#define STAPSK  "PASSWORD"


const char* ssid = STASSID;
const char* password = STAPSK;

int CO2Val=0;

ESP8266WebServer server(80);


void handleRoot() {
      server.sendHeader("Access-Control-Allow-Origin", "*");

  server.send(200, "text/plain", "Connected");
}
void handle_CO2_current() {
      server.sendHeader("Access-Control-Allow-Origin", "*");

  server.send(200, "text/plain", String(CO2Val));
  CO2Val++; //for test purpose
}

void setup(void) {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());


  server.on("/", handleRoot);
  server.on("/CO2_current",handle_CO2_current );



  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
}