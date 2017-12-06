

#ifndef PUB_H
#define PUB_H
#include <QtGui>
#include "pubtype.h"
#include "ZString.h"
#include "ScreenEventManager.h"
#include "paramter.h"
#include "threadstatereport.h"
#include "screenmem.h"
DWORD callIRD(DWORD cmd,DWORD parameter=0);
void markContrlDataChanged();
void initDvdControl();

enum Radio_Type{	//MCU define
    RADIO_NXP6621=0,
    RADIO_NXP6686,
    RADIO_SI4730,
    RADIO_SI4702,
	RADIO_SI4754
};

#ifdef WINCE
bool WinExec(LPCTSTR exeFileName/* =_T */,LPCTSTR fileName);
#endif
bool runGPS(bool changedWindow=true,bool showPinP=false);
void runPingMuXiuding();



#define DESIGN_MODE	0
#define RUN_MODE	1


#define VOL_NULL	0
#define VOL_DVD		1
#define VOL_RADIO	2
#define VOL_BT		3
#define VOL_AUX		4
#define VOL_IIS		5
#define VOL_IPOD	6
#define VOL_CDC		7
#define VOL_TV		8
#define VOL_BT_MUSIC	9
#define VOL_安吉星		10
#define VOL_GPS		11
#define VOL_MP5		12
#define VOL_AUX2		13
#define VOL_CARLIFE		14



#define V4052_CH1	0
#define V4052_CH2	1

#define OPEN_SOURCE_MUTE()		willData.setnVolumeType(VOL_NULL)	
#define OPEN_DVD_VOLUME()		willData.setnVolumeType(VOL_DVD)
#define OPEN_RADIO_VOLUME()		willData.setnVolumeType(VOL_RADIO)

#define OPEN_BT_VOLUME(saveOld)		willData.setnVolumeType(VOL_BT,saveOld)

//#define OPEN_GPS_OUT_VOLUME()	willData.setnVolumeType(VOL_GPS)
#define OPEN_MP5_VOLUME()		willData.setnVolumeType(VOL_MP5)
#define OPEN_IIS_VOLUME()		willData.setnVolumeType(VOL_IIS)

#define OPEN_IPOD_VOLUME()		willData.setnVolumeType(VOL_IPOD)
#define OPEN_CDC_VOLUME()		willData.setnVolumeType(VOL_CDC)
#define OPEN_TV_VOLUME()		willData.setnVolumeType(VOL_TV)
#define OPEN_AUX_VOLUME()		willData.setnVolumeType(VOL_AUX)
#define OPEN_AUX2_VOLUME()		willData.setnVolumeType(VOL_AUX2)
#define OPEN_BT_MUSIC()			willData.setnVolumeType(VOL_BT_MUSIC);
#define OPEN_CARLIFE_VOLUME()	willData.setnVolumeType(VOL_CARLIFE);


class ControlData{
public:
	bool beVolChange;
	bool beChangedBright;
	bool beChangedPower;
	bool beChanged6502;
	//bool beChangedScreenClosed;
	bool bePower6410PowerOff;
	bool beShowCheBiaoOnly;
	bool isBackOnCD;
	bool bePoweredOffByUser;
	bool beDrawClock;
	DWORD iisInOutputingTime;
public:
	inline DWORD getIisInOutputingTime(){
		return iisInOutputingTime;
	};
	bool isAccOn;
	bool beServiceCanRun;
	bool bePoweredMainOn;
	DWORD dPoweredOnTime;
	bool beCanKeyScan;
	void setPoweredMainOn(bool b);
	void saveVolToPowerOnVol();
	void markAllSaveData(){
		beChangedBright=true;
	};

