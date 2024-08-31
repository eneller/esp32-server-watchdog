const int HEARTBEAT_REBOOT_DELAY_MILLIS = 20000;  //this is coupled to the HEARTBEAT_INTERVAL in src/main.rs
const int HEARTBEAT_BOOT_DELAY_MILLIS = 60000;
const int PIN_REBOOT = 2;
const int PIN_BOOT = 3;

unsigned long startTimeMillis;
void setup() {
  Serial.begin(9600);
  pinMode(PIN_REBOOT, OUTPUT);
  pinMode(PIN_BOOT, OUTPUT);
  waitForSerial();
  //NOTE might want to replace this initialization with a check in the first loop, so we dont instantly reboot
  startTimeMillis = millis(); 

}

void loop(){
  if (millis() - startTimeMillis > HEARTBEAT_REBOOT_DELAY_MILLIS){pin_switch(PIN_REBOOT);}
  if (Serial.available() > 0) { // if something has been written to the serial port
    startTimeMillis = millis();
    clearSerial();
  }
}


void pin_switch(int pin){
  //TODO connect the RST pins on the motherboard
  Serial.println("Error!");
  digitalWrite(pin, LOW);
  delay(500);
  digitalWrite(pin, HIGH);
  waitForSerial();
}

/*
busy wait for first serial input
*/
void waitForSerial(){
    while(Serial.available() == 0){
    //check if we may need to initiate a normal boot instead of a reboot, e.g. after a power outage
    if (millis() - startTimeMillis > HEARTBEAT_BOOT_DELAY_MILLIS){
      pin_switch(PIN_BOOT);
    }
    }
}

void clearSerial(){
  while (Serial.available()>0){
    char t = Serial.read();
  }
}
