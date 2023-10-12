#ifndef DHT_HEADER
#define DHT_HEADER
#include <DHT.h>

void DhtSetup(DHT &dht);

void DhtRead(DHT &dht, float &temperature, float &humid);

#endif