	void setCloseScreenAcc(bool beCloseScreen);
	/*
	bool isChangedScreenClosed(){
		return beChangedScreenClosed;
	}
	*/
	/*
	void clearChangedScreenClosed(){
		beChangedScreenClosed=false;
	}
	*/
	bool isChanged6502(){
		return beChanged6502;
	}
	void clearChanged6502(){
		beChanged6502=false;
	}
	bool isChangedPower(){
		return beChangedPower;
	}
	void clearPowerChangedFlag(){
		beChangedPower=false;
	}
	bool isChangedBright(){
		return beChangedBright;
	}
	void clearChangedBrightFlag(){
		beChangedBright=false;
	}

private:
	int vol[15];	//声音
public:
	// CONTRL VOLUME
	int lastVol;// 实际的音量，当音量被修订的时候，逐渐增加，不然会感觉突然加大。
	int bas;	//BAS
	int middle;
	int tre;	//tre
	int SuperBass;// 低重音
	int bal;	//平衡
	int fad;	//FAD 前后
	int v_dsp;	//0;JAZZ——>CLAS——>ROCK——>FLAT——>POP
	bool beLound;//
	int loundValue;
	int 重低音截至频率;
	int 响度频率;
	//unsigned char vVolumeChanel;
	/** 声音输入通道　*/
	int nVolumeType;
	int bright;
	int backBright;
	int userBright;
	bool beMute;
	bool beSearchMute;
	unsigned char nSTM8AB;
	/** 2312 输入通道 */
	int n2312Chanel;
	int power;// 会有多位进行处理。
	int n6502;
	bool beClosedScreen;
	int nMetaSource;
	bool btInCalling;
	bool iisInOutputing;
	bool beDvdMute;
	bool be安吉星ON;
	bool be车身蓝牙;
	bool be标致车系电话接入;
	DWORD dTheTimeOpenVolume;
	DWORD dDvdTheTimeOpenVolume;
	BOOL 猜测IIS来电结果;
	DWORD beLastIIsTime;
	DWORD beLastComingCallTime;
	void setIsHaveCalling(bool b);
	BOOL 猜猜是IIS来电铃声;
	BOOL get猜猜是IIS来电铃声();
public:
	bool beGps独立;
	int n独立声音大小;
	int n跟随声音大小;
public:
	void setN独立声音大小(int n);
	void setN跟随声音大小(int n);
	void setGps独立(bool b);
	bool isGps独立(){
		return beGps独立;
	}
	int getN独立声音大小(){
		return n独立声音大小;
	}
	int getN跟随声音大小(){
		return n跟随声音大小;
	}

	void setDVDMute(bool b);
	void setBtInCalling(bool b);
	void setIisInOutputing(bool b);
	bool isIisInOutputing();
	bool isMute(){
		return beMute;
	}
	void markVolChanged();
public:
	void setUserBright(int brightSet);
	int getUserBright(){
		return userBright;
	}
	void setMetaSource(int nSource);

	void setCloseScreen(bool set);

	bool isClosedScreen(){
		return beClosedScreen;
	}
	void set6502(int n);
	int get6502(){
		return n6502;
	}
	void setPowerOn(int n){
		power|=n;
		beChangedPower=true;
	}
	void setPowerOff(int n){
		power&=~n;
		beChangedPower=true;
	}
	int getPower(){
		return power;
	}
	void setSearchMute(bool muteSet);
	void setBeDrawClock(bool b);
	void setBePoweredOffByUser(bool b);
	bool isSearchMute(){
		return beSearchMute;
	}

	void setMute(bool muteSet);
	void setMuteNew(bool muteSet);

	void setVol(int volSet);
	int getVol();
	int getSrcVol(int src);
	void set响度频率(int 响度频率set);
	int get响度频率(){
		return 响度频率;
	}
	void set重低音截至频率(int 重低音截至频率set);
	int get重低音截至频率(){
		return 重低音截至频率;
	}
	void setLoundValue(int loundValue);
	int getLoundValue(){
		return loundValue;
	}

	void setBas(int basSet);
	void setMiddle(int middle);
	int getMiddle(){
		return middle;
	}
	int getBas(){
		return bas;
	}

	void setSuperBass(int treSet);
	 
	int getSuperBass(){
		return SuperBass;
	}

	void setTre(int treSet);
	 
	int getTre(){
		return tre;
	}

	void setBal(int balSet);
	int getBal(){
		return bal;
	}

