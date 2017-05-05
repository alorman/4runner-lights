// Testing serial1 writing between Teensy boards
//Master
// debug mode
int debug = 1; //change to 1 to debug over serial

//Set the mid level light in resulting things
int midlightlevel = 50;
int midLEDoutlevel = 75;

//Override options (how many switch toggles are required  to override)
int OverrideNumber = 5; //should always be an odd number

//serial vars
int voltage = 0;
int lightsstate = 0;
int ignitionstate = 0;
int highbeamsstate = 0;
int systemtime;
String unitname = "Upper";
String mastername = "Lower";
//end vars needed for serial driver

//LED Outputs
int S1LEDlower = 48; //testing values
int S1LEDupper = 49;
int S2LEDlower = 51;//testing from here out not used
int S2LEDupper = 52;
int S3LEDlower = 53;
int S3LEDupper = 54;
int S4LEDlower = 10; //assign to dashcam for testing
int S4LEDupper = 9;  //assign to dashcam for testing
int S5LEDlower = 57;
int S5LEDupper = 58;
int S6LEDlower = 59;
int S6LEDupper = 599;

// Switch inputs
int S1lowerPin = 59;
int S1upperPin = 60;
int S2lowerPin = 61;//testing not used below
int S2upperPin = 62;
int S3lowerPin = 63;
int S3upperPin = 64;
int S4lowerPin = 4; //dashcam testing
int S4upperPin = 3;  //dashcam testing
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
int S4stateupper = 0;
int S4statelower = 0;
int S5statelower = 0;
int S5stateupper = 0;
int S6statelower = 0;
int S6stateupper = 0;

//Global variables for the timer routing
unsigned long previousMillis = 0;
unsigned long currentMillis = 0;

//array and setup for the LED panel switchs
//uppers
int UpperLEDoutArray[] = {0, 0, 0, 0, 0, 0};

//lowers
int LowerLEDoutArray[] = {0, 0, 0, 0, 0, 0};


//Override function variables
//declare the various arrays needed for override globally
int static WorkingCounterArray[] = {0, 0, 0, 0, 0, 0};
int static PreviousNameArray[] = {0, 0, 0, 0, 0, 0};
int static WorkingNumberCounterArray[] = {0, 0, 0, 0, 0, 0};

//output vars
int ledpin = 13;
int lightbar1out = 0;
int lightbar2out = 0;

//Override function variables (and declare them as zero so that they don't do random things)
int Override1 = 0;
int Override2 = 0;

//The dashcam variables
//int DashcamPin = 12;
int DashCamPower = 8;
int DashCamDropoutVoltage = 1145;
int DashCamOn = 1; //assign these to change the on off ports on the dashcam
int DashCamOff = 0;
int DashCamBlinkInterval = 250; //Dashcam override blink interval

//Normal on/off function array variables
int LightOutputArray[] = {0, 0, 0, 0, 0, 0};


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
  pinMode(S4LEDlower, OUTPUT);
  pinMode(S4LEDupper, OUTPUT);
  pinMode(S5LEDlower, OUTPUT);
  pinMode(S5LEDupper, OUTPUT);
  pinMode(S6LEDlower, OUTPUT);
  pinMode(S6LEDupper, OUTPUT);
  //Switch inputs
  pinMode(S1lowerPin, INPUT);
  pinMode(S1upperPin, INPUT);
  pinMode(S2lowerPin, INPUT);
  pinMode(S2upperPin, INPUT);
  pinMode(S3lowerPin, INPUT);
  pinMode(S3upperPin, INPUT);
  pinMode(S4lowerPin, INPUT);
  pinMode(S4upperPin, INPUT);
  pinMode(S5lowerPin, INPUT);
  pinMode(S5upperPin, INPUT);
  pinMode(S6lowerPin, INPUT);
  pinMode(S6upperPin, INPUT);

  //Dashcam Outputs;
  pinMode(DashCamPower, OUTPUT);
  
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
  int LightNumber4 = 4;
  int LightNunber5 = 5;
  int LightNumber6 = 6;

  //resulting variables (for light bars)(and declare them as zero so that they don't do random things)
  
  //Override function variables (and declare them as zero so that they don't do random things)

  
 //Setup the serial driver and diagnostic
 //pinMode(ledpin, OUTPUT);
