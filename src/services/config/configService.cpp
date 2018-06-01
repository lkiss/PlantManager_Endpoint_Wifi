#include "configService.h"


ConfigService::ConfigService()
{
  this->config.appServer = "http://plantmanagerweb.azurewebsites.net/api/sensor";
}

Configuration ConfigService::getConfiguration()
{
  return this->config;
}

void ConfigService::setConfiguration(Configuration config)
{
  this->config = config;
}