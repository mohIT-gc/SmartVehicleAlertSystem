#ifndef MY_LIBRARY_H
#define MY_LIBRARY_H
#endif

#include <Arduino.h>

int addTwoInts(int a, int b);

void startOLEDnano33IoT_Ascii(void);
void displayTextOLED_Ascii(String oledline[9]);

void convHHMMSS(unsigned long currSeconds, char *uptimeHHMMSS);
void convDDHHMMSS(unsigned long currSeconds, char *uptimeDDHHMMSS);
void convCurrentTimeET(unsigned long currSeconds, char *currentTimeET);
void convCurrentTimePT(unsigned long currSeconds, char *currentTimeET);

void getWiFiRSSI(char *wifiRSSI);
void getMacWifiShield(char *macWifiShield);
void getMacRouter(char *macRouter);