Serial.begin(9600);
Serial1.begin(9600);
delay(1000);
Serial.println("setup complete...");
}

void loop() { //MAIN LOOP
  
  
systemtime ++; //increment the main counter
currentMillis = millis(); //assign timing in the main loop

  //read switch state variables
 S1statelower = digitalRead(S1lowerPin);
 S1stateupper = digitalRead(S1upperPin);
 S2statelower = digitalRead(S2lowerPin);
 S2stateupper = digitalRead(S2upperPin);
 S3statelower = digitalRead(S3lowerPin);
 S3stateupper = digitalRead(S3upperPin);
 S4statelower = digitalRead(S4lowerPin);
 S4stateupper = digitalRead(S4upperPin);
 S5statelower = digitalRead(S5lowerPin);
 S5stateupper = digitalRead(S5upperPin);
 S6statelower = digitalRead(S6lowerPin);
 S6stateupper = digitalRead(S6upperPin);
  
//Write out the values for the swithc panel backlights. 
//uppers
analogWrite(S1LEDupper, UpperLEDoutArray[0]);
analogWrite(S2LEDupper, UpperLEDoutArray[1]);
analogWrite(S3LEDupper, UpperLEDoutArray[2]);
analogWrite(S4LEDupper, UpperLEDoutArray[3]);
analogWrite(S5LEDupper, UpperLEDoutArray[4]);
analogWrite(S6LEDupper, UpperLEDoutArray[5]);
//lowers
analogWrite(S1LEDlower, LowerLEDoutArray[0]);
analogWrite(S2LEDlower, LowerLEDoutArray[1]);
analogWrite(S3LEDlower, LowerLEDoutArray[2]);
analogWrite(S4LEDlower, LowerLEDoutArray[3]);
analogWrite(S5LEDlower, LowerLEDoutArray[4]);
analogWrite(S6LEDlower, LowerLEDoutArray[5]);

if (ignitionstate == HIGH) { //if the car is on, run the normal lighting procedure
    
    //Call the main light controls for 1 and 2
    LightLogicFunction(S1statelower, S1stateupper, S1LEDlower, S1LEDupper, lightsstate, highbeamsstate, ignitionstate, 0, lightbar1out);//call ofthe actual function
    //LightLogicFunction(S2statelower, S2stateupper, S2LEDlower, S2LEDupper, lightsstate, highbeamsstate, ignitionstate, 1, lightbar2out);//call ofthe actual function
    
    //reset the counters to zero for the override tables
    //Probably best to comment out the switch being used for the dashcam so it doesn't have weird behavior
    WorkingCounterArray[0] = 0;
    WorkingCounterArray[1] = 0;
    WorkingCounterArray[2] = 0;
    WorkingCounterArray[3] = 0;
    PreviousNameArray[0] = 0;
    PreviousNameArray[1] = 0;
    PreviousNameArray[2] = 0;
    PreviousNameArray[3] = 0;
    
    delay(10);
    }
    if (debug == 1) {
      Serial.println("debug 0.75");
    }
    
if (ignitionstate == LOW) { //While the car is off run the following 
    OverrideRoutine(ignitionstate, S1statelower, S1LEDlower, LightOutputArray[0], 0);
   //OverrideRoutine(ignitionstate, S2statelower, S2LEDlower, lightbar2out, 1);
    
    if(debug == 1){
      Serial.println("debug 0.8");
    }
    delay(10);
}

//Run the dashcam logic, since we don't really care what state the car is in to do so
   DashCamLogic(S4statelower, S4stateupper, S4LEDlower, S4LEDupper, ignitionstate, lightsstate, 3, DashCamPower); //single integer is WorkingLightNumber, should match the LEDs and Switches being used

//Serial read
if(Serial1.available() > 0){ //if the port has data on the buffer then read it then send it out the diagnostic
  serialread();
  serialdiagnostic();
  }
  
serialsend(); //send the serial data

} //end of main loop

//Light bar logic block

