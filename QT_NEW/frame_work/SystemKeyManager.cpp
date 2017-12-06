#include "pub.h"
#include "BaseStateEventItem2.h"
#include "ReadPNG.h"
//#include "Screen.h"
#include "ScreenEventManager.h"
#pragma message("Insert User-defined Information here-----------------!") 
#define WriteFile(x)
#define CloseHandle(x)
#include "msg.h"
#include	"pub.h"

BOOL exists(ZString name);

//extern SystemDialog_Event systemDialog_Event;
#define NO_BIRGHT	1
#define MAX_BIRGHT	1
#include "keyEvent.h"
#pragma message("Insert User-defined Information here-----------------4!") 
#include "sdusb_control.h"
#include "sdusb_save.h"
#pragma message("Insert User-defined Information here-----------------3!") 
#include "sdconfig.h"
//#include "LoadManager.h"
#include "VerConfig.h"
#pragma message("Insert User-defined Information here-----------------5!") 
#pragma message("Insert User-defined Information here-----------------2!") 


extern int carlifeLinkDevType;

static bool be软键盘=false;

DWORD d软键盘ActiveTime;


void muteAll_GPH2_arm11_proxy();


bool __cdecl is软键盘ON(void){
	return be软键盘;
}

void clearBackCache(int notDelete);


void executeSTM8Force(DWORD cmd,unsigned char b0,unsigned char b1);


extern volatile long  vTimmerCounter;



bool isIgnorThisKey=false;



#define TIME_OUT	40


void mayCloseVi();
void toMainMenu(){
	mayCloseVi();
	TO_SCRN_EX_ASY(getMainScreen());
	if(isInMainThread()){
		PostMessageZhw(MSG_SHOW_ZHW_CONTRL);
	}else{
		showZHWConsol(false);
	}
}
void mayCloseAllSource();
void dealF42SBackButton(){
	 mayCloseAllSource();
	 toMainMenu();
}



void setBright(int bright){
	if(willData.getBright()!=bright){
		if(bright>MAX_BRIGHT)
			bright=MAX_BRIGHT;
		//if(bright<0)
			//bright=0;
		if(bright<4)
			bright=4;
		willData.setBright(bright);
		//turnBright(); 全部修改成异步处理
	}
}


void turnBirghtDb(unsigned int db){
	int n=willData.getBright()+db;
	setBright(n);
	//willData.setUserBright(willData.getBright());
}



void sendCurrentVolToMcu(int volSet);
void turnVolumeDv(int dv){
	int volTemp=willData.getVolByScrn()+dv;
	if(volTemp>MAX_VOL)
		volTemp=MAX_VOL;
	if(volTemp<0)
		volTemp=0;
	willData.setVolByScrn(volTemp);
	//sendCurrentVolToMcu(volTemp);
	void sendCanVol(int volSet);
#ifdef HAVE_CAN_BUS
	//sendCanVol(volTemp);
#endif 
	if(willData.isMute()){
		willData.setMute(false);
		PostMessageZhw(MSG_DRAW_MUTE);
		//drawMute();
		RE_DRAW;
	}
}


//drawVolumeOrBright()




void startNextTurnLong(bool b循环=false){
	nCurrentTurn++;
	if(nCurrentTurn>TURN_MAX_LONG){
		if(b循环)
			nCurrentTurn=TURN_VOLUMNE;
		else{
			nCurrentTurn=TURN_NULL;
			closeVolWin();
		}
	}
#ifdef WINCE 
	PostMessageZhw(MSG_DRAW_BRIGHT_VOL,0);
	//tryClose屏幕调节();
#endif
	vTimmerCounter=TIME_OUT;
}

void startNextTurn(bool b循环=false){
	nCurrentTurn++;
	if(nCurrentTurn>TURN_MAX){
		if(b循环)
			nCurrentTurn=TURN_VOLUMNE;
		else{
			nCurrentTurn=TURN_NULL;
			closeVolWin();
		}
	}
#ifdef WINCE 
	//drawVolumeOrBright();
	PostMessageZhw(MSG_DRAW_BRIGHT_VOL,0);
#endif
	vTimmerCounter=TIME_OUT;
}



void upBright(){
	turnBirghtDb(1);

}

void downBright(){
	turnBirghtDb(-1);
}



void upVolume(){
	turnVolumeDv(1);
}

char *getTurnName(int nCurrentTurn){
	switch(nCurrentTurn){
		case TURN_前后:
			return "前后";
		case TURN_左右:
			return "左右";
		case TURN_高音:
			return "高音";
		case TURN_低音:
			return "低音";
	}
	return "";
}

void dowVolume(){
	turnVolumeDv(-1);
}

extern bool beFirstDraw32;


void startTurn(){
	nCurrentTurn=TURN_VOLUMNE;
	/*if(nCurrentTurn==TURN_NULL){
		nCurrentTurn=TURN_VOLUMNE;
		beFirstDraw32=false;
	}
	if(!willData.bePower6410PowerOff&&beEnterBack()){
		nCurrentTurn=TURN_BRIGHT;// 关机到车只能调整亮度
	}*/
}


void closeTurnBar(){
	nCurrentTurn=TURN_NULL;
	vTimmerCounter=0;
	closeVolWin();
}	

int getMaxTurnValue(){
	switch(nCurrentTurn){
		case TURN_VOLUMNE:
			return MAX_VOL;
		case TURN_BRIGHT:
			return 25;
		case TURN_前后:
			return 15;
		case TURN_左右:
			return 15;
		case TURN_高音:
			return 15;
		case TURN_低音:
			return 15;
	}
	return 100;
}

int getValue(int x,int min,int max){
	int value=(x-200)*(max-min)/400+min;
	if(value<min)
		value=min;
	if(value>max)
		value=max;
	return value;
}



void turnForX(int x){
	//int value;
	switch(nCurrentTurn){
		case TURN_VOLUMNE:
			willData.setVolByScrn(getValue(x,0,MAX_VOL));
			if(willData.isMute()){
				willData.setMuteNew(false);//2016/09/20
			}
			break;
		case TURN_BRIGHT:{
				int n=getValue(x,1,MAX_BRIGHT);
				if(n<4){
					willData.setBright(willData.getBright()-1);
				}
				else{
					willData.setBright(n);
				}
			}
			break;
		case TURN_前后:
			willData.setFad(getValue(x,-MAX_SHUAI_JIAN3702,MAX_SHUAI_JIAN3702));
			break;
		case TURN_左右:
			willData.setBal(getValue(x,-MAX_SHUAI_JIAN3702,MAX_SHUAI_JIAN3702));
			break;
		case TURN_高音:
			willData.setTre(getValue(x,-MAX_SHUAI_JIAN3702,MAX_SHUAI_JIAN3702));
			break;
		case TURN_低音:
			willData.setBas(getValue(x,-MAX_SHUAI_JIAN3702,MAX_SHUAI_JIAN3702));
			break;
	}
	//drawVolumeOrBright();
	PostMessageZhw(MSG_DRAW_BRIGHT_VOL,0);
	vTimmerCounter=TIME_OUT;
}
void  drawVolumeOrBright();

void startTurnAndDraw(){
	startTurn();
#ifdef WINCE
	drawVolumeOrBright();
	//PostMessageZhw(MSG_DRAW_BRIGHT_VOL,0);
	willData.setMute(false);
#else
	RE_DRAW;
#endif
	vTimmerCounter=TIME_OUT;
}

