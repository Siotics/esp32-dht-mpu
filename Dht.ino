#include "Dht.h"
#include <DHT.h>
#define DHT_PIN 15
#define DHT_TYPE DHT22

void DhtSetup(DHT &dht)
{
    dht.begin();
}

void DhtRead(DHT &dht, float &temperature, float &humid)
{
    temperature = dht.readTemperature();
    humid = dht.readHumidity();
    if (isnan(temperature) || isnan(humid))
    {
        Serial.println("Can't read DHT");
        return;
    }
}