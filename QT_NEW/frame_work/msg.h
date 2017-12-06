
#ifndef _ZHW_BASE_MSG_TT
#define _ZHW_BASE_MSG_TT
//#include "basetsd.h"
class MSG_ZHW{
public:
	ZString actionName;
	WPARAM msgID;
	//int serialNo;
	//bool noSendRedrawMessageInMouseMove;
	MSG_ZHW(){
//				actionName="";
				msgID=0;
	};
};
#define MB(X) 
//MessageBox(0,_T(X),L"MSG",0)

#define NULL_MSG            900 
#define NULL_RELEASE        901 
#define NULL_PRESSING       902 
#define NULL_PRESSED        903 
#define NULL_ENTER	        904 
#define NULL_LEAVE		      905 

#define _TIMMER_10PS			1000
#define _TIMMER_OVER			1001
#define MSG_FoundValidChannel	1002
#define MSG_SEARCH_OVER			1003
#define	独占MouseMove			1004
#define 独占MouseUp				1005
#define	MSG_SET_OK				1006
#define MSG_ENTER_STATE			1007
#define MSG_SELECT_UP			1008
#define	MSG_AUTO_SCROLL			1009
#define MSG_SCROLL_STOP			1010
#define MSG_ENTER_SCRN			1011
#define MSG_RECORD_OVER			1012
#define MSG_GAME_OVER			1013
#define MSG_DIR_LIST			1014
#define MSG_FILE_LIST			1015
#define MSG_SONG_TXT			1016
#define MSG_SONG_TITLE			1017
#define MSG_REDRAW				1018
#define MSG_KEY_EVENT			1019
#define MSG_EXCHANG_SCRN		1020
#define MSG_EXCHANG_STATE		1021
#define MSG_TURN_UP				1023
#define MSG_TURN_DOWN			1024
#define MSG_DIR_LIST_NEW		1025
#define MSG_FILE_LIST_NEW		1026
#define MSG_GET_TEL_NO			1027
#define MSG_BT_STATE_CHANGED	1028
#define MSG_TURN_SELECT			1029
#define MSG_SONG_NAME_RE		1030
#define MSG_DIR_CHANGED			1031
#define MSG_MP3_INFOR			1032
#define MSG_PLAY_NO_CHANGED		1033
#define MSG_USB_PLUG_IN			1034
#define MSG_USB_DRAG_OUT		1035
#define MSG_SD_PLUG_IN			1036
#define MSG_SD_DRAG_OUT			1037
#define MSG_OUT_DVD_DOOR		1038
#define MSG_IIS_ACTIVE_ON		1039
#define MSG_IIS_ACTIVE_OFF		1040
#define MSG_INIT_COPY_DATA		1041
#define MSG_CHANGE_TO_WINCE		1042
#define MSG_CHANGE_TO_CONTROL	1043
#define MSG_SCREEN_右滑动		1044
#define MSG_SCREEN_左滑动		1045
#define MSG_DISK_PLUG_IN		1046
#define MSG_RE_ENTER_SCRN		1047
#define MSG_LONG_PRESSED_MESSAGE	1048
#define MSG_MOVE_PRESSED_MESSAGE	1049
#define MSG_POWER_ON			1050
#define MSG_FILE_PLAY_OVER		1051
#define MSG_FULL_SCREEN_CAMERA	1052
#define MSG_ENTER_BACK		1056
#define MSG_CLOSE_BACK		1057
#define MSG_DVD_STATE		1058
#define MSG_DVD_FIRST_ENTER	1059
#define MSG_ENTERED_NEW		1060
#define MSG_OPEN_CAMERA_WINDOW	1061
#define MSG_CLOSE_CAMERA_WINDOW	1062
#define MSG_CLEAR_CAMERA_WIN_BUFFER	1063
#define MSG_CARD_REMOVED			1064
#define MSG_CARD_INSERTED			1065
#define MSG_POWER_OFF_EVETN			1066
#define MSG_IIS_SOURCE_CHANGED		1067
#define MSG_REDRAW_FORCE			1068
#define MSG_SHOW_ZHW_CONTRL			1069
#define MSG_DISABLE_SHOW_CHEBIAO	1070
#define MSG_UNLOCK_SCREEN_LOCK		1080
#define MSG_LOCK_SCREEN				1090
#define MSG_SD_CARD_HAVE_EEROR		1091
#define MSG_DRAW_BRIGHT_VOL			1092
#define MSG_DRAW_MUTE				1093
#define MSG_draw空调Win				1094
#define MSG_draw倒车Win				1095
#define MSG_SEND_MUTE_CMD			1096
#define MSG_RESTORE_WIN0_PHR		1097

