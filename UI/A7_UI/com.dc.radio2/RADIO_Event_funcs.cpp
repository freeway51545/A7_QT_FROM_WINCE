#include "fix\RADIO_EventV1.h"
#include <qscrollbar.h>
//@Override


// 
//		添加滚动条
//
//		添加列表控件
//
//
#include "收音机pub.h"
#include "radioControl.h"

void redraw();
RadioWork *getFMWorker();
RadioWork *getAMWorker();
extern bool bRadioNeedMute;
bool isInited=false;
RadioWork *radioWork=NULL;
void radioLoad();
void radioPlayCurrent();
static bool inSaveMode=0;
char *noDraw[]={"p1","p2","p3","p4","p5","p6"};
int nBand=0;
void nextBand(){
	nBand++;
	nBand%=5;
	if(nBand==3){
		radioWork=getAMWorker();
	}
	if(nBand==0){
		radioWork=getFMWorker();
	}
	int nOffSet=nBand%3;
	radioWork->setBeginLoc(nOffSet*6);
}

void openRadioGlobal(){
	//	OPEN_RADIO_VOLUME();
	if(!isInited){
		isInited=true;
		getFMWorker()->init();
		getAMWorker()->init();
		if(radioWork==NULL){
			radioWork=getFMWorker();
		}
		radioLoad();
		//radioPlayCurrent();
	}
	setSrcType(SRC_RADIO);
}


static QScrollBar *qsb=NULL;
void RADIO_EventV1::_F_INIT_FUN(MSG_ZHW&msg) {

	//		TODO Auto-generated method stub
	//		BackUtil.showBackGround(this.getMainActivity(), IScreenConst.backList,IScreenConst.back_id_radio);
	//		BackUtil.setBackGround("radio");
	//	addBar(qsb);
	setAllActiveNoDraw(noDraw,6);
	openRadioGlobal();
	setAllTextShowMiddle();
	if(qsb==NULL){
		//	qsb=new QScrollBar();
		//	addScrollBar(qsb);
		//	qsb->move(300,300);
		//	qsb->resize(100,30);
	}

}

//@Override
void RADIO_EventV1::_F_UPDATE_TIMMER(MSG_ZHW&msg) {
	// TODO Auto-generated method stub
}


/*
void drawRadioFreq(Canvas canvas) {
String freqStr = RadioData.getCurrentFreqString();
TXT_STRUCT txt = getBindScreen().findTxt("FREQ");
if (txt != null) {
DrawNumManager.drawString(getBindScreen(), canvas, freqStr, "P", txt.xLoc, txt.yLoc);
}
TXT_STRUCT txt1 = getBindScreen().findTxt("RATE");
if (txt1 != null) {
DrawNumManager.drawStringExt(getBindScreen(), canvas, freqStr, "S", txt1.xLoc, txt1.yLoc);
}
}
*/
void RADIO_EventV1::_F_STOP(MSG_ZHW&msg){
};
void RADIO_EventV1::_F_EQ(MSG_ZHW&msg){
};

void RADIO_EventV1::_F_BAND(MSG_ZHW&msg){
	nextBand();
	redraw();
};
void RADIO_EventV1::_F_PREV(MSG_ZHW&msg){
};
void RADIO_EventV1::_F_NEXT(MSG_ZHW&msg){
};
void RADIO_EventV1::_F_SEARCH(MSG_ZHW&msg){
};

void RADIO_EventV1::_F_p(MSG_ZHW&msg,char* no){
	
	int nNo=no[0]-'1';
	if(nNo>=0&&nNo<6){
		if(inSaveMode){
			radioWork->storeCurrentPlAt(nNo);
			redraw();
			inSaveMode=0;
		}else{
			radioWork->turnLoc(nNo);
			redraw();
		}
	}
};


void RADIO_EventV1::_F_SUB_ONE(MSG_ZHW&msg){
};
void RADIO_EventV1::_F_HOME(MSG_ZHW&msg){
	ZString screName2="SCRN2_MAIN";
	TO_SCRN(screName2);
};
void RADIO_EventV1::_F_BACK(MSG_ZHW&msg){
	ZString screName2="SCRN2_MAIN";
	TO_SCRN(screName2);
};
void RADIO_EventV1::_F_PLUS_ONE(MSG_ZHW&msg){
};


