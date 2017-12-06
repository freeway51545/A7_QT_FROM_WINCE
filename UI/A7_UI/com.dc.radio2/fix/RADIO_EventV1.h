#ifndef RADIO_EventV1_HEAD
#define RADIO_EventV1_HEAD
#include "pub.h"
#include "BaseStateEventItem2.h"

#define SCRN2_RADIO "SCRN2_RADIO"

 //---------- NEXT IS CMD DEFIND -----


 //---------- NEXT IS FUN DEFIN-----

class RADIO_EventV1 : public BaseStateEventItemV2 {
public:
	PNG_STRUCT pngs[50];
	virtual int getPngLength(){return 50;};
	TXT_STRUCT	texts[1];
	virtual int getTextLength(){return 1;};
	RADIO_EventV1();
	virtual void _F_INIT_FUN(MSG_ZHW&msg);
	virtual void _F_UPDATE_TIMMER(MSG_ZHW&msg);
	virtual void dispatch(MSG_ZHW&msg);
	virtual void drawDynimicQt(QPainter *qp);
	virtual int getMsgLen(){return 0;};
	virtual char* getTitleName();
	void initPng();
	void initTxt();
	virtual  void initScreen();
	virtual char *getScreenName(){ return "RADIO";};
	void  _F_EQ(MSG_ZHW&msg);
	void  _F_BAND(MSG_ZHW&msg);
	void  _F_PREV(MSG_ZHW&msg);
	void  _F_STOP(MSG_ZHW&msg);
	void  _F_NEXT(MSG_ZHW&msg);
	void  _F_SAVE(MSG_ZHW&msg);
	void  _F_SEARCH(MSG_ZHW&msg);
	void  _F_p(MSG_ZHW&msg,char* no);
	void  _F_HOME(MSG_ZHW&msg);
	void  _F_BACK(MSG_ZHW&msg);
	void  _F_PLUS_ONE(MSG_ZHW&msg);
	void  _F_SUB_ONE(MSG_ZHW&msg);
#include "..\RADIO_EventV1_extend.h"

};
#endif


