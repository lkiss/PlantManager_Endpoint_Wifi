#ifndef JSON_SERVICE
#define JSON_SERVICE

#include <ArduinoJson.h>
#include "../config/config.h"
#include "../sensor/sensorReading.h"

class JsonService
{
public:
  Configuration convertJsonToConfig(String &configJson);
};

#endif