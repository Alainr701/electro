//EJEMPLO DE COMO USAR EL MODULO RGB_COLORS EN ARDUINO
//@autor : Alain 

#define green 2
#define blue  3
#define red   4

int number = 0;

void setup() {
  Serial.begin(9600);
  pinMode(green, OUTPUT);
  pinMode(blue , OUTPUT);
  pinMode(red  , OUTPUT);
}

void loop() {

  analogWrite(green, randomColor());
  analogWrite(blue , randomColor());
  analogWrite(red  , randomColor());

  delay(1000);
}

int randomColor(){
  number = random(0, 255);
  return number;
}
