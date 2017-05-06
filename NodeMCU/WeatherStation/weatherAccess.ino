#include <ESP8266WiFi.h>

const char* ssid     = "your-SSID";
const char* password = "your-pw";

const char* host = "api.wunderground.com";                        // API site host

void setup()  
{
  String weather = "";
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
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  
  // We now create a URI for the request
  String url = "http://api.wunderground.com/api/<yourAPI_Key>/conditions/q/<Country>/<City>.json";
  
  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    weather += line;
    weather += "\r";
  }

  //Serial.println(weather);
  int s = weather.indexOf("station_id");
  int w = weather.indexOf("\"weather\":");
  int t = weather.indexOf("temp_c");
  int h = weather.indexOf("relative_humidity");
  String station = "";
  String wN = "";
  String temp = "";
  String humidity = "";
  
  for(int i = t + 8;weather[i]!= ',';i++)
  {
    temp += weather[i]; 
  }

  for(int i = h + 20;weather[i]!= '"';i++)
  {
    humidity += weather[i];
  }

  for(int i = w + 11;weather[i]!= '"';i++)
  {
    wN += weather[i];
  }

  for(int i = s + 13;weather[i]!= '"';i++)
  {
    station += weather[i];
  }


  Serial.println("**Weather access provided by Wunderground API**");
  Serial.print("\tStation: " + station + "\n" + "\tWeather: " + wN + "\n" + "\tTemperature: " + temp + 
                " degree Celcius" + "\n" + "\tRelative Humidity: " + humidity);
  Serial.println();
  Serial.println("closing connection"); 
}

void loop() 
{
 
}