	void setFad(int fadSet);
	int getFad(){
		return fad;
	}
	void setV_dsp(int v_dspSet);
	int getV_dsp(){
		return v_dsp;
	}
	//int bas;
	//int tre;

	void setLound(bool isLoundSet);
	bool isLound(){
		return beLound;
	}
	void startSmallVol();
	void markVolInc();
	void setnVolumeType(int nVolumeTypeSet,bool record=true);
	void setMuteDelay(int sleepTime);
	void setDvdMuteDelay(int sleepTime);
	void setBright(int brightSet);
	int getBright();
	int nextVol();
	void clearStepVol();
	int getTrueVol();
	///
public:
	/*
	bool b刹车;
	bool b键盘声;
	bool b倒车影像;
	bool b导航兼听;
	*/
	int hourType;
	int runMode;
	//
	bool showBtBook;
	bool autoChangeBright;

	int screenWidth;
	int screenHeight;

	bool isFMStore;

	bool isDesignMode(){return runMode==DESIGN_MODE;};
	bool isRunMode(){return runMode==RUN_MODE;};


	bool runGpsWhenStart;

	ControlData();
	void setWillDataInitValue();
	void setPowerOnVol(int volSet,int id);
	void setPowerOnInitVol();
	void saveData();
	void loadData();
	void saveDefaultData();
	void setVolByScrn(int n);
	bool isVolChanged();
	int getVolByScrn();
	void setBtCallVol(int volval);
public:
	bool IsHaveCalling;
	bool IsInTalking;
	bool IsTelDialing;
	bool set安吉星ON(bool on);
	bool set标致车系电话接入(bool on);

//=========================add 20130808=======
	int DVD_PowerOn_Vol;
	int AUX_PowerOn_Vol;
	int 收音机_PowerOn_Vol;
	int 蓝牙_PowerOn_Vol;
	int 蓝牙音乐_PowerOn_Vol;
//============================================
//=========================20140214===================
	int fileProgressBar;
	void setFile_Progress_Bar(int n);
//=============================
	void setDVD_PowerOn_Vol(int n);
	void set收音机_PowerOn_Vol(int n);
	void set蓝牙_PowerOn_Vol(int n);
	void set蓝牙音乐_PowerOn_Vol(int n);
	void setAUX_PowerOn_Vol(int n);
	//=============================
};


extern ControlData workData;
extern ControlData willData;

#define ENTER_RUN_MODE	willData.runMode=RUN_MODE;
#define ENTER_DISIGN_MODE	willData.runMode=DESIGN_MODE;
#define IS_DESIGN_MODE	willData.isDesignMode()
#define IS_RUN_MODE	willData.isRunMode()

#define SCREEN_WIDTH	willData.screenWidth
#define SCREEN_HEIGHT	willData.screenHeight
unsigned char *getCurrentDataBuffer();
void updateShow(UINT8*workBuf);
#ifdef WINCE
//void drawVolumeOrBright();
void updateScrenVolume();
#else
#define updateScrenVolume()
#endif

#ifndef WINCE 
#define RETAILMSG(x,x1)
#endif


void closeVolWin();
int showWIN3(DWORD phy_addr,int width,int height,int x,int y,bool resetWindow);

#define TURN_NULL		0
#define TURN_VOLUMNE	1
#define TURN_BRIGHT		2
#define TURN_前后		3
#define TURN_左右		4
#define TURN_高音		5
#define TURN_低音		6
#define TURN_重低音		7
//define TURN_BLANCE		2
//#define TURN_MAX		6
#define TURN_MAX		2 
#define TURN_MAX_LONG	TURN_MAX
//#define TURN_MAX_LONG	TURN_重低音
// 只切换声音 和亮度。




void initDvdControl();
TCHAR *getTCHAR1_0(TCHAR *buffer,int maxLength,char*toDraw);

#define GetDiskNo(x)	(x->discNo_vmcd_ui_disc_index&0xf)
#define TIMMER_MAX	20
#define TIMMER_CMD	5
extern int keyVMCDTimmer;
extern int keyStopTimmer;
extern int beShowDataTime;

