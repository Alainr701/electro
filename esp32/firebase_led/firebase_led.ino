//#include <WiFi.h>
//#include "FirebaseESP32.h"
//
//#define FIREBASE_HOST "https://proyect-app-d9350-default-rtdb.firebaseio.com"
//#define FIREBASE_AUTH ""
//#define WIFI_SSID ""
//#define WIFI_PASSWORD "0aOx7aUbdzWy"
//
//FirebaseData firebaseData;
//String path = "/Test";

void setup() {
  pinMode(13,OUTPUT);
//  
//  Serial.begin(9600);
//  pinMode(2,OUTPUT);
//  pinMode(27,OUTPUT);
//  
//  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
//  Serial.print("[Wi-Fi]...Connecting");
//  while (WiFi.status() != WL_CONNECTED)
//  {
//    Serial.print(".");
//    delay(300);
//  }
//  Serial.println();
//  Serial.print("Connected with IP: ");
//  Serial.println(WiFi.localIP());
//  Serial.println();
//
//  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
//  Firebase.reconnectWiFi(true);

  //Firewall that allows only GET and POST requests
  //Firebase.enableClassicRequest(firebaseData, true);
}

void loop() {
  digitalWrite(13,HIGH);
  delay(1000);
  digitalWrite(13,LOW);
  delay(1000);
//  Firebase.getInt(firebaseData, path + "/LED");
//  Serial.println("Data= " + String(firebaseData.intData()));
//  delay(200);
//  if(firebaseData.intData()==1)
//  {
//    digitalWrite(2,HIGH);
//    digitalWrite(27,HIGH);
//  }
//  else{
//    digitalWrite(2,LOW);
//    digitalWrite(27,LOW);
//  }
 // Firebase.end(firebaseData);
}
