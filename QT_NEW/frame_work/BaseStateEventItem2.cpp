#include "BaseStateEventItem2.h"


TXT_STRUCT *BaseStateEventItemV2::findTxt(char* name) {
	if (name == NULL)
		return NULL;
	for (int i = 0; i < getTextLength(); i++) {
		if (strcmp(name,txtStruct[i].name)==0)
			return &txtStruct[i];

	}
	return NULL;
}
void BaseStateEventItemV2::setPngs(PNG_STRUCT* pngs) {
	// TODO Auto-generated method stub
	pnStructList = pngs;
}

void BaseStateEventItemV2::setTexts(TXT_STRUCT* texts) {
	// TODO Auto-generated method stub
	txtStruct = texts;
}

RECT BaseStateEventItemV2::getRect(char* name) {
	RECT r;
	PNG_STRUCT *png = findPng(name);
	if (png == NULL) {
		TXT_STRUCT *c = findTxt(name);
		if (c != NULL) {
			r = c->getRect();
		}
		return r;
	}
	return png->getRect();
}

PNG_STRUCT*BaseStateEventItemV2::findPng(char* name) {
	if (pnStructList == NULL) {
		return NULL;
	}
	if (name == NULL)
		return NULL;
	for (int i = 0; i < getPngLength(); i++) {
		if (strcmp(name,pnStructList[i].name)==0) {
			PNG_STRUCT*png=&pnStructList[i];
			png->fetchImageBitmap();
			return png;
		}
		if(pnStructList[i].aliasName!=NULL){
			if (strcmp(name,pnStructList[i].aliasName)==0) {
				pnStructList[i].fetchImageBitmap();
				return &pnStructList[i];
			}
		}
	}
	return NULL;
}

void BaseStateEventItemV2::initItems() {
	if (pnStructList != NULL) {
		for (int i = 0; i < getPngLength(); i++) {
			//pnStructList[i].fetchImageBitmap();
			//pnStructList[i].fillSubNames();
		}
	}
}


void BaseStateEventItemV2::unInitItems() {
	//if (beLockAllImage)
	//	return;
	if (pnStructList != NULL) {
		for (int i = 0; i < getPngLength(); i++) {
			pnStructList[i].unLoadPNG();
		}
	}
}



extern BOOL bInDrawOverlay;
UINT8	*getCurrentDataBufferToShow();
UINT8	*getCurrentDataBufferToShowOverly();

extern QPaintEvent *pwThisEvent;
void BaseStateEventItemV2::drawOnScreen(QPainter *qp){
	//		CeLock cl(&screenObjectAccess,L"drawOnScreen");
	//		cl.Lock();
	PNG_STRUCT  *png=getActivePng();
	if(png!=NULL){
		if(!png->noDrawWhenActive){
			png->draw(qp);
		}
	}

	drawDynimicQt(qp);
}



PNG_STRUCT *BaseStateEventItemV2::searchActionPng(int x, int y) {
	// x -= IScreenConst.xOrg;
	// y -= IScreenConst.yOrg;
	if (pnStructList == NULL)
		return NULL;
	for (int i = 0; i < getPngLength(); i++) {
		PNG_STRUCT &pngStruct = pnStructList[i];
		int showCondition = pngStruct.getShowCondition();
		if (showCondition == 0
			|| showCondition ==2) {
				if (pngStruct.getWidth() == 0) {
					pngStruct.fetchImageBitmap();
				}
				if (pngStruct.inBox(x, y)) {
					// System.out.println("found png" + pngStruct.name);
					return &pngStruct;
				}
		}
	}
	return NULL;
}

void BaseStateEventItemV2::mouseDown(float x, float y) {
	// TODO Auto-generated method stub

}

void BaseStateEventItemV2::mouseUp(float x, float y) {
	// TODO Auto-generated method stub

}

PNG_STRUCT *BaseStateEventItemV2::searchActionPng(float x, float y) {
	// TODO Auto-generated method stub
	return searchActionPng((int) x, (int) y);
}


void BaseStateEventItemV2::drawPicProcessV(QPainter *c, char* name, int value, int max) {
	// TODO Auto-generated method stub
	// CLEAR ALL BAR DATA
	PNG_STRUCT *png = findPng(name);
	//png.drawPicProcessV(c, value, max);
}

void BaseStateEventItemV2::setAllTextShowNull() {
	// TODO Auto-generated method stub
	for (int i = 0; i < getTextLength(); i++) {
		txtStruct[i].replaceValue = "";
	}

}


