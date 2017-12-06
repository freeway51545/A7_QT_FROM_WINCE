#include "fix\MAIN_EventV1.h"
#include "fix\MAIN2_EventV1.h"

 static MAIN_EventV1 MAIN_inst ;
 static MAIN2_EventV1 MAIN2_inst ;

	 void main_init() {
		addScren(SCRN2_MAIN,MAIN_inst);
		addScren(SCRN2_MAIN2,MAIN2_inst);
	}
