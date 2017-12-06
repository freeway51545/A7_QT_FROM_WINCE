#include "pub.h"
#include "msg.h"
#include "pub.h"
#include "stdio.h"
#include "stdlib.h"

int sendShowWindowCMD(DWORD cmd);
bool isNowBTCalling();
ControlData workData;
ControlData willData;

bool ControlData::isVolChanged(){
	return beVolChange;
}
void ControlData::setSearchMute(bool muteSet){
		beSearchMute=muteSet;
		markVolChanged();
	}

void ControlData::setBeDrawClock(bool b){
	beDrawClock=b;
	markContrlDataChanged();
}
void ControlData::setBePoweredOffByUser(bool b){
	bePoweredOffByUser=b;
	markContrlDataChanged();
	//markVolChanged();
}


void ControlData::setVolByScrn(int n){
	setVol(n);
}

int  ControlData::getVolByScrn(){
	return getVol();
}

int ControlData::getBright(){
	if(beEnterBack()){
		return backBright;
	}else{
		return bright;
	}
}

void ControlData::setBright(int brightSet){
	if(brightSet<1)
		brightSet=1;
	if(brightSet>=MAX_BRIGHT)
		brightSet=MAX_BRIGHT;
		if(beEnterBack()){
			backBright=brightSet;
		}else{
			bright=brightSet;
		}
		beChangedBright=true;
		markContrlDataChanged();
	}

void ControlData::startSmallVol(){
	lastVol=SMALL_VOL;
}
int ControlData::getTrueVol(){
	return lastVol;
}

void reSendVolume(){
	willData.markVolChanged();
}

void ControlData::markVolChanged(){
	beVolChange=true;
}

void ControlData::setDVDMute(bool b){
	beDvdMute=b;
	markVolChanged();
}

void ControlData::setBtInCalling(bool bCalingFlag){
	if(btInCalling!=bCalingFlag){
		btInCalling=bCalingFlag;
		RETAILMSG_DC(1,(L"set setBtInCalling %d \r\n",bCalingFlag));
		markVolChanged();
	}
}



void ControlData::setIisInOutputing(bool b){
	/* */
	if(!b){
		iisInOutputingTime=GetTickCount();
	}else{
		iisInOutputingTime=0;
	}
	/* */
	iisInOutputing=b;
	if(iisInOutputing){
		beLastIIsTime=GetTickCount();
		if(IsHaveCalling&&iisInOutputing){
			// 进行猜测
			if(!猜测IIS来电结果){
				if(GetTickCount()-beLastComingCallTime<4000){
					猜测IIS来电结果=true;
					RETAILMSG_DC(1,(L"GUST COMING CALL IS IIS \r\n"));
				}
			}
		}
	}
	if(iisInOutputing){
		//closeCarlifeAudio();
//		closeCarlifeAudioImmedia();		//这里要用sendmessage
	}else{
		//openCarlifeAudio();
//		openCarlifeAudioImmedia();
	}
	markVolChanged();
}

#define 蓝牙_DELAY_TIME	2000
void ControlData::setIsHaveCalling(bool b){
	IsHaveCalling=b;
	if(IsHaveCalling){
		beLastComingCallTime=GetTickCount();//
		if(beLastComingCallTime>beLastIIsTime){
			if(beLastComingCallTime-beLastIIsTime<4000){
				猜测IIS来电结果=true;
				RETAILMSG_DC(1,(L"GUST COMING CALL IS IIS TRUE\r\n"));
			}else{
				猜测IIS来电结果=false;
				RETAILMSG_DC(1,(L"GUST COMING CALL IS IIS FALSE\r\n"));
			}
		}
	}
	markVolChanged();
}

BOOL ControlData::get猜猜是IIS来电铃声(){
	if(!willData.IsHaveCalling)
		return false;
	if(willData.IsInTalking)
		return false;
	if(willData.IsTelDialing)
		return false;
	return 猜测IIS来电结果;
}

bool ControlData::isIisInOutputing(){
	return iisInOutputing;
}


void ControlData::setMuteNew(bool muteSet){//2016/09/20
	static long lLastSetMuteTime=0;
	beMute=muteSet;
	markVolChanged();
	if(!muteSet){
		if(GetTickCount()-lLastSetMuteTime>1*1000){
			lastVol=SMALL_VOL;// 声音逐渐增加
			if(lastVol<getVol()){
				lastVol=getVol()-2;
			}
			if(lastVol<0)
				lastVol=0;
		}
		void muteOff();
		muteOff();//2014-12-12 muteoff后没按键音
	}
	if(muteSet){
		lLastSetMuteTime=GetTickCount();
	}
	RE_DRAW;
}

