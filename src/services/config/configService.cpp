#include "configService.h"

ConfigService::ConfigService()
{
  this->config.appServer = "http://192.168.1.101/plantmanager/api/sensor";
}

Configuration ConfigService::getConfiguration()
{
  return this->config;
}

void ConfigService::setConfiguration(Configuration config)
{
  this->config = config;
}