bool mPauseFlag=false;
void drawTime(QPainter *qp,BaseStateEventItemV2*screen);
char *names[]={"STOP","BAND","PREV","NEXT","SEARCH"};
char *namesIcon[]={"STOP_P","BAND_P","PREV_P","NEXT_P","SEARCH_P"};


void drawStringRadio(QPainter *qp,RADIO_EventV1*bi,ZString &zs,int x,int y){
	for(int i=0;i<zs.size();i++){
		int mm =zs.size();
		char c=zs[i];
		PNG_STRUCT * pngNew=NULL;
		if(c>='0'&&c<='9'){
			ZString zsPng;
			//zsPng.format("%s%c",begin,c);
			zsPng.format("N%c",c);
			pngNew=bi->findPng(zsPng);
		}
		if(c=='.'){
			pngNew=bi->findPng("dot");
		}
		if(pngNew!=NULL){
			bi->drawPic(qp,pngNew,x,y);
			/*if(c=='.'){
			x+=pngNew->getWidth()/2;
			}else{
			x+=pngNew->getWidth();
			}*/
			x+=pngNew->getWidth()+4;
		}
	}
}


void drawStringRadioS(QPainter *qp,RADIO_EventV1*bi,ZString &zs,int x,int y){
	for(int i=0;i<zs.size();i++){
		int mm =zs.size();
		char c=zs[i];
		PNG_STRUCT * pngNew=NULL;
		if(c>='0'&&c<='9'){
			ZString zsPng;
			//zsPng.format("%s%c",begin,c);
			zsPng.format("S%c",c);
			pngNew=bi->findPng(zsPng);
		}
		if(c=='.'){
			pngNew=bi->findPng("sdot");
		}
		if(pngNew!=NULL){
			bi->drawPic(qp,pngNew,x,y);
			/*if(c=='.'){
			x+=pngNew->getWidth()/2;
			}else{
			x+=pngNew->getWidth();
			}*/
			x+=pngNew->getWidth()+4;
		}
	}
}
void drawRadioFreq(QPainter *qp,RADIO_EventV1*bi,PNG_STRUCT *activePng0){
	ZString infor=radioWork->getCurrentShowMain();
	//PNG_STRUCT *png=bi->findPng("PL_LOCAION");
	{
		ZString zs;
		if(	nBand<3){
			zs.format("FM%d",nBand+1);
		}else{
			zs.format("AM%d",nBand-3+1);
		}
		bi->drawTextInBox(qp,zs,30,"FM123",0xFF00FFFF,0);
		//PNG_STRUCT *pngFM123=bi->findPng("FM123");
		
	}
	//if(png!=NULL)
	{
		//if(0)
		//	drawStringRadio(qp,bi,infor,png->xLoc,png->yLoc);
		//bi->drawTextInBox(qp,infor,76,"PL_LOCAION",0XFFFFFFFF,10);
		bi->drawTextReplace(qp,"PL_LOCAION",infor,0XFFFFFFFF,false);
		/*
		TXT_STRUCT txt;
		txt.name=infor;
		txt.xLoc=png->xLoc-30;
		txt.yLoc=png->yLoc+83;
		txt.layOutMode=MIDDLE;
		txt.width=300;
		txt.height=76;
		txt.fontSize=76;
		txt.rgb=0xFFFFFFFF;
		txt.draw(qp);
		*/
	}
	if(inSaveMode){
		bi->drawPic(qp,"SF1");
		bi->drawPic(qp,"SF2");
		bi->drawPic(qp,"SF3");
		bi->drawPic(qp,"SF4");
		bi->drawPic(qp,"SF5");
		bi->drawPic(qp,"SF6");
	}

	{
		if(0)
		for(int i=1;i<=6;i++){
			ZString st;
			st.format("p%d",i);
			PNG_STRUCT *png=bi->findPng(st);
			if(png!=NULL){
				infor=radioWork->getShowString(i-1);
				drawStringRadioS(qp,bi,infor,png->xLoc,png->yLoc+10);
			}
		}
		ZString activeName;
		if(activePng0!=NULL){
			activeName=activePng0->getMsgName();
		}
		for(int i=1;i<=6;i++){
			ZString st;
			st.format("p%d",i);
			//PNG_STRUCT *png=bi->findPng(st);
			infor=radioWork->getShowString(i-1);
			COLORREF color=0;
			if(activeName==st){
				activePng0->draw(qp);
				color=0xFF00FFFF;
			}else{
				color=0xFFFFFFFF;
			}
			if(inSaveMode){
				color=0xFFFF00FF;
			}
			bi->drawTextInBox(qp,infor,40,st,color,0);
		}

	}
	/*
	TXT_STRUCT *txt=screen->findTxt("FREQ");
	if(txt!=NULL){
	DNM.drawStringRadio(screen,dc,infor,"P",txt->xLoc,txt->yLoc);	
	}	

	TXT_STRUCT *txt1=screen->findTxt("RATE");
	if(txt1!=NULL){
	if(radioWork->getCurrentFreq()<10000){
	DNM.drawStringExt(screen,dc,infor,"S",txt1->xLoc+10,txt1->yLoc);	
	}else{
	DNM.drawStringExt(screen,dc,infor,"S",txt1->xLoc,txt1->yLoc);	
	}

	}
	*/
}


