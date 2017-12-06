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
			// ���в²�
			if(!�²�IIS������){
				if(GetTickCount()-beLastComingCallTime<4000){
					�²�IIS������=true;
					RETAILMSG_DC(1,(L"GUST COMING CALL IS IIS \r\n"));
				}
			}
		}
	}
	if(iisInOutputing){
		//closeCarlifeAudio();
//		closeCarlifeAudioImmedia();		//����Ҫ��sendmessage
	}else{
		//openCarlifeAudio();
//		openCarlifeAudioImmedia();
	}
	markVolChanged();
}

#define ����_DELAY_TIME	2000
void ControlData::setIsHaveCalling(bool b){
	IsHaveCalling=b;
	if(IsHaveCalling){
		beLastComingCallTime=GetTickCount();//
		if(beLastComingCallTime>beLastIIsTime){
			if(beLastComingCallTime-beLastIIsTime<4000){
				�²�IIS������=true;
				RETAILMSG_DC(1,(L"GUST COMING CALL IS IIS TRUE\r\n"));
			}else{
				�²�IIS������=false;
				RETAILMSG_DC(1,(L"GUST COMING CALL IS IIS FALSE\r\n"));
			}
		}
	}
	markVolChanged();
}

BOOL ControlData::get�²���IIS��������(){
	if(!willData.IsHaveCalling)
		return false;
	if(willData.IsInTalking)
		return false;
	if(willData.IsTelDialing)
		return false;
	return �²�IIS������;
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
			lastVol=SMALL_VOL;// ����������
			if(lastVol<getVol()){
				lastVol=getVol()-2;
			}
			if(lastVol<0)
				lastVol=0;
		}
		void muteOff();
		muteOff();//2014-12-12 muteoff��û������
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
				lastVol=SMALL_VOL;// ����������
				if(lastVol<getVol()){
					lastVol=getVol()-2;
				}
				if(lastVol<0)
					lastVol=0;
			}
			void muteOff();
			muteOff();//2014-12-12 muteoff��û������
		}
		if(muteSet){
			lLastSetMuteTime=GetTickCount();
		}
		RE_DRAW;
}


