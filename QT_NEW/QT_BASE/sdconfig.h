#ifndef _SDCONFIG_H_
#define _SDCONFIG_H_
#include "ZString.h"
#include "TZString.h"

#define GPS_SDMMC //卡槽类型:1<->该宏打开  2<->该宏关闭
//#define NO_SDMMC
#ifdef GPS_SDMMC
#ifdef NO_SDMMC
#define GPS_USB
#endif
#endif

#define MEDIA_SLOT 1
#define GPS_SLOT   2	
#define USB_SLOT   3
#define USB1_SLOT  4
extern int cardSlotConfig;
int getCardType();
char* getSlotTypePath(int slType);

#endif