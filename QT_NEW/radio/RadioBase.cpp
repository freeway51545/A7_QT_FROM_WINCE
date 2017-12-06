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

void writeStringToFile(FILE *fp,char *str){
}

#include "radioControl.h"

#define WriteFile(x)
#define CloseHandle(x)
#define INVALID_HANDLE_VALUE 0
bool RadioControl::isInSearch(){
	return beSearch;
}
void RadioControl::setInSearch(bool b){
	beSearch=b;
}

bool RadioControl::isInScan(){
	return beInScan;
}
void RadioControl::setInScan(bool b){
	beInScan=b;
}

RadioControl radionContrl;

void RadioWork::turnToCurrentProxy(){
}

void RadioWork::locAt(int loc){
	if(loc>=0&&loc<amount){
		//beginLoc=loc/8*8;
		current=��̨[loc];		
		turnToCurrentProxy();
		makeChanged��̨();
	}
	locationNear();
}



int findLocation(int*arr,int max,int m){
	for(int i=0;i<max;i++){
		if(arr[i]==m)
			return i;
	}
	return -1;
}

void sort(int*arr,int n){
	while(1){
		bool bSwitch=false;
		for(int i=0;i<n-1;i++){
			if(arr[i]>arr[i+1]){
				int a=arr[i];
				arr[i]=arr[i+1];
				arr[i+1]=a;
				bSwitch=true;
			}
		}
		if(!bSwitch)
			break;
	}
}

int deleteSame(int*arr,int n,int min,int max){
	int saveOld[MAX_AMOUNT];
	int loc=0;
	int last=0xffff;
	for(int i=0;i<n;i++){
		int aa=arr[i];
		if(aa<min||aa>max)
			continue;// ������
		if(aa!=last){
			saveOld[loc++]=aa;
		}
		last=aa;
	}
	memset(arr,0,sizeof(int)*MAX_AMOUNT);
	memcpy(arr,saveOld,sizeof(int)*loc);
	return loc;
}


void waitStopSearch();

int RadioWork::searchCurrentLoc(){
	return findLocation(��̨,amount,current);
}
#ifdef WINCE

int readLineData(HANDLE hHandle);


bool RadioWork::verifyData(HANDLE hHandle){
	char buffer[300];
	int toRead=0;
	//memset(��̨,0,sizeof(��̨));
	readLine(buffer,hHandle,300);// HEAD
	int currentR=readLineData(hHandle);
	if(currentR>max||currentR<min)
		return false;
	int nReadMount=readLineData(hHandle);
	for(int i=0;i<nReadMount;i++){
		int n��̨=(int)readLineData(hHandle);
		if(n��̨>max||n��̨<min)
			return false;
	}
	return true;
}

void RadioWork::load(HANDLE hHandle){
	char buffer[300];
	amount=0;
	memset(��̨,0,sizeof(��̨));
	readLine(buffer,hHandle,300);// HEAD
	int currentR=readLineData(hHandle);
	if(currentR!=0){
		current=currentR;		
	}
	amount=readLineData(hHandle);
	if(amount>sizeof(��̨)/sizeof(��̨[0])){
		amount=0;// error file
		�ղ�Amount=0;
		return;
	}
	for(int i=0;i<amount;i++){
		int pl=(int)readLineData(hHandle);
		if(pl<min||pl>max){
			pl=min;
		}
		��̨[i]=pl;
	}
	�ղ�Amount=readLineData(hHandle);
	if(�ղ�Amount>sizeof(�ղ�)/sizeof(�ղ�[0])){
		amount=0;// error file
		�ղ�Amount=0;
		return;
	}
	for(int i=0;i<�ղ�Amount;i++){
		int pl=(int)readLineData(hHandle);
		if(pl<min||pl>max){
			pl=min;
		}
		�ղ�[i]=pl;
	}
}

void RadioWork::setData(int totalPage,int currentPage,int *datas){
	for(int i=0;i<PAGE_AMOUNT;i++){
		int s=datas[i];
		��̨[i+currentPage*PAGE_AMOUNT]=s;
	}
	beginLoc=currentPage*PAGE_AMOUNT;
	amount=totalPage*PAGE_AMOUNT;
}

