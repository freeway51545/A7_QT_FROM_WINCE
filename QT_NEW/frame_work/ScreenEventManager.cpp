#include "pub.h"

#include "BaseStateEventItem2.h"
#include "ReadPNG.h"
//#include "Screen.h"
#include "stdio.h"
#include "ScreenEventManager.h"
#include	"pub.h"
//extern SystemDialog_Event systemDialog_Event;
#define NO_BIRGHT	1
#define MAX_BIRGHT	1
#include "uartservice.h"

#include "keyEvent.h"
#include "zstring.h"
//#include "LoadManager.h"
#include "VerConfig.h"
#include "VerConfig.h"

void updateOverlay();
void power6410On(bool fromMeta);
void closeOrOpenScreen();
void drawCheBiao();

void reportDrawThread(TCHAR *infor,void*p);

bool is软键盘ON();

ScreenEventManager  sem;

int beShowDataTime=1;
void LOG(char *log);




void makeKeyPressing();
//char showData[10];


bool isCurrentShowTime();
void updateMapTopWindow();
void checkTimeChangeRedraw(){
	/*
	SYSTEMTIME showNowTime;   
	GetLocalTime(&showNowTime);
	static int lastMinutes =0;
	if(lastMinutes!=showNowTime.wMinute){
	lastMinutes=showNowTime.wMinute;
	/*if(isCurrentShowTime()){
	reDrawAtOnce();
	} * /
	updateMapTopWindow();
	RE_DRAW;

	}
	*/
}


HWND hWndCurrent=NULL;

extern void timmerValue();
int lastMinute=0;

void makeFTJKeyPressing();
//void dealPressingIX45();
void checkPowerLongPressed();
void timmerShow空调();
void 倒车TimmerCheck();
void checkBTPlayState10PS();
void close软键盘Timmer();
void clearMSG_REDRAWCounterBy10Ps();
void timmerShowCarDr();
void timmerShowPhoneDr();
void clearMsg_MouseCounter();
void sendMusicOrVideoInfo();
DWORD lTime000=0;
TCHAR *tInfor=0;
BOOL outPutPrintInfo =TRUE;
void CheckRadarEndShow();
void checkDvrDeviceCommStat(){
}

void activeOneTime(HWND hWnd){
	//setThreadState("$A0 ");
	clearMSG_REDRAWCounterBy10Ps();
	//setThreadState("$A1 ");
	PostMessage(hWnd,WM_USER,_TIMMER_10PS,GetTickCount());
	//setThreadState("$A2 ");
	timmerValue();
	//setThreadState("$A3 ");
	makeKeyPressing();
	//setThreadState("$A4 ");
	checkTimeChangeRedraw();
	//setThreadState("$A5 ");
	//timmerShow空调();
	//倒车TimmerCheck();
	//timmerShowCarDr();
	//CheckRadarEndShow();
	//timmerShowPhoneDr();
	//setThreadState("$A6 ");
	//close软键盘Timmer();
	//sendMusicOrVideoInfo();
	clearMsg_MouseCounter();
	//setThreadState("$A7 ");
	checkDvrDeviceCommStat();
}



BOOL isBtConnected();
BOOL IsBtSwitchOn();
void printBtPairStatus();
extern DWORD btSwitchTime;
BOOL g_fgBZInited=true;
void makeBtCanSearch(){
}
DWORD makeBtSearchPost(LPVOID lpParameter){

	return 1;
}

void startCheckBtCanSearchThread(){
	//	CreateThread(NULL, 0, makeBtSearchPost, NULL, 0, NULL);
}
void updateOverlay();
void reDrawAtOnce(){
	if(beEnterBack()){
		return;
	}	
	if(isInMainThread()){
		activeTraslateMsg(hWndCurrent,WM_USER,MSG_REDRAW,0);
		try{
			//updateOverlay();
		}
		catch(...)
		{		RETAILMSG(1,(L"EXCEPTION updateOverlay()\r\n"));
		}

	}else{
		PostMessage(hWndCurrent,WM_USER,MSG_REDRAW,0);
		PostMessageZhw(MSG_UPDATE_OVERLAY);
	}

}

void FreshScreenAtOnce(){
	if(isInMainThread()){
		activeTraslateMsg(hWndCurrent,WM_USER,MSG_REDRAW,0);
	}
}

void ExecuteMessageZhw(WPARAM msgId,LPARAM lparam){
	static int i=0;
	activeTraslateMsg(hWndCurrent,WM_USER,msgId,lparam);
	RETAILMSG(1,(L"[ExecuteMessageZhw:]%d\r\n",i));
	i++;
}

