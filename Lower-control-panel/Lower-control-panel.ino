//Lower (relay side) control logic for Teensy control board
//2016-17 Alex Lorman
//IO Pin setup
int LightBarOut1 = 3;
int LightBarOut2 = 4;
int LightBarOut3 = 23;
int LightBarOut4 = 22;
//values that store the intended values
int LightBarValue1 = 0;
int LightBarValue2 = 0;
int LightBarValue3 = 0;
int LightBarValue4 = 0;
//The environmental sensing inputs
int IgnitionInput = 16;
int LightsInput = 17;
int HighBeamsInput = 18;
//Any other variables
//Timing variables for the serial link
int currentMillis;
//move the below variables to setup for troubleshooting
int Voltage;
int SystemTimeString = 0;
int StateIgnitionInput = 0;
int StateLights = 0;
int StateHighBeams = 0;
unsigned int PreviousSystemTime = 0; //changed to unsigned int
String MarkerString; //moved markerstring into setup


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
  //while (Serial1.available() != 0) {//while we have a good serial link
  //establish the state reasds foir tr the inputs
  StateIgnitionInput = digitalRead(IgnitionInput); //now declaring the INTS in setup
  StateLights = digitalRead(LightsInput);
  StateHighBeams = digitalRead(HighBeamsInput);

  currentMillis = millis();
  //Setup the serial heartbeat variables
   //read all our serial variables
   MarkerString = Serial1.readStringUntil(','); //markerstring is the T4R preamble
   //SystemTimeString = Serial1.parseInt(); //somehow this is causing problems
   Voltage = Serial1.parseInt();
   LightBarValue1 = Serial1.parseInt();
   LightBarValue2 = Serial1.parseInt();
   LightBarValue3 = Serial1.parseInt();
    // check to make sure the heartbeat is different before we actually fire lights and that we have the voltage too
    //commented out voltage sensing //previous lineif (PreviousSystemTime != SystemTimeString&&Voltage >= 1205)
      analogWrite(LightBarOut1, LightBarValue1); //again, reverse order
      //analogWrite(LightBarValue2, LightBarOut2);
      //analogWrite(LightBarValue3, LightBarOut3);
      //analogWrite(LightBarValue4, LightBarOut4);
      //PreviousSystemTime = SystemTimeString;
      Serial.println("debug point1");
    //if (Serial1.available() > 0) {
    Serial1.print("TFourRLower,T/");
    Serial1.print(SystemTimeString);
    Serial1.print(",I");
    Serial1.print(StateIgnitionInput);
    Serial1.print(",L");
    Serial1.print(StateLights);
    Serial1.print(",H");
    Serial1.println(StateHighBeams); 
   // }
    //send the byte up the main serial line for diagnostics
   // if (Serial.available() > 0) {
    Serial.print("TFourRLower,T/");
    Serial.print(currentMillis);
    Serial.print(",I");
    Serial.print(StateIgnitionInput);
    Serial.print(",L");
    Serial.print(StateLights);
    Serial.print(",H");
    Serial.print(StateHighBeams);
    Serial.println(LightBarValue1); //add serial debug for light bar output on pin 3
    //}
    //}
}