#endif
void RadioWork::save(FILE*fp){
	if(fp==INVALID_HANDLE_VALUE){
		return;
	}
	DWORD writed;
	//char buffer[1000];
	//ZString buffer="";
	//buffer=buffer+getRadioName()+"\r\n";			//sprintf_s(buffer,sizeof(buffer),"%s\r\n",getRadioName());
	ZString buffer;
	buffer.format("%s\r\n",getRadioName());
	writeStringToFile(fp,buffer);
	//WriteFile(hHandle,buffer,buffer.size(),&writed,0);
	//buffer="Current=";
	//buffer.catFormat("%d",current).cat("\r\n");		//sprintf_s(buffer,sizeof(buffer),"Current=%d\r\n",current);
	buffer.format("Current=%d\r\n",current);
	writeStringToFile(fp,buffer);
	//WriteFile(hHandle,buffer,buffer.size(),&writed,0);
	//buffer="Amount=";
	//buffer.catFormat("%d",amount).cat("\r\n");		//sprintf_s(buffer,sizeof(buffer),"Amount=%d\r\n",amount);
	buffer.format("Amount=%d\r\n",amount);
	//WriteFile(hHandle,buffer,buffer.size(),&writed,0);
	writeStringToFile(fp,buffer);
	for(int i=0;i<amount;i++){
		//buffer="S";
		//buffer.catFormat("%d",i).cat("=").catFormat("%d",��̨[i]).cat("\r\n");
		buffer.format("S%d=%d\r\n",i,��̨[i]);
		//sprintf_s(buffer,sizeof(buffer),"S%d=%d\r\n",i,��̨[i]);
		//WriteFile(hHandle,buffer,buffer.size(),&writed,0);
		writeStringToFile(fp,buffer);
	}
	buffer.format("SCAmount=%d\r\n",�ղ�Amount);
	//WriteFile(hHandle,buffer,buffer.size(),&writed,0);
	writeStringToFile(fp,buffer);
	for(int i=0;i<�ղ�Amount;i++){
		//buffer="S";
		//buffer.catFormat("%d",i).cat("=").catFormat("%d",��̨[i]).cat("\r\n");
		buffer.format("S%d=%d\r\n",i,�ղ�[i]);
		//sprintf_s(buffer,sizeof(buffer),"S%d=%d\r\n",i,��̨[i]);
		//WriteFile(hHandle,buffer,buffer.size(),&writed,0);
		writeStringToFile(fp,buffer);
	}
}



bool RadioWork::canMovePrevPage(){
	if(beginLoc-PAGE_AMOUNT<0)
		return false;
	return true;
}

bool RadioWork::canMoveNextPage(){
	if(beginLoc+PAGE_AMOUNT>=amount){
		return false;
	}
	return true;
}

bool RadioWork::prevPage(){
	int oldLoc=beginLoc;
	beginLoc-=PAGE_AMOUNT;
	if(beginLoc<0)
		beginLoc=0;
	return oldLoc==oldLoc;
}


int adjustFm(int pl);
int adjustAm(int pl);
void RadioWork::setCurrentFreq(int freq){
	if(freq!=0&&current!=freq){
		if(this->isFm()){
			current=adjustFm(freq);
		}else{
			current=adjustAm(freq);
		}

		markChanged();
	}

}

void RadioWork::powerOff(){
	//::openRadioAM
	void closeRadio();
	closeRadio();

}

bool RadioWork::nextPage(){
	int oldLoc=beginLoc;
	beginLoc+=PAGE_AMOUNT;
	if(beginLoc>=amount){
		beginLoc-=PAGE_AMOUNT;
	}
	return oldLoc==oldLoc;
}



void RadioWork::clear(){
	memset(��̨,0,sizeof(��̨));
	amount=0;
}
void RadioWork::beginSearch(bool fromBegin){
	if(fromBegin){
		beginSearchTunner=current=min;
	}else{
		beginSearchTunner=current;
	}
}
bool RadioWork::isSearchOver(){
	bool b=current==beginSearchTunner;
	return b;
}


