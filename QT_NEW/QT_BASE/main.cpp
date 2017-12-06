/*
 * Project Name JPEG DRIVER IN WINCE
 * Copyright  2007 Samsung Electronics Co, Ltd. All Rights Reserved. 
 *
 * This software is the confidential and proprietary information
 * of Samsung Electronics  ("Confidential Information").   
 * you shall not disclose such Confidential Information and shall use
 * it only in accordance with the terms of the license agreement
 * you entered into with Samsung Electronics 
 *
 * This file implements JPEG Test Application.
 *
 * @name JPEG Test Application Module (jpg_app.c)
 * @author Jiyoung Shin (idon.shin@samsung.com)
 * @date 28-05-07
 */

#include "pub.h"
#include <QtGui>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "ScreenEventManager.h"
#include "pub.h"
#include "systemScreen.h"
#include "sdconfig.h"
#include "volumdef.h"
#include "SysRw.h"


void setBright(int bright);
int seh_filer(int code,struct _EXCEPTION_POINTERS *infor,int module);
void startNextTurnLong(bool b);
void maySeedBeep();
BOOL BtInitAndRegCallBack();
/*
*******************************************************************************
Name            : main
Description     : Main function
Parameter       :
Return Value    : SUCCESS or FAILURE
*******************************************************************************
*/

void initMemToShow();
void initScreen();
void endShow();
void CALLBACK lpTimmerFuncZhw(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime );

void startCameraService();

HDC hdcCopyFile;
long lLastMouseTime;

HWND hGlobal=NULL;


BOOL exists(ZString name){
	FILE *fp=fopen(name,"rb");
	if(fp==NULL){
		return false;
	}
	fclose(fp);
	return true;
}

bool checkMcuUpdateFileExist(){
	if(exists("/SDMMC/DC_MCU.s19")||exists("/USBDisk1/DC_MCU.s19")
		||exists("/USBDisk/DC_MCU.s19")){
			return true;
	}else{
		return false;
	}
}


void startUpdateThread(char* filePath);
int sendMcuUpdateCMDToMcu();
/*
bool needUpdateMCU_M20(){
	if(exists(L"/SDMMC/DC_MCU.s19")){
		char* path="/SDMMC/DC_MCU.s19";
		//report("find mcu update file");
		report("检测到MCU升级文件");
		if(!sendMcuUpdateCMDToMcu()){
			return false;
		}	
		startUpdateThread(path);
		return true;
	}else if(exists(L"/Storage Card/DC_MCU.s19")){
		char* path="/Storage Card/DC_MCU.s19";
		report("检测到MCU升级文件");
		if(!sendMcuUpdateCMDToMcu()){
			return false;
		}	
		startUpdateThread(path);
		return true;
	}
	return false;
}

*/

HBRUSH rB;
RECT rtext={100,100,700,150};
void drawInfor(TCHAR *cc){
	//FillRect(hdcCopyFile,&rtext,rB);
	//DrawText(hdcCopyFile,cc,-1,&rtext,DT_LEFT);
}


bool isDirNotExist(TCHAR* src)
{
	ZString zs(src);
	QFile dir((char*)zs);
	if(!dir.exists() ){
		return 0;
	}
	return 1;
	
}
void copyBTIniFile(){


}
void copyFileAfterUpdate()
{
}

bool WinExecWaitFor(LPCTSTR exeFileName/* =_T */,LPCTSTR fileName);
void ControlData_loadData();
void rrrAtLast(TCHAR *c);

void startBluethollthService();
void startIpodServiceTEST();
int OpenComTESTSTM8_UART();
DWORD GetBootBackCarState();


void readConfigueVal();
void loadIconConfigSetting();
void startSTM8_UARTService();
void loadMatchTypeInit();
void initDebug();
void read音频AndExecute();
void startGPSDataThread();
void startCanService();
bool isSycTime();

void enableVedioGQ();
void sendTimeDataToCanBusThread();
//void readCanEqVal();
void loadIconConfigSetting();
BOOL StartLog(VOID);
extern int logPrintOn;
void radio2_init();
void main_init();
void init(){
	static int inited=false;
	if(inited)
		return;
	inited=true;
	
	//readConfigueVal();//读屏幕参数
	ControlData_loadData();//before CMD_MCU_REPORT_STA
	//loadIconConfigSetting();
	ENTER_RUN_MODE;

	initScreen();
	SysReadVal();

}


