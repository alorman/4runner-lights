//TO MAKE CODE WORK. YOU MUST FORCEFEED IT SERIAL COMMANDS
//Like this "TFourR,T/31905,I0,L0,H0" as if the lower unit is connected. Timing should change between commands
//IO pin setup
//LED outputs to switches
int S1LEDlower = 20;
int S1LEDupper = 21;
int S2LEDlower = A3;
int S2LEDupper = A4;
int S3LEDlower = A6;
int S3LEDupper = 11;
//Switch inputs
int S1lower = 7;
int S1upper = 8;
int S2lower = A2;
int S2upper = A17;
int S3lower = A15;
int S3upper = 13;
//car environmental inputs
int lights = 2;
int highbeams = 3;
int ignitioninput = 4;
int voltagesense = A5;
//outputs
int lightbarout = 10;
//other counters and variables
unsigned long previousmillis = 0; // undevolt variable
const long undervoltinterval = 1000; // undervolt timing
const long undervoltblinks = 5; //undervolt blinks
int currentblinks = 0; //undervolt current blinks
int OverrideBlinkTime = 300; //blink interval for the override code
//Normal on/off function array variables
int LightOutput1 = 0;
int LightOutput2 = 0;
int LightOutput3 = 0;
int LightOutputArray[] = {LightOutput1, LightOutput2, LightOutput3};
//global states
int statelights = 0;// = digitalRead(lights);
int statehighbeams = 0; // = digitalRead(highbeams); //commented out since we're reading it over the serial line instead
int stateignition = 0; // = digitalRead(ignitioninput);//key switch to run
//Override function variables
int WorkingPreviousOverrideState1 = 0;//will work as global  variable -- need not be a static
int WorkingPreviousOverrideState2 = 0;
int WorkingPreviousOverrideState3 = 0;
int WorkingPreviousOverrideState4 = 0;
//working override counters
int WorkingOverrideCount1 = 0;
int WorkingOverrideCount2 = 0;
int WorkingOverrideCount3 = 0;
int WorkingOverrideCount4 = 0;
// working number counters
int WorkingNumberCounter1 = 1;
int WorkingNumberCounter2 = 2;
int WorkingNumberCounter3 = 3;
int WorkingNumberCounter4 = 4; 
//declare the various arrays needed for override globally
int static WorkingCounterArray[] = {WorkingOverrideCount1, WorkingOverrideCount2, WorkingOverrideCount3, WorkingOverrideCount4};
int static PreviousNameArray[] = {WorkingPreviousOverrideState1, WorkingPreviousOverrideState2, WorkingPreviousOverrideState3, WorkingPreviousOverrideState4};
int static WorkingNumberCounterArray[] = {WorkingNumberCounter1, WorkingNumberCounter2, WorkingNumberCounter3, WorkingNumberCounter4};
//declare variable needed for the protect record functionality
long static previousMillis = 0;
unsigned long currentMillis = millis(); //create timing variable for the flashing protect button in dashcam

