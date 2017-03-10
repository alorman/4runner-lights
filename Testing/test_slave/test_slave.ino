#include <Wire.h>

#define Self_address 0x8
#define Remote_address 0x9

int lightsPin = 14; //initialize the ignition and lights pins with integers and define their pins
int ignitionPin = 15;
int ledPin = 13; //LED pin for troubleshooting output
int lights = 0;
int ignition = 0;
int led = 0;
unsigned long systemtime = 0;
int out1 = 0; //add output variable from master
String test;

void setup() {
 pinMode(ledPin, OUTPUT);
 digitalWrite(ledPin, LOW); //make LED low on first boot
 pinMode(lightsPin, INPUT); //define them as input pins
 pinMode(ignitionPin, INPUT);
 Wire.begin(Self_address);
 Wire.onReceive(receiveMessage);
 Wire.onRequest(requestMessage);
 delay(1000);
 Serial.begin(9600);
 delay(1000);
 Serial.println("setup complete");
}

void loop() 
{
  lights = digitalRead(lightsPin); //read the pins
  ignition = digitalRead(ignitionPin);
  systemtime = millis(); //update the system time from from millis to be called later
  Serial.println("Waiting for input...");
  delay(100);
}

void receiveMessage(int Bytes){ //receive message from master
  Serial.println("received but not understood");
 while (Wire.available() > 0){
   Serial.println("New message incoming from master...");
   digitalWrite(ledPin, HIGH);
   test = "";
   Serial.println(test);
   delay(100);
   digitalWrite(ledPin, LOW);
   delay(100);
 }
 Serial.println("Error Mode 1");
 delay(100);
}


void requestMessage() { //change to int
  Serial.println("requested");
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
    Serial.println("Error Mode 2");
    delay(100);
}
  