void openOverlayVolChange();
void turnDown(){
	startTurn();
	switch(nCurrentTurn){
		case TURN_VOLUMNE:
			dowVolume();
			break;
		/*case TURN_BRIGHT:
			downBright();
			break;*/
	}
	//openOverlayVolChange();
	//updateMapTopWindow();
	RE_DRAW;	
}
void turnUp(){
	startTurn();
	switch(nCurrentTurn){
		case TURN_VOLUMNE:
			upVolume();
			break;
		case TURN_BRIGHT:
			upBright();
			break;
	}
	//openOverlayVolChange();
	//updateMapTopWindow();
	RE_DRAW;
	//drawVolumeOrBright();	
	//vTimmerCounter=TIME_OUT;
}





//extern bool beShowVolumne;
void timmerValue(){
	if(vTimmerCounter>0){
		vTimmerCounter--;
		if(vTimmerCounter==0){
			//PostMessageZhw(MSG_REDRAW);
			nCurrentTurn=0; 
			closeVolWin();
		}
	}
	//
	if(vTimmerCounter==0){
		//if(beShowVolumne)
		//	closeVolWin();	
	}
	if(reportTimer>0){
		reportTimer--;
		if(reportTimer<=0){
			reportTimer=0;
			PostMessageZhw(MSG_UPDATE_OVERLAY);
			RE_DRAW;
		}
	}
}

//extern Screen*volumeScreen;

int inGps=0;
int inXiuDing=0;
void openAll6621_7181_TV();

void set7181_7778(int dx);
//void EjectOrLoadDvd(bool beForceOutDoor);

DWORD dTimeDownKeyPressing=0;


 
int muteCounter=0;
long nLastMuteTime=0;
int src_type=0;
int meta_src_type=-1;
int oldMetaSrcType=-1;


//#主界面->DVD(如果存在)->SD->USB->收音机->GPS


void closeDvd(){
	void DVP_Close();
	//DVP_Close();
}

#include "uartservice.h"
void clearLastSendSrc();
void closeRadio(){
	if(SRC_RADIO==meta_src_type){
		OPEN_SOURCE_MUTE();
		const unsigned char cmdData[2]={SOURCE_OFF,SOURCE_OFF};
		executeSTM8Cmdnew(CMD_SRC_CHANGE,sizeof(cmdData),cmdData);
		clearLastSendSrc();// 避免CLOSE 收音机 不能再 打开的问题
	}
	
}

void btSusTest(){
	OPEN_SOURCE_MUTE();
	const unsigned char cmdData[2]={SOURCE_OFF,SOURCE_OFF};
	executeSTM8Cmdnew(CMD_SRC_CHANGE,sizeof(cmdData),cmdData);
}

void mmp_releaseAll();
void closeUsbPlaying(){
}

void closeUsb2Playing(){

}

void  close_aux();
void closeAux(){
	//close_aux();
}

void closeSdPlaying(){

}
void closeBtMusic();



bool isNowCalling();

bool isCurrentIsBtMusic(){
	return SRC_BT_MUSIC==meta_src_type;
}

void clearoldMetaSrcType(){
	oldMetaSrcType=0;
}

void ShutDownCarLifeVol(){
}


void mayCloseAllSource(){
	//closeBtMusic();
	closeUsbPlaying();
	closeAux();
	closeRadio();	
}

void dealKeySoftPowerOff(){
	willData.setMute(true);
	mayCloseAllSource();
	showZHWConsol(false);
	//btDisconnect(0);
	
}


bool isCarLifeTrsfByBT();

bool setSource(int currentType){
	if(beEnterBack()){
		return false;
	}
	if(isNowCalling()){
		return false;
	}	
	if(currentType!=oldMetaSrcType){
		mayCloseAllSource();
		if(isCarLifeTrsfByBT()){
			if(oldMetaSrcType==SRC_CARLIFE||oldMetaSrcType==SRC_BT_MUSIC){
				ShutDownCarLifeVol();
			}
		}else{
			if(oldMetaSrcType==SRC_CARLIFE){
				ShutDownCarLifeVol();
			}
		}
		
	}
	oldMetaSrcType=currentType;
	return true;
}

void setSrcType(int type){
	switch(type){
		case SRC_DVD:
		case SRC_SD:
		case SRC_USB:
		case SRC_RADIO:
		case SRC_BT_MUSIC:
		case SRC_AUX:
		case SRC_USB2:
		case SRC_AUX2:
		case SRC_CARLIFE:
			meta_src_type=type;
			break;
	}
	src_type=type;
	RETAILMSG_DC(1,(L"setSrcType:%d\r\n",type));
}

int getMetaSrcType(){
	return meta_src_type;
}


bool isBtMusicSrce(){
	if(meta_src_type!=SRC_BT_MUSIC){
		if(actScrnNo==SCRN_BT_MUSIC){
			OPEN_BT_MUSIC();
		}
	}
	return meta_src_type==SRC_BT_MUSIC;
}

int getCurrentVlumeType(){
	switch(meta_src_type){
		case SRC_DVD:
		case SRC_SD:
		case SRC_USB:
		case SRC_USB2:
			return VOL_DVD;
		case SRC_RADIO:
			return VOL_RADIO;
		case SRC_BT_MUSIC:
			return VOL_IIS;
		case SRC_AUX:
			return VOL_AUX;
		case SRC_AUX2:
			return VOL_AUX2;
		case SRC_CARLIFE:
			return VOL_CARLIFE;
	}
	return VOL_NULL;
}

int getSrcType(){
	return src_type;
}

//void clearOldScreenBeforeBt();


void executeCdAuxPressed(){
	while(true){
		RETAILMSG_DC(0,(L"CHANGE SOURCE BY exchangeToNextSource\r\n"));
		//closeCamWindow();
		switch(src_type){
			case SRC_SD:
			case SRC_USB:
			case SRC_DVD:
				setSrcType(SRC_AUX);
				void setNullScreenShow外部输入();
				//setNullScreenShow外部输入();
				TO_SCRN_EX_ASY(ZString(SCRN_NullScreen));
				break;
			case SRC_AUX:
				TO_SCRN_EX_ASY(getMainScreen());
				setSrcType(SRC_MAIN_MENU);
				break;
			default:
				setSrcType(SRC_DVD);// 无论如何都要继续处理的
				continue;
		}
		break;
	}
}

bool showGPS配置提示ThisTime=false;		
extern unsigned char cDvdState;		

/*
void exchangeToNextSource(){
	if(beEnterBack()||isNowCalling()){
		return;
	}
	if(inGps){//gps界面 手机互联界面却换mode先关gps界面20151218
		showZHWConsol(false);
		toMainMenu();
		setSrcType(SRC_MAIN_MENU);
		return;
	}

	while(true){
		switch(src_type){
			case SRC_MAIN_MENU:
				setSource(SRC_RADIO);
				TO_SCRN(SCRN_RADIO);
				break;
			case SRC_RADIO:
				setSrcType(SRC_BT);
				setSource(SRC_BT);
				//void InBtEnterSetSrcBTMusic();
				//InBtEnterSetSrcBTMusic();
				TO_SCRN(SCRN_BT_DIAL);
				break;
			case SRC_BT:
				setSrcType(SRC_BT_MUSIC);
				setSource(SRC_BT_MUSIC);
				TO_SCRN_EX_ASY(SCRN_BT_MUSIC);
				break;
			case SRC_BT_MUSIC:
#ifdef R102_LOW_VER
				setSrcType(SRC_USB2);
				if(isDeviceExist(pbRootPathUSB0)){
					cLoadMgr.MultiMediaToPlay();
				}else {
					continue;
				}
#else
				setSrcType(SRC_AUX);
				cDvrMgr.StartDvrPlay();//DVR
#endif
				break;
			case SRC_AUX:
				closeAux();
				setSrcType(SRC_USB2);
				if(isDeviceExist(LOAD_DEVICE)){
					cLoadMgr.MultiMediaToPlay();
				}else {
					continue;
				}
				break;

			case SRC_USB2:
				if(isMeidaDevice()){
					closeUsbPlaying();
				}
				setSrcType(SRC_MAIN_MENU);
				TO_SCRN_EX_ASY(getMainScreen());
				showZHWConsol(false);
				OPEN_SOURCE_MUTE();//2015-10-22
				RE_DRAW;
				break;		
			default:
				TO_SCRN_EX_ASY(getMainScreen());
				mayCloseVi();
				setSrcType(SRC_MAIN_MENU);
				break;
		}
				break;
	}
}*/


