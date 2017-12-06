#include  "pub.h"
#include "uartService.h"
//#include "iic_cmd.h"
#include "pub.h"



#define UART_OUT	1

#include  "pub.h"



#include "VerConfig.h"

#define SHOW_DOWN_LOAD_DATA	0

static char runGotoCmdOk=0;
HANDLE hSTM8_UARTCom;

bool connectOk=false;

int stm8BufferLoc=0;
unsigned char u8;

bool printReciveData=false;
bool bAccOff=false;

#define WANT_02		0
#define WANT_80		1
#define WANT_CMD	2
#define WANT_LEN	3
#define WANT_DAT	4
#define WANT_SUM	5

#define UART_SERVICE_BOOTLOADER	0
#define UART_SERVICE_SLAVE		1


static unsigned short nResultSerial;
static unsigned char checkSum=0;
static unsigned short executeResult;
static			char nResultLen=0;
static unsigned char nState=WANT_02;
static unsigned char rxBuffer[256];
static unsigned char rxBufferLoc=0;


int nCmdReceivedSerialNo=-1;
unsigned short nCmdExecuteResult=0;
bool cmdBeReceiveed=false;
int nCmdMessageGotedSerialNo=-1;
char receivedDataLen=0;
static unsigned char receivedData[256];


bool bHandShaked=false;
void writeData(unsigned short cmd,unsigned char len,unsigned char *data,unsigned short *serialNoP);
int executeSTM8IC_uart3360(DWORD cmd,unsigned char len,const unsigned char *cmdData,int loopTimes);
#include "收音机PUB.h"
extern RadioWork *radioWork;

int g_getCur=0;
unsigned char getStereoFlag=0;
unsigned char radioPlayState=RADIO_NULL;
unsigned char currentPreset=0;

void clearResult(){
	nCmdReceivedSerialNo=-1;
	cmdBeReceiveed=0;
	nCmdExecuteResult=0xFF;
	receivedDataLen=0;
	nCmdMessageGotedSerialNo=-1;
}


int waitForResult(int waitForNo){
	for(int i=0;i<20;i++){
		if(cmdBeReceiveed){
			return 1;
		}
		Sleep(10);// 等待200 没有收到对方的应答重新发送一次
	}
	return -1;
}

unsigned char BCDtoD(unsigned char ByteBCD){
	return ((ByteBCD/0x10)*10+(ByteBCD%0x10));
}
unsigned char DtoBCD(unsigned char ByteD){
	return ((ByteD/10)*0x10+(ByteD%10));
}

int nUartServiceType=0;
unsigned char keyType,key;
extern "C" 	void PRINT_FRQ(UINT16 Freq);
void DealMCU2ARM(unsigned short nResultSerial);
void DealMCUReply(unsigned short nResultSerial);
bool bNowUpdateMcu;
bool whenMcuUpdateGoOn(unsigned char nowCmd){

	if(bNowUpdateMcu){
		if((CMD_HANDSHAKE==nowCmd)||
				(CMD_MCU_REQUEST_PROG_DATA==nowCmd)||
				(CMD_REPORT_UPDATE==nowCmd)||
				(CMD_PROG_DATA==nowCmd)||
				(MCU_STRING_CMD==nowCmd)||
				(MCU_DATA_CMD==nowCmd)){
			return true;//升级只交流这些消息
		}else{
			return false;
		}
	}else{
		return true;//没升级
	}
}


//CMD_BEGIN
#define CMD_BEGIN       "menu_begin"


void foundCmd(char *cmd){
#define MAX_UP	30
	if(strcmp(cmd,CMD_BEGIN)==0){
		PostMessageZhw(MSG_START_MCU_UPDATE);
		return;
	}
}



extern bool inUpgradeSTM32;
void gotSTM8_UARTChar_stm32(BYTE c);

