

#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>


#include "ThingSpeak.h"

int ind1; // , locations
int ind2;
int ind3;
int ind4;
int ind5;
const char* ssid     = "jiko";
const char* password = "weather1";
unsigned long myChannelNumber =  1019289;
const char * myWriteAPIKey = "F38MEM46QE9LZX4K";
String readString; //main captured String
String distance; //data String
String acc;
String latitude;
String longitude;
String xac;

// Initializing TITAN
//const char BotToken[] = "823827689:AAFiOH-bRS9iJTH5qoYYKKx2MgrnRbqZi9U"; 


WiFiClient  client;

void setup() {
  // Open serial communications and wait for port to open:

  Serial.begin(115200);
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
  Serial.println("FETCHING.....");
  while (!Serial) {
    delay(500); // wait for serial port to connect. Needed for native USB port only
  }
 
}

void loop() { // run over and over
  if (Serial.available()) {
    
    char c = Serial.read();
    if (c == '*') {
    Serial.println();
      Serial.print("captured String is : ");
      Serial.println(readString); //prints string to serial port out
     
      ind1 = readString.indexOf(',');  //finds location of first ,
      distance = readString.substring(0, ind1);   //captures first data String
      ind2 = readString.indexOf(',', ind1+1 );   //finds location of second ,
      acc = readString.substring(ind1+1, ind2+1);   //captures second data String
      ind3 = readString.indexOf(',', ind2+1 );
      latitude = readString.substring(ind2+1, ind3+1);
      ind4 = readString.indexOf(',', ind3+1 );
      longitude = readString.substring(ind3+1);
      ind5 = readString.indexOf(',', ind4+1 );
      xac = readString.substring(ind4+1);//captures remain part of data after last ,

     //ThingSpeak.writeField(myChannelNumber, 1,distance, myWriteAPIKey); //Update in ThingSpeak ThingSpeak.setField(1,distance);
     //ThingSpeak.writeField(myChannelNumber, 2,acc, myWriteAPIKey); //Update in ThingSpeak ThingSpeak.setField(2, acc);
     //ThingSpeak.writeField(myChannelNumber, 3, latitude, myWriteAPIKey); //Update in ThingSpeakThingSpeak.setField(3, latitude);
     //ThingSpeak.writeField(myChannelNumber, 5, longitude, myWriteAPIKey); //Update in ThingSpeak ThingSpeak.setField(4, longitude);
    ThingSpeak.setField(6, distance);
    ThingSpeak.setField(5, acc);
    ThingSpeak.setField(1, latitude);
    ThingSpeak.setField(2, longitude);
    ThingSpeak.setField(3, xac);
        
      Serial.print("distance = ");
      Serial.println(distance);
      Serial.print("accZ = ");
      Serial.println(acc);
      Serial.print("accX= ");
      Serial.println(xac);
      Serial.print("latitude = ");
      Serial.println(latitude);
      Serial.print("longitude = ");
      Serial.println(longitude);
      Serial.println();
      Serial.println();
     
      readString=""; //clears variable for new input
      distance="";
      acc="";
      latitude="";
      longitude="";
      xac="";
    } 
    else {     
      readString += c; //makes the string readString
    }
    ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  }

}