int ControlData::getVol(){
		// ���ݲ�ͬ������Դ��������
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




void ControlData::set���Ƶ��(int ���Ƶ��set){
	���Ƶ��=���Ƶ��set;
	markVolChanged();
	markContrlDataChanged();
}

void ControlData::set�ص�������Ƶ��(int �ص�������Ƶ��Set){
	�ص�������Ƶ��=�ص�������Ƶ��Set;
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
void sendǰ������ƽ��();
void sendCanDataDsp();
#else
#define sendEQ()
#define sendǰ������ƽ��()
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
		sendǰ������ƽ��();
	}

void ControlData::setFad(int fadSet){
		fad=fadSet;
		markVolChanged();
		markContrlDataChanged();
		sendǰ������ƽ��();
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
L"VOL_CDC",L"VOL_TV",L"VOL_BT_MUSIC",L"VOL_������",L"VOL_GPS",L"VOL_MP5",L"VOL_AUX2",L"VOL_CARLIFE"};
void clearnLastChanel(int nVolumeTypeSet);
void ControlData::setnVolumeType(int nVolumeTypeSet,bool recordVolume){
	clearnLastChanel(nVolumeTypeSet);//2016/09/18 fixbug yh
	if(nVolumeType!=nVolumeTypeSet){	
		if(nVolumeTypeSet==VOL_RADIO){//�������� �����ӳ�  hss
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
 showGPS();// ����
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
	//{"�ص�������Ƶ��",'i',&willData.�ص�������Ƶ��},
	{"���Ƶ��",'i',&willData.���Ƶ��},
	{"bal",'i',&willData.bal},
	{"fad",'i',&willData.fad},
	{"v_dsp",'i',&willData.v_dsp},
	{"beLound",'b',&willData.beLound},
	{"bright",'i',&willData.bright},
	{"backBright",'i',&willData.backBright},
	{"beGps����",'b',&willData.beGps����},
	{"n����������С",'i',&willData.n����������С},
	{"n����������С",'i',&willData.n����������С},
	//{"bɲ��",'b',&willData.bɲ��},
	//{"b������",'b',&willData.b������},
	{"hourType",'i',&willData.hourType},
	{"showBtBook",'b',&willData.showBtBook},
	{"autoChangeBright",'b',&willData.autoChangeBright},
	{"userBright",'i',&willData.userBright},
	{"bePoweredOffByUser",'b',&willData.bePoweredOffByUser},
	{"DVD_PowerOn_Vol",'i',&willData.DVD_PowerOn_Vol},
	{"AUX_PowerOn_Vol",'i',&willData.AUX_PowerOn_Vol},
	{"������_PowerOn_Vol",'i',&willData.������_PowerOn_Vol},
	{"����_PowerOn_Vol",'i',&willData.����_PowerOn_Vol},
	{"��������_PowerOn_Vol",'i',&willData.��������_PowerOn_Vol},
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
		report("�������ô���");
		return;
	}
	__try{
		saveControlData00(hHandle);
	}
	__except(seh_filer(GetExceptionCode(),GetExceptionInformation(),46))
	{
		
		RETAILMSG_DC(1,(L" saveControlData0��̨0 MEE A EXCEPTION \r\n"));
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
		return;// ���������޸�Ƶ����������
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
		//remove(SAVE_FILE); // �ļ���
		saveControlData();     // ���±���һ��
	}
}

void ControlData::saveDefaultData(){
	//
	
}

void restoreRadioData();
void restore����������();



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
	void stopGPS���();
	stopGPS���();
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

void restore����������();

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
    fp2 = fopen(dst, "wb");//���ļ�
    if(fp1 == NULL || fp2 == NULL)//������
    {
        printf("open file failed\n");
        if(fp1) fclose(fp1);
        if(fp2) fclose(fp2);
    }
     
    while((c = fgetc(fp1)) != EOF)//���ֽ�
        fputc(c, fp2); //д����
    fclose(fp1);//�ر��ļ�
    fclose(fp2);
     
}

void restoreContrlDataDefaultData(){
	willData.setWillDataInitValue();
	saveControlData();
	//restore����������();
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

	setBackGroundAs("/Residentflash2/APP/IMG_WORK/����ͼ/01.JPG");
	//initBackGround();

	//drawBackGroud(true);

	void defaultupdateBootLogo();
	//defaultupdateBootLogo();
	RE_DRAW;

	//report("ϵͳ�ָ�Ĭ������!");//bal eq bt��Ҫ������Ч
	TO_SCRN_EX_ASY(getSCRN_��������());
	
	const unsigned char cmdData[]={T_SETTING_RESET,0,0,0,0};
	executeSTM8Cmdnew(CMD_CMD_TO_MCU,sizeof(cmdData),cmdData);	
}

void ControlData::setN����������С(int n){
	n����������С=n;
	markVolChanged();
}

void ControlData::setN����������С(int n){
	n����������С=n;
	markVolChanged();
}

void ControlData::setGps����(bool b){
	beGps����=b;
	markVolChanged();
}


void closeWINDOWS(){

}
void ControlData::setPowerOnVol(int volSet,int id){
	if(id<0||id>=sizeof(vol)/sizeof(vol[0]))
		return;
	if(id!=VOL_BT){//����ͨ�������Ƕ��ٻָ�����
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
		DVD_PowerOn_Vol=��������_PowerOn_Vol=����_PowerOn_Vol=INIT_VOL;
		������_PowerOn_Vol=AUX_PowerOn_Vol=INIT_VOL;
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
		//b��������=true;
		bePower6410PowerOff=false;
		lastVol=0;
		beChanged6502=true;
		//b������=1;
		//beGps����=true;	//��������Ϊ���� 2014-12-9
		//n����������С=17;
		/*
	willData.vol=30;
	willData.bas=0;
	willData.tre=0;
	willData.bal=0;
	willData.fad=0;
	willData.v_dsp=0;
	willData.beLound=0;
	willData.bright=15;
	willData.bɲ��=1;
	willData.b������=1;
	willData.b����Ӱ��=0;
	willData.b��������=1;
	willData.hourType=12;
	willData.userBright=10;
	*/
 }

 bool ControlData::set���³�ϵ�绰����(bool on){
	 be���³�ϵ�绰����=on;
	  markVolChanged();
	  return on;
 }

 bool ControlData::set������ON(bool on){
	 be������ON=on;
	 switch(on){
		 case true:
			 report("����������");
			 break;
		 case false:
			 report("�˳�������");
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
		be������ON=false;
		be��������=false;
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
		�²���IIS��������=false;
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
	   // AfxMessageBox(L"����");  
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
					RETAILMSG_DC(1,(TEXT("��ȡ����ʧ��")));
					break;
			  }
			  beExistProcess=true;
			  //DWORD exitCode;
			  /*
			  if (GetExitCodeProcess(hProcess, &exitCode) != 0)
			  {
					 TerminateProcess(hProcess, exitCode);//��������.
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
	   // AfxMessageBox(L"����");  
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
					RETAILMSG_DC(1,(TEXT("��ȡ����ʧ��")));
					break;
			  }
			  DWORD exitCode;
			  if (GetExitCodeProcess(hProcess, &exitCode) != 0)
			  {
					 TerminateProcess(hProcess, exitCode);//��������.
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
		setPowerOnVol(������_PowerOn_Vol,VOL_RADIO);
		setPowerOnVol(����_PowerOn_Vol,VOL_BT);
		setPowerOnVol(��������_PowerOn_Vol,VOL_BT_MUSIC);
 }


 void ControlData::saveVolToPowerOnVol(){//2015-5-12
	 DVD_PowerOn_Vol=vol[VOL_DVD];
	 AUX_PowerOn_Vol=vol[VOL_AUX];
	 ������_PowerOn_Vol=vol[VOL_RADIO];
	 ����_PowerOn_Vol=vol[VOL_BT];
	 ��������_PowerOn_Vol=vol[VOL_BT_MUSIC];
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


void ControlData::set������_PowerOn_Vol(int n){
	������_PowerOn_Vol=n;
	markContrlDataChanged();
}
void ControlData::set����_PowerOn_Vol(int n){
	����_PowerOn_Vol=n;
	markContrlDataChanged();
}
void ControlData::set��������_PowerOn_Vol(int n){
	��������_PowerOn_Vol=n;
	markContrlDataChanged();
}
//==================================================