void ControlData::setMute(bool muteSet){
static long lLastSetMuteTime=0;
		beMute=muteSet;
		markVolChanged();
		if(!muteSet){
			if(GetTickCount()-lLastSetMuteTime>1*1000){
				lastVol=SMALL_VOL;// 声音逐渐增加
				if(lastVol<getVol()){
					lastVol=getVol()-2;
				}
				if(lastVol<0)
					lastVol=0;
			}
			void muteOff();
			muteOff();//2014-12-12 muteoff后没按键音
		}
		if(muteSet){
			lLastSetMuteTime=GetTickCount();
		}
		RE_DRAW;
}


int ControlData::getVol(){
		// 根据不同的声音源设置声音
	if(isNowBTCalling()){		
		return vol[VOL_BT];
	}else{
		if(nVolumeType>=0&&nVolumeType<sizeof(vol)/sizeof(vol[0])){
			return vol[nVolumeType];
		}
		return vol[0];
	}	
}

int ControlData::getSrcVol(int src){
	return vol[src];
}

void ControlData::setBtCallVol(int volval){
	vol[VOL_BT]=volval;
}

void ControlData::setVol(int volSet){
	if(isNowBTCalling()){		
		vol[VOL_BT]=volSet;
	}else{
		if(nVolumeType>=0&&nVolumeType<sizeof(vol)/sizeof(vol[0])){
			vol[nVolumeType]=volSet;
		}else{
			vol[0]=volSet;
		}
	}
	
#ifdef HAVE_CAN_BUS
		void sendVOL_CAN();
		sendVOL_CAN();
#endif
		markVolChanged();
}




void ControlData::set响度频率(int 响度频率set){
	响度频率=响度频率set;
	markVolChanged();
	markContrlDataChanged();
}

void ControlData::set重低音截至频率(int 重低音截至频率Set){
	重低音截至频率=重低音截至频率Set;
	markVolChanged();
	markContrlDataChanged();
}


void ControlData::setLoundValue(int loundValueSet){
	loundValue=loundValueSet;
	markVolChanged();
	markContrlDataChanged();
}

#ifdef HAVE_CAN_BUS
void sendEQ();
void send前后左右平衡();
void sendCanDataDsp();
#else
#define sendEQ()
#define send前后左右平衡()
#define sendCanDataDsp()
#endif

void ControlData::setMiddle(int middleSet){
	middle=middleSet;
	markVolChanged();
	markContrlDataChanged();
	sendEQ();
}

void ControlData::setBas(int basSet){
		bas=basSet;
		markVolChanged();
		markContrlDataChanged();
		sendEQ();
	}

void ControlData::setSuperBass(int SuperBassSet){
		SuperBass=SuperBassSet;
		markVolChanged();
		markContrlDataChanged();
	}


void ControlData::setTre(int treSet){
		tre=treSet;
		markVolChanged();
		markContrlDataChanged();
		sendEQ();
	}



void ControlData::setBal(int balSet){
		bal=balSet;
		markVolChanged();
		markContrlDataChanged();
		send前后左右平衡();
	}

void ControlData::setFad(int fadSet){
		fad=fadSet;
		markVolChanged();
		markContrlDataChanged();
		send前后左右平衡();
	}
void ControlData::setV_dsp(int v_dspSet){
		v_dsp=v_dspSet;
		markVolChanged();
		//void sendCanDataDsp();
		sendCanDataDsp();
		markContrlDataChanged();
	}
	
void ControlData::setLound(bool isLoundSet){
		beLound=isLoundSet;
		markVolChanged();
		markContrlDataChanged();
	}

void ControlData::markVolInc(){
		if(!beVolChange){
			bool b=getVol()!=lastVol;
			if(b){
				markVolChanged();
			}
		}
	}

void changedToDvdVolumeChanelForc();

void ControlData::setMetaSource(int nSource){
		bool bChanged=(nMetaSource!=nSource);
		nMetaSource=nSource;
		markVolChanged();
		switch(nSource){
			case VOL_DVD:
			case VOL_BT:
			case VOL_RADIO:
				if(bChanged)
					startSmallVol();
				break;
		}
}

void ControlData::setDvdMuteDelay(int sleepTime){
	DWORD dNew=GetTickCount()+sleepTime;
	if(dDvdTheTimeOpenVolume<dNew){
		dDvdTheTimeOpenVolume=dNew;
		markVolChanged();
	}
}

