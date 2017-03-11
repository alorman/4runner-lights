// Testing serial1 writing between Teensy boards
//Slave
//serial vars
float voltage = 0;
int lights = 1;
int ignition = 0;
int highbeams = 1;
int ch1 = 0;
int ch2 = 0;
int ch3 = 0;
int ch4 = 0;
int ch5 = 0;
int ch6 = 0;
int systemtime;
String unitname = "Lower";
String mastername = "Upper";

//output vars
int ledpin = 13;
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
//systemtime ++;
serialdiagnostic();
if(Serial1.available() > 0){
  serialread();
  digitalWrite(ledpin, ch1); //and write it
  delay(20);
  }
//read the actual sensors in here
 else{
  serialsend();
 }

delay(50);
}

void serialread() { //serial read function. Use this area to adjust what gets listened to
  delay (40);
  String discard = Serial1.readStringUntil('-');
  String tempsystemtime = Serial1.readStringUntil('/');
  String tempvoltage = Serial1.readStringUntil('/');
  String tempignition = Serial1.readStringUntil('/');
  String templights = Serial1.readStringUntil('/');
  String temphighbeams = Serial1.readStringUntil('/');
  String tempch1 = Serial1.readStringUntil('/');
  String tempch2 = Serial1.readStringUntil('/');
  String tempch3 = Serial1.readStringUntil('/');
  String tempch4 = Serial1.readStringUntil('/');
  String tempch5 = Serial1.readStringUntil('/');
  String tempch6 = Serial1.readStringUntil('/');
  int tempvoltage2 = tempvoltage.toInt();
  tempvoltage = tempvoltage2 * (5.0 / 1025); //adjust voltage offset value here
  systemtime = tempsystemtime.toInt();
  ignition = tempignition.toInt();
  lights = templights.toInt();
  highbeams = temphighbeams.toInt();
  ch1 = tempch1.toInt();
  ch2 = tempch1.toInt();
  ch3 = tempch1.toInt();
  ch4 = tempch1.toInt();
  ch5 = tempch1.toInt();
  ch6 = tempch1.toInt();
}
void serialdiagnostic() { //diagnostic readout for USB serial port
    Serial.println((String)"TFourR/" + unitname +" > " + mastername + "/T-" + systemtime + "/I" + ignition + "/L" + lights + "/H" + highbeams + "/CH1" + ch1 + "/CH2" + ch2 + "/CH3" + ch3 + "/CH4" + ch4 + "/CH5" + ch5 + "/CH6" + ch6 + "/");
  }

void serialsend()  { //send the outgoing serial data
  Serial1.println((String)"TFourR/" + unitname +" > " + mastername + "/T-" + systemtime + "/I" + ignition + "/L" + lights + "/H" + highbeams + "/CH1" + ch1 + "/CH2" + ch2 + "/CH3" + ch3 + "/CH4" + ch4 + "/CH5" + ch5 + "/CH6" + ch6 + "/");
}


