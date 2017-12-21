#ifndef CONFIG_SERVICE
#define CONFIG_SERVICE

#include <Arduino.h>
#include "config.h"

class ConfigService
{
private:
  static ConfigService *instance;
  Configuration config;

public:
  ConfigService();

  Configuration getConfiguration();
  void setConfiguration(Configuration config);
};

#endif