#include "pub.h"

#include "BaseStateEventItem.h"
#include "ReadPNG.h"
//#include "Screen.h"
#include "stdio.h"
#include "ScreenEventManager.h"
#include "pub.H"
#ifdef WINCE
	#include "pm.h"
#endif

void LOG(char*);

bool existsFile(TCHAR *path){
	/*
	HANDLE h1= CreateFile(path,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,0,0);
	if(h1==INVALID_HANDLE_VALUE){
		// ���ǵ���̬
		return false;
	}
	CloseHandle(h1);
	*/
	return true;
}

bool existDebug()
{
	return existsFile(L"/Residentflash2/APP/debug.txt");
}

bool existDebugGps(){
	return existsFile(L"/Residentflash2/APP/debugGps.txt");
}

bool isAccOn(){
	return willData.isAccOn;
}

bool beFoundGPSNeedKill=false;
bool endAllGPSWindow();
DWORD dFindSDRemove;
bool bSdRemoved;






 void killProcess(TCHAR *processName);

void reportSdError(LPARAM l){
	if(inGps){
		 PostMessageZhw(MSG_SHOW_ZHW_CONTRL);
		 RETAILMSG_DC(1,(L"MSG_SHOW_ZHW_CONTRL 0\r\n"));
		//showZHWConsol();
	}
	//report("����GPS�����������ݿ��ܱ��𻵣�����������GPS��");
	report("GPS�����쳣��������ϵͳ");
	killProcess(L"NaviOne.exe");
}



char connectState=CONNECT_UNCONNECT;
//void updateMapTopWindow();
void setStateBtConnect()
{
	connectState=CONNECT_OK;
	//updateMapTopWindow();
	RE_DRAW;
}
void makeBtCanSearch();
void clrStateBtConnect()
{
	connectState=CONNECT_UNCONNECT;
	makeBtCanSearch();
	//updateMapTopWindow();
	RE_DRAW;
}

BOOL isBtConnected()
{
	return (CONNECT_OK==connectState);
}



void _F_����_����_C(){
}
void _F_�Ҷ�_C(){
}

TCHAR *dlg_getFileName(TCHAR *c){
	wcscpy(c,L"ZHW");
	return c;
}

void BT_�л�(){
}

void disconnectBT(){
}

void _F_�ز�(){
}

void connectOld(DWORD d){
}

void _F_����(){
}

void  _F_ֹͣ����Native(){
}

void _F_����Native(int n){
}

void exitBtByConnect(){
}

void _F_�Ͽ�(){
}

void btListPairList3360(){
}

void _F_PLAYNative(){
}

void  _F_PAUSE(){
}

void _F_PREV(){
}

void _F_NEXT(){
}

bool isBtMusicPlaying(){
	return false;
}




void closeBackCameraMSG(){
}

void openBackCameraMSG(){
}

bool isCameraOn(){
	return false;
}

void restoreRadioData(){
}

void closeBackCamera(){

}

void openBackCamera(){
}


long lLastExceptionTime=0;

DWORD callIRDWorkData(DWORD dwcode,DWORD parameter){
	return 0;
}


int executeSTM8Cmd(DWORD,unsigned char,unsigned int){
	return 0;
}

bool isWorkedAfterPowerOn(){
	return false;
}

void accOffOk(){
}

void accOnOk(){
}
void setWorkedOn(){
}



bool isAccHaveUped(){
	return 1;
}

void setFullScreen(){
}


