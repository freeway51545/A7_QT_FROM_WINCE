
#include "PUBLIC_EventV1.h"
	 PUBLIC_EventV1::PUBLIC_EventV1(){
		char *actionList[]={
		NULL};
		setActions(actionList);
		initScreen();	
	};
	void PUBLIC_EventV1:: dispatch(MSG_ZHW&msg){
		if(msg.msgID==MSG_ENTER_SCRN&&msg.actionName==""){
			_F_INIT_FUN(msg);
			comsumer(msg);return;
		}
		if(msg.msgID==_TIMMER_10PS&&msg.actionName==""){
			_F_UPDATE_TIMMER(msg);
			comsumer(msg);
			return;
			}
	}
