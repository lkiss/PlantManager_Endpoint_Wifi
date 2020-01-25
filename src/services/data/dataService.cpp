#include "dataService.h"

DataService::DataService(ConfigService configService)
{
    this->configurationService = configService;
}

int DataService::sendSensorReadings(String &sensorReadingsJson, String &deviceId, String &sensorIndex)
{
    Configuration config = this->configurationService.getConfiguration();
    String requestUrl = config.appServer + "/readings/" + deviceId + "/" + sensorIndex + "/iot";

    httpClient.begin(requestUrl);
    httpClient.addHeader("Content-Type", "application/json");

    int httpStatusCode = httpClient.POST(sensorReadingsJson);

    // if (httpStatusCode != HTTP_CODE_CREATED)
    // {
    //     Serial.println("RequestUrl:");
    //     Serial.println(requestUrl);
    //     Serial.println(httpStatusCode);
    // }

    httpClient.end();

    return httpStatusCode;
}

String DataService::getConfiguration(String &deviceId, String &sensorIndex)
{
    Configuration config = this->configurationService.getConfiguration();
    String configPayload = "";

    String requestUrl = config.appServer + "/devices/" + deviceId + "/" + sensorIndex + "/iot/configuration";

    httpClient.begin(requestUrl);

    int httpStatusCode = httpClient.GET();

    if (httpStatusCode == HTTP_CODE_OK)
    {
        configPayload = httpClient.getString();
    }
    // else
    // {
    //     Serial.println("RequestUrl:");
    //     Serial.println(requestUrl);
    //     Serial.println(httpStatusCode);
    // }

    httpClient.end();

    return configPayload;
}

String DataService::getsensorConfiguration(String &deviceId, String &sensorNumber)
{
    Configuration config = this->configurationService.getConfiguration();
    String sensorConfiguration = "";

    String requestUrl = config.appServer + "/devices/" + deviceId + "/" + sensorNumber + "/iot/configuration";

    // Serial.print("Request URL");
    // Serial.println(requestUrl);

    httpClient.begin(requestUrl);
    int httpStatusCode = httpClient.GET();
    if (httpStatusCode == HTTP_CODE_OK)
    {
        sensorConfiguration = httpClient.getString();
    }
    // else
    // {
    //     Serial.println("RequestUrl:");
    //     Serial.println(requestUrl);
    //     Serial.println("StatusCode");
    //     Serial.println(httpStatusCode);
    // }

    httpClient.end();
    // Serial.println("sensorConfiguration");
    // Serial.println(sensorConfiguration);
    return sensorConfiguration;
}