BaseStateEventItemV2 * finsEventItem(ZString&name);
BaseStateEventItemV2 *ScreenEventManager::getStateEvent(ZString&n){
	return finsEventItem(n);
}

ScreenEventManager::ScreenEventManager(){
}



ScreenEventManager * getScreenEventManagerInstance(){
	return &sem;
}

void replaceHead0(ZString&showData);

char *weekOfDay[]={
	"星期日","星期一",	"星期二",	"星期三",	"星期四",	"星期五",	"星期六"
};


char *showTimeScreenList[]={
	//SCRN_MAIN1,
	//SCRN_DVD	,
	SCRN_DVD1	,
	//SCRN_图片预览	,
	//SCRN_音乐播放,
	SCRN_多媒体,
	//SCRN_蓝牙,
	SCRN_收音机2,
	SCRN_电话本,
	SCRN_车标,
	//SCRN_蓝牙音乐,
	SCRN_收音列表,
	SCRN_参数设置,
	SCRN_时间调整,
	SCRN_方向盘设置,
	SCRN_显示设置,
	SCRN_音频设置,
	SCRN_音频调节,
	SCRN_GPS声音,
	//SCRN_蓝牙配置,
	SCRN_MCU_UPDATE,
	SCRN_平衡设置
};

bool beShowTime;
void setTimeShowOrNot(bool bn){
	beShowTime=bn;
}
ZString actScrnNo;

bool isCurrentShowTime(){
	if(!beShowTime)
		return false;
	for(int i=0;i<sizeof(showTimeScreenList);i++){
		if(actScrnNo==showTimeScreenList[i])
			return true;
	}
	return false;
}

static bool inited_SCRN_蓝牙浮动=false;





BOOL isCurrentAVScreen(){
	return 0;
}

bool needDrawReportInAVIn(){
	if(isCurrentAVScreen()&&reportTimer>0){
		//switch(actScrnNo)
		{
			if(actScrnNo== SCRN_AVIN2){
				return false;
			}
			if(actScrnNo== SCRN_NullScreen){
				return false;
			}
		}
		return true;
	}
	return false;
}

bool doButtonPressedEvn=false;

//void globalReturnDeal();
void toScreenExecuteSTM8();
void toScreenExA(ZString&screnNo,bool saveCurrent);

void toScreenDir(ZString&screnNo){
	if(!isInMainThreadAndReport()){
		return;
	}
	toScreenExA(screnNo,true);
	toScreenExecuteSTM8();//hss
}

void toScreenDir(char *screenName){
	if(!isInMainThreadAndReport()){
		return;
	}
	toScreenExA(ZString(screenName),true);
}


//extern ZString actScrnNoBeforeEnterBack;
extern BaseStateEventItemV2 *activeBsei;
void toScreenExA(char* screnNo0,bool saveCurrent){
	activeBsei->toScreen(ZString(screnNo0));
}

void toScreenExA(ZString&screnNo,bool saveCurrent){
	activeBsei->toScreen(screnNo);
	 
}





bool redrawFlag=false;
bool isRedrawFlag(){
	return redrawFlag;
}

void clearRedrawFlag(){
	redrawFlag=false;
}

void redraw();
void setRedrawFlag(){
	redraw();
}
volatile int sendMSG_REDRAWCounter=0;
volatile bool beBusyFlag=0;

bool isPossibleHaveError=false;
void clearMSG_REDRAWCounterBy10Ps(){
	static DWORD dLastClearTime=GetTickCount();
	if(sendMSG_REDRAWCounter==0){
		dLastClearTime=GetTickCount();
		if(isPossibleHaveError){
			RETAILMSG_DC(1,(L"clearMSG_REDRAWCounterBy10Ps RETURN!\r\n"));
		}
		return;
	}
	if(GetTickCount()-dLastClearTime>1000){
		// 1秒没有动作可能有错误
		isPossibleHaveError=true;
		sendMSG_REDRAWCounter=0;
		dLastClearTime=GetTickCount();
		RETAILMSG_DC(1,(L"clearMSG_REDRAWCounterBy10Ps act \r\n")); 
	}
	if(beBusyFlag){
		// 补发一个消息
		if(GetTickCount()-dLastClearTime>300){
			PostMessageZhw(MSG_REDRAW,GetTickCount());
			beBusyFlag=0;
			RETAILMSG_DC(1,(L"补发一个MSG_REDRAW消息 \r\n"));
		}
	}
}

