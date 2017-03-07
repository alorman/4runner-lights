// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int ledauto = 7;
int ledhigh = 6;
int buttonauto = 3;
int buttonhigh = 2;
int lights = 4;
int highbeams = 5;
int lightbarout = 8;
int ignitioninput = 9;
unsigned long previousmillis = 0; // undevolt variable
const long undervoltinterval = 1000; // undervolt timing
const long undervoltblinks = 5; //undervolt blinks
int currentblinks = 0; //undervolt current blinks//added to main init routine NOT void setup (deleted = 0)
int WorkingOverrideState = 0; //need
int WorkingOverrideCount = 0;//need
int PreviousOverrideState1 = 0; //will compile if in the run loop too
int PreviousOverrideState2 = 0;//call for functionizing override
int WorkingPreviousOverrideState = 0; //make and array of the different names
int WorkingPreviousOverrideState1 = 0;//will work as global  variable -- need not be a static
int WorkingPreviousOverrideState2 = 0;
int WorkingPreviousOverrideState3 = 0;
int WorkingPreviousOverrideState4 = 0;
//working override counters
int WorkingOverrideCount1 = 0;
int WorkingOverrideCount2 = 0;
int WorkingOverrideCount3 = 0;
int WorkingOverrideCount4 = 0;
//define array for working switches




// the setup routine runs once when you press reset:
void setup() {
  // initialize the digital pin as an output.
  pinMode(ledauto, OUTPUT);
  pinMode(ledhigh, OUTPUT);
  pinMode(buttonauto, INPUT);
  pinMode(buttonhigh, INPUT);
  pinMode(lights, INPUT);
  pinMode(highbeams, INPUT);
  pinMode(lightbarout, OUTPUT);
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  int stateignition = digitalRead(ignitioninput);
  int stateauto = digitalRead(buttonauto);
  int statehigh = digitalRead(buttonhigh); 
  int statelights = digitalRead(lights);
  int statehighbeams = digitalRead(highbeams);
  int voltagesense = analogRead(A2);
  int incomingByte;
  int oldByte;
  int time;
  int Override1;
  int Override2;

    // Voltage regulation checking

  float voltage;
  time = millis();
  voltage = voltagesense / 51.17; //remember to add the damn zero after the decimal
  /*if (incomingByte == oldByte) {
    incomingByte = Serial.read();
    Serial.println("serial good ");
    oldByte = incomingByte;
  *//*  if (OverrideState != PreviousOverrideState&&statelights == LOW) {
        OverrideCount ++;
        Serial.print("Button presses ");
        Serial.println(OverrideCount);
        PreviousOverrideState = OverrideState;
  }
  /* else {
    Serial.println("serial no good");
    incomingByte = Serial.read();
    incomingByte = oldByte;
  }
 *//* if (OverrideCount >= 2&&statehigh == HIGH&&statelights == LOW) {
    analogWrite(ledhigh, 255);
    Serial.println("Overriden and hot");
  }
  else if (statehigh == HIGH&&statelights == HIGH) {
    OverrideCount = 1;
    analogWrite(ledhigh, 255);
    Serial.println("Car on now, overrides reset");
  }
  else {
    analogWrite(ledhigh, 0);
    Serial.println("cold power off"); */
  Override1 = OverrideRoutine(PreviousOverrideState1, statelights, statehigh, ledhigh, 1);
  Override2 = OverrideRoutine(PreviousOverrideState2, statelights, stateauto, ledauto, 2);
  delay(100);
}

int OverrideRoutine(int WorkingOutput, int WorkingStateEngine, int WorkingStateButtonHigh, int WorkingLEDHigh, int WorkingSwitchNumber) { 

  int static PreviousNameArray[] = {WorkingPreviousOverrideState1, WorkingPreviousOverrideState2, WorkingPreviousOverrideState3, WorkingPreviousOverrideState4};
  int static WorkingCounterArray[] = {WorkingOverrideCount1, WorkingOverrideCount2, WorkingOverrideCount3, WorkingOverrideCount4};
  if (WorkingStateButtonHigh != PreviousNameArray[WorkingSwitchNumber]&&WorkingStateEngine == LOW) { //these table calls seems to work
    WorkingCounterArray[WorkingSwitchNumber] ++;
        Serial.print("Button presses ");
        Serial.println(WorkingCounterArray[WorkingSwitchNumber]);
    	Serial.print("on switch ");
    	Serial.println(WorkingSwitchNumber);
        PreviousNameArray[WorkingSwitchNumber] = WorkingStateButtonHigh;
  }
    if (WorkingOverrideCount >= 3&&WorkingStateButtonHigh == HIGH&&WorkingStateEngine == LOW) {
    analogWrite(WorkingLEDHigh, 255);
    Serial.print("Overriden and hot on ");
    Serial.println(PreviousNameArray[WorkingSwitchNumber]);
  }
  else if (WorkingStateButtonHigh == HIGH&&WorkingStateEngine == HIGH) {
    WorkingCounterArray[WorkingSwitchNumber] = 1;
    analogWrite(WorkingLEDHigh, 255);
    Serial.println("Car on now, overrides reset");
  }
  else {
    analogWrite(WorkingLEDHigh, 0);
    Serial.println("cold power off");
  }  
}/*
  if (voltage <= 11.5&&currentblinks <= undervoltblinks) {
    analogWrite(ledauto, 255);
    delay (undervoltinterval);
    analogWrite(ledauto, 0);
    delay (undervoltinterval);
    currentblinks++;
    Serial.println(currentblinks);
  } 
  else if (voltage <= 11.5&&currentblinks >= undervoltblinks) {
    analogWrite(ledauto, 0);
    Serial.println("Low Batt");
  }
  else
  {
  //check for illegal button press before we do anything
  if (statehigh == HIGH&&stateauto == HIGH) {
    Serial.println("Illegal button press");
  }   
  //check to see if we're in auto then check to see about lights, if yes, then high beams
  else if (stateauto == HIGH&&statelights == HIGH&&statehighbeams == HIGH) {
    Serial.println("Auto High, please");
    analogWrite(ledauto, 255);
    analogWrite(ledhigh, 125);
    analogWrite(lightbarout, 255);
    }
  else if (stateauto == HIGH&&statelights == HIGH&&statehighbeams == LOW) {
    Serial.println("Auto medium beams, please");
    analogWrite(ledauto, 255);
    analogWrite(ledhigh, 125);
    analogWrite(lightbarout, 125);
   }
  else if (stateauto == LOW&&statelights == HIGH&&statehigh == LOW) {
    Serial.println("Lights on, light bars off, just light up the panel");
    analogWrite(ledauto, 125);
    analogWrite(ledhigh, 125);
    analogWrite(lightbarout, 0);
  }  
  else if (stateauto == HIGH&&statelights == LOW&&statehighbeams == LOW) {
    Serial.println("Auto, but no lights, thanks");
    analogWrite(ledauto, 0);
    analogWrite(ledhigh, 0);
    analogWrite(lightbarout, 0);
  }
  else if (stateauto == LOW&&statelights == LOW&&statehighbeams == LOW&&statehigh == LOW) {
    Serial.println("All off");
    analogWrite(ledauto, 0);
    analogWrite(ledhigh, 0);
    analogWrite(lightbarout, 0);
  }
  else if (statehigh == HIGH){
    Serial.println("Manual high LEDS");
    analogWrite(ledauto, 0);
    analogWrite(ledhigh, 255);
    analogWrite(lightbarout, 255);
  }
  }
}
*/
