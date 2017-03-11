// Testing serial1 writing between Teensy boards
//Slave
int lights = 1;
int ignition = 0;
int highbeams = 1;
int ch1 = 0;
String systemtime;
int ledpin = 13;
String unitname = "Lower";
String mastername = "Upper";
//String outgoingbuffer = "";
// trying out variables for the incoming buffer here instead

void setup() {
  // put your setup code here, to run once:
pinMode(ledpin, OUTPUT);
Serial.begin(9600);
Serial1.begin(9600);
delay(1000);
Serial.println("setup complete...");
}

void loop() {
while(Serial1.available() > 0){
  serialread();
  serialdiagnostic();
  Serial1.println((String)"TFourR/Lower -> Upper/T-" + systemtime + "/I" + ignition + "/L" + lights + "/H" + highbeams + "/CH1" + ch1 + "/");
  
//systemtime = millis();
 // while (systemtime != temptime) //check to make sure time is reading
 // {
  //tempch1 = ch1; //set temp value to actual
  
  digitalWrite(ledpin, ch1); //and write it

  //read the actual sensors in there

  //send it
 // Serial1.println(outgoingbuffer);
  //repeat the whole sheband for diagnostic
  //Serial.println(outgoingbuffer);
 // outgoingbuffer = ""; //clear the buffer after its beensent
  delay(20);
  }
  //Serial.println("time no good");
  //delay(200);
//}
Serial.println("Serial 1 not found");
//Serial.println((String)"TFourR/Lower -> Upper/T-" + systemtime + "/I" + ignition + "/L" + lights + "/H" + highbeams + "/CH1" + ch1 + "/");
delay(200);
}

void serialread() { //serial read function
  delay (20);
  String discard = Serial1.readStringUntil('-');
  systemtime = Serial1.readStringUntil('/');
  String tempignition = Serial1.readStringUntil('/');
  String templights = Serial1.readStringUntil('/');
  String temphighbeams = Serial1.readStringUntil('/');
  String tempch1 = Serial1.readStringUntil('/');
  //temptime = systemtime;
  ignition = tempignition.toInt();
  lights = templights.toInt();
  highbeams = temphighbeams.toInt();
  ch1 = tempch1.toInt();
}

void serialdiagnostic() { //diagnostic readout for USB serial port
    Serial.println((String)"TFourR/" + unitname +" > " + mastername + "/T-" + systemtime + "/I" + ignition + "/L" + lights + "/H" + highbeams + "/CH1" + ch1 + "/");
  }

void serialsend()  { //send the outgoing serial data
  Serial1.println((String)"TFourR/" + unitname + " > " + mastername + "/T-" + systemtime + "/I" + ignition + "/L" + lights + "/H" + highbeams + "/CH1" + ch1 + "/");
}