// Defining all our input variables into the function
//Writing directly the variables for the driver, rather than doing an analogWrite. Doing analogWrite for the display LEDS
//UPPER = AUTO and LOWER = HIGH BEAMS
// HIGH and LOW are REVERSED!!! (on input switches)
  void LightLogicFunction(int workinglower, int workingupper, int workingLEDlower, int workingLEDupper, int workingStateLights, int workingStateHighBeams, int workingIgnitionInput, int workingLightNumber, int workingoutput){
    //define the array of the output names before we get too far
    //start the main loop
    if (workingupper == LOW && workinglower == LOW) {
      if (debug == 1) {
        Serial.println((String)" Lights Breakpoint 1/" + workingLightNumber);
        //  Serial.println(workinglower);
      }
  }   
  //check to see if we're in auto then check to see about lights, if yes, then high beams
  else if (workingupper == LOW&&workingStateLights == HIGH&&workingStateHighBeams == LOW) {
      if (debug == 1) {
      Serial.println((String)" Light Breakpoint 2/" + workingLightNumber);
      }
    UpperLEDoutArray[workingLightNumber] = 255;
    LowerLEDoutArray[workingLightNumber] = midlightlevel;
    LightOutputArray[workingLightNumber] = midLEDoutlevel;
    }
    //Auto LEDs but with lights but no hight beams
  else if (workingupper == LOW&&workingStateLights == HIGH&&workingStateHighBeams == HIGH) {
      if (debug == 1) {
      Serial.println((String)" Light Breakpoint 3/" + workingLightNumber);
      }
    UpperLEDoutArray[workingLightNumber] = 255;
    LowerLEDoutArray[workingLightNumber] = midlightlevel;
    LightOutputArray[workingLightNumber] = 255;
   }//no switch action but lights on, so glow the panel
  else if (workingupper == HIGH&&workinglower ==HIGH&&workingStateLights == HIGH&&workingStateHighBeams == LOW) {
      if (debug == 1) {
      Serial.println((String)" Lights Breakpoint 4/" + workingLightNumber);
      }
    UpperLEDoutArray[workingLightNumber] = midlightlevel;
    LowerLEDoutArray[workingLightNumber] = midlightlevel;
    LightOutputArray[workingLightNumber] = 0;
  }//Auto LEDS, but no car lights
  else if (workingupper == LOW&&workingStateLights == LOW&&workingStateHighBeams == LOW) {
      if (debug == 1) {
      Serial.println((String)" Lights Breakpoint 5/" + workingLightNumber);
      }
    UpperLEDoutArray[workingLightNumber] = 255;
    LowerLEDoutArray[workingLightNumber] = 0;
    LightOutputArray[workingLightNumber] = 0;
  }//all off, no glow
  else if (workinglower == HIGH&&workingupper == HIGH&&workingStateLights == HIGH&&workingStateHighBeams == HIGH) {
      if (debug == 1) {
      Serial.println((String)" Lights Breakpoint 6/" + workingLightNumber);
      }
    UpperLEDoutArray[workingLightNumber] = midlightlevel;
    LowerLEDoutArray[workingLightNumber] = midlightlevel;
    LightOutputArray[workingLightNumber] = 0;
  }//Hight beams and glowing panel
  else if (workinglower == LOW&&workingStateLights == LOW) {
      if (debug == 1) {
      Serial.println((String)" Lighs Breakpoint 7/" + workingLightNumber);
      }
    UpperLEDoutArray[workingLightNumber] = 0;
    LowerLEDoutArray[workingLightNumber] = 255;
    LightOutputArray[workingLightNumber] = 255;
  }//High beams no glow on rest of panel
  else if (workinglower == LOW){
      if (debug == 1) {
      Serial.println((String)" Lights Breakpoint 8/" + workingLightNumber);
      }
    UpperLEDoutArray[workingLightNumber] = midlightlevel;
    LowerLEDoutArray[workingLightNumber] = 255;
    LightOutputArray[workingLightNumber] = 255;
  }//all off panel glowing
  else if (workinglower == HIGH&&workingupper == HIGH&&workingStateLights == HIGH&&workingStateHighBeams == LOW) {
    UpperLEDoutArray[workingLightNumber] = midlightlevel;
    LowerLEDoutArray[workingLightNumber] = midlightlevel;
    LightOutputArray[workingLightNumber] = 0;
      if (debug == 1) {
      Serial.println((String)" Lights Breakpoint 9/" + workingLightNumber);
      }
  }
  else if (workinglower == HIGH&&workingupper == HIGH&&workingStateLights == LOW&&workingStateHighBeams == LOW) { //this line returns the system to zero state
  UpperLEDoutArray[workingLightNumber] = 0; //turn off the LEDs when we return to this state
  LowerLEDoutArray[workingLightNumber] = 0;
  LightOutputArray[workingLightNumber] = 0; // turn off any light output too
  if (debug == 1){
    Serial.println((String)" Lights Breakpoint 9.5/" + workingLightNumber);
  }
  else if (workinglower == HIGH&&workingupper == LOW&&workingStateLights == LOW&&workingStateHighBeams == LOW) { //possibly redudent, this should proably be all converted to tables
    UpperLEDoutArray[workingLightNumber] = 0;
    LowerLEDoutArray[workingLightNumber] = 0;
    LightOutputArray[workingLightNumber] = 0;
    if (debug == 1){
      Serial.println((String)" Lights Breakpoint 9.75/" + workingLightNumber);
      }
    }
  //else if (workingupper == HIGH&&workingStateLights == LOW&&workingStateHighBeams == LOW 
  }
  }//end Light selection function