static void gotSTM8_UARTChar(unsigned char c){

	//if(inUpgradeSTM32){
		// MCU 升级，会一直执行直道重新启动
	//	gotSTM8_UARTChar_stm32(c);
	//	return;
	//}
	//addUpdateChar(c);
	//RETAILMSG_DC(1,(L"\r\n`%02X ",c));
	switch(nState){
		case WANT_02:
			if(c==0x02){	
				nState=WANT_80;	
			}
			break;
		case WANT_80:
			if(c==0x02){	
				nState=WANT_80;	
			}else if(c==0x80){//MCU reply ARM		/返回码+data
				nState=WANT_CMD;		
				checkSum=c;		
				nUartServiceType=UART_SERVICE_BOOTLOADER;
			}else if(c==0x81){//MCU send cmd to ARM	/only data		/MCU总认为ARM收到了 不需要返回应答
				nState=WANT_CMD;		
				checkSum=c;		
				nUartServiceType=UART_SERVICE_SLAVE;
			}else{	
				nState=WANT_02;	
			}
			break;
		case WANT_CMD:	
			{	
				nResultSerial=c&0xFF;		
				checkSum^=c;		
				nState=WANT_LEN;	
			}
			break;
		case WANT_LEN:  
			{	
				nResultLen=c;			
				checkSum^=c;		
				nState=WANT_DAT;
				if(nResultLen==0){		
					nState=WANT_SUM;
				}
				rxBufferLoc=0;
			}
			break;
		case WANT_DAT:	
			{
				rxBuffer[rxBufferLoc++]=c;
				checkSum^=c;
				if(rxBufferLoc>=nResultLen){
					nState=WANT_SUM;
				}
			}
			break;
		case WANT_SUM:
			{
				if(checkSum==c){
					cmdBeReceiveed=true;
					bool bCanGoOn=whenMcuUpdateGoOn(nResultSerial);
					if(bCanGoOn){
						if(nUartServiceType==UART_SERVICE_SLAVE){
							DWORD startDealMCU2ARM = GetTickCount();
							DealMCU2ARM(nResultSerial);
							if(GetTickCount()-startDealMCU2ARM>2){
								RETAILMSG(1,(L"DealMCU2ARM Spend Time = %d  Val=%x\r\n",GetTickCount()-startDealMCU2ARM,nResultSerial));
							}
							
						}else{
							DWORD startDealMCUReply = GetTickCount();
							DealMCUReply(nResultSerial);//首字节返回码
							if(GetTickCount()-startDealMCUReply>2){
								RETAILMSG(1,(L"DealMCUReply Spend Time = %d  Val=%x\r\n",GetTickCount()-startDealMCUReply,nResultSerial));
							}
						}
					}
				}
				nState=WANT_02;
			}
			break;
	}
}
typedef struct __KeyMap{
	char *key;
	LPARAM keyValue;
	int fxp_key;
	bool suportRepeatKey;
} KeyMap;
#define MAX_KEY	15
extern KeyMap keyMap[MAX_KEY];
extern unsigned char fxpValue[4];
extern HWND hGlobal;
bool bGoOnProData=false;
unsigned char cDvdState=0x00;
void	dealValue(unsigned char type,unsigned char value);
void setScreenBright();
void setScreenBrightBy3360(int n);
bool bBigLightOn=false;
unsigned char brakeState =false;
bool isBreakFlag = false;
void realTimeBreakViedo(bool sor);
bool is刹车检测();

void setBreakViedoFlag(){
	if(is刹车检测())
	{
		/*if(brakeState)
		{
			isBreakFlag = true;
		}else
		{
			isBreakFlag = false;
		}*/
		isBreakFlag=true;
	}else{
		isBreakFlag = false;
	}
}


bool bMSG_REVERSE_OPEN=0;
bool isIllAutoOn();