int initDelayTask();
bool isPressed=false;
int oldX,oldY;
int typeT=0;
// 1. 200 120 / 
// 2. 320 192 /
// 2. 400 240 /2


//TCHAR *cGgs=L"NaviOne";
// RtNavi

TCHAR *cGgsNames[]={
	L"NaviOne",
	L"RtNavi",
	L"Navigation",	
};


bool bMoved=false;
int ddx=0;
int ddy=0;
long lLastTime=0;
bool beFirstDraw=0;

int screen滑动Counter=0;
int nForword=0;
#define FOR_WORD_LEFT	1
#define	FORWORD_RIGHT	2
int xLastMouseMoved;
int yLastMouseMoved;
long lTime=0;
bool beNotDealMouse=false;
// 
// 如果在声音条中
// 
void turnUp();
void turnDown();
int getMaxTurnValue();
void closeTurnBar();
void startNextTurn(bool b循环);
bool dealedAsTurn=false;
void turnForX(int x);
bool beEnterScollVolume=false;


#define TURN_OFF_SET 40

bool isChangeVolume(int x,int y){
	return false;
}

bool isChangedTurn(int x,int y){
	return false;
}

bool checkBox(int x,int y){
	return false;
}

bool isInVolumeBOX(int x,int y){
	return false;
	/*
	if(x<xOrgVolume||x>xOrgVolume+VOLUM_WIDTH)
		return false;
	if(y<getyOrgVolume()||y>getyOrgVolume()+VOLUM_HEIGHT)
		return false;
	return true;
	*/
}
bool is软键盘ON();

bool dealed滑动Inback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	int x=LOWORD(lParam);
	int y=HIWORD(lParam);
	/** 滑动功能不处理了 */
	switch(message){
		case WM_LBUTTONDOWN:
			if(willData.isClosedScreen()){
				willData.setCloseScreen(false);
				dealedAsTurn=true;
				return true;
			}
			dealedAsTurn=false;
			beEnterScollVolume=false;
			if(nCurrentTurn!=TURN_NULL){
				// 需要判断，处于 声音条之中，进入声音滑动模式
				// 否则，关闭声音条。
				if(isChangedTurn(x,y)){
					startNextTurnLong(true);
				}else if(isChangeVolume(x,y)){ 
					beEnterScollVolume=true;
				}else{
					
					if(!is软键盘ON())
					{
						closeTurnBar();
						dealedAsTurn=true;
						beNotDealMouse=true;
					}else{
						beNotDealMouse=false;
						break;
					}
					return true;
				}
				/*
				if(isInVolumeBOX(x,y)){
					// 处理成声音。
					if(checkBox(x,y)){
						beEnterScollVolume=true;
					}
				}else{
					if(x>400){
						startNextTurnLong(true);
					}else{
						closeTurnBar();
						
					}
					dealedAsTurn=true;
					beNotDealMouse=true;
					return true;
				}
				*/
				return true;
			}
			beNotDealMouse=false;
			break;
		case WM_MOUSEMOVE:
			if(dealedAsTurn)
				return true;
			if(nCurrentTurn!=TURN_NULL){
				//在滚动期间
				if(beEnterScollVolume){
					turnForX(x);
				}
				if(is软键盘ON()){
					return false;
				}
				return true;
			}
			if(beNotDealMouse)
				return true;
			{
				
			}
			break;
		case WM_LBUTTONUP:
			if(dealedAsTurn)
				return true;
			if(nCurrentTurn!=TURN_NULL){
				if(is软键盘ON()){
					return false;
				}
				return true;
			}
			break;
	}
	return false;
}