//Override logic block 

void OverrideRoutine(int WorkingStateIgnition, int WorkingStateButtonHigh, int WorkingLEDlower, int WorkingOutput, int WorkingSwitchNumber) {
  //tables are established in global variables
  //check for state change from last time
  if (WorkingStateButtonHigh != PreviousNameArray[WorkingSwitchNumber]&&WorkingStateIgnition == LOW) { //increments the value in the counter array on change detection
        WorkingCounterArray[WorkingSwitchNumber] ++;
    if (debug == 1) { 
    Serial.println((String)" Override Breakpoint 10/" + WorkingCounterArray[WorkingSwitchNumber]);//same
    }
        PreviousNameArray[WorkingSwitchNumber] = WorkingStateButtonHigh;//same
  }
    if (WorkingCounterArray[WorkingSwitchNumber] >= OverrideNumber&&WorkingStateButtonHigh == LOW&&WorkingStateIgnition == LOW) {
    LowerLEDoutArray[WorkingSwitchNumber] = 255; 
    LightOutputArray[WorkingSwitchNumber] = 255;
   if (debug == 1){
    Serial.print((String)" override Breakpoint 10.5/" + WorkingNumberCounterArray[WorkingSwitchNumber] + "/255");
   }
    
  }
  else if (WorkingStateButtonHigh == LOW&&WorkingStateIgnition == LOW&&WorkingCounterArray[WorkingSwitchNumber] == 1) {
    WorkingCounterArray[WorkingSwitchNumber] = 0;
    LowerLEDoutArray[WorkingSwitchNumber] = 255; 
    LightOutputArray[WorkingSwitchNumber] = 255;
       if (debug == 1){
    Serial.print((String)" Override Breakpoint 11/" + WorkingNumberCounterArray[WorkingSwitchNumber] + "/255");
   }
  }
  else {
    analogWrite(WorkingLEDlower, 0);
    LightOutputArray[WorkingSwitchNumber] = 0;//this is what's causing the working output  to go bananas
      if (debug == 1){
    Serial.print((String)" Override Breakpoint 12/" + WorkingNumberCounterArray[WorkingSwitchNumber] + "/0");
   }
  }  
  if (debug == 1){
    Serial.println((String)" Override Breakpoint 13/" + WorkingNumberCounterArray[WorkingSwitchNumber]);
  }
}

//Dashcam logic block
//HIGH and LOW switch logic is reversed!!!

