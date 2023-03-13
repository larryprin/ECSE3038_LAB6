#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "env.h"


#define fan 23
#define light 22


float j;



void setup() {
  // put your setup code here, to run once:
  pinMode(fan, OUTPUT);
  pinMode(light, OUTPUT);
 

  Serial.begin(9600);
	
	// WiFi_SSID and WIFI_PASS should be stored in the env.h
  WiFi.begin(WIFI_SSID, WIFI_PASS);

	// Connect to wifi
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}
void loop() {
  // put your main code here, to run repeatedly:
  if(WiFi.status()== WL_CONNECTED){
    HTTPClient http;
  
    http.begin(endpoint);
    
        http.addHeader("Content-type", "application/json");
        http.addHeader("Content-length", "23");
        StaticJsonDocument<23>doc;
         String httpRequestData;
          j = random(21.0,33.0);
         doc["Temperature"] = j;
      
       
        serializeJson(doc, httpRequestData);
	      int http_Response_Code= http.PUT(httpRequestData);
        String http_response;
        if(http_Response_Code>0)
    {
      Serial.print("HTTP Response Code: ");
      Serial.println(http_Response_Code);
      Serial.print("Response from server");
      http_response=http.getString();
      Serial.println(http_response);

    }
    else{
      Serial.print("Error code: ");
      Serial.println(http_Response_Code);
    }
     delay(2000);
      http.end();

 String httpResponse;
 int httpResponseCode = http.GET();
 if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);

        Serial.print("Response from server: ");
        httpResponse = http.getString();
        Serial.println(httpResponse);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      // Free resources
      http.end();

StaticJsonDocument<1024> doc2;

      DeserializationError error = deserializeJson(doc2, httpResponse);

      if (error) {
        Serial.print("deserializeJson() failed: ");
        Serial.println(error.c_str());
        return;
      }
         
         bool fanstate = doc2["fan"];
         bool lightstate = doc2["light"];

         Serial.println("");

    Serial.print("fan is : ");
    Serial.println(fanstate);

    Serial.print("light is: ");
    Serial.println(lightstate);

    Serial.println("");

if (fanstate==1)
    {
      digitalWrite(fan,HIGH);
    }
    else
    {
      digitalWrite(fan,LOW);
    }

    if (lightstate==1)
    {
      digitalWrite(light,HIGH);
    }
    else
    {
      digitalWrite(light,LOW);
    }


    }   
