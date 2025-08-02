#include <time.h>
#include "my_library.h"
#include <WiFiNINA.h>
#include <Wire.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"

#define I2C_ADDRESS 0x3C
SSD1306AsciiWire oled;

int addTwoInts(int a, int b)
{
  return a + b;
};

void startOLEDnano33IoT_Ascii(void){
  //Arduino Nano 33 IoT SDA->A4, SCL->A5
  Wire.begin(); //Arduino Nano 33 ioT
  oled.begin(&Adafruit128x64, I2C_ADDRESS, -1);
  oled.setFont(Adafruit5x7);
}

void displayTextOLED_Ascii(String oledline[9]) {
  oled.clear();
  oled.set1X();
  for (int jj = 1; jj <= 8; jj++) {  
     oled.println(oledline[jj]);
  }
}

void convHHMMSS(unsigned long currSeconds, char *uptimeHHMMSS) 
{
  int hh, mm, ss;

  hh = (currSeconds/3600);
  mm = (currSeconds -(3600*hh))/60;
  ss = (currSeconds -(3600*hh)-(mm*60));
  sprintf(uptimeHHMMSS, "Time: %02d:%02d:%02d", hh, mm, ss);

};

 
void convDDHHMMSS(unsigned long currSeconds, char *uptimeDDHHMMSS) 
{
  int dd, hh, mm, ss;

  ss = currSeconds; //258320.0 2 23:45:20
  dd = (ss/86400);
  hh = (ss-(86400*dd))/3600; 
  mm = (ss-(86400*dd)-(3600*hh))/60;
  ss = (ss-(86400*dd)-(3600*hh)-(60*mm));

  sprintf(uptimeDDHHMMSS, "%d %02d:%02d:%02d", dd, hh ,mm, ss);
};

void convCurrentTimeET(unsigned long currSeconds, char *currentTimeET) 
{
    time_t rawtime = currSeconds - 18000;
    struct tm  ts;
    char buf[70];

    ts = *localtime(&rawtime);

    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &ts);
    sprintf(currentTimeET, buf);

};

void convCurrentTimePT(unsigned long currSeconds, char *currentTimeET) 
{
    time_t rawtime = currSeconds - 28800;
    struct tm  ts;
    char buf[70];

    ts = *localtime(&rawtime);

    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &ts);
    sprintf(currentTimeET, buf);

};

void getWiFiRSSI(char *wifiRSSI) 
{
    sprintf(wifiRSSI, "%lddBm %d.%d.%d.%d", WiFi.RSSI(), WiFi.localIP()[0], WiFi.localIP()[1], WiFi.localIP()[2], WiFi.localIP()[3]);
};

void getMacWifiShield(char *macWifiShield) 
{
    byte mac[6];

    WiFi.macAddress(mac);
    sprintf(macWifiShield, "%02X:%02X:%02X:%02X:%02X:%02X", mac[5], mac[4], mac[3], mac[2], mac[1], mac[0]);
};

void getMacRouter(char *macRouter) 
{
    byte mac[6];

    WiFi.BSSID(mac);
    sprintf(macRouter, "%02X:%02X:%02X:%02X:%02X:%02X", mac[5], mac[4], mac[3], mac[2], mac[1], mac[0]);
};