extern bool muteTimeDelayFlag;
void ControlData::setMuteDelay(int sleepTime)
{
	DWORD dNew=GetTickCount()+sleepTime;
	if(dTheTimeOpenVolume<dNew){
		RETAILMSG_DC(1,(L"set mute delay = %d \r\n",sleepTime));
		dTheTimeOpenVolume=dNew;
		markVolChanged();
		muteTimeDelayFlag=true;
	}
}

extern bool bRadioNeedMute;


TCHAR *currentVolSet[]={L"VOL_NULL",L"VOL_DVD",L"VOL_RADIO",L"VOL_BT",L"VOL_AUX",L"VOL_IIS",L"VOL_IPOD",
L"VOL_CDC",L"VOL_TV",L"VOL_BT_MUSIC",L"VOL_安吉星",L"VOL_GPS",L"VOL_MP5",L"VOL_AUX2",L"VOL_CARLIFE"};
void clearnLastChanel(int nVolumeTypeSet);
void ControlData::setnVolumeType(int nVolumeTypeSet,bool recordVolume){
	clearnLastChanel(nVolumeTypeSet);//2016/09/18 fixbug yh
	if(nVolumeType!=nVolumeTypeSet){	
		if(nVolumeTypeSet==VOL_RADIO){//进入收音 静音延长  hss
			bRadioNeedMute=true;
			setMuteDelay(1000);			
		}
	}
	nVolumeType=nVolumeTypeSet;	
	switch(nVolumeTypeSet){
		case	 VOL_NULL	:
		case	 VOL_DVD	:
		case	 VOL_RADIO	:
		case	 VOL_BT		:
		case	 VOL_AUX	:
		case	 VOL_IPOD	:
		case     VOL_BT_MUSIC:
		case	 VOL_AUX2:
		case	 VOL_CARLIFE:
				RETAILMSG_DC(1,(L"==Set Vol MetaSource =%s=\r\n",currentVolSet[nVolumeTypeSet]));
				willData.setMetaSource(nVolumeTypeSet);
				break;	
		default:
			break;
	}

	if(recordVolume){
		switch(nVolumeTypeSet){
			case	 VOL_NULL	:
			case	 VOL_DVD	:
			case	 VOL_RADIO	:
			case	 VOL_AUX	:
			case	 VOL_IPOD	:
			case     VOL_BT_MUSIC:
			case	 VOL_AUX2:
			case	 VOL_CARLIFE:
					//screenCurrent.seVolumeType(nVolumeType);
					break;
		}
	}		
}

volatile long  vTimmerCounter;


int nCurrentTurn=0;


bool WinExec(LPCTSTR exeFileName/* =_T */,LPCTSTR fileName)
{
#ifdef WINCE
 PROCESS_INFORMATION processInfo; 
 if (!CreateProcess(exeFileName,fileName,NULL,NULL,NULL,CREATE_NEW_CONSOLE
  ,NULL,NULL,NULL,&processInfo))
 {
  return false;
 } 
 CloseHandle(processInfo.hThread);
 CloseHandle(processInfo.hProcess);
#endif
 return true;
}

bool WinExecWaitFor(LPCTSTR exeFileName/* =_T */,LPCTSTR fileName)
{
#ifdef WINCE
 PROCESS_INFORMATION processInfo; 
 if (!CreateProcess(exeFileName,fileName,NULL,NULL,NULL,CREATE_NEW_CONSOLE
  ,NULL,NULL,NULL,&processInfo))
 {
	RETAILMSG_DC(1,(L"CreateProcess failed (%d)\r\n", GetLastError())); 
	 return false;
 }
 Sleep(200);
 showGPS();// 公用
 WaitForSingleObject(processInfo.hProcess,INFINITE);
 CloseHandle(processInfo.hThread);
 CloseHandle(processInfo.hProcess);
#endif
 return true;
}

 

typedef struct _ttr{
	char *name;
	char type;
	void *address;
}ControlDataSaveStruct;