// -----SETUP------
void setup() {
  //Set the pins to do the things
  //Switch LEDs
  pinMode(S1LEDlower, OUTPUT);
  pinMode(S1LEDupper, OUTPUT);
  pinMode(S2LEDlower, OUTPUT);
  pinMode(S2LEDupper, OUTPUT);
  pinMode(S3LEDlower, OUTPUT);
  pinMode(S3LEDupper, OUTPUT);
  //Switch inputs
  pinMode(S1lower, INPUT);
  pinMode(S1upper, INPUT);
  pinMode(S2lower, INPUT);
  pinMode(S2upper, INPUT);
  pinMode(S3lower, INPUT);
  pinMode(S3upper, INPUT);
  //Environmental inputs
  pinMode(lights, INPUT);
  pinMode(highbeams, INPUT);
  pinMode(voltagesense, INPUT);
  pinMode(ignitioninput, INPUT);
  //outputs to lights
  pinMode(lightbarout, OUTPUT);
  Serial.begin(9600);
  Serial1.begin(9600);
}
// --------END SETUP---------
// the loop routine runs over and over again forever:
void loop() {
  //set the states of the envionrmental inputs and give them variables
  //switch state variables
  int S1statelower = digitalRead(S1lower);
  int S1stateupper = digitalRead(S1upper);
  int S2statelower = digitalRead(S2lower);
  int S2stateupper = digitalRead(S2upper);
  int S3statelower = digitalRead(S3lower);
  int S3stateupper = digitalRead(S3upper);
  //environmental variables
  int statevoltagesense = digitalRead(voltagesense);//alternator sense
  int ScaledVoltage; //voltage sensing
  ScaledVoltage = voltagesense / .0176; //(remember to add the damn zero after the decimal)
  //Which Light we're controlling (used in arrays)
  int LightNumber1 = 1;
  int LightNumber2 = 2;
  int LightNumber3 = 3;
  //resulting variables (for light bars)(and declare them as zero so that they don't do random things)
  int lightbar1out = 0;
  int lightbar2out = 0;
  //Override function variables (and declare them as zero so that they don't do random things)
  int Override1 = 0;
  int Override2 = 0;
  //The dashcam variables
  int Dashcam1;
  int DashCamOut;
  int DashCamProtectOut;
  //dashcam update clock on main logic refresh
  currentMillis = millis();
  //Setup the serial heartbeat variables
  int oldByte;
  int incomingByte;
  int time;
  time = millis();//used in transmitting heartbeat to receiver
  // Call the functions (MAIN LOGIC BLOCK)
  //int SerialDigaByte = Serial1.read(); //TESTING serial1 stuff
  /*if (ScaledVoltage < 1150)  //check for low voltage before we get into the functions
  {
    //Serial.println("Low Batt");
  }
  else 
  {
    //Serial.println("Good Batt");
  }//finish battery testing
 */
  //Test to see if we have a good serial link
  if (Serial1.available() != 0) { 
    //incomingByte = Serial.read();
    //Serial.print("serial good ");
    //Serial.println(time, DEC);
    //read the incoming serial bits and parse them
    oldByte = incomingByte;
    String MarkerString = Serial1.readStringUntil(',');
    int SystemTimeString = Serial1.parseInt();
    statelights = Serial1.parseInt();
    statehighbeams = Serial1.parseInt();
    stateignition = Serial1.parseInt();
    // ----Main subroutine Logic----
    if (stateignition == HIGH) { //If the car is on run the normal routine
    //Call the main light controls for 1 and 2
    lightbar1out = LightLogicFunction(S1statelower, S1stateupper, S1LEDlower, S1LEDupper, statelights, statehighbeams, stateignition, 0, lightbar1out);//call ofthe actual function
    lightbar2out = LightLogicFunction(S2statelower, S2stateupper, S2LEDlower, S2LEDupper, statelights, statehighbeams, stateignition, 1, lightbar2out);//call ofthe actual function
    //reset the counters to zero for the override tables
    WorkingCounterArray[0] = 0;
    WorkingCounterArray[1] = 0;
    WorkingCounterArray[2] = 0;
    WorkingCounterArray[3] = 0;
    delay(10);
    }
    // call the light override function for 1
    else { //if the car isn't on run the battery off logic
    Override1 = OverrideRoutine(stateignition, S1statelower, S1LEDlower, lightbar1out, 0);
    Override2 = OverrideRoutine(stateignition, S2statelower, S2LEDlower, lightbar2out, 1);
    // call the dashcam logic
    Dashcam1 = OnOffLogic(S3statelower, S3stateupper, S3LEDlower, S3LEDupper, statelights, 2, DashCamProtectOut);
    delay(100);
    }
    // ----end main logic----
    oldByte ++; //comment out for real deployment
      }
  else { //if we don't have a good link do this stuff
    //Serial.println("serial no good");
    incomingByte = Serial1.read();
    delay(200);
  }
  //Serial driver begin
    Serial1.print("TFourRpperSerial1");
    Serial1.print(",");
    Serial1.print("T/");
    Serial1.print(time);
    Serial1.print(",");
    //Serial1.print(ScaledVoltage);
    //Serial1.print(",");
    Serial1.print(LightOutputArray[0]);
    Serial1.print(",");
    Serial1.print(LightOutputArray[1]);
    Serial1.print(",");
    Serial1.print(LightOutputArray[2]);
    Serial1.println();
  //Serial driver end
  //Serial diagnostic driver begin
    Serial.print("TFourUpperSerial");
    Serial.print(",");
    Serial.print("T/");
    Serial.print(time);
    Serial.print(",");
    //Serial.print(ScaledVoltage);
    //Serial.print(",");
    Serial.print(LightOutputArray[0]);
    Serial.print(",");
    Serial.print(LightOutputArray[1]);
    Serial.print(",");
    Serial.print(LightOutputArray[2]);
    Serial.println();
  //Serial diagnostic driver end
  //Add a copy system to send the serial byte coming from the lower unit to the main unit over usb
  //if (Serial1.available() > 0) { //if loop seems to work fine
  //  Serial.println(SerialDigaByte, DEC); //dec seems to make no difference
  //}
 }//end main code
//Light Bar function block
  // Defining all our input variables into the function
