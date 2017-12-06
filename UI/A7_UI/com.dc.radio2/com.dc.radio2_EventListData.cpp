#include "fix\RADIO_EventV1.h"

 static RADIO_EventV1 RADIO_inst ;

	 void radio2_init() {
		addScren(SCRN2_RADIO,RADIO_inst);
	}
