#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include "ThingSpeak.h"
#include <ESP8266WiFi.h>

static const int RXPin = 12, TXPin = 13;
static const uint32_t GPSBaud = 9600;
 
// repace your wifi username and password
const char* ssid     = "j##";
const char* password = "w#####";

unsigned long myChannelNumber = 970279;
const char * myWriteAPIKey = "PMB0W######1";

// The TinyGPS++ object
TinyGPSPlus gps;
WiFiClient  client;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin); 

void setup()
{
  Serial.begin(115200);
  ss.begin(GPSBaud);
  Serial.println(F("DeviceExample.ino"));
  Serial.println(F("A simple demonstration of TinyGPS++ with an attached GPS module"));
  Serial.print(F("Testing TinyGPS++ library v. ")); Serial.println(TinyGPSPlus::libraryVersion());
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
  Serial.print("Netmask: ");
  Serial.println(WiFi.subnetMask());
  Serial.print("Gateway: ");
  Serial.println(WiFi.gatewayIP());
  ThingSpeak.begin(client);
  
}

void loop()
{
  // This sketch displays information every time a new sentence is correctly encoded.
  while (ss.available() > 0)
    if (gps.encode(ss.read()))
      displayInfo();

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    while(true);
  }
}
void displayInfo()
{
  Serial.println(F("Location: ")); 
  if (gps.location.isValid())
  {

    double latitude = (gps.location.lat());
    double longitude = (gps.location.lng());
    
    String latbuf;
    latbuf += (String(latitude, 6));
    Serial.println(latbuf);

    String lonbuf;
    lonbuf += (String(longitude, 6));
    String place;

    Serial.println(lonbuf);

    ThingSpeak.setField(1, latbuf);
    ThingSpeak.setField(2, lonbuf);
    if(TinyGPSPlus::distanceBetween(latitude, longitude,24.759636, 92.787895) < 10)
    {
          place+="9";
      ThingSpeak.setField(3, place);
     Serial.println(("AT HOSTEL "));
    }
    else if(TinyGPSPlus::distanceBetween(latitude, longitude, 24.759135, 92.788302) < 10)
    {
          place+="1";
      ThingSpeak.setField(3, place);
     Serial.println(F("H-8"));
    }
    else if(TinyGPSPlus::distanceBetween(latitude, longitude, 24.758645, 92.788291) < 10)
    {
          place+="2";
      ThingSpeak.setField(3, place);
     Serial.println(F("H-4"));
    }
    else if(TinyGPSPlus::distanceBetween(latitude, longitude, 24.757977, 92.788382) < 10)
    {
          place+="3";
      ThingSpeak.setField(3, place);
     Serial.println(F("TeaPoint"));
    }
    else if(TinyGPSPlus::distanceBetween(latitude, longitude, 24.757681, 92.787195) < 10)
    {
          place+="4";
      ThingSpeak.setField(3, place);
     Serial.println(F("P.G"));
    }
    else if(TinyGPSPlus::distanceBetween(latitude, longitude, 24.757032, 92.788426) < 10)
    {
          place+="5";
      ThingSpeak.setField(3, place);
     Serial.println(F("SAC"));
    }
    else if(TinyGPSPlus::distanceBetween(latitude, longitude, 24.758024, 92.790308) < 10)
    {
          place+="6";
      ThingSpeak.setField(3, place);
     Serial.println(F("NEW GALLERY"));
    }
    
    ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);  
    delay(20000);
    
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F("Date/Time: "));

  if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.year());
  }
  else
  {
    Serial.print(F("INVALID"));
    }

  Serial.print(F(" "));
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(F(":"));
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(F(":"));
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(F("."));
    if (gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.print(gps.time.centisecond());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.println();
}