ControlDataSaveStruct controlDataSaveList[]={
{"bas",'i',&willData.bas},
	{"middle",'i',&willData.middle},
	{"tre",'i',&willData.tre},
	{"SuperBase",'i',&willData.SuperBass},
	{"loundValue",'i',&willData.loundValue},
	//{"重低音截至频率",'i',&willData.重低音截至频率},
	{"响度频率",'i',&willData.响度频率},
	{"bal",'i',&willData.bal},
	{"fad",'i',&willData.fad},
	{"v_dsp",'i',&willData.v_dsp},
	{"beLound",'b',&willData.beLound},
	{"bright",'i',&willData.bright},
	{"backBright",'i',&willData.backBright},
	{"beGps独立",'b',&willData.beGps独立},
	{"n独立声音大小",'i',&willData.n独立声音大小},
	{"n跟随声音大小",'i',&willData.n跟随声音大小},
	//{"b刹车",'b',&willData.b刹车},
	//{"b键盘声",'b',&willData.b键盘声},
	{"hourType",'i',&willData.hourType},
	{"showBtBook",'b',&willData.showBtBook},
	{"autoChangeBright",'b',&willData.autoChangeBright},
	{"userBright",'i',&willData.userBright},
	{"bePoweredOffByUser",'b',&willData.bePoweredOffByUser},
	{"DVD_PowerOn_Vol",'i',&willData.DVD_PowerOn_Vol},
	{"AUX_PowerOn_Vol",'i',&willData.AUX_PowerOn_Vol},
	{"收音机_PowerOn_Vol",'i',&willData.收音机_PowerOn_Vol},
	{"蓝牙_PowerOn_Vol",'i',&willData.蓝牙_PowerOn_Vol},
	{"蓝牙音乐_PowerOn_Vol",'i',&willData.蓝牙音乐_PowerOn_Vol},
};

#define SAVE_FILE "system_init/initParamter.save"

long lLastChangeValue=0;
void markContrlDataChanged(){
	lLastChangeValue=GetTickCount();
}

void saveControlData00(FILE*fp){
	for(int i=0;i<sizeof(controlDataSaveList)/sizeof(ControlDataSaveStruct);i++){
			//char buffer[100];
			ZString zs="";
			if(controlDataSaveList[i].type=='i'){
				zs.format("%s=%d\r\n",controlDataSaveList[i].name,*(int*)controlDataSaveList[i].address);				
			}else{
				zs.format("%s=%d\r\n",controlDataSaveList[i].name,*(bool*)controlDataSaveList[i].address);
			}
			DWORD writed;
			fwrite(zs.getData(),1,zs.size(),fp);
			//WriteFile(hHandle,zs,zs.size(),&writed,0);
		}
}

void saveControlData0(){
#ifdef WINCE
	HANDLE hHandle= createWriteOutPropFile(SAVE_FILE);
	RETAILMSG_DC(1,(L"WriteFile3\r\n"));
	if(hHandle==INVALID_HANDLE_VALUE){
		report("保存设置错误");
		return;
	}
	__try{
		saveControlData00(hHandle);
	}
	__except(seh_filer(GetExceptionCode(),GetExceptionInformation(),46))
	{
		
		RETAILMSG_DC(1,(L" saveControlData0电台0 MEE A EXCEPTION \r\n"));
	}
	CloseHandle(hHandle);
#endif
}
int seh_filer(int code,struct _EXCEPTION_POINTERS *infor,int module);

void saveControlData(){
	try
	{
		saveControlData0();
	}
	catch(...)
	{
		
		RETAILMSG_DC(1,(L" saveControlData MEE A EXCEPTION \r\n"));
	}
}

void trySaveContrlData(){
	if(lLastChangeValue==0)
		return;
	if(GetTickCount()-lLastChangeValue<10*1000)
		return;// 避免连续修改频繁保存数据
	saveControlData();
	lLastChangeValue=0;
}

void saveControlDataAndClear(){
	lLastChangeValue=0;
	willData.saveVolToPowerOnVol();
	saveControlData();
	//HSS
	void writeEqVal();
	//writeEqVal();
	void writeBalVal();
	//writeBalVal();
	void writeCanEqVal();
	writeCanEqVal();
}

static void ControlData_loadData0(){
#ifdef WINCE
	HANDLE hHandle= openReadinPropFile(SAVE_FILE);
	if(hHandle==INVALID_HANDLE_VALUE){
		return;
	}
	__try{
	{
			int len=sizeof(controlDataSaveList)/sizeof(controlDataSaveList[0]);
			for(int i=0;i<len;i++){
				char buffer[1000];
				char *line=readLine(buffer,hHandle,1000);
				if(line==NULL)
					break;
				//DWORD writed;
				char *pp=strstr(buffer,"=");
				if(pp){
					*pp=0;
					pp++;
					for(int j=0;j<len;j++){
						if(!strcmp(buffer,controlDataSaveList[j].name)){
							if(controlDataSaveList[j].type=='b'){
								int n=0;
								sscanf(pp,"%d",&n);
								*(bool*)controlDataSaveList[j].address=(n==0)? false:true;
							}else{
								sscanf(pp,"%d",controlDataSaveList[j].address);
							}
						}
					}
				}
			}
		}
	}
	__except(seh_filer(GetExceptionCode(),GetExceptionInformation(),48))
	{
		
		RETAILMSG_DC(1,(L" read false \r\n"));
	}
	CloseHandle(hHandle);
	willData.markAllSaveData();
#endif
}

