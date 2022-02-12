#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif

#include <Firebase_ESP_Client.h>

#include <addons/TokenHelper.h>

#include <addons/RTDBHelper.h>

#include <DHT.h>


/* 1. Define the WiFi credentials */
#define WIFI_SSID ""
#define WIFI_PASSWORD ""

/** 2. Define the API key*/
#define API_KEY ""

/* 3. Define the user Email and password that already registerd or added in your project */
#define USER_EMAIL "asd@gmail.com"
#define USER_PASSWORD "123456"

/* 4. If work with RTDB, define the RTDB URL */
#define DATABASE_URL "https://proyect-app-d9350-default-rtdb.firebaseio.com/" //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app

/** 5. Define the database secret (optional)*/
#define DATABASE_SECRET "DATABASE_SECRET"

// const
#define pinvA 13
#define pinvB 12
#define pinvC 14

//sensors
#define DHTTYPE DHT11
#define DHTPIN 15

DHT dht(DHTPIN, DHTTYPE, 27);

float temperature;
float humidity;

/* 6. Define the Firebase Data object */
FirebaseData fbdo;

/* 7. Define the FirebaseAuth data for authentication data */
FirebaseAuth auth;

/* 8. Define the FirebaseConfig data for config data */
FirebaseConfig config;

unsigned long dataMillis = 0;
unsigned long dataMillis2 = 0;

int count = 0;

// Variables
byte a = 0;
byte b = 0;
byte c = 0;

void setup()
{
  Serial.begin(115200);
  //sensors
  dht.begin();

  // firebase
  initFirebase();
  // puertos
  pinMode(pinvA, OUTPUT);
  pinMode(pinvB,OUTPUT);
  pinMode(pinvC,OUTPUT);
 
}

void loop(){

 readTemperature();


  // writeFirebase(HIGH, vA ,"valvulaA");
  // writeFirebase(HIGH, vB ,"valvulaB");
  // writeFirebase(HIGH, vC ,"valvulaC");
//  readFirebase("valvulaA",pinvA);

//  readFirebase("valvulaB",pinvB);
//
//  readFirebase("valvulaC",pinvC);



  if (millis() - dataMillis > 5000 && Firebase.ready()){
    dataMillis = millis();
    Serial.print(dataMillis);
    readApp("valvulaA",pinvA);
    readApp("valvulaB",pinvB);
    readApp("valvulaC",pinvC);
    readApp("temp",0);
  }
   writeFirebaseTemp();


}

void readApp(String name , byte pin){
  String path = "/UsersDevice/";
    path += auth.token.uid.c_str();
    path += "/Actuators/";
    path += name;
    if (Firebase.RTDB.getInt(&fbdo, path)){
      if (fbdo.dataTypeEnum() == fb_esp_rtdb_data_type_integer){
        Serial.println(fbdo.to<int>());
        if (fbdo.to<int>() == 1){
          digitalWrite(pin, HIGH);
        }
        if (fbdo.to<int>() == 0){
          digitalWrite(pin, LOW);
        }
      }
    }
    else{
      Serial.println(fbdo.errorReason());
    }  
}

void readTemperature(){
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
  
  if (isnan(humidity)) {
    Serial.println(F("Failed to read humidity!"));
    return;
  }
//  Serial.print(F("Temperature: "));
//  Serial.print(temperature);
//  Serial.print(F(" *C"));
//  Serial.print(F("Humidity: "));
//  Serial.print(humidity);
//  Serial.println(F("%"));
}


void readFirebase(String name,int pin){

  if (millis() - dataMillis > 5000 && Firebase.ready()){
    dataMillis = millis();
    Serial.print(dataMillis);
    String path = "/UsersDevice/";
    path += auth.token.uid.c_str();
    path += "/Actuators/";
    path += name;
    if (Firebase.RTDB.getInt(&fbdo, path)){
      if (fbdo.dataTypeEnum() == fb_esp_rtdb_data_type_integer){
        Serial.println(fbdo.to<int>());
        if (fbdo.to<int>() == 1){
          digitalWrite(pin, HIGH);
        }
        if (fbdo.to<int>() == 0){
          digitalWrite(pin, LOW);
        }
      }
    }
    else{
      Serial.println(fbdo.errorReason());
    }
    //
     String pathf = "/UsersDevice/";
    pathf += auth.token.uid.c_str();
    pathf += "/Actuators/";
    pathf += name;
    if (Firebase.RTDB.getFloat(&fbdo, pathf)){
      if (fbdo.dataTypeEnum() == fb_esp_rtdb_data_type_float){
        Serial.println(fbdo.to<float>());
        
      }
    }
    else{
      Serial.println(fbdo.errorReason());
    }
  }
}

void writeFirebaseTemp(){
   if (millis() - dataMillis2 > 10000 && Firebase.ready()){
      dataMillis2 = millis();
      String path = "/UsersDevice/";
      path += auth.token.uid.c_str();
      path += "/Actuators/temp";
       String path2 = "/UsersDevice/";
      path2 += auth.token.uid.c_str();
      path2 += "/Actuators/Humi";
      Serial.printf("Set Temp %s\n", Firebase.RTDB.setFloat(&fbdo, path, temperature) ? "ok" : fbdo.errorReason().c_str());
      Serial.printf("Set Humi %s\n", Firebase.RTDB.setFloat(&fbdo, path2, humidity) ? "ok" : fbdo.errorReason().c_str());

   }
}

void writeFirebase(byte state, byte pin, String name){
  if (millis() - dataMillis > 10000 && Firebase.ready()){
    dataMillis = millis();
    String path = "/UsersDevice/";
    path += auth.token.uid.c_str();
    path += "/Actuators/" + name;
    Serial.printf("Set  data ... %s\n", Firebase.RTDB.setInt(&fbdo, path, state) ? "ok" : fbdo.errorReason().c_str());
    switch (pin){
    case pinvA:
      digitalWrite(pinvA, state);
      break;
    case pinvB:
      digitalWrite(pinvB, state);
      break;
    case pinvC:
      digitalWrite(pinvC, state);
      break;

    default:
      Serial.println("Send");
      break;
    }
  }
}

void initFirebase()
{
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }

  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);
  config.api_key = API_KEY;
  /* Assign the user sign in credentials */
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;
  /* Assign the RTDB URL */
  config.database_url = DATABASE_URL;
  Firebase.reconnectWiFi(true);
  fbdo.setResponseSize(4096);
  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h
  /** Assign the maximum retry of token generation */
  config.max_token_generation_retry = 5;
  /* Initialize the library with the Firebase authen and config */
  Firebase.begin(&config, &auth);
}
