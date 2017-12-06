#ifndef pubIcon_EventV1_HEAD
#define pubIcon_EventV1_HEAD
#include "pub.h"
#include "BaseStateEventItem2.h"

#define SCRN2_pubIcon "SCRN2_pubIcon"

 //---------- NEXT IS CMD DEFIND -----


 //---------- NEXT IS FUN DEFIN-----

class pubIcon_EventV1 : public BaseStateEventItemV2 {
public:
	PNG_STRUCT pngs[12];
	virtual int getPngLength(){return 12;};
	TXT_STRUCT	texts[0];
	virtual int getTextLength(){return 0;};
	pubIcon_EventV1();
	virtual void _F_INIT_FUN(MSG_ZHW&msg);
	virtual void _F_UPDATE_TIMMER(MSG_ZHW&msg);
	virtual void dispatch(MSG_ZHW&msg);
	virtual void drawDynimicQt(QPainter *qp);
	virtual int getMsgLen(){return 0;};
	virtual char* getTitleName();
	void initPng();
	void initTxt();
	virtual  void initScreen();
	virtual char *getScreenName(){ return "pubIcon";};
#include "..\pubIcon_EventV1_extend.h"

};
#endif


