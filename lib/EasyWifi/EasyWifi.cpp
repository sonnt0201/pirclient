/*
12/1/2023
Custom Wifi Connecting Library for Esp32 with Arduino environment
by Thai-Son Nguyen
*/

#include "EasyWifi.hpp"

CurrentWifiStruct CurrentWifi;



void findAndConnectWifi()
{
    
    // Init CurrentWifi value
    CurrentWifi.SSID = "";
    CurrentWifi.password = "";
    int maxStrength = -1000;
    Serial.println("Scan start");

    // WiFi.scanNetworks will return the number of networks found
    int n = WiFi.scanNetworks();
    Serial.println("Scan done");
    if (n == 0)
    {
        Serial.println("no networks found");
    }
    else
    {
        Serial.print(n);

        // Find best network to connect
        Serial.println(" networks found, connecting ...");
        for (int i = 0; i < n; ++i)
        {
            // Print SSID and RSSI for each network found
            String ssid = WiFi.SSID(i);
            int strength = WiFi.RSSI(i);

            for (int j = 0; j < APs.size(); j++)
            {
                std::vector<String> AP = APs[j];

                if (AP[APVALID] == "1" && AP[APNAME] == ssid && strength > maxStrength)
                {
                    CurrentWifi.SSID = ssid;
                    CurrentWifi.password = AP[APPASS];
                    CurrentWifi.APID = j;
                    maxStrength = strength;
                }
            }
        }
    }

    // Connect the best network

    // Check if having found viable Wifi
    if (CurrentWifi.SSID == "") {
        Serial.println("Cannot find Wifi to connect, preparing to retry ...");
        delay(3000);
        findAndConnectWifi();
    }
        

    // Start connecting
    Serial.println("Connecting to: " + CurrentWifi.SSID);
    WiFi.begin(CurrentWifi.SSID, CurrentWifi.password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(250);
        Serial.print(".");

        if (WiFi.status() == WL_CONNECT_FAILED)
        {
            // Set invalid to the wrong AP
            APs[CurrentWifi.APID][APVALID] = "0";

            // notify
            Serial.println("");
            Serial.println("Connection failed. Incorrect password?");
            // Handle the incorrect password scenario here
            findAndConnectWifi();
        }
    }
    Serial.println("\nConnected to: " + CurrentWifi.SSID);
    
}