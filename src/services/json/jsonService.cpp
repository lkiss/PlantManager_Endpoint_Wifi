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
        // Serial.println(config["plantGrowingStep"].as<char *>());

        configuration.plantGrowingStep = config["plantGrowingStep"].as<char *>();
        configuration.appServer = config["appServer"].as<char *>();
        configuration.ssid = config["ssid"].as<char *>();
        configuration.password = config["password"].as<char *>();

        buffer.clear();
    }

    // Serial.println("After jsonParse");
    // Serial.println("PlantGrowingStep from config: ");
    // Serial.println(configuration.plantGrowingStep);
    // Serial.println(config["plantGrowingStep"].as<char *>());

    return configuration;
}