//extern QWidget *wParent;
extern QMainWindow *qmw;
void BaseStateEventItemV2::addScrollBar(QScrollBar*sqb){
	if(tsbList.indexOf(sqb)>=0){
		return;
	}
	//		wParent->addWidget(sbq);
	sqb->setParent(getPaintedWidget());
	//QVBoxLayout
	tsbList.append(sqb);
}

void BaseStateEventItemV2::setAllActiveNoDraw(char *names[],int num){
	for(int i=0;i<num;i++){
		PNG_STRUCT* png=findPng(names[i]);
		if(png!=NULL){
			png->noDrawWhenActive=true;
			//	 png->yLoc=TOP;
		}
	}
}
void BaseStateEventItemV2::setScreenTxtMiddle(char* names[], int length) {
	// TODO Auto-generated method stub
	for (int i = 0; i < length; i++) {
		TXT_STRUCT *txt = findTxt(names[i]);
		if (txt != NULL) {
			txt->layOutMode = 2;// MIDDLE
		}
	}
}

void BaseStateEventItemV2::drawTextReplace3(QPainter *c, char* name, char* replaceValue,
											int color, bool bBorder, int xOffSet, int yOffSet) {
												// TODO Auto-generated method stub
												TXT_STRUCT *txt = findTxt(name);
												// this.toDrawScreenName=screen.getName();
												if (txt != NULL) {
													txt->xLoc += xOffSet;
													txt->yLoc += yOffSet;
													char* oldValue = txt->replaceValue;
													txt->replaceValue = replaceValue;
													txt->boder = bBorder;
													int oldColor = txt->rgb;
													txt->rgb = color;
													txt->draw(c);
													// drawTextBig(txt);
													txt->rgb = oldColor;
													txt->replaceValue = oldValue;
													txt->xLoc -= xOffSet;
													txt->yLoc -= yOffSet;
												}
												// this.toDrawScreenName=NULL;
}

void BaseStateEventItemV2::drawTextReplace(QPainter *c, char* name, char* replaceValue,
										   bool bBorder, int xOffSet, int yOffSet) {
											   // TODO Auto-generated method stub
											   TXT_STRUCT *txt = findTxt(name);
											   // this.toDrawScreenName=screen.getName();
											   if (txt != NULL) {
												   txt->xLoc += xOffSet;
												   txt->yLoc += yOffSet;
												   char* oldValue = txt->replaceValue;
												   txt->replaceValue = replaceValue;
												   txt->boder = bBorder;
												   // int oldColor = txt->rgb;
												   // txt->rgb = color;
												   txt->draw(c);
												   // drawTextBig(txt);
												   // txt->rgb = oldColor;
												   txt->replaceValue = oldValue;
												   txt->xLoc -= xOffSet;
												   txt->yLoc -= yOffSet;
											   }
											   // this.toDrawScreenName=NULL;
}

void BaseStateEventItemV2::drawTextReplace(QPainter *c, char* name, char* replaceValue) {
	drawTextReplace(c, name, replaceValue, false, 0, 0);
}

void BaseStateEventItemV2::drawTextReplaceNotNull(QPainter * c, char* name,
												  char* replaceValue, bool bBorder, int xOffSet, int yOffSet) {
													  if (replaceValue == NULL) {
														  return;
													  }
													  drawTextReplace(c, name, replaceValue, bBorder, xOffSet, yOffSet);
}

void BaseStateEventItemV2::drawTextReplace(QPainter *c, char* name, char* replaceValue,
										   int color, bool bBorder) {
											   // TODO Auto-generated method stub
											   TXT_STRUCT *txt = findTxt(name);
											   // this.toDrawScreenName=screen.getName();
											   if (txt != NULL) {
												   // txt->xLoc+=xOffSet;
												   // txt->yLoc+=yOffSet;
												   char* oldValue = txt->replaceValue;
												   txt->replaceValue = replaceValue;
												   txt->boder = bBorder;
												   int oldColor = txt->rgb;
												   txt->rgb = color;
												   txt->draw(c);
												   // drawTextBig(txt);
												   txt->rgb = oldColor;
												   txt->replaceValue = oldValue;
												   // txt->xLoc-=xOffSet;
												   // txt->yLoc-=yOffSet;
											   }
}

void BaseStateEventItemV2::drawTextReplace(QPainter *c, char* name, char* replaceValue,
										   int color, int xOffSet, int yOffSet) {
											   // TODO Auto-generated method stub
											   TXT_STRUCT *txt = findTxt(name);
											   // this.toDrawScreenName=screen.getName();
											   if (txt != NULL) {
												   txt->xLoc += xOffSet;
												   txt->yLoc += yOffSet;
												   char* oldValue = txt->replaceValue;
												   txt->replaceValue = replaceValue;
												   // txt->boder = bBorder;
												   int oldColor = txt->rgb;
												   txt->rgb = color;
												   txt->draw(c);
												   // drawTextBig(txt);
												   txt->rgb = oldColor;
												   txt->replaceValue = oldValue;
												   txt->xLoc -= xOffSet;
												   txt->yLoc -= yOffSet;
											   }

}