UINT8 MCU_TEMP = 0;
UINT8 MCU_SPEED = 0;
static UINT8 lastMcuTemp=0;
static UINT8 lastSpeed=0;
static DWORD tempTimeRecord =0;
static int tenTimeTotal = 0;
int tempTimeCount=0;
UINT8 TEMPMiddle =0;
bool canShowTemp=false;
void changedChanelVolume(int nChanel,int nSecondChanel,int volSet);
void setBlackScreen();
void DealMCU2ARM(unsigned short nResultSerial){
	unsigned char dvdStateTemp,reverseState;

	switch(nResultSerial){
		case CMD_MCU_REPORT_STA:
			// DVD 倒车 大灯 刹车 启动源
			{
				static unsigned char rxBuffer_0=0xFF;
				static unsigned char rxBuffer_1=0xFF;
				static DWORD lLastReport=0;
				if(rxBuffer_0==rxBuffer[0]&&
					rxBuffer[1]==rxBuffer_1&&
					GetTickCount()-lLastReport<1000){
				}
				rxBuffer_0=rxBuffer[0];
				rxBuffer_1=rxBuffer[1];
				lLastReport=GetTickCount();

			}
			dvdStateTemp=rxBuffer[0];
			reverseState=rxBuffer[1]&0x01;
			brakeState=rxBuffer[1]&0x04;

#ifndef BK09_LOW_VER
			if(reverseState==0x01){				
				void setBlackScreen();
				if(!bMSG_REVERSE_OPEN){
					//setBlackScreen();//倒车时先让屏幕黑屏 防止灰屏
				}				
				bMSG_REVERSE_OPEN=true;
				RETAILMSG_DC(1,(L"CMD_MCU_REPORT_STA  \n"));
				return;
			}else{
				RETAILMSG_DC(1,(L"CMD_MCU_REPORT_STA  close\n"));
				bMSG_REVERSE_OPEN=false;				
				if(willData.beClosedScreen){		
					willData.setCloseScreen(true);//关屏倒车恢复关屏
				}				
			}
#endif			
			if(brakeState){			
				//刹车
				isBreakFlag = false;
			}else{			
				isBreakFlag = false;
				if(is刹车检测()){
					isBreakFlag = true;
				}
				//行车
			}

				
			break;

		case MCU_SPEED_AND_TEMP:
			/*MCU_SPEED = rxBuffer[0];

			if(lastSpeed!=MCU_SPEED){
				lastSpeed=MCU_SPEED;
				if(MCU_SPEED>60&&MCU_SPEED<180){
					PostMessageZhw(MSG_SPEED_CHANGE,0);
				}
			}

			MCU_TEMP = rxBuffer[1];	
			if(lastMcuTemp!=MCU_TEMP){
				lastMcuTemp=MCU_TEMP;
				RE_DRAW;
			}*/

			/*if(GetTickCount()-tempTimeRecord>2000){
				tempTimeRecord=GetTickCount();
				tenTimeTotal+=rxBuffer[1];
				tempTimeCount++;
				if(tempTimeCount==5){
					TEMPMiddle=rxBuffer[1];//记录10次采样中间的数据
				}
			}
			if(tempTimeCount==10){
				if(TEMPMiddle==(tenTimeTotal/10)){//有效数据
					MCU_TEMP = TEMPMiddle;	
					canShowTemp=true;
					if(lastMcuTemp!=MCU_TEMP){
						lastMcuTemp=MCU_TEMP;
						RE_DRAW;
					}
				}
				tempTimeCount=0;//每10次清理一次
				tenTimeTotal=0;
			}*/			
			//RETAILMSG_DC(1,(L"MCU_TEP = %d MCU_SPEED=%d\r\n",MCU_TEMP,MCU_SPEED));
			
			break;

		case CMD_MCU_SRC_CHANGE:
			//NONE
			break;
		case CMD_MCU_VOL_CHANGE:
			//或许可以发送硬件静音标志
			break;
		case CMD_MCU_EQ_CHANGE:
			//NONE
			break;
		case CMD_MCU_CMD:
			PostMessageZhw(MSG_KEY_EVENT,rxBuffer[1]);
			RETAILMSG_DC(1,(L"Receive Mode key=%x %d\r\n",rxBuffer[1],GetTickCount()));	
			break;
		case CMD_MCU_REPORT_RADIO:
			//MCU主动发送的收音信息 ??
			break;
		case CMD_MCU_REPORT_CDC:
			//NONE
			break;
		case CMD_MCU_REPORT_SYS:
			//MCU没有主动报告 E_SYS_SET_INDEX 等项目
			break;
		case CMD_MCU_REPORT_SWC:
			//SWC映射表
			for(int i=0;i<MAX_KEY;i++){
				//keyMap[i].keyValue=rxBuffer[i*2];//数据太长
				//keyMap[i].keyValue=rxBuffer[i];//一个按键一个字节
			}
			break;
		case CMD_MCU_REPORT_SAMPLE:
			//方向盘学习 采样事件
			if(nResultLen==0x02){
				if(rxBuffer[0]==0x01){
					report("此按键已经学习 请选择方控其他按键");
				}
			}else if(nResultLen==0x04){
				fxpValue[0]=rxBuffer[0];//high
				fxpValue[1]=rxBuffer[1];//low
				fxpValue[2]=rxBuffer[2];
				fxpValue[3]=rxBuffer[3];
			}
			break;
		case CMD_MCU_REQUEST_SRC:
			//??
			break;
		case CMD_MCU_REPORT_STA2:
			//NONE
			break;
		case CMD_MCU_REPORT_ACC:
			//ACC 检测	//只处理ACCOFF
			if(rxBuffer[0]==0x00){
				//sendAutoNaviAccOff();
				PostMessageZhw(MSG_KEY_EVENT,ACC_OFF);//HSS TEST  dealAccOnOff
				bAccOff=true;
				changedChanelVolume(0,-1,0);				
				//setBlackScreen();
			}
			break;
		case CMD_MCU_REQUEST_PROG_DATA:
			//请求继续发送MCU升级数据
			bGoOnProData=true;			
			break;
		case CAN_MCU_INFO:
			void dealR102OneFrame(unsigned char ca[],int len);
			//dealR102OneFrame(rxBuffer,nResultLen);			
			break;
		default:
			break;
	}
}

