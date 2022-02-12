#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif

#include <Firebase_ESP_Client.h>

#include <addons/TokenHelper.h>

#include <addons/RTDBHelper.h>

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
#define vA 13
#define vB 12
#define vC 14
#define vD 27

/* 6. Define the Firebase Data object */
FirebaseData fbdo;

/* 7. Define the FirebaseAuth data for authentication data */
FirebaseAuth auth;

/* 8. Define the FirebaseConfig data for config data */
FirebaseConfig config;

unsigned long dataMillis = 0;

int count = 0;

// Variables
byte valveA = 0;
byte valveB = 0;
byte valveC = 0;
byte valveD = 0;

void setup()
{
  Serial.begin(115200);
  // firebase
  initFirebase();
  // puertos
  pinMode(vA, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(vB, OUTPUT);
  pinMode(vC, OUTPUT);
  pinMode(vD, OUTPUT);
}

void loop()
{
  // writeFirebase(HIGH, vA ,"valvulaA");
  // writeFirebase(HIGH, vB ,"valvulaB");
  // writeFirebase(HIGH, vC ,"valvulaC");
  // writeFirebase(HIGH, vD ,"valvulaD");
  // readFirebase();
}

void readArray(){
  
  if (millis() - dataMillis > 5000 && Firebase.ready())
  {
    dataMillis = millis();
    String path = "/UsersDevice/";
    path += auth.token.uid.c_str();
    path += "/Actuators/lista";
    if (Firebase.RTDB.get(&fbdo, path))
    {
      if (fbdo.dataTypeEnum() == fb_esp_rtdb_data_type_integer)
      {
        Serial.println(fbdo.to<int>());
        if (fbdo.to<int>() == 1)
        {
          digitalWrite(13, HIGH);
        }
        if (fbdo.to<int>() == 0)
        {
          digitalWrite(13, LOW);
        }
      }
    }
    else
    {
      Serial.println(fbdo.errorReason());
    }
  }

}


void readFirebase()
{

  if (millis() - dataMillis > 1000 && Firebase.ready())
  {
    dataMillis = millis();
    String path = "/UsersDevice/";
    path += auth.token.uid.c_str();
    path += "/Actuators/valvulaA";
    if (Firebase.RTDB.getInt(&fbdo, path))
    {
      if (fbdo.dataTypeEnum() == fb_esp_rtdb_data_type_integer)
      {
        Serial.println(fbdo.to<int>());
        if (fbdo.to<int>() == 1)
        {
          digitalWrite(13, HIGH);
        }
        if (fbdo.to<int>() == 0)
        {
          digitalWrite(13, LOW);
        }
      }
    }
    else
    {
      Serial.println(fbdo.errorReason());
    }
  }
}

void writeFirebase(byte state, byte pin, String name)
{
  if (millis() - dataMillis > 10000 && Firebase.ready())
  {
    dataMillis = millis();
    String path = "/UsersDevice/";
    path += auth.token.uid.c_str();
    path += "/Actuators/" + name;
    Serial.printf("Set  data ... %s\n", Firebase.RTDB.setInt(&fbdo, path, state) ? "ok" : fbdo.errorReason().c_str());
    switch (pin)
    {
    case vA:
      digitalWrite(vA, state);
      break;
    case vB:
      digitalWrite(vB, state);
      break;
    case vC:
      digitalWrite(vC, state);
      break;
    case vD:
      digitalWrite(vD, state);
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
