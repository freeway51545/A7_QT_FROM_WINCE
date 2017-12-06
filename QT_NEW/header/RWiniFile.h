#ifndef _RWINIFILE_
#define _RWINIFILE_

#include "systemScreen.h"

#define SECTION_LEN 4
#define SCREEN_LEN 5


#define VAL_BRT 0
#define VAL_CTS 1
#define VAL_HUE 2
#define VAL_STR 3
#define VAL_BKL 4


#define SCREEN_FILE_NAME     L"/Residentflash3/system_init/Screen2.ini"



void readConfigueVal();
void writeConfigueVal();
void selectToSave(int section,int typeVal,int iTemp);
int getTheValueToSave(int section,int typeVal);
int getDefaultVal(int selType);

void everyTimeEnterInit();
void exitInitSystem();

#endif _RWINIFILE_