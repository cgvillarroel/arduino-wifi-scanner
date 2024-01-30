/*
  Pretty WiFi Scanner

  Scans for WiFi networks and formats the output to look pretty.
*/

#include <SPI.h>
#include <WiFiNINA.h>
#include <plogger.h>

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
  (void)logger.info(F("Serial port connected."));

  if (WiFi.status() == WL_NO_MODULE) {
    (void)logger.fatal(F("No WiFi module detected. Halting."));
    while (true)
      ;
  }

  String firmware_ver = WiFi.firmwareVersion();
  if (firmware_ver < WIFI_FIRMWARE_LATEST_VERSION) {
    (void)logger.warning(F("WiFi firmware is outdated."));
  }

  byte mac[6];
  (void)WiFi.macAddress(mac);
  (void)logger.logHeader(LogLevel::Info);
  (void)Serial.print(F("MAC: "));
  (void)Serial.println(macAddressToString(mac));
}

void loop(void) {
  int ssid_count = listNetworks();
  for (int i = REFRESH_PERIOD; i > 0; --i) {
    (void)logger.logHeader(LogLevel::Info);
    (void)Serial.print(F("Refreshing in "));
    (void)Serial.print(i);
    (void)Serial.println(F("s... "));
    (void)ansi.previousLine(1);
    delay(1000);
  }
  (void)ansi.previousLine(ssid_count + 3);
}
