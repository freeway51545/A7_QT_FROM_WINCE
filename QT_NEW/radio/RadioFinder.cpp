#include <qscrollbar.h>
//@Override


// 
//		添加滚动条
//
//		添加列表控件
//
//
#include "收音机pub.h"
#include "radioControl.h"
//#ifdef WINCE
//#include "csync.h"
//#else
class CLockObject{
public:
	void Lock(){};
	void Unlock(){};
};
//s#endif

// 1. 查找收音机类型。
// 2. 根据类型进行实际的工作。


//bool beFoundSyj=false;


#define SYJ_6621	0
#define SYJ_4730	1
#define SYJ_6640	2

#define syj_type SYJ_6621
FMRadioWork *getWindowsFMRadio();
AMRadioWork *getWindowsAMRadio();


#define SAVE_RADIO_FILE_FM L"/Residentflash3/system_init/FM_LIST.save"
#define SAVE_RADIO_FILE_AM L"/Residentflash3/system_init/AM_LIST.save"



RadioWork *getFMWorker(){
	return getWindowsFMRadio();
}



RadioWork *getAMWorker(){
	return getWindowsAMRadio();
}



extern "C"{
void si4730_powerOnRADIO();
};

void powerOnRadio(){
#ifdef WINCE
	//si4730_powerOnRADIO();// 线路共用 4730 和 6621 同一个供电脚
#endif	
}

bool changed电台=false;
long lLastChange电台Time=0;

CLockObject lockWriteRead;


static const TCHAR * readioFile=L"/Residentflash3/system_init/radioList.sav";
static const TCHAR * readioFileBack=L"/Residentflash3/system_init/radioList_back.sav";


static bool verifyRadioData(FILE* hHandle,const TCHAR *fileName){
	//char buffer[100];
	//int nn;
	if(!getFMWorker()->verifyData(hHandle)){
		return false;
	}
	if(!getAMWorker()->verifyData(hHandle)){
		return false;
	}
	return true;
}

static bool verifyRadioData(const TCHAR *fileName){
	return false;
}

void saveData电台00(HANDLE hHandle){

}

void saveData电台0(bool force){

}



int seh_filer(int code,struct _EXCEPTION_POINTERS *infor,int module);

void saveData电台(bool force){
		
}


void saveRadioWhenPowerOff(){
	
}




int readLineData(HANDLE hHandle){
#ifdef WINCE
	char buffer[100];
	char *line=readLine(buffer,hHandle,100);
	if(line==NULL)
		return 0;
	line=strstr(buffer,"=");
	if(line==0)
		return 0;
	int n;
	sscanf(line,"=%d",&n);
	return n;
#else
	return 0;
#endif
}




static void loadData电台0(){

}


void loadData电台(){

}

void makeChanged电台(){
	changed电台=true;
	lLastChange电台Time=GetTickCount();
}

//bool BE立体声开关=true;
bool BE立体声开关=false;//hss

void set立体声开关(bool b){
	BE立体声开关=b;
}

bool 收音机立体声开关(){
	return BE立体声开关;
}

 void exchange立体声开关(){
	 BE立体声开关=!BE立体声开关;
 }