UINT8 *getCurrentScreenMem();
UINT8	*getBackGroundBuf();
void drawBackGroud(bool forceDraw=false);


void setBackGroundAs(char *name);
void getBackGround(char *name);
void initBackGround();
void heapdump(   HWND hwnd ,char *fileName  ) ;
void ZhwShowMessageBox(LPCWSTR lpText,LPCWSTR lpCaption,int TYPE);
void showSystemMessage(LPCWSTR lpText,LPCWSTR lpCaption,int TYPE);
char*getChar1_0(char *buffer,int len,TCHAR*toDraw);

extern bool messageBeModel;

#define DVD_NO_RESPONE  1
#define DVD_RUN			2
#define DVD_UNKOWN		0
extern int dvdState;
extern int dirFirst_seq;
extern int dirFile_Count;
extern int dirCurrent;

extern int fileFirst_seq;
extern int fileFile_Count;
extern int fileCurrent;

#define PI 3.1415926

void enterDarkScreen();

extern RECT rNormal;


// SOUND CHANDEL EXCHANGED 

//#define CMD_SELECT_SWAB00	10014
//#define CMD_SELECT_SWAB01	10015
//#define CMD_SELECT_SWAB10	10016
//#define CMD_SELECT_SWAB11	10017

//int changeToChanel(int n2313Chanel,int nSTM8AB);
/*
#define V4052_CH1	0
#define V4052_CH2	1

#define OPEN_DVD_VOLUME		changeToChanel(3,-1)
#define OPEN_RADIO_VOLUME	changeToChanel(2,-1)

#define OPEN_BT_VOLUME		changeToChanel(V4052_CH1,0)
#define OPEN_GPS_OUT_VOLUME	changeToChanel(V4052_CH1,1)
#define OPEN_MP5_VOLUME		changeToChanel(V4052_CH1,2)
#define OPEN_IIS_VOLUME		changeToChanel(V4052_CH1,3)

#define OPEN_IPOD_VOLUME	changeToChanel(V4052_CH2,0)
#define OPEN_CDC_VOLUME		changeToChanel(V4052_CH2,1)
#define OPEN_TV_VOLUME		changeToChanel(V4052_CH2,2)
#define OPEN_AUX_VOLUME		changeToChanel(V4052_CH2,3)
*/
void muteALL();

void muteOff();

#define META_蓝牙音乐	1
#define META_USB		2
#define META_SD			3
#define META_DISC		4
#define META_NONE		5

//void setMetaType(unsigned char type,bool force);

void setIsSearchMute(bool b);
void setIsMute(bool b);
void exchangeMute();
extern int nCurrentTurn;


#define CVBS_TP2	0
#define CVBS_DVD	1
void setCVBS_AS(int n);



void hideTaskBar();

void showTaskBar();



typedef struct _memLocs{
	ZString SCRN_NO;
	PVOID address;
	HDC memDc;
	DWORD usedTime;
}MEM_ALLOC;





void report(char *);
extern ZString reportString;
extern int reportTimer;







void setFad前();
void setFad后();
void setBalLeft();
void setBalRight();
void setBasLeft();
void setBasRight();
void setTreLeft();
void setTreRight();

char *getTurnName(int nCurrentTurn);

void clearAllCachedBackGround();
extern bool beSystemExit;

#define SYSTEM_WILL_CLOSE()		beSystemExit


#define UNKOWN		-1
#define YUV_7181	0
#define CVBS_TOP0	1
#define CVBS_TOP1	2
#define YUV_7181_GPS	3


extern int nCurrent7181STATE;
void setCamAsYUV();
void setCamAsCVBS(int n);
 void setAVISource(int source);
void postTouchCmd(int x,int y);

typedef void (*V_CALL_ID)(DWORD d);
int addDelayTask(V_CALL_ID callBackFunction,long timeToDelay);



#endif

bool startsWith(char *cc,char *pref);



void scanTaskToexecut();