void BaseStateEventItemV2::drawPicProcessH(QPainter * c, char* name, int value, int max) {
	// TODO Auto-generated method stub
	// void drawPicProcessV(Canvas c, char* name, int value, int
	// max) {
	// TODO Auto-generated method stub
	// CLEAR ALL BAR DATA
	PNG_STRUCT *png = findPng(name);
	//png.drawPicProcessH(c, value, max);
	// }
}

void BaseStateEventItemV2::setAllTextShowMiddle() {
	// TODO Auto-generated method stub
	for (int i = 0; i < getTextLength(); i++) {
		txtStruct[i].layOutMode = 2;
	}
}

void BaseStateEventItemV2::drawPic(QPainter * c, char* string) {
	// TODO Auto-generated method stub
	PNG_STRUCT *png = findPng(string);
	if (png == NULL)
		return;
	png->draw(c);
}

PNG_STRUCT BaseStateEventItemV2::getDlgBack() {
	// TODO Auto-generated method stub
	return pnStructList[0];
}

void BaseStateEventItemV2::setAllTextShowRight() {
	// TODO Auto-generated method stub
	for (int i = 0; i < getTextLength(); i++) {
		txtStruct[i].layOutMode = 1;
	}
}

void BaseStateEventItemV2::drawPic(QPainter * c, PNG_STRUCT*png, int xVal, int yVal) {
	// TODO Auto-generated method stub
	if (png == NULL)
		return;
	int x = png->xLoc;
	int y = png->yLoc;
	png->xLoc = xVal;
	png->yLoc = yVal;
	png->draw(c);
	png->xLoc = x;
	png->yLoc = y;
}

void BaseStateEventItemV2::setAllTextShowLeft() {
	// TODO Auto-generated method stub
	for (int i = 0; i < getTextLength(); i++) {
		txtStruct[i].layOutMode = 0;
	}
}

void BaseStateEventItemV2::setThisUiIsNotMain() {
	// TODO Auto-generated method stub
	for (int i = 0; i < getPngLength(); i++) {
		//pnStructList[i].setBeIsMainUiButton(false);
	}
}


//virtual char *getScreenName(){ return "";};
void BaseStateEventItemV2::drawBackGround(QPainter *qp){
	if(backGroundImage==NULL){
		ZString path("G:\\A7_QT_FROM_WINCE\\WORK_DIR\\png_resource\\img\\back_groud\\auto_image_back_ground_");
		path+=getScreenName();
		path+=".png";
		backGroundImage=new QImage;
		char *pathDir=path;
		if(! (backGroundImage->load(pathDir) ) ) //加载图像
		{
			delete backGroundImage;
			backGroundImage=NULL;
			return;
		}
	}
	if(qp!=NULL){
		QRectF qr(0,0,1024,600);
		qp->drawImage(qr,*backGroundImage,qr);
	}
}


void BaseStateEventItemV2::drawTextInBox(QPainter *qp,char *data,int fontSize,char *idName,COLORREF rgb,int yAddjust){
	PNG_STRUCT *png=findPng(idName);
	if(png==NULL){
		return;
	}
	if(png->width==0){
		//png->loadHeader();
	}
	TXT_STRUCT txt;
	txt.name=data;
	txt.xLoc=png->xLoc;
	txt.yLoc=png->yLoc+yAddjust;
	txt.width=png->width;
	txt.height=png->height;
	txt.fontSize=fontSize;
	txt.rgb=rgb;
	txt.layOutMode=MIDDLE;
	txt.draw(qp);
}
extern QMainWindow *qmw;
PaintedWidget *BaseStateEventItemV2::getPaintedWidget(){
	if(pw==NULL){
		pw=new PaintedWidget(this);
	}
	return pw;
}
void  BaseStateEventItemV2::hide(){
	for(int i=0;i<listList.size();i++){
		listList[i]->hide();
	}
	getPaintedWidget()->hide();
}
void  BaseStateEventItemV2::show(){
	getPaintedWidget()->setParent(qmw);
	getPaintedWidget()->show();
}





