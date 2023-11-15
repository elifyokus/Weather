#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";

const String url = "http://api.weatherapi.com/v1/current.json?key=bf453ccfe0e04a72aa3113052222205&q=Elazig&aqi=yes";

void setup() 
{
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }

  Serial.print("OK! IP=");
  Serial.println(WiFi.localIP());

  Serial.print("Bekleniyor " + url + "... ");

  HTTPClient http;
  http.begin(url);
  int httpResponseCode = http.GET();
  
  String data = "{}";
  float okunanArr[4];
  
  if (httpResponseCode>0) 
  {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    data = http.getString();
  }
  else 
  {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }

  http.end();
  
  JSONVar havaJson = JSON.parse(data);

  if (JSON.typeof(havaJson) == "undefined") 
  {
    Serial.println("Veri ayristirilamadi!");
    return;
  }

  Serial.println();
  Serial.print("JSON nesnesi = ");
  Serial.println(havaJson);

  Serial.println();
  Serial.println("-----------------HAVA DURUMU------------------");
  Serial.print("Hava sicakligi: ");
  Serial.println(havaJson["current"]["temp_c"]);

  Serial.print("Hissedilen sicaklik: ");
  Serial.println(havaJson["current"]["feelslike_c"]);

  Serial.print("Atmosferik basinc: ");
  Serial.println(havaJson["current"]["pressure_mb"]);

  Serial.print("Nem: ");
  Serial.println(havaJson["current"]["humidity"]);

  Serial.print("Ruzgar hizi: ");
  Serial.println(havaJson["current"]["wind_mph"]);
}

void loop() 
{
  delay(100); 
}