#define SRC_MAIN_MENU	0
#define SRC_DVD			1
#define SRC_SD			2
#define SRC_USB			3
#define SRC_RADIO		4
#define SRC_GPS			5
#define SRC_BT			6
#define SRC_BT_MUSIC	7
#define SRC_AUX			8
#define SRC_USB2		9
#define SRC_AUX2		10
#define SRC_CARDVR		11
#define SRC_CARLIFE		12

void setSrcType(int type);
int getSrcType();

extern int inGps;



void drawMute();
void showVolumeWindow();
void hideVolumeWindow();
void showMuteWindow();
void hideMuteWindow();

void markContrlDataChanged();


#define FXP_RESET		(0|FXP_TRASLATE_KEY)
#define FXP_QUE_REN		(1|FXP_TRASLATE_KEY)
#define FXP_CLEAR		(2|FXP_TRASLATE_KEY)
#define FXP_MUTE		(3|FXP_TRASLATE_KEY)
#define FXP_POWER		(4|FXP_TRASLATE_KEY)
#define FXP_VOL_SUB		(5|FXP_TRASLATE_KEY)
#define FXP_VOL_ADD		(6|FXP_TRASLATE_KEY)
#define FXP_PREV		(7|FXP_TRASLATE_KEY)
#define FXP_NEXT		(8|FXP_TRASLATE_KEY)
#define FXP_MODE		(9|FXP_TRASLATE_KEY)
#define FXP_RADIO		(10|FXP_TRASLATE_KEY)
#define FXP_GPS			(11|FXP_TRASLATE_KEY)
#define FXP_DVD			(12|FXP_TRASLATE_KEY)
#define FXP_CALL_TEL	(13|FXP_TRASLATE_KEY)
#define FXP_CANCEL_TEL	(14|FXP_TRASLATE_KEY)
#define FXP_EQ			(15|FXP_TRASLATE_KEY)


POINT getCurrentMuteLocation();


void _F_PUB_忽略本按钮();

bool beEnterBack();

bool isInMainThread();
bool isInMainThreadAndReport();




#define MAX_VOL			30
#define INIT_VOL		10
#define SMALL_VOL		10

#define MAX_BASS_TRE_DB	   20
#define MAX_SHUAI_JIAN3702 30
#define POP_CLASS_DB_L1	6
#define POP_CLASS_DB_L2	12	
#define MAX_响度 2

bool isScreenOnShow(int screenNo);
void zhw_strcat_s(char *strCat,int len,char *s1);

//void showMem(TCHAR *infor);
void showMem(char *infor);


typedef   void(*FileWorkFun)(TCHAR*fullName,TCHAR *shortName); 
void workDir(TCHAR* src,FileWorkFun fileWorkFun);


void convertStrToTchar(char *strSource,TCHAR *wstrTarget,int max);
void setAllScreenTxtNULL(ZString scrnNo);
void setAllScreenTxtMiddle(ZString scrnNo);
void setScreenTxtMiddle(int scrnNo,char *names[],int size);
int getMonthMaxDay(int m,int year);
//TCHAR *getLangTran(TCHAR *name);

bool installKeyHwnd();
void accOffOk();
void accOnOk();

RECT LargRect(RECT r,int w);
char *getCheBiao(char *name);


bool getParamValue(char *name);

bool getParamValueN(int nLoc);




unsigned int testJMIC_ON();

void waitForVolExecute();

#define TEMP_WORK_SCRN		1000 /** DC 绘制区域*/
#define JPG_LITTEL_CACH_NO	1001 /* 图片预览的缓存*/
//#define ICON_DATA_SCRN		1002 /* ICON 的缓存*/
//#define SZ_BACK_GROUND		1003 /* 时钟的缓存*/
//#define	D2_WORK_SCRN1		1004 /* 2D 动画绘制区*/	
//#define	D2_WORK_SCRN2		1005 /* 2D 动画绘制区*/	
//#define BackGroundID		1006 /* 背景缓存区 */
#define WORK_SCRN			1007 /* WORK BUFFER */
#define DH_SCRN				1008
#define DH_OLD_SCRN				1009


