
/*
12/1/2023
Custom Wifi Connecting Library for Esp32 with Arduino environment
by Thai-Son Nguyen
*/

#include <Arduino.h>
#include "WiFi.h"
#include <iostream>
#include <vector>
#include <SD.h>
#pragma once

#define APNAME 0
#define APPASS 1
#define APVALID 2

extern std::vector<std::vector<String>> APs ;


struct CurrentWifiStruct {
    String SSID, password;
    int APID;
};

extern CurrentWifiStruct CurrentWifi;

void findAndConnectWifi() ;