int seh_filer(int code,struct _EXCEPTION_POINTERS *infor,int module);

void ControlData_loadData(){
	try
	{
		ControlData_loadData0();
		willData.setPowerOnInitVol();
	}
	catch(...)
	{
		
		RETAILMSG_DC(1,(L"ControlData_loadData MEE A EXCEPTION \r\n"));
		remove(SAVE_FILE);
		//remove(SAVE_FILE); // 文件损坏
		saveControlData();     // 从新保存一份
	}
}

void ControlData::saveDefaultData(){
	//
	
}

void restoreRadioData();
void restore方向盘设置();



int executeSTM8Cmd(DWORD cmd,unsigned char b0=0,unsigned b1=0);

void notRestoreGpsData(){
	
//	if(!existDebug())
//		executeSTM8Cmd(POWER_MAIN_OFF_ALL,0,0);
	willData.setPoweredMainOn(false);
	Sleep(200);
//	SetSystemPowerState(NULL, POWER_STATE_RESET, POWER_FORCE);
}

void restoreGpsDAta(){
	// 
	// STOP GPS
	// DELETE DATA FILE
	// 
	// RESTART
	// 
	void stopGPS监控();
	stopGPS监控();
	Sleep(200);


	Sleep(2000);
	// 
	// DELETE THE FILE
	// 
//	remove(L"/Residentflash2/APP/Orion.fsh");
	// 
	// RESTART
	// 

#ifdef WINCE
//	if(!existDebug())
//	executeSTM8Cmd(POWER_MAIN_OFF_ALL,0,0);
	Sleep(200);
//	SetSystemPowerState(NULL, POWER_STATE_RESET, POWER_FORCE);
#endif
}

void backSetting();

void notRestoreGpsData();

void restore方向盘设置();

#define BAL_FILE_NAME			"/Residentflash3/system_init/balance.ini"
#define EQU_FILE_NAME			"/Residentflash3/system_init/equ.ini"
#define SD_SAVE_FILE_NAME		"/Residentflash3/system_init/sdLastMem.ini"
#define USB_SAVE_FILE_NAME		"/Residentflash3/system_init/usbLastMem.ini"
#define DVP_LMFILE_NAME			"/Residentflash3/system_init/lastMem_dvp.txt"
#define SCREEN_FILE				"/Residentflash3/system_init/screen.sav"
#define MEDIA_FILE				"/Residentflash3/system_init/Media_Acc.sav"
#define SCREEN_FILE_NAME		"/Residentflash3/system_init/Screen2.ini"

#include "uartservice.h"
void file_copy(char *src, char *dst)
{
    FILE *fp1, *fp2;
    int c;
    fp1 = fopen(src, "rb");
    fp2 = fopen(dst, "wb");//打开文件
    if(fp1 == NULL || fp2 == NULL)//错误处理
    {
        printf("open file failed\n");
        if(fp1) fclose(fp1);
        if(fp2) fclose(fp2);
    }
     
    while((c = fgetc(fp1)) != EOF)//读字节
        fputc(c, fp2); //写数据
    fclose(fp1);//关闭文件
    fclose(fp2);
     
}

