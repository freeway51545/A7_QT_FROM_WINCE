#include "pub.h"

bool inBox(int x,int y,RECT r){
	 return x>=r.left&&x<r.right&&y>=r.top&&y<r.bottom;
 }


char*getChar1_0(char *buf,int len,TCHAR*toDraw){
	return buf;
}



bool inBox(RECT r,int x,int y){
	return x>r.left&&x<r.right&&y>r.top&&y<r.bottom;
}


int isFullScreenVd(){
	return 1;
}

bool endsWith(char*c1,char*c2){
	if(c1==NULL||c2==NULL)
		return false;
	int loc1=strlen(c1)-strlen(c2);
	return strcmp(c1+loc1,c2)==0;
}


void muteOff(){
}
void sendVOL_CAN(){
}

void __cdecl sendEQ(void){};
void __cdecl sendÇ°ºó×óÓÒÆ½ºâ(void){};
void __cdecl sendCanDataDsp(void){};//;//?sendCanDataDsp@@YAXXZ) referenced in function "public: void __thiscall ControlData::setV_dsp(int);//?setV_dsp@ControlData@@QAEXH@Z)
void __cdecl writeCanEqVal(void){};//;//?writeCanEqVal@@YAXXZ) referenced in function "void __cdecl saveControlDataAndClear(void);//?saveControlDataAndClear@@YAXXZ)



void zhw_strcat_s(char *strCat,int len,char *s1){
	int n=strlen(strCat);
	int maxChar=len-1;
	if(n>=maxChar)
		return;
	int i=0;
	for(i=n;i<maxChar;i++){
		if(*s1){
			strCat[i]=*s1++;
		}else{
			break;
		}
	}
	strCat[i]=0;
}


void __cdecl powerOnMethod(bool){};
void __cdecl stopGPS¼à¿Ø(void){};
int __cdecl executeSTM8Cmdnew(unsigned long,unsigned char,unsigned char const *){return 1;};



void setBackGroundAs(char *name){
/*	TCHAR BACK_FLAG_NAME[256];
	getBackName(BACK_FLAG_NAME);
	HANDLE fHandle= CreateFile(BACK_FLAG_NAME,GENERIC_WRITE,FILE_SHARE_WRITE,NULL,CREATE_ALWAYS,0,0);
	if(fHandle==INVALID_HANDLE_VALUE)
	{
		return;
	}
	DWORD writed;
	WriteFile(fHandle,name,256,&writed,0);
	CloseHandle(fHandle);
	*/
}


void setScreenBright(){
}
void runPhoneMapping(){};


bool __cdecl runGPS(bool,bool){return 1;};

int phone_map;


bool __cdecl checkFlash3DirExist(){
	return 1;
}


LPARAM getFxpKey(LPARAM lParamFxpKey){
	return lParamFxpKey;
}

void __cdecl sendFMAM(int,bool){
}
ZString nPlayingScreen;


void __cdecl timmerToCloseOverlay(void);

bool beLastIsFullWindow=false;

int passwordFlag=0;

void getBackGround(char *name);

void __cdecl timmerToCloseOverlay(void){
}
bool beDealedJustNow=false;

void __cdecl manufacSet(void){
}





void __cdecl sendDaZhongData(void){};//;//?sendDaZhongData@@YAXXZ) referenced in function "void __cdecl showCarDrData(void);//?showCarDrData@@YAXXZ)
unsigned int so_LittleLamp;//;//?so_LittleLamp@@3IA)

//struct tagCARINFO carInfo;//?carInfo@@3UtagCARINFO@@A)
//struct tagCANCARINFO canCarInfo;//?canCarInfo@@3UtagCANCARINFO@@A)
double canMileage;//?canMileage@@3NA)
double canCarSpeed;//?canCarSpeed@@3NA)
unsigned long canRPM;//?canRPM@@3KA)
double canBatVoltage;//?canBatVoltage@@3NA)
double canOutTemp;//?canOutTemp@@3NA)
bool canTempFlag;//?canTempFlag@@3_NA)
double canLevOil;//?canLevOil@@3NA)
unsigned char canParkStat;//?canParkStat@@3EA)
unsigned char canILLValue;//?canILLValue@@3EA)
int canCarSpeedUnit;//?canCarSpeedUnit@@3HA)



