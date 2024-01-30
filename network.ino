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

  (void)logger.info(String(F("Number of available networks: ")) +
                    String(ssid_count));
  (void)logger.info(F("=== AVAILABLE NETWORKS ==="));

  for (int i = 0; i < ssid_count; ++i) {
    String ssid = WiFi.SSID(i);
    String details = String(i) + F(": ") + ssid;

    // ssid padding
    for (int j = ssid.length(); j < MAX_SSID_LENGTH; ++j) {
      details += F(" ");
    };

    details += String(F("\tSignal: ")) + WiFi.RSSI(i) +
               F(" dBm\t\tEncryption: ") + encryptionTypeToString(i);

    (void)logger.info(details);
  }

  return ssid_count;
}

String encryptionTypeToString(int netId) {
  switch (WiFi.encryptionType(netId)) {
  case ENC_TYPE_WEP:
    return F("WEP");

  case ENC_TYPE_TKIP:
    return F("WPA");

  case ENC_TYPE_CCMP:
    return F("WPA2");

  case ENC_TYPE_NONE:
    return F("None");

  case ENC_TYPE_AUTO:
    return F("Auto");

  case ENC_TYPE_UNKNOWN:

  default:
    return F("Unknown");
  }
}
