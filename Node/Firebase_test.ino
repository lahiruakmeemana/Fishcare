
/**
 * Created by K. Suwatchai (Mobizt)
 * 
 * Email: k_suwatchai@hotmail.com
 * 
 * Github: https://github.com/mobizt
 * 
 * Copyright (c) 2021 mobizt
 *
*/

#if defined(ESP32)
#include <WiFi.h>
#include <FirebaseESP32.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#endif
#include <time.h>

//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

/* 1. Define the WiFi credentials */
#define WIFI_SSID "CHAMPIKA"
#define WIFI_PASSWORD "udt2279826"

/* 2. Define the API Key */
#define API_KEY "AIzaSyCqDbo5x8NMHswaEV7EZpDEWcYc10vSdLk"

/* 3. Define the RTDB URL */
#define DATABASE_URL "https://water-measures-default-rtdb.asia-southeast1.firebasedatabase.app" //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app

/* 4. Define the user Email and password that alreadey registerd or added in your project */
#define USER_EMAIL "lahirua.18@cse.mrt.ac.lk"
#define USER_PASSWORD "fishcare1234"

//Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;

unsigned long count = 0;

const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 5.5 * 3600;
const int daylightOffset_sec = 0;
struct tm timeinfo;
char timeStringBuff[50];

void setup()
{

    Serial.begin(115200);
    Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(WiFi.localIP());
    

    Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);
    while(!getLocalTime(&timeinfo)){
      configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
      delay(500);
    }
    Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
    
    
    /* Assign the api key (required) */
    config.api_key = API_KEY;

    /* Assign the user sign in credentials */
    auth.user.email = USER_EMAIL;
    auth.user.password = USER_PASSWORD;

    /* Assign the RTDB URL (required) */
    config.database_url = DATABASE_URL;

    /* Assign the callback function for the long running token generation task */
    config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h

    //Or use legacy authenticate method
    //config.database_url = DATABASE_URL;
    //config.signer.tokens.legacy_token = "<database secret>";

    Firebase.begin(&config, &auth);

    //Comment or pass false value when WiFi reconnection will control by your code or third party library
    Firebase.reconnectWiFi(true);
}

void loop()
{
    //Flash string (PROGMEM and  (FPSTR), String C/C++ string, const char, char array, string literal are supported
    //in all Firebase and FirebaseJson functions, unless F() macro is not supported.

    if (Firebase.ready() && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0))
    {
        sendDataPrevMillis = millis();
        
        FirebaseJson json;
        json.setDoubleDigits(3);
        json.add("value", count);

        //Serial.printf("Set json... %s\n", Firebase.pushJSON(fbdo, "/json", json) ? "ok" : fbdo.errorReason().c_str());

        //Serial.printf("Get json... %s\n", Firebase.getJSON(fbdo, "/json") ? fbdo.to<FirebaseJson>().raw() : fbdo.errorReason().c_str());

        //FirebaseJson jVal;
        //Serial.printf("Get json ref... %s\n", Firebase.getJSON(fbdo, "/json", &jVal) ? jVal.raw() : fbdo.errorReason().c_str());
        getLocalTime(&timeinfo);
        strftime(timeStringBuff, sizeof(timeStringBuff), "%A, %B %d %Y %H:%M:%S", &timeinfo);
        
        Serial.println(timeStringBuff);
        FirebaseJsonArray arr;
        arr.setFloatDigits(1);
        //arr.setDoubleDigits();
        arr.add(count,timeStringBuff);

        Serial.printf("Set array... %s\n", Firebase.pushArray(fbdo, "/array", arr) ? "ok" : fbdo.errorReason().c_str());

      
        count++;
    }
}
