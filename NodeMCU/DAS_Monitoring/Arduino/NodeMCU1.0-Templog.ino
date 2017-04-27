/*
 *  This sketch sends data via HTTP GET requests to Raspberry Pi web server.
 *
 */

#include <ESP8266WiFi.h>

const char* ssid     = "";
const char* password = "";

const char* host = "192.168.0.103";
float t;
String data = "";

float readTemp()
{
  float temp = analogRead(A0);
  temp = (3300*temp/1024);  //Temperature in mV
  temp = temp/10;           //10mV per degree scaling
  return(temp);
}

void setup() {
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("connecting to ");
  Serial.println(host);
}


void loop() {
  t = readTemp();
   
  Serial.println(data);
  data = "GET /addData.php?" + "temp1=" + String(t,2) + " HTTP/1.1\r\nHost: 192.168.0.103\r\nConnection: close\r\n\r\n";  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  if (client.connect(host,80)) 
  {
    // This will send the request to the server
    client.print(data);
    Serial.println("data posted"); 
  }
  else 
  {
    Serial.println("connection failed");
    return;
  }

  delay(300000);
}

