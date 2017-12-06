#ifndef _SDUSB_SAVE_
#define _SDUSB_SAVE_


#include "zstring.h"
#include "filelist.h"
//#include "tzstring.h"

extern ZString SD_SAVE_FILE_NAME;
//("/Residentflash3/system_init/sdLastMem.ini");
extern ZString USB_SAVE_FILE_NAME;//     ("/Residentflash3/system_init/usbLastMem.ini");
extern ZString USB2_SAVE_FILE_NAME ;//    ("/Residentflash3/system_init/usb2LastMem.ini");

bool existsFile(TCHAR *path);
TCHAR *getTCHAR1_0A(TCHAR *tBuf,int maxLen,char *toDraw);

typedef struct{
	ZString  LMFileDir; //Ŀ¼
	ZString  LMFileName;//�ļ���
	int  LMFilter;//��������
	int LMPlayPos;//����ʱ���
	int LMIndex;//�����б�����λ��
}mLastInfo;

typedef struct {
	mLastInfo USB_LMInfo;	
	mLastInfo SD_LMInfo;
	mLastInfo USB2_LMInfo;
} mLMFileInfo;

extern bool IS_SD_USB_File_Played;
extern mLMFileInfo LmInfo;
extern FileList fList;
extern bool isLMinfo; 

extern int iInitShowDirInfo;
extern TCHAR *pbRootPathSD0;
extern TCHAR *pbRootPathUSB0;
extern TCHAR *pbRootPathUSB2;

ZString fetchData(FILE* h,char *head);
int fetchInt(FILE*h,char *head);

void writeSdUsbVal0(ZString &fileName);
void writeSdUsbVal(ZString &fileName);
bool ClearSDLMFileInfo();
bool ClearUSBLMFileInfo();
bool ClearUSB2LMFileInfo();
void readSdUsbVal0(ZString &fileName);
void readSdUsbVal(ZString &fileName);
void saveMediaPlayInfo();
bool existLMdirAndFile(ZString dir,ZString file);
bool recoverLMInfo(TZString rootDir);
void setLMSeekTime();

#endif _SDUSB_SAVE_