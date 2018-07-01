#include <Arduino.h>
#include <SoftwareSerial.h>

#include "./services/services.h"

int readyPin = 14;
int configPin = 5;
bool isWifiReady = false;

JsonService jsonService;
ConfigService configService(jsonService);
DataService dataService(configService);
WifiService wifiService(configService);

String messageFromSensor;

void setup()
{
    pinMode(readyPin, OUTPUT);
    pinMode(configPin, INPUT);
    digitalWrite(readyPin, LOW);
    Serial.begin(9600);
    wifiService.begin(digitalRead(configPin));

    // Serial.println(digitalRead(configPin));

    //Serial.swap();
}

void loop()
{
    digitalWrite(readyPin, HIGH);

    if (Serial.available())
    {
        String sensorId = Serial.readStringUntil('\n');
        sensorId.trim();

        // Serial.println("SensorId read");

        digitalWrite(readyPin, LOW);

        String plantGrowingStep;

        if (configService.getConfiguration().appServer != "")
        {
            String configString = dataService.getConfiguration(sensorId);

            configService.setConfiguration(configString);

            plantGrowingStep = dataService.getPlantGrowingStep(sensorId);
            // Serial.println("Configuration from cloud: ");
        }
        else
        {
            // Serial.println("Configuration from memory: ");
            // Serial.println(configService.getConfiguration().plantGrowingStep);
            Configuration config = configService.getConfiguration();
            // Serial.println(config.plantGrowingStep);
            // Serial.println(config.appServer);
            // Serial.println(config.ssid);
            // Serial.println(config.password);
            plantGrowingStep = config.plantGrowingStep;
            plantGrowingStep.replace("'", "\"");
        }

        // Serial.println("Sending plant growing step config");
        Serial.println(plantGrowingStep);

        if (configService.getConfiguration().appServer != "")
        {
            while (!Serial.available())
            {
            }

            // Serial.println("Before sensor read");
            messageFromSensor.concat(Serial.readStringUntil('\n'));

            dataService.sendSensorReadings(messageFromSensor, sensorId);
        }

        Serial.flush();
        Serial.end();
        ESP.deepSleep(0);
    }
}
