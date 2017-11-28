#include <Arduino.h>

#include "./services/services.h"

ConfigService configService;
WifiService wifiService;
DataService dataService(configService);

uint32_t sleepTime = 1000000L * 60L * 15L;

void setup()
{
    Serial.setTimeout(2000);
    wifiService.begin();
}

void loop()
{
    Serial.begin(9600);
    while(Serial.available() == 0){
        delay(2000);
        Serial.print(1);
    }
    
    String message = Serial.readStringUntil('\n');
    message += "}";
    dataService.sendSensorReadings(message);
    Serial.end();
    ESP.deepSleep(sleepTime, WAKE_RF_DEFAULT);
}