void restoreContrlDataDefaultData(){
	willData.setWillDataInitValue();
	saveControlData();
	//restore方向盘设置();
	willData.markAllSaveData();
	void restoreParameter();
	//restoreParameter();

	remove(BAL_FILE_NAME);
	remove(EQU_FILE_NAME);
	remove(SD_SAVE_FILE_NAME);
	remove(USB_SAVE_FILE_NAME);
	remove(DVP_LMFILE_NAME);
	remove(SCREEN_FILE);
	remove(MEDIA_FILE);
	remove(SCREEN_FILE_NAME);
	void resetVol();
	//resetVol();

	void clearPairList();
	//clearPairList();
	remove("/Residentflash3/BT/BlueTooth.ini");
	//file_copy("/Residentflash2/APP/BT/BlueTooth.ini","/Residentflash3/BT/BlueTooth.ini");

	//remove(L"/Residentflash3/system_init/CHEBIAO_SELECT.INI");
	void resetLogo();
	//resetLogo();

	setBackGroundAs("/Residentflash2/APP/IMG_WORK/背景图/01.JPG");
	//initBackGround();

	//drawBackGroud(true);

	void defaultupdateBootLogo();
	//defaultupdateBootLogo();
	RE_DRAW;

	//report("系统恢复默认数据!");//bal eq bt需要重启生效
	TO_SCRN_EX_ASY(getSCRN_参数设置());
	
	const unsigned char cmdData[]={T_SETTING_RESET,0,0,0,0};
	executeSTM8Cmdnew(CMD_CMD_TO_MCU,sizeof(cmdData),cmdData);	
}

void ControlData::setN独立声音大小(int n){
	n独立声音大小=n;
	markVolChanged();
}

void ControlData::setN跟随声音大小(int n){
	n跟随声音大小=n;
	markVolChanged();
}

void ControlData::setGps独立(bool b){
	beGps独立=b;
	markVolChanged();
}


void closeWINDOWS(){

}
void ControlData::setPowerOnVol(int volSet,int id){
	if(id<0||id>=sizeof(vol)/sizeof(vol[0]))
		return;
	if(id!=VOL_BT){//蓝牙通话音量是多少恢复多少
		if(volSet>INIT_VOL){//2016/09/18
			volSet=INIT_VOL;
		}
	}	
	if(volSet>0&&volSet<=MAX_VOL){
		vol[id]=volSet;
	}
}

 void  ControlData::setWillDataInitValue(){
		SuperBass=bas=tre=fad=bal=0;
		beMute=false;
		beSearchMute=true;
		isFMStore=true;		
		DVD_PowerOn_Vol=蓝牙音乐_PowerOn_Vol=蓝牙_PowerOn_Vol=INIT_VOL;
		收音机_PowerOn_Vol=AUX_PowerOn_Vol=INIT_VOL;
		for(int i=0;i<sizeof(vol)/sizeof(vol[0]);i++){
			vol[i]=INIT_VOL;
		}
		bright=MAX_BRIGHT;
		backBright=MAX_BRIGHT;
		beChangedBright=false;
		nVolumeType=VOL_NULL;
		beLound=false;
		beChanged6502=false;
		//isBTConnected=false; 
		//beChangedScreenClosed=false;
		runGpsWhenStart=false;
		//b导航兼听=true;
		bePower6410PowerOff=false;
		lastVol=0;
		beChanged6502=true;
		//b键盘声=1;
		//beGps独立=true;	//出厂设置为独立 2014-12-9
		//n独立声音大小=17;
		/*
	willData.vol=30;
	willData.bas=0;
	willData.tre=0;
	willData.bal=0;
	willData.fad=0;
	willData.v_dsp=0;
	willData.beLound=0;
	willData.bright=15;
	willData.b刹车=1;
	willData.b键盘声=1;
	willData.b倒车影像=0;
	willData.b导航兼听=1;
	willData.hourType=12;
	willData.userBright=10;
	*/
 }

 bool ControlData::set标致车系电话接入(bool on){
	 be标致车系电话接入=on;
	  markVolChanged();
	  return on;
 }

 bool ControlData::set安吉星ON(bool on){
	 be安吉星ON=on;
	 switch(on){
		 case true:
			 report("开启安吉星");
			 break;
		 case false:
			 report("退出安吉星");
			break;
	 }
	 markVolChanged();
	 return on;
 }
 
 void setScreenBright();
 void setBlackScreen();

 int closeScreenInGps = 0;
 int closeScreenInMapPhone = 0;

 extern int phone_map;
 void runPhoneMapping();
 void ControlData::setCloseScreenAcc(bool beCloseScreen){
	 beClosedScreen=beCloseScreen;			
	 if(beCloseScreen){		
		 //setBlackScreen();
	 }
 }
 void ControlData::setCloseScreen(bool beCloseScreen)
	{
		beClosedScreen=beCloseScreen;			
		if(beCloseScreen){
			if(inGps||phone_map){
				closeScreenInGps=inGps;
				closeScreenInMapPhone=phone_map;
				showZHWConsol(false);
			}
			//setBlackScreen();
		}else{	
			if(closeScreenInGps){
				closeScreenInGps=0;
				runGPS();
			}else if(closeScreenInMapPhone){
				closeScreenInMapPhone=0;
				runPhoneMapping();
			}
			setScreenBright();			
		}
	}




 void ControlData::setPoweredMainOn(bool b){
	 if(b&&!bePoweredMainOn){
		 dPoweredOnTime=GetTickCount();
	 }
	bePoweredMainOn=b;
 }

 ControlData::ControlData(){
		runMode=DESIGN_MODE;
		setWillDataInitValue();
		screenWidth=1024;
		screenHeight=600;
		beClosedScreen=false;
		IsHaveCalling=false;
		IsInTalking=false;
		IsTelDialing=false;
		beShowCheBiaoOnly=false;
		beDrawClock=true;
		be安吉星ON=false;
		be车身蓝牙=false;
		dDvdTheTimeOpenVolume=0;
		dTheTimeOpenVolume=0;
		isAccOn=false;
		beServiceCanRun=false;
		beCanKeyScan=false;
		bePoweredMainOn=false;
		iisInOutputingTime=0;
		beLastIIsTime=0;
		beLastIIsTime=0;
		beLastComingCallTime=0;
		猜猜是IIS来电铃声=false;
		fileProgressBar=0;
}

