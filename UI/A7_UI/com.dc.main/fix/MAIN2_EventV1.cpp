#include "MAIN2_EventV1.h"
	//public PNG_STRUCT pngStruct0[]=new PNG_STRUCT[34];
	//public TXT_STRUCT txtStruct[]=new TXT_STRUCT[0];
void MAIN2_EventV1::initPng(){
	pngs[0].setValues("±ÚÖ½","qtmain\\bi4zhi3.png",0,0,1,-1,0);
	pngs[1].setValues("×´Ì¬Ìõ","qtmain\\zhuang4tai4lan2\\zhuang4tai4tiao2.png",0,0,1,-1,0);
	pngs[2].setValues("¹ØÆÁ¿ª¹Ø","qtmain\\zhuang4tai4lan2\\guan1ping2kai1guan1.png",56,9,1,-1,0);
	pngs[3].setValues("_0002_Ö÷Ò³","qtmain\\zhuang4tai4lan2\\_0002_zhu3ye4.png",155,12,1,-1,0);
	pngs[4].setValues("CLOSE_SCREEN","qtmain\\zhuang4tai4lan2\\_0002_guan1ping2gao1liang4.png",55,9,0,-1,0);
	pngs[5].setValues("_0001_Í¼²ã-1","qtmain\\zhuang4tai4lan2\\_0001_tu2ceng2-1.png",933,11,1,-1,0);
	pngs[6].setValues("PREV_PAGE","qtmain\\zhuang4tai4lan2\\_0001_tu2ceng2-1.png",933,10,0,-1,0);
	pngs[7].setValues("VEDIO1","qtmain\\dong4tai4tu2biao1\\shi4pin2\\_0011_shi4pin2-kao3bei4-1.png",41,85,7,-1,0);
	pngs[8].setValues("VEDIO","qtmain\\dong4tai4tu2biao1\\shi4pin2\\_0010_shi4pin2.png",48,84,0,-1,0);
	pngs[9].setValues("VEDIO2","qtmain\\dong4tai4tu2biao1\\shi4pin2\\_0009_shi4pin2kao3bei4.png",50,89,7,-1,0);
	pngs[10].setValues("PIC","qtmain\\dong4tai4tu2biao1\\tu2ku4\\_0008_tu2ku4.png",214,99,0,-1,0);
	pngs[11].setValues("PIC2","qtmain\\dong4tai4tu2biao1\\tu2ku4\\_0007_tu2ku4-kao3bei41.png",220,99,7,-1,0);
	pngs[12].setValues("PIC1","qtmain\\dong4tai4tu2biao1\\tu2ku4\\_0006_tu2ku4-kao3bei4.png",228,101,7,-1,0);
	pngs[13].setValues("VICE","qtmain\\dong4tai4tu2biao1\\yu3yin1zhu4shou3\\_0014_yu3yin1zhu4shou3.png",379,81,0,-1,0);
	pngs[14].setValues("VICE1","qtmain\\dong4tai4tu2biao1\\yu3yin1zhu4shou3\\_0013_yu3yin1zhu4shou3-kao3bei41.png",387,82,7,-1,0);
	pngs[15].setValues("VICE2","qtmain\\dong4tai4tu2biao1\\yu3yin1zhu4shou3\\_0012_yu3yin1zhu4shou3kao3bei4.png",398,89,7,-1,0);
	pngs[16].setValues("SET","qtmain\\dong4tai4tu2biao1\\she4zhi4\\_0002_she4zhi4.png",550,83,0,-1,0);
	pngs[17].setValues("SET1","qtmain\\dong4tai4tu2biao1\\she4zhi4\\_0001_she4zhi4-kao3bei41.png",560,82,7,-1,0);
	pngs[18].setValues("SET2","qtmain\\dong4tai4tu2biao1\\she4zhi4\\_0000_she4zhi4-kao3bei4.png",563,85,7,-1,0);
	pngs[19].setValues("VICH","qtmain\\dong4tai4tu2biao1\\che1liang3xin4xi1\\_0005_che1liang3xin4xi1.png",743,100,0,-1,0);
	pngs[20].setValues("VICH1","qtmain\\dong4tai4tu2biao1\\che1liang3xin4xi1\\_0004_che1liang3xin4xi1-kao3bei4-1.png",757,101,7,-1,0);
	pngs[21].setValues("VICH2","qtmain\\dong4tai4tu2biao1\\che1liang3xin4xi1\\_0003_che1liang3xin4xi1-kao3bei4.png",771,106,7,-1,0);
	pngs[22].setValues("timeLocation","qtmain\\button.png",438,11,7,-1,0);
	pngs[23].setValues("T9","shi2jian1\\_0000_9.png",361,12,7,-1,0);
	pngs[24].setValues("T8","shi2jian1\\_0001_8.png",361,12,7,-1,0);
	pngs[25].setValues("T7","shi2jian1\\_0002_7.png",361,12,7,-1,0);
	pngs[26].setValues("T6","shi2jian1\\_0003_6.png",361,12,7,-1,0);
	pngs[27].setValues("T5","shi2jian1\\_0004_5.png",361,12,7,-1,0);
	pngs[28].setValues("T4","shi2jian1\\_0005_4.png",361,12,7,-1,0);
	pngs[29].setValues("T3","shi2jian1\\_0006_3.png",361,12,7,-1,0);
	pngs[30].setValues("T2","shi2jian1\\_0007_2.png",361,12,7,-1,0);
	pngs[31].setValues("T1","shi2jian1\\_0008_1.png",361,12,7,-1,0);
	pngs[32].setValues("T0","shi2jian1\\_0008_1.png",361,12,7,-1,0);
	pngs[33].setValues("TDOT","shi2jian1\\_0009_65306_.png",385,20,7,-1,0);
			 pnStructList=pngs;
	}

	void MAIN2_EventV1::initTxt(){
		txtStruct=texts;
	;}
	void MAIN2_EventV1::initScreen(){
		static bool beIntied=0;
		if(beIntied)
			return;
		beIntied=1;
		initPng();
		initTxt();
	}