void decMSG_DRAW(){
	if(sendMSG_REDRAWCounter>0)
		sendMSG_REDRAWCounter--;
}

extern bool isPossibleHaveError;
void dealRedrawFlag(){
	if(redrawFlag){
		if(sendMSG_REDRAWCounter<1){
			LPARAM l=GetTickCount();
			PostMessageZhw(MSG_REDRAW,l);
			sendMSG_REDRAWCounter++;
			isPossibleHaveError=false;
			beBusyFlag=0;
		}else{
			beBusyFlag=1;
			RETAILMSG_DC(1,(L"REDRAW BUSY \r\n"));
		}
		clearRedrawFlag();
	}
}

void toSD_SCRN();
void toUSB_SCRN();


bool b忽略本按钮=false;

void _F_PUB_忽略本按钮(){
	b忽略本按钮=true;
}

extern bool beLongPressedLock;
//MSG_LONG_PRESSED_MESSAGE

bool showMouseParameter(TCHAR *msg,EventContext*ec){
	/*
	switch(ec->message){
		case WM_LBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_MOUSEMOVE:
			//if(msg!=NULL)
			//RETAILMSG_DC(1,(L"%s MOUSE ec=%0x X,Y (%d,%d)\r\n",msg,(UINT)ec,ec->mouseX,ec->mouseY));
			return true;
	}
	*/
	return false;
}
bool isShowedOnDvd();
bool isFullVScreen();
void reportSdError(LPARAM l);





void mayCallBeep(LPARAM lParam){
	unsigned pres=lParam&0xC0;
	if(pres==KEY_PRESSED){
		void maySeedBeep();
		maySeedBeep();
	}
}

//extern int toJumpToScrn;
extern bool beGpsCardInserted;
void restoreWin0Phr();
LPARAM 交换上下曲(LPARAM lParam);

bool beHaveOverlay();
bool igNorRedrawWhenHaveOverlay(){
	return false;
}

#define isCameraInShow() true

void executeCmdAA(LPARAM lParam);
void _F_MSG_EJECT_STOP_DVP_TOMAIN();
void mayCloseVi();
void excuteMcuUpdate(){
	if(inGps){
		showZHWConsol(false);
	}	
	mayCloseVi();
	TO_SCRN(SCRN_MCU_UPDATE);
}
void entryMcuUpdate();
void dealSpeedVol();
void setLocalDevNamePin(TCHAR *szTextName,TCHAR *szTextPin);
void sysGetBtDevName();
extern BOOL g_fgBZInited;

void initBtDevNamePass(){
	try
	{
		if(g_fgBZInited){
			//setLocalDevNamePin(L"欧诺S",L"0000");
			//sysGetBtDevName();
			makeBtCanSearch();			
		}	
	}
	catch(...)
	{
		RETAILMSG(1,(L" initBtDevNamePass Exception 123\r\n"));
	}	
}
void initBtDevName(){	
	PostMessageZhw(MSG_BTDVENAMEPASS_INIT);
}

void initBtPairOpenJudge(){
	try
	{
		if(g_fgBZInited){
			//sysGetBtDevName();;
		}	
	}
	catch(...)
	{
		RETAILMSG(1,(L" initBtPairOpenJudge Exception 123 \r\n"));
	}	
}

void initBtPairOpen(){	
	PostMessageZhw(MSG_BTPAIROPENJUDGE_INIT);
}

void decMSG_DRAW();
void closeAVInfoWhenChangedScreen();
int dealAccOnOff(LPARAM lParam);
bool reSendMcuUpdate =false;
bool bInited;
extern bool MutilMeidaStartPlay;
void dealKeySoftPowerOff();

void saveScreen();
bool softPowerOffStat = false;
bool in触摸屏校正=false;

