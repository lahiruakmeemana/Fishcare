#include <OneWire.h>
#include <DallasTemperature.h>
#include <WiFi.h>
#include <FirebaseESP32.h>
#include <time.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

const char* ssid     = "CHAMPIKA";
const char* password = "udt2279826";

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 5.5*3600;
const int   daylightOffset_sec = 0;
struct tm timeinfo;
char timeStringBuff[50];

const int SENSOR_PIN = 4;
OneWire oneWire(SENSOR_PIN);         // setup a oneWire instance
DallasTemperature sensors(&oneWire); // pass oneWire to DallasTemperature library
DeviceAddress insideThermometer = { 0x28, 0x94, 0xE2, 0xDF, 0x02, 0x00, 0x00, 0xFE };
float tempCelsius;

#define uS_TO_S_FACTOR 1000000ULL  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  889       /*ESP32 will go to sleep 15min (-11sec for boot up and send) */
RTC_DATA_ATTR int bootCount = 0;

bool wifi_on(){
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(WiFi.localIP());
  return true;
}
void wifi_off(){
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
}

void sleep(){
  ++bootCount;
  Serial.println("Boot number: " + String(bootCount));

  //Print the wakeup reason for ESP32
  //print_wakeup_reason();

  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  Serial.println("Setup ESP32 to sleep for every " + String(TIME_TO_SLEEP) +
  " Seconds");

  Serial.println("Going to sleep now");
  Serial.flush(); 
  esp_deep_sleep_start();
}

void getTemp(){
  sensors.begin();    
  sensors.setResolution(insideThermometer, 10);
  sensors.requestTemperatures();
  delay(1500);
  tempCelsius = sensors.getTempCByIndex(0);
  
}

void sendfirebase(){
    
    Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);
  
    config.api_key = "AIzaSyCqDbo5x8NMHswaEV7EZpDEWcYc10vSdLk";
    auth.user.email = "lahirua.18@cse.mrt.ac.lk";
    auth.user.password = "fishcare1234";
    config.database_url = "https://water-measures-default-rtdb.asia-southeast1.firebasedatabase.app";
    config.token_status_callback = tokenStatusCallback;
    
    Firebase.begin(&config, &auth);
    //Optional, set AP reconnection in setup()
    Firebase.reconnectWiFi(true);
    delay(3000);
    getLocalTime(&timeinfo);
    strftime(timeStringBuff, sizeof(timeStringBuff), "%A, %B %d %Y %H:%M:%S", &timeinfo);
    Serial.println(tempCelsius);
    Serial.println(timeStringBuff);
    FirebaseJsonArray arr;
    arr.setFloatDigits(2);
    //tempCelsius = 20.5;
    arr.add(tempCelsius,timeStringBuff);
    //Firebase.pushArray(fbdo, "/array", arr);
    Serial.printf("Set array... %s\n", Firebase.pushArray(fbdo, "/array", arr) ? "ok" : fbdo.errorReason().c_str());

}

void setup() {
  Serial.begin(115200); // initialize serial
  delay(1000);
  

  bool res = wifi_on();
  Serial.println("");
  
  if(res){
    Serial.println("WiFi connected.");
  }
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  delay(1500);
  
  getTemp();
  
  sendfirebase();
  wifi_off();
  sleep();
}

void loop() {
  // put your main code here, to run repeatedly:

}
