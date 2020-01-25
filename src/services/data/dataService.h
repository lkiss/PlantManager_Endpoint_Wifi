#ifndef DATA_SERVICE
#define DATA_SERVICE

#include "../config/configService.h"

#include <Arduino.h>
#include <ESP8266HTTPClient.h>

class DataService
{
private:
  HTTPClient httpClient;
  ConfigService configurationService;

public:
  DataService(ConfigService configService);
  int sendSensorReadings(String &sensorReadingsJson, String &deviceId, String &sensorNumber);
  String getConfiguration(String &deviceId, String &sensorNumber);
  String getsensorConfiguration(String &deviceId, String &sensorNumber);
};

#endif