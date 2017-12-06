#include "pub.h"
  
#include "BaseStateEventItem2.h"
#include "ReadPNG.h"
//#include "Screen.h"
#include "stdio.h"
#include "ScreenEventManager.h"
#include "pub.H"
void LOG(char*);


UINT8	*getCurrentDataBuffer();
UINT8 *getBackGroundBuf();

void reportDrawThread(TCHAR *infor,void*p);
#define WINCE 

#ifndef WINCE	

BYTE workBuf[2000*2000*4];
UINT8	*getCurrentDataBuffer(){
	return workBuf;
}

BYTE backBuffer[2000*2000*4];
UINT8 *getBackGroundBuf(){
	return backBuffer;
}
 
#endif


 void releaseMetaPicMem();

void exchangeBright();
BaseStateEventItemV2 *finsEventItem(ZString&bseSet);
BaseStateEventItemV2 *activeBsei=NULL;
void traslateMsgPressingM(){
	if(activeBsei!=NULL){
		activeBsei->traslateMsgPressing();
	}
}
void selectScren(ZString no){
	if(no==actScrnNo){
		return;
	}
	actScrnNo=no;
	if(actScrnNo!=SCRN_AVIN2){//20160925
		//exchangeBright();
	}
	try{
		if(activeBsei!=NULL){
			activeBsei->unInitItems();
			activeBsei->hide();
		}
		activeBsei=finsEventItem(no);
		//activeBsei->initItems();
		activeBsei->show();
	}catch(...){
		RETAILMSG(1,(L"EXCEPTION 33\r\n"));
	}

	
	try{
		MSG_ZHW msg;
		msg.msgID=MSG_ENTER_SCRN;
		activeBsei->dispatch(msg);
		//sem.getStateEvent(actScrnNo)
	}catch(...){
		RETAILMSG(1,(L"EXCEPTION 44\r\n"));
	}
	
}




void BaseStateEventItemV2::comsumer(MSG_ZHW&msg){
	
}

bool beKeepCam=false;
bool isDVDScrn(){
	return actScrnNo==SCRN_DVD||actScrnNo==SCRN_DVD1;
}
extern ScreenEventManager  sem;
void closeTurnBar();
//void clearScreen音效();
void setScreen音效(int n);
extern int keepYBegin,keepYEnd;

//#include "CeCriticalSelection.h"
//extern  CeCriticalSelection screenObjectAccess;

TCHAR *getTCHAR1_0A(TCHAR *tBuf,int maxLen,char *toDraw);

bool isScreenNoChanged=false;
void BaseStateEventItemV2::toScreen(ZString screnNo){
	if(!isInMainThread()){
		TO_SCRN_EX_ASY(screnNo);
		return;
	}

	/*CeLock cl(&screenObjectAccess,L"screenObjectAccess.toScreen");
	cl.Lock();*/
	setNewActivePng(NULL);
	
	
	BaseStateEventItemV2 *bse=sem.getStateEvent(screnNo);
	if(bse!=NULL){
		ZString zs("");
		zs=bse->getScreenName();
		TCHAR cur[256];
		TCHAR des[256];
//		MultiByteToWideChar (CP_ACP, 0, getScreenName(), -1, cur, sizeof(cur));
//		MultiByteToWideChar (CP_ACP, 0, zs, -1, des, sizeof(des));
		//RETAILMSG_DC(1,(L"\r\n==========================================\r\n"));
		//RETAILMSG_DC(1,(L"From %s[%d] To %s[%d]\r\n",cur,actScrnNo,des,screnNo));
		//RETAILMSG_DC(1,(L"===========================================\r\n\r\n"));
	}
	isScreenNoChanged=true;
	selectScren(screnNo);
	RE_DRAW;
}


void BaseStateEventItemV2::changeState(int *p,int state){
	*p=state;
	//setBeNeedRedraw(true);
	//ExecuteMessageZhw(MSG_ENTER_STATE,state);
	//RE_DRAW;
}

POINT lastMouse;

FILE *fpDataRecord=NULL;

DWORD lastTime=0;


void BaseStateEventItemV2::clearUnDrawrect()
{
	rectUnDraw.left=NONE;
	beChagedUi=false;
};

PNG_STRUCT *BaseStateEventItemV2::getActivePng(){
	return activePng0;
}


void BaseStateEventItemV2::setBeNeedRedraw(bool b){
	if(ec!=NULL){
		ec->setBeNeedRedraw(b);
	}else{
		RE_DRAW;
	}
}

