const int HEARTBEAT_MAX_DELAY_MILLIS = 20000;  //this is coupled to the HEARTBEAT_INTERVAL in src/main.rs
const int PIN_SWITCH = 2;

unsigned long startTimeMillis;
void setup() {
  Serial.begin(9600);
  pinMode(PIN_SWITCH, OUTPUT);
  waitForSerial();
  //NOTE might want to replace this initialization with a check in the first loop, so we dont instantly reboot
  startTimeMillis = millis(); 

}

void loop(){
  unsigned long currentTimeMillis = millis();
  unsigned long tickMillis = currentTimeMillis - startTimeMillis;
  if (tickMillis > HEARTBEAT_MAX_DELAY_MILLIS){rst();}
  if (Serial.available() > 0) { // if something has been written to the serial port
    startTimeMillis = millis();
    clearSerial();
  }
}


void rst(){
  //TODO connect the RST pins on the motherboard
  Serial.println("Error!");
  digitalWrite(PIN_SWITCH, LOW);
  delay(500);
  digitalWrite(PIN_SWITCH, HIGH);
  waitForSerial();
}

/*
busy wait for first serial input
*/
void waitForSerial(){
    while(Serial.available() == 0){}
}

void clearSerial(){
  while (Serial.available()>0){
    char t = Serial.read();
  }
}
