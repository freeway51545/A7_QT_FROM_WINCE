#include <qscrollbar.h>
//@Override


// 
//		��ӹ�����
//
//		����б�ؼ�
//
//
#include "������pub.h"
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

// 1. �������������͡�
// 2. �������ͽ���ʵ�ʵĹ�����


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
	//si4730_powerOnRADIO();// ��·���� 4730 �� 6621 ͬһ�������
#endif	
}

bool changed��̨=false;
long lLastChange��̨Time=0;

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

void saveData��̨00(HANDLE hHandle){

}

void saveData��̨0(bool force){

}



int seh_filer(int code,struct _EXCEPTION_POINTERS *infor,int module);

void saveData��̨(bool force){
		
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




static void loadData��̨0(){

}


void loadData��̨(){

}

void makeChanged��̨(){
	changed��̨=true;
	lLastChange��̨Time=GetTickCount();
}

//bool BE����������=true;
bool BE����������=false;//hss

void set����������(bool b){
	BE����������=b;
}

bool ����������������(){
	return BE����������;
}

 void exchange����������(){
	 BE����������=!BE����������;
 }
