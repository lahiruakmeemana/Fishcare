#include <OneWire.h>
#include <DallasTemperature.h>
#include <WiFi.h>
#include <FirebaseESP32.h>
#include <time.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

#define uS_TO_S_FACTOR 1000000ULL  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  60       /*1800 Time ESP32 will go to sleep (in seconds) */

RTC_DATA_ATTR int bootCount = 0;

const char* ssid     = "CHAMPIKA";
const char* password = "udt2279826";

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 5.5*3600;
const int   daylightOffset_sec = 0;
struct tm timeinfo;
char timeStringBuff[50];

const int SENSOR_PIN = 4;
OneWire oneWire(SENSOR_PIN);         // setup a oneWire instance
DallasTemperature sensors(&oneWire); // pass oneWire to DallasTemperature library
DeviceAddress insideThermometer = { 0x28, 0x94, 0xE2, 0xDF, 0x02, 0x00, 0x00, 0xFE };

float tempCelsius;    // temperature in Celsius

void print_wakeup_reason(){
  esp_sleep_wakeup_cause_t wakeup_reason;

  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch(wakeup_reason)
  {
    case ESP_SLEEP_WAKEUP_EXT0 : Serial.println("Wakeup caused by external signal using RTC_IO"); break;
    case ESP_SLEEP_WAKEUP_EXT1 : Serial.println("Wakeup caused by external signal using RTC_CNTL"); break;
    case ESP_SLEEP_WAKEUP_TIMER : Serial.println("Wakeup caused by timer"); break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD : Serial.println("Wakeup caused by touchpad"); break;
    case ESP_SLEEP_WAKEUP_ULP : Serial.println("Wakeup caused by ULP program"); break;
    default : Serial.printf("Wakeup was not caused by deep sleep: %d\n",wakeup_reason); break;
  }
}
void sleep(){
  ++bootCount;
  Serial.println("Boot number: " + String(bootCount));

  //Print the wakeup reason for ESP32
  print_wakeup_reason();

  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  Serial.println("Setup ESP32 to sleep for every " + String(TIME_TO_SLEEP) +
  " Seconds");

  Serial.println("Going to sleep now");
  Serial.flush(); 
  esp_deep_sleep_start();
}


void printLocalTime(){
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%d %b %Y %H:%M:%S");
  //return timeinfo;
}
bool wifi_on(){
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
void getTemp(){
  sensors.begin();    
  sensors.setResolution(insideThermometer, 10);
  sensors.requestTemperatures();
  delay(3000);
  tempCelsius = sensors.getTempCByIndex(0);
  
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); // initialize serial
  delay(1000);
  Serial.print("Connecting to ");
  Serial.println(ssid);

  bool res = wifi_on();
  Serial.println("");
  
  if(res){
    Serial.println("WiFi connected.");
  }
  while(!getLocalTime(&timeinfo)){
      configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
      delay(500);
  }
  getTemp();
  //sendfirebase();
  wifi_off();
  sleep();
  
}

void loop() {

}
