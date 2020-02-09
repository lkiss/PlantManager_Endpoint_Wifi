#include "./utility.h"

Utility::Utility() {}

void Utility::oscillatePin(uint8_t pinNumber, int frequencyInMilliseconds, uint8_t repetitions)
{
    for (uint8_t i = 0; i < repetitions; i++)
    {
        digitalWrite(pinNumber, LOW);
        delay(frequencyInMilliseconds);
        digitalWrite(pinNumber, HIGH);
        delay(frequencyInMilliseconds);
        yield();
    }
}

void Utility::sendMessageAndWait(String message)
{
    char buffer[100];
    int attempts = 0;
    int maximumAttempts = 10;
    String response;
    Serial.println(message);
    Serial.flush();
    while (true)
    {
        while (!Serial.available())
        {
            Serial.read();
            yield();
        }
        attempts++;

        delay(100);

        Serial.readBytes(buffer, 100);

        for (int i = 0; i < 100; i++)
        {
            if (buffer[i] == '-')
            {
                while (Serial.read() != '-')
                {
                    response += buffer[i];
                    break;
                }
            }
        }

        response.trim();

        // Serial.print(response);
        // Serial.flush();
        if (response == "OK")
        {
            break;
        }
        yield();
    }

    return;
}

void Utility::waitMessage(String message)
{
    char buffer[100];
    String response;
    while (true)
    {
        while (!Serial.available())
        {
            Serial.read();
            yield();
        }

        delay(100);

        Serial.readBytes(buffer, 100);

        for (int i = 0; i < 100; i++)
        {
            if (buffer[i] == '-')
            {
                Serial.read();
                while (Serial.read() != '-')
                {
                    response += buffer[i];
                    break;
                }
            }
            break;
        }

        response.trim();
        // Serial.println(response);
        // Serial.flush();
        if (response == message)
        {
            Serial.println("OK");
            Serial.flush();
            break;
        }
        yield();
    }

    return;
}