unsigned char receiveRSSI=0;
unsigned char radioVolAmp=0;
void setRadioData(int totalPage,int thisPage,int currentFre);
static int prelist[6]={8750,8750,8750,8750,8750,8750};
char mcuVer[32];
DWORD lastGetRadioTickTime=0;
static unsigned char saveCurrentPage=0;
char machineTypeFromMcu=0xff;
extern char machineTypeConfig;
/* //radio 信息
0x00  信息类型 00
0x01  Min Frequency
0x03  Max Frequency
0x05  Granularity 
0x06  Signal 
0x07  Radio status 

0x00  信息类型 01
0x01  Current Band 
0x02  Current Preset 
0x03  Cur Frequency 
0x05  Preset List 
*/
unsigned char uuIdDevice[12]={0};
extern bool bMSG_REVERSE_OPEN;


RadioWork *getFMWorker();

RadioWork *getAMWorker();

bool requestMcuUpdateSuc=false;
void radioSearchOver(void){
}

unsigned char beNeedSetFreqAtSearchOver=0;
#pragma pack (1)
#define uint8_t unsigned char
typedef struct _PresetList{
  uint8_t head;
  uint8_t cmd;
  uint8_t len;
  uint8_t success;
  uint8_t PresetList;
  uint8_t CurrentBand;
  uint8_t inPlaying;
  uint8_t currentPlH;
  uint8_t currentPlL;
  uint8_t usn;
  uint8_t wam;
  uint8_t var;
  uint8_t levelH;
  uint8_t levelL;
  uint8_t offsetH;
  uint8_t offsetL;
}PList;
PList plRRR;
#pragma pack ()