//
#define MSG_REVERSE_OPEN		    1098
#define MSG_REVERSE_CLOSE		    1099
#define MSG_UPDATE_OVERLAY		    1100
#define MSG_CLOSE_USB_AV		    1101
#define MSG_INIT_AVIN			    1102
#define MSG_PHONE_PLUG_IN			1103
#define MSG_PHONE_PLUG_OUT			1104


#define MSG_RESTOP_AUDIO			1105
#define MSG_FAKE_POWER				1106

#define MSG_EXCHANGED_VIDO			1110

#define MSG_EXECUTE_CMD				 1111
#define MSG_EJECT_STOP_DVP_TOMAIN	 1112
#define MSG_TO_MCU_UPDATE			 1113
#define MSG_RECOVER_MEDIA_PLAY	     1114
#define MSG_READ_DISC_EXCEPTION      1115
#define MSG_ILL_CHANGE_SCREEN        1116
#define MSG_TO_RESET_MCU			 1117
#define MSG_CAN_TO_SETUP			 1118
#define MSG_CAN_TO_SYSINFO			 1119
#define MSG_RECOVER_DVD_PLAY		 1120
#define MSG_CAN_MEDIA_PLAY			 1121
#define MSG_SPEED_CHANGE			 1122
#define MSG_BTDVENAME_INIT			 1123
#define MSG_CHECK_MCU_UPDATE         1124
#define MSG_RE_INIT_AVIN			 1125

#define MSG_LOAD_START				 1126
#define MSG_LOAD_COMPLETE			 1127

#define MSG_START_MCU_UPDATE         1128



//#define MSG_NEW_RSS_COM				 1200
#define MSG_DRAW_RADARWIN			 1129

#define MSG_UPGRADE_MAP				 1130

#define MSG_SCREEN_FIRST_DRAWED	     1131
#define MSG_RADIO_PLAY_FIRST	     1132
#define MSG_MEDIA_FIRST_SCREEN	     1133

#define MSG_BTPAIROPEN_INIT			 1134


#define MSG_BTDVENAMEPASS_INIT			 1135
#define MSG_BTPAIROPENJUDGE_INIT			 1136
#define MSG_BTSEARCH_MSG			 1137


void PostMessageZhw(WPARAM msgId,LPARAM lparam=0);
void ExecuteMessageZhw(WPARAM msgId,LPARAM lparam=0);





#define V_DSP_NONE		0
#define V_DSP_JASS		1
#define V_DSP_CLASS		2
#define V_DSP_ROCK		3
#define V_DSP_FLAT		4
#define	V_DSP_POP		5



//#define	MAX_BRIGHT	20
#define	MAX_BRIGHT	17

void reDrawAtOnce();
//void mute();
void turnVolume();
void setupBright();
void upBright();
void downBright();
void setRedrawFlag();
#define RE_DRAW			setRedrawFlag()
//#define RE_DRAW_AT_ONCE			ExecuteMessageZhw(MSG_REDRAW)
#define RE_DRAW_AT_ONCE			reDrawAtOnce()
//PostMessageZhw(MSG_REDRAW)
//#define DRAW_AT_ONCE	ExecuteMessageZhw(MSG_REDRAW)

#define CH_RADIO	2
#define CH_DVD		3
#define CH_IPOD		4
#define CH_TV		5
#define CH_AUX		6
#define CH_CDC		7
#define CH_BT		8
#define CH_MP5		9
#define CH_IIS		10
#define CH_GPS		1

ZString&getMainScreen();
ZString&getSCRN_参数设置();
ZString&show多国语言();


#define CMD_GO						10
#define CMD_WRITE_DATA		11
#define CMD_READ_DATA			12
#define CMD_CHECK_SUM			13
#define CMD_QUERY_PROGRAM	14
#define CMD_RESTART				15
#define CMD_CHECK_CAN_RUN	16

#define RS_UNKOWN					0
#define RS_OK							1
#define RS_FALSE					2
#define RS_DATA						3
#define RS_BOOT_LODER			15
#define RS_PROGRAM				16
#define RS_NEED_REPROGRAM	17
#define RS_PROGRAM_COD_OK	18
#define RS_CHECK_COD_OK		19
#define RS_UNKOWN_CMD			30
#define RS_GOT_DATA				0X8989
#define RS_GOT_DATA_FALSE	0X8990

#define CLEAR_WATCH_DOG	IWDG_KR=0xAA;

