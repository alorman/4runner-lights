// Testing serial1 writing between Teensy boards
//Master
// debug mode
int debug = 1; //change to 1 to debug over serial

//Set the mid level light in resulting things
int midlightlevel = 125;

//serial vars
int voltage = 0;
int lightsstate = 0;
int ignitionstate = 0;
int highbeamsstate = 0;
int ch1state = 0;
int ch2state = 0;
int ch3state = 0;
int ch4state = 0;
int ch5state = 0;
int ch6state = 0;
int systemtime;
String unitname = "Upper";
String mastername = "Lower";
//end vars needed for serial driver

//LED Outputs
int S1LEDlower = 10;
int S1LEDupper = 9;
int S2LEDlower = 51;//testing from here out not used
int S2LEDupper = 52;
int S3LEDlower = 53;
int S3LEDupper = 54;
int S4LEDlower = 55;
int S4LEDupper = 56;
int S5LEDlower = 57;
int S5LEDupper = 58;
int S6LEDlower = 59;
int S7LEDupper = 60;//not used above

// Switch inputs
int S1lowerPin = 2;
int S1upperPin = 3;
int S2lowerPin = 61;//testing not used below
int S2upperPin = 62;
int S3lowerPin = 63;
int S3upperPin = 64;
int S4lowerPin = 65;
int S4upperPin = 66;
int S5lowerPin = 67;
int S5upperPin = 68;
int S6lowerPin = 69;
int S6upperPin = 70;//testing not used above

//State holders for switches
int S1statelower = 0;
int S1stateupper = 0;
int S2statelower = 0;
int S2stateupper = 0;
int S3statelower = 0;
int S3stateupper = 0;


//various blink intervals
unsigned long previousmillis = 0; // undevolt variable
const long undervoltinterval = 1000; // undervolt timing
const long undervoltblinks = 5; //undervolt blinks
int currentblinks = 0; //undervolt current blinks
int OverrideBlinkTime = 300; //blink interval for the override code

//Override function variables
int WorkingPreviousOverrideState1 = 0;//will work as global  variable -- need not be a static
int WorkingPreviousOverrideState2 = 0;
int WorkingPreviousOverrideState3 = 0;
int WorkingPreviousOverrideState4 = 0;
int WorkingPreviousOverrideState5 = 0;
int WorkingPreviousOverrideState6 = 0;

//working override counters
int WorkingOverrideCount1 = 0;
int WorkingOverrideCount2 = 0;
int WorkingOverrideCount3 = 0;
int WorkingOverrideCount4 = 0;
int WorkingOverrideCount5 = 0;
int WorkingOverrideCount6 = 0;

// working number counters
int WorkingNumberCounter1 = 1;
int WorkingNumberCounter2 = 2;
int WorkingNumberCounter3 = 3;
int WorkingNumberCounter4 = 4; 
int WorkingNumberCounter5 = 5; 
int WorkingNumberCounter6 = 6; 

//declare the various arrays needed for override globally
int static WorkingCounterArray[] = {WorkingOverrideCount1, WorkingOverrideCount2, WorkingOverrideCount3, WorkingOverrideCount4, WorkingOverrideCount5, WorkingOverrideCount6};
int static PreviousNameArray[] = {WorkingPreviousOverrideState1, WorkingPreviousOverrideState2, WorkingPreviousOverrideState3, WorkingPreviousOverrideState4, WorkingPreviousOverrideState5, WorkingPreviousOverrideState6};
int static WorkingNumberCounterArray[] = {WorkingNumberCounter1, WorkingNumberCounter2, WorkingNumberCounter3, WorkingNumberCounter4, WorkingNumberCounter5, WorkingNumberCounter6};

//declare variable needed for the protect record functionality
long static previousMillis = 0;
unsigned long currentMillis = millis(); //create timing variable for the flashing protect button in dashcam

//output vars
int ledpin = 13;
int lightbar1out = 0;
int lightbar2out = 0;

//Override function variables (and declare them as zero so that they don't do random things)
int Override1 = 0;
int Override2 = 0;
//The dashcam variables
int Dashcam1;
int DashCamOut;
int DashCamProtectOut;

//Normal on/off function array variables
int LightOutput1 = 0;
int LightOutput2 = 0;
int LightOutput3 = 0;
int LightOutputArray[] = {LightOutput1, LightOutput2, LightOutput3};


