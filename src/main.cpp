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
    Serial.setTimeout(2000);
    if (digitalRead(reConfigPin) == HIGH)
    {
        serverService.start();
    }
    wifiService.connectIfConfigured();

    Serial.swap();
    // Serial.println("Not swapped");
    // Serial.flush();

    digitalWrite(statusLedPin, HIGH);
}

void loop()
{
    digitalWrite(readyPin, HIGH);

    if (Serial.available())
    {
        utilities.waitMessage("CONFIG_GET");
        while (!Serial.available())
        {
            yield();
        }

        //  utilities.oscillatePin(statusLedPin, 500, 1);

        String sensorId = Serial.readStringUntil(' ');
        String sensorIndex = Serial.readStringUntil('\n');
        sensorId.trim();
        sensorIndex.trim();

        // Serial.print("SensorId: ");
        // Serial.println(sensorId);

        // Serial.print("Sensor Number: ");
        // Serial.println(sensorNumber);

        // Serial.println("SensorId read");

        digitalWrite(readyPin, LOW);

        String sensorConfiguration;

        if (configService.isCloudConfigured())
        {
            utilities.oscillatePin(statusLedPin, 500, 1);
            sensorConfiguration = dataService.getsensorConfiguration(sensorId, sensorIndex);
        }
        else
        {
            // utilities.oscillatePin(statusLedPin, 500, 3);
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

        utilities.sendMessageAndWait("CONFIG_SUCCESS");

        // Serial.println("Sending plant growing step config");
        Serial.println(sensorConfiguration);

        if (configService.isCloudConfigured())
        {
            utilities.waitMessage("READING_SET");

            while (!Serial.available())
            {
                yield();
            }

            // Serial.println("Before sensor read");
            messageFromSensor.concat(Serial.readStringUntil('\n'));

            dataService.sendSensorReadings(messageFromSensor, sensorId, sensorIndex);
            // utilities.oscillatePin(statusLedPin, 500, 4);
        }

        Serial.flush();
        Serial.end();
        ESP.deepSleep(0);
    }
}
