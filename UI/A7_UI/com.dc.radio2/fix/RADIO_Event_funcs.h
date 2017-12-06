
#include "fix\RADIO_EventV1.h"

class RADIO_Event_funcs :: public RADIO_EventV1 {
	
	public void _F_INIT_FUN(MSG_ZHW msg) {
		// TODO Auto-generated method stub
		BackUtil.showBackGround(this.getMainActivity(), IScreenConst.backList,IScreenConst.back_id_radio);
	}

	
	public void _F_UPDATE_TIMMER(MSG_ZHW msg) {
		// TODO Auto-generated method stub
	}
	public  void _F_Play(MSG_ZHW msg){
	};
	public  void _F_DOWN(MSG_ZHW msg){
	};
	public  void _F_SCAN(MSG_ZHW msg){
	};
	public  void _F_ADJUST(MSG_ZHW msg){
	};
	public  void _F_SAVE(MSG_ZHW msg){
	};
	public  void _F_UP(MSG_ZHW msg){
	};
	public  void _F_LEFT(MSG_ZHW msg){
	};
	public  void _F_RIGHT(MSG_ZHW msg){
	};
	public  void _F_LIST(MSG_ZHW msg){
	};
	public  void _F_EQ(MSG_ZHW msg){
	};

}