void setup() {
  // put your setup code here, to run once:

//Set the pins to do the things
  //Switch LEDs
  pinMode(S1LEDlower, OUTPUT);
  pinMode(S1LEDupper, OUTPUT);
  pinMode(S2LEDlower, OUTPUT);
  pinMode(S2LEDupper, OUTPUT);
  pinMode(S3LEDlower, OUTPUT);
  pinMode(S3LEDupper, OUTPUT);
  //Switch inputs
  pinMode(S1lowerPin, INPUT);
  pinMode(S1upperPin, INPUT);
  pinMode(S2lowerPin, INPUT);
  pinMode(S2upperPin, INPUT);
  pinMode(S3lowerPin, INPUT);
  pinMode(S3upperPin, INPUT);
  
  //Environmental inputs
  //pinMode(lights, INPUT);
  //pinMode(highbeams, INPUT);
  //pinMode(voltagesense, INPUT);
  //pinMode(ignitioninput, INPUT);
  //outputs to lights
  //pinMode(lightbarout, OUTPUT);

 //Which light we're controlling (used in arrays)
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
  
 //Setup the serial driver and diagnostic
 //pinMode(ledpin, OUTPUT);
Serial.begin(9600);
Serial1.begin(9600);
delay(1000);
Serial.println("setup complete...");
}

void loop() { //MAIN LOOP
  
  
systemtime ++;

  //switch state variables
 S1statelower = digitalRead(S1lowerPin);
 S1stateupper = digitalRead(S1upperPin);
 S2statelower = digitalRead(S2lowerPin);
 S2stateupper = digitalRead(S2upperPin);
 S3statelower = digitalRead(S3lowerPin);
 S3stateupper = digitalRead(S3upperPin);
 Serial.println((String)"S1 lower" + S1statelower);
 Serial.println((String)"S1 upper" + S1stateupper);
  
//read the actual sensors in here
digitalWrite(ledpin, ch1state); //and write it

if (ignitionstate == HIGH) { //if the car is on, run the normal lighting procedure
    //Call the main light controls for 1 and 2
    lightbar1out = LightLogicFunction(S1statelower, S1stateupper, S1LEDlower, S1LEDupper, lightsstate, highbeamsstate, ignitionstate, 0, ch1state);//call ofthe actual function
    //lightbar2out = LightLogicFunction(S2statelower, S2stateupper, S2LEDlower, S2LEDupper, lightsstate, highbeamsstate, ignitionstate, 1, lightbar2out);//call ofthe actual function

    //reset the counters to zero for the override tables
    WorkingCounterArray[0] = 0;
    WorkingCounterArray[1] = 0;
    WorkingCounterArray[2] = 0;
    WorkingCounterArray[3] = 0;
    delay(10);
    }
    else if (debug == 1) {
      Serial.println("debug 0.75");
    }
//else if (ignitionstate == LOW) { //While the car is off run the following 
    //Override1 = OverrideRoutine(ignitionstate, S1statelower, S1LEDlower, lightbar1out, 0);
   // Override2 = OverrideRoutine(ignitionstate, S2statelower, S2LEDlower, lightbar2out, 1);
    //Dashcam1 = DashCamLogic(S3statelower, S3stateupper, S3LEDlower, S3LEDupper, lightsstate, 2, DashCamProtectOut);
//}

if(Serial1.available() > 0){ //if the port has data on the buffer then read it then send it out the diagnostic
  serialread();
  serialdiagnostic();
  }
  
serialsend(); //send the serial data

} //end of main loop

//Light bar logic block

