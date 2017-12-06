#include "fix\videolist_EventV1.h"

 static videolist_EventV1 videolist_inst ;

	 void videolist_init() {
		addScren(SCRN2_videolist,videolist_inst);
	}