void DealMCUReply(unsigned short nResultSerial){
	switch(nResultSerial){
		case CMD_HANDSHAKE:
			bHandShaked=true;
			//RETAILMSG_DC(1,(L"Handshake with MCU\r\n"));
			break;
		case CMD_SET_BAUDRATE:
			//NONE
			break;
		case CMD_INIT_REQUEST:
			{
				for(int i=0;i<12;i++){
					uuIdDevice[i]=rxBuffer[i];
				}
				//setDeviceIdData(uuIdDevice);
			}
			//??
			break;
		case CMD_REQUEST_MCU:
			//主要获取是否有DVD 启动源由ARM控制 启动后可以主动获取一次倒车 大灯 刹车的状态
			cDvdState=rxBuffer[1+0]&0x02;//仅检测是否存在
			machineTypeFromMcu=rxBuffer[1+2];//2015-5-23
			if(rxBuffer[1+1]&01){
				for(int i=0;i<100;i++){
					if(hGlobal==NULL){
						Sleep(20);
					}
					else{
						//PostMessage(hGlobal, MSG_REVERSE_OPEN, NULL, NULL);
						RETAILMSG_DC(1,(L"CMD_REQUEST_MCU ENTER"));
						bMSG_REVERSE_OPEN=true;
						break;
					}
				}
			}
			break;
		case CMD_REPORT_MCU:
			//NONE
			break;
		case CMD_SRC_CHANGE:
			//MEAN OK
			break;
		case CMD_REQUEST_VOL:
			//NONE
			break;
		case CMD_SET_VOL:
			//MEAN OK
			break;
		case CMD_REQUEST_EQ:
			//NONE
			break;
		case CMD_SET_EQ:
			//NONE
			break;
		case CMD_CMD_TO_MCU:
			//MEAN OK ， BUT NO NEED
			break;
		case CMD_XY_TO_MCU:
			//NONE			
			break;
		case CMD_FOUND_ONE_PL:
			{
				{
					// print all RADIO MSG
					TCHAR buf[1000];
					TCHAR p[30];
					wcscpy(buf,L"\r\nRADIO  0XBE ");
					for(int i=0;i<nResultLen;i++){
						//wsprintf(p,L" 0x%02X ",rxBuffer[i]);
						//wcscat(buf,p);
					}
					wcscat(buf,L"\r\n");
					//RETAILMSG(1,(L"%s",buf));
				}
				g_getCur=(int)(rxBuffer[1]<<8)+rxBuffer[2];
				if(rxBuffer[0]<=2){
					//getFMWorker()->foundPl(g_getCur);
				}else{
					//getAMWorker()->foundPl(g_getCur);
				}
			}
			break;
		case CMD_REQUEST_RADIO:
			//收音信息
		{
				// print all RADIO MSG
				TCHAR buf[1000];
				TCHAR p[300];				

				memset(&plRRR,0,sizeof(plRRR));
				wcscpy(buf,L"\r\nRADIO  0XB3 ");
				unsigned char *pa=(unsigned char *)&plRRR;
				memcpy(pa+4,rxBuffer+1,sizeof(plRRR)-4);
				for(int i=0;i<nResultLen;i++){
//					wsprintf(p,L" 0x%02X ",rxBuffer[i]);
					//wcscat(buf,p);
				}
				if(rxBuffer[1+0]==1){
				//	wsprintf(p,L"(  %d level:%d usn:%d wam:%d offset:%d)",(plRRR.currentPlH<<8)+plRRR.currentPlL,(plRRR.levelH<8)+plRRR.levelL,
				//		plRRR.usn,plRRR.wam,(plRRR.offsetH<<8)+plRRR.offsetL);
				//	wcscat(buf,p);
				}
				
				//wcscat(buf,L"\r\n");
				//RETAILMSG(1,(L"%s",buf));
			}
			if(rxBuffer[1+0]==0x01){
				currentPreset=rxBuffer[1+2];
				g_getCur=(int)(rxBuffer[1+3]<<8)+rxBuffer[1+4];
				saveCurrentPage=rxBuffer[1+1];
				beNeedSetFreqAtSearchOver=1;
				//if(GetTickCount()-lastGetRadioTickTime>150){//don't too quick change form 100 to 150
				//	lastGetRadioTickTime=GetTickCount();
					setRadioData(3,rxBuffer[1+1],g_getCur);
					//beNeedSetFreqAtSearchOver=0;
				//}
			}else if(rxBuffer[1+0]==0x00){
				getStereoFlag=(rxBuffer[1+7]&0x10)?1:0;
				void set立体声开关(bool b);
				if(rxBuffer[1+7]&0x20){
					//set立体声开关(true);
				}else{
					//set立体声开关(false);
				}
				if(rxBuffer[1+7]&0x03){
					radioPlayState=RADIO_SEEK;
				}else if(rxBuffer[1+7]&0x04){
					radioPlayState=RADIO_SCAN;
				}else if(rxBuffer[1+7]&0x08){
					radioPlayState=RADIO_STORE;
				}else if(rxBuffer[1+8]&0x01){
					radioPlayState=RADIO_PS;
				}else{
					if(radioPlayState!=RADIO_NULL){//last is seek/aps/scan/ps
						lastGetRadioTickTime=0;//may redraw again
						setRadioData(3,saveCurrentPage,g_getCur);
					}
					radioPlayState=RADIO_NULL;
				}
				receiveRSSI=rxBuffer[1+6];//信号强度
				if(rxBuffer[1+9]!=RADIO_NXP6621){
					radioVolAmp=1;//si系列放大倍数
				}else{
					radioVolAmp=0;//6621放大倍数
				}
			}else if(rxBuffer[1+0]==0x02){
				// searchOver
				//if(beNeedSetFreqAtSearchOver){
				//	setRadioData(3,saveCurrentPage,g_getCur);
				////	beNeedSetFreqAtSearchOver=0;
				//}
				radioSearchOver();
			}
			break;
		case CMD_REQUEST_CDC:
			//NONE
			break;
		case CMD_REQUEST_SYS:
			//APP启动后获取一些系统参数
			if(SYS_SET_TIME==rxBuffer[1+0]){//获取时间 时制由controlDataSaveList保存
				/*
				SYSTEMTIME showNowTime;
				GetLocalTime(&showNowTime);
				showNowTime.wYear=(WORD)(BCDtoD(rxBuffer[1+1])*100)+BCDtoD(rxBuffer[1+2]);
				showNowTime.wMonth=BCDtoD(rxBuffer[1+3]);
				showNowTime.wDay=BCDtoD(rxBuffer[1+4]);
				showNowTime.wHour=BCDtoD(rxBuffer[1+5]);
				showNowTime.wMinute=BCDtoD(rxBuffer[1+6]);
				showNowTime.wSecond=BCDtoD(rxBuffer[1+7]);
				RETAILMSG_DC(1,(L"%d年%d月%d日 %d时%d分%d秒\r\n",showNowTime.wYear,showNowTime.wMonth,showNowTime.wDay,showNowTime.wHour,showNowTime.wMinute,showNowTime.wSecond));
				if(FALSE==SetLocalTime(&showNowTime)){
					RETAILMSG_DC(1,(L"SetLocalTime FAIL\r\n"));
				}
				*/
			}else if(SYS_SET_COMMON==rxBuffer[1+0]){//AMP设置
			
			}else if(SYS_SET_VIDEO==rxBuffer[1+0]){//屏幕参数
			
			}else if(SYS_SET_RADIO==rxBuffer[1+0]){//设置收音
				unsigned char radioT=rxBuffer[1+2]&0x7f;
				RETAILMSG_DC(1,(L"设置收音芯片类型：%d\r\n",radioT));
				if(rxBuffer[1+2]&0x80){
					//成功
					report("收音设置成功");
				}else{
					//失败
					report("收音设置失败");
				}
			}
			break;
		case CMD_SET_SYS:
			//MEAN OK
			break;
		case CMD_REQUEST_SWC:
			//获取SWC映射表
			break;
		case CMD_SET_SWC:
			//NONE
			break;
		case CMD_FXP_LEARN:
			//??
			break;
		case CMD_REQUEST_MCU_VER:
			//获取MCU版本号
			for(int i=0;i<nResultLen;i++){
				mcuVer[i]=rxBuffer[1+i];
			}
			break;
		case CMD_REPORT_UPDATE:
			requestMcuUpdateSuc=true;
			{
				extern bool reSendMcuUpdate;
				reSendMcuUpdate=true;
			}

			//MEAN OK
			break;
		case CMD_PROG_DATA:
			//MEAN OK				
			break;
		case MCU_STRING_CMD:
			
			//for(int i=0;i<nResultLen;i++){
				rxBuffer[nResultLen]=0;
				if(!inUpgradeSTM32){
					// 没有开始升级
					//addUpdateChar(rxBuffer[i]);
					
					foundCmd((char*)rxBuffer);
				}else{
					void foundCmdInUpgrad(char *cmd);
					//foundCmdInUpgrad((char*)rxBuffer);
					//gotSTM8_UARTChar_stm32(rxBuffer[i]);
				}
			//}
			break;
		case MCU_DATA_CMD:
			//gotSTM8_UARTChar_stm32(rxBuffer[0]);
			break;
//			#define MCU_STRING_CMD				0XE0
//#define MCU_DATA_CMD                0XE1
		default:
			break;
	}
}

