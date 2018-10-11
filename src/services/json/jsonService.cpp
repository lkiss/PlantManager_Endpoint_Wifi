#include "./jsonService.h"

Configuration JsonService::convertJsonToConfig(String &configJson)
{
    const size_t bufferSize = 2 * JSON_OBJECT_SIZE(4) + 210;
    Configuration configuration = Configuration();
    String jsonMessage;
    DynamicJsonBuffer buffer(bufferSize);

    // Serial.println(configJson);
    // Serial.println("Before jsonParse");
    JsonObject &config = buffer.parseObject(configJson);
    if (config.success())
    {
        // Serial.println("Assign values from json");
        // Serial.println(config["sensorConfiguration"].as<char *>());

        configuration.sensorConfiguration = config["sensorConfiguration"].as<String>();
        configuration.appServer = config["appServer"].as<String>();
        configuration.ssid = config["ssid"].as<String>();
        configuration.password = config["password"].as<String>();

        buffer.clear();
    }

    // Serial.println("After jsonParse");
    // Serial.println("sensorConfiguration from config: ");
    // Serial.println(configuration.sensorConfiguration);
    // Serial.println(config["sensorConfiguration"].as<String>());

    return configuration;
}