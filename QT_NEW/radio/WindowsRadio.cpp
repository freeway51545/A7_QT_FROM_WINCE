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


class WINDOW_FMRadioWork:public FMRadioWork{
public:
	virtual bool is��Ч��̨(){
		return true;
	}
	virtual void openRadioIfOff(){
	}
	virtual bool isTurnOk(){
		return true;
	}
	virtual void turnToCurrent(){
	}
	virtual void startFMAMSeek(SearchContext&sc){
	}
	virtual int getStoreFlag(){
		return 1;
	}
	virtual void getShowSSI(char *buffer){
		sprintf(buffer,"LEVEL:100 ����:1 \r\n");
	}
	virtual	void stopSearch(){
	}

};



class WINDOW_AMRadioWork:public AMRadioWork{
public:
	virtual void turnToCurrent(){
	}
	virtual bool is��Ч��̨(){
		return true;
	}
	virtual void openRadioIfOff(){
	}
	virtual bool isTurnOk(){
		return true;
	}
	virtual void startFMAMSeek(SearchContext&sc){
		
	}
	virtual void getShowSSI(char *buffer){
		sprintf(buffer,"LEVEL:100 ����:1 \r\n");
	}
	virtual	void stopSearch(){
	}

};

FMRadioWork *getWindowsFMRadio(){
static WINDOW_FMRadioWork fmRadio;
	return &fmRadio;
}

AMRadioWork *getWindowsAMRadio(){
static WINDOW_AMRadioWork amRadio;
	return &amRadio;
}

