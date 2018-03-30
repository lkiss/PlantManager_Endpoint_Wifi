#include <Arduino.h>
#include <SoftwareSerial.h>

#include "./services/services.h"

int readyPin = 14;
bool isWifiReady = false;

ConfigService configService;
JsonService jsonService;
WifiService wifiService;
DataService dataService(configService);

String messageFromSensor;

void setup()
{
    pinMode(readyPin, OUTPUT);
    digitalWrite(readyPin, LOW);

    wifiService.begin();
    Serial.begin(9600);
    Serial.swap();
}

void loop()
{
    digitalWrite(readyPin, HIGH);

    if (Serial.available())
    {
        String sensorId = Serial.readStringUntil('\n');
        sensorId.trim();

        digitalWrite(readyPin, LOW);

        String configString = dataService.getConfiguration(sensorId);
        configService.setConfiguration(jsonService.convertJsonToConfig(configString));

        String plantGrowingStep = dataService.getPlantGrowingStep(sensorId);
        Serial.println(plantGrowingStep);

        while (!Serial.available())
        {
        }

        messageFromSensor.concat(Serial.readStringUntil('\n'));
        Serial.flush();
        
        dataService.sendSensorReadings(messageFromSensor, sensorId);
        Serial.end();
        ESP.deepSleep(0);
    }
}