//////////////////////////////////////////////////////////////////////
//0X80 ARM->MCU
#define CMD_HANDSHAKE		0XA0
#define CMD_SET_BAUDRATE	0XA1
#define CMD_INIT_REQUEST	0XA2
#define CMD_REQUEST_MCU		0XA4
#define CMD_REPORT_MCU		0XA5
#define CMD_SRC_CHANGE		0XA7
#define CMD_REQUEST_VOL		0XA9
#define CMD_SET_VOL			0XAA
#define CMD_REQUEST_EQ		0XAB
#define CMD_SET_EQ			0XAC
#define CMD_CMD_TO_MCU		0XB0
#define CMD_XY_TO_MCU		0XB1
#define CMD_REQUEST_RADIO	0XB3
#define CMD_REQUEST_CDC		0XB5
#define CMD_REQUEST_SYS		0XB7
#define CMD_SET_SYS			0XB8
#define CMD_REQUEST_SWC		0XBA
#define CMD_SET_SWC			0XBC
#define CMD_FXP_LEARN		0XBD

#define CMD_FOUND_ONE_PL	0xBE

#define CMD_REQUEST_MCU_VER	0XC3
#define CMD_REPORT_UPDATE	0XC4
#define CMD_PROG_DATA		0XC6

//0X81	MCU->ARM
#define CMD_MCU_REPORT_STA			0XA6
#define CMD_MCU_SRC_CHANGE			0XA8
#define CMD_MCU_VOL_CHANGE			0XAD
#define CMD_MCU_EQ_CHANGE			0XAE
#define CMD_MCU_CMD					0XB2
#define CMD_MCU_REPORT_RADIO		0XB4
#define CMD_MCU_REPORT_CDC			0XB6
#define CMD_MCU_REPORT_SYS			0XB9
#define CMD_MCU_REPORT_SWC			0XBB
#define CMD_MCU_REPORT_SAMPLE		0XBE
#define CMD_MCU_REQUEST_SRC			0XC0
#define CMD_MCU_REPORT_STA2			0XC1
#define CMD_MCU_REPORT_ACC			0XC2
#define CMD_MCU_REQUEST_PROG_DATA	0XC5

#define CAN_MCU_INFO				0XD1
#define CAN_MCU_RETURN				0XD2

#define MCU_SPEED_AND_TEMP	 0XD5

#define MCU_STRING_CMD				0XE0
#define MCU_DATA_CMD                0XE1

#define MCU_ARM_VOL			0XEA//ARM通知MCU当前音量


#define ERR_SUCCESS			0x00  //成功 
#define ERR_FAIL			0x01  //失败 
#define ERR_UNSUPPORTEDBAUDRATE  0x02  //波特率不支持 
#define ERR_INVALIDTIME		0x03  //非法时间 
#define ERR_CLOCKHWERR		0x04  //时钟硬件错误
#define ERR_UNSUPPORTEDCMD  0xFF  //不支持该命令 


#define   SOURCE_OFF  0x00 
#define   SOURCE_DISC  0x01 
#define   SOURCE_SD  0x02 
#define   SOURCE_USB  0x03 
#define   SOURCE_Radio  0x04 
#define   SOURCE_TV  0x05 
#define   SOURCE_CMMB  0x06 
#define   SOURCE_DVB_T  0x07 
#define   SOURCE_AUX1  0x08 
#define   SOURCE_ AUX2  0x09 
#define   SOURCE_CDC  0x0A 
#define   SOURCE_BT  0x0B 
#define   SOURCE_Camera  0x0C 
#define   SOURCE_Navigation  0x0D 
#define   SOURCE_Main           0x0F 
#define   SOURCE_IPOD           0x10 
#define   SOURCE_McuTV           0x11 
#define   SOURCE_ARM_UI_SRC           0x12 
#define   SOURCE_IPOD_USB  0x13 
#define   SOURCE_USB_REAR  0x14 
#define   SOURCE_ISDBT  0x15 
#define   SOURCE_ATV           0x16 
#define   SOURCE_DRIVE_RECORD           0X17
/*2015-5-25*/
#define   SOURCE_DISC_LOAD	0X18
#define   SOURCE_SD_LOAD	0X19
#define   SOURCE_USB_LOAD   0X1A

#define   SOURCE_MCU_STANDBY           0xFF

#define K_POWER  0x01   
#define K_MUTE  0x02    //静音
#define K_EQ  0x03    //音效切换
#define K_CLOCK  0xC5
#define K_VOL_UP  0x04   
#define K_VOL_DN  0x05   
#define K_PHONE_ON  0x06    //蓝牙电话接听
#define K_PHONE_OFF  0x07   // 蓝牙电话挂断
#define K_SOURCE_MODE  0x08   // 各源模式之间轮流循环切换
#define K_SOURCE_HOME  0X09  	//HOME按键  切换到主界面
#define K_HOME_FRONTSRC  0x0A 	//在HOME界面和当前媒体源之间切换