void reportT(TCHAR *);

extern ZString actScrnNo;

//#define SUPORT_PINP

void needConfirm(char *titleSet,char *infor,void (*functionExitInit)(),void (*functionOKInit)());

int getCurrentVlumeType();

/** 设置是否需要现实雷达 */
bool isWillDraw雷达WhenBack();

bool is分体机();

void exchange分体机ToUsb();
void exchange分体机ToSd();


void stateUpdateProxy(unsigned long l);


 FILE *createWriteOutPropFile(ZString &fileName);
 FILE *openReadinPropFile(ZString &fileName);


extern char *uiBaseRoot;

void initGPIOFromDLL();

char *getRelateName(char *fileName,char *target);

TCHAR *getTUiRootName();

char *getUiRootName();

ZString&getSCRN_参数设置();

ZString&getSCRN_DVD();

int seh_filer(int code,struct _EXCEPTION_POINTERS *infor,int module);


void sendSrcChanged();


#define DIR_ACCESS_DVD	1

void beepDirect();

bool existDebug();
//#include "zhwlock.h"

bool isInStartUp();
void zhwResetSystem();

int executeARM11_CMD(DWORD cmd);
int executeARM11_CMD1(DWORD cmd,int nParameter);
int executeARM11_CMD2(DWORD cmd,int nParameter,unsigned char *buffer,int len);
int executeARM11_CMD_ALL(DWORD cmd,unsigned char *paramter,int paramterlen,unsigned char *buffer,int len);


#define UART_MODLE
WINBASEAPI BOOL WINAPI DeviceIoControl_prox(HANDLE hDevice, DWORD dwIoControlCode, __inout_bcount_opt(nInBufSize)LPVOID lpInBuf, DWORD nInBufSize, __inout_bcount_opt(nOutBufSize) LPVOID lpOutBuf, DWORD nOutBufSize, __out_opt LPDWORD lpBytesReturned, __reserved LPOVERLAPPED lpOverlapped);

#define SUPPORT_AUTO_FXP
#ifdef SUPPORT_AUTO_FXP
	#define updateParamterState()
#else
	void updateParamterState();
#endif

void strncpy_s_zhw(char *buffer,int lenToCopy,char *sss,int max);
void strcpy_s_zhw(char *buffer,int lenToCopy,char *sss);

#include "zstring.h"
#include "tzstring.h"
  QDateTime getTimeString(ZString &showTimeString,ZString&amPm);
void WriteExceptionDealed();

//hss
#define CONNECT_UNCONNECT 0
#define CONNECT_ING 1
#define CONNECT_OK 2
void setStateBtConnect();
void clrStateBtConnect();
BOOL isBtConnected();
#define DEFAULT_BT_PHONE_GAIN 63
#define FULL_BT_PHONE_GAIN 255

void enter屏幕调节(int screnNo);
void exchangeBright();

void darkMainUI();


#define VOL_DVD_2313		1
#define VOL_RADIO_2313		2
#define	VOL_IIS_2313		3
#define VOL_CDC_2313		4		
#define VOL_BT_2313			5
#define	VOL_AUX_2313		6
#define	VOL_AUX2_2313		8
#define	VOL_IPOD_2313		12
#define VOL_BT_MUSIC_2313_IIS	3
#define VOL_BT_MUSIC_2313_BT	7//5->7

#define VOL_CARLIFE_SYSTEM	14

#define PGB_LEN 184
#define HAVE_CAN_BUS

#define GET16COLOR(r,g,b) (((unsigned short)(r&0xF8))<<8)|((unsigned short)(g&0xFC)<<3)|((b&0xF8)>>3)
#define CONVERT_24_TO_16(c,loc) GET16COLOR(c[loc+2],c[loc+1],c[loc]);

extern BOOL beOverlayDvdShow;
void timmerToCloseOverlay();

void addScren(char *screenName,BaseStateEventItemV2&);;
//BaseStateEventItem

#define RETAILMSG_DC(x)

void releaseAllIfRequestHandleForThisThread();