int DashCamLogic(int workinglower, int workingupper, int workingLEDlower, int workingLEDupper, int workingStateIgnition, int workingStateLights, int workingSwitchNumber, int workingPower){ //UPPER  = auto and LOWER = ON no matter what
  if (voltage >= DashCamDropoutVoltage){ //check to make sure the voltage is high enough so we don't kill a battery
   if (workingupper == LOW && workingStateIgnition == LOW) { // car off, auto mode
   digitalWrite(workingPower, DashCamOff);
   LowerLEDoutArray[workingSwitchNumber] = 0;
   UpperLEDoutArray[workingSwitchNumber] = 0; 
   if (debug == 1) {
    Serial.println((String)"Dashcam " + workingSwitchNumber + " breakpoint 1");
     }
   }
   else if (workingupper == LOW && workingStateLights == LOW && workingStateIgnition == HIGH) { //car on auto mode, no lights
    digitalWrite(workingPower, DashCamOn);
    LowerLEDoutArray[workingSwitchNumber] = 0;
    UpperLEDoutArray[workingSwitchNumber] = 255; 
     if (debug == 1) {
    Serial.println((String)"Dashcam " + workingSwitchNumber + " breakpoint 2");
     }
   }
   else if (workingupper == LOW && workingStateLights == HIGH && workingStateIgnition == HIGH) { //car on, lights on, auto mode
    digitalWrite(workingPower, DashCamOn);
    LowerLEDoutArray[workingSwitchNumber] = midlightlevel;
    UpperLEDoutArray[workingSwitchNumber] = 255;
     if (debug == 1) {
    Serial.println((String)"Dashcam " + workingSwitchNumber + " breakpoint 3 // lower = " + LowerLEDoutArray[workingSwitchNumber] + "upper = " + UpperLEDoutArray[workingSwitchNumber]);
     }
   }
   else if (workingupper == HIGH && workinglower == HIGH && workingStateIgnition == HIGH && workingStateLights == LOW) {//no orders no backlight
    digitalWrite(workingPower, DashCamOff);
    LowerLEDoutArray[workingSwitchNumber] = 0;
    UpperLEDoutArray[workingSwitchNumber] = 0;
      if (debug == 1) {
    Serial.println((String)"Dashcam " + workingSwitchNumber + " breakpoint 3.5");
     }
   }
   else if (workingupper == HIGH && workinglower == HIGH && workingStateLights == HIGH) { //no orders, general backlight
    digitalWrite(workingPower, DashCamOff);
    LowerLEDoutArray[workingSwitchNumber] = midlightlevel;
    UpperLEDoutArray[workingSwitchNumber] = midlightlevel;
     if (debug == 1) {
    Serial.println((String)"Dashcam " + workingSwitchNumber + " breakpoint 4");
     }
   }
   else if (workinglower == LOW && workingStateLights == LOW && workingStateIgnition == LOW) { //ignition off, no lights, commanded force on
    TimerCall (DashCamBlinkInterval, workingSwitchNumber, "Lower"); //calling timer instead of directly writing to the array
    UpperLEDoutArray[workingSwitchNumber] = 0;
    digitalWrite(workingPower, DashCamOn);
     if (debug == 1) {
     Serial.println((String)"Dashcam " + workingSwitchNumber + " breakpoint 5");
     }
   }
   else if (workinglower == LOW && workingStateLights == LOW && workingStateIgnition == HIGH) { //ignition on, no lights, commanded force on, 
    digitalWrite(workingPower, DashCamOn);
    LowerLEDoutArray[workingSwitchNumber] = 255;
    UpperLEDoutArray[workingSwitchNumber] = 0;
     if (debug == 1) {
    Serial.println((String)"Dashcam " + workingSwitchNumber + " breakpoint 5.5");
     }
   }
  else if (workinglower == LOW && workingStateLights == HIGH && workingStateIgnition == HIGH) { //force on, lights on 
    digitalWrite(workingPower, DashCamOn);
    LowerLEDoutArray[workingSwitchNumber] = 255;
    UpperLEDoutArray[workingSwitchNumber] = midlightlevel;
     if (debug == 1) {
     Serial.println((String)"Dashcam " + workingSwitchNumber + " breakpoint 6");
     }
   }
  else if (workinglower == HIGH && workingupper == HIGH && workingStateIgnition == LOW) { //needed to clear the light state
    digitalWrite(workingPower, DashCamOff);
    LowerLEDoutArray[workingSwitchNumber] = 0;
    UpperLEDoutArray[workingSwitchNumber] = 0;
     if (debug == 1) {
     Serial.println((String)"Dashcam " + workingSwitchNumber + " breakpoint 7");
     }
   }
  else if (workinglower == LOW && workingStateIgnition == HIGH && workingStateLights == LOW) { //needed to keep on in auto no lights
    digitalWrite(workingPower, DashCamOn);
    LowerLEDoutArray[workingSwitchNumber] = 255;
    UpperLEDoutArray[workingSwitchNumber] = 0;
     if (debug == 1) {
     Serial.println((String)"Dashcam " + workingSwitchNumber + " breakpoint 8");
     }
   }
  else if (workinglower == LOW && workingStateIgnition == HIGH && workingStateLights == HIGH) {
    digitalWrite(workingPower, DashCamOn);
    LowerLEDoutArray[workingSwitchNumber] = 255;
    UpperLEDoutArray[workingSwitchNumber] = midlightlevel;
     if (debug == 1) {
     Serial.println((String)"Dashcam " + workingSwitchNumber + " breakpoint 9");
     }
   }
  else if (workinglower == HIGH && workingStateIgnition == LOW && workingStateLights == LOW) {
    digitalWrite(workingPower, DashCamOff);
    LowerLEDoutArray[workingSwitchNumber] = 0;
    UpperLEDoutArray[workingSwitchNumber] = 0;
     if (debug == 1) {
     Serial.println((String)"Dashcam " + workingSwitchNumber + " breakpoint 10");
     }
   }
  }
  else {
  digitalWrite(workingPower, DashCamOn); //shutdown if batts low
  LowerLEDoutArray[workingSwitchNumber] = 0;
  UpperLEDoutArray[workingSwitchNumber] = 0;
   if (debug == 1) {
     Serial.println((String)"Dashcam " + workingSwitchNumber + " breakpoint 11");
     }
  }
} //end dashcam subroutine

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
}
void serialdiagnostic() { //diagnostic readout for USB serial port
  Serial.println((String)"TFourR/" + unitname +" > " + mastername + "/T-" + systemtime + "//1//" + previousMillis + "//2//" + currentMillis + "/V" + voltage + "/I" + ignitionstate + "/L" + lightsstate + "/H" + highbeamsstate + "/CH1" + LightOutputArray[0] + "/CH2" + LightOutputArray[1] + "/CH3" + LightOutputArray[2] + "/CH4" + LightOutputArray[3] + "/CH5" + LightOutputArray[4] + "/CH6" + LightOutputArray[5] + "/");
  }

