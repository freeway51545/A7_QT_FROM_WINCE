#ifndef EQ_EventV1_HEAD
#define EQ_EventV1_HEAD
#include "pub.h"
#include "BaseStateEventItem2.h"

#define SCRN2_EQ "SCRN2_EQ"

 //---------- NEXT IS CMD DEFIND -----


 //---------- NEXT IS FUN DEFIN-----

class EQ_EventV1 : public BaseStateEventItemV2 {
public:
	PNG_STRUCT pngs[51];
	virtual int getPngLength(){return 51;};
	TXT_STRUCT	texts[4];
	virtual int getTextLength(){return 4;};
	EQ_EventV1();
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
	virtual char *getScreenName(){ return "EQ";};
	void  _F_banlance(MSG_ZHW&msg);
	void  _F_DEFAULT(MSG_ZHW&msg);
	void  _F_VOLUME(MSG_ZHW&msg);
	void  _F_LEFT(MSG_ZHW&msg);
	void  _F_LEFT_L(MSG_ZHW&msg);
	void  _F_LEFT_M(MSG_ZHW&msg);
	void  _F_LEFT_H(MSG_ZHW&msg);
	void  _F_RIGHT(MSG_ZHW&msg);
	void  _F_RIGHT_L(MSG_ZHW&msg);
	void  _F_RIGHT_M(MSG_ZHW&msg);
	void  _F_RIGHT_H(MSG_ZHW&msg);
	void  _F_LIST(MSG_ZHW&msg);
	void  _F_MAIN(MSG_ZHW&msg);
	void  _F_SRC(MSG_ZHW&msg);
	void  _F_CMD(MSG_ZHW&msg);
	void  _F_SYS_H(MSG_ZHW&msg);
	void  _F_USER_H(MSG_ZHW&msg);
#include "..\EQ_EventV1_extend.h"

};
#endif


