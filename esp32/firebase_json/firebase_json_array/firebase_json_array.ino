#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>

#include <addons/TokenHelper.h>

#include <addons/RTDBHelper.h>


#define WIFI_SSID ""
#define WIFI_PASSWORD ""
/* 2. Define the API Key */
#define API_KEY ""
/* 3. Define the RTDB URL */
#define DATABASE_URL "https://proyect-app-d9350-default-rtdb.firebaseio.com/" //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app
/* 4. Define the user Email and password that alreadey registerd or added in your project */
#define USER_EMAIL "asd@gmail.com"
#define USER_PASSWORD "123456"

//Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;

void setup()
{

  Serial.begin(115200);

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

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the user sign in credentials */
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  Firebase.begin(&config, &auth);

  //Comment or pass false value when WiFi reconnection will control by your code or third party library
  Firebase.reconnectWiFi(true);
}

void loop() {

  if (Firebase.ready() && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0)) {
    sendDataPrevMillis = millis();

    FirebaseJsonArray arr;
    arr.setFloatDigits(2);
    arr.setDoubleDigits(4);
    arr.add("a", "b", "c", true, 45, (float)6.1432, 123.45692789, false);

//    Serial.printf("Set array... %s\n", Firebase.RTDB.setArray(&fbdo, "/test/array", &arr) ? "ok" : fbdo.errorReason().c_str());
      //true o false
    Serial.printf("Get array... %s\n", Firebase.RTDB.getArray(&fbdo, "/test/array") ? fbdo.to<FirebaseJsonArray>().raw() : fbdo.errorReason().c_str());
    Firebase.RTDB.getArray(&fbdo, "/test/array");

    //obtener el array de getArray y guardarlo en una variable
    // FirebaseJsonArray arr2   = Firebase.RTDB.getArray(&fbdo, "/test/array");
    
    // arr2.get(fbdo.to<FirebaseJsonArray>().raw());

//char *data  = fbdo.to<FirebaseJsonArray>().raw();
// FirebaseJsonData result;
//    FirebaseJsonArray arr2  ;
//    arr2.get();
  
//Get array data
//result.get<FirebaseJsonArray>(Firebase.RTDB.getArray(&fbdo, "/test/array") ? fbdo.to<FirebaseJsonArray>().raw(): fbdo.errorReason().c_str()));

//Call get with FirebaseJsonData to parse the array at defined index i
for (size_t i = 0; i <arr2.size(); i++)
{
  //result now used as temporary object to get the parse results
  arr.get(result, i);

  //Print its value
  Serial.print("Array index: ");
  Serial.print(i);
  Serial.print(", type: ");
  Serial.print(result.type);
  Serial.print(", value: ");
  Serial.println(result.to<String>());
}
   

  }

}
