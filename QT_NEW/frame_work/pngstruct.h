#ifndef _ZHW_STRUCT
#define _ZHW_STRUCT


#include "SCREENMEM.H"


void loadSetting();
void loadScreen(int n);
void saveSetting();

void initActiveScreen();

#define BACK_GROUND	100


#define PIC_DYNAMIC_DRAW			7
#define PIC_BACK_GROUND				1
#define PIC_SELECT_PIC				0
#define PIC_SELECT_PIC_NO_DRAW		2
#define PIC_USE_AFTER_CUT			8

class BaseItem{
public:
	void makeNameCode();
	char *aliasName;
	char *name;
	int nameCode; /**  提高查找速度 */
	int aliasNameCode; /** 提高查找速度 */
	int xLoc;
	int yLoc;
	unsigned long width;
	unsigned long height;
	int showCondition;	//0,allways show,1、move on show 
	int showCustomer;
	bool inBox(int x,int y);
	int inBoxDest(int x,int y);
	ZString getLocStr();
	RECT *bounder;
	TCHAR *getNameAndAlias(TCHAR *name,int len);
	bool beRGBASwitched;
	BaseItem(){
		showCustomer=-1;
		showCondition=0;
		width=height=0;
		xLoc=yLoc=0;
		name=aliasName=NULL;
		beRGBASwitched=false;
		bounder=NULL;
	};

	void moveDxDy(int dx,int dy){
		xLoc+=dx;
		yLoc+=dy;
	}
	int getShowCondition(){
		return showCondition;
	}
	int getX(){
		return xLoc;
	};

	int getY(){
		return yLoc;
	};
	int getWidth(){
		return width;
	};
	int getHeight(){
		return height;
	};
	char *getName(){
		return name;
	}
	char *getMsgName(){
		if(aliasName!=NULL)
			return aliasName;
		return name;
	}

	void setLocation(int x,int y){
		xLoc=x;
		yLoc=y;
	}
	void setRect(RECT r){
		xLoc=r.left;
		yLoc=r.top;
		width=r.right-r.left;
		height=r.bottom-r.top;
	}
	RECT getRect()
	{
		RECT r;
		r.left=xLoc;
		r.top=yLoc;
		r.right=r.left+width;
		r.bottom=r.top+height;
		return r;
	};
};


class PNG_STRUCT:public BaseItem{
public:
	bool noDrawWhenActive;
	//virtual BYTE*getData(){return data;};
	void unLoadPNG();
	//virtual BYTE*get16BitData();
	//bool beChangedTo16BIT;
	void resetAllPngInfor();
	POINT getLocation(){
		POINT p;
		p.x=xLoc;
		p.y=yLoc;
		return p;
	};
	virtual void draw(QPainter *qp);
public:
	QImage* imageBitmap;
	int nNumberPic;
	void loadPNG();
	PNG_STRUCT(){
		noDrawWhenActive=false;
	};
	void *fetchImageBitmap();
	bool isShowMe() {
		if (showCustomer != -1)
			return true;
		switch (getShowCondition()) {
		case 0:
		case 2:
		case 6:
		case 7:
			return false;
		case 8:
			return false;
		}
		return true;
	}

	void setValues(char* aliasNameSet, char* nameSet, int xLocSet,
			int yLocSet, int showConditionSet, int showCustomerSet,
			int nNumberPicSet) {
		aliasName = aliasNameSet;
		name = nameSet;
		xLoc = xLocSet;
		yLoc = yLocSet;
		showCondition = showConditionSet;
		showCustomer = showCustomerSet;
		// nNumberPic = nNumberPicSet;
	}
};








#define LEFT	0
#define	RIGHT	1
#define MIDDLE	2
class BaseStateEventItemV2;

class TXT_STRUCT:public BaseItem{
public:
	COLORREF rgb;
	DWORD lBeginScrollTime;
	bool boder;
	bool beScrollMe;
	int fontSize;
	// 设置变形的数据。
	int dY;
	int dHgith;
	char *replaceValue;
	int nShowOffSet;
	unsigned char layOutMode;
	TXT_STRUCT(BaseStateEventItemV2*s,char *idAsName,int fontSize);
	TXT_STRUCT(){replaceValue=NULL;bounder=NULL;boder=false;layOutMode=LEFT;nShowOffSet=0;beScrollMe=false;};
	char *getShowString();
	void setTextBeginScroll();
	void setTextBeginScroll(DWORD l);
	void setValues(char *nameSet, int xLocSet, int yLocSet,
			int widthSet, int heightSet, int rgbSet, int fontSizeSet,
			int showConditionSet, int dySet, int dHgithSet) {
		name = nameSet;
		xLoc = xLocSet;
		yLoc = yLocSet;
		width = widthSet;
		height = heightSet;
		rgb = rgbSet;
		fontSize = heightSet;// 没有fontSizeSet
		showCondition = showConditionSet;
		dY = dySet;
		dHgith = dHgithSet;
	}
	void draw(QPainter *qp);
};

#ifdef WINCE
#define ROOT_LOC	"/StaticStore"
#else
#define ROOT_LOC	"f:/ZHW-wince-C/ARM11/WORK-DIR"
#endif
//#define ROOT_LOC	"硬盘"

typedef struct _PIC_IMG{
	char ID[30];
	int width;
	int height;
	int bytePerPixel;
}PIC_IMG;

//extern PNG_STRUCT backGroundStruct;

void fillSubNames(PNG_STRUCT&);

#endif