#ifndef WIFIHELPERS_H
#define WIFIHELPERS_H

#include <ESP8266WiFi.h>

const char* wifiStatusDescription(wl_status_t status);
const char* wifiDisconnectReasonDescription(WiFiDisconnectReason reason);

#endif // WIFIHELPERS_H