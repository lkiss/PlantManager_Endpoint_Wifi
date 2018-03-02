#include <Arduino.h>
#include <SoftwareSerial.h>

#include "./services/services.h"

int receivePin = 4;
int transmitPin = 5;
int readyPin = 14;

SoftwareSerial espSerial(receivePin, transmitPin);

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
    Serial.setTimeout(10000);
    Serial.flush();
    digitalWrite(readyPin, HIGH);
}

void loop()
{
    if (Serial.available())
    {
        digitalWrite(readyPin, LOW);
        String sensorId = Serial.readStringUntil('\n');
        sensorId.trim();
        String configString = dataService.getConfiguration(sensorId);
        configService.setConfiguration(jsonService.convertJsonToConfig(configString));

        String plantGrowingStep = dataService.getPlantGrowingStep(sensorId);

        Serial.println(plantGrowingStep);
        Serial.flush();

        while (!Serial.available())
        {
            delay(100);
        }

        messageFromSensor.concat(Serial.readStringUntil('\n'));

        dataService.sendSensorReadings(messageFromSensor, sensorId);
        Serial.println("Done");
    }
}