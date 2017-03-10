// Testing serial1 writing between Teensy boards
//Master
int lights = 1;
int ignition = 0;
int highbeams = 1;
int ch1 = 255;
int systemtime;
int ledpin = 13;
String outgoingbuffer = "";

void setup() {
  // put your setup code here, to run once:
pinMode(ledpin, OUTPUT);
Serial.begin(9600);
Serial1.begin(9600);
Serial.println("setup complete...");
}

void loop() {
  //while(Serial1.available() > 0){
 
  //int temptime = Serial1.parseInt();
  //int tempignition = Serial1.parseInt();
  //int templights = Serial1.parseInt();
  //int temphighbeams = Serial1.parseInt();
  //int tempch1 = Serial1.parseInt(); //dont actually care about this data

 // while (systemtime != temptime) //check to make sure time is reading
 // {
    //copy the temp incoming values to real ones
  //ignition = tempignition;
  //lights = templights;
  //highbeams = temphighbeams;

   //do our sensor reading here


 systemtime ++;
  Serial1.println((String)"*" + systemtime + "/" + ignition + "/" + lights + "/" + highbeams + "/" + ch1 + "/");
  //whole shebang again for serial diagnostic
  Serial.println((String)"TFourR/Upper -> Lower/T-" + systemtime + "/I" + ignition + "/L" + lights + "/H" + highbeams + "/CH1" + ch1 + "/");
  delay(50);
 // }
 // Serial.println("time no good");
 // delay(200);
  }
//Serial.println("Serial 1 not found");
//delay(200);
//}