bool isCanPowerOff(){
	return 0;
}
extern bool quickAccOff; 
bool dealed滑动(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	int x=LOWORD(lParam);
	int y=HIWORD(lParam);
	/** 滑动功能不处理了 */
	switch(message){
		case WM_LBUTTONDOWN:
			if(willData.isClosedScreen()&&(!isCanPowerOff())){
				if(!quickAccOff){
					willData.setCloseScreen(false);
					dealedAsTurn=true;
				}		
				return true;
			}
			dealedAsTurn=false;
			beEnterScollVolume=false;
			if(nCurrentTurn!=TURN_NULL){
				if(isChangedTurn(x,y)){
					startNextTurnLong(true);
				}else if(isChangeVolume(x,y)){ 
					beEnterScollVolume=true;
				}else{
					bool is软键盘ON();
					if(!is软键盘ON())
					{
						closeTurnBar();
						dealedAsTurn=true;
						beNotDealMouse=true;
					}else{
						beNotDealMouse=false;
						break;
					}
					return true;
				}				
				return true;
			}		
			beNotDealMouse=false;
			break;
		case WM_MOUSEMOVE:
			if(dealedAsTurn)
				return true;
			if(nCurrentTurn!=TURN_NULL){
				//在滚动期间
				if(beEnterScollVolume){
					turnForX(x);
				}
				if(is软键盘ON()){
					return false;
				}
				return true;
			}
			if(beNotDealMouse)
				return true;			
			break;
		case WM_LBUTTONUP:
			if(dealedAsTurn)
				return true;
			if(nCurrentTurn!=TURN_NULL){
				if(is软键盘ON()){
					return false;
				}
				return true;
			}
			break;
	}
	return false;
}


bool dealed滑动(QEvent*ev0){
	switch(ev0->type()){
		case QMouseEvent::MouseButtonPress :
		case QMouseEvent::MouseMove:
		case QMouseEvent::MouseButtonRelease:
			break;
		default:
			return 0;
	}
	QMouseEvent *ev=(QMouseEvent*)ev0;
	int x=ev->x();
	int y=ev->y();
	/** 滑动功能不处理了 */
	switch(ev->type()){
		case QMouseEvent::MouseButtonPress :
			if(willData.isClosedScreen()&&(!isCanPowerOff())){
				if(!quickAccOff){
					willData.setCloseScreen(false);
					dealedAsTurn=true;
				}		
				return true;
			}
			dealedAsTurn=false;
			beEnterScollVolume=false;
			if(nCurrentTurn!=TURN_NULL){
				if(isChangedTurn(x,y)){
					startNextTurnLong(true);
				}else if(isChangeVolume(x,y)){ 
					beEnterScollVolume=true;
				}else{
					bool is软键盘ON();
					if(!is软键盘ON())
					{
						closeTurnBar();
						dealedAsTurn=true;
						beNotDealMouse=true;
					}else{
						beNotDealMouse=false;
						break;
					}
					return true;
				}				
				return true;
			}		
			beNotDealMouse=false;
			break;
		case QMouseEvent::MouseMove:
			if(dealedAsTurn)
				return true;
			if(nCurrentTurn!=TURN_NULL){
				//在滚动期间
				if(beEnterScollVolume){
					turnForX(x);
				}
				if(is软键盘ON()){
					return false;
				}
				return true;
			}
			if(beNotDealMouse)
				return true;			
			break;
		case QMouseEvent::MouseButtonRelease:
			if(dealedAsTurn)
				return true;
			if(nCurrentTurn!=TURN_NULL){
				if(is软键盘ON()){
					return false;
				}
				return true;
			}
			break;
	}
	return false;
}

void activeTraslateMsg(QEvent*ev);
#include "basestateeventitem2.h"

void mouseEventDeal(BaseStateEventItemV2*pBined,QEvent*ev){
	if(!dealed滑动(ev)){
		if(pBined!=NULL)
			pBined->activeTraslateMsg(ev);
	}		
}

void mouseEventDeal(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	if(!dealed滑动(hWnd,message,wParam,lParam)){
		activeTraslateMsg(hWnd,message, wParam, lParam);
	}		
}