extern int backScreenFromBtMusic; 
void exchangeToNextSource(){//蓝牙-》U盘-》收音机
	if(beEnterBack()||isNowCalling()){
		return;
	}
	if(inGps){//gps界面 手机互联界面却换mode先关gps界面20151218
		showZHWConsol(false);
		//toMainMenu();
		void ShutDownCarLifeVol();
				ShutDownCarLifeVol();
		//setSrcType(SRC_MAIN_MENU);
		//return;
	}

	//backScreenFromBtMusic=-1;
	RETAILMSG(1,(L"Current src_type=%d\r\n",src_type));
	while(true){
		switch(src_type){
			case SRC_RADIO:
				//setSrcType(SRC_BT);
				//setSource(SRC_BT);
				setSrcType(SRC_BT_MUSIC);
				setSource(SRC_BT_MUSIC);
				//void InBtEnterSetSrcBTMusic();
				//InBtEnterSetSrcBTMusic();
				//TO_SCRN(SCRN_BT_DIAL);
				TO_SCRN(ZString(SCRN_BT_MUSIC));
				break;
			case SRC_BT:
			case SRC_BT_MUSIC:
					setSrcType(SRC_USB2);
					continue;
				break;
			case SRC_USB2:
			
				break;		
			default:
				setSrcType(SRC_RADIO);
				setSource(SRC_RADIO);
				TO_SCRN(ZString(SCRN_RADIO));
				break;			
		}
		break;
	}
}


extern volatile  int oldPC_IDR;


void closeScreenAA(DWORD userId){
	if(willData.bePower6410PowerOff){
		willData.setCloseScreen(true);
	}
}



void saveScreen();
void restoreScreen();
int executeSTM8Cmd(DWORD cmd,unsigned char b0,unsigned b1);
bool isWorkedAfterPowerOn();
void power6410Off(){
//#ifndef TEST_CHEBIAO
	void 	btMusicStop();
	if(isWorkedAfterPowerOn()){
		if(!willData.bePower6410PowerOff){
			// 只有在 POWER ON 的时候才保存
			saveScreen();// 只保存 USB,SD,DVD，收音机
		}
	}
	addDelayTask(closeScreenAA,1000);
//#endif
	RETAILMSG_DC(0,(L"KEY 3\r\n"));
	willData.beShowCheBiaoOnly=true;
	willData.bePower6410PowerOff=true;
	TO_SCRN_EX_ASY(getMainScreen());
	willData.setMute(true);/** 必须先静音，然后再SET SOURCE MUTE */
	OPEN_SOURCE_MUTE();
	void closeOverlayWindow();
	//closeOverlayWindow();
	if(inGps){
		showZHWConsol(false);
	}else{
		RE_DRAW_AT_ONCE;
	}
}

void clearBackCache(int notdeleted=-1);

// 
bool bPowerOnFromMeta=false;

void openScreenACCON(DWORD userId){
	if(!willData.bePower6410PowerOff){
		willData.setCloseScreen(false);
		if(!bPowerOnFromMeta){
			restoreScreen();
			//addDelayTask(lightScreenTrue,200,0);
			
			// 需要等待一会 然后再点亮屏幕
		}
		PostMessageZhw(MSG_DISABLE_SHOW_CHEBIAO);
		//SEND_SYSTEM_CMD(LIGHT_SCREEN,0);
	}
}


void power6410On(bool fromMeta){
	bPowerOnFromMeta=fromMeta;
	void clearBackGround();
	//clearBackGround();
	if(willData.bePower6410PowerOff)
		willData.beShowCheBiaoOnly=true;
	addDelayTask(openScreenACCON,300);
	//willData.setCloseScreen(false);
	willData.bePower6410PowerOff=false;
	OPEN_SOURCE_MUTE();// 开机，没有播放媒体前，静音
	willData.setMute(false);
}


 
#include "uartservice.h"



bool dealSUB_PLUS(int key){
	switch(key){
			case K_SOURCE_HOME:
				if(nCurrentTurn!=TURN_NULL){					
					//startNextTurn();// 下一个调整内容	
					//return true;
					return false;
				}
				break;
		
			case K_VOL_UP:
				turnUp();
				return true;
			case K_VOL_DN:
				turnDown();
				return true;
			case K_MUTE:
				
				break;
			case T_CAMERA_RECORD://disp全景却换
				if(isNowCalling()){
					return true;
				}else{
				}			
				return true;			
	}
	return false;
}


void _F_接听_拨打_C();
void _F_挂断_C();



int getNullScreenType();
bool IS_SD_USB_File_Played=false;

static char *format="SCRN:%d SUB:%d InGps:%d nSource:%d MetaSrcType:%d GpsBack:%d";
static char *format_sdusb="SCRN:%d DEV_TYPE:%d PLAY_STA:%d GUIEVENT_STA:%d";

void openRadioGlobal();

ZString SCREEN_FILE("/Residentflash3/system_init/screen.sav");
ZString MEDIA_FILE("/Residentflash3/system_init/Media_Acc.sav");

void runGPSresotre(DWORD userId);
DWORD callIRDWorkData(DWORD dwcode,DWORD parameter);

BOOL beFirstRestore=TRUE;
#define INVALID_HANDLE_VALUE 0
#define ReadFile(x)
#define CloseHandle(x)
void restoreMedia0(int *ScrnNo,int *mediaDev,int *mediaPlaySta,int *guiSta){
	HANDLE hHandle= openReadinPropFile(MEDIA_FILE);
	if(hHandle==INVALID_HANDLE_VALUE){
		return;
	}
	DWORD readed;
	{
		char buffer[1000];
		ReadFile(hHandle,buffer,sizeof(buffer)-1,&readed,0);
		buffer[readed]=0;
		TCHAR buff[1000];
		sscanf(buffer,format_sdusb,ScrnNo,mediaDev,mediaPlaySta,guiSta);
	}
	CloseHandle(hHandle);
}

int isGpsRunBack=0;
extern bool beBeginGps;
extern bool tellBootExitRearview;


bool cancelResotre=false;

void cancelRestoreSdUse(){
	cancelResotre=true;
}


bool checkRecoverCondition(int mediaType){
	/*switch(mediaType){
		case IS_SD_SELECT:
			return isDeviceExist(pbRootPathSD0);
		case IS_USB_SELECT: 
			return isDeviceExist(pbRootPathUSB0);
		case IS_USB2_SELECT:
			return isDeviceExist(pbRootPathUSB2);
		default:
			return false;
	}*/
	return false;
}

