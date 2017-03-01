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
}
void loop()
{
  while (Serial.available() != 0) {//while we have a good serial link
  //establish the state reasds foir tr the inputs
  int StateIgnitionInput = digitalRead(IgnitionInput);
  int StateLights = digitalRead(LightsInput);
  int StateHighBeams = digitalRead(HighBeamsInput);
  int PreviousSystemTime;
  currentMillis = millis();
  //Setup the serial heartbeat variables
   //read all our serial variables
    String MarkerString = Serial.readStringUntil(',');
    SystemTimeString = Serial.parseInt();
    Voltage = Serial.parseInt();
    LightBarValue1 = Serial.parseInt();
    LightBarValue2 = Serial.parseInt();
    LightBarValue3 = Serial.parseInt();
  	// check to make sure the heartbeat is different before we actually fire lights and that we have the voltage too
    if (PreviousSystemTime != 0&&Voltage >= 1205) {
      analogWrite(LightBarValue1, LightBarOut1);
      analogWrite(LightBarValue2, LightBarOut2);
      analogWrite(LightBarValue3, LightBarOut3);
      analogWrite(LightBarValue4, LightBarOut4);
 	  PreviousSystemTime = SystemTimeString;
    }
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