#define K_EJECT  0x1D


#define K_0  0x20    //0
#define K_1  0x21    //1
#define K_2  0x22    //2/
#define K_3  0x23    //3
#define K_4  0x24    //4
#define K_5  0x25    //5
#define K_6  0x26    //6
#define K_7  0x27    //7
#define K_8  0x28    //8
#define K_9  0x29    //9
#define K_UP  0x2A    //UP
#define K_DOWN  0x2B    //DOWN
#define K_LEFT  0x2C    //LEFT
#define K_RIGHT  0x2D    //RIGHT
#define K_ENTER  0x2E		//BYTE0: 0表示遥控上此按键不带复合
												//功能或者其他按键值(比如T_PLAY  0x71
												//则没有GOTO显示时此按键代表播放键值)
												//Enter、五位键中的OK
#define K_RETURN  0x2F   // BACK
#define K_STAR  0x30    //*号键
#define K_NUMBER  0x31    //＃号键
#define K_CLEAR  0x32    //Clea
#define K_NAVI  	0x43  

#define K_MUSIC  0x40    //MUSIC
#define K_PHOTO  0x41    //PHOTO
#define K_MP5  0x42    //VIDEO
#define K_NAVI  0x43    //NAVI
#define K_TUNER  0x44 //RADIO(ARM 会判断当前状态进行不同动作，不在RADIO
											//界面时切换到RADIO界面，在RADIO界面时切换波段)
#define K_DVD  0x45    //DVD
#define K_BLUETOOTH  0x46    //BlueTooth
#define K_SETTING  0X47 
#define K_TV  0x48    //快捷键进入电视
#define K_USB  0x49   // 快捷键进入USB源
#define K_SD_CARD  0x4A   // 快捷键进入SD卡源
#define K_TOUCH_MENU   0X4F    //Touch calibrate men

#define T_RADIO_BAND  0x50   
#define T_RADIO_TUNE_UP  0x51   
#define T_RADIO_TUNE_DOWN  0x52   
#define T_RADIO_SEEK_UP  0x53   
#define T_RADIO_SEEK_DOWN  0x54   
#define T_RADIO_AS  0x55	//BYTE0: 0表示自动搜索并存台
													//1示进自动搜索预览
													//(搜索到可用电台听5秒， 再 搜
													//索下一个电台，但不存台)
													//(Auto Scan)
#define T_RADIO_PS  0x56   
#define T_RADIO_LOC  0x57    //远程/本地
#define T_RADIO_TA  0x58 			////Traffic Announcement //(RDS information)
#define T_RADIO_PTY  0x59 	////Program TYpe (RDS information)
#define T_RADIO_AF  0x5A //Automatic Follow (RDS information)
#define T_RADIO_REG  0x5B   
#define T_RADIO_CT  0x5C   
#define T_RADIO_EON  0x5D    //增强其他网络信息(RDS)
#define T_RADIO_RDS  0x5E   
#define T_RADIO_RDS_TYPE  0x5F   
#define T_RADIO_FM_FREQ  0x60 	//BYTE0：高位 BYTE1:次高位 BYTE2:次低位 BYTE3:  低位
#define T_RADIO_AM_FREQ  0x61   
#define T_RADIO_PRESET_SAVE  0x62   
#define T_RADIO_PRESET_LOAD  0x63     
#define T_RADIO_PTY_SEEK  0x64   
#define T_RADIO_STERO_STATE_CHANGE 0x65 //收音界面立体声状态状态切换
#define T_RADIO_PRESET_PRE  0x66   // 选中前一个预存电台
#define T_RADIO_PRESET_NEXT  0x67    //选中下一个预存电台
#define T_DVR_CMD  0x68    //DVR_CMD



#define T_STOP  0x70 
#define T_PLAY  0x71	//BYTE0: 0 播放暂停循	环切换，不需要MCU控制，1播放，2暂停	PLAY_PAUSE
#define T_NEXT  0x72   
#define T_PREV  0x73   
#define T_FASTF  0x74   
#define T_FASTB  0x75   
#define T_REPEAT  0x76   
#define T_SHUFFLE  0x77   
#define T_SCAN  0x78   
#define T_A_B  0x79   
#define T_ZOOM  0X7A  //放大缩小循环 
#define T_TITLE  0x7B   
#define T_SUB_T  0x7C   
#define T_PBC  0x7D   
#define T_ANGLE  0x7E    //角度
#define T_STEP  0x7F   
#define T_TRACK  0x80 

