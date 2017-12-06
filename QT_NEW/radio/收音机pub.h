#ifndef ������PUB_H
#define ������PUB_H

#include "zstring.h"
#include "tzstring.h"

void seekTOFM(int tunner);

void seekTOAM(int tunner);


void makeChanged��̨();

#define FM_STATE	0	
#define AM_STATE	1

#define MAX_AMOUNT	1000

class RadioWork;

typedef struct _SearchContext{
	int min;
	int max;
	int step;
	int beginSearch;
	bool isOnlySearchOnce;
	bool isFm;
}SearchContext;


class RadioWork{
//protected:
public:
	int current;
public:
	int ��̨[MAX_AMOUNT];
	int �ղ�[MAX_AMOUNT];
	int max;
	int min;
	int step;
	int amount;
	int �ղ�Amount;
	int beginLoc;
	int beginSearchTunner;
	bool radioOpend;
	int nScanNo;
	bool isChanged;
	DWORD nChangedTime;
public:
	int getCurrentFreq(){
		return current;
	}
	RadioWork(){
		radioOpend=false;
	}
	void markChanged();
	void clear();
	void addCurrent();
	//void del(int tunner);
	void deleteCurrent();
	void toFistLoc();
	int loc(int tunner);
	virtual ZString getShowString(int no);
	void storeCurrentPlAt(int no);
	virtual ZString getShowStringTrue(int actNo,bool waitBlank=true)=0;
	bool isStoreIsCurrent(int no);
	virtual void turnToCurrent()=0;
	void turnToCurrentProxy();
	virtual ZString getCurrentShowMain()=0;
	virtual bool is��Ч��̨()=0;
	virtual bool isTurnOk()=0;
	void beginSearch(bool fromBegin=false);
	void locationNear();
	void setBeginLoc(int loc);
	int getCurrentLoc();
	bool isSearchOver();
	void turn(int dSearchForWord);
	void turnLoc(int no);
	bool turnLocDir(int no);
	bool isCurrentSelectNo(int no);
	int get����LOC();
	void turnToInbox(int x,RECT r);
	int getAmount(){
		return amount;
	}
	void locAt(int loc);
	void save(FILE*fp);
	virtual ZString getRadioName()=0;
	virtual void openRadioIfOff()=0;
	void load(FILE*fp);
	void RadioWork::setData(int totalPage,int currentPage,int *datas);
	bool verifyData(FILE*fp);
	bool prevPage();
	bool nextPage();
	bool canMoveNextPage();
	bool canMovePrevPage();
	void setCurrentFreq(int freq);
	virtual void stopSearch(){};
	void powerOff();
	int searchCurrentLoc();
	void beginSearchRadio(int dir,bool once);
	virtual bool isFm()=0;
	virtual void startFMAMSeek(SearchContext&sc){
	}
	virtual void init()=0;
	virtual int getStoreFlag(){return 0;}
	virtual ZString getShowSSI(){
		ZString  ts;
		return ts;
	}
	virtual TCHAR* getPropFileName()=0;
	virtual void initData()=0;
	void foundPl(unsigned short pl);
	void add�ղ�(unsigned short pl);
	int find�ղ�(unsigned short pl);
	bool isNeedSaveChange(bool force);
	void delete�ղ�(unsigned int no);
	virtual void adjustAllPl()=0;
		//sprintf(buffer,"RSSI:%d SNR:%d \r\n",R_CUR_RSS,ASNR);
};

//extern RadioWork *radioWork;




class FMRadioWork:public RadioWork{
public:
	virtual void init();
	virtual ZString getCurrentShowMain()	;
	virtual ZString getShowStringTrue(int loc,bool waitBlank);
	virtual	ZString getRadioName();
	virtual bool isFm();
	virtual TCHAR* getPropFileName(){
		return L"/Residentflash3/system_init/FM_LIST.save";
	}
	virtual void initData();
	virtual void adjustAllPl();
	
};

class AMRadioWork:public RadioWork{
public:
	virtual void init();
	virtual ZString getCurrentShowMain()	;
	virtual ZString getShowStringTrue(int loc,bool waitBlank);
	virtual	ZString getRadioName();
	virtual bool isFm();
	virtual TCHAR* getPropFileName(){
		return L"/Residentflash3/system_init/AM_LIST.save";
	}
	virtual void initData();
	virtual void adjustAllPl();
};


#define PAGE_AMOUNT	6
/*  �Ƿ��������*/
bool ����������������();
/*  �򿪹ر�������*/
void exchange����������();
/* ��ǰ����������������*/
extern RadioWork *radioWork;


#define DEBUG_SYJ	0

extern bool beԶ��;

#endif