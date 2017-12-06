#include "fix\pubIcon_EventV1.h"
//@Override
void pubIcon_EventV1::_F_INIT_FUN(MSG_ZHW&msg) {
	// TODO Auto-generated method stub
	//BackUtil.showBackGround(this.getMainActivity(), IScreenConst.backList,IScreenConst.back_id_pubicon);
	//BackUtil.showBackGround(this.getMainActivity(), IScreenConst.backList,IScreenConst.back_id_pubicon);
}

//@Override
void pubIcon_EventV1::_F_UPDATE_TIMMER(MSG_ZHW&msg) {
	// TODO Auto-generated method stub
}

char * pubIcon_EventV1::getTitleName(void){
	return "MAIN";
}
void  pubIcon_EventV1::drawDynimicQt(QPainter *qp){
}
BaseStateEventItemV2 * finsEventItem(ZString&name);
void drawTime(QPainter *qp,BaseStateEventItemV2*screen){
		BaseStateEventItemV2*screenPub=(BaseStateEventItemV2*)finsEventItem(ZString(SCRN2_pubIcon));
		QTime current_time = QTime::currentTime();
		PNG_STRUCT *pngLoc=screen->findPng("timeLocation");
		if(pngLoc==NULL){
			pngLoc=screenPub->findPng("timeLocation");
			if(pngLoc==NULL){
				return;
			}
		}
		int x=pngLoc->xLoc;
		int y=pngLoc->yLoc;
		ZString str;
		str.format("%d:%02d",current_time.hour(),current_time.minute());
		for(int i=0;i<str.size();i++){
			char c=str[i];
			ZString t1;
			//t1="T";
			if(c>='0'&&c<='9'){
				t1.format("T%c",c);
			}else{
				t1="TDOT";
			}
			PNG_STRUCT *pngT=screenPub->findPng(t1);
			if(pngT!=NULL){
				screen->drawPic(qp,pngT,x,y);
				x+=pngT->width+6;
			}
		}
	}

void initPub(){
	BaseStateEventItemV2*screenPub=(BaseStateEventItemV2*)finsEventItem(ZString("SCRN2_pubIcon"));
	if(screenPub!=NULL){
		screenPub->initItems();
	}
}