void __cdecl initBtRecord(void){}//" (?initBtRecord@@YAXXZ) referenced in function "public: void __thiscall BT_RECORD_Event::_F_INIT_FUN(class MSG_ZHW &)" (?_F_INIT_FUN@BT_RECORD_Event@@QAEXAAVMSG_ZHW@@@Z)
void __cdecl btRecordTimmer(void){}//" (?btRecordTimmer@@YAXXZ) referenced in function "public: void __thiscall BT_RECORD_Event::_F_UPDATE_TIMMER(class MSG_ZHW &)" (?_F_UPDATE_TIMMER@BT_RECORD_Event@@QAEXAAVMSG_ZHW@@@Z)
void __cdecl BtRecordCallType(int){}//" (?BtRecordCallType@@YAXH@Z) referenced in function "public: void __thiscall BT_RECORD_Event::_F_ALL(class MSG_ZHW &)" (?_F_ALL@BT_RECORD_Event@@QAEXAAVMSG_ZHW@@@Z)
void __cdecl btRecordMouseDown(int,int){}//" (?btRecordMouseDown@@YAXHH@Z) referenced in function "public: virtual void __thiscall BT_RECORD_Event::mouseDownNative(int,int)" (?mouseDownNative@BT_RECORD_Event@@UAEXHH@Z)
void __cdecl btRecordMouseMove(int,int){}//" (?btRecordMouseMove@@YAXHH@Z) referenced in function "public: virtual void __thiscall BT_RECORD_Event::mouseMoveNative(int,int)" (?mouseMoveNative@BT_RECORD_Event@@UAEXHH@Z)
void __cdecl btRecordMouseRelease(int,int){}//" (?btRecordMouseRelease@@YAXHH@Z) referenced in function "public: virtual void __thiscall BT_RECORD_Event::mouseReleaseNative(int,int)" (?mouseReleaseNative@BT_RECORD_Event@@UAEXHH@Z)
void __cdecl getBtDeviceName(char *){}//" (?getBtDeviceName@@YAXPAD@Z) referenced in function "void __cdecl sysGetBtDevName(void)" (?sysGetBtDevName@@YAXXZ)
void __cdecl SetBtDevNameToSystem(void){}//" (?SetBtDevNameToSystem@@YAXXZ) referenced in function "public: void __thiscall BT_SETNAME_Event::_F_OK(class MSG_ZHW &)" (?_F_OK@BT_SETNAME_Event@@QAEXAAVMSG_ZHW@@@Z)
void __cdecl backSpaceBtEditInfo(void){}//" (?backSpaceBtEditInfo@@YAXXZ) referenced in function "public: void __thiscall BT_SETNAME_Event::_F_BKS(class MSG_ZHW &)" (?_F_BKS@BT_SETNAME_Event@@QAEXAAVMSG_ZHW@@@Z)
void __cdecl addBtEditInfo(char *){}//" (?addBtEditInfo@@YAXPAD@Z) referenced in function "public: void __thiscall BT_SETNAME_Event::_F_KEYDOWN(char *,class MSG_ZHW &)" (?_F_KEYDOWN@BT_SETNAME_Event@@QAEXPADAAVMSG_ZHW@@@Z)
void __cdecl DrawBtDevNamedrawDynimic(class Screen *,class DrawContext &){}//" (?DrawBtDevNamedrawDynimic@@YAXPAVScreen@@AAVDrawContext@@@Z) referenced in function "public: virtual void __thiscall BT_SETNAME_Event::drawDynimic(class Screen *,class DrawContext &)" (?drawDynimic@BT_SETNAME_Event@@UAEXPAVScreen@@AAVDrawContext@@@Z)

