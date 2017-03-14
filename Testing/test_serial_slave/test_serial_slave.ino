// Testing serial1 writing between Teensy boards
//Slave
//serial vars
int voltage = 1325;
int lightsstate = 1;
int ignitionstate = 0;
int highbeamsstate = 1;
int ch1state = 0;
int ch2state = 0;
int ch3state = 0;
int ch4state = 0;
int ch5state = 0;
int ch6state = 0;
int systemtime;
String unitname = "Lower";
String mastername = "Upper";
//end vars needed for serial

//output vars
int ch1pin = 13; //most likely would be 6 
int ch2pin = 23;
int ch3pin = 22;
int ch4pin = 21;
int ch5pin = 20;
int ch6pin = 5;

//fan pin

int fanpin = 11;
int fanstate = 0;

//input sensing vars
int ignitionpin = 17;
int lightspin = 16;
int highbeamspin = 15;
int voltagepin = 14;

void setup() {
  // put your setup code here, to run once:
//Main output pins
pinMode(ch1pin, OUTPUT);
pinMode(ch2pin, OUTPUT);
pinMode(ch3pin, OUTPUT);
pinMode(ch4pin, OUTPUT);
pinMode(ch5pin, OUTPUT);
pinMode(ch6pin, OUTPUT);

//main input pins
pinMode(ignitionpin, INPUT);
pinMode(lightspin, INPUT);
pinMode(highbeamspin, INPUT);
pinMode(voltagepin, INPUT);

//fan pin
pinMode(fanpin, OUTPUT);

Serial.begin(9600);
Serial1.begin(9600);
delay(1000);
Serial.println("setup complete...");
}

void loop() {
//systemtime ++;
//read the actual sensors in here
lightsstate = digitalRead(lightspin);
ignitionstate = digitalRead(ignitionpin);
highbeamsstate = digitalRead(highbeamspin);
voltage = analogRead(voltagepin) * 10; //voltage multiplier here

//write out the desired outputs
analogWrite(ch1pin, ch1state); //and write it
analogWrite(ch2pin, ch2state);
analogWrite(ch3pin, ch3state);
analogWrite(ch3pin, ch3state);
analogWrite(ch4pin, ch4state);
analogWrite(ch5pin, ch5state);
analogWrite(ch6pin, ch6state);

digitalWrite(fanpin, fanstate);

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
  //int tempvoltage2 = tempvoltage.toInt(); //We're sending this not receving it
  systemtime = tempsystemtime.toInt();
  //ignitionstate = tempignition.toInt();
  //lightsstate = templights.toInt();
  //highbeamsstate = temphighbeams.toInt();
  ch1state = tempch1.toInt();
  ch2state = tempch2.toInt();
  ch3state = tempch3.toInt();
  ch4state = tempch4.toInt();
  ch5state = tempch5.toInt();
  ch6state = tempch6.toInt();
}
void serialdiagnostic() { //diagnostic readout for USB serial port
    Serial.println((String)"TFourR/" + unitname +" > " + mastername + "/T-" + systemtime + "/V" + voltage + "/I" + ignitionstate + "/L" + lightsstate + "/H" + highbeamsstate + "/CH1" + ch1state + "/CH2" + ch2state + "/CH3" + ch3state + "/CH4" + ch4state + "/CH5" + ch5state + "/CH6" + ch6state + "/");
  }

void serialsend()  { //send the outgoing serial data
  Serial1.println((String)"TFourR/" + unitname +" > " + mastername + "/T-" + systemtime + "/" + voltage + "/" + ignitionstate + "/" + lightsstate + "/" + highbeamsstate + "/" + ch1state + "/" + ch2state + "/" + ch3state + "/" + ch4state + "/" + ch5state + "/" + ch6state + "/");
}


