#include <Wire.h>

#define Self_address 0x9
#define Remote_address 0x8

int ledPin = 13; //LED pin for troubleshooting output
int lights = 0;
int ignition = 0;
int led = 0;
unsigned long systemtime = 0;
int out1 = 255; //main output variable

void setup() {
 pinMode(ledPin, OUTPUT);
 Serial.begin(9600);
 delay(1000);
 Serial.println("setting up");
 digitalWrite(ledPin, HIGH); //make LED low on first boot
 Wire.begin(Self_address);
 //Wire.onReceive(receiveMessage);
 //Wire.onRequest(requestMessage);
}

void loop() 
{
  delay(1000);
  digitalWrite(ledPin, LOW);
  systemtime = millis(); //update the system time from from millis to be called later
    Serial.println("Sending message");
    Wire.beginTransmission(0x8);
    //Wire.write("TFourR/");
    Wire.write(out1);
    //Wire.write(Remote_address);
    //Wire.write(systemtime);
    //Wire.write(lights);
    //Wire.write(ignition);
    Wire.endTransmission();
    Serial.print("TFourR/");
    Serial.print(Self_address);
    Serial.print(Remote_address);
    Serial.print("/");
    Serial.print(systemtime);
    Serial.print("/");
    Serial.write(lights);
    Serial.print("/");
    Serial.println(ignition);
   //}
   
  delay(100);

Serial.println("No wire available");
}
/*void receiveMessage(int howMany){ //receive message from master
 while (Wire.available() > 0){
   Serial.println("New message incoming from master...");
   digitalWrite(ledPin, HIGH);
 }
 Serial.println("Error Mode 1");
 delay(100);
}
*/
/*void requestMessage(){ //change to int
  while (Wire.available() > 0) {
    Serial.println("Message requested by master...");
    Wire.beginTransmission(Remote_address);
    Wire.write("TFourR/");
    Wire.write(Self_address);
    Wire.write(Remote_address);
    Wire.write(systemtime);
    Wire.write(lights);
    Wire.write(ignition);
    Wire.endTransmission();
    Serial.print("TFourR/");
    Serial.print(Self_address);
    Serial.print(Remote_address);
    Serial.print("/");
    Serial.print(systemtime);
    Serial.print("/");
    Serial.write(lights);
    Serial.print("/");
    Serial.println(ignition);
    }
    Serial.println("fuck");
}
*/
