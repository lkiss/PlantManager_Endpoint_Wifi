#include "./jsonService.h"

Configuration JsonService::convertJsonToConfig(String &configJson)
{
    const size_t bufferSize = JSON_OBJECT_SIZE(1) + 70;
    Configuration configuration = Configuration();
    String jsonMessage;
    DynamicJsonBuffer buffer(bufferSize);

    JsonObject &config = buffer.parseObject(configJson);
    configuration.appServer = config["appServer"].as<char*>();

    buffer.clear();

    return configuration;
}