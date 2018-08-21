#include "./wifiService.h"

WifiService::WifiService(ConfigService configService)
{
  this->configService = configService;
}

void WifiService::connectToWifiNetwork()
{
  ConfigService configService = this->configService;

  Configuration config = configService.getConfiguration();
  WiFi.begin(config.ssid.c_str(), config.password.c_str());

  while (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    WiFi.begin(config.ssid.c_str(), config.password.c_str());
  }
}