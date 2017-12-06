#include "pub.h"

#include "ReadPNG.h"
#include "ScreenOp.h"
#include "ScreenEventManager.h"


/*
void registerEscap(HWND hDlg,bool r){
	if(r){
		RegisterHotKey(hDlg,VK_ESCAPE,0,VK_ESCAPE);
	}else{
		UnregisterHotKey(hDlg,VK_ESCAPE);
	}
}*/

int unit_ptr=10;
void activeOneTime(HWND hWnd);
void trySaveContrlData();
void dealDVDPrevNextKey();
void CALLBACK lpTimmerFuncZhw(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime ){
	activeOneTime(hwnd);
}


DWORD WINAPI timmerThreadA(LPVOID lparam){
	Sleep(1000);
	while(1){
		Sleep(100);
		try
		{
			scanTaskToexecut();
		}
		catch(...)
		{
			
			RETAILMSG_DC(1,(L" timmerThreadA MEE A EXCEPTION \r\n"));
		}
		releaseAllIfRequestHandleForThisThread();
	}
	return 0;
}