// Defining all our input variables into the function
//Writing directly the variables, rather than doing an analogWrite.
//UPPER = AUTO and LOWER = HIGH BEAMS
  int LightLogicFunction(int workinglower, int workingupper, int workingLEDlower, int workingLEDupper, int workingStateLights, int workingStateHighBeams, int workingIgnitionInput, int workingLightNumber, int workingoutput){
    //define the array of the output names before we get too far
    //start the main loop
    if (workingupper == LOW&&workinglower == LOW) {
      if (debug == 1) {
        Serial.println((String)"Breakpoint 1/" + workingLightNumber);
        //  Serial.println(workinglower);
      }
  }   
  //check to see if we're in auto then check to see about lights, if yes, then high beams
  else if (workingupper == LOW&&workingStateLights == LOW&&workingStateHighBeams == LOW) {
      if (debug == 1) {
      Serial.println((String)"Breakpoint 2/" + workingLightNumber);
      }
    analogWrite(workingLEDlower, 255);
    analogWrite(workingLEDupper, midlightlevel);
    LightOutputArray[workingLightNumber] = 255;
    }
    //Auto LEDs but with lights but no hight beams
  else if (workingupper == LOW&&workingStateLights == LOW&&workingStateHighBeams == HIGH) {
      if (debug == 1) {
      Serial.println((String)"Breakpoint 3/" + workingLightNumber);
      }
    analogWrite(workingLEDupper, 255);
    analogWrite(workingLEDlower, midlightlevel);
    LightOutputArray[workingLightNumber] = midlightlevel;
   }//no switch action but lights on, so glow the panel
  else if (workingupper == HIGH&&workinglower ==HIGH&&workingStateLights == LOW&&workingStateHighBeams == HIGH) {
      if (debug == 1) {
      Serial.println((String)"Breakpoint 4/" + workingLightNumber);
      }
    analogWrite(workingLEDlower, midlightlevel);
    analogWrite(workingLEDupper, midlightlevel);
    LightOutputArray[workingLightNumber] = 0;
  }//Auto LEDS, but no car lights
  else if (workingupper == LOW&&workingStateLights == HIGH&&workingStateHighBeams == HIGH) {
      if (debug == 1) {
      Serial.println((String)"Breakpoint 5/" + workingLightNumber);
      }
    analogWrite(workingLEDlower, 0);
    analogWrite(workingLEDupper, 255);
    LightOutputArray[workingLightNumber] = 0;
  }//all off, no glow
  else if (workinglower == HIGH&&workingStateLights == HIGH&&workingStateHighBeams == HIGH&&workingupper == HIGH) {
      if (debug == 1) {
      Serial.println((String)"Breakpoint 6/" + workingLightNumber);
      }
    analogWrite(workingLEDlower, 0);
    analogWrite(workingLEDupper, 0);
    LightOutputArray[workingLightNumber] = 0;
  }//Hight beams and glowing panel
  else if (workinglower == LOW&&workingStateLights == LOW) {
      if (debug == 1) {
      Serial.println((String)"Breakpoint 7/" + workingLightNumber);
      }
    analogWrite(workingLEDlower, 255);
    analogWrite(workingLEDupper, midlightlevel);
    LightOutputArray[workingLightNumber] = 255;
  }//High beams no glow on rest of panel
  else if (workinglower == LOW){
      if (debug == 1) {
      Serial.println((String)"Breakpoint 8/" + workingLightNumber);
      }
    analogWrite(workingLEDlower, 255);
    analogWrite(workingLEDupper, 0);
    LightOutputArray[workingLightNumber] = 255;
  }//all off panel glowing
  else if (workinglower == HIGH&&workingupper == HIGH&&workingStateLights == LOW&&workingStateHighBeams == LOW) {
      if (debug == 1) {
      Serial.println((String)"Breakpoint 9/" + workingLightNumber);
      Serial.println(workingupper);
      }
    analogWrite(workingLEDlower, midlightlevel);
    analogWrite(workingLEDupper, midlightlevel);
    LightOutputArray[workingLightNumber] = 0;
  }
  }//end Light selection function

//Override logic block 

int OverrideRoutine(int WorkingStateEngine, int WorkingStateButtonHigh, int WorkingLEDlower, int WorkingOutput, int WorkingSwitchNumber) {
  //tables are established in global variables
  //check for state change from last time
  if (WorkingStateButtonHigh != PreviousNameArray[WorkingSwitchNumber]&&WorkingStateEngine == HIGH) {
        WorkingCounterArray[WorkingSwitchNumber] ++;
    if (debug == 1) { 
    Serial.println((String)"Breakpoint 10/" + WorkingNumberCounterArray[WorkingSwitchNumber] + WorkingNumberCounterArray[WorkingSwitchNumber]);//same
    }
        PreviousNameArray[WorkingSwitchNumber] = WorkingStateButtonHigh;//same
  }
    if (WorkingCounterArray[WorkingSwitchNumber] >= 3&&WorkingStateButtonHigh == HIGH&&WorkingStateEngine == HIGH) {
    analogWrite(WorkingLEDlower, 255);
    LightOutputArray[WorkingSwitchNumber] = 255;
   if (debug == 1){
    Serial.print((String)"Breakpoint 10.5/" + WorkingNumberCounterArray[WorkingSwitchNumber] + "255");
   }
    
  }
  else if (WorkingStateButtonHigh == LOW&&WorkingStateEngine == LOW) {
    WorkingCounterArray[WorkingSwitchNumber] = 0;
    analogWrite(WorkingLEDlower, 255);
    LightOutputArray[WorkingSwitchNumber] = 255;
       if (debug == 1){
    Serial.print((String)"Breakpoint 11/" + WorkingNumberCounterArray[WorkingSwitchNumber] + "255");
   }
  }
  else {
    analogWrite(WorkingLEDlower, 0);
    LightOutputArray[WorkingSwitchNumber] = 0;//this is what's causing the working output  to go bananas
      if (debug == 1){
    Serial.print((String)"Breakpoint 12/" + WorkingNumberCounterArray[WorkingSwitchNumber] + "0");
   }
  }  
}

