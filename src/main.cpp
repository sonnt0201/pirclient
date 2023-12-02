#include <Arduino.h>
#include "WiFi.h"

#include <vector>
#include <EasyWifi.hpp>

void setup()
{
  Serial.begin(9600);
  WiFi.mode(WIFI_AP_STA);

  findAndConnectWifi();
}

void loop()
{

  // Wait a bit before scanning again
  // delay(5000);
}