bool recoverMediaIsBack=false;//20160116
int recoverMediaType=0;
void whenAccOnToRecoverMedia(int mediaDev){
	if(beEnterBack()){	
		recoverMediaType=mediaDev;
		recoverMediaIsBack=true;
		return;
	}
	/*if(mediaDev==IS_SD_SELECT){
		void playSdFromMainEnter();
		if(isDeviceExist(pbRootPathSD0)){
			RETAILMSG_DC(1,(L"call playSdFromMainEnter\r\n"));
			playSdFromMainEnter();
		}
	}else if(mediaDev==IS_USB_SELECT){
		void playUsbFromMainEnter();
		if(isDeviceExist(pbRootPathUSB0)){
			RETAILMSG_DC(1,(L"call playUsbFromMainEnter\r\n"));
			playUsbFromMainEnter();
		}
	}else if(mediaDev==IS_USB2_SELECT){
		void playUsb2FromMainEnter();
		if(isDeviceExist(pbRootPathUSB2)){
			RETAILMSG_DC(1,(L"call playUsb2FromMainEnter\r\n"));
			playUsb2FromMainEnter();
		}
	}*/
	//cLoadMgr.MultiMediaToPlay();
}

DWORD WINAPI restorePlayThread(LPVOID lparam){
	int mediaDev=(int)lparam;
		Sleep(1500);
		try
		{
			for(int i=0;i<1000;i++){
				Sleep(50);
				if(cancelResotre){
					break;
				}
				if(checkRecoverCondition(mediaDev)){
					PostMessageZhw(MSG_RECOVER_MEDIA_PLAY,(LPARAM)lparam);
					break;
				}				
			}
			RETAILMSG_DC(1,(L"resotre over\r\n"));
		}
		catch(...)
		{
			RETAILMSG_DC(1,(L"phone mapping thread Exception!\n"));
		}
		return 1;
}



char * getEventName(int n);

void InBtEnterSetSrcBTMusic();
void restoreScreen0(HANDLE *handOut){ 
	/*
	int toActScrnNo=SCRN_MAIN1,sub=-1;
	int inGpsFlag;
	int nMetaType=-1;
	int metaSrcType=-1;

	/*DWORD rsState=callIRDWorkData(QUERY_RESULT_STATE,0);
	if((rsState&1)&&beFirstRestore){
		// 从RESET中启动，不恢复.	
		if(exists(SCREEN_FILE)){
			DeleteFile(SCREEN_FILE);
		}
		beFirstRestore=FALSE;
		return;
	}* /
	HANDLE hHandle= openReadinPropFile(SCREEN_FILE);
	if(hHandle==INVALID_HANDLE_VALUE){//FIRST B+		
		if(1)
		{
			toActScrnNo=SCRN_RADIO;
			nMetaType=VOL_RADIO;
			metaSrcType=SRC_RADIO;
			oldMetaSrcType=SRC_RADIO;
		}
		TO_SCRN_EX_ASY(SCRN_RADIO);
		return;
	}
	*handOut=hHandle;
	DWORD readed;
	{
		char buffer[1000];
		ReadFile(hHandle,buffer,sizeof(buffer)-1,&readed,0);
		buffer[readed]=0;
		TCHAR buff[1000];
		sscanf(buffer,format,&toActScrnNo,&sub,&inGpsFlag,&nMetaType,&metaSrcType,&isGpsRunBack);		
	}
	CloseHandle(hHandle);
	*handOut=INVALID_HANDLE_VALUE;
	RETAILMSG(1,(L"[RESTORE ScrnNo=%d,inGps=%d,isGpsRunBack=%d\r\n",toActScrnNo,inGpsFlag,isGpsRunBack));
	isGpsRunBack=0;
	int mediaScrnNo=SCRN_MAIN1;
	int mediaDev = -1;
	int mediaPlaySta = -1;
	int gUiSta_t =0;
	restoreMedia0(&mediaScrnNo,&mediaDev,&mediaPlaySta,&gUiSta_t);
	//isGpsRunBack=1;
	if(inGpsFlag||isGpsRunBack){//添加gps在后台运行的处理
		//addDelayTask(runGPSresotre,4000);
		if(inGpsFlag){
			isGpsRunBack=0;
		}
		//addDelayTask(runGPSresotre,3000);
	}else{
		bool isRunGpsAtStartUp();	
		if(isRunGpsAtStartUp()){
			void runGpsIn(DWORD d);
			if(toActScrnNo!=SCRN_PowerOFF){
				//addDelayTask(runGpsIn,5000);
			}
		}
	}
	///////////  ???? 2017-07-22 toActScrnNo
	//toActScrnNo=SCRN_BT_MUSIC;
	//switch(toActScrnNo)
	{
		case SCRN_RADIO:
		case SCRN_RADIOLIST:
			oldMetaSrcType=SRC_RADIO;
			TO_SCRN_EX_ASY(SCRN_RADIO);
			break;
		case SCRN_MAIN1:
			switch(nMetaType){
				case VOL_RADIO:
					openRadioGlobal();
					break;
				case VOL_BT_MUSIC:
					InBtEnterSetSrcBTMusic();
					TO_SCRN_EX_ASY(SCRN_MAIN1);							
					break;
			}
			break;

		/*case SCRN_DVP_DVD1:
		case SCRN_DVP_DVD2:
		case SCRN_DVP_FS:
		case SCRN_DVP_VCD:
		case SCRN_DVP图片:
		case SCRN_LOAD_PROCESS:
			 void RecoverDvdPlay();
			 if(!tellBootExitRearview){
				addDelayTask((V_CALL_ID)RecoverDvdPlay,3000);
			 }
			break;* /
		case SCRN_MEDIA_SRC:
		case SCRN_MEDIA_VIDEO_LIST:
		case SCRN_MEDIA_VIDEO:
		case SCRN_VIDEO_FULL:
		case SCRN_AUDIO_LIST:
		case SCRN_MEDIA_AUDIO:
		case SCRN_PIC_LIST:
		case SCRN_PIC_MAIN:
		case SCRN_PIC_FULL:
			if(!tellBootExitRearview){
				
				{
					if(toActScrnNo==mediaScrnNo){
						if(mediaPlaySta==TRUE){											
							//CreateThread( NULL,0,restorePlayThread,(LPVOID)mediaDev,0,0);       
						}
					}
				}				
			}
			break;
			case SCRN_BT_MUSIC:
			case SCRN_BT_DIAL:
			case SCRN_BT_RECORD:
			case SCRN_BT_BOOK:
			case SCRN_BT_PAIR:
			case SCRN_BT_SET:
			case SCRN_BT_OPTION:
				RETAILMSG(1,(L"[ACC ON]>>To Recovery BT Source!"));
				InBtEnterSetSrcBTMusic();
				TO_SCRN(toActScrnNo);
			break;
		default:
			break;
	}

	if(exists(SCREEN_FILE)){
//		DeleteFile(SCREEN_FILE);
	}
	*/
}
bool existDebugGps();

int seh_filer(int code,struct _EXCEPTION_POINTERS *infor,int module);


void restoreScreen(){
	if(beEnterBack()){		
		return;
	}
	HANDLE handOut;
	try
	{
		restoreScreen0(&handOut);
	}
	catch(...)
	{		
		if(handOut!=INVALID_HANDLE_VALUE){
			CloseHandle(handOut);
		}
	}
}

