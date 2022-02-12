//registro de desplazamiento74HC595


//Pin connected to ST_CP 
int latchPin = 4;
//Pin connected to SH_CP
int clockPin = 2;
////Pin connected to DS 
int dataPin = 3;

#define TIEMPO 150


void setup(){
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void ledWrite(int Led){
   shiftOut(dataPin, clockPin, LSBFIRST, Led);
   digitalWrite(latchPin, HIGH);
   digitalWrite(latchPin, LOW);
}
  
void loop(){
  
//   for (int j = 0; j < 256; j++) {
//     digitalWrite(latchPin, LOW);
//     shiftOut(dataPin, clockPin, LSBFIRST, j);
//     digitalWrite(latchPin, HIGH);
//     delay(100);
//   }
	
   ledWrite(B00000000); delay(TIEMPO);
   ledWrite(B00000001); delay(TIEMPO);
   ledWrite(B00000011); delay(TIEMPO);
   ledWrite(B00000110); delay(TIEMPO);
   ledWrite(B00001100); delay(TIEMPO);
   ledWrite(B00011000); delay(TIEMPO);
   ledWrite(B00110000); delay(TIEMPO);
   ledWrite(B01100000); delay(TIEMPO);
   ledWrite(B11000000); delay(TIEMPO);
   ledWrite(B10000000); delay(TIEMPO);
   ledWrite(B00000000); delay(TIEMPO);

   delay(1000);

   ledWrite(B00000000); delay(TIEMPO);
   ledWrite(B10000001); delay(TIEMPO);
   ledWrite(B01000010); delay(TIEMPO);
   ledWrite(B00100100); delay(TIEMPO);
   ledWrite(B00011000); delay(TIEMPO);
   ledWrite(B00100100); delay(TIEMPO);
   ledWrite(B01000010); delay(TIEMPO);
   ledWrite(B10000001); delay(TIEMPO);
   ledWrite(B00000000); delay(TIEMPO);

   delay(1000);

   ledWrite(B00000000); delay(TIEMPO);
   ledWrite(B10000000); delay(TIEMPO);
   ledWrite(B11000000); delay(TIEMPO);
   ledWrite(B11100000); delay(TIEMPO);
   ledWrite(B11110000); delay(TIEMPO);
   ledWrite(B11111000); delay(TIEMPO);
   ledWrite(B11111100); delay(TIEMPO);
   ledWrite(B11111110); delay(TIEMPO);
   ledWrite(B11111111); delay(TIEMPO);
   ledWrite(B01111111); delay(TIEMPO);
   ledWrite(B00111111); delay(TIEMPO);
   ledWrite(B00011111); delay(TIEMPO);
   ledWrite(B00001111); delay(TIEMPO);
   ledWrite(B00000111); delay(TIEMPO);
   ledWrite(B00000011); delay(TIEMPO);
   ledWrite(B00000001); delay(TIEMPO);
   ledWrite(B00000000); delay(TIEMPO);

   delay(1000);

   ledWrite(B00000000); delay(TIEMPO);
   ledWrite(B10101010); delay(TIEMPO);
   ledWrite(B01010101); delay(TIEMPO);
   ledWrite(B10101010); delay(TIEMPO);
   ledWrite(B01010101); delay(TIEMPO);
   ledWrite(B10101010); delay(TIEMPO);
   ledWrite(B01010101); delay(TIEMPO);
   ledWrite(B10101010); delay(TIEMPO);
   ledWrite(B01010101); delay(TIEMPO);
   ledWrite(B00000000); delay(TIEMPO);

   delay(1000);
}
