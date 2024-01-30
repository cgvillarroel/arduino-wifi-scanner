String macAddressToString(byte *mac) {
  String addr;
  for (int i = 5; i >= 0; i--) {
    if (mac[i] < 16) {
      addr += 0;
    }
    addr += String(mac[i], HEX);
    if (i > 0) {
      addr += F(":");
    }
  }

  return addr;
}

/// Returns the number of networks found
int listNetworks(void) {
  (void)ansi.eraseDisplay(EraseMode::After);
  (void)logger.info(F("Scanning for networks..."));
  int ssid_count = WiFi.scanNetworks();
  if (ssid_count == -1) {
    (void)logger.fatal(F("Could not find any networks"));
    while (true)
      ;
  }

  (void)logger.logHeader(LogLevel::Info);
  (void)Serial.print(F("Number of available networks: "));
  (void)Serial.println(ssid_count);
  (void)logger.info(F("=== AVAILABLE NETWORKS ==="));

  for (int i = 0; i < ssid_count; ++i) {
    (void)logger.logHeader(LogLevel::Info);
    String ssid = WiFi.SSID(i);
    (void)Serial.print(i);
    (void)Serial.print(F(": "));
    (void)Serial.print(ssid);

    // ssid padding
    for (int j = ssid.length(); j < MAX_SSID_LENGTH; ++j) {
      (void)Serial.print(F(" "));
    };

    (void)Serial.print(F("\tSignal: "));
    (void)Serial.print(WiFi.RSSI(i));
    (void)Serial.print(F(" dBm\t\tEncryption: "));
    printEncryptionType(WiFi.encryptionType(i));
  }

  return ssid_count;
}

void printEncryptionType(uint8_t type) {
  switch (type) {
  case ENC_TYPE_WEP:
    Serial.println(F("WEP"));
		break;

  case ENC_TYPE_TKIP:
    Serial.println(F("WPA"));
		break;

  case ENC_TYPE_CCMP:
    Serial.println(F("WPA2"));
		break;

  case ENC_TYPE_NONE:
    Serial.println(F("None"));
		break;

  case ENC_TYPE_AUTO:
    Serial.println(F("Auto"));
		break;

  case ENC_TYPE_UNKNOWN:
  default:
    Serial.println(F("Unknown"));
  }
}
