const char OFF = 'o';
const char LON = 'L';
const char LOFF = 'l';
const char WATERON = 'W';
const char WATEROFF = 'w';

int lightpin1 = 5;
int lightpin2 = 6;
int lightpin3 = 7;
int waterpin1 = 8;


void setup() {
  pinMode(lightpin1, OUTPUT);
  pinMode(lightpin2, OUTPUT);
  pinMode(lightpin3, OUTPUT);
  pinMode(waterpin1, OUTPUT);
  digitalWrite(lightpin1, LOW);
  digitalWrite(lightpin2, LOW);
  digitalWrite(lightpin3, LOW);
  digitalWrite(waterpin1, LOW);
  Serial.begin(115200);
}
void loop() {

  if (Serial.available() > 0) {
    int incomingByte = Serial.read(); // read the incoming byte:

//    Serial.print("Recieved: ");
//    Serial.println(incomingByte, DEC);
    if (incomingByte == LON) {
//        Serial.println("yeehaw");
        digitalWrite(lightpin1, HIGH);
        digitalWrite(lightpin2, HIGH);
        digitalWrite(lightpin3, HIGH);
        delay(2000);
    }
    if (incomingByte == LOFF) {
//      Serial.println("yeehaw");
        digitalWrite(lightpin1, LOW);
        digitalWrite(lightpin2, LOW);
        digitalWrite(lightpin3, LOW);
        delay(2000);
    }
    if (incomingByte == WATERON) {
//      Serial.println("yeehaw");
        digitalWrite(waterpin1, HIGH);
        delay(2000);
    }
    if (incomingByte == WATEROFF) {
//      Serial.println("yeehaw");
        digitalWrite(waterpin1, LOW);
        delay(2000);
    }
    
    if (incomingByte == OFF) {
//      Serial.println("yeehaw");
        digitalWrite(waterpin1, LOW);
        digitalWrite(lightpin1, LOW);
        digitalWrite(lightpin2, LOW);
        digitalWrite(lightpin3, LOW);
        delay(2000);
    }
  }

  
}