void BaseStateEventItemV2::revalidateRect(RECT&rect){
	if(rectUnDraw.left==NONE){
		rectUnDraw=rect;
	}else{
		if(rectUnDraw.left>rect.left){
			rectUnDraw.left=rect.left;
		}
		if(rectUnDraw.right<rect.right){
			rectUnDraw.right=rect.right;
		}
		if(rectUnDraw.top>rect.top){
			rectUnDraw.top=rect.top;
		}
		if(rectUnDraw.bottom<rect.bottom){
			rectUnDraw.bottom=rect.bottom;
		}
	}
}

void BaseStateEventItemV2::revalidateRect(PNG_STRUCT *activePng){
	if(activePng==NULL)
		return;
	int left=activePng->xLoc;
	int top=activePng->yLoc;
	int right=left+activePng->width;
	int bottom=top+activePng->height;
	if(rectUnDraw.left==NONE){
		rectUnDraw.left=left;
		rectUnDraw.top=top;
		rectUnDraw.right=right;
		rectUnDraw.bottom=bottom;
	}else{
		if(rectUnDraw.left>left){
			rectUnDraw.left=left;
		}
		if(rectUnDraw.right<right){
			rectUnDraw.right=right;
		}
		if(rectUnDraw.top>top){
			rectUnDraw.top=top;
		}
		if(rectUnDraw.bottom<bottom){
			rectUnDraw.bottom=bottom;
		}
	}
}


void BaseStateEventItemV2::setNewActivePng(PNG_STRUCT *activePng){
	if(activePng0==activePng)
		return;
	revalidateRect(activePng0);
	activePng0=activePng;
	beChagedUi=true;
}


int mouseMoved=0;
extern bool b忽略本按钮;
extern bool beUseVer2;
void BaseStateEventItemV2::traslateMsgPressing(){
	if(activedTimmer>0){
		DWORD dNow=GetTickCount();
		if(dNow-activedTimmer>1000&&dNow-activedTimmer<11000){
			// > 1秒 小于 11 秒
			activedTimmer=0;
			// SEND A PRESSING MESSAGE
			if(activePng0!=NULL){
				//MSG_ZHW *pmsg=&ec->msg;
				if(activePng0!=NULL){
					PostMessageZhw(NULL_PRESSING,(LPARAM)activePng0->getMsgName());
				}
				// 需要等待 RELASE
			}
		}
	}
}

#ifndef WINCE
FILE *fp=NULL;
#endif

//#define LOG_ON


void LOG(char *log){
#ifndef WINCE
	if(fp==NULL){
		fp=fopen("f:\\test.log","wt");
	}
	fprintf(fp,log);
	fflush(fp);
#else
#ifdef LOG_ON
	RETAILMSG_DC(1, (getTCHAR1_0(tBuf,sizeof(tBuf),log)));	
#endif
#endif
}
#include "zstring.h"

void findPngStruct(PNG_STRUCT*png){
	if(png!=NULL){
		ZString buf;
		//char buffer[1000];
		buf.cat("found png ").cat(png->getMsgName()).cat("\r\n");
		LOG(buf);
	}else{
		LOG("find none\r\n");
	}
}
#include "zstring.h"
#include "BaseStateEventItem2.h"

void oldActiveIsStruct(PNG_STRUCT*png){
	if(png!=NULL){
		ZString zs;
		zs.cat("old active png is ").cat(png->getMsgName()).cat("\r\n");
		//sprintf_s(buffer,1000,"old active png is %s\r\n",png->getMsgName());
		LOG(zs);
		zs.destory();
	}else{
		LOG("old active png none\r\n");
	}
}
extern bool doButtonPressedEvn;
bool beLongPressedLock=false;
bool showMouseParameter(TCHAR *msg,EventContext*ec);

#include "ZMyMessage.h"
bool beUseVer2=false;

