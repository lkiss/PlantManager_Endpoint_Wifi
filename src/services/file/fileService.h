#ifndef FILE_SERVICE
#define FILE_SERVICE

#include <Arduino.h>
#include "FS.h"

class FileService
{
  public:
    void saveStringToFile(String content, String path);
    void readStringFromFile(String path);
};

#endif