//Writing directly the variables, rather than doing an analogWrite.
//UPPER = AUTO and LOWER = HIGH BEAMS
  int LightLogicFunction(int workinglower, int workingupper, int workingLEDlower, int workingLEDupper, int workingStateLights, int workingStateHighBeams, int workingIgnitionInput, int workingLightNumber, int workingoutput){
    //define the array of the output names before we get too far
    //start the main loop
    if (workingupper == HIGH&&workinglower == HIGH) {
    /*Serial.print("Light ");
    Serial.print(WorkingNumberCounterArray[workingLightNumber]);
    Serial.print(":");
    Serial.println("Illegal button press");
    */
  }   
  //check to see if we're in auto then check to see about lights, if yes, then high beams
  else if (workingupper == HIGH&&workingStateLights == HIGH&&workingStateHighBeams == HIGH) {
    /*Serial.print("Light ");
    Serial.print(WorkingNumberCounterArray[workingLightNumber]);
    Serial.print(":");
    Serial.println("255");
    */
    analogWrite(workingLEDlower, 255);
    analogWrite(workingLEDupper, 125);
    LightOutputArray[workingLightNumber] = 255;
    }
    //Auto LEDs but with lights but no hight beams
  else if (workingupper == HIGH&&workingStateLights == HIGH&&workingStateHighBeams == LOW) {
    /*Serial.print("Light ");
    Serial.print(workingLightNumber);
    Serial.print(":");
    Serial.println("128");
    */
    analogWrite(workingLEDupper, 255);
    analogWrite(workingLEDlower, 125);
    LightOutputArray[workingLightNumber] = 125;
   }//no switch action but lights on, so glow the panel
  else if (workingupper == LOW&&workinglower ==LOW&&workingStateLights == HIGH&&workingStateHighBeams == LOW) {
    /*Serial.print("Light ");
    Serial.print(workingLightNumber);
    Serial.print(":");
    Serial.println("Lights on, light bars off, just light up the panel");
    */
    analogWrite(workingLEDlower, 125);
    analogWrite(workingLEDupper, 125);
    LightOutputArray[workingLightNumber] = 0;
  }//Auto LEDS, but no car lights
  else if (workingupper == HIGH&&workingStateLights == LOW&&workingStateHighBeams == LOW) {
    /*Serial.print("Light ");
    Serial.print(workingLightNumber);
    Serial.print(":");
    Serial.println("0");
    */
    analogWrite(workingLEDlower, 0);
    analogWrite(workingLEDupper, 255);
    LightOutputArray[workingLightNumber] = 0;
  }//all off, no glow
  else if (workinglower == LOW&&workingStateLights == LOW&&workingStateHighBeams == LOW&&workingupper == LOW) {
    /*Serial.print("Light ");
    Serial.print(workingLightNumber);
    Serial.print(":");
    Serial.println("0");
    */
    analogWrite(workingLEDlower, 0);
    analogWrite(workingLEDupper, 0);
    LightOutputArray[workingLightNumber] = 0;
  }//Hight beams and glowing panel
  else if (workinglower == HIGH&&workingStateLights == HIGH) {
    /*Serial.print("Light ");
    Serial.print(workingLightNumber);
    Serial.print(":");
    Serial.println("255");
    */
    analogWrite(workingLEDlower, 255);
    analogWrite(workingLEDupper, 125);
    LightOutputArray[workingLightNumber] = 255;
  }//High beams no glow on rest of panel
  else if (workinglower == HIGH){
    /*Serial.print("Light ");
    Serial.print(workingLightNumber);
    Serial.print(":");
    Serial.println("255");
    */
    analogWrite(workingLEDlower, 255);
    analogWrite(workingLEDupper, 0);
    LightOutputArray[workingLightNumber] = 255;
  }//all off panel glowing
  else if (workinglower == LOW&&workingupper == LOW&&workingStateLights == HIGH&&workingStateHighBeams == HIGH) {
    /*Serial.print("Light ");
    Serial.print(workingLightNumber);
    Serial.print(":");
    Serial.println("0");
    */
    analogWrite(workingLEDlower, 125);
    analogWrite(workingLEDupper, 125);
    LightOutputArray[workingLightNumber] = 0;
  }
  }//end Light selection function