bool isMcuNormalWork=true;
static int mcuExceptionNum=0;
DWORD WINAPI detectedMcuThread(LPVOID lparam){
	/*while(1){
		Sleep(1000);
			__try
			{
				if(runGotoCmdOk){
					if(!bNowUpdateMcu){
						unsigned char cmdData[1]={0x00};
						executeSTM8IC_uart3360(0xA0,0,cmdData,1);//发数据给mcu
						Sleep(1000);
						if(!isMcuNormalWork){
							mcuExceptionNum++;
							if(mcuExceptionNum>15){
								PostMessageZhw(MSG_TO_RESET_MCU,0);
								mcuExceptionNum=0;
							}
						}
					}					
				}	
			}
			__except(seh_filer(GetExceptionCode(),GetExceptionInformation(),200))
			{
				RETAILMSG_DC(1,(L"detectedMcuThread thread Exception!\n"));
			}

	}*/
	return 1;
}


DWORD sendHankshake15s=0;
DWORD resetMcuTime60s=0;
DWORD WINAPI STM8_UARTThreadFunc0(LPVOID lparam)
{
       
       return 0;
}

int seh_filer(int code,struct _EXCEPTION_POINTERS *infor,int module);

DWORD WINAPI STM8_UARTThreadFunc(LPVOID lparam){
		return STM8_UARTThreadFunc0(lparam);
}