extern BaseStateEventItemV2 *activeBsei;
void BaseStateEventItemV2::activeTraslateMsg(QEvent*ev){
	if(actScrnNo<0)
		return;// 没有初始化完成
	EventContext ecBody;
	ecBody.ev=ev;
	switch(ev->type()){
		case QMouseEvent::MouseButtonPress:
			b忽略本按钮=false;
			doButtonPressedEvn=true;
			if(reportTimer>0){
				reportTimer=0;
				RE_DRAW;
			}
			break;
		case QMouseEvent::MouseButtonRelease:
			doButtonPressedEvn=false;
			break;
	}
	activeBsei->ec=&ecBody;
	activeBsei->traslateMsg();
	activeBsei->ec=NULL;



}
void activeTraslateMsg(HWND hWnd,UINT message, WPARAM wParam, LPARAM lParam){
}
/*
void activeTraslateMsg(HWND hWnd,UINT message, WPARAM wParam, LPARAM lParam){
	if(actScrnNo<0)
		return;// 没有初始化完成

	hWndCurrent=hWnd;

	EventContext ecBody;
	ecBody.sm=sem;
	ecBody.hWnd=hWnd;
	ecBody.message=message;
	ecBody.wParam=wParam;
	ecBody.lParam=lParam;

	MSG_ZHW msg;
	msg.lParam=lParam;
	msg.comsumered=false;

	switch(message){
		case WM_LBUTTONDOWN:
			b忽略本按钮=false;
			doButtonPressedEvn=true;
			if(reportTimer>0){
				reportTimer=0;
				RE_DRAW;
			}
			break;
		case WM_LBUTTONUP:
			doButtonPressedEvn=false;
			break;
	}





	if(message==WM_USER){
		switch(wParam){
			 case MSG_INIT_AVIN:
				 {
					 void AVIN_INIT();//AVIN INIT(ONLY ONE TIME)
					 //AVIN_INIT();	
					 /*#ifndef R102_LOW_VER
					 StartUpToRunCarlife(); 
					 #endif* /	

				 }
				 break;
			 case MSG_SHOW_ZHW_CONTRL:
				 showZHWConsol(false);
				 break;
			 case MSG_DISABLE_SHOW_CHEBIAO:

				 if(!willData.bePower6410PowerOff){
					 willData.beShowCheBiaoOnly=false;
					 //willData.setCloseScreen(false);
				 }
				 break;
			 case MSG_DRAW_MUTE:
				 void drawMute();
				 //drawMute();
				 break;
			 case MSG_DRAW_BRIGHT_VOL:
				 void drawVolumeOrBright();
				 drawVolumeOrBright();
				 break;
			 case MSG_draw倒车Win:
				 {
					 void show空调显示INGPS();
					 //show空调显示INGPS();
				 }
				 break;

			 case MSG_DRAW_RADARWIN:
				 {
					 void showRadarInGPS();
					 //showRadarInGPS();
				 }
				 break;
			 case MSG_draw空调Win:
				 {
					 void show空调显示INGPS();
					 //show空调显示INGPS();
				 }
				 break;
			 case MSG_CARD_INSERTED:
				 if(actScrnNo!=SCRN_导航_2)
					 beGpsCardInserted=true;
				 break;
			 case MSG_UPDATE_OVERLAY:
				 {
					 //updateOverlay();
				 }
				 break;
			 case MSG_CHANGE_TO_CONTROL:
				 void dealReopenAv();
				 //dealReopenAv();
				 break;
			 case MSG_EXECUTE_CMD:
				 executeCmdAA(lParam);
				 break;
			 case MSG_EJECT_STOP_DVP_TOMAIN:
				 //_F_MSG_EJECT_STOP_DVP_TOMAIN();
				 break;
			 case MSG_TO_MCU_UPDATE:
				 excuteMcuUpdate();
				 break;
			 case MSG_RECOVER_MEDIA_PLAY:
				 void whenAccOnToRecoverMedia(int mediaDev);
				 whenAccOnToRecoverMedia((int)lParam);
				 break;
			 case MSG_RECOVER_DVD_PLAY:
				 void RecoverDvdPlay();
				 //RecoverDvdPlay();
				 break;
			 case MSG_READ_DISC_EXCEPTION:
				 // void readDiscException();
				 // readDiscException();
				 break;
			 case MSG_ILL_CHANGE_SCREEN:
				 void setScreenBright();
				 setScreenBright();
				 break;
			 case MSG_TO_RESET_MCU:
				 void exceptionFoundToResetMcu();
				 exceptionFoundToResetMcu();
				 break;
			 case MSG_CAN_TO_SETUP:
				 void FXP_SETUP_FUN();
				 FXP_SETUP_FUN();
				 break;
			 case MSG_CAN_TO_SYSINFO:
				 void FXP_SYSINFO_FUN();
				 FXP_SYSINFO_FUN();
				 break;
			 case MSG_CAN_MEDIA_PLAY:
				 void playSdFromMainEnter();
				 //playSdFromMainEnter();
				 break;
			 case MSG_REDRAW:	
				 decMSG_DRAW();// 表示处理了一个RE_DRAW 了				 				 
				 if(inGps||beEnterBack()
					 ||igNorRedrawWhenHaveOverlay()
					 ||willData.beShowCheBiaoOnly
					 ||willData.isClosedScreen()
					 ||willData.bePower6410PowerOff)
					 break;
				 break;
			 case MSG_SCREEN_FIRST_DRAWED:				 
				 void openDvrAux();
				 //openDvrAux();				
				 break;
			 case MSG_RADIO_PLAY_FIRST:
				 void PlayRadioFirstLoc();
				 //PlayRadioFirstLoc();
				 break;
			 case MSG_MEDIA_FIRST_SCREEN:
				 break;
			 case MSG_DVD_STATE:
				 //stateUpdateProxy(lParam);
				 break;

			 case MSG_SEND_MUTE_CMD:
				 void reSendMuteOrNotCmd();
				 //reSendMuteOrNotCmd();
				 break;

			 case MSG_EXCHANGED_VIDO:
				 {
					 void needExchangeVidio();
					 //needExchangeVidio();
				 }
				 break;

			 case MSG_KEY_EVENT:
				 RETAILMSG_DC(1,(L"KEY=0x%02x %d\r\n",lParam,GetTickCount()));
				 if(!bInited){
					 bInited=true;
				 }
				 if(dealAccOnOff(lParam)){
					 RETAILMSG(1,(L"dealAccOnOff\r\n"));
					 break;
				 }
				 if(in触摸屏校正){
					 return;
				 }

				 if(MSG_KEY_EVENT==wParam){
					 switch(lParam){
			 case T_KEY_SOFT_POWER_ON:
				 softPowerOffStat=false;
				 return;
			 case T_KEY_SOFT_POWER_OFF:								 					
				 saveScreen();
				 softPowerOffStat=true;	
				 dealKeySoftPowerOff();
				 return;
					 }
				 }
				 if(softPowerOffStat){
					 break;
				 }


				 if(beEnterBack()){
					 dealKeyEventInBack(lParam);
					 RETAILMSG(1,(L"beEnterBack\r\n"));
					 break;
				 }	

				 if(MSG_KEY_EVENT==wParam){
					 if(lParam==K_POWER){
						 //	 pMg.dealKeyPower();
						 RETAILMSG(1,(L"lParam==K_POWER\r\n"));
						 closeOrOpenScreen();
						 break;
					 }		
				 }

				 /* if(pMg.isPowerOffStat()){
				 RETAILMSG(1,(L"isPowerOffStat\r\n"));
				 break;
				 }* /

				 if(!dealKeyEvent(lParam)){
					 bool executeFxpForMeta=true;
					 BaseStateEventItemV2 *bse=sem.getStateEvent(actScrnNo);
					 if(bse!=NULL){
						 if(bse->dealKeyEvent(wParam,lParam)){
							 executeFxpForMeta=false;
						 }
					 }
				 }
				 break;

			 case MSG_EXCHANG_SCRN:
				 // void globalReturnDeal();
				 // globalReturnDeal();//2014-12-6
				 //toScreenExA((int)lParam,true);
				 void toScreenExecuteSTM8();
				 toScreenExecuteSTM8();//hss
				 //TO_SCRN_EX_ASY((int)lParam);
				 break;

			 case MSG_POWER_OFF_EVETN:
				 {
					 void reportPowerTime(int n);
					 reportPowerTime((int)lParam);
				 }
				 break;

			 case MSG_USB_PLUG_IN:
				 if(willData.bePower6410PowerOff){
					 power6410On(true);
					 willData.setBePoweredOffByUser(false);
				 }
				 break;

			 case MSG_SD_PLUG_IN:
				 if(willData.bePower6410PowerOff){
					 power6410On(true);
					 willData.setBePoweredOffByUser(false);
				 }
				 break;

			 case MSG_DISK_PLUG_IN:
				 break;
			 case MSG_LONG_PRESSED_MESSAGE:
				 beLongPressedLock=true;
				 break;
			 case MSG_SD_CARD_HAVE_EEROR:
				 reportSdError(lParam);//
				 break;
			 case MSG_SPEED_CHANGE:
				 //dealSpeedVol();
				 break;
			 case MSG_BTDVENAME_INIT://初始化默认的蓝牙设备明
				 addDelayTask((V_CALL_ID)initBtDevName,3000);
				 break;
			 case MSG_BTDVENAMEPASS_INIT:
				 initBtDevNamePass();
				 break;

			 case MSG_BTPAIROPEN_INIT://蓝牙开机难连
				 addDelayTask((V_CALL_ID)initBtPairOpen,2000);
				 break;

			 case MSG_BTPAIROPENJUDGE_INIT:
				 initBtPairOpenJudge();
				 startCheckBtCanSearchThread();
				 break;

			 case MSG_BTSEARCH_MSG:
				 RETAILMSG(1,(L"MSG_BTSEARCH_MSG StartPairing\r\n"));
				 makeBtCanSearch();
				 break;

			 case MSG_CHECK_MCU_UPDATE:
				 {
					 const unsigned char cmdData[1]={1};
					 executeSTM8Cmdnew(CMD_REPORT_UPDATE,sizeof(cmdData),cmdData);
					 for(int i=0;i<10;i++){
						 Sleep(200);
						 if(reSendMcuUpdate){
							 break;
						 }
					 }
					 if(!reSendMcuUpdate){
						 const unsigned char cmdData[1]={1};
						 executeSTM8Cmdnew(CMD_REPORT_UPDATE,sizeof(cmdData),cmdData);
					 }
					 // entryMcuUpdate();
				 }
				 //void entryMcuUpdate();//hss test
				 //entryMcuUpdate();
				 break;
			 case MSG_START_MCU_UPDATE:
				 void entryMcuUpdateForce();
				 //entryMcuUpdateForce();
				 break;
			 case MSG_UPGRADE_MAP:
				 bool checkMapUpgrade();
				 //checkMapUpgrade();
				 break;
			 case MSG_RE_INIT_AVIN:
				 void REINIT_AVIN();
				 //REINIT_AVIN();
				 break;

			 case MSG_LOAD_START:
				 //cLoadMgr.LoadStart();
				 break;

			 case MSG_LOAD_COMPLETE:
				 if(MutilMeidaStartPlay){
					 //cLoadMgr.LoadComplete();				  
				 }else{
					 //cLoadMgr.InLoadingPlugOut();
				 }				 
				 break;
		}
	}

	if(ecBody.isBeNeedRedraw()){
		if(!msg.noSendRedrawMessageInMouseMove){
			RE_DRAW;	
		}
		RETAILMSG_DC(0,(L"event %x,%x,%lx\r\n",message,wParam,lParam));
	}

	dealRedrawFlag();// TIMMER 会到达这个地方。
}
*/

