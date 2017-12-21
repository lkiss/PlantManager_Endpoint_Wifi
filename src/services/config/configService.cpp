#include "configService.h"

ConfigService::ConfigService()
{
  // this->config.sleepTime = UINT32_MAX;
  this->config.sleepTime = 30e6;
  this->config.appServer = "http://192.168.1.101:8080/api/sensor";
}

Configuration ConfigService::getConfiguration()
{
  return this->config;
}

void ConfigService::setConfiguration(Configuration config)
{
  this->config = config;
}