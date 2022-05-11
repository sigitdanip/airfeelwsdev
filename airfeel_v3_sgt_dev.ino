#define RX1 16
#define TX1 17

void setup(){
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RX1, TX1);
}

void loop(){
  while (Serial2.available()){
    Serial.print(char(Serial2.read()));
  }
  delay(2000);
}
