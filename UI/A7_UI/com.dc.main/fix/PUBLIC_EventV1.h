#ifndef PUBLIC_EventV1_HEAD
#define PUBLIC_EventV1_HEAD
#include "pub.h"
#include "BaseStateEventItem2.h"

#define SCRN2_PUBLIC "SCRN2_PUBLIC"

 //---------- NEXT IS CMD DEFIND -----


 //---------- NEXT IS FUN DEFIN-----

class PUBLIC_EventV1 : public BaseStateEventItemV2 {
public:
	PNG_STRUCT pngs[12];
	virtual int getPngLength(){return 12;};
	TXT_STRUCT	texts[0];
	virtual int getTextLength(){return 0;};
	PUBLIC_EventV1();
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
	virtual char *getScreenName(){ return "PUBLIC";};
#include "..\PUBLIC_EventV1_extend.h"

};
#endif


