 ///********************** UPDATE THESE **********************///
#define WIFI_SSID           "YourSSID"      // your network SSID (name)
#define WIFI_PASS           "YourPassword"  // your network password (use for WPA, or use as key for WEP)
#define CONNECTION_STRING   "YourDeviceConnectionString"    //your device connection string
///*********************************************************///

#define BUILT_IN_LED LED_BUILTIN

//For IoT Hub
#define MESSAGE_MAX_LEN 256     //
#define INTERVAL 2000           // Interval time(ms) for sending message to IoT Hub

//For NeoPixels
#define NUMBER_OF_PIXELS_IN_STRIP 12
#define ARDUINO_PIN_NUMBER        13
#define PIXEL_TYPE                NEO_GRB + NEO_KHZ800

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)