int getMetaSrcType();
int getSCRN_屏幕调节BackScrn();
extern int lastEnterScrnNo; 
void saveScreen0(){
#ifdef WINCE 
	/*if(beBeginGps){
		isGpsRunBack=1;
	}else{
		isGpsRunBack=0;
	}*/
	isGpsRunBack=0;
	void saveControlDataAndClear();
	saveControlDataAndClear();
	//void saveRadioWhenPowerOff();
	//saveRadioWhenPowerOff();
	HANDLE hHandle= createWriteOutPropFile(SCREEN_FILE);
	RETAILMSG_DC(0,(L"WriteFile0 saveScreen0\r\n"));
	if(hHandle==INVALID_HANDLE_VALUE){
		return;
	}
	try
	{
		DWORD writed;
		char buffer[1000];
		if(actScrnNo==SCRN_屏幕调节){//20160109
			actScrnNo=getSCRN_屏幕调节BackScrn();
		}
		
		switch(actScrnNo){
			case SCRN_RADIO:
			case SCRN_RADIOLIST:
				isGpsRunBack=0;
				sprintf(buffer,format,actScrnNo,0,inGps,willData.nMetaSource,getMetaSrcType(),isGpsRunBack);
				break;
			case SCRN_BT_MUSIC:
			case SCRN_BT_DIAL:
			case SCRN_BT_RECORD:
			case SCRN_BT_BOOK:
			case SCRN_BT_PAIR:
			case SCRN_BT_SET:
			case SCRN_BT_OPTION:
				isGpsRunBack=0;
				sprintf(buffer,format,actScrnNo,0,inGps,getSrcType(),isGpsRunBack);
				break;
			case SCRN_MEDIA_SRC:
			case SCRN_MEDIA_VIDEO_LIST:
			case SCRN_MEDIA_VIDEO:
			case SCRN_VIDEO_FULL:
			case SCRN_AUDIO_LIST:
			case SCRN_MEDIA_AUDIO:
			case SCRN_PIC_LIST:
			case SCRN_PIC_MAIN:
			case SCRN_PIC_FULL:
				isGpsRunBack=0;
				sprintf(buffer,format,actScrnNo,cmd8202State.getMetaData(),inGps,willData.nMetaSource,getMetaSrcType(),isGpsRunBack);
				break;			
			case SCRN_NullScreen:
				isGpsRunBack=0;
				sprintf(buffer,format,actScrnNo,getNullScreenType(),inGps,willData.nMetaSource,getMetaSrcType(),isGpsRunBack);
				break;
			default:
				{
					isGpsRunBack=0;
					sprintf(buffer,format,SCRN_MAIN1,cmd8202State.getMetaData()
						,inGps,willData.nMetaSource,getMetaSrcType(),isGpsRunBack);
				}
				break;
		}
		WriteFile(hHandle,buffer,strlen(buffer),&writed,0);
		RETAILMSG(1,(L"[ScrnNo=%d,inGps=%d,isGpsRunBack=%d\r\n",actScrnNo,inGps,isGpsRunBack));
	}
	catch(...)
	{
		
		RETAILMSG_DC(0,(L" saveScreen0 MEE A EXCEPTION \r\n"));
	}
	CloseHandle(hHandle);
#endif
}

void saveMedia0(){
	FILE* fp= createWriteOutPropFile(MEDIA_FILE);
	RETAILMSG_DC(0,(L"WriteFile saveMedia\r\n"));
	if(fp==NULL){
		return;
	}
	/*
	try
	{
		DWORD writed;
		char buffer[1000];
		if(actScrnNo==SCRN_屏幕调节){//20160109
			actScrnNo=getSCRN_屏幕调节BackScrn();
		}
		if(actScrnNo==SCRN_音频调节||actScrnNo==SCRN_平衡设置){
			if(lastEnterScrnNo!=-1){
				actScrnNo=lastEnterScrnNo;
			}
		}
		switch(actScrnNo){
			case SCRN_MEDIA_SRC:
			case SCRN_MEDIA_VIDEO_LIST:
			case SCRN_MEDIA_VIDEO:
			case SCRN_VIDEO_FULL:
			case SCRN_AUDIO_LIST:
			case SCRN_MEDIA_AUDIO:
			case SCRN_PIC_LIST:
			case SCRN_PIC_MAIN:
			case SCRN_PIC_FULL:
			//case SCRN_MEDIA_PIC:
			//case SCRN_MEDIA:
			//case SCRN_音乐播放://多加个变量判断 SCRN_音乐播放 SCRN_DVP文件列表 是CDDA SDUSB 刻录碟共用 需判断类型
			//case SCRN_DVP文件列表://屏幕号 设备类型 是否播放
//				sprintf(buffer,format_sdusb,actScrnNo,iDeviceType,IS_SD_USB_File_Played,g_UIEventCon);
				saveMediaPlayInfo();
				break;
			default:
				{
					sprintf(buffer,format_sdusb,SCRN_MAIN1,0,0);
				}
				break;
		}
		WriteFile(hHandle,buffer,strlen(buffer),&writed,0);
	}
	catch(...)
	{
		
		RETAILMSG_DC(0,(L" saveScreen0 MEE A EXCEPTION \r\n"));
	}
	CloseHandle(hHandle);
	*/
}

extern bool softPowerOffStat ;
void saveScreen(){
	try
	{
		if(softPowerOffStat){
			return;
		}
		saveScreen0();
		saveMedia0();//sd usb 存储
		/*if(UI_START!=g_UIEventCon){
			ReadDataFromDramCb();//dvd存储
		}*/
	}
	catch(...)
	{
		
		RETAILMSG_DC(0,(L" saveScreen0 MEE A EXCEPTION \r\n"));
	}
}

int executeSTM8IC0_uart(DWORD cmd,unsigned char b0,unsigned char b1,int loopTimes);

void sysHardMute();

BOOL beAccOffTest=0;
BOOL accWillBeOff=0;

void accOffAction(){
	RETAILMSG_DC(0,(L"ACC OFF XX\r\n"));
	beAccOffTest=1;
	power6410Off();
	void closeGPSHandle();
	//closeGPSHandle();
	//Sleep(2000);// 等待所有任务执行完成
//	OffOk();
	willData.isAccOn=false;
	willData.beServiceCanRun=false;
	/** 书写一次的界面和播放源 */
}

void accOffsendBackMcu();
int dealAccOnOff(LPARAM lParam){
	if(lParam==ACC_OFF){		
		accOffsendBackMcu();
		return 1;
	}
	return 0;
}

int executeSTM8Cmd(DWORD cmd,unsigned char b0,unsigned b1);



void executeSTM8Force(DWORD cmd,unsigned char b0,unsigned char b1){
	for(int i=0;i<100;i++){
		if(executeSTM8Cmd(cmd,b0,b1)==0){
			return;
		}
		Sleep(100);
	}
}


