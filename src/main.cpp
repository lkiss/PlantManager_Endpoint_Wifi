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
    espSerial.begin(9600);
    espSerial.setTimeout(10000);
    espSerial.flush();
}

void loop()
{
    delay(1000);
    digitalWrite(readyPin, HIGH);
    if (espSerial.available() > 0)
    {
        digitalWrite(readyPin, LOW);
        String sensorId = espSerial.readStringUntil('\n');
        sensorId.trim();

        String configString = dataService.getConfiguration(sensorId);
        configService.setConfiguration(jsonService.convertJsonToConfig(configString));

        String plantGrowingStep = dataService.getPlantGrowingStep(sensorId);

        espSerial.println(plantGrowingStep);
        espSerial.flush();

        while (espSerial.available() == 0)
        {
            delay(100);
        }

        messageFromSensor.concat(espSerial.readStringUntil('\n'));

        dataService.sendSensorReadings(messageFromSensor, sensorId);
        espSerial.println("Done");
    }
}