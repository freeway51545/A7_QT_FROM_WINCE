#include "videolist_EventV1.h"
	//public PNG_STRUCT pngStruct0[]=new PNG_STRUCT[8];
	//public TXT_STRUCT txtStruct[]=new TXT_STRUCT[1];
void videolist_EventV1::initPng(){
	pngs[0].setValues("±⁄÷Ω","shou1yin1ji1\\bi4zhi3.png",0,0,1,-1,0);
	pngs[1].setValues("_0006_æÿ–Œ-1","shou1yin1ji1\\zhuang4tai4lan2\\_0006_ju3xing2-1.png",0,0,1,-1,0);
	pngs[2].setValues("_0000_Õº≤„-16","shou1yin1ji1\\zhuang4tai4lan2\\_0000_tu2ceng2-16.png",39,9,1,-1,0);
	pngs[3].setValues("_0002_Õº≤„-18","shou1yin1ji1\\zhuang4tai4lan2\\_0002_tu2ceng2-18.png",952,14,1,-1,0);
	pngs[4].setValues("HOME","shou1yin1ji1\\zhuang4tai4lan2\\_0000_tu2ceng2-16.png",40,6,0,-1,0);
	pngs[5].setValues("BACK","shou1yin1ji1\\zhuang4tai4lan2\\_0002_tu2ceng2-18.png",951,12,0,-1,0);
	pngs[6].setValues("lettel","vediolist\\lettel.png",925,75,2,-1,0);
	pngs[7].setValues("list","vediolist\\list.png",102,75,2,-1,0);
			 pnStructList=pngs;
	}

	void videolist_EventV1::initTxt(){
		texts[0].setValues("“Ù¿÷",117,3,100,36,0xffffffff,10,0,0,0);
		txtStruct=texts;
	;}
	void videolist_EventV1::initScreen(){
		static bool beIntied=0;
		if(beIntied)
			return;
		beIntied=1;
		initPng();
		initTxt();
	}


#include "videolist_EventV1.h"
	 videolist_EventV1::videolist_EventV1(){
		char *actionList[]={
		"HOME",
		"BACK",
		NULL};
		setActions(actionList);
		initScreen();	
	};
	void videolist_EventV1:: dispatch(MSG_ZHW&msg){
		if(msg.msgID==MSG_ENTER_SCRN){
			_F_INIT_FUN(msg);
			comsumer(msg);return;
		}
		if(msg.msgID==_TIMMER_10PS){
			_F_UPDATE_TIMMER(msg);
			comsumer(msg);
			return;
			}
		if(msg.actionName=="HOME"&&msg.msgID==NULL_RELEASE){
			_F_HOME(msg);
			comsumer(msg);;
		}
		if(msg.actionName=="BACK"&&msg.msgID==NULL_RELEASE){
			_F_BACK(msg);
			comsumer(msg);;
		}
	}