void accOnAction(){
	RETAILMSG_DC(0,(L"ACC ON XX \r\n"));
//		post6450CtlCmd(RESTORE_LIGHT,0,0,0);
	willData.beServiceCanRun=false;
	void setMuteFlagTrue();
	//setMuteFlagTrue();

	
	//Sleep(100);// 等待静音起作用
	
	//muteAll_GPH2_arm11_proxy();
	
	//executeARM11_CMD(CMD_muteAll_GPH2_arm11);();
	
	Sleep(100);//等待静音启作用
	
	//if(!existDebug())
//	executeSTM8Force(POWER_MAIN_OFF,0,0);// 已经有了
	willData.setPoweredMainOn(false);
	// 已经执行了 POWER_MAIN_OFF 
	accOnOk();
	willData.isAccOn=true;
	// willData.beServiceCanRun=false; 服务后面在开启
	// 服务只能启动一次
	void closeVolMuteWindow();// 必须要加上
	closeVolMuteWindow();
	void startSstartGpsBtService();
	//startSstartGpsBtService();//

	
	willData.setPoweredMainOn(true);
	
	Sleep(100);// 等待电压稳定
	willData.beServiceCanRun=true;
	
	if(!willData.bePoweredOffByUser)
		power6410On(false);

	RE_DRAW;
	//restoreScreen();
	//需要恢复
	//muteOff();
	//void muteOpenFlag();
	//muteOpenFlag();
	//willData.setMute(false);
#ifdef HAVE_CAN_BUS
	void maySendPowerOnCanMessage();
	//maySendPowerOnCanMessage();
#endif
		if(!willData.bePoweredOffByUser)
		willData.setMute(false);// 最后打开声音
}



bool isVolTunEvent(LPARAM lParam){
	return false;
}
void dealKeyEventInBack(LPARAM lParam){
	switch(int(lParam))
	{
		case FXP_MUTE:
		case K_MUTE:
			if(isNowCalling()){
				//_F_挂断_new();
			}					
			break;

		case FXP_MODE:
		case K_BLUETOOTH:
			if(isNowCalling()){
				//_F_接听_拨打_new();
			}
			break;

		case K_VOL_UP:
		case FXP_VOL_ADD:
			turnUp();
			break;

		case K_VOL_DN:
		case FXP_VOL_SUB:
			turnDown();
			break;
	}	
}

LPARAM translateFxp(LPARAM l){

	if(IS_IN_FXP_SHE_ZHI)
		return l;
	if(IS_FXP_KEY(l))
		return getFxpKey(l);
	return l;
}



bool isPowerLongPressed=false;
long lLongPowerLongPressed=0;
int resetLefeCount=0;

#define MAX_LEAVE_VALUE	7

void tryResetCSRGps();

void reportPowerTime(int n){
	ZString zs;
	zs.format("继续长按 SRC 系统将重新启动(%d)",n);
	report(zs);
	if(n==0){
		willData.setPoweredMainOn(false);
	}

}

void checkPowerLongPressed(){
	if(1)
		return;
	if(!isPowerLongPressed)
		return;
	if(GetTickCount()-lLongPowerLongPressed>1000){
		beepDirect();
		resetLefeCount--;
		char buffer[1000];
		reportPowerTime(resetLefeCount);
		lLongPowerLongPressed=GetTickCount();
	}
}


BOOL dealPubRemoteKey(LPARAM lParam){
	
	return false;
}



void toPlayDvd();
void callEq();
void callToRadio();
void callToBt();
void toRadioForceFmOrAm(unsigned key);


#include "uartservice.h"
bool isNowCalling();
/*
FXP_MAP fxpMap[MAX_KEY]={
	{0xff,0xff,0,T_PREV},			{0xff,0xff,0,K_MUTE},				{0xff,0xff,0,T_NEXT},
	{0xff,0xff,0,K_VOL_UP},		{0xff,0xff,0,K_POWER},			{0xff,0xff,0,K_VOL_DN},
	{0xff,0xff,0,K_PHONE_ON},	{0xff,0xff,0,K_SOURCE_MODE},{0xff,0xff,0,K_PHONE_OFF},
	{0xff,0xff,0,K_EQ},				{0xff,0xff,0,K_ENTER},			{0xff,0xff,0,K_RETURN},
	{0xff,0xff,0,K_TUNER},		{0xff,0xff,0,K_NAVI},				{0xff,0xff,0,K_DVD},
};
*/

void enterDestnationScrn(ZString& scrnNo,ZString destNo){
}
void FXP_EQ_FUN(){
	if(SCRN_音频调节!=actScrnNo){
		mayCloseVi();
		enterDestnationScrn(actScrnNo,SCRN_音频调节);
	}
}

void R102_EQ_FUN(){

}
void FXP_CLOCK_FUN(){
	if(SCRN_时间调整!=actScrnNo){
		mayCloseVi();
		enterDestnationScrn(actScrnNo,SCRN_时间调整);
	}
}

void FXP_SETUP_FUN(){
	if(SCRN_参数设置!=actScrnNo){
		mayCloseVi();
		enterDestnationScrn(actScrnNo,SCRN_参数设置);
	}
}

void FXP_SYSINFO_FUN(){
	if(SCRN_TXTSHOW!=actScrnNo){
		mayCloseVi();
		enterDestnationScrn(actScrnNo,SCRN_TXTSHOW);
	}
}

void _F_PLAY_PAUSE();
void FXP_PLAY_PAUSE(){
	

}
unsigned char LastRadioKey=0;
void FXP_MODE_FUN(){
	/*if(nCurrentTurn!=TURN_NULL){
		startNextTurn();// 下一个调整内容
	}else{
		exchangeToNextSource();
	}*/
	exchangeToNextSource();
}

bool isMediaPlaying(){
	return false;
}
void FXP_PREV_FUN(LPARAM lParam){
	if(VOL_RADIO==willData.nMetaSource){
		if(LastRadioKey==T_FASTB){
			LastRadioKey=0;
			return;
		}
		/*if(T_PREV==lParam){
			const unsigned char cmdData[]={T_RADIO_PRESET_PRE,0,0,0,0};
			executeSTM8Cmdnew(CMD_CMD_TO_MCU,sizeof(cmdData),cmdData);	
		}else{
			const unsigned char cmdData[]={T_RADIO_TUNE_DOWN,0,0,0,0};
			executeSTM8Cmdnew(CMD_CMD_TO_MCU,sizeof(cmdData),cmdData);			
		}*/
		const unsigned char cmdData[]={T_RADIO_SEEK_DOWN,0,0,0,0};
		executeSTM8Cmdnew(CMD_CMD_TO_MCU,sizeof(cmdData),cmdData);
	}else if(VOL_BT_MUSIC==willData.nMetaSource){
		void _F_PREV_new();		
		//_F_PREV_new();
	}else{//DVD USB SD
		if(isMediaPlaying()
			&&actScrnNo==SCRN_PIC_FULL/*mediaCon.iPicMeidaType==CUR_IS_PIC*/){//sd usb 图片单独处理
			//mediaCon._F_PicPrev();
		}else if(isMediaPlaying()){
			//mediaCon._F_MediaPrev();
		}else{

		}
	}
}

void FXP_NEXT_FUN(LPARAM lParam){
	if(VOL_RADIO==willData.nMetaSource){
		if(LastRadioKey==T_FASTF){
			LastRadioKey=0;
			return;
		}
		/*if(T_NEXT==lParam){
			const unsigned char cmdData[]={T_RADIO_PRESET_NEXT,0,0,0,0};
			executeSTM8Cmdnew(CMD_CMD_TO_MCU,sizeof(cmdData),cmdData);
		}else{
			const unsigned char cmdData[]={T_RADIO_TUNE_UP,0,0,0,0};
			executeSTM8Cmdnew(CMD_CMD_TO_MCU,sizeof(cmdData),cmdData);			
		}*/
		const unsigned char cmdData[]={T_RADIO_SEEK_UP,0,0,0,0};
		executeSTM8Cmdnew(CMD_CMD_TO_MCU,sizeof(cmdData),cmdData); 
	}else if(VOL_BT_MUSIC==willData.nMetaSource){
		void _F_NEXT_new();
		//_F_NEXT_new();
	}else{//DVD USB SD
		
		if(isMediaPlaying()&&actScrnNo==SCRN_PIC_FULL/*mediaCon.iPicMeidaType==CUR_IS_PIC*/){//sd usb 图片单独处理
			//mediaCon._F_PicNext();
		}else if(isMediaPlaying()){
			//mediaCon._F_MediaNext();
		}else{

		}
	}
}

