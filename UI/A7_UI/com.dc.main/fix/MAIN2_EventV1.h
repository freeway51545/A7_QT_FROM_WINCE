#ifndef MAIN2_EventV1_HEAD
#define MAIN2_EventV1_HEAD
#include "pub.h"
#include "BaseStateEventItem2.h"

#define SCRN2_MAIN2 "SCRN2_MAIN2"

 //---------- NEXT IS CMD DEFIND -----


 //---------- NEXT IS FUN DEFIN-----

class MAIN2_EventV1 : public BaseStateEventItemV2 {
public:
	PNG_STRUCT pngs[34];
	virtual int getPngLength(){return 34;};
	TXT_STRUCT	texts[0];
	virtual int getTextLength(){return 0;};
	MAIN2_EventV1();
	virtual void _F_INIT_FUN(MSG_ZHW&msg);
	virtual void _F_UPDATE_TIMMER(MSG_ZHW&msg);
	virtual void dispatch(MSG_ZHW&msg);
	virtual void drawDynimicQt(QPainter *qp);
	virtual int getMsgLen(){return 0;};
	virtual char* getTitleName();
	void initPng();
	void initTxt();
	virtual  void initScreen();
	virtual char *getScreenName(){ return "MAIN2";};
	void  _F_PREV_PAGE(MSG_ZHW&msg);
	void  _F_VEDIO(MSG_ZHW&msg);
	void  _F_PIC(MSG_ZHW&msg);
	void  _F_VICE(MSG_ZHW&msg);
	void  _F_SET(MSG_ZHW&msg);
	void  _F_VICH(MSG_ZHW&msg);
#include "..\MAIN2_EventV1_extend.h"

};
#endif


