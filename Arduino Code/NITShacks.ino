
#include <TinyGPS.h>
//#include <BoltDeviceCredentials.h>
//#include <BoltIoT-Arduino-Helper.h>
#include "ThingSpeak.h"

#include <LiquidCrystal.h> 
#include <SoftwareSerial.h>
#include<Wire.h>


#define trigger 19
#define echo 18
 TinyGPS gps; // create gps object 
 
LiquidCrystal lcd(10,11,12,5,6,7);

SoftwareSerial mySerial(8,9);
SoftwareSerial gpsSerial(3,4);//rx,tx 
SoftwareSerial Serialmc(10, 11);
 
const int MPU_addr=0x68;  // I2C address of the MPU-6050
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
float lat = 28.5458,lon = 77.1703;
float time=0,distance=0;
 int pin =5;
unsigned long duration;
String str;
unsigned long myChannelNumber =  978582;
const char * myWriteAPIKey = "QQDSA5BAIFU0DBI4";

void setup()
{ Serial.begin(115200);
  Serialmc.begin(115200);
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
    gpsSerial.begin(115200);
  mySerial.begin(115200);
 lcd.begin(16,2);
 pinMode(trigger,OUTPUT);
 pinMode(echo,INPUT);
 lcd.print(" Ultra sonic");
 lcd.setCursor(0,1);
 lcd.print("Distance Meter");
 delay(1000);
 lcd.clear();
 lcd.print(" Circuit Digest");
   pinMode(pin, INPUT);

 delay(2000);
}
 
String data;
uint8_t dataRead = 0;

void loop()
{ 
  //>>>>>>>>>>>>>>>distance
          duration = pulseIn(pin, HIGH);
          distance=duration/10;
//lcd.clear();
 //digitalWrite(trigger,LOW);
// delayMicroseconds(2);
// digitalWrite(trigger,HIGH);
// delayMicroseconds(10);
 //digitalWrite(trigger,LOW);
 ///delayMicroseconds(2);
 //time=pulseIn(echo,HIGH);
 //lcd.clear();
 //lcd.setCursor(0,1);
 //lcd.print("Distance:");
// lcd.print(distance);
// lcd.print("mm");
           Serial.print("distance: ");
           Serial.print( distance);
            ThingSpeak.setField(1, distance);
           Serial.print(" mm,time: ");
           Serial.print( duration); 
           Serial.println("us");
  delay(500);
//>>>>>>>>>>>>>>>>VERTICAL ACC.
Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  Serial.print("AcX = "); Serial.print(AcX);
  Serial.print(" | AcY = "); Serial.print(AcY);
  Serial.print(" | AcZ = "); Serial.print(AcZ);
  Serial.print(" | Tmp = "); Serial.print(Tmp/340.00+36.53);  //equation for temperature in degrees C from datasheet
  Serial.print(" | GyX = "); Serial.print(GyX);
  Serial.print(" | GyY = "); Serial.print(GyY);
  Serial.print(" | GyZ = "); Serial.println(GyZ);
  ThingSpeak.setField(2, AcZ);
  delay(500);
  //>>>>>>>>>>>>>>>>>>>>GPS NEO
  while(gpsSerial.available()){ // check for gps data 
  if(gps.encode(gpsSerial.read()))// encode gps data 
  {  
  gps.f_get_position(&lat,&lon); // get latitude and longitude 
   // printFloat(gps.f_speed_kmph());
  } 
} 
String latitude = String(lat,6); 
  String longitude = String(lon,6); 
Serial.println(latitude+" ; "+longitude); 
//>>>>>>>>>>>>>DATA_to_ESP
  str =String(distance)+String(',')+String(AcZ)+String(',')+String(latitude)+String(',')+String(longitude)+String(',')+String(AcX)+String('*');
  Serialmc.println(str);
  delay(500);
  
   //>>>>>>>>>>>>>>>>>SEE IF TITAN WANTS ANYTHING(telgram_message_check)
/*message m = bot.getUpdates(); // Read new messages   
if (m.text.equals("on"))  
      {   
  digitalWrite(LED, 1);    
  bot.sendMessage(m.chat_id, "The Led is now ON");   
}   
else if (m.text.equals("off"))  
      {   
  digitalWrite(LED, 0);    
  bot.sendMessage(m.chat_id, "The Led is now OFF");   
}   
*/  

  //>>>>>>>>>>>>>>>>>>>>BOLT iot...
 /* if (mySerial.available() > 0) 
  {
    delay(50);
    String readData = "";
    Serial.print("cmd from bolt:");
    while (mySerial.available() > 0 ) {
      readData = readData + (char)mySerial.read();
    }
    Serial.println(readData);
    if (readData.indexOf("RD") != -1) {
      String data = sensor_data_to_push(distance,AcZ);
      mySerial.print(data);
      Serial.print("data sent to bolt:");
      Serial.print(data);
    }
  }*/
  
  
}
/*
String sensor_data_to_push(float distance,int16_t acz) {
  String data;
  data = String(distance)+ "," + String(acz);;
  return data;
}*/
