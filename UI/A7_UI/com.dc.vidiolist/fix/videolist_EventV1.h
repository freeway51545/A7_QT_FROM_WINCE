#ifndef videolist_EventV1_HEAD
#define videolist_EventV1_HEAD
#include "pub.h"
#include "BaseStateEventItem2.h"

#define SCRN2_videolist "SCRN2_videolist"

 //---------- NEXT IS CMD DEFIND -----


 //---------- NEXT IS FUN DEFIN-----

class videolist_EventV1 : public BaseStateEventItemV2 {
public:
	PNG_STRUCT pngs[8];
	virtual int getPngLength(){return 8;};
	TXT_STRUCT	texts[1];
	virtual int getTextLength(){return 1;};
	videolist_EventV1();
	virtual void _F_INIT_FUN(MSG_ZHW&msg);
	virtual void _F_UPDATE_TIMMER(MSG_ZHW&msg);
	virtual void dispatch(MSG_ZHW&msg);
	virtual void drawDynimicQt(QPainter *qp);
	virtual int getMsgLen(){return 0;};
	virtual char* getTitleName();
	void initPng();
	void initTxt();
	virtual  void initScreen();
	virtual char *getScreenName(){ return "videolist";};
	void  _F_HOME(MSG_ZHW&msg);
	void  _F_BACK(MSG_ZHW&msg);
#include "..\videolist_EventV1_extend.h"

};
#endif


