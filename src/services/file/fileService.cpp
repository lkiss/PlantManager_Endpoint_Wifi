#include "./fileService.h"

void FileService::saveStringToFile(String content, String path)
{
    SPIFFS.begin();
    File configFile = SPIFFS.open(path, "a");

    if (!configFile)
    {
        Serial.println("file open failed");
    }
    else
    {
        configFile.print(content);
    }

    configFile.close();
    SPIFFS.end();
}

void FileService::readStringFromFile(String path)
{
    SPIFFS.begin();
    File configFile = SPIFFS.open(path, "r");

    if (!configFile)
    {
        Serial.println("file open failed");
    }
    else
    {
        configFile.readStringUntil('\n');
    }

    configFile.close();
    SPIFFS.end();
}