const int MAX_SILENCE_MILLIS = 2000;  

unsigned long startTimeMillis;
void setup() 
{
  Serial.begin(9600);
  waitForSerial();
  //NOTE might want to replace this initialization with a check in the first loop, so we dont instantly reboot
  startTimeMillis = millis(); 

}

void loop() {
  unsigned long currentTimeMillis = millis();
  unsigned long tickMillis = currentTimeMillis - startTimeMillis;
  if (tickMillis > MAX_SILENCE_MILLIS){rst();}
  if (Serial.available() > 0) { // if something has been written to the serial port
    startTimeMillis = millis();


    int value = Serial.parseInt();
    
    if(value > 0)
    {
      Serial.print("Number: ");
      Serial.print(value);
      Serial.print(", hex: ");
      Serial.print(value, HEX);
      Serial.print(", bin: ");
      Serial.println(value, BIN);
    }
  }
}


void rst(){
  //TODO connect the RST pins on the motherboard
  Serial.println("Error!");
  waitForSerial();
}

/*
busy wait for first serial signal
*/
void waitForSerial(){
    while(Serial.available() == 0){}
}

