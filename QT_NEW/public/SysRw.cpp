
#include "pub.h"
#include "rwinifile.h"
#include "zstring.h"

//#define SYS_PUB_FILE (L"/Residentflash3/system_init/SysPub.ini")



char *btDevFlag="BT_DEV";
int initBtDev = 0;

char *bootLogoFlag="BOOT_LOGO";
int initBootLogo = 0;


char *startUpTip="NT_SHOW";
extern int isSelectNtshow;

char *logPrintTip="LOG_PRINT";
int logPrintOn = 0;

char *btRingTip="BT_RING";
extern int btCallVol;

char *clfVoxTip="CLF_VOX";
extern int clfVolTrsf;


void SysReadValExt(){
}

void SysReadVal(){
	try
	{
		SysReadValExt();
	}
	catch(...)
	{
		RETAILMSG_DC(1,(L"SysReadVal EXCEPTION\r\n"));
	}

}

#define INVALID_HANDLE_VALUE 0
void SysWriteValExt(){
}

void SysWriteVal(){
	try
	{
		initBtDev=1;
		SysWriteValExt();
	}
	catch(...)
	{
		RETAILMSG_DC(1,(L" SysWriteVal EXCEPTION\r\n"));
	}
}






