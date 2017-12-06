#include "fix\EQ_EventV1.h"
#include "fix\BANLANCE_EventV1.h"
#include "fix\VOLUME_EventV1.h"

 static EQ_EventV1 EQ_inst ;
 static BANLANCE_EventV1 BANLANCE_inst ;
 static VOLUME_EventV1 VOLUME_inst ;

	 void f102_eq_init() {
		addScren(SCRN2_EQ,EQ_inst);
		addScren(SCRN2_BANLANCE,BANLANCE_inst);
		addScren(SCRN2_VOLUME,VOLUME_inst);
	}