void RadioWork::turn(int dSearchForWord){
	current+=dSearchForWord*step;
	if(current>max){
		current=min;		
	}
	if(current<min){
		current=max;	
	}
}

void RadioWork::toFistLoc(){
	if(amount!=0){
		beginLoc=0;
		current=��̨[0];		
	}else{
		current=min;	
	}
}
void radioPlayCurrent();
bool RadioWork::turnLocDir(int no){
	if(no<0||no>=amount)
		return false;
	current=��̨[no];	
	//turnToCurrentProxy();
	//radioPlayCurrent();
	makeChanged��̨();
	locationNear();
	return true;
}

void RadioWork::turnLoc(int no){
	int loc=beginLoc+no;
	if(loc>=amount)
		return;
	current=��̨[loc];	
	turnToCurrentProxy();
	makeChanged��̨();
	//locationNear();
}

bool RadioWork::isStoreIsCurrent(int no){
	int	loc=no;
	if(loc>=amount||loc<0)
		return false;
	return current==��̨[loc];
}
extern unsigned char currentPreset;
bool RadioWork::isCurrentSelectNo(int no){
	/*		int	loc=beginLoc+no;
	if(loc>=amount||loc<0)
	return false;
	return current==��̨[loc];*/
	if(currentPreset==0)
		currentPreset=PAGE_AMOUNT+1;
	return no==(currentPreset-1);
}

static RECT rSlideBoxaaa={92,268,705,355};
RECT getRSlideBox(){
	//if(mt.ui_type==1){
	//	RECT r=screen[SCRN_������2].getRect("��������");
	//	return r;
	//}
	return rSlideBoxaaa;
}

RECT rSlideBoxWW={92,149,695,203}; //changed by luffy  11-26

//F:\ZHW-WINCE-C\ARM11\WORK-DIR\img\������

int RadioWork::get����LOC(){
	return 0;
}

void RadioWork::turnToInbox(int x,RECT r){
	int value=(x-r.left)*(max-min)/(r.right-r.left)+min;
	if(value<min)
		value=min;
	if(value>max)
		value=max;
	current=(value+step/2)/step*step;	
	turnToCurrentProxy();
	makeChanged��̨();
}

void 	RadioWork::markChanged(){
	isChanged=true;
	nChangedTime=GetTickCount();
}

void RadioWork::addCurrent(){
	if(amount<MAX_AMOUNT){
		��̨[amount++]=current;
	}
	sort(��̨,amount);
	amount=deleteSame(��̨,amount,min,max);
	// LOCATION 
	int loc=findLocation(��̨,amount,current);
	locationNear();
	//beginLoc=loc/8*8;
	makeChanged��̨();
}

int RadioWork::getCurrentLoc(){
#ifndef WINCE
	//if(1)
	//	return 0;
#endif
	for(int i=0;i<amount;i++){
		if(current<=��̨[i]){
			//beginLoc=i/8*8;
			//int n=i-PAGE_AMOUNT/2;
			//if(n<0){
			//	n=0;
			//}
			//..beginLoc=n;
			return i;
		}
	}
	return 0;
}

void RadioWork::setBeginLoc(int no){
	beginLoc=no;
}
void RadioWork::locationNear(){
	for(int i=0;i<amount;i++){
		if(current<=��̨[i]){
			beginLoc=i/PAGE_AMOUNT*PAGE_AMOUNT;
			break;// FOUND A LOCATION
		}
	}
	//RETAILMSG_DC(1,(L"beginLoc== %d \r\n",beginLoc));
}



ZString RadioWork::getShowString(int no){
	ZString ts="";
	int	loc=beginLoc+no;
	if(loc<amount&&loc>=0){
		return getShowStringTrue(loc);
	}
	return ts;
};

void RadioWork::storeCurrentPlAt(int no){
	ZString ts="";
	int	loc=beginLoc+no;
	if(loc<amount&&loc>=0){
		��̨[loc]=current;
	}
};


