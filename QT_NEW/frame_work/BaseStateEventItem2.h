#ifndef BaseStateEventItem2_H
#define BaseStateEventItem2_H
#include "pub.h"
#include "PaintedWidget.h"
#include "list.h"

#include "Msg.h"	
class EventContext;
class PNG_STRUCT;
#include "pngstruct.h"



#define NONE	-99999

class BaseStateEventItem{
	
};

#define _F_NULL_(x)
#define COSUMER_CALL(x) x(msg)
#define IS_COMSUMED_RETURN(msg) if(msg.comsumered)return;

class BaseStateEventItemV2{

	bool beChagedUi;
	DWORD activedTimmer;
public:
	//int STATE;
	HWND currenthWnd;
	EventContext * ec;
	char **acList;
	void setBeNeedRedraw(bool b);
	PNG_STRUCT *getActivePng();
	RECT rectUnDraw;// 消除位置。
	void setNewActivePng(PNG_STRUCT *activePng);
	PNG_STRUCT *activePng0;
	void revalidateRect(RECT&rect);
	void revalidateRect(PNG_STRUCT *activePng);
	RECT getUnDrawRect(){return rectUnDraw;};
	void clearUnDrawrect();
	bool isChangedUI(){return beChagedUi;}
public:
	virtual void dispatch(MSG_ZHW&msg)=0;
	void comsumer(MSG_ZHW&msg);
	void CHANGED_TO_STATE(int stateId);
	void mouseLeave(PNG_STRUCT*png);
	void mouseEnter(PNG_STRUCT*png);
	void traslateMsgPressing();
	virtual bool is独占MouseMove(){return false;};
	virtual int getMsgLen()=0;
	/** 绘制动态界面 */

	/** 可以给其他窗口进行重载*/
	//}
	HWND getCurrentHwnd(){return currenthWnd;};
	void toScreen(ZString screnNo);
	void changeState(int *p,int state);
	virtual void mouseDown(MSG_ZHW&){};
	virtual void mouseMove(MSG_ZHW&){};
	virtual void mouseRelease(MSG_ZHW&){};
	virtual void mouseDownNative(int /*x*/,int /*y*/){};
	virtual void mouseMoveNative(int /*x*/,int /*y*/){};
	virtual void mouseReleaseNative(int /*x*/,int /*y*/){};
	virtual bool isDrawSelectItem(){return true;}
	void repaint();
	virtual bool isIn动画(){return false;}
	virtual char* getScreenName(){return "UNKOWN";};
	virtual char* getTitleName()=NULL;
	virtual bool dealKeyEvent(WPARAM /*wp*/,LPARAM /*lp*/){return false;}
	virtual bool beHasAction(char *action){return false;};
	void setActions(char *actionList[]){acList=actionList;};
	virtual int getDlgMainViewId(){return 0;};//	
	virtual bool isDlg(){return false;};//' : is not a member of 'RADIO_COMFIRE_EventV1'
	virtual int getActiveViewId(){return 0;};
	virtual int getBackId(){return 0;};
	// include all screen function
	QVector<QListView*> listList;
private:
	void addToHideComponet(QListView *qListView){
		listList.append(qListView);
	}
public:	
	//PNG_STRUCT pngs[65];
#define QSMAX	10	
	QVector<QScrollBar*> tsbList;
	BaseStateEventItemV2(){
		pw=NULL;
		beChagedUi=true;
		activePng0=NULL;
	}
	QImage* backGroundImage;
	virtual int getPngLength()=0;
	//TXT_STRUCT	texts[5];
	virtual int getTextLength()=0;
	PNG_STRUCT *pnStructList;
	TXT_STRUCT *txtStruct;
	
	TXT_STRUCT *findTxt(char* name) ;
	 void setPngs(PNG_STRUCT* pngs) ;

	 void setTexts(TXT_STRUCT* texts);

	RECT getRect(char* name) ;

	PNG_STRUCT*findPng(char* name) ;
	void drawOnScreen(QPainter *qp);
	void initItems() ;
	void unInitItems();

	void drawBackGround(QPainter *c) ;
	void drawOnScreen(BYTE* membuffer);

	 void drawOnScreen0(QPainter *c);
	 PNG_STRUCT *searchActionPng(int x, int y) ;
	virtual	void mouseDown(float x, float y) ;

	virtual void mouseUp(float x, float y) ;
	MSG_ZHW BaseStateEventItemV2::traslateMsg();
	PNG_STRUCT *searchActionPng(float x, float y) ;


	void drawPicProcessV(QPainter *c, char* name, int value, int max) ;
	void setAllTextShowNull() ;

	

	void setScreenTxtMiddle(char* names[], int length) ;

	void drawTextReplace3(QPainter *c, char* name, char* replaceValue,
			int color, bool bBorder, int xOffSet, int yOffSet) ;

	void drawTextReplace(QPainter *c, char* name, char* replaceValue,
			bool bBorder, int xOffSet, int yOffSet) ;

	void drawTextReplace(QPainter *c, char* name, char* replaceValue) ;

	void drawTextReplaceNotNull(QPainter * c, char* name,
			char* replaceValue, bool bBorder, int xOffSet, int yOffSet) ;

	void drawTextReplace(QPainter *c, char* name, char* replaceValue,
			int color, bool bBorder) ;

	void drawTextReplace(QPainter *c, char* name, char* replaceValue,
			int color, int xOffSet, int yOffSet) ;
	void drawPicProcessH(QPainter * c, char* name, int value, int max) ;

	void setAllTextShowMiddle() ;
	void drawPic(QPainter * c, char* string) ;
	PNG_STRUCT getDlgBack() ;

	void setAllTextShowRight();

	void drawPic(QPainter * c, PNG_STRUCT*png, int xVal, int yVal) ;

	void setAllTextShowLeft() ;

	void setThisUiIsNotMain() ;
	virtual void drawDynimicQt(QPainter *qp)=0;
	void addScrollBar(QScrollBar*sqb);
	void setAllActiveNoDraw(char *names[],int num);
	void drawTextInBox(QPainter *qp,char *data,int fountSize,char *boxName,COLORREF rgb,int yAddjust=0);
	virtual void show();
	virtual void hide();
	QListViewMy*  makeListView();
	PaintedWidget *getPaintedWidget();
	void activeTraslateMsg(QEvent*ev);
private:
	PaintedWidget *pw;/** 绑定的WINDOWS */
public:
	void redraw(){
		getPaintedWidget()->update();
	}
};

#endif