MSG_ZHW BaseStateEventItemV2::traslateMsg(){
	MSG_ZHW pmsg;//=&ec->msg;
	//pmsg->lParam=ec->lParam;
	//mouseMoved=WM_MOUSEMOVE==ec->message;
	switch(ec->ev->type()){
		case QEvent::MouseButtonPress:
			{
				QMouseEvent *me=(QMouseEvent*)ec->ev;
				mouseDownNative(me->x(),me->y());
				if(ec->eventDealed)
					return pmsg;
				beLongPressedLock=false;
			}
			break;
		case QEvent::MouseButtonRelease:
			{
				QMouseEvent *me=(QMouseEvent*)ec->ev;
				mouseReleaseNative(me->x(),me->y());
				if(ec->eventDealed)
					return pmsg;
				beLongPressedLock=false;
			}
			break ;
		case QEvent::MouseMove:
			{
				mouseMoved=1;	
				QMouseEvent *me=(QMouseEvent*)ec->ev;
				mouseMoveNative(me->x(),me->y());
				//pmsg->noSendRedrawMessageInMouseMove=ec->msg.noSendRedrawMessageInMouseMove;
				if(ec->eventDealed)
					return pmsg;
				}
			break;
	}
	switch(ec->ev->type()){
		case QEvent::MouseButtonPress:
		case QEvent::MouseButtonRelease:
			mouseMoved=0;
		case QEvent::MouseMove:
			{
				QMouseEvent *me=(QMouseEvent*)ec->ev;
				PNG_STRUCT *pngStructActive=NULL;
				if(abs(lastMouse.x-me->x())>3||abs(lastMouse.y-me->y())>3){
					lastMouse.x=me->x();
					lastMouse.y=me->y();
					if(!ec->noSendRedrawMessageInMouseMove){
						setBeNeedRedraw(true);
					}
				}
				PNG_STRUCT *pngStruct=NULL;
				extern BaseStateEventItemV2 *activeBsei;
				if(activeBsei!=NULL){
					BaseStateEventItemV2 *bse=(BaseStateEventItemV2*)activeBsei;
					pngStruct=bse->searchActionPng(me->x(),me->y());
					beUseVer2=true;
				}
				findPngStruct(pngStruct);
				oldActiveIsStruct(activePng0);
				if(pngStruct!=activePng0&&doButtonPressedEvn){
					mouseLeave(activePng0);
					mouseEnter(pngStruct);
				}
				if(pngStruct!=NULL){
					{
						MSG_ZHW msg;
						switch(ec->ev->type()){
								case QEvent::MouseButtonPress:
									//PostMessageZhw(NULL_PRESSED,(LPARAM)pngStruct->getMsgName());
									pngStructActive=pngStruct;
									msg.msgID=NULL_PRESSING;
									msg.actionName=pngStruct->getMsgName();
									dispatch(msg);	
									mouseDown(pmsg);
									break;
								case  QEvent::MouseMove:
									if(doButtonPressedEvn){
										pngStructActive=pngStruct;
									}
									mouseMove(pmsg);
									break;
								case QEvent::MouseButtonRelease:
									//PostMessageZhw(NULL_RELEASE,(LPARAM)pngStruct->getMsgName());
									msg.msgID=NULL_RELEASE;
									msg.actionName=pngStruct->getMsgName();
									dispatch(msg);	
									mouseRelease(pmsg);
									activedTimmer=0;
									break;
								default:
									break;
						}
					}

				}
				setNewActivePng(pngStructActive);
				if(this->isChangedUI()){
					RE_DRAW;
				}
			}
			break;
		case MyEvent:
			{
				ZMyMessage *zmm=(ZMyMessage*)ec->ev;
				pmsg.msgID=zmm->msgId;
				if(zmm->msgId==MSG_KEY_EVENT){
					this->dealKeyEvent(MSG_KEY_EVENT,zmm->lparam);
					return pmsg;
				}else{
					if(zmm->lparam!=NULL){
						pmsg.actionName=(char*)zmm->lparam;
					}
				}
				if(NULL_PRESSING==pmsg.msgID){
					pmsg.msgID=NULL_PRESSING;
				}
				dispatch(pmsg);
			}
			break;
	//case WM_USER:
	//	pmsg->msgID=ec->wParam;
	//	dispatch(*pmsg);
	//	break;
	}
	return pmsg;
}




void BaseStateEventItemV2::mouseLeave(PNG_STRUCT *png){
	if(png==NULL)
		return;
	activedTimmer=0;
}

void BaseStateEventItemV2::mouseEnter(PNG_STRUCT *png){
	if(png==NULL)
		return;
	activedTimmer=GetTickCount();
}

void BaseStateEventItemV2::repaint(){
	RE_DRAW;
}






bool startsWith(char *cc,char *pref)
{
	int len=strlen(pref);
	for(int i=0;i<len;i++){
		if(cc[i]!=pref[i])
			return false;
	}
	return true;
}

TCHAR *getTCHAR1_0A(TCHAR *tBuf,int maxLen,char *toDraw){
	int n=0;
	while(toDraw[n]&&(n<maxLen-1)){
		tBuf[n]=toDraw[n];
		n++;
	}
	tBuf[n]=0;
	return tBuf;
}





TCHAR *getTCHAR1_0(TCHAR *tBuf,int maxLen,char*toDraw){
	/*
	if(toDraw==NULL)
		return NULL;
	DWORD len=MultiByteToWideChar (CP_ACP, 0,toDraw, -1, NULL, 0);
	if(len>=maxLen-1){
		len=maxLen-1;
	}
	MultiByteToWideChar (CP_ACP, 0, toDraw, -1, tBuf, len);
	*/
	return tBuf;
}