const char *STR_HEADER="ZHW-CONFIG-FILE\r\n";

 void savePropHeader(FILE*fp){
	 DWORD dwrited;
	fwrite(STR_HEADER,1,strlen(STR_HEADER),fp);
 }

 bool checkPropHeader(FILE*h,ZString fileName){
	 char buffer[100];
	 DWORD dreaded;
	 int len=strlen(STR_HEADER);
	 fread(buffer,1,len,h);
	 bool re=true;
	 if(dreaded!=len)
		 re=false;
	 else  if(strncmp(buffer,STR_HEADER,len)!=0){
			 re=false;
		 }
	 if(!re){
		 RETAILMSG_DC(1,(L"\r\n---- check header %s false !!! ---- \r\n",fileName));
	 }else{
		 RETAILMSG_DC(1,(L"\r\n---- check header %s OK !!! ---- \r\n",fileName));
	 }
	 return re;
 }

 bool checkFlash3DirExist();
 FILE* createWriteOutPropFile(ZString &fileName){
	 if(fileName.isEmpty())
		 return NULL;
	 if(!checkFlash3DirExist())
		 return NULL;
	FILE*fp=fopen(fileName,"wb");
	//RETAILMSG_DC(1,(L"Create prop file WriteFile0\r\n"));
	if(fp==NULL){
		return NULL;
	}
	savePropHeader(fp);
	return fp;
 }

 FILE* openReadinPropFile(ZString &fileName){
	  if(fileName.isEmpty())
		 return NULL;
	  if(!checkFlash3DirExist())
		  return NULL;
	 FILE *fp=fopen(fileName,"rb");
	 if(fp==NULL){
		 return NULL;
	 }
	 if(!checkPropHeader(fp,fileName)){
		 fclose(fp);
		 return NULL;
	 }
	 return fp;
 }

 FILE*openReadinPropFileMachine(ZString &fileName){
	 if(fileName.isEmpty())
		 return NULL;
	 if(!checkFlash3DirExist())
		 return NULL;
	 FILE *fp=fopen(fileName,"rb");//CreateFile(fileName,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,0,0);
	 if(fp==NULL){
		 return fp;
	 }
	 return fp;
 }


bool ifExistProcess(TCHAR *processName){
	#ifdef WINCE
	 const int TH32CS_SNAPNOHEAPS = 0x40000000;  
	PROCESSENTRY32 pe32;  
	pe32.dwSize = sizeof(pe32);  
	HANDLE hProcessSnap=
	CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS|TH32CS_SNAPNOHEAPS,0);//TH32CS_SNAPPROCESS|TH32CS_SNAPNOHEAPS   
	if(hProcessSnap == INVALID_HANDLE_VALUE)  
	{         
	   // AfxMessageBox(L"错误");  
		return FALSE;
	}          
	BOOL bMore=Process32First(hProcessSnap, &pe32);  
	bool beExistProcess=false;
	while(bMore)  
	{  
		TCHAR *szExeFile=pe32.szExeFile;  
		if(wcscmp(szExeFile,processName)==0)  
		{  
			  HANDLE hProcess = OpenProcess(0, FALSE, pe32.th32ProcessID);
			  if (hProcess == NULL)
			  {
					RETAILMSG_DC(1,(TEXT("获取进程失败")));
					break;
			  }
			  beExistProcess=true;
			  //DWORD exitCode;
			  /*
			  if (GetExitCodeProcess(hProcess, &exitCode) != 0)
			  {
					 TerminateProcess(hProcess, exitCode);//结束进程.
			  }
			  */
			break;  
		}        
		else  
		{   
				bMore = Process32Next(hProcessSnap, &pe32);           
		}    
	}  
	CloseToolhelp32Snapshot(hProcessSnap);  
	return beExistProcess;