//Dashcam logic block

int DashCamLogic(int workinglower, int workingupper, int workingLEDlower, int workingLEDupper, int workingStateLights, int workingLightNumber, int workingProtect){
    if (workingupper == HIGH&&workinglower == LOW) {
    if (debug == 1){
    Serial.print((String)"Breakpoint 13/" + workingLightNumber);
   }
  }   
  //If we're in auto and the lights are on, glow the dash
  else if (workingupper == LOW&&workingStateLights == LOW) {
    if (debug == 1){
    Serial.print((String)"Breakpoint 14/" + workingLightNumber + "High");
   }
    analogWrite(workingLEDupper, 255);
    analogWrite(workingLEDlower, midlightlevel);
    LightOutputArray[workingLightNumber] = 255;
   }//if we're in OFF and the dash still needs glowing
  else if (workingupper == HIGH&&workinglower ==HIGH&&workingStateLights == LOW) {
    if (debug == 1){
    Serial.print((String)"Breakpoint 14.5/" + workingLightNumber + "Panel only");
   }
    analogWrite(workingLEDlower, midlightlevel);
    analogWrite(workingLEDupper, midlightlevel);
    LightOutputArray[workingLightNumber] = 0;
  }//in auto with no car lighting on
  else if (workingupper == LOW&&workingStateLights == HIGH) {
    if (debug == 1){
    Serial.print((String)"Breakpoint 15/" + workingLightNumber + "High");
   }
    analogWrite(workingLEDlower, 0);
    analogWrite(workingLEDupper, 255);
    LightOutputArray[workingLightNumber] = 255;
  }//dashcam off, and panel not glowing
  else if (workinglower == HIGH&&workingStateLights == HIGH&&workingupper == HIGH) {
    if (debug == 1){
    Serial.print((String)"Breakpoint 16/" + workingLightNumber + "Off");
   }
    analogWrite(workingLEDlower, 0);
    analogWrite(workingLEDupper, 0);
    LightOutputArray[workingLightNumber] = 255;
  }//protect mode on and panel glowing
  else if (workinglower == LOW&&workingStateLights == LOW) {
    if (debug == 1){
    Serial.print((String)"Breakpoint 17/" + workingLightNumber + "High");
   }
    analogWrite(workingLEDlower, 255);
    analogWrite(workingLEDupper, midlightlevel);
    LightOutputArray[workingLightNumber] = 255;
    if (currentMillis - previousMillis >= OverrideBlinkTime) {
      previousMillis = currentMillis;
    digitalWrite(workingProtect, HIGH);
    }
    else
    digitalWrite(workingProtect, LOW);
  }//protect mdoe and panel not glowing
  else if (workinglower == LOW){
    if (debug == 1){
    Serial.print((String)"Breakpoint 18/" + workingLightNumber + "High");
   }
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
  }//end Dascam override function



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
  ignitionstate = tempignition.toInt();
  lightsstate = templights.toInt();
  highbeamsstate = temphighbeams.toInt();
  //ch1state = tempch1.toInt(); //dont overwrite the thigns were trying to send
  //ch2state = tempch2.toInt();
  //ch3state = tempch3.toInt();
  //ch4state = tempch4.toInt();
  //ch5state = tempch5.toInt();
  //ch6state = tempch6.toInt();
}
void serialdiagnostic() { //diagnostic readout for USB serial port
  Serial.println((String)"TFourR/" + unitname +" > " + mastername + "/T-" + systemtime + "/V" + voltage + "/I" + ignitionstate + "/L" + lightsstate + "/H" + highbeamsstate + "/CH1" + ch1state + "/CH2" + ch2state + "/CH3" + ch3state + "/CH4" + ch4state + "/CH5" + ch5state + "/CH6" + ch6state + "/");
  }

void serialsend()  { //send the outgoing serial data
  Serial1.println((String)"TFourR/" + unitname +" > " + mastername + "/T-" + systemtime + "/" + voltage + "/" + ignitionstate + "/" + lightsstate + "/" + highbeamsstate + "/" + ch1state + "/" + ch2state + "/" + ch3state + "/" + ch4state + "/" + ch5state + "/" + ch6state + "/");
}


