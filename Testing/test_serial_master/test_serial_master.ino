// Testing serial1 writing between Teensy boards
//Master
//serial vars
int voltage = 0;
int lights = 0;
int ignition = 0;
int highbeams = 0;
int ch1 = 1;
int ch2 = 0;
int ch3 = 0;
int ch4 = 0;
int ch5 = 0;
int ch6 = 0;
int systemtime;
String unitname = "Upper";
String mastername = "Lower";

//output vars
int ledpin = 13;
// trying out variables for the incoming buffer here instead

void setup() {
  // put your setup code here, to run once:
//pinMode(ledpin, OUTPUT);
Serial.begin(9600);
Serial1.begin(9600);
delay(1000);
Serial.println("setup complete...");
}

void loop() {
systemtime ++;
//read the actual sensors in here
//digitalWrite(ledpin, ch1); //and write it

if(Serial1.available() > 0){
  serialread();
  serialdiagnostic();
  }
  
serialsend();
}


void serialread() { //serial read function. Use this area to adjust what gets listened to
  delay (50);
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
  voltage = tempvoltage.toInt(); //voltage remains x100
  //systemtime = tempsystemtime.toInt();
  ignition = tempignition.toInt();
  lights = templights.toInt();
  highbeams = temphighbeams.toInt();
  //ch1 = tempch1.toInt(); //dont overwrite the thigns were trying to send
  //ch2 = tempch2.toInt();
  //ch3 = tempch3.toInt();
  //ch4 = tempch4.toInt();
  //ch5 = tempch5.toInt();
  //ch6 = tempch6.toInt();
  Serial.println(tempvoltage);
}
void serialdiagnostic() { //diagnostic readout for USB serial port
    Serial.println((String)"TFourR/" + unitname +" > " + mastername + "/T-" + systemtime + "/V" + voltage + "/I" + ignition + "/L" + lights + "/H" + highbeams + "/CH1" + ch1 + "/CH2" + ch2 + "/CH3" + ch3 + "/CH4" + ch4 + "/CH5" + ch5 + "/CH6" + ch6 + "/");
  }

void serialsend()  { //send the outgoing serial data
  Serial1.println((String)"TFourR/" + unitname +" > " + mastername + "/T-" + systemtime + "/" + voltage + "/" + ignition + "/" + lights + "/" + highbeams + "/" + ch1 + "/" + ch2 + "/" + ch3 + "/" + ch4 + "/" + ch5 + "/" + ch6 + "/");
}

