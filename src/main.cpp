#include <Arduino.h>

#include "./services/services.h"

ConfigService configService;
JsonService jsonService;
WifiService wifiService;
DataService dataService(configService);
Configuration config;

char rawMessage[1000];
String messageFromSensor;
int i = 0;

void setup()
{
    config = configService.getConfiguration();
    wifiService.begin();
    Serial.begin(9600);
    Serial.setDebugOutput(true);
    Serial.setTimeout(10000);
    Serial.flush();
}

void loop()
{
    if (Serial.available())
    {
        messageFromSensor.concat(Serial.readStringUntil('\n'));

        String sensorId = jsonService.getSensorIdFromJson(messageFromSensor);

        Serial.println(sensorId);
        dataService.sendSensorReadings(messageFromSensor, sensorId);
        Serial.end();
        ESP.deepSleep(config.sleepTime, WAKE_RF_DEFAULT);
    }
}