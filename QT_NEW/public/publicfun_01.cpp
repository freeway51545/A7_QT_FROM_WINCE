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

void CALLBACK lpTimmerFuncZhw(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime );

DWORD WINAPI timmerThread(LPVOID lparam){
	Sleep(1000);
	while(1){
		Sleep(100);
		try
		{
			extern HWND hGlobal;
			lpTimmerFuncZhw(hGlobal,0,0,0);
			willData.markVolInc();			
		}
		catch(...)
		{
			
			RETAILMSG_DC(1,(L" timmerThread MEE A EXCEPTION \r\n"));
		}
		releaseAllIfRequestHandleForThisThread();
	}
	return 0;
}



DWORD WINAPI gpsSpyThread(LPVOID lparam);
DWORD WINAPI gpsSpyThreadLost(LPVOID lparam);
void powerOnMethod(bool accOn);

void startSTM8_UARTService();

DWORD WINAPI send8202CMDThread(LPVOID lparam);
DWORD WINAPI timmerThreadA(LPVOID lparam);
DWORD WINAPI detectedMcuThread(LPVOID lparam);
bool beInAttention=true;
void start8202ServiceA(){
	
	bool accOn=true;
	willData.isAccOn=accOn;
	powerOnMethod(accOn);
	RETAILMSG_DC(1,(L"Start 8202 service OK \r\n"));
	/*CreateThread( 
             NULL,                    //安全属性使用缺省。
             0,                         //线程的堆栈大小。
             send8202CMDThread,                 //线程运行函数地址。
             0,               //传给线程函数的参数。
             0,                         //创建标志。
             0);*/       //成功创建后的线程标识码。
	/*
	CreateThread( 
             NULL,                    //安全属性使用缺省。
             0,                         //线程的堆栈大小。
             timmerThread,                 //线程运行函数地址。
             0,               //传给线程函数的参数。
             0,                         //创建标志。
             0);       //成功创建后的线程标识码。
	CreateThread( 
			NULL,                    //安全属性使用缺省。
			0,                         //线程的堆栈大小。
			timmerThreadA,                 //线程运行函数地址。
			0,               //传给线程函数的参数。
			0,                         //创建标志。
			0);       //成功创建后的线程标识码。
	CreateThread( 
			 NULL,                    //安全属性使用缺省。
			 0,                         //线程的堆栈大小。
			 phoneMapThread,                 //线程运行函数地址。
			 0,               //传给线程函数的参数。
			 0,                         //创建标志。
			 0);       //成功创建后的线程标识码。
	CreateThread( 
             NULL,                    //安全属性使用缺省。
             0,                         //线程的堆栈大小。
             gpsSpyThread,                 //线程运行函数地址。
             0,               //传给线程函数的参数。
             0,                         //创建标志。
             0);       //成功创建后的线程标识码。
	HANDLE hGpsThread=CreateThread( 
             NULL,                    //安全属性使用缺省。
             0,                         //线程的堆栈大小。
             gpsSpyThreadLost,                 //线程运行函数地址。
             0,               //传给线程函数的参数。
             0,                         //创建标志。
             0);       //成功创建后的线程标识码。
	/*CreateThread( 
		NULL,                    //安全属性使用缺省。
		0,                         //线程的堆栈大小。
		detectedMcuThread,                 //线程运行函数地址。
		0,               //传给线程函数的参数。
		0,                         //创建标志。
		0);       //成功创建后的线程标识码。*/
	
	//CeSetThreadPriority(hGpsThread,100);// 设置线程有限级别
//	startSTM8_UARTService();
	return;
}


ZString reportString("");
int reportTimer=0;

TCHAR *getTCHAR1_0A(TCHAR *tBuf,int maxLen,char *toDraw);


void reportLong(char *a){
	if(strlen(a)==0||a==NULL){
		if(reportTimer==0){
			return;
		}
	}
	TCHAR tBuf[1000];
	RETAILMSG_DC(1,(L"report1 :%s\r\n",getTCHAR1_0A(tBuf,sizeof(tBuf),a)));
	reportString=a;
	//strncpy_s_zhw(reportString,sizeof(reportString)-1,a,99);
	//reportString[99]=0;
	reportTimer=40;
	RE_DRAW;
}


void report(char *a){
	if(beEnterBack()){
		return;
	}		
	if(strlen(a)==0||a==NULL){
		if(reportTimer==0){
			return;
		}
	}
	TCHAR tBuf[1000];
	RETAILMSG_DC(1,(L"report :%s\r\n",getTCHAR1_0A(tBuf,sizeof(tBuf),a)));
	reportString=a;
	//strncpy_s_zhw(reportString,sizeof(reportString)-1,a,99);
	//reportString[99]=0;
	reportTimer=30;
	RE_DRAW;
	//reDrawAtOnce();
}

void reportAtonce(char *a){
	if(beEnterBack()){
		return;
	}		
	if(strlen(a)==0||a==NULL){
		if(reportTimer==0){
			return;
		}
	}
	reportString=a;
	reportTimer=30;
	//RE_DRAW;
	reDrawAtOnce();
}

void reportT(TCHAR *a){
	char cBuf[1000];
	report(getChar1_0(cBuf,sizeof(cBuf),a));
}




void sendDataAndTimeDataToCanBox();
/*
SYSTEMTIME getTimeString(ZString &showTimeString,ZString&amPm){
		SYSTEMTIME showNowTime;   
		GetLocalTime(&showNowTime);
		char *formatString="%02d:%02d";
		int hour=showNowTime.wHour;
		//amPm[0]=0;
		if(willData.hourType==12){
			if(hour>=12){
				amPm="PM";
				//strncpy_s_zhw(amPm,5,"PM",10);
				if(hour>12)
					hour-=12;
			}else{
				//strncpy_s_zhw(amPm,5,"AM",10);
				amPm="AM";
			}
		}else{
			amPm="";
		}
		showTimeString="";
		//showTimeString.catFormat("%d",hour).cat(":").catFormat("%02d",showNowTime.wMinute);
		//sprintf_s(showTimeString,100,"%d:%02d",hour,);
		showTimeString.format("%d:%02d",hour,showNowTime.wMinute);

		static int lastMinutes =0;
		if(lastMinutes!=showNowTime.wMinute){
			lastMinutes=showNowTime.wMinute;
			//sendDataAndTimeDataToCanBox();
			void sendIllChangeToMcu(int hour,int min);
			sendIllChangeToMcu(hour,showNowTime.wMinute);
		}
		return showNowTime;
}

*/
