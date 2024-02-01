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
  (void)logger.infoLine(F("Scanning for networks..."));
  int ssid_count = WiFi.scanNetworks();
  if (ssid_count == -1) {
    (void)logger.fatalLine(F("Could not find any networks"));
    while (true)
      ;
  }

  (void)logger.info(F("Number of available networks: "));
  (void)logger.infoLine(ssid_count);
  (void)logger.infoLine(F("=== AVAILABLE NETWORKS ==="));

  for (int i = 0; i < ssid_count; ++i) {
    String ssid = WiFi.SSID(i);
    (void)logger.info(String(i));
    (void)logger.info(F(": "));
    (void)logger.info(ssid);

    // ssid padding
    for (int j = ssid.length(); j < MAX_SSID_LENGTH; ++j) {
      (void)logger.info(F(" "));
    };

    (void)logger.info(F("\tSignal: "));
    (void)logger.info(String(WiFi.RSSI(i)));
    (void)logger.info(F(" dBm\t\tEncryption: "));
    logEncrypetionType(WiFi.encryptionType(i));
  }

  return ssid_count;
}

void logEncrypetionType(uint8_t type) {
  switch (type) {
  case ENC_TYPE_WEP:
    logger.infoLine(F("WEP"));
    break;

  case ENC_TYPE_TKIP:
    logger.infoLine(F("WPA"));
    break;

  case ENC_TYPE_CCMP:
    logger.infoLine(F("WPA2"));
    break;

  case ENC_TYPE_NONE:
    logger.infoLine(F("None"));
    break;

  case ENC_TYPE_AUTO:
    logger.infoLine(F("Auto"));
    break;

  case ENC_TYPE_UNKNOWN:
  default:
    logger.infoLine(F("Unknown"));
  }
}
