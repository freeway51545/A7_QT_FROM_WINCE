#ifndef RADIOLIST_EventV1_HEAD
#define RADIOLIST_EventV1_HEAD
#include "pub.h"
#include "BaseStateEventItem2.h"

#define SCRN2_RADIOLIST "SCRN2_RADIOLIST"

 //---------- NEXT IS CMD DEFIND -----


 //---------- NEXT IS FUN DEFIN-----

class RADIOLIST_EventV1 : public BaseStateEventItemV2 {
public:
	PNG_STRUCT pngs[43];
	virtual int getPngLength(){return 43;};
	TXT_STRUCT	texts[5];
	virtual int getTextLength(){return 5;};
	RADIOLIST_EventV1();
	virtual void _F_INIT_FUN(MSG_ZHW&msg);
	virtual void _F_UPDATE_TIMMER(MSG_ZHW&msg);
	virtual void dispatch(MSG_ZHW&msg);
	virtual void drawDynimicQt(QPainter *qp);
	virtual int getMsgLen(){return 0;};
	virtual NAME_TO_MSG_ID * getMsgList(){return NULL;};
	virtual char* getTitleName();
	void initPng();
	void initTxt();
	virtual  void initScreen();
	virtual char *getScreenName(){ return "RADIOLIST";};
	void  _F_FM(MSG_ZHW&msg);
	void  _F_LIST(MSG_ZHW&msg);
	void  _F_AM(MSG_ZHW&msg);
	void  _F_up(MSG_ZHW&msg);
	void  _F_down(MSG_ZHW&msg);
	void  _F_UPDATE(MSG_ZHW&msg);
	void  _F_RADIO(MSG_ZHW&msg);
	void  _F_EQ(MSG_ZHW&msg);
#include "..\RADIOLIST_EventV1_extend.h"

};
#endif


