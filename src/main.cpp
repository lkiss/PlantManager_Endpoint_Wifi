#include <Arduino.h>
#include <SoftwareSerial.h>

#include "./services/services.h"
#include "./utility/utility.h"

int readyPin = 14;
int reConfigPin = 5;
int statusLedPin = 2;

JsonService jsonService;
ConfigService configService(jsonService);
DataService dataService(configService);
WifiService wifiService(configService);
ServerService serverService;

Utility utilities;

String messageFromSensor;

void setup()
{
    pinMode(statusLedPin, OUTPUT);
    pinMode(readyPin, OUTPUT);
    pinMode(reConfigPin, INPUT);
    digitalWrite(readyPin, LOW);
    Serial.begin(9600);
    if (digitalRead(reConfigPin) == HIGH)
    {
        serverService.start();
    }
    wifiService.connectIfConfigured();

    Serial.swap();
    // Serial.println("Not swapped");

    digitalWrite(statusLedPin, HIGH);
}

void loop()
{
    digitalWrite(readyPin, HIGH);

    if (Serial.available())
    {
        utilities.oscillatePin(statusLedPin, 500, 1);
        String sensorId = Serial.readStringUntil(' ');
        String sensorNumber = Serial.readStringUntil('\n');
        sensorId.trim();
        sensorNumber.trim();

        // Serial.print("SensorId: ");
        // Serial.println(sensorId);

        // Serial.print("Sensor Number: ");
        // Serial.println(sensorNumber);

        // Serial.println("SensorId read");

        digitalWrite(readyPin, LOW);

        String sensorConfiguration;

        if (configService.isCloudConfigured())
        {
            utilities.oscillatePin(statusLedPin, 500, 2);
            sensorConfiguration = dataService.getsensorConfiguration(sensorId, sensorNumber);
        }
        else
        {
            utilities.oscillatePin(statusLedPin, 500, 3);
            // Serial.println("Configuration from memory: ");
            // Serial.println(configService.getConfiguration().sensorConfiguration);

            Configuration config = configService.getConfiguration();

            // Serial.println(config.sensorConfiguration);
            // Serial.println(config.appServer);
            // Serial.println(config.ssid);
            // Serial.println(config.password);

            sensorConfiguration = config.sensorConfiguration;
            sensorConfiguration.replace("'", "\"");
        }

        // Serial.println("Sending plant growing step config");
        Serial.println(sensorConfiguration);

        if (configService.isCloudConfigured())
        {
            while (!Serial.available())
            {
                yield();
            }

            // Serial.println("Before sensor read");
            messageFromSensor.concat(Serial.readStringUntil('\n'));

            dataService.sendSensorReadings(messageFromSensor, sensorId, sensorNumber);
            utilities.oscillatePin(statusLedPin, 500, 4);
        }

        Serial.flush();
        Serial.end();
        ESP.deepSleep(0);
    }
}