void RadioWork::deleteCurrent(){
	for(int i=0;i<amount;i++){
		if(��̨[i]==current){
			int nCopySize=amount-i-1;
			if(nCopySize>0){
				memcpy(��̨+i,��̨+i+1,sizeof(int)*(nCopySize));
			}
			amount--;
			if(nCopySize>0){
				current=��̨[i];				
			}else{
				if(i==0){
					//current=tunner;
				}
				else
					current=��̨[i-1];;				
			}
		}
	}
	locationNear();
	makeChanged��̨();
};
/*
void RadioWork::save(){
HANDLE handle=createWriteOutPropFile(getPropFileName());
if(handle==INVALID_HANDLE_VALUE){
initData();
return;
}
DWORD dw;
ZString zs="";
zs.format("amount=%d\r\n",amount);
WriteFile(handle,zs,zs.length(),&dw,0);
for(int i=0;i<amount;i++){
zs.format("%d\r\n",��̨[i]);
}
zs.format("szAmount=%d\r\n",amount);
WriteFile(handle,zs,zs.length(),&dw,0);
for(int i=0;i<amount;i++){
zs.format("%d\r\n",��̨[i]);
}
CloseHandle(handle);

}
void RadioWork::load(){
HANDLE handle=openReadinPropFile(getPropFileName());
if(handle==INVALID_HANDLE_VALUE){	
initData();
return;
}
char buffer[256];
char *pp=readLine(buffer,handle,255);
sscanf(buffer,"amount=%d",&this->amount);
for(int i=0;i<amount;i++){
pp=readLine(buffer,handle,255);
sscanf(buffer,"%d",&��̨[i]);
}
sscanf(buffer,"szAmount=%d",&this->�ղ�Amount);
for(int i=0;i<amount;i++){
pp=readLine(buffer,handle,255);
sscanf(buffer,"%d",&�ղ�[i]);
}
CloseHandle(handle);
}
*/
void RadioWork::load(FILE*fp){
	return;
}
void RadioWork::foundPl(unsigned short pl){
	if(amount<sizeof(��̨)/sizeof(��̨[0])){
		��̨[amount++]=pl;
	}
	markChanged();
}

void RadioWork::add�ղ�(unsigned short pl){
	for(int i=0;i<�ղ�Amount;i++){
		if(�ղ�[i]==pl){
			return;
		}
	}
	if(�ղ�Amount<sizeof(�ղ�)/sizeof(�ղ�[0])){
		�ղ�[�ղ�Amount++]=pl;
	}
	markChanged();
	return;
}

void RadioWork::delete�ղ�(unsigned int no){
	if(no<0)
		return;
	if(no>=�ղ�Amount){
		return;
	}
	if(�ղ�Amount==0)
		return;
	for(int i=no;i<�ղ�Amount-1;i++){
		�ղ�[i]=�ղ�[i+1];
	}
	�ղ�Amount--;
}

int RadioWork::find�ղ�(unsigned short pl){
	for(int i=0;i<�ղ�Amount;i++){
		if(�ղ�[i]==pl){
			return i;
		}
	}
	return -1;
}

bool RadioWork::isNeedSaveChange(bool force){
	bool beSaveThis=false;
	if(!isChanged)
		return false;
	if(force){
		beSaveThis=true;
	}else{
		beSaveThis=(GetTickCount()-nChangedTime>2000)? true:false;
	}
	return beSaveThis;
}


void RadioWork::beginSearchRadio(int dir,bool once){
//	willData.setSearchMute(true);
	if(once){
		beginSearch(false);
	}else{
		beginSearch(true);
		clear();
	}
	SearchContext sc;
	sc.max=max;
	sc.min=min;
	sc.isOnlySearchOnce=once;
	sc.isFm=isFm();
	if(once){
		sc.beginSearch=current;//����
	}else{
		sc.beginSearch=min;//��̨
	}
	sc.step=step*dir;
	startFMAMSeek(sc);
}


unsigned short plList[5][6][2]={
{{8750,0},{9010,0},{9810,0},{10610,0},{10800,0},{8750,0},},
{{8750,0},{9010,0},{9810,0},{10610,0},{10800,0},{8750,0},},
{{8750,0},{9010,0},{9810,0},{10610,0},{10800,0},{8750,0},},
{{531,0},{603,0},{999,0},{1404,0},{1629,0},{531,0},},
{{531,0},{603,0},{999,0},{1404,0},{1629,0},{531,0},},
};