void loadFxpKeyValue();

long lBegin=0;
int debug=0;
void rrrAtLast(TCHAR *msg){
	if(!debug)
		return;
	long lCurrent=::GetTickCount();
	long lSpeed=lCurrent-lBegin;
	if(lBegin==0){
		lSpeed=0;
	}
	lBegin=lCurrent;
	if(msg!=NULL)
		RETAILMSG_DC(1, (L"%s %d\r\n",msg,lSpeed));	
}

#include "BaseStateEventItem.h"
#define MAX2	100
char *screen2Name[MAX2];
BaseStateEventItemV2 *baseEventItem[MAX2];

int max2Len=0;
#define SCRN_MAIN1_LOC		0

BaseStateEventItemV2 * finsEventItem(ZString&name){
	if(name.isEmpty()){
		return NULL;
	}
	for(int i=0;i<max2Len;i++){
		if(strcmp(screen2Name[i],name)==0){
			return baseEventItem[i];
		}
	}
	return NULL;
}



//      addScren(SCRN_system,system_EventHandle);
//		addScren(SCRN_MAIN1,MAIN1_EventHandle);

void addScren(char *screenName,BaseStateEventItemV2&item){
	if(max2Len>=MAX2){
		return;
	}
	screen2Name[max2Len]=screenName;
	baseEventItem[max2Len]=&item;
	max2Len++;
}
void radio2_init();
void main_init();
void initPub();
void videolist_init() ;
void initScreen(){
	//loadSetting();	
	//initBackGround();
	main_init();
	radio2_init();
	initPub();
	videolist_init();
	selectScren("SCRN2_MAIN");
	//selectScren(getMainScreen());	
}