//Begin the override switch function
int OverrideRoutine(int WorkingStateEngine, int WorkingStateButtonHigh, int WorkingLEDlower, int WorkingOutput, int WorkingSwitchNumber) {
  //tables are established in global variables
  //check for state change from last time
  if (WorkingStateButtonHigh != PreviousNameArray[WorkingSwitchNumber]&&WorkingStateEngine == LOW) {
        WorkingCounterArray[WorkingSwitchNumber] ++;
        /*Serial.print(WorkingNumberCounterArray[WorkingSwitchNumber]);
        Serial.print("presses on switch ");//comment out during deployment
      Serial.println(WorkingNumberCounterArray[WorkingSwitchNumber]);//same
        */
        PreviousNameArray[WorkingSwitchNumber] = WorkingStateButtonHigh;//same
  }
    if (WorkingCounterArray[WorkingSwitchNumber] >= 3&&WorkingStateButtonHigh == HIGH&&WorkingStateEngine == LOW) {
    analogWrite(WorkingLEDlower, 255);
    LightOutputArray[WorkingSwitchNumber] = 255;
    /*Serial.print("Light ");
    Serial.print(WorkingNumberCounterArray[WorkingSwitchNumber]);
    Serial.println(":255");
    */
  }
  else if (WorkingStateButtonHigh == HIGH&&WorkingStateEngine == HIGH) {
    WorkingCounterArray[WorkingSwitchNumber] = 0;
    analogWrite(WorkingLEDlower, 255);
    LightOutputArray[WorkingSwitchNumber] = 255;
    /*Serial.println("Car on now, overrides reset");
    Serial.print("Light ");
    Serial.print(WorkingNumberCounterArray[WorkingSwitchNumber]);
    Serial.println(":255");
    */
  }
  else {
    analogWrite(WorkingLEDlower, 0);
    LightOutputArray[WorkingSwitchNumber] = 0;//this is what's causing the working output  to go bananas
    /*Serial.print("Light ");
    Serial.print(WorkingNumberCounterArray[WorkingSwitchNumber]);
    Serial.println(":0");
    */
  }  
}
//Start the logic for simple auto/off states like the dashcam. Updated for the drivers to put together the ascii bit later on. Removed digitalWrite commands
//For consistency we're trying to keep it as similar to the light logica s we can
//UPPER = AUTO and off is off and LOWER = PROTECT
//protect mode will pulse the protect output, connected to the MODE button on the mobious
int OnOffLogic(int workinglower, int workingupper, int workingLEDlower, int workingLEDupper, int workingStateLights, int workingLightNumber, int workingProtect){
    if (workingupper == HIGH&&workinglower == HIGH) {
    /*Serial.print("Circuit ");
    Serial.print(workingLightNumber);
    Serial.print(":");
    Serial.println("Illegal button press");
    */
  }   
  //If we're in auto and the lights are on, glow the dash
  else if (workingupper == HIGH&&workingStateLights == HIGH) {
    /*Serial.print("Circuit ");
    Serial.print(workingLightNumber);
    Serial.print(":");
    Serial.println("HIGH");
    */
    analogWrite(workingLEDupper, 255);
    analogWrite(workingLEDlower, 125);
    LightOutputArray[workingLightNumber] = 255;
   }//if we're in OFF and the dash still needs glowing
  else if (workingupper == LOW&&workinglower ==LOW&&workingStateLights == HIGH) {
    /*Serial.print("Circuit ");
    Serial.print(workingLightNumber);
    Serial.print(":");
    Serial.println("Lights on, light bars off, just light up the panel");
    */
    analogWrite(workingLEDlower, 125);
    analogWrite(workingLEDupper, 125);
    LightOutputArray[workingLightNumber] = 0;
  }//in auto with no car lighting on
  else if (workingupper == HIGH&&workingStateLights == LOW) {
    /*Serial.print("Circuit ");
    Serial.print(workingLightNumber);
    Serial.print(":");
    Serial.println("HIGH");
    */
    analogWrite(workingLEDlower, 0);
    analogWrite(workingLEDupper, 255);
    LightOutputArray[workingLightNumber] = 255;
  }//dashcam off, and panel not glowing
  else if (workinglower == LOW&&workingStateLights == LOW&&workingupper == LOW) {
    /*Serial.print("Circuit ");
    Serial.print(workingLightNumber);
    Serial.print(":");
    Serial.println("OFF");
    */
    analogWrite(workingLEDlower, 0);
    analogWrite(workingLEDupper, 0);
    LightOutputArray[workingLightNumber] = 255;
  }//protect mode on and panel glowing
  else if (workinglower == HIGH&&workingStateLights == HIGH) {
    /*Serial.print("Circuit ");
    Serial.print(workingLightNumber);
    Serial.print(":");
    Serial.println("HIGH");
    */
    analogWrite(workingLEDlower, 255);
    analogWrite(workingLEDupper, 125);
    LightOutputArray[workingLightNumber] = 255;
    if (currentMillis - previousMillis >= OverrideBlinkTime) {
      previousMillis = currentMillis;
    digitalWrite(workingProtect, HIGH);
    }
    else
    digitalWrite(workingProtect, LOW);
  }//protect mdoe and panel not glowing
  else if (workinglower == HIGH){
    /*Serial.print("Circuit ");
    Serial.print(workingLightNumber);
    Serial.print(":");
    Serial.println("HIGH");
    */
    analogWrite(workingLEDlower, 255);
    analogWrite(workingLEDupper, 0);
    LightOutputArray[workingLightNumber] = 255;
    if (currentMillis - previousMillis >= OverrideBlinkTime) {
      previousMillis = currentMillis;
    digitalWrite(workingProtect, HIGH);
    }
    else
    digitalWrite(workingProtect, LOW);
  }
  }//end Light selection function