void FMRadioWork::init(){
	memset(��̨,0,sizeof(��̨));
	amount=18;
	step=10;
	current=8750;	
	min= 8750;
	max=10800;
	beginLoc=0;
	for(int i=0;i<3;i++){
		for(int j=0;j<6;j++){
			��̨[i*6+j]=plList[i][j][0];
		}
	}
	//load();
}

int readLineData(HANDLE hHandle);

RadioWork *getFMWorker();
RadioWork *getAMWorker();
ZString RADIO_SAVE_FILE("/Residentflash3/system_init/RADIO_LIST.save");
void radioLoad(){
	/*
	try{
		FILE*fp=openReadinPropFile(RADIO_SAVE_FILE);
		if(fp==NULL){	
			//initData();
			getFMWorker()->initData();
			getAMWorker()->initData();
			radioWork=getFMWorker();
			return;
		}
		int isFm=readLineData(fp);
		if(isFm){
			radioWork=getFMWorker();
		}else{
			radioWork=getAMWorker();
		}
		getFMWorker()->load(fp);
		getAMWorker()->load(fp);
		getFMWorker()->adjustAllPl();
		getAMWorker()->adjustAllPl();
		CloseHandle(handle);
	}
	catch(...)
	{
		
		RETAILMSG(1,(L" sendStartUpCmd MEE A EXCEPTION \r\n"));
		getFMWorker()->initData();
		getAMWorker()->initData();
		radioWork=getFMWorker();
		// �����ļ����ƻ���
	}
	*/
}

static void radioSave0(){
	/*
	FILE*fp=createWriteOutPropFile(RADIO_SAVE_FILE);
	if(fp==NULL){	
		return;
	}
	ZString zs;
	zs.format("IS_FM=%d\r\n",radioWork==getFMWorker()? 1:0);
	DWORD d;
	writeStringToFile(fp,zs);
	//WriteFile(handle,zs.getData(),zs.length(),&d,0);
	getFMWorker()->save(fp);
	getAMWorker()->save(fp);
	//CloseHandle(handle);
	fclose(fp);
	*/
}

void radioSave(){
	try{
		radioSave0();
	}
	catch(...)
	{
		//		RETAILMSG(1,(L" sendStartUpCmd MEE A EXCEPTION \r\n"));
	}
}

void saveAllRadionChanged(bool beSaveForce){
	// �������������̨ ����̨
	// �������SCANģʽ
	// ����ģʽ�Ǵ���ִ�е�
	if(radionContrl.isInSearch()){
		return;
	}
	if(radionContrl.isInScan()){
		return;
	}
	bool toSaveData=getFMWorker()->isNeedSaveChange(beSaveForce)
		||
		getAMWorker()->isNeedSaveChange(beSaveForce);
	if(toSaveData){
		radioSave();
		getFMWorker()->isChanged=false;
		getAMWorker()->isChanged=false;
	}
}

ZString FMRadioWork::getCurrentShowMain()	{
	ZString ts;
	ts.format("%3.01f",getCurrentFreq()/100.0);
	return ts;
}


ZString FMRadioWork::getShowStringTrue(int loc,bool waitBlank){
	ZString ts;
	if(loc>=0&&loc<amount){
		if(waitBlank){
			//ts.format("%6.1f",��̨[loc]/100.0);
			ts.format("%3.1f",��̨[loc]/100.0);
		}
		else{
			ts.format("%3.1f",��̨[loc]/100.0);
		}
	}
	return ts;
};
ZString FMRadioWork::getRadioName(){
	ZString ts("FM");
	return ts;
}
bool FMRadioWork::isFm(){
	return true;
}