#endif
	return TRUE;
}

bool ifProcessFullRuned(TCHAR *p){
	int len=wcslen(p);
	TCHAR *processName=p;
	for(int i=len-1;i>=0;i--)
	{
		if(p[i]==L'\\'||p[i]==L'//')
		{
			processName=p+i+1;
			break;
		}
	}
	return ifExistProcess(processName);
}
 void killProcess(TCHAR *processName);

 void killFullNameProcess(TCHAR *p){
	int len=wcslen(p);
	TCHAR *processName=p;
	for(int i=len-1;i>=0;i--)
	{
		if(p[i]==L'\\'||p[i]==L'//')
		{
			processName=p+i+1;
			break;
		}
	}
	killProcess(processName);
 }

 void killProcess(TCHAR *processName){
#ifdef WINCE
	 const int TH32CS_SNAPNOHEAPS = 0x40000000;  
	PROCESSENTRY32 pe32;  
	pe32.dwSize = sizeof(pe32);  
	HANDLE hProcessSnap=
	CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS|TH32CS_SNAPNOHEAPS,0);//TH32CS_SNAPPROCESS|TH32CS_SNAPNOHEAPS   
	if(hProcessSnap == INVALID_HANDLE_VALUE)  
	{         
	   // AfxMessageBox(L"错误");  
		return ;
	}          
	BOOL bMore=::Process32First(hProcessSnap, &pe32);  
	while(bMore)  
	{  
		TCHAR *szExeFile=pe32.szExeFile;  
		if(wcscmp(szExeFile,processName)==0)  
		{  
			  HANDLE hProcess = OpenProcess(0, FALSE, pe32.th32ProcessID);
			  if (hProcess == NULL)
			  {
					RETAILMSG_DC(1,(TEXT("获取进程失败")));
					break;
			  }
			  DWORD exitCode;
			  if (GetExitCodeProcess(hProcess, &exitCode) != 0)
			  {
					 TerminateProcess(hProcess, exitCode);//结束进程.
			  }
			break;  
		}        
		else  
		{   
				bMore = Process32Next(hProcessSnap, &pe32);           
		}    
	}  
	CloseToolhelp32Snapshot(hProcessSnap);  
#endif
 }


 void ControlData::setPowerOnInitVol(){
		setPowerOnVol(DVD_PowerOn_Vol,VOL_DVD);
		setPowerOnVol(AUX_PowerOn_Vol,VOL_AUX);
		setPowerOnVol(收音机_PowerOn_Vol,VOL_RADIO);
		setPowerOnVol(蓝牙_PowerOn_Vol,VOL_BT);
		setPowerOnVol(蓝牙音乐_PowerOn_Vol,VOL_BT_MUSIC);
 }


 void ControlData::saveVolToPowerOnVol(){//2015-5-12
	 DVD_PowerOn_Vol=vol[VOL_DVD];
	 AUX_PowerOn_Vol=vol[VOL_AUX];
	 收音机_PowerOn_Vol=vol[VOL_RADIO];
	 蓝牙_PowerOn_Vol=vol[VOL_BT];
	 蓝牙音乐_PowerOn_Vol=vol[VOL_BT_MUSIC];
 }

 //===================================================
 void ControlData::setFile_Progress_Bar(int n){
	 fileProgressBar=n;
 }

//==========================20130808=================
void ControlData::setDVD_PowerOn_Vol(int n){
	DVD_PowerOn_Vol=n;
	markContrlDataChanged();
}

void ControlData::setAUX_PowerOn_Vol(int n){
	AUX_PowerOn_Vol=n;
	markContrlDataChanged();
}


void ControlData::set收音机_PowerOn_Vol(int n){
	收音机_PowerOn_Vol=n;
	markContrlDataChanged();
}
void ControlData::set蓝牙_PowerOn_Vol(int n){
	蓝牙_PowerOn_Vol=n;
	markContrlDataChanged();
}
void ControlData::set蓝牙音乐_PowerOn_Vol(int n){
	蓝牙音乐_PowerOn_Vol=n;
	markContrlDataChanged();
}
//==================================================


