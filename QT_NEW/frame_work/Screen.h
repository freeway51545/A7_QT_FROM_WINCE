#ifndef _ZHW_SCREEN
#define _ZHW_SCREEN
#include "PNGStruct.h"

	#define TEST_DRAWX 0
	#define TEST_DRAWY 0

typedef BaseItem* PBaseItem;
class BaseStateEventItem;
class ScreenEventManager;



#include "zstring.h"



extern ZString  actScrnNo;
extern int nBackGroundActive;
int readFile(char *fileName,PNG_STRUCT *pngStruct);

#define BACK_GROUD					5
#define SETTING_LOCATION_NO_SHOW	6
#define SETTING_LOCATION_NO_NO		7


void selectBackDno(int dx);
void setChangedFlag();

int makeStrCode(char *);
#endif
