#ifndef MAIN_EventV1_HEAD
#define MAIN_EventV1_HEAD
#include "pub.h"
#include "BaseStateEventItem2.h"

#define SCRN2_MAIN "SCRN2_MAIN"

 //---------- NEXT IS CMD DEFIND -----


 //---------- NEXT IS FUN DEFIN-----

class MAIN_EventV1 : public BaseStateEventItemV2 {
public:
	PNG_STRUCT pngs[64];
	virtual int getPngLength(){return 64;};
	TXT_STRUCT	texts[0];
	virtual int getTextLength(){return 0;};
	MAIN_EventV1();
	virtual void _F_INIT_FUN(MSG_ZHW&msg);
	virtual void _F_UPDATE_TIMMER(MSG_ZHW&msg);
	virtual void dispatch(MSG_ZHW&msg);
	virtual void drawDynimicQt(QPainter *qp);
	virtual int getMsgLen(){return 0;};
	virtual char* getTitleName();
	void initPng();
	void initTxt();
	virtual  void initScreen();
	virtual char *getScreenName(){ return "MAIN";};
	void  _F_buttona(MSG_ZHW&msg);
	void  _F_buttonb(MSG_ZHW&msg);
	void  _F_buttonc(MSG_ZHW&msg);
	void  _F_NEXT_PAGE(MSG_ZHW&msg);
	void  _F_CLOSE_SCREEN(MSG_ZHW&msg);
	void  _F_CAR_LEFT(MSG_ZHW&msg);
	void  _F_BT(MSG_ZHW&msg);
	void  _F_RADIO(MSG_ZHW&msg);
	void  _F_MUSIC(MSG_ZHW&msg);
	void  _F_APP(MSG_ZHW&msg);
#include "..\MAIN_EventV1_extend.h"

};
#endif