void serialsend()  { //send the outgoing serial data
  Serial1.println((String)"TFourR/" + unitname +" > " + mastername + "/T-" + systemtime + "/" + voltage + "/" + ignitionstate + "/" + lightsstate + "/" + highbeamsstate + "/" + LightOutputArray[0] + "/" + LightOutputArray[1] + "/" + LightOutputArray[2] + "/" + LightOutputArray[3] + "/" + LightOutputArray[4] + "/" + LightOutputArray[5] + "/");
}

void TimerCall (int workingInterval, int workingSwitchNumber, String workingSwitchChoice) {
    if(currentMillis - previousMillis >= workingInterval){
    previousMillis = currentMillis;
      if(workingSwitchChoice == "Upper") {
        Serial.println((String)workingSwitchNumber+ " Upper array out = " + UpperLEDoutArray[workingSwitchNumber]);
        if(UpperLEDoutArray[workingSwitchNumber] == 255) {
        UpperLEDoutArray[workingSwitchNumber] = 0;
        Serial.println((String)workingSwitchNumber+ " Upper array out = " + UpperLEDoutArray[workingSwitchNumber]);
        } else {
        UpperLEDoutArray[workingSwitchNumber] = 255;
        Serial.println((String)workingSwitchNumber+ "// Upper array out = " + UpperLEDoutArray[workingSwitchNumber]);
        }
      }
      if(workingSwitchChoice == "Lower") {
        Serial.println((String)workingSwitchNumber+ "array out = " + LowerLEDoutArray[workingSwitchNumber]);
        if(LowerLEDoutArray[workingSwitchNumber] == 255) {
        LowerLEDoutArray[workingSwitchNumber] = 0;
        Serial.println((String)workingSwitchNumber+ "array out = " + LowerLEDoutArray[workingSwitchNumber]);
        } else {
        LowerLEDoutArray[workingSwitchNumber] = 255;
        Serial.println((String)workingSwitchNumber+ "//array out = " + LowerLEDoutArray[workingSwitchNumber]);
        }
      }
   }
}