//extern int keepYBegin,keepYEnd;

void getKeepLines(int *yBegin,int *yEnd){
	
}


bool	is软键盘ON(void);

void makeKeyPressing(){
	BaseStateEventItemV2 *bse=sem.getStateEvent(actScrnNo);
	if(bse!=NULL){
		bse->traslateMsgPressing();
	}
}


void EventContext::setBeNeedRedraw(bool b){
	beNeedRedraw=b;
}



/**  */


typedef struct ___delayTask{
	DWORD timeToExecute;
	V_CALL_ID callBackFunction;
	DWORD userData;
}DelayTask;


#define MAX_DT 100
#define MIN	1
static int nLoc=MIN;	// 千万不要修改，不知道为什么
static DelayTask dta[MAX_DT];
//static CRITICAL_SECTION messageLock; 


int initDelayTask(){
	//	InitializeCriticalSection(&messageLock);
	return 1;
}

int addDelayTask(V_CALL_ID callBackFunction,long timeToDelay){
#ifndef WINCE
	if(true)
		return 1; 
#endif 
	if(nLoc>=MAX_DT)
		return 1;
	//	EnterCriticalSection(&messageLock);
	dta[nLoc].timeToExecute=GetTickCount()+timeToDelay;
	dta[nLoc].callBackFunction=(V_CALL_ID)callBackFunction;
	//	dta[nLoc].userData=userId;
	RETAILMSG_DC(0,(L"ADD NO.%d %x timeToExecute ,%d current \r\n",nLoc,dta[nLoc].timeToExecute,GetTickCount()));
	nLoc++;
	for(int i=MIN;i<nLoc;i++){
		RETAILMSG_DC(0,(L"PP NO.%x %x timeToExecute ,%d ---- \r\n",i,dta[i].timeToExecute,GetTickCount()));
	}
	//	LeaveCriticalSection(&messageLock);
	return 1;
}


