//Lower (relay side) control logic for Teensy control board
//2016-17 Alex Lorman
//IO Pin setup
int LightBarOut1 = 2;
int LightBarOut2 = 3;
int LightBarOut3 = 4;
int LightBarOut4 = 5;
//values that store the intended values
int LightBarValue1 = 0;
int LightBarValue2 = 0;
int LightBarValue3 = 0;
int LightBarValue4 = 0;
//The environmental sensing inputs
int IgnitionInput = A5;
int LightsInput = A4;
int HighBeamsInput = A3;
//Any other variables
//Timing variables for the serial link
int currentMillis;
int Voltage;
int SystemTimeString;
/// -- Setup --//
void setup()
{
  pinMode(LightBarOut1, OUTPUT);
  pinMode(LightBarOut2, OUTPUT);
  pinMode(LightBarOut3, OUTPUT);
  pinMode(LightBarOut4, OUTPUT);
  // and the inputs
  pinMode(IgnitionInput , INPUT);
  pinMode(LightsInput, INPUT);
  pinMode(HighBeamsInput, INPUT);
  // start the serial link
  Serial.begin(9600);
  Serial1.begin(9600);
}
void loop()
{
  while (Serial1.available() != 0) {//while we have a good serial link
  //establish the state reasds foir tr the inputs
  int StateIgnitionInput = digitalRead(IgnitionInput);
  int StateLights = digitalRead(LightsInput);
  int StateHighBeams = digitalRead(HighBeamsInput);
  int PreviousSystemTime;
  currentMillis = millis();
  //Setup the serial heartbeat variables
   //read all our serial variables
    String MarkerString = Serial1.readStringUntil(',');
    SystemTimeString = Serial1.parseInt();
    Voltage = Serial1.parseInt();
    LightBarValue1 = Serial1.parseInt();
    LightBarValue2 = Serial1.parseInt();
    LightBarValue3 = Serial1.parseInt();
  	// check to make sure the heartbeat is different before we actually fire lights and that we have the voltage too
    if (PreviousSystemTime != 0&&Voltage >= 1205) {
      analogWrite(LightBarValue1, LightBarOut1);
      analogWrite(LightBarValue2, LightBarOut2);
      analogWrite(LightBarValue3, LightBarOut3);
      analogWrite(LightBarValue4, LightBarOut4);
 	  PreviousSystemTime = SystemTimeString;
    }
    Serial1.print("TFourR,T/");
    Serial1.print(currentMillis);
    Serial1.print(",I");
    Serial1.print(StateIgnitionInput);
    Serial1.print(",L");
    Serial1.print(StateLights);
    Serial1.print(",H");
    Serial1.println(StateHighBeams); 
    //send the byte up the main serial line for diagnostics
    Serial.print("TFourR,T/");
    Serial.print(currentMillis);
    Serial.print(",I");
    Serial.print(StateIgnitionInput);
    Serial.print(",L");
    Serial.print(StateLights);
    Serial.print(",H");
    Serial.println(StateHighBeams);
    }
}
