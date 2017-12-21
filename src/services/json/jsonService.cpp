#include "./jsonService.h"

String JsonService::getSensorIdFromJson(String sensorReadingJson){
    DynamicJsonBuffer jsonBuffer(350);

    JsonObject& root = jsonBuffer.parseObject(sensorReadingJson);
    return root["sensor"]["sensorId"];
}

String JsonService::convertConfigToJson(Configuration configuration)
{
    String jsonMessage;
    DynamicJsonBuffer jsonBuffer(250);

    JsonObject &config = jsonBuffer.createObject();

    config.printTo(jsonMessage);

    return jsonMessage;
}

Configuration JsonService::convertJsonToConfig(String configJson)
{
    Configuration configuration = Configuration();
    String jsonMessage;
    DynamicJsonBuffer buffer(200);

    JsonObject &config = buffer.parseObject(configJson);
    

    return configuration;
}