void	FMRadioWork::initData(){
	amount=6;
	��̨[0]=8750;
	��̨[1]=9010;
	��̨[2]=9810;
	��̨[3]=10610;
	��̨[4]=10800;
	��̨[5]=8750;
	�ղ�Amount=12;
	�ղ�[0]=8750;
	�ղ�[1]=9010;
	�ղ�[2]=9810;
	�ղ�[3]=10610;
	�ղ�[4]=10800;
	�ղ�[5]=8750;
	�ղ�[6]=8750;
	�ղ�[7]=9010;
	�ղ�[8]=9810;
	�ղ�[9]=10610;
	�ղ�[10]=10800;
	�ղ�[11]=8750;

}

#define FM_MIN	8750
#define FM_MAX	10800
#define AM_MIN  522
#define AM_MAX  1720
#define FM_STEP 10
#define AM_STEP 9

int adjustFm(int pl){
	pl=pl/FM_STEP*FM_STEP;
	if(pl<FM_MIN){
		pl=FM_MIN;
	}
	if(pl>FM_MAX){
		pl=FM_MAX;
	}
	return pl;
}

int adjustAm(int pl){
	pl=pl/AM_STEP*AM_STEP;
	if(pl<AM_MIN){
		pl=AM_MIN;
	}
	if(pl>AM_MAX){
		pl=AM_MAX;
	}
	return pl;
}


void FMRadioWork::adjustAllPl(){
	current=adjustFm(current);
	for(int i=0;i<amount;i++){
		��̨[i]=adjustFm(��̨[i]);
	}
	for(int i=0;i<�ղ�Amount;i++){
		�ղ�[i]=adjustFm(�ղ�[i]);
	}
}
void AMRadioWork::adjustAllPl(){
	current=adjustAm(current);
	for(int i=0;i<amount;i++){
		��̨[i]=adjustAm(��̨[i]);
	}
	for(int i=0;i<�ղ�Amount;i++){
		�ղ�[i]=adjustAm(�ղ�[i]);
	}
}
/// {{8750,0},{9010,0},{9810,0},{10610,0},{10800,0},{8750,0},},

#define AM_MIN  522
#define AM_MAX  1720

void AMRadioWork::init(){
	memset(��̨,0,sizeof(��̨));
	amount=12;
	��̨[0]=531;
	��̨[1]=603;
	��̨[2]=999;
	��̨[3]=1404;
	��̨[4]=1629;
	��̨[5]=531;
	��̨[6]=531;
	��̨[7]=603;
	��̨[8]=999;
	��̨[9]=1404;
	��̨[10]=1629;
	��̨[11]=531;

	step=9;
	min=AM_MIN;
	max=AM_MAX;
	current=min;
	beginLoc=0;
	//load();
}


void	AMRadioWork::initData(){
	amount=6;
	��̨[0]=531;
	��̨[1]=603;
	��̨[2]=999;
	��̨[3]=1404;
	��̨[4]=1629;
	��̨[5]=531;
	�ղ�Amount=10;
	�ղ�[0]=531;
	�ղ�[1]=603;
	�ղ�[2]=999;
	�ղ�[3]=1404;
	�ղ�[4]=1629;
	�ղ�[5]=531;
	�ղ�[6]=531;
	�ղ�[7]=603;
	�ղ�[8]=999;
	�ղ�[9]=1404;
}

ZString AMRadioWork::getCurrentShowMain()	{
	//sprintf_s(buffer,100,"%5d kHz",current);
	ZString zs;
	zs.format("%3d",getCurrentFreq());
	return zs;
}
ZString AMRadioWork::getShowStringTrue(int loc,bool waitBlank){
	ZString zs="";
	if(loc>=0&&loc<amount){
		if(waitBlank)
			//zs.format("%5d",��̨[loc]);
			zs.format("%3d",��̨[loc]);
		else
			//zs.format("%3d",��̨[loc]);
			zs.format("%3d",��̨[loc]);
	}
	return zs;
};

ZString AMRadioWork::getRadioName(){
	return ZString("AM");
}
bool AMRadioWork::isFm(){
	return false;
}



#ifdef WINCE

bool read6621(unsigned char *readOutData);

void postCmd(unsigned char *cmdp,int len)
{

}

bool readSTM8(){
	return true;
}

void callSTM8(){
	readSTM8();
	static unsigned char  tempWork[5]={0x02,0x01,02,3,4};
	postCmd(tempWork,4);
}

#endif