void RADIO_EventV1::drawDynimicQt(QPainter *qp){
	drawTime(qp,this);
	drawPic(qp,"BAR");
	if(activePng0!=NULL){
		ZString name;
		name=activePng0->getMsgName();
		for(int i=0;i<sizeof(names)/sizeof(names[0]);i++){
			if(name==names[i]){
				this->drawPic(qp,namesIcon[i]);
			}
		}
	}
	drawRadioFreq(qp,this,activePng0);
	if(inSaveMode){
		if(activePng0!=NULL){
			this->drawPic(qp,activePng0,activePng0->xLoc,activePng0->yLoc);
		}
	}
	drawPic(qp,"SUB");
	drawPic(qp,"plus");
	double loc=(radioWork->getCurrentFreq()-radioWork->min)*1.0/(radioWork->max-radioWork->min);
	PNG_STRUCT *png=findPng("BAR");
	PNG_STRUCT *pngPointer=findPng("pointer");
	if(png!=NULL&&pngPointer!=NULL){
		RECT r=png->getRect();
		int length=(r.right-r.left)-pngPointer->width;
		int locx=loc*length+r.left;
		this->drawPic(qp,pngPointer,locx,pngPointer->yLoc);
	}
	if(radioWork->isFm()){
		drawPic(qp,"mhz");
	}else{
		drawPic(qp,"khz");
	}
}

bool inBox(RECT r,int x,int y);
int getValueXX(int x,int xMin,int xMax,int min,int max);
char * RADIO_EventV1::getTitleName(void){
	return "RADIO";
}

void RADIO_EventV1::moveTo(int x,int y){
	PNG_STRUCT *png=findPng("BAR");
	if(png==NULL){
		return;
	}
	RECT r= png->getRect();
	r=LargRect(r,10);
	if(inBox(r,x,y)){
		int pl=getValueXX(x,r.left,r.right,radioWork->min,radioWork->max);
		pl=pl/radioWork->step*radioWork->step;
		radioWork->setCurrentFreq(pl);
		redraw();
	}
}
void RADIO_EventV1::mouseDownNative(int x,int y){

}
void RADIO_EventV1::_F_SAVE(MSG_ZHW &){
	inSaveMode=!inSaveMode;
	redraw();
}
void RADIO_EventV1::mouseReleaseNative(int x,int y){
	moveTo(x,y);
}
void RADIO_EventV1::mouseMoveNative(int x,int y){
	moveTo(x,y);
}


int getValueXX(int x,int xMin,int xMax,int min,int max){
	xMin+=10;
	xMax-=10;
	int value=(x-xMin)*(max-min+1)/(xMax-xMin)+min;
	if(max>min){
		if(value<min)
			value=min;
		if(value>max)
			value=max;
	}else{
		if(value>min)
			value=min;
		if(value<max)
			value=max;
	}
	return value;
}


//扩大矩形区域
RECT LargRect(RECT r,int w){
	r.left-=w;
	r.top-=w;
	r.bottom+=w;
	r.right+=w;
	return r;
}