void setStype(QListView* listView){
	listView->setStyleSheet("QScrollBar:vertical"
		"{"
		"width:40px;"
		"background:rgba(0,0,0,0%);"
		"margin:0px,0px,0px,0px;"
		"padding-top:40px;"
		"padding-bottom:40px;"
		"}"
		"QScrollBar::handle:vertical{"
		"border-image: url(/A7_QT_FROM_WINCE/WORK_DIR/png_resource/img/public/loc_1.png);"
		"min-height:38px;"
		"}"
		"QScrollBar::add-line:vertical"
		"{"
		"height:36px;width:36px;"
		"border-image:url(/A7_QT_FROM_WINCE/WORK_DIR/png_resource/img/radio/list/down.png);"
		"subcontrol-position:bottom;"
		"}"
		"QScrollBar::sub-line:vertical"
		"{"
		"height:36px;width:36px;"
		"border-image:url(/A7_QT_FROM_WINCE/WORK_DIR/png_resource/img/radio/list/up.png);"
		"subcontrol-position:top;"
		"}"
		"QScrollBar::add-line:vertical:hover"
		"{"
		"height:36px;width:36px;"
		"border-image:url(/A7_QT_FROM_WINCE/WORK_DIR/png_resource/img/radio/list/up.png);"
		"subcontrol-position:bottom;"
		"}"
		"QScrollBar::sub-line:vertical:hover"
		"{"
		"height:36px;width:36px;"
		"border-image:url(/A7_QT_FROM_WINCE/WORK_DIR/png_resource/img/radio/list/down.png);"
		"subcontrol-position:top;"
		"}"
		"QScrollBar::add-page:vertical,QScrollBar::sub-page:vertical"
		"{"
		"background:rgba(0,0,0,0);"
		"border-radius:0px;"
		"}"
		"QListView{"
		"border-left: 0px solid gray;"
		"border-right: 0px solid gray;"
		"border-top: 0px solid gray;"
		"border-bottom: 0px solid gray;"
		"outline:0px;"
		"background-color: transparent;"
		"color:#FFFFFF;border-width:0;"
		"}"
		"QListView::item:selected {"
		//"border: 1px solid #6a6ea9;"
		"}"
		"QListView::item:selected:!active {"
		"background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
		"stop: 0 #ABAFE5, stop: 1 #8588B2);"
		"color:#FFFFFF;border-width:0;"
		"}"
		"QListView::item:selected:active {"
		"border-image:url(/A7_QT_FROM_WINCE/WORK_DIR/png_resource/img/public/c6/cl_circle6_4.png);"
		"color: red"
		//"     background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
		//"                                 stop: 0 #6a6ea9, stop: 1 #888dd9);"
		"}"
		);






}

QListViewMy*   BaseStateEventItemV2::makeListView(){
	PaintedWidget *pwThis=getPaintedWidget();
	QListViewMy*listView = new QListViewMy(pwThis);  
	///////////!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
	////			
	//////
	/////		需要验证 Linux 下是否能够支持 全屏滑动问题，如果不能；需要做一个假的。
	//////
	/////////
	////////
	/////////
	QStandardItemModel*standardItemModel = new QStandardItemModel(pwThis);  
	listView->standardItemModel=standardItemModel;
	QStringList strList; 
	const char * str = "我是汉字";
	QTextCodec *t=QTextCodec::codecForName("gb2312");
	QString a= t->toUnicode(str);
	strList.append(a);  
	strList.append("string1");  
	//strList.append(QTextCodec::toUnicode(str));  
	strList.append("string3");  
	strList.append("string4");  
	strList.append("string5");  
	strList.append("string6");  
	strList.append("string7");  
	strList << "string8";  
	strList += "string9";  
	for(int i=0;i<100;i++){
		QString str;
		str="ABC";
		str+=i;
		strList.append(str);
	}
	int nCount = strList.size();  
	QFont list_font;
	list_font.setPointSize(20);
	list_font.setBold(true);
	list_font.setWeight(50);
	listView->setFont(list_font);
	for(int i = 0; i < nCount; i++)  
	{  
		QString string = static_cast<QString>(strList.at(i));  
		QStandardItem *item = new QStandardItem(string);  
		standardItemModel->appendRow(item);  
	}  
	listView->setModel(standardItemModel);  
	listView->setFixedSize(200,300);  
	listView->setFixedSize(200,300);  
	listView->move(500,100);
	setStype(listView);

	pwThis->connect(listView,SIGNAL(clicked(QModelIndex)),pwThis,SLOT(itemClicked(QModelIndex)));  
	//	Button *pointButton = createButton(tr(".XXXX"), SLOT(pointClicked()));
	//	pointButton->show();
	addToHideComponet(listView);
	return listView;
}
