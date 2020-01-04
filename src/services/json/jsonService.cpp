#include "./jsonService.h"

Configuration JsonService::convertJsonToConfig(String &configJson)
{
    const size_t bufferSize = 1024;
    Configuration configuration = Configuration();
    StaticJsonDocument<bufferSize> document;

    // Serial.println(configJson);
    // Serial.println("Before jsonParse");
    // Serial.println("Jsonmemory usage: ");
    // Serial.println(document.memoryUsage());

    auto error = deserializeJson(document, configJson);
    if (error)
    {
        Serial.print(F("deserializeJson() failed with code "));
        Serial.println(error.c_str());
        return configuration;
    }

    // Serial.println("Assign values from json");
    // Serial.println(config["sensorConfiguration"].as<char *>());

    configuration.sensorConfiguration = document["sc"].as<String>();
    configuration.appServer = document["appserv"].as<String>();
    configuration.ssid = document["ssid"].as<String>();
    configuration.password = document["pswd"].as<String>();

    document.clear();

    // Serial.println("After jsonParse");
    // Serial.println("sensorConfiguration from config: ");
    // Serial.println(configuration.sensorConfiguration);
    // Serial.println(config["sensorConfiguration"].as<String>());

    return configuration;
}