void FXP_POWER_FUN(){
	const unsigned char cmdData[]={K_POWER,0,0,0,0};//K_POWER
	executeSTM8Cmdnew(CMD_CMD_TO_MCU,sizeof(cmdData),cmdData);
}

bool isCanOprationScreen(ZString scrnnum){
	if(scrnnum==actScrnNo){
		return true;
	}else{
		return false;
	}
}
void Can_APSkey(){
	if(isCanOprationScreen(SCRN_收音机2)){
		if(VOL_RADIO==willData.nMetaSource){
			const unsigned char cmdData[]={T_RADIO_AS,1,0,0,0};//带参APS_STORE-1  SCAN-0
			executeSTM8Cmdnew(CMD_CMD_TO_MCU,sizeof(cmdData),cmdData);
		}
	}
}
extern bool showGPS配置提示ThisTime;


void playFromUsbDevice();
void closeOrOpenScreen();
void can_runNAVI(){
	if(!inGps){
		showGPS配置提示ThisTime=true;
		runGPS();
	}else{
		showZHWConsol(false);
	}	
}

bool isScreenClosedWhenAccOff=0;

LPARAM lLastParam=0;
bool dealKeyTelR102(){
	return 1;
}
bool restoreOldScreenBeforeBt();
void saveOldScreenBeforeBt(int nScreen);

//void updateMapTopWindow();

void KEY_NAVI_FUN(){
	if(!isNowCalling()){
		
		{
			if(!inGps){
				runGPS();
			}else{
				showZHWConsol(false);
			}	
		}		
	}			
}

bool quickAccOff = false;
bool dealKeyEvent(LPARAM lParam){
	lParam=translateFxp(lParam);

	if(dealPubRemoteKey(lParam)){
		return true;
	}


	if(lLastParam==lParam){
		if(lParam==K_CLOSE_SCREEN_WHEN_ACC
			||lParam==K_OPEN_SCREEN_WHEN_ACC_ON){
			return true;
		}
	}
	lLastParam=lParam;
	if(willData.isClosedScreen()){
		if(!(lParam==K_CLOSE_SCREEN_WHEN_ACC
			||lParam==K_OPEN_SCREEN_WHEN_ACC_ON)){
			willData.setCloseScreen(false);
			return true;
		}
	}

	if(isKeyEvent(lParam)){				
		switch(lParam){	
			case K_CLOSE_SCREEN_WHEN_ACC:
				quickAccOff=true;
				isScreenClosedWhenAccOff=willData.isClosedScreen();
				willData.setCloseScreenAcc(true);
//				sendAutoNaviAccOff();
				break;		

			case K_OPEN_SCREEN_WHEN_ACC_ON:
				quickAccOff=false;
				if(isScreenClosedWhenAccOff){
					willData.setCloseScreen(true);
				}else{
					willData.setCloseScreen(false);
				}
				break;
		}
	}
	if(quickAccOff){
		return true;
	}
	if(isKeyEvent(lParam)){		
		if(!dealSUB_PLUS(lParam))
		switch(lParam){			
			case K_TOUCH_MENU:
				if(inXiuDing){
					showZHWConsol(false);
					inXiuDing=0;
				}else{
					if(!inGps
						&&actScrnNo!=SCRN_MEDIA_VIDEO
						&&actScrnNo!=SCRN_VIDEO_FULL
						&&actScrnNo!=SCRN_DVR_START
						&&actScrnNo!=SCRN_DVR_LIST
						&&actScrnNo!=SCRN_DVR_PLAY
						&&actScrnNo!=SCRN_DVR_FULL){					
						runPingMuXiuding();
						inXiuDing=1;
					}
				}			
				break;
			case K_NAVI:
				#ifdef R102_LOW_VER
					#ifdef BK09_LOW_VER
					R102_EQ_FUN();
					#else
					KEY_NAVI_FUN();
					#endif	
				#else
					 KEY_NAVI_FUN();
				#endif										
				break;
			case K_BACKLIGHT_STATE:
				if(!willData.isClosedScreen()){
					willData.setCloseScreen(true);
				}
				break;

			case K_CLOSE_SCREEN_WHEN_ACC:
				isScreenClosedWhenAccOff=willData.isClosedScreen();
				//willData.setCloseScreen(true);
				willData.setCloseScreenAcc(true);
//				sendAutoNaviAccOff();
				break;		

			case K_OPEN_SCREEN_WHEN_ACC_ON:
				if(isScreenClosedWhenAccOff){
					willData.setCloseScreen(true);
				}else{
					willData.setCloseScreen(false);
				}
				break;
			case K_SOURCE_HOME:	
				/*void openCarlifeAudioImmedia();						
				openCarlifeAudioImmedia();
				willData.markVolChanged();*/
				if(!isNowCalling()){
					toMainMenu();
				}
				break;
			case K_MUTE:
				/*void closeCarlifeAudioImmedia();	
				closeCarlifeAudioImmedia();	
				willData.markVolChanged();*/
				if(isNowCalling()){
					//_F_挂断_new();
				}else{
					exchangeMute();								
				}			
				break;

			case K_MP5:
				if(inGps){
					showZHWConsol(false);
				}
				//playFromUsbDevice();
				break;
			case T_KEY_DISP:
				closeOrOpenScreen();
				//exchangeMute();
				break;
			case K_RETURN:
				if(!isNowCalling()){
					//toMainMenu();
					dealF42SBackButton();
				}
				break;
			case T_RADIO_PS://搜台 并存储
				//void can_scarn();
				//can_scarn();
				if(VOL_RADIO==willData.nMetaSource){
					const unsigned char cmdData[]={T_RADIO_AS,1,0,0,0};//带参APS_STORE-1  SCAN-0
					executeSTM8Cmdnew(CMD_CMD_TO_MCU,sizeof(cmdData),cmdData);
				}
				break;
			case K_EJECT:
				//等待光盘停止 然后返回K_EJECT按键
				void dvdEject();
				dvdEject();
				break;


			case T_PREV://
				FXP_PREV_FUN(lParam);
				break;

			case T_FASTB://prev 长按
				if(VOL_RADIO==willData.nMetaSource){
					LastRadioKey=T_FASTB;
					/*const unsigned char cmdData[]={T_RADIO_SEEK_DOWN,0,0,0,0};
					executeSTM8Cmdnew(CMD_CMD_TO_MCU,sizeof(cmdData),cmdData);	*/
					//const unsigned char cmdData[]={T_RADIO_TUNE_DOWN,0,0,0,0};
					//executeSTM8Cmdnew(CMD_CMD_TO_MCU,sizeof(cmdData),cmdData);						
				}else{//快退
					
				}
				break;

			case T_NEXT:
				FXP_NEXT_FUN(lParam);
				break;

			case T_FASTF://next 长按
				if(VOL_RADIO==willData.nMetaSource){
					LastRadioKey=T_FASTF;
					/*const unsigned char cmdData[]={T_RADIO_SEEK_UP,0,0,0,0};
					executeSTM8Cmdnew(CMD_CMD_TO_MCU,sizeof(cmdData),cmdData);*/ 
					const unsigned char cmdData[]={T_RADIO_TUNE_UP,0,0,0,0};
					executeSTM8Cmdnew(CMD_CMD_TO_MCU,sizeof(cmdData),cmdData);					
				}else{//快进
					
				}
				break;

			

			case K_PHONE_ON:
				//void _F_接听_拨打_new();
				//_F_接听_拨打_new();
				break;
			case K_PHONE_OFF:
				void _F_挂断_new();
				//_F_挂断_new();
				break;
			case K_SOURCE_MODE:	
				if(isNowCalling()){
//					_F_接听_拨打_new();
				}else{
					exchangeToNextSource();					
				}				
				break;
			case T_PLAY:
				FXP_PLAY_PAUSE();
				break;
			case K_EQ:	
				FXP_EQ_FUN();
				break;
			case K_CLOCK:	
				FXP_CLOCK_FUN();
				break;
			/*case T_CAMERA_RECORD://disp全景却换
				if(isNowCalling()){
					break;
				}else{
					void sendQiJunVedioExchange();
					sendQiJunVedioExchange();
				}			
				break;*/
			case K_TUNER:
				if(inGps){
					showZHWConsol(false);
				}
				if(setSource(SRC_RADIO)){
					TO_SCRN_EX_ASY(ZString(SCRN_收音机2));
				}
				break;
			case K_DVD:
				if(inGps){
					showZHWConsol(false);
				}
				//cmd8202State.setMetaTypeForAll(META_DISC,false);
				void RecoverDvdPlay();
				//RecoverDvdPlay();//yh 方控DVD按键
				break;
			case K_POWER:
			case K_ENTER:			
				break;

			//2014-12-1
			case K_BLUETOOTH:
				if(inGps){
					showZHWConsol(false);
				}
				void ShutDownCarLifeVol();
				if(isCarLifeTrsfByBT()){
//					if(carlifeLinkDevType==CL_CONNECT_DEVICE_ANDROID){
//						ShutDownCarLifeVol();
//					}									
				}
				
				if(!dealKeyTelR102()){
					if(actScrnNo!=SCRN_BT_DIAL){
						if((actScrnNo!= SCRN_AVIN2)/*&&setSource(SRC_BT)*/){
							void InBtEnterSetSrcBTMusic();
							InBtEnterSetSrcBTMusic();
							TO_SCRN_EX_ASY(ZString(SCRN_BT_DIAL));	
						}
					}
				}								
				break;

			case T_RADIO_BAND:
				void BandAmFm();	
				if(actScrnNo==SCRN_RADIO||actScrnNo==SCRN_RADIOLIST){
					if(inGps){
						showZHWConsol(false);
						break;
					}
					//BandAmFm();
				}else{
					if(inGps){
						showZHWConsol(false);						
					}
					if(setSource(SRC_RADIO)){
						TO_SCRN_EX_ASY(ZString(SCRN_RADIO));
					}		
				}				
				break;
			case T_RADIO_AS:
				if(VOL_RADIO==willData.nMetaSource){
					const unsigned char cmdData[]={T_RADIO_AS,1,0,0,0};//带参APS_STORE-1  SCAN-0
					executeSTM8Cmdnew(CMD_CMD_TO_MCU,sizeof(cmdData),cmdData);
				}
				break;
		}
	}else{
		switch(lParam){

			case FXP_MUTE:
				if(isNowCalling()){
//					_F_挂断_new();
				}else{
					exchangeMute();
				}				
				RE_DRAW;
				break;
			case FXP_MODE:
				if(isNowCalling()){
//					_F_接听_拨打_new();
				}else{
					FXP_MODE_FUN();
				}
				break;
			case FXP_RADIO:
				if(inGps){
					showZHWConsol(false);
				}
				TO_SCRN_EX_ASY(ZString(SCRN_收音机2));
				break;
			case FXP_CALL_TEL:
				 _F_接听_拨打_C();
				break;
			case FXP_CANCEL_TEL:
				_F_挂断_C();
				break;
			case FXP_GPS:
				if(!inGps){
					showGPS配置提示ThisTime=true;
					runGPS();
				}else{
					showZHWConsol(false);
				}
				break;
			case FXP_DVD:
				if(inGps){
					showZHWConsol(false);
				}
				break;
			case FXP_VOL_SUB:
				turnDown();
				break;
			case FXP_VOL_ADD:
				turnUp();
				break;
			case FXP_POWER:
				FXP_POWER_FUN();
				break;			
		}
	}
	return false;
}




