#include "..\list.h"
#include "fix\videolist_EventV1.h"
#include "PaintedWidget.h"
QListViewMy *qlViewMy=NULL;
//@Override
void videolist_EventV1::_F_INIT_FUN(MSG_ZHW&msg) {
	// TODO Auto-generated method stub
	//BackUtil.showBackGround(this.getMainActivity(), IScreenConst.backList,IScreenConst.back_id_videolist);
	//BackUtil.showBackGround(this.getMainActivity(), IScreenConst.backList,IScreenConst.back_id_videolist);
	if(qlViewMy==NULL){
		PNG_STRUCT*png=this->findPng("list");
		qlViewMy=makeListView();
		//png->loadHeader();
		RECT r=png->getRect();
		qlViewMy->setFixedSize(r.right-r.left,r.bottom-r.top);  
		qlViewMy->move(r.left,r.top);
	}
	//qlViewMy->hide();
	//qlViewMy->setParent(getPaintedWidget());
	qlViewMy->show();
}
extern PaintedWidget *pwThis;
//@Override
void videolist_EventV1::_F_UPDATE_TIMMER(MSG_ZHW&msg) {
	// TODO Auto-generated method stub

}

char *  videolist_EventV1::getTitleName(void){
	return "VEDIO_LIST";
}

void videolist_EventV1::drawDynimicQt(class QPainter *){
}

void videolist_EventV1::_F_BACK(class MSG_ZHW &){
	ZString screName2="SCRN2_MAIN";
	TO_SCRN(screName2);
}

void videolist_EventV1::_F_HOME(class MSG_ZHW &){
	ZString screName2="SCRN2_MAIN";
	TO_SCRN(screName2);
}