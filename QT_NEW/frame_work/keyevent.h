#ifndef KEY_EVENT_H
#define KEY_EVENT_H
// KeyEvent.h
#include "RemoteKey.h"
#include "keyValue.h"


bool isKeyEvent(LPARAM l);
LPARAM tranlsate(unsigned char key0);


#define NULL_KEY			0x001ff
#define UNKOWN_KEY			0x001fe
#define FANGXPAN_BASE		0x08000
#define FANGXPAN_MIN		0x08000
#define FANGXPAN_MAX		0x081FF
#define CAN_KEY_BASE		0x08200
#define CAN_KEY_MAX			0x08300

#define FXP_TRASLATE_KEY			0x04000
#define IS_NULL_KEY(x)		(x==NULL_KEY)		
#define IS_FXP_KEY(x)		((x&0xFFFF)>=FANGXPAN_MIN&&(x&0xFFFF)<=FANGXPAN_MAX)
LPARAM tranlsate(unsigned char key0);

#define FXP_RESET_VALUE		(0|FXP_TRASLATE_KEY)
#define	FXP_QUEREN_VALUE	(1|FXP_TRASLATE_KEY)
#define	FXP_CLEAR_VALUE		(2|FXP_TRASLATE_KEY)
#define	FXP_MUTE_VALUE		(3|FXP_TRASLATE_KEY)
#define	FXP_POWER_VALUE		(4|FXP_TRASLATE_KEY)
#define	FXP_VOL_DOWN_VALUE	(5|FXP_TRASLATE_KEY)
#define	FXP_VOL_UP_VALUE	(6|FXP_TRASLATE_KEY)
#define	FXP_POREV_VALUE		(7|FXP_TRASLATE_KEY)
#define	FXP_NEXT_VALUE		(8|FXP_TRASLATE_KEY)
#define	FXP_MODE_VALUE		(9|FXP_TRASLATE_KEY)
#define	FXP_RADIO_VALUE		(10|FXP_TRASLATE_KEY)
#define	FXP_GPS_VALUE		(11|FXP_TRASLATE_KEY)
#define	FXP_DVD_VALUE		(12|FXP_TRASLATE_KEY)
#define	FXP_CALL_TEL_VALUE	(13|FXP_TRASLATE_KEY)
#define	FXP_HUGE_UP_VALUE	(14|FXP_TRASLATE_KEY)
LPARAM getFxpKey(LPARAM lParamFxpKey);
int getSerialNo();


#define IS_IN_FXP_SHE_ZHI		(actScrnNo==SCRN_方向盘设置)


#define SCREEN_6_2

#ifdef SCREEN_6_2

// POWER,SRC 0K
// VOL+      33K
// VOL-      12K
// MUTE      20K
// GPS       2K7
// EJECT     6K8
//	电阻	  KEY 上拉	理论值	理论值	实际值	实际分界值	程序分界值
// POWER,SRC 1	0K		0		22		0 		0 														
// GPS       2	2K7	2.7	22	28 		14 		29 		15 		14 
// EJECT     3	6K8	6.8	22	60 		44 		64 		47 		45 
// VOL-      4	12K	12	22	90 		75 		97 		81 		78 
// MUTE      5	20K	20	22	121 	106 	130 	114 	110 
// VOL+      6	33K	33	22	153 	137 	163 	147 	142 


/// VOL+	93		174		1	5	和众宏公用面板
/// VOL-	78		85.5	1	4
/// GPS		39		58.5	1	3
/// EJECT	28		33.5	1	2
/// MUTE	11		19.5	1	1
/// SRC		0		5.5		1	0


	//#define VOLUME_PLUS		4

/*
	#define KEY_BASE0		1	
	#define GPS				1
	#define EJECT			2
	#define POWER_SOURCE	3
	#define MUTE			4
	#define VOL_PLUS		5
	#define VOL_SUB			6
	#define VOL_LEFT		14
	#define VOL_RIGHT		16
*/
/*
	#define APS				37
	#define EQ2				38	
	#define TURN			39	
	#define KEY5			30
	#define KEY_BASE1		31	
	#define GPS_x			32	
	#define VOLUME			33
	#define	RESET			34

	#define TURN_LEFT	17
	#define TURN_RIGHT	18
	*/
#else
	#define KEY_BASE0		1	
	#define EJECT			1
	#define APS				2
	#define EQ2				3	
	#define TURN			4	
	#define KEY5			5
	#define KEY_BASE1		6	
	#define POWER_SOURCE	6
	#define MUTE			7	
	#define GPS_x			8	
	#define VOLUME			9
	#define GPS				10
	#define	RESET			11

	#define VOL_LEFT	15
	#define VOL_RIGHT	16
	#define TURN_LEFT	17
	#define TURN_RIGHT	18
#endif

#include "keydefine.h"
#define KEY_PRESSED		0x40
#define KEY_PRESSING	0x80
#define KEY_RELEASE		0xC0


extern volatile long  vTimmerCounter;

bool dealKeyEvent(LPARAM lParam);
void dealKeyEventInBack(LPARAM lParam);
int dealAccOnOff(LPARAM lParam);

#endif
