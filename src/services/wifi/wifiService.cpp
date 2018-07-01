#include "./wifiService.h"

WifiService::WifiService(ConfigService configService)
{
  this->configService = configService;
}

void WifiService::begin(bool isConfigEnabled)
{
  ConfigService service = this->configService;

  // Serial.print("AppServer: ");
  // Serial.println(config.appServer);

  // Serial.print("SSID: ");
  // Serial.println(config.ssid);

  // Serial.print("Password: ");
  // Serial.println(config.password);

  // Serial.print("PlantGrowingStep: ");
  // Serial.println(config.plantGrowingStep);

  if (isConfigEnabled)
  {
    WiFi.softAP("PlantManager_Device");
    ESP8266WebServer server(80);

    bool isConfigSet = false;

    // Serial.println("Waiting for configuration");

    server.on("/", HTTP_PUT, [&server, &service, &isConfigSet]() {
      if (server.hasArg("plain") == false)
      {
        // Serial.println("No body");
        server.send(400);
      }
      else
      {
        // Serial.println("Request send");
        service.setConfiguration(server.arg("plain"));
        server.send(200, "application/json", server.arg("plain"));
        delay(300);
        isConfigSet = true;

        // Configuration config = service.getConfiguration();

        // Serial.print("AppServer: ");
        // Serial.println(config.appServer);

        // Serial.print("SSID: ");
        // Serial.println(config.ssid);

        // Serial.print("Password: ");
        // Serial.println(config.password);

        // Serial.print("PlantGrowingStep: ");
        // Serial.println(config.plantGrowingStep);
      }
    });

    server.begin();

    while (!isConfigSet)
    {
      server.handleClient();
    }

    server.close();
  }

  // Serial.println("Connection to wifi... ");
  // Serial.print("SSID: ");
  // Serial.println(config.ssid.c_str());
  // Serial.println("Password: ");
  // Serial.print(config.password.c_str());
  Configuration config = service.getConfiguration();
  WiFi.mode(WIFI_AP_STA);
  WiFi.enableAP(false);
  WiFi.begin(config.ssid.c_str(), config.password.c_str());

  while (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    WiFi.begin(config.ssid.c_str(), config.password.c_str());
  }
}