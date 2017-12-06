#ifndef RADIO_COMFIRE_EventV1_HEAD
#define RADIO_COMFIRE_EventV1_HEAD
#include "pub.h"
#include "BaseStateEventItem2.h"

#define SCRN2_RADIO_COMFIRE "SCRN2_RADIO_COMFIRE"

 //---------- NEXT IS CMD DEFIND -----


 //---------- NEXT IS FUN DEFIN-----

class RADIO_COMFIRE_EventV1 : public BaseStateEventItemV2 {
public:
	PNG_STRUCT pngs[3];
	virtual int getPngLength(){return 3;};
	TXT_STRUCT	texts[1];
	virtual int getTextLength(){return 1;};
	RADIO_COMFIRE_EventV1();
	virtual void _F_INIT_FUN(MSG_ZHW&msg);
	virtual void _F_UPDATE_TIMMER(MSG_ZHW&msg);
	virtual void dispatch(MSG_ZHW&msg);
	virtual void drawDynimicQt(QPainter *qp);
	 virtual int getDlgMainViewId();
	 virtual bool isDlg();
	 virtual int getActiveViewId();
	 virtual int getBackId();
	virtual int getMsgLen(){return 0;};
	virtual NAME_TO_MSG_ID * getMsgList(){return NULL;};
	virtual char* getTitleName();
	void initPng();
	void initTxt();
	virtual  void initScreen();
	virtual char *getScreenName(){ return "RADIO_COMFIRE";};
	void  _F_AGREE(MSG_ZHW&msg);
	void  _F_REFUSE(MSG_ZHW&msg);
#include "..\RADIO_COMFIRE_EventV1_extend.h"

};
#endif


