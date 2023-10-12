#include "secrets.h"
#include "AdaFruit.h"
#include "Dht.h"
#include <WiFiClientSecure.h>
#include <DHT.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <WiFi.h>
#include <PubSubClient.h>

const char *mqtt_server = AWS_IOT_ENDPOINT;
const int mqtt_port = 8883;
// const char* mqtt_username = "XXXXXXXX";
// const char* mqtt_password = "XXXXXXXX";
const char *mqtt_topic = AWS_IOT_TOPIC;
float temperature, humid;

Adafruit_MPU6050 mpu;
WiFiClientSecure espClient;
PubSubClient client(espClient);
DHT dht(15, DHT22);

void setup()
{
    Serial.begin(115200);
    Serial.print("Connecting to WiFi");
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(100);
        Serial.print(".");
    }
    Serial.println(" Connected!");
    espClient.setCACert(AWS_CERT_CA);
    espClient.setCertificate(AWS_CERT_CRT);
    espClient.setPrivateKey(AWS_CERT_PRIVATE);
    client.setServer(mqtt_server, mqtt_port);
    /*scan_mpu();*/
    AdafruitSetup(mpu);
    DhtSetup(dht);
}

void reconnect_mqtt()
{
    while (!client.connected())
    {
        Serial.print("Connecting to MQTT Broker...");
        if (client.connect("ESP32Client"))
        {
            Serial.println("connected");
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" retrying in 5 seconds");
            delay(5000);
        }
    }
}

void loop()
{
    /*
    if (!client.connected())
    {
        reconnect_mqtt();
    }

    */

    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    Serial.print("Acceleration X: ");
    Serial.print(a.acceleration.x);
    Serial.print(", Y: ");
    Serial.print(a.acceleration.y);
    Serial.print(", Z: ");
    Serial.print(a.acceleration.z);
    Serial.println(" m/s^2");

    Serial.print("Rotation X: ");
    Serial.print(g.gyro.x);
    Serial.print(", Y: ");
    Serial.print(g.gyro.y);
    Serial.print(", Z: ");
    Serial.print(g.gyro.z);
    Serial.println(" rad/s");
    DhtRead(dht, temperature, humid);

    /*
        String payload = "{\"suhu\":" + String(random(10, 50)) + ", \"kelembaban\":" + String(random(20, 80)) + "}";

    */
    String payload = "{\"suhu\":" + String(temperature) + ", \"kelembaban\":" + String(humid) + "}";
    char msgBuffer[100];
    payload.toCharArray(msgBuffer, 100);

    Serial.print("Publishing message: ");
    Serial.println(msgBuffer);
    /*

    client.publish(mqtt_topic, msgBuffer);

    client.loop();
    */
    delay(1000);
}