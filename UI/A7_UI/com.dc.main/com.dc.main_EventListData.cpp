#include "fix\MAIN_EventV1.h"
#include "fix\MAIN2_EventV1.h"
#include "fix\pubIcon_EventV1.h"

 static MAIN_EventV1 MAIN_inst ;
 static MAIN2_EventV1 MAIN2_inst ;
 static pubIcon_EventV1 pubIcon_inst ;

	 void main_init() {
		addScren(SCRN2_MAIN,MAIN_inst);
		addScren(SCRN2_MAIN2,MAIN2_inst);
		addScren(SCRN2_pubIcon,pubIcon_inst);
	}
