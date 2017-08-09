#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <sys/time.h>
#include <SPI.h>

#ifdef ARDUINO_ARCH_ESP8266
// for ESP8266
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <WiFiUdp.h>
#elif ARDUINO_SAMD_FEATHER_M0
// for Adafruit WINC1500
#include <Adafruit_WINC1500.h>
#include <Adafruit_WINC1500SSLClient.h>
#include <Adafruit_WINC1500Udp.h>
#include <NTPClient.h>
#else
#include <WiFi101.h>
#include <WiFiSSLClient.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#endif
#ifdef ARDUINO_SAMD_FEATHER_M0
// For the Adafruit WINC1500 we need to create our own WiFi instance
// Define the WINC1500 board connections below.
#define WINC_CS   8
#define WINC_IRQ  7
#define WINC_RST  4
#define WINC_EN   2     // or, tie EN to VCC
// Setup the WINC1500 connection with the pins above and the default hardware SPI.
Adafruit_WINC1500 WiFi(WINC_CS, WINC_IRQ, WINC_RST);
#endif

// In the next line we decide each client ssl we'll use.
#ifdef ARDUINO_ARCH_ESP8266
static WiFiClientSecure sslClient; // for ESP8266
#elif ARDUINO_SAMD_FEATHER_M0
static Adafruit_WINC1500SSLClient sslClient; // for Adafruit WINC1500
#else
static WiFiSSLClient sslClient;
#endif

static char *ssid = WIFI_SSID;
static char *pass = WIFI_PASS;

void initSerial()
{
    // Start serial and initialize stdout
    Serial.begin(115200);
    Serial.setDebugOutput(true);
    Serial.println("Serial successfully inited.");
    delay(2000);
}

void initWifi()
{
    // Attempt to connect to Wifi network:
    Serial.printf("Attempting to connect to SSID: %s.\r\n", ssid);

    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED)
    {
        // Get Mac Address and show it.
        // WiFi.macAddress(mac) save the mac address into a six length array, but the endian may be different. The huzzah board should
        // start from mac[0] to mac[5], but some other kinds of board run in the oppsite direction.
        uint8_t mac[6];
        WiFi.macAddress(mac);
        Serial.printf("Your device with MAC address %02x:%02x:%02x:%02x:%02x:%02x connection to %s failed! Waiting 10 seconds to retry.\r\n",
                mac[0], mac[1], mac[2], mac[3], mac[4], mac[5], ssid);
        WiFi.begin(ssid, pass);
        delay(10000);
    }
    Serial.printf("Connected to wifi %s.\r\n", ssid);
}


void initTime() 
{
#if defined(ARDUINO_SAMD_ZERO) || defined(ARDUINO_SAMD_MKR1000) || defined(ARDUINO_SAMD_FEATHER_M0)
#ifdef ARDUINO_SAMD_FEATHER_M0
    Adafruit_WINC1500UDP ntpUdp; // for Adafruit WINC1500
#else
    WiFiUDP ntpUdp;
#endif
    NTPClient ntpClient(ntpUdp);

    ntpClient.begin();

    while (!ntpClient.update()) {
        Serial.println("Fetching NTP epoch time failed! Waiting 5 seconds to retry.");
        delay(5000);
    }

    ntpClient.end();

    unsigned long epochTime = ntpClient.getEpochTime();

    Serial.print("Fetched NTP epoch time is: ");
    Serial.println(epochTime);

    iotHubClient.setEpochTime(epochTime);

#elif ARDUINO_ARCH_ESP8266
    time_t epochTime;

    configTime(0, 0, "pool.ntp.org", "time.nist.gov");

    while (true) {
        epochTime = time(NULL);

        if (epochTime == 0) {
            Serial.println("Fetching NTP epoch time failed! Waiting 2 seconds to retry.");
            delay(2000);
        } else {
            Serial.print("Fetched NTP epoch time is: ");
            Serial.println(epochTime);
            break;
        }
    }
#endif
}
