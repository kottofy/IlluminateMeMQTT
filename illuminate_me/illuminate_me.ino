#include <AzureIoTHub.h>
#include <AzureIoTProtocol_MQTT.h>
#include <AzureIoTUtility.h>

#include "config.h"

static bool messagePending = false;
//static bool messageSending = true;
static char *connectionString = CONNECTION_STRING;

static int interval = INTERVAL;

void successLED(){
    digitalWrite(BUILT_IN_LED, HIGH);
    delay(500);
    digitalWrite(BUILT_IN_LED, LOW);

    colorWipePixels(255, 0, 0); // Red
    colorWipePixels(0, 255, 0); // Green
    colorWipePixels(0, 0, 255); // Blue

    theatherChasePixels(0, 178, 148);  // turquoise
    theatherChasePixels(50, 20, 90);   // purple
    colorWipePixels(0, 0, 0); 
}

static IOTHUB_CLIENT_LL_HANDLE iotHubClientHandle;
void setup()
{
    pinMode(ARDUINO_PIN_NUMBER, OUTPUT);
    pinMode(BUILT_IN_LED, OUTPUT);

    initSerial();
    initWifi();
    initTime();
    initPixels();

    rainbowCycle(7);
    colorWipePixels(0, 0, 0); 

    iotHubClientHandle = IoTHubClient_LL_CreateFromConnectionString(connectionString, MQTT_Protocol);
    if (iotHubClientHandle == NULL)
    {
        Serial.println("Failed on IoTHubClient_CreateFromConnectionString.");
        colorWipePixels(127, 127, 127); // White      
        while(1);
    }

    IoTHubClient_LL_SetMessageCallback(iotHubClientHandle, receiveMessageCallback, NULL);
    IoTHubClient_LL_SetDeviceMethodCallback(iotHubClientHandle, deviceMethodCallback, NULL);
    IoTHubClient_LL_SetDeviceTwinCallback(iotHubClientHandle, twinCallback, NULL);
}

static int messageCount = 1;
void loop()
{
    if (!messagePending)
        rainbow(10);
    IoTHubClient_LL_DoWork(iotHubClientHandle);
}