unsigned char fxpValue[4]={255,255,255,255};

LPARAM getFxpKey(LPARAM lParamFxpKey);
LPARAM getFxpKey_Repeat(LPARAM lParamFxpKey);

void dealFxpKeySTM80_R(unsigned char hightValue,unsigned char lowValue,int offSet){
		int loc=0;
		if(offSet>0){
			loc=2;;
		}
		UINT32 currentKeyHight=(hightValue+offSet)|FANGXPAN_BASE;
		UINT32 currentKeyLow=(lowValue+offSet)|FANGXPAN_BASE;
		LPARAM l=(currentKeyHight<<16)|currentKeyLow;
		if(hightValue!=0XFF&&lowValue!=0XFF){
			hightValue=hightValue;
		}
		//LPARAM lTran=getFxpKey_Repeat(l);
		
}



void dealFxpKeySTM80(unsigned char hightValue,unsigned char lowValue,int offSet){
	//if(hightValue>240){
		//*lastKey=-1;
	//}else
	{
		//lowValue>>=1;
		//hightValue>>=1;
		int loc=0;
		if(offSet>0){
			loc=2;;
		}
		UINT32 currentKeyHight=(hightValue+offSet)|FANGXPAN_BASE;
		UINT32 currentKeyLow=(lowValue+offSet)|FANGXPAN_BASE;
		fxpValue[loc]=hightValue;
		fxpValue[loc+1]=lowValue;
		if(actScrnNo==SCRN_方向盘设置){
			//if(GetTickCount()-dLastUpdateTime>500)
			{
				//dLastUpdateTime=GetTickCount();
				RE_DRAW;
			}
		}

		/*
		if(loc==0){
			//pushNewValue0(hightValue,lowValue,0);
		}else{
			pushNewValue0(hightValue,lowValue,1);
		}
		//if(abs(*lastKey-currentKey1)<3){
			// SEND MSG
		if(actScrnNo==SCRN_方向盘设置){
			if(GetTickCount()-dLastUpdateTime>500){
				dLastUpdateTime=GetTickCount();
				RE_DRAW;
			}
		}
		//*/
		//RETAILMSG_DC(0,(L"no(%d)= (currentKeyHight<<16)|currentKeyLow");
		if(actScrnNo==SCRN_方向盘设置){
			PostMessageZhw(MSG_KEY_EVENT,(currentKeyHight<<16)|currentKeyLow);		
		}else{
			RETAILMSG_DC(0,(L"no(%08X)=",(currentKeyHight<<16)|currentKeyLow));
			LPARAM l=(currentKeyHight<<16)|currentKeyLow;
			LPARAM lTran=getFxpKey(l);
			if(lTran!=NULL_KEY){
				PostMessageZhw(MSG_KEY_EVENT,lTran);		
			}
		}
	}

}