void __cdecl drawbtTalkingInfo(class Screen *,class DrawContext &){};//" (?drawbtTalkingInfo@@YAXPAVScreen@@AAVDrawContext@@@Z) referenced in function "public: virtual void __thiscall BT_TALKING_Event::drawDynimic(class Screen *,class DrawContext &)" (?drawDynimic@BT_TALKING_Event@@UAEXPAVScreen@@AAVDrawContext@@@Z)
void __cdecl clearSelectFlagDVP(void){};//" (?clearSelectFlagDVP@@YAXXZ) referenced in function "public: void __thiscall AUDIO_LIST_Event::_F_INIT_FUN(class MSG_ZHW &)" (?_F_INIT_FUN@AUDIO_LIST_Event@@QAEXAAVMSG_ZHW@@@Z)
void __cdecl showAllSdUsbInfo(void){};//" (?showAllSdUsbInfo@@YAXXZ) referenced in function "public: virtual void __thiscall MEDIA_AUDIO_Event::drawDynimic(class Screen *,class DrawContext &)" (?drawDynimic@MEDIA_AUDIO_Event@@UAEXPAVScreen@@AAVDrawContext@@@Z)
void __cdecl runPingMuXiuding(void){};//" (?runPingMuXiuding@@YAXXZ) referenced in function "public: void __thiscall SHOW_DLG_Event::_F_AGREE(class MSG_ZHW &)" (?_F_AGREE@SHOW_DLG_Event@@QAEXAAVMSG_ZHW@@@Z)
void __cdecl copyLastScrnBackGroundShow(int,int){};//" (?copyLastScrnBackGroundShow@@YAXHH@Z) referenced in function "public: void __thiscall SHOW_Event::_F_CALIBRATION(class MSG_ZHW &)" (?_F_CALIBRATION@SHOW_Event@@QAEXAAVMSG_ZHW@@@Z)
void __cdecl InBtEnterSetSrcBTMusic(void){};//" (?InBtEnterSetSrcBTMusic@@YAXXZ) referenced in function "public: void __thiscall MAIN1_Event::_F_CALL_À¶ÑÀ(class MSG_ZHW &)" (?_F_CALL_À¶ÑÀ@MAIN1_Event@@QAEXAAVMSG_ZHW@@@Z)
void __cdecl initBtLineBorder(int){};//" (?initBtLineBorder@@YAXH@Z) referenced in function "void __cdecl startLoadPhoneBook(void)" (?startLoadPhoneBook@@YAXXZ)
void __cdecl LoadSavePhoneBookNum(void){};//" (?LoadSavePhoneBookNum@@YAXXZ) referenced in function "void __cdecl startLoadPhoneBook(void)" (?startLoadPhoneBook@@YAXXZ)
void __cdecl clearTelBookAllHistory(void){};//" (?clearTelBookAllHistory@@YAXXZ) referenced in function "void __cdecl clearAllPhoneData(void)" (?clearAllPhoneData@@YAXXZ)
void __cdecl clearTelBook(void){};//" (?clearTelBook@@YAXXZ) referenced in function "void __cdecl clearAllPhoneData(void)" (?clearAllPhoneData@@YAXXZ)
bool inUpgradeSTM32=false;
bool __cdecl chechUpGradeFile(void){return 0;};//" (?chechUpGradeFile@@YA_NXZ) referenced in function "public: static unsigned long __stdcall CLoadManager::ScanListThreadProc(void *)" (?ScanListThreadProc@CLoadManager@@SGKPAX@Z)
void __cdecl setToMediaVolumeDir(void){};//" (?setToMediaVolumeDir@@YAXXZ) referenced in function "public: void __thiscall CLoadManager::OpenMediaVolume(void)" (?OpenMediaVolume@CLoadManager@@QAEXXZ)
int selecTimesDVP;
void mayCloseVi(){
}
void exchangeMute(){
}
BOOL IsBtSwitchOn(){
	return 1;
}
int haveAuxVedioSignal=0;

bool isBackNoSignal(void){
	return 0;
}

bool isIllAutoOn(){
	return 0;
}


void maySeedBeep(){
}
bool bRadioNeedMute;

int getActSelectType(){
	return 0;
}

void convertStrToTchar(char *,unsigned short *,int){
}

bool isMeidaDevice(){
	return 0;
}


bool isDeviceExist(unsigned short *){
	return 0;
}

unsigned short * pbRootPathUSB0=L"";


bool isNowCalling(void){
	return 0;
}

bool MutilMeidaStartPlay=0;

bool beGpsCardInserted=0;

bool whenBackCallover=0;
bool auxEnter=0;
bool auxIsPlaying=0;

bool beEnterBack(){
	return 0;
}
bool inBackRestore=0;

int iDeviceType=0;

void _F_½ÓÌý_²¦´ò_new(){
}
void _F_¹Ò¶Ï_new(){
}
void beepDirect(){
}

bool isÉ²³µ¼ì²â(){
	return 0;
}
void	setRadioData(int,int,int){
}
bool isCarLifeTrsfByBT(){
	return 0;
}