void scanTaskToexecut(){
	RETAILMSG_DC(0,(L"E0"));
	/*if(!beEnterBack()){
	return;
	}*/
	RETAILMSG_DC(0,(L"E00"));
	DelayTask dtToExecut[MAX_DT];
	memset(dtToExecut,0,sizeof(dtToExecut));
	int toExecutCount=0;
	//	EnterCriticalSection(&messageLock);
	char cc[MAX_DT];
	memset(cc,0,MAX_DT);
	int ttNew=MIN;
	for(int i=MIN;i<nLoc;i++){
		//RETAILMSG_DC(1,(L"NO.%d %d timeToExecute ,%d current \r\n",i,dta[i].timeToExecute,GetTickCount()));
		if(dta[i].timeToExecute<GetTickCount()){
			//(*dta[i].callBackFunction)();
			dtToExecut[toExecutCount].callBackFunction=dta[i].callBackFunction;
			dtToExecut[toExecutCount].userData=dta[i].userData;
			toExecutCount++;
			// remove i
			cc[i]=1;
			//RETAILMSG_DC(1,(L"TO EXECUTE NO.%d %d timeToExecute ,%d current \r\n",i,dta[i].timeToExecute,GetTickCount()));
			// WILL DELETE THE MESSAGE
		}
	}
	for(int i=MIN;i<nLoc;i++){
		if(cc[i])
			continue;
		memcpy(&dta[ttNew],&dta[i],sizeof(DelayTask));
		ttNew++;
	}
	nLoc=ttNew;
	//	LeaveCriticalSection(&messageLock);
	for(int i=0;i<toExecutCount;i++){
		RETAILMSG_DC(1,(L"to execute task :%x \r\n",dtToExecut[i].callBackFunction));
		RETAILMSG_DC(1,(L"E1"));
		PostMessageZhw(MSG_EXECUTE_CMD,(LPARAM)dtToExecut[i].callBackFunction);
		//(*dtToExecut[i].callBackFunction)(dtToExecut[i].userData);
		RETAILMSG_DC(1,(L"E2 r\n"));
	}
}

void executeCmdAA(LPARAM lParam){
	V_CALL_ID callBackFunction=(V_CALL_ID)lParam;
	callBackFunction(0);
}





extern bool whenBackCallover;
bool restoreOldScreenBeforeBt(){
	void setCheckVi();
	if(beEnterBack()){
		whenBackCallover=true;
		return true;// 不用恢复
	}else{
		//setCheckVi();
	}
	//screenCurrent.restoreCurrentState();
	return true;
}

void setFirstScreen(ZString nScreen,bool *canJumpToScreen){
	if(willData.btInCalling){
		//screenCurrent.setScrnNo(nScreen);
		*canJumpToScreen=false;
		return;
	}
	if(beEnterBack()){
		//screenCurrent.setScrnNo(nScreen);
		//actScrnNoBeforeEnterBack=nScreen;
		*canJumpToScreen=false;
		return;
	}
	//ExecuteMessageZhw(MSG_EXCHANG_SCRN,nScreen);
	//ExecuteMessageZhw(MSG_REDRAW,nScreen);
	return;
}

