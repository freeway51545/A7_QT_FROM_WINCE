#ifndef BANLANCE_EventV1_HEAD
#define BANLANCE_EventV1_HEAD
#include "pub.h"
#include "BaseStateEventItem2.h"

#define SCRN2_BANLANCE "SCRN2_BANLANCE"

 //---------- NEXT IS CMD DEFIND -----


 //---------- NEXT IS FUN DEFIN-----

class BANLANCE_EventV1 : public BaseStateEventItemV2 {
public:
	PNG_STRUCT pngs[29];
	virtual int getPngLength(){return 29;};
	TXT_STRUCT	texts[5];
	virtual int getTextLength(){return 5;};
	BANLANCE_EventV1();
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
	virtual char *getScreenName(){ return "BANLANCE";};
	void  _F_eq(MSG_ZHW&msg);
	void  _F_VOLUME(MSG_ZHW&msg);
	void  _F_DEFAULT(MSG_ZHW&msg);
	void  _F_LEFT(MSG_ZHW&msg);
	void  _F_RIGHT(MSG_ZHW&msg);
	void  _F_UP(MSG_ZHW&msg);
	void  _F_DOWN(MSG_ZHW&msg);
	void  _F_LIST(MSG_ZHW&msg);
	void  _F_MAIN(MSG_ZHW&msg);
	void  _F_SRC(MSG_ZHW&msg);
	void  _F_CMD(MSG_ZHW&msg);
	void  _F_SYS_H(MSG_ZHW&msg);
	void  _F_USER_H(MSG_ZHW&msg);
#include "..\BANLANCE_EventV1_extend.h"

};
#endif