#define T_FULL_SCREEN  0x81 	//播放时全屏与非全屏之间切换
#define T_DVD_MENU  0x82    //DVD MENU

#define T_BT_AUDIO_MUTE  0XA0   
#define T_BLACKOUT  0xA1 //白天，黑夜，关闭3种背光模式之间的切换
#define T_NAVI_MUTE  0xA2 //如果导航在前台，导航混音和导航兼听之间切换
#define T_BEEP  0xA3 //按键音,ARM 界面上操作按键时，会发送该按键给MCU
#define T_SELECT  0xA4   
#define T_SETTING_RESET  0xA5 //恢复出厂设置时会发送该按键，如果MCU也需要恢复出厂设置，则动作，否则可不处理
#define T_SEND_WHEEL_STUDY  0xA6//参数BYTE0，代表 当前学习的按键通知MCU当前ARM学习的是界面上第几个按键,
#define T_WHEEL_STUDY_OK  0xA7  //  方向盘学习完成保存
#define T_WHEEL_STUDY_RESET  0xA8 //   方向盘学习复位
#define T_SET_EQ  0xA9 //设置音效快捷键收到此按键
											//，进入音效设置界面
#define T_LOUDNESS	0xAA  //响度设置按键按下此按键开启或关闭响度,开启时默认设置最
													//大的响度，MCU也可以通过参数的第
													//一个字节设置响度的值(0 默认最大)
#define T_SUBWOOFER  0xAB // 重低音按键  重低音开关切换
#define T_IR_GOTO  0xB1   // 遥控按键上的GOTO按键
#define T_KEY_DISP  0xB2   
#define T_REARVIEW  0XB3   // 遥控器后视按键
#define T_MOUSE_POS  0XB4	//High-order word 表示Y坐标，low-order 
													//word 表示X坐标
													//触摸屏坐标
													//按顺序接收p1 p2 p3 p4
													//x = p1 + (p2<<8);
													//y = p3 + (p4<<8);
#define T_CAMERA_RECORD  0XB5	//各参数具体含义请参
															//考注释文档
															//行车记录仪按键
															
#define T_ONSTAR  0xB6  //安吉星按键通知参数第一个字节：
												//0x00:数字0
												//0x01:数字1
												//0x02:数字2
												//0x03:数字3
												//0x04:数字4 
												//0x05:数字5
												//0x06:数字6
												//0x07:数字7
												//0x08:数字8 
												//0x09:数字9
												//0x0a:*
												//0x0b:#
												//0x0c:退出OnStar系统
												//0x0d:开启OnStar系统
												//0x0e:电话接听命令
												//0x0f:电话挂断/拒接命
#define T_KEY_SOFT_POWER_ON    0xB8
#define T_KEY_SOFT_POWER_OFF   0xB7
												
#define K_BACKLIGHT_STATE			0xFC  

#define K_CLOSE_SCREEN_WHEN_ACC	0xC8   //20161008
#define K_OPEN_SCREEN_WHEN_ACC_ON	0xC9
									//第一个字节 0 白天，1 关闭， 2 黑夜
#define K_SAVE_ALL	0xFD
#define K_USER  0xFF
#define K_NONE	0x00

#define WINCE_DESKTOP 0xC2		//2015-1-20

typedef enum{
	SYS_SET_MEPG = 0,
	SYS_SET_BT,
	SYS_SET_TIME,
	SYS_SET_COMMON,
	SYS_SET_VIDEO,
	SYS_SET_RADIO,
	SYS_SET_RDS,
	SYS_SET_AUDIO,
	SYS_SET_REVERSE
}E_SYS_SET_INDEX;

#define RADIO_NULL	0
#define RADIO_SCAN	1
#define RADIO_STORE 2
#define RADIO_PS	3
#define RADIO_SEEK	4


#define ACC_OFF						0X88319931

typedef enum _DSP
{
	EQ_NONE = 0x00,
	EQ_POP,
	EQ_FLAT,
	EQ_ROCK,
	EQ_CLASS,
	EQ_JASS,
}DSP;

#define SOUND_VOL_CHANGE_MASK  0x01
#define SOUND_FAD_CHANGE_MASK  0x02
#define SOUND_BAL_CHANGE_MASK  0x04
#define SOUND_FAD_BAL_CHANGE_MASK  0x06
#define SOUND_MUTE_CHANGE_MASK 0x08
#define SOUND_SHOW_VOL_MASK  	 0x10

#define PLAY_MODE_REPEAT_MASK  0X01
#define PLAY_MODE_INT_MASK     0X02
#define PLAY_MODE_RANDOM_MASK  0X04



#endif




#include "keyevent.h"