void closeAVinWhenEntenGPS();
void closeVedioagain();



extern bool enterBackFromHere ;
extern bool loadDvpIsBack;
BOOL isLastAVScreen(ZString lScrn);
void openAVinWhenLeaveBack();
extern bool auxEnter;

extern bool recoverMediaIsBack;//20160116
extern int recoverMediaType;
void AUX_LeveBack22();
void recoverMediaAcconWhenBackEnd(){
	if(recoverMediaIsBack){
		RETAILMSG_DC(1,(L"ACC SAVE then Restore\r\n"));
		recoverMediaIsBack=false;
		PostMessageZhw(MSG_RECOVER_MEDIA_PLAY,(LPARAM)recoverMediaType);
	}
}

//void globalReturnDeal();
//void toScreenExA(int screnNo,bool save);
void toScreenExecuteSTM8();
void closeCarlifeAudio();
void saveOldScreenBeforeBt(int nScreen){
	if(actScrnNo!=SCRN_AVIN2){
		//toScreenExA(nScreen,false);
		//closeCarlifeAudio();
		if(inGps){
			showZHWConsol(true);			
		}
	}
	//closeVedioagain();
}


#define MUTE_X	740
#define MUTE_Y	430

POINT getCurrentMuteLocation(){
	static POINT pDvd={740,350};
	static POINT pNormal={740,430};
	if(inGps)
		return pNormal;

	return pDvd;
}

ZString&getMainScreen(){
	static ZString zs(SCRN_MAIN1);
	return zs;
}
ZString&getSCRN_DVD(){
	static ZString zs(SCRN_DVD);
	return zs;
}
ZString&getSCRN_参数设置(){
	static ZString zs(SCRN_参数设置);
	return zs;
}


void toScreenNotForce(ZString n){
	if(n!=actScrnNo){
		TO_SCRN_EX_ASY(n);
	}
	if(inGps){
		PostMessageZhw(MSG_SHOW_ZHW_CONTRL);
		RETAILMSG_DC(1,(L"MSG_SHOW_ZHW_CONTRL 1\r\n"));
	}
}


void setAllScreenTxtMiddle(int scrnNo){
	//screen[scrnNo].setAllTextShowMiddle();
}

void setScreenTxtMiddle(int scrnNo,char *names[],int size){
	//screen[scrnNo].setScreenTxtMiddle(names,size);
}



unsigned char mDays[]={31,30,31,30,31,30,31,31,30,31,30,31};
int getMonthMaxDay(int m,int year){
	if(m==2){
		if(year%400 == 0 || year%100 != 0 && year % 4 == 0)
			return 29;
		else
			return 28;
	}
	return mDays[m-1];
}









//////////////////////////---------



char *uiBaseRootList[]={
	"",
	"ui-01"
};
TCHAR  *uiTBaseRootList[]={
	L"",
	L"ui-01\\"
};

char *uiCBaseRootList[]={
	"",
	"ui-01\\"
};

void nextUiType(){

	uiBaseRoot=uiBaseRootList[0];

}

TCHAR *getTUiRootName(){
	return uiTBaseRootList[0];
}

char *getUiRootName(){
	return uiCBaseRootList[0];
}

char *uiBaseRoot=uiBaseRootList[0];
//static int 0=0;
char *getUiSlName(){
	return uiBaseRootList[0];
}
char *getRelateName(char *fileName,char *target){
	strcpy(target,uiBaseRoot);
	if(uiBaseRoot[0]!=0){
		strcat(target,"\\");
	}
	strcat(target,fileName);
	return target;
}

TCHAR * getTFileName(TCHAR *src,TCHAR *target){
	getTCHAR1_0(target,1000,uiBaseRoot);
	if(uiBaseRoot[0]!=0){
		wcscat(target,L"\\");
	}
	wcscat(target,src);
	return target;
}

char *getPropIni(char *name){
	strcpy(name,uiBaseRoot);
	if(uiBaseRoot[0]!=0){
		strcat(name,"\\");
	}
	strcat(name,"prop.ini");
	return name;
}

char *getPngName(char *name){
	char namep[2000];
	strcpy(namep,uiBaseRoot);
	if(uiBaseRoot[0]!=0){
		strcat(namep,"\\");
	}
	strcat(namep,name);
	strcpy(name,namep);
	return name;
}


#include "BaseStateEventItem2.h"
