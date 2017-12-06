#include "pubIcon_EventV1.h"
	//public PNG_STRUCT pngStruct0[]=new PNG_STRUCT[12];
	//public TXT_STRUCT txtStruct[]=new TXT_STRUCT[0];
void pubIcon_EventV1::initPng(){
	pngs[0].setValues("timeLocation","qtmain\\button.png",438,10,7,-1,0);
	pngs[1].setValues("T9","shi2jian1\\_0000_9.png",361,12,7,-1,0);
	pngs[2].setValues("T8","shi2jian1\\_0001_8.png",361,12,7,-1,0);
	pngs[3].setValues("T7","shi2jian1\\_0002_7.png",361,12,7,-1,0);
	pngs[4].setValues("T6","shi2jian1\\_0003_6.png",361,12,7,-1,0);
	pngs[5].setValues("T5","shi2jian1\\_0004_5.png",361,12,7,-1,0);
	pngs[6].setValues("T4","shi2jian1\\_0005_4.png",361,12,7,-1,0);
	pngs[7].setValues("T3","shi2jian1\\_0006_3.png",361,12,7,-1,0);
	pngs[8].setValues("T2","shi2jian1\\_0007_2.png",361,12,7,-1,0);
	pngs[9].setValues("T1","shi2jian1\\_0008_1.png",361,12,7,-1,0);
	pngs[10].setValues("T0","shi2jian1\\_0008_1.png",361,12,7,-1,0);
	pngs[11].setValues("TDOT","shi2jian1\\_0009_65306_.png",385,20,7,-1,0);
			 pnStructList=pngs;
	}

	void pubIcon_EventV1::initTxt(){
		txtStruct=texts;
	;}
	void pubIcon_EventV1::initScreen(){
		static bool beIntied=0;
		if(beIntied)
			return;
		beIntied=1;
		initPng();
		initTxt();
	}


#include "pubIcon_EventV1.h"
	 pubIcon_EventV1::pubIcon_EventV1(){
		char *actionList[]={
		NULL};
		setActions(actionList);
		initScreen();	
	};
	void pubIcon_EventV1:: dispatch(MSG_ZHW&msg){
		if(msg.msgID==MSG_ENTER_SCRN){
			_F_INIT_FUN(msg);
			comsumer(msg);return;
		}
		if(msg.msgID==_TIMMER_10PS){
			_F_UPDATE_TIMMER(msg);
			comsumer(msg);
			return;
			}
	}