#include "MAIN2_EventV1.h"
	 MAIN2_EventV1::MAIN2_EventV1(){
		char *actionList[]={
		"PREV_PAGE",
		"VEDIO",
		"PIC",
		"VICE",
		"SET",
		"VICH",
		NULL};
		setActions(actionList);
		initScreen();	
	};
	void MAIN2_EventV1:: dispatch(MSG_ZHW&msg){
		if(msg.msgID==MSG_ENTER_SCRN){
			_F_INIT_FUN(msg);
			comsumer(msg);return;
		}
		if(msg.msgID==_TIMMER_10PS){
			_F_UPDATE_TIMMER(msg);
			comsumer(msg);
			return;
			}
		if(msg.actionName=="PREV_PAGE"&&msg.msgID==NULL_RELEASE){
			_F_PREV_PAGE(msg);
			comsumer(msg);;
		}
		if(msg.actionName=="VEDIO"&&msg.msgID==NULL_RELEASE){
			_F_VEDIO(msg);
			comsumer(msg);;
		}
		if(msg.actionName=="PIC"&&msg.msgID==NULL_RELEASE){
			_F_PIC(msg);
			comsumer(msg);;
		}
		if(msg.actionName=="VICE"&&msg.msgID==NULL_RELEASE){
			_F_VICE(msg);
			comsumer(msg);;
		}
		if(msg.actionName=="SET"&&msg.msgID==NULL_RELEASE){
			_F_SET(msg);
			comsumer(msg);;
		}
		if(msg.actionName=="VICH"&&msg.msgID==NULL_RELEASE){
			_F_VICH(msg);
			comsumer(msg);;
		}
	}
