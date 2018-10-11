#include <Arduino.h>
#include <SoftwareSerial.h>

#include "./services/services.h"

int readyPin = 14;
int reConfigPin = 5;
bool isWifiReady = false;

JsonService jsonService;
ConfigService configService(jsonService);
DataService dataService(configService);
WifiService wifiService(configService);
ServerService serverService;

String messageFromSensor;

void setup()
{
    pinMode(readyPin, OUTPUT);
    pinMode(reConfigPin, INPUT);
    digitalWrite(readyPin, LOW);
    Serial.begin(9600);
    if (digitalRead(reConfigPin) == HIGH)
    {
        serverService.start();
    }
    wifiService.connectIfConfigured();

    // Serial.swap();
    Serial.println("Not swapped");
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

        String sensorConfiguration;

        if (configService.isCloudConfigured())
        {
            // String configString = dataService.getConfiguration(sensorId);

            // configService.setConfiguration(configString);

            sensorConfiguration = dataService.getsensorConfiguration(sensorId);
            // Serial.println("Configuration from cloud: ");
        }
        else
        {
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