int initSTM8_UARTDCB()
{
    return 1;
}

int OpenComTESTSTM8_UART()
{
	return 1;
}

void writeSTM8_UARTCmd(unsigned char *data,int size,unsigned char *re,bool needWait=false){
	if(inUpgradeSTM32)
		return;
	DWORD nwrited;
	//WriteFile(hSTM8_UARTCom,data,size,&nwrited,NULL);
}

bool bReplyMcu=false;
void writeData(unsigned short cmd,unsigned char len,unsigned char *data,unsigned short *serialNoP){
}

void getParam0XB8FromMcu()
{
}

DWORD WINAPI runGotoCmd(LPVOID lparam)
{
	return 0;
}



#define u8 unsigned char
#include "pub.h"
bool isAccHaveUped();
bool isAccOn();


int executeSTM8IC0_uart(DWORD cmd,unsigned char b0,unsigned char b1,int loopTimes){
	return 0;
}

int executeSTM8IC_uart(DWORD cmd,unsigned char b0,unsigned char b1){
	return 0;
}


int executeSTM8IC_uart3360(DWORD cmd,unsigned char len,const unsigned char *cmdData,int loopTimes){
	return 0;
}

int executeSTM8IC_uart3360(DWORD cmd,unsigned char len,const unsigned char *cmdData){
	return 1;
}

extern int loadType;
#include "sdusb_control.h"
static int lastSendSrc=0xffff; 
void clearLastSendSrc(){
	lastSendSrc=0xffff;
}
void toScreenExecuteSTM8()
{
	
}



UINT32 getCurrentBright(int n);
void setParamXOB8ToMcu()
{
}

bool btDisconnect(unsigned int bt_no);
void saveScreen();
void accOffsendBackMcu()
{
	
}

DWORD dvdOutThread(LPVOID lpParameter)
{
	return 1;
}

void dvdEject(){
	
}

void setHardMute()
{
	
}

void setHardMuteOff()
{
	
}

bool isM20(){
	return (machineTypeFromMcu=='M');
}
static bool bMcuShowVol=false;
//static bool bMcuShowMute=false;
void sendMuteOrUnMute(){
	
}
void sendVolOpenAndUnMute(){//取消MUTE且显示声音
	
}
void sendVolClose(){//取消显示音量
	
}
extern int fR_Val;
extern int lR_Val;
void sendFad(){
	
}
void sendBal(){
	
}

void sendEqType(char type){
}


void sendMediaInfo(unsigned int trackNo,unsigned int playSec,u8 playMode){
}

extern int oldMetaSrcType;
void sendMcuSrcClose(int src){
	if(!isM20())
		return;
	if(src==oldMetaSrcType){
		const unsigned char cmdData[2]={SOURCE_OFF,SOURCE_OFF};
		executeSTM8Cmdnew(CMD_SRC_CHANGE,sizeof(cmdData),cmdData);
	}
}