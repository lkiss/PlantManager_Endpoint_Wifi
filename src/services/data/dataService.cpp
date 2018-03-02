#include "dataService.h"

DataService::DataService(ConfigService configService)
{
    this->configurationService = configService;
}

int DataService::sendSensorReadings(String sensorReadingsJson, String sensorId)
{
    Configuration config = this->configurationService.getConfiguration();
    String requestUrl = config.appServer + "/" + sensorId + "/reading";

    httpClient.begin(requestUrl);
    httpClient.addHeader("Content-Type", "application/json");

    int httpStatusCode = httpClient.POST(sensorReadingsJson);

    httpClient.end();

    return httpStatusCode;
}

String DataService::getConfiguration(String sensorId)
{
    Configuration config = this->configurationService.getConfiguration();
    String configPayload = "";

    String requestUrl = config.appServer + "/" + sensorId + "/configuration";

    httpClient.begin(requestUrl);

    int httpStatusCode = httpClient.GET();

    if (httpStatusCode == HTTP_CODE_OK)
    {
        configPayload = httpClient.getString();
    }

    httpClient.end();

    return configPayload;
}

String DataService::getPlantGrowingStep(String sensorId)
{
    Configuration config = this->configurationService.getConfiguration();
    String plantGrowingStep = "";

    String requestUrl = config.appServer + "/" + sensorId + "/currentplantgrowingstep";

    httpClient.begin(requestUrl);

    int httpStatusCode = httpClient.GET();

    if (httpStatusCode == HTTP_CODE_OK)
    {
        plantGrowingStep = httpClient.getString();
    }

    httpClient.end();

    return plantGrowingStep;
}