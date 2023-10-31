int pumpPin = 13; 
int solenoidPin2 = 12; //These are the output pins on the Arduino we are using
int solenoidPin3 = 11;
int solenoidPin1 = 10;
int solenoidPin4 = 9;
int pushButton = 15;

void spray(){
  digitalWrite(pumpPin,HIGH);
  digitalWrite(solenoidPin2,HIGH);
  digitalWrite(solenoidPin3,HIGH);
  digitalWrite(solenoidPin4,HIGH);
  digitalWrite(solenoidPin1,HIGH);
  Serial.println("poump on ");
  delay(2000);
  digitalWrite(pumpPin,LOW);
  digitalWrite(solenoidPin2,LOW);
  digitalWrite(solenoidPin3,LOW);
  digitalWrite(solenoidPin4,LOW);
  digitalWrite(solenoidPin1,LOW);
  Serial.println("Soli OFF");
}
void setup() {
  Serial.begin(9600);
pinMode(pumpPin,OUTPUT);
pinMode(solenoidPin2, OUTPUT); //Sets the pins as outputs
pinMode(solenoidPin3, OUTPUT); //Sets the pins as outputs
pinMode(solenoidPin4, OUTPUT); //Sets the pins as outputs
pinMode(solenoidPin1, OUTPUT);
pinMode(pushButton,INPUT);
}

void loop() {
  if (digitalRead(pushButton) == HIGH) {
    Serial.println("triggered");
    spray();
  }
}
