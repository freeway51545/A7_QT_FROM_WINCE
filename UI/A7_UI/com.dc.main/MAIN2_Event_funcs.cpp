#include "fix\MAIN2_EventV1.h"
	//@Override
#define ICON_WIDTH 163
#define ICON_HEIGHT	146

#define TOP	375
#define LEFT	42

int getLocationPages(int loc){
	int locationTemp=1024-LEFT*2-ICON_WIDTH*5;
	int dx=locationTemp/5;
	return LEFT+dx*loc+ICON_WIDTH*loc;
}

void drawTime(QPainter *qp,BaseStateEventItemV2*screen);

static 	char *icon2[5]={"VEDIO","PIC","VICE","SET","VICH"};
	 void MAIN2_EventV1::_F_INIT_FUN(MSG_ZHW&msg) {
		// TODO Auto-generated method stub
		//BackUtil.showBackGround(this.getMainActivity(), IScreenConst.backList,IScreenConst.back_id_main);
		//BackUtil.showBackGround(this.getMainActivity(), IScreenConst.backList,IScreenConst.back_id_main);
		 for(int i=0;i<sizeof(icon2)/sizeof(icon2[0]);i++){
			 PNG_STRUCT* png=findPng(icon2[i]);
			 if(png!=NULL){
				 png->xLoc=getLocationPages(i);
				 png->noDrawWhenActive=true;
			//	 png->yLoc=TOP;
			 }
			 ZString name1=icon2[i];
			 name1+="1";
			 png=findPng(name1);
			 if(png!=NULL){
				 png->xLoc=getLocationPages(i);
			 }
			 name1=icon2[i];
			 name1+="2";
			 png=findPng(name1);
			 if(png!=NULL){
				 png->xLoc=getLocationPages(i);
			 }
		 }
	 }


	//@Override
	void MAIN2_EventV1::_F_UPDATE_TIMMER(MSG_ZHW&msg) {
		// TODO Auto-generated method stub
	}
	
	void MAIN2_EventV1::_F_PREV_PAGE(MSG_ZHW&msg){
		ZString screName2="SCRN2_MAIN";
		TO_SCRN(screName2);
	};
	void MAIN2_EventV1::_F_VEDIO(MSG_ZHW&msg){
	};
	void MAIN2_EventV1::_F_PIC(MSG_ZHW&msg){
	};
	void MAIN2_EventV1::_F_VICE(MSG_ZHW&msg){
	};
	void MAIN2_EventV1::_F_SET(MSG_ZHW&msg){
	};
	void MAIN2_EventV1::_F_VICH(MSG_ZHW&msg){
	};

	void MAIN2_EventV1::drawDynimicQt(QPainter *qp){
		ZString activeName="";
		if(activePng0!=NULL){
			activeName=activePng0->getMsgName();
		}
		for(int i=0;i<sizeof(icon2)/sizeof(icon2[0]);i++){
			if(!(activeName==icon2[i])){
				drawPic(qp, icon2[i]);
			}
		}
		if(activeName.size()>0){
			activeName+="1";
			drawPic(qp, activeName);
		}
		if(this->activePng0!=NULL){
			drawPic(qp, "");
		}
		drawTime(qp,this);
	}
	char * MAIN2_EventV1::getTitleName(void){
		return "MAIN2";
	}
	