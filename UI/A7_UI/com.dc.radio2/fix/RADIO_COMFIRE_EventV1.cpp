
#include "RADIO_COMFIRE_EventV1.h"
	 RADIO_COMFIRE_EventV1::RADIO_COMFIRE_EventV1(){
		char *actionList[]={
		"AGREE",
		"REFUSE",
		NULL};
		setActions(actionList);
		initScreen();	
	};
	void RADIO_COMFIRE_EventV1:: dispatch(MSG_ZHW&msg){
		if(msg.actionName=="AGREE"&&msg.actionType==NULL_RELEASE){
			_F_AGREE(msg);
			comsumer(msg);;
		}
		if(msg.actionName=="REFUSE"&&msg.actionType==NULL_RELEASE){
			_F_REFUSE(msg);
			comsumer(msg);;
		}
	}
