#ifndef KEY_DEF
#define KEY_DEF

#include "pubtype.h"

#define LIGHT_SCREEN_IRDA			0x10095
#define DVD_RESET_ED				0x10096
#define	MAIN_ACC_OFF_SLEEP			0x10097
#define MAIN_ACC_ON_STATE_OK		0x10098
#define	MAIN_ACC_OFF_RESET			0x10099
#define QUERY_STATE					0x10100
#define SET_MATCH_TYPE				0x10101
#define DARK_SCREEN_IRDA			0x10102
#define SET_MATCH_TYPE_DATA1		0x11111
#define CMD_REGISTER_ME				0x12000
#define CMD_REGISTER_ME_LONG		0x12001
#define QUERY_RESULT_STATE			0x12002


#define ACC_UNKOWN			0
#define ACC_OFF_NEED_RESET	1
#define ACC_OFF_CAN_SLEEP	2

//void addKeyEvent(BYTE b);
void addKeyEventLong(DWORD b);

#endif