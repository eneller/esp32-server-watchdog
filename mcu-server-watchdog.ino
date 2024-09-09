const int HEARTBEAT_REBOOT_DELAY_MILLIS = 2000;  //this is coupled to the HEARTBEAT_INTERVAL in src/main.rs
const int HEARTBEAT_BOOT_DELAY_MILLIS = 9000;
const int PIN_REBOOT = 2;
const int PIN_BOOT = 3;

bool rebooted = false;

unsigned long startTimeMillis;
void setup() {
  Serial.begin(9600);
  pinMode(PIN_REBOOT, OUTPUT);
  pinMode(PIN_BOOT, OUTPUT);
  //NOTE might want to replace this initialization with a check in the first loop, so we dont instantly reboot
  startTimeMillis = millis(); 

}

void loop(){
  if (Serial.available() > 0) { // if something has been written to the serial port
    startTimeMillis = millis();
    clearSerial();
    rebooted = false;
    Serial.println("read serial");
  }
  unsigned long timeElapsed = millis() - startTimeMillis;
  if (timeElapsed > HEARTBEAT_REBOOT_DELAY_MILLIS &&  not rebooted){
    pin_switch(PIN_REBOOT);
    startTimeMillis = millis();
    rebooted = true;
    Serial.println("reboot");

  }
  if (timeElapsed > HEARTBEAT_BOOT_DELAY_MILLIS){
    pin_switch(PIN_BOOT);
    startTimeMillis = millis();
    Serial.println("boot");

  }
  
}


void pin_switch(int pin){
  //TODO connect the RST pins on the motherboard
  digitalWrite(pin, LOW);
  delay(500);
  digitalWrite(pin, HIGH);
}



void clearSerial(){
  while (Serial.available()>0){
    char t = Serial.read();
  }
}
