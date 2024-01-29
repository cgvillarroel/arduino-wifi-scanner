String macAddressToString(byte *mac) {
  String addr;
  for (int i = 5; i >= 0; i--) {
    if (mac[i] < 16) {
      addr += String(0);
    }
    addr += String(mac[i], HEX);
    if (i > 0) {
      addr += String(":");
    }
  }

  return addr;
}

/// Returns the number of networks found
int listNetworks(void) {
  ansi.eraseDisplay(EraseMode::After);
  logger.info(F("Scanning for networks..."));
  int ssid_count = WiFi.scanNetworks();
  if (ssid_count == -1) {
    logger.fatal(F("Could not find any networks"));
    while (true)
      ;
  }

  logger.info(String(F("Number of available networks: ")) + String(ssid_count));
  logger.info(F("=== AVAILABLE NETWORKS ==="));

  for (int i = 0; i < ssid_count; ++i) {
    String ssid = WiFi.SSID(i);
    String details = String(i)
                     + String(F(": "))
                     + ssid;

		// ssid padding
    for (int j = ssid.length(); j < MAX_SSID_LENGTH; ++j) {
      details += String(" ");
    };

    details += String(F("\tSignal: "))
               + WiFi.RSSI(i)
               + String(F(" dBm\t\tEncryption: "))
               + encryptionTypeToString(i);

    logger.info(details);
  }

	return ssid_count;
}

String encryptionTypeToString(int netId) {
  switch (WiFi.encryptionType(netId)) {
    case ENC_TYPE_WEP:
      return String(F("WEP"));

    case ENC_TYPE_TKIP:
      return String(F("WPA"));

    case ENC_TYPE_CCMP:
      return String(F("WPA2"));

    case ENC_TYPE_NONE:
      return String(F("None"));

    case ENC_TYPE_AUTO:
      return String(F("Auto"));

    case ENC_TYPE_UNKNOWN:

    default:
      return String(F("Unknown"));
  }
}
