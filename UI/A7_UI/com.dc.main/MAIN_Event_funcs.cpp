#include "fix\MAIN_EventV1.h"
	//@Override
#define ICON_WIDTH 163
#define ICON_HEIGHT	146

#define TOP	375
#define LEFT	42

void drawTime(QPainter *qp,BaseStateEventItemV2*screen);

int getLocation(int loc){
	int locationTemp=1024-LEFT*2-ICON_WIDTH*5;
	int dx=locationTemp/5;
	return LEFT+dx*loc+ICON_WIDTH*loc;
}
	char *icions[5]={"CAR_LEFT","BT","RADIO","MUSIC","APP"};
	char *icionsNoDraw[3]={"buttona","buttonb","buttonc"};
	 void MAIN_EventV1::_F_INIT_FUN(MSG_ZHW&msg) {
		// TODO Auto-generated method stub
		//BackUtil.showBackGround(this.getMainActivity(), IScreenConst.backList,IScreenConst.back_id_main);
		//BackUtil.showBackGround(this.getMainActivity(), IScreenConst.backList,IScreenConst.back_id_main);
		 for(int i=0;i<sizeof(icions)/sizeof(icions[0]);i++){
			 PNG_STRUCT* png=findPng(icions[i]);
			 if(png!=NULL){
				 png->xLoc=getLocation(i);
				 png->noDrawWhenActive=true;
			//	 png->yLoc=TOP;
			 }
			 ZString name1=icions[i];
			 name1+="1";
			 png=findPng(name1);
			 if(png!=NULL){
				 png->xLoc=getLocation(i);
			 }
			 name1=icions[i];
			 name1+="2";
			 png=findPng(name1);
			 if(png!=NULL){
				 png->xLoc=getLocation(i);
			 }
		 }
		 for(int i=0;i<sizeof(icionsNoDraw)/sizeof(icionsNoDraw[0]);i++){
			 PNG_STRUCT* png=findPng(icionsNoDraw[i]);
			 if(png!=NULL){
				 png->noDrawWhenActive=true;
			//	 png->yLoc=TOP;
			 }
		 }
	 }
//"SCRN2_MAIN2"
	//@Override
	 unsigned long GetTickCount(void);
	 unsigned long beginDrawTime;
	 int toDrawButi=0;
	 void redraw();
	 int oldMinute=-1;
	 int oldSencord=0;
	 int r_min=1000;
	 int totalKm=1000;
	 int currentKm=0;
	 int speed=0;
	void MAIN_EventV1::_F_UPDATE_TIMMER(MSG_ZHW&msg) {
		// TODO Auto-generated method stub
		QTime current_time = QTime::currentTime();
		if(oldMinute!=current_time.minute()){
			redraw();
			oldMinute=current_time.minute();
		}
		if(oldSencord!=current_time.second()){
			r_min++;
			r_min%=5000;
			totalKm++;
			currentKm+=1;
			speed++;
			speed%=100;
			oldSencord=current_time.second();
			redraw();
		}
		if(0)
		if(toDrawButi){
			if(GetTickCount()-beginDrawTime>2000){
				toDrawButi=0;
				redraw();
			}
		}
	}
	ZString screName2="SCRN2_MAIN2";
	void MAIN_EventV1::_F_NEXT_PAGE(class MSG_ZHW &){
		TO_SCRN(screName2);
	}
	void MAIN_EventV1::_F_CLOSE_SCREEN(MSG_ZHW&msg){
	};
	void MAIN_EventV1::_F_CAR_LEFT(MSG_ZHW&msg){
	};
	void MAIN_EventV1::_F_BT(MSG_ZHW&msg){
	};
	void MAIN_EventV1::_F_RADIO(MSG_ZHW&msg){
		TO_SCRN(ZString("SCRN2_RADIO"));
	};
	void MAIN_EventV1::_F_MUSIC(MSG_ZHW&msg){
		TO_SCRN(ZString("SCRN2_videolist"));
	};
	void MAIN_EventV1::_F_APP(MSG_ZHW&msg){
	};
	void  MAIN_EventV1::_F_buttona(MSG_ZHW&msg){
		toDrawButi=1;
		beginDrawTime=GetTickCount();
	}
	void  MAIN_EventV1::_F_buttonb(MSG_ZHW&msg){
		toDrawButi=2;
		beginDrawTime=GetTickCount();

	}
	
	void  MAIN_EventV1::_F_buttonc(MSG_ZHW&msg){
		if(toDrawButi!=0){
			toDrawButi=0;
			redraw();
		}
		toDrawButi=3;
		beginDrawTime=GetTickCount();
	}
	void MAIN_EventV1::drawDynimicQt(QPainter *qp){
		//char *icions[5]={"CAR_LEFT","BT","RADIO","MUSIC","APP"};
		ZString activeName="";
		if(activePng0!=NULL){
			activeName=activePng0->getMsgName();
		}
		for(int i=0;i<sizeof(icions)/sizeof(icions[0]);i++){
			if(!(activeName==icions[i])){
				drawPic(qp, icions[i]);
			}
		}
		if(activeName.size()>0){
			activeName+="1";
			drawPic(qp, activeName);
		}
		if(toDrawButi==3){
			drawPic(qp, "FDJ1");
			drawPic(qp, "Mkm_h");
			drawSpeedNumber(qp,speed);
			// »ØÖ´ ³µËÙ
		}
		if(this->activePng0!=NULL){
			drawPic(qp, "");
		}
		{
			drawNumber("buttona",qp,r_min);
			drawNumber("buttonb",qp,totalKm);
			drawNumber("buttonc",qp,currentKm);
			
			drawTime(qp,this);
		}
	}
	void MAIN_EventV1::drawSpeedNumber(QPainter *qp,int data){
		PNG_STRUCT *pngLoc=findPng("speedLocation");
		if(pngLoc==NULL){
			return;
		}
		int x=pngLoc->xLoc;
		int y=pngLoc->yLoc;
		ZString str;
		str.format("%2d",data);
		for(int i=0;i<str.size();i++){
			char c=str[i];
			ZString t1;
			//t1="T";
			if(c>='0'&&c<='9'){
				t1.format("N%c",c);
			}
			PNG_STRUCT *pngT=findPng(t1);
			if(pngT!=NULL){
				drawPic(qp,pngT,x,y);
				x+=pngT->width+2;
			}
		}
	}
	void  MAIN_EventV1::drawNumber(char *locName,QPainter *qp,int data){
		PNG_STRUCT *pngLoc=findPng(locName);
		if(pngLoc==NULL){
			return;
		}
		int x=pngLoc->xLoc;
		int y=pngLoc->yLoc;
		ZString str;
		str.format("%2d",data);
		for(int i=0;i<str.size();i++){
			char c=str[i];
			ZString t1;
			//t1="T";
			if(c>='0'&&c<='9'){
				t1.format("S%c",c);
			}
			PNG_STRUCT *pngT=findPng(t1);
			if(pngT!=NULL){
				drawPic(qp,pngT,x,y);
				x+=pngT->width+2;
			}
		}
	}

	
	char * MAIN_EventV1::getTitleName(void){
		return "MAIN";
	}