void setup() {
  Serial.begin(9600);
  pinMode(13,OUTPUT);
}

void loop() {
 Serial.print("Hola mundo");
 delay(1000);
 digitalWrite(13,HIGH);
 delay(1000);
 digitalWrite(13,LOW);
 delay(1000);
}