void drawOverlayScreen(HDC hdc);
void drawMapTopWin(HDC hdc);
void drawOverlayScreenVolWin(HDC hdc);
//void updateMapTopWindow();
extern bool MapMainDown;
int CALLBACK WndProc_Volume0(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	int wmId, wmEvent;
//    PAINTSTRUCT ps;
    HDC hdc;
	
    switch (message) 
    {
		/*case WM_SETCURSOR:
			SetCursor(NULL);
			return TRUE;
        case WM_COMMAND:
            wmId    = LOWORD(wParam); 
            wmEvent = HIWORD(wParam); 
            break;
        case WM_CREATE:
			{}
            break;*/
       // case WM_PAINT:			
		//	hdc = BeginPaint(hWnd, &ps);
			//drawOverlayScreenVolWin(hdc);
		//	drawMapTopWin(hdc);
		//	EndPaint(hWnd, &ps);
		//	break;
		//case WM_ERASEBKGND:
	//		break;
      //  case WM_DESTROY:
        //    PostQuitMessage(0);
          //  break;
		case WM_LBUTTONDOWN:
			{
				int x=LOWORD(lParam);
				int y=HIWORD(lParam);

				if(y<46&&x<120){
					//MapMainDown=true;
					//updateMapTopWindow();
				}
				//turnForX(x+xOrgVolume);
			}
			break;
		case WM_MOUSEMOVE:
			{
				int x=LOWORD(lParam);
				int y=HIWORD(lParam);
				//if(wParam!=0)
				//	turnForX(x+xOrgVolume);
			}
			break;
		case WM_LBUTTONUP:
			{
				int x=LOWORD(lParam);
				int y=HIWORD(lParam);

				if(y<46&&x<120){
					//MapMainDown=false;
					//updateMapTopWindow();
					showZHWConsol(false);
					RE_DRAW;
				}				
			}		
			break;;
        default:
          return 1;
		  //return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}


int CALLBACK WndProc_Volume(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
		try
		{
			RETAILMSG_DC(0,(L"windp message =%x\r\n",message));
			return WndProc_Volume0(hWnd,message,wParam,lParam);
		}
		catch(...)
		{
			//seh_filer(GetExceptionCode(),GetExceptionInformation(),76)
			RETAILMSG_DC(1,(L"MEE A EXCEPTION 76 \r\n"));
		}
		return true;
}

int CALLBACK WndProc_doNothing(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	int wmId, wmEvent;
    HDC hdc;
	
    switch (message) 
    {
        case WM_CREATE:
			{

			}
            break;
        case WM_DESTROY:
            //PostQuitMessage(0);
            break;
		case WM_USER:
		break;
		case WM_USER+1:
			break;
		case WM_LBUTTONDOWN:
		case WM_MOUSEMOVE:
		case WM_LBUTTONUP:
			return 1;
        default:
           return 1;
    }
    return 0;
}



void power6410Off();

Qt::HANDLE  threadMain=NULL;

void showMemc(char *infor){
	//TCHAR tBuf[1000];
	//showMem(getTCHAR1_0(tBuf,sizeof(tBuf),infor));
	//showMem(infor);
}

void showMem(TCHAR *infor){
//	if(1)
//		return;

}

/*
void testOpenFile(){
	showMem(L"T1");
	FILE *fp=fopen("/Storage Card/NaviOne/NAVIBG2.CLD","rb");
	showMem(L"T2");
	fclose(fp);
	showMem(L"T3");
}
*/



bool isInMainThread(){
	return 1;
}

BOOL beHaveError=0;

bool isInMainThreadAndReport(){
	bool b=threadMain==QThread::currentThreadId();
	if(!b){
		beHaveError=1;
	}
	return b;
}


static bool isLastVolumeMuteByTime=true;
void checkDataChanged();
void trySaveContrlData();// 避免冲突，将检查移动到这里
bool find提示();
void killGpsProcess();
void testEnterBackOverCloseBack();
bool muteTimeDelayFlag = false;

void dealDealyMuteTimeDueToMute(){
	if(GetTickCount()-willData.dTheTimeOpenVolume>400){
		if(muteTimeDelayFlag){
			willData.markVolChanged();
			muteTimeDelayFlag=false;
		}
	}
} 


void showMemc(char *infor);

DWORD dtCheck;

void timmser10psCheck(){
	RETAILMSG_DC(0,(L"timmser10psCheck Normal"));
	//checkDataChanged();//监测音源变化
	trySaveContrlData();//参数存储
	bool beMuteByeTime=GetTickCount()<willData.dTheTimeOpenVolume;
	if(beMuteByeTime){
		isLastVolumeMuteByTime=true;
	}
	else{
		if(isLastVolumeMuteByTime){
			willData.markVolChanged();
			muteTimeDelayFlag=false;
			isLastVolumeMuteByTime=false;
		}
	}
	dealDealyMuteTimeDueToMute();//处理蓝牙电话结束无声
	/*if(find提示()){		
		PostMessageZhw(MSG_SHOW_ZHW_CONTRL);		
		killGpsProcess();
	}*/
	//testEnterBackOverCloseBack();//倒车和刹车扫描
	if(GetTickCount()-dtCheck>1000){
		//showMemc("show infor once");
		dtCheck=GetTickCount();
	}
	
}


static DWORD lLastUpTime=0;
bool beScreenLocked=false;

bool tryUnlockScreen(UINT message){
	if(message==WM_LBUTTONDOWN){
		if(GetTickCount()>lLastUpTime)
		{
			beScreenLocked=false;
			RETAILMSG_DC(0,(L"UnLOCK TIME %d \r\n",GetTickCount()));
		}
	}
	return beScreenLocked;
}

void unlockScreen(){
	//beScreenLocked=false; // 不好使。
	//RETAILMSG_DC(1,(L"UnLOCK  \r\n"));
}

bool isScreenLocked(){
	return beScreenLocked;
}
void lockScreen(){
	RETAILMSG_DC(0,(L"LOCK TIME %d \r\n",GetTickCount()));
	lLastUpTime=GetTickCount()+30;
	beScreenLocked=true;
	PostMessageZhw(MSG_UNLOCK_SCREEN_LOCK);
}


void iisHaveNumbers(int n);

DWORD lPowerOffPressedTime;
bool bePowerDownPrssed=false;

void powerOnForScreenPrssed(DWORD d){
	if(!bePowerDownPrssed)
		return;
	if(!willData.isAccOn)
		return;
	void power6410On(bool fromMeta);
	power6410On(false);
	willData.setBePoweredOffByUser(false);
}


void printDebug(){
	if(existDebug()){
		//RETAILMSG_DC(1,(L"ExDisableReset zhwJpg.exe "));
		//RETAILMSG_DC(1,(L"Exception zhwJpg.exe "));
		
		//char *a=0;
		//a[0]=0;
	}
}
#define WM_MSDK_MEDIAGRAPH        (WM_USER + 0x3900)
#define HSS_DEBUG 1
extern bool beFoundGPSNeedKill;
extern DWORD dFindSDRemove;
extern bool bSdRemoved;

bool isDeviceExist(TCHAR *devName);

void mmp_clearFlag();
int loadType = 0;
void mmp_releaseAll();//播放时拔卡 需要释放

void closeOverlayDvdRightNow();
void setFirstScreen(ZString nScreen,bool *canJumpToScreen);

void toMainScreenNow(){
	///closeOverlayDvdRightNow();
	bool canJumpToScreen;
	setFirstScreen(SCRN_MAIN1,&canJumpToScreen);
}

void setFileReadFlag();


void deviceMonitorProc(WPARAM wParam,LPARAM lParam){

}





extern BOOL beHaveError;
#define GPS_STREAMING_START_STOP_MESSAGE  0x3644

bool isCurrentIsBtMusic();

//======20151229==============================
typedef struct _MouseCache{
	UINT message;
	WPARAM wParam;
	LPARAM lParam;
}MouseMessage;

#define MAX_BUFFER	100
MouseMessage mbuffer[MAX_BUFFER];
extern HWND hWndCurrent;

bool beHaveLockedScreenMouseMove=false;
DWORD lHaveLoedScreenMouse=0;
int locMM=0;
void clearMouseLockedTurn(){
	beHaveLockedScreenMouseMove=0;
	lHaveLoedScreenMouse=0;
	locMM=0;
}
#define RE_SEND_MOUSE	99089

void addLockedScreenMessage(UINT message, WPARAM wParam, LPARAM lParam){
	if(wParam==RE_SEND_MOUSE)
		return;
	MouseMessage mm;
	mm.message=message;
	mm.wParam=wParam;
	mm.lParam=lParam;
	switch(message){
		case WM_LBUTTONDOWN:
			{
				beHaveLockedScreenMouseMove=false;
				lHaveLoedScreenMouse=0;
				locMM=0;
				memcpy(&mbuffer[locMM++],&mm,sizeof(mm));
			};
			break;
		case WM_MOUSEMOVE:
			{
				if(locMM<MAX_BUFFER){
					memcpy(&mbuffer[locMM++],&mm,sizeof(mm));
				}
			}
			break;
		case WM_LBUTTONUP:	
			{
				beHaveLockedScreenMouseMove=true;
				lHaveLoedScreenMouse=GetTickCount();
				if(locMM<MAX_BUFFER){
					memcpy(&mbuffer[locMM++],&mm,sizeof(mm));
				}else{
					memcpy(&mbuffer[locMM-1],&mm,sizeof(mm));
				}
			}
			break;
	}
}


void closeOrOpenScreen(){
	if(willData.beClosedScreen){
		willData.setCloseScreen(false);
	}else{
		willData.setCloseScreen(true);
	}

}

void clearMsg_MouseCounter(){
	static DWORD dLastClearTime=GetTickCount();
	if(beHaveLockedScreenMouseMove==0){
		return;
	}
	if(beHaveLockedScreenMouseMove){

		// 补发一个消息
		if(GetTickCount()-lHaveLoedScreenMouse>50){
			//if(!willData.beClosedScreen){//非关屏状态下才补发
				//PostMessageZhw(MSG_REDRAW,GetTickCount());
			if(actScrnNo==SCRN_MAIN1){
				MouseMessage m1[MAX_BUFFER];
				memcpy(m1,mbuffer,sizeof(m1));
				int locMM1=locMM;
				for(int i=0;i<locMM1;i++){
					m1[i].wParam=RE_SEND_MOUSE;
					PostMessage(hWndCurrent,m1[i].message,m1[i].wParam,m1[i].lParam);
				}
			}
			//}			
			beHaveLockedScreenMouseMove=0;

			RETAILMSG(1,(L"补发一个mouse 消息消息 \r\n"));
		}
	}
}
/* */
//============================================

TCHAR *connectedRing=L"\\Residentflash2\\APP\\BT\\connected.wav";
void playBtConnectedSound(){

}

DWORD bootBackEndTime = 0;
void initParamet();
void mmp_volume_init();
void setThrowoffWave();
extern int initBootLogo;
#define LOG_ON 1
extern bool bInited;

void startMcuUpdate();
void setGPSvolume(int volSet);
void printBtPairStatus();
void initBtPairList();
void setAutoConnect();//2014-12-31
void checkA2DPConnectStatus();
void startupEndCarlifeWindow();
extern bool softPowerOffStat;
bool isLastIsMouseDown;

int CALLBACK WndProc1(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	int wmId, wmEvent;
    HDC hdc;
	if(message==WM_USER){
		threadMain=QThread::currentThreadId(); 
	}
    switch (message) 
    {
		
		//case WM_IMAGEDECODER_EVENT:
		//	return (INT_PTR)FALSE;
		//void MediaGraph_HandleEvent_m_hMediaGraph();
		//MediaGraph_HandleEvent_m_hMediaGraph();
		case WM_CREATE:
			{
					//loadUartTouch();//927touch
					//GetBootBackCarState();
					bootBackEndTime=GetTickCount();
					//ShowCursor(false);
					//initParamet();
					initDelayTask();
					//mmp_volume_init();
					{
					//	int iFullWidth = GetSystemMetrics(SM_CXSCREEN); 
					//	int iFullHeight = GetSystemMetrics(SM_CYSCREEN); 
					//	SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, iFullWidth, iFullHeight, SWP_NOOWNERZORDER|SWP_SHOWWINDOW);
					}
					//endAllGPSWindow();
					//startupEndCarlifeWindow();//20170821
					extern HWND hWndCurrent;
					hWndCurrent=hWnd;
					threadMain=GetCurrentThreadId(); 
					init();

//					hB=CreateSolidBrush(RGB(100,100,100));	

					PostMessageZhw(MSG_INIT_AVIN);
					PostMessageZhw(MSG_REDRAW);								
					if(initBtDev==0){
						PostMessageZhw(MSG_BTDVENAME_INIT);			
					}	
					if(initBootLogo==0){
					//	void updateBootLogo();
					//	updateBootLogo();
					}
					//startMcuUpdate();					
			}			
            return 1;
			/*
		case MSG_FAKE_POWER:
			void mayCloseAllSource();
			mayCloseAllSource();
			Sleep(500);
			willData.setCloseScreen(true);//关屏
			break;
			*/
//////////////////////////////GPS
		//case GPS_STREAMING_START_STOP_MESSAGE:
			
		//	break;
		//case WM_BT_EVT_MSG://WM_USER + 10209  //hss
		//	BZ_HandleBTEventEntry();
		//	break;

		
		
//===============================================================================================
		case WM_USER:			
			if(wParam==_TIMMER_10PS){				
				try{
					timmser10psCheck();
				}
				catch(...)
				{
					RETAILMSG_DC(1,(L" timmser10psCheck MEE A EXCEPTION 77 \r\n"));
				}
				if(GetTickCount()-lParam>300)
					break;
			}
			activeTraslateMsg(hWnd,message, wParam, lParam);
			break;
		case WM_LBUTTONDOWN:		
			if(willData.bePower6410PowerOff){
				lPowerOffPressedTime=GetTickCount();
				bePowerDownPrssed=true;
				addDelayTask(powerOnForScreenPrssed,1000);
				break;
			}
			maySeedBeep();
			isLastIsMouseDown=true;
		case WM_MOUSEMOVE:
		case WM_LBUTTONUP:			
			if(willData.bePower6410PowerOff){
				if(WM_LBUTTONUP==message){
					bePowerDownPrssed=false;
				}
				break;
			}
			/*if((actScrnNo==SCRN_DVP_DVD2||actScrnNo==SCRN_DVP_DVD1)&&IsInDvpMenu()){
				break;//dvd菜单时 禁止其他界面操作
			}*/
			if(message==WM_MOUSEMOVE&&wParam==0)
				break;
			lLastMouseTime=GetTickCount();
			if(isScreenLocked()){
				tryUnlockScreen(message);
				if(isScreenLocked()){
						addLockedScreenMessage(message,wParam,lParam);
						//添加到 缓存队列中 保存最后一个 MOUSE 队列
					break;
				}else{
					clearMouseLockedTurn();
				}
			}
			if(message==WM_LBUTTONUP){
				if(!isLastIsMouseDown){
					mouseEventDeal(hWnd,WM_LBUTTONDOWN,wParam,lParam);
					maySeedBeep();
				}
				isLastIsMouseDown=false;
			}
			mouseEventDeal(hWnd,message,wParam,lParam);
			return 1;

        default:
            return 1;
    }
    return 0;
}


void processMouseEvent(BaseStateEventItemV2*pBined,QEvent*ev){
//void processMouseEvent(QEvent*ev){
	//QMouseEvent r(10);
	//int type=ev->type();
	mouseEventDeal(pBined,ev);
		/*
	case WM_LBUTTONDOWN:		
			if(willData.bePower6410PowerOff){
				lPowerOffPressedTime=GetTickCount();
				bePowerDownPrssed=true;
				addDelayTask(powerOnForScreenPrssed,1000);
				break;
			}
			maySeedBeep();
			isLastIsMouseDown=true;
		case WM_MOUSEMOVE:
		case WM_LBUTTONUP:			
			if(willData.bePower6410PowerOff){
				if(WM_LBUTTONUP==message){
					bePowerDownPrssed=false;
				}
				break;
			}
			/*if((actScrnNo==SCRN_DVP_DVD2||actScrnNo==SCRN_DVP_DVD1)&&IsInDvpMenu()){
				break;//dvd菜单时 禁止其他界面操作
			}* /
			if(message==WM_MOUSEMOVE&&wParam==0)
				break;
			lLastMouseTime=GetTickCount();
			if(isScreenLocked()){
				tryUnlockScreen(message);
				if(isScreenLocked()){
						addLockedScreenMessage(message,wParam,lParam);
						//添加到 缓存队列中 保存最后一个 MOUSE 队列
					break;
				}else{
					clearMouseLockedTurn();
				}
			}
			if(message==WM_LBUTTONUP){
				if(!isLastIsMouseDown){
					mouseEventDeal(hWnd,WM_LBUTTONDOWN,wParam,lParam);
					maySeedBeep();
				}
				isLastIsMouseDown=false;
			}
			mouseEventDeal(hWnd,message,wParam,lParam);
			return 1;
			*/
}


void registerMeToSystem();

#define MAIN_ERROR

UINT toExecuteMesage=0;
WPARAM toExecutewParam=0;
LPARAM toExecutelParam=0;
DWORD timeToExecute=0;

void accOffsendBackMcuForTest();
void Sleep(int ms){
	QTime reTime=QTime::currentTime().addMSecs(ms);
	while(QTime::currentTime()<reTime){
		QApplication::processEvents(QEventLoop::AllEvents,100);
	}
}
void accOffsendBackMcuForTest(){
	Sleep(100);
}
void releaseAllIfRequestHandleForThisThread(){
}

int CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
		toExecuteMesage=message;
		toExecutewParam=wParam;
		toExecutelParam=lParam;
		timeToExecute=GetTickCount();
#ifdef MAIN_ERROR
 		try
		{
#endif
			LRESULT r= WndProc1(hWnd,message,wParam,lParam);
			releaseAllIfRequestHandleForThisThread();
			toExecuteMesage=0;
			return r;
#ifdef MAIN_ERROR
		}
		catch(...)
		{
			
			RETAILMSG_DC(1,(L"MEE A EXCEPTION \r\n"));
			releaseAllIfRequestHandleForThisThread();
			RETAILMSG_DC(1,(L"PARAMTER message=0x%x wParam=0x%x lParam=0x%x 78\r\n",message,wParam,lParam));
		}
		toExecuteMesage=0;
		return true;
#endif
}

int nCount=0;

				 
void tryToStopAduio();
void decMSG_DRAW();
void updateOverlay();
LRESULT CALLBACK WnProcChildOverlay(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	int re;
	if((message!=WM_CREATE)){//20160928
		re=WndProc(hWnd, message, wParam, lParam);
	}
	 

	 if(message==WM_USER){
		 switch(wParam){
			 case MSG_REDRAW:
				 decMSG_DRAW();		
				 //updateOverlay();
				 break;
		 }
	 }
	 switch(message){
		case WM_CREATE:
			return 1;
		case WM_LBUTTONDOWN:
			if(nCount==10){
				void stopPlay(bool backToMenu);
				//stopPlay(true);
				nCount=0;
			}
			break;
		case WM_LBUTTONUP:
			{
				//void DVPMenuEnter(WPARAM wParam, LPARAM lParam);
				//DVPMenuEnter(wParam,lParam);
			}
			break;

	 }
	return re;
}


HWND hWnd_volume;
HWND hWnd_mute;
bool beShowed=false;
bool beShowMuteWindow=false;

void showMuteWindow(){
	RETAILMSG_DC(1,(L"showMuteWindow\r\n "));
}

void hideMuteWindow(){
	RETAILMSG_DC(0,(L"hideMuteWindow\r\n "));
}


void showVolumeWindow(){
	/** 设置全屏幕，没有菜单和状态条 */
	RETAILMSG_DC(1,(L"showVolumeWindow\r\n "));
}


void hideVolumeWindow(){
	RETAILMSG_DC(0,(L"hideVolumeWindow\r\n "));
}

void showInGPSCamera();

#define MAX_LOADSTRING 100
HINSTANCE			g_hInst;			// current instance



void writeRegister();

void createIdleThread();
void writeRegisterCarlifeForMFI();
int WINAPI WinMain()
{
    return 1;
}


Qt::HANDLE GetCurrentThreadId(){
	return  QThread::currentThreadId();
}

unsigned long GetTickCount(void){
	qint64 r=QDateTime::currentMSecsSinceEpoch();
	return r;
}

BOOL
WINAPI
PostMessageW(
    __in_opt HWND hWnd,
    __in UINT Msg,
    __in WPARAM wParam,
	__in LPARAM lParam){
		return 0;
}


void initWINCEEntery(){
			bootBackEndTime=GetTickCount();
			//initParamet();
			threadMain=GetCurrentThreadId(); 
			init();
			PostMessageZhw(MSG_REDRAW);								
}