// Testing serial1 writing between Teensy boards
  //Slave
  
//Debug
int debug = 1; //set to 1 for advanced debug via usb

//Fan options
int fanconnected = 0; //set to 1 for fan present, 0 for fan not connectioned

//serial vars
int voltage = 0;
float voltagefloat = 0.00;
int lightsstate = 1;
int ignitionstate = 1; 
int highbeamsstate = 0;
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
int ch1pin = 50; //most likely would be 6 
int ch2pin = 51; //testing pins not used
int ch3pin = 5;
int ch4pin = 53;
int ch5pin = 54;
int ch6pin = 55;

//fan pin
int fanpin = 11; //not used in testing
int fanstate = 0;
float fanstarttemp = 100;

//input sensing vars
int ignitionpin = 15; 
int lightspin = 16;
int highbeamspin = 17;
int voltagepin = A4;
int tempsensepin = A0;
float tempF = 0;
int tempsenseraw = 0;

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
pinMode(tempsensepin, INPUT);

//fan pin
pinMode(fanpin, OUTPUT);

Serial.begin(9600);
Serial1.begin(9600);
delay(1000);
Serial.println("Serial setup complete...");
}

//////////////////main loop
void loop() {
//systemtime ++;
//read the actual sensors in here
//lightsstate = digitalRead(lightspin);
//ignitionstate = digitalRead(ignitionpin);
//highbeamsstate = digitalRead(highbeamspin);
//voltage = analogRead(voltagepin) * 1.75; //voltage multiplier here
if(debug == 1){
Serial.println("Analog Reading...");
}

voltageread();

//write out the desired outputs
analogWrite(ch1pin, ch1state); //and write it
analogWrite(ch2pin, ch2state);
analogWrite(ch3pin, ch3state);
analogWrite(ch3pin, ch3state);
analogWrite(ch4pin, ch4state);
analogWrite(ch5pin, ch5state);
analogWrite(ch6pin, ch6state);
if(debug == 1) {
Serial.println("Analog Writing...");
}

//read the temp only if there's some output going on. Saves on cycles
if(ch1state != 0 || ch2state != 0 || ch3state != 0 || ch4state != 0 || ch5state != 0 || ch6state != 0 || debug == 1){
tempread();
if(debug == 1) {
  //  Serial.println("Fan logic activated");
  }
  // fan logic
  if(fanconnected == 1) {
   if(tempF >= fanstarttemp) {
    fanstate = 255;
    if(debug == 1) {
      Serial.println("Fan On");
      }
   }else{
    fanstate = 0;
    }
   }
  }else{
  fanstate = 0;
  }
  digitalWrite(fanpin, !fanstate); //invert the logic here due to being a sinking current system

//If there is data in the serial buffer, read it
if(Serial1.available() > 0){
  serialread(); //read serial from master  
  }

if(debug == 1) {
  serialdiagnostic();
  }

serialsend();
}
////////////END main loop

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
  //ignitionstate = tempignition.toInt();  //were sending these
  //lightsstate = templights.toInt();       //sending these
  //highbeamsstate = temphighbeams.toInt();  //sending these
  ch1state = tempch1.toInt();
  ch2state = tempch2.toInt();
  ch3state = tempch3.toInt();
  ch4state = tempch4.toInt();
  ch5state = tempch5.toInt();
  ch6state = tempch6.toInt();
}
void serialdiagnostic() { //diagnostic readout for USB serial port
    Serial.println((String)"TFourR/" + unitname +" > " + mastername + "/T-" + systemtime + "/V:" + voltagefloat + "/I:" + ignitionstate + "/L:" + lightsstate + "/H:" + highbeamsstate + "/TMP:" + tempF + "/CH1:" + ch1state + "/CH2:" + ch2state + "/CH3:" + ch3state + "/CH4:" + ch4state + "/CH5:" + ch5state + "/CH6:" + ch6state + "/");
  }

void serialsend()  { //send the outgoing serial data
  Serial1.println((String)"TFourR/" + unitname +" > " + mastername + "/T-" + systemtime + "/" + voltage + "/" + ignitionstate + "/" + lightsstate + "/" + highbeamsstate + "/" + ch1state + "/" + ch2state + "/" + ch3state + "/" + ch4state + "/" + ch5state + "/" + ch6state + "/");
}

void tempread() { //read and do math on the temperature sensor
  tempsenseraw = analogRead(tempsensepin);
  float tempsensevoltage = tempsenseraw * 3.3;
  tempsensevoltage /= 1024.0; //turning this off makes the fan temp go bananas
  float tempC = (tempsensevoltage - 0.5) * 100;
  tempF = (tempC * 9.0 / 5.0) + 32.0;
  //Serial.println((String)"Temp read:" + tempF);
}

void voltageread() { //read the voltage coming into the sense port
  int voltagesenseraw = analogRead(voltagepin);
  voltage = voltagesenseraw / 63;
  voltagefloat = voltagesenseraw / 63.80;
}

