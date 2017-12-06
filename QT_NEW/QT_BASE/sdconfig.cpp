#include <QtGui>

#define CARDTYPE_ONE 0
#define CARDTYPE_TWO 1
#include "pubtype.h"
#include "sdconfig.h"
#include "zstring.h"
#include "tzstring.h"

#define PATH_SDMMC "\\SDMMC"		//DSK1
#define PATH_STOR  "\\Storage Card" //DSK2
#define PATH_USB   "\\USBDisk"//DISK3
#define PATH_USB1  "\\USBDisk1"//DISK4

int getCardType(){
#ifdef GPS_SDMMC
	return CARDTYPE_ONE;
#else
	return CARDTYPE_TWO;
#endif
	//return cardSlotConfig;
}

char* getSlotTypePath(int slType){
		switch(slType){
			case MEDIA_SLOT:
				if(CARDTYPE_ONE==getCardType()){//TYPE_ONE 相当于GPS_SDMMC宏打开
					return PATH_STOR;
				}else{//TYPE_TWO
					return PATH_SDMMC;
				}				
				break;
			case GPS_SLOT:
				if(CARDTYPE_ONE==getCardType()){
					return PATH_SDMMC;
				}else{
					return PATH_STOR;
				}				
				break;
			case USB_SLOT:
				return PATH_USB;
				break;
			case USB1_SLOT:
				return PATH_USB1;
				break;
		}
		return NULL;
}

