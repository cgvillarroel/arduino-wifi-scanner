/*
  Pretty WiFi Scanner

  Scans for WiFi networks and formats the output to look pretty.
*/

#include <plogger.h>
#include <SPI.h>
#include <WiFiNINA.h>


#define REFRESH_PERIOD 10

// just for padding, don't worry about getting this wrong
#define MAX_SSID_LENGTH 24

Logger logger(&Serial);
Ansi ansi(&Serial);
String data;

void setup(void) {
  Serial.begin(9600);
  while (!Serial) {
    ;
  }

  logger.setLogLevel(LogLevel::Debug);
  logger.info(F("Serial port connected."));

  if (WiFi.status() == WL_NO_MODULE) {
    logger.fatal(F("No WiFi module detected. Halting."));
    while (true)
      ;
  }

  String firmware_ver = WiFi.firmwareVersion();
  if (firmware_ver < WIFI_FIRMWARE_LATEST_VERSION) {
    logger.warning(F("WiFi firmware is outdated."));
  }

  byte mac[6];
  WiFi.macAddress(mac);
  logger.info(String(F("MAC: ")) + macAddressToString(mac));
}

void loop(void) {
  int ssid_count = listNetworks();
  for (int i = REFRESH_PERIOD; i > 0; --i) {
    logger.info(String(F("Refeshing in ")) + String(i) + String(F("s... ")));
    ansi.previousLine(1);
    delay(1000);
  }
  ansi.previousLine(ssid_count + 3);

}
