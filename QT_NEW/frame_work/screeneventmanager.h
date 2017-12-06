#ifndef ScreenEventManager_h
#define ScreenEventManager_h
#include "msg.h"
#include "BaseStateEventItem.h"
class BaseStateEventItemV2;

class ScreenEventManager{
public:
	BaseStateEventItemV2 *getStateEvent(ZString&n);
	ScreenEventManager();
};

class EventContext{
public:
	QEvent *ev;
	bool eventDealed;
	bool noSendRedrawMessageInMouseMove;
	EventContext(){
		//doButtonPressed=false;
		noSendRedrawMessageInMouseMove=false;
		setBeNeedRedraw(false);
		eventDealed=0;
		ev=0;
		noSendRedrawMessageInMouseMove=false;
	};
	//MSG_ZHW msg;
	void setBeNeedRedraw(bool b);
	bool isBeNeedRedraw(){
		return beNeedRedraw;
	}
private:
	bool beNeedRedraw;
};




ScreenEventManager * getScreenEventManagerInstance();
void activeTraslateMsg(HWND hWnd,UINT message, WPARAM wParam, LPARAM lParam);

void toScreenDir(ZString&screnNo);
#define TO_SCRN(x)		toScreenDir(x);
//#define TO_SCRN(x) PostMessageZhw(MSG_EXCHANG_SCRN,x);
//#define TO_SCRN_EX(x)	toScreenEx(x);
#define TO_SCRN_EX_ASY(x)	toScreenDir(x);
//PostMessageZhw(MSG_EXCHANG_SCRN,x);
void toScreenForce(int x);
//#define TO_SCRN_ST_ASY(x)	PostMessageZhw(MSG_EXCHANG_STATE,x);

void selectScren(ZString no);

#define SCRN_MAIN1		"SCRN_MAIN1"
#define SCRN_SHOW		"SCRN_SHOW"
#define SCRN_VER		"SCRN_VER"
#define SCRN_DATE		"SCRN_DATE"
#define SCRN_EQ			"SCRN_EQ"
#define SCRN_TONE		"SCRN_TONE"
#define SCRN_MANUAL		"SCRN_MANUAL"
#define SCRN_RADIO		"SCRN_RADIO"
#define SCRN_RADIOLIST	"SCRN_RADIOLIST"
#define SCRN_BT_SRC		"SCRN_BT_SRC"
#define SCRN_BT_MUSIC	"SCRN_BT_MUSIC"
#define SCRN_BT_DIAL	"SCRN_BT_DIAL"
#define SCRN_BT_RECORD	"SCRN_BT_RECORD"
#define SCRN_BT_BOOK	"SCRN_BT_BOOK"
#define SCRN_BT_PAIR	"SCRN_BT_PAIR"
#define SCRN_BT_SET		"SCRN_BT_SET"
#define SCRN_BT_OPTION	"SCRN_BT_OPTION"
#define SCRN_MEDIA_SRC	"SCRN_MEDIA_SRC"
#define SCRN_COMN		"SCRN_COMN"
#define SCRN_DIALOG		"SCRN_DIALOG"
#define SCRN_WALLPAPER	"SCRN_WALLPAPER"
#define SCRN_FULLPAPER	"SCRN_FULLPAPER"
#define SCRN_CALENDAR	"SCRN_CALENDAR"
#define SCRN_MEDIA_VIDEO_LIST	"SCRN_MEDIA_VIDEO_LIST"
#define SCRN_MEDIA_VIDEO	"SCRN_MEDIA_VIDEO"
#define SCRN_VIDEO_FULL		"SCRN_VIDEO_FULL"
#define SCRN_AUDIO_LIST		"SCRN_AUDIO_LIST"
#define SCRN_MEDIA_AUDIO	"SCRN_MEDIA_AUDIO"
#define SCRN_PIC_LIST		"SCRN_PIC_LIST"
#define SCRN_PIC_MAIN		"SCRN_PIC_MAIN"
#define SCRN_PIC_FULL		"SCRN_PIC_FULL"
#define SCRN_DVR_START		"SCRN_DVR_START"
#define SCRN_DVR_PHOTO		"SCRN_DVR_PHOTO"
#define SCRN_DVR_LIST		"SCRN_DVR_LIST"
#define SCRN_DVR_PLAY		"SCRN_DVR_PLAY"
#define SCRN_DVR_FULL		"SCRN_DVR_FULL"
#define SCRN_DVR_INFO		"SCRN_DVR_INFO"
#define SCRN_DVR_SETUP		"SCRN_DVR_SETUP"
#define SCRN_DVR_RATIO		"SCRN_DVR_RATIO"
#define SCRN_DVR_TIME		"SCRN_DVR_TIME"
#define SCRN_DVR_FORMAT		"SCRN_DVR_FORMAT"
#define SCRN_BT_PAIR_DLG	"SCRN_BT_PAIR_DLG"
#define SCRN_BT_DEV_DLG		"SCRN_BT_DEV_DLG"
#define SCRN_BT_DAIL_DLG	"SCRN_BT_DAIL_DLG"
#define SCRN_MCU_UPDATE		"SCRN_MCU_UPDATE"
#define SCRN_TIME_SET		"SCRN_TIME_SET"
#define SCRN_RADAR			"SCRN_RADAR"
#define SCRN_AVIN2			"SCRN_AVIN2"
#define SCRN_Attention		"SCRN_Attention"
#define SCRN_BT_TALKING	    "SCRN_BT_TALKING"
#define SCRN_BT_CALLING	    "SCRN_BT_CALLING"
#define SCRN_BT_DIALING	    "SCRN_BT_DIALING"
#define SCRN_BT_SETNAME	    "SCRN_BT_SETNAME"
#define SCRN_屏幕调节		"SCRN_屏幕调节"
#define SCRN_GPS测试	    "SCRN_GPS测试"
#define SCRN_DVR_FULL_DEL   "SCRN_DVR_FULL_DEL"
#define SCRN_LOG_PASS	    "SCRN_LOG_PASS"
#define SCRN_LOG_SWITCH     "SCRN_LOG_SWITCH"
#define SCRN_SHOW_DLG	    "SCRN_SHOW_DLG"
//===============================================================================
#define SCRN_DVD		"SCRN_DVD"
#define SCRN_DVD1		"SCRN_DVD1"
#define SCRN_方向盘设置	"SCRN_方向盘设置"
#define SCRN_蓝牙	"SCRN_蓝牙"
#define SCRN_电话本	"SCRN_电话本"
#define SCRN_密码盘		"SCRN_密码盘"
#define SCRN_显示设置	"SCRN_显示设置"
#define SCRN_音乐播放	"SCRN_音乐播放"
#define SCRN_音频设置	"SCRN_音频设置"
#define SCRN_参数设置	"SCRN_参数设置"
#define SCRN_导航_2		 "SCRN_导航_2"
#define SCRN_图片预览	"SCRN_图片预览"
#define SCRN_多媒体		"SCRN_多媒体"
#define SCRN_声音		"SCRN_声音"
#define SCRN_收音列表	"SCRN_收音列表"
#define SCRN_车标		"SCRN_车标"
#define SCRN_蓝牙音乐	"SCRN_蓝牙音乐"
#define SCRN_NullScreen	"SCRN_NullScreen"
#define SCRN_收音机2		"SCRN_收音机2"
#define SCRN_LOAD_PROCESS "SCRN_LOAD_PROCESS"
#define SCRN_多国语言 "SCRN_多国语言"
#define SCRN_时间调整	"SCRN_时间调整"
#define SCRN_系统设置	"SCRN_系统设置"
#define SCRN_GPS声音	"SCRN_GPS声音"
#define SCRN_蓝牙配置	"SCRN_蓝牙配置"
#define SCRN_TXTSHOW	"SCRN_TXTSHOW"
#define SCRN_对话框		"SCRN_对话框"	
#define SCRN_空调		"SCRN_空调"
#define SCRN_倒车11		"SCRN_倒车11"
#define SCRN_倒车	"SCRN_倒车"


#define SCRN_工厂设置	"SCRN_工厂设置"
#define SCRN_安吉星		"SCRN_安吉星"
#define SCRN_车身信息	"SCRN_车身信息"
#define SCRN_软键盘		"SCRN_软键盘"
#define SCRN_标志仪表控制	"SCRN_标志仪表控制"
#define SCRN_原车蓝牙和USB	"SCRN_原车蓝牙和USB"
#define SCRN_原车蓝牙	"SCRN_原车蓝牙"
#define SCRN_DVP图片    "SCRN_DVP图片"
#define SCRN_DVP文件列表 "SCRN_DVP文件列表"
//#define SCRN_屏幕调节 77+30
//#define SCRN_AVIN2	   78+30
#define SCRN_MEDIA     "SCRN_MEDIA"
#define SCRN_音频调节 "SCRN_音频调节"
#define SCRN_DVP_FS  "SCRN_DVP_FS"
#define SCRN_平衡设置  "SCRN_平衡设置"
#define SCRN_MEDIA_PIC "SCRN_MEDIA_PIC"
#define SCRN_SDUSB_LOAD "SCRN_SDUSB_LOAD"
#define SCRN_通讯录		"SCRN_通讯录"
#define SCRN_新电话本		"SCRN_新电话本"
#define SCRN_蓝牙编辑		"SCRN_蓝牙编辑"
#define SCRN_蓝牙搜索		"SCRN_蓝牙搜索"
#define SCRN_车身状态		"SCRN_车身状态"
#define SCRN_音量平衡		"SCRN_音量平衡"
#define SCRN_AUX2 "SCRN_AUX2"
#define SCRN_行车记录	"SCRN_行车记录"
#define SCRN_胎压检测	"SCRN_胎压检测"
#define SCRN_燃油里程	"SCRN_燃油里程"
#define SCRN_摄像头状态 "SCRN_摄像头状态"
#define SCRN_燃油2		"SCRN_燃油2"
#define SCRN_原车功放控制	"SCRN_原车功放控制"
#define SCRN_PowerOFF		"SCRN_PowerOFF"

/*
#define SCRN_MAIN1		0
#define SCRN_DVD		1
#define SCRN_DVD1		2
#define	SCRN_方向盘设置	3
#define SCRN_蓝牙		4
#define SCRN_电话本		5
#define SCRN_密码盘		6
#define	SCRN_显示设置	7
#define SCRN_音乐播放	8
#define	SCRN_音频设置	9
#define SCRN_参数设置	11
#define SCRN_导航_2		12
#define SCRN_图片预览	13
#define SCRN_多媒体		14
#define SCRN_声音		15
#define SCRN_收音列表	16
#define SCRN_车标		17
#define SCRN_蓝牙音乐	18
#define SCRN_DVD_控制	19
#define SCRN_NullScreen	20
#define SCRN_收音机2		21
#define SCRN_LOAD_PROCESS	22
#define SCRN_多国语言	23
#define SCRN_时间调整	24
#define	SCRN_系统设置	25
#define SCRN_GPS声音	26
#define SCRN_蓝牙配置	27
#define SCRN_TXTSHOW	28
#define SCRN_对话框		29
#define SCRN_空调		30
#define SCRN_倒车11		31
#define SCRN_倒车		32
#define SCRN_参数设置1  33
#define SCRN_GPS测试	34
#define SCRN_工厂设置	35
#define SCRN_安吉星		36
#define SCRN_车身信息	37
#define SCRN_软键盘		38
#define SCRN_标志仪表控制	39
#define SCRN_原车蓝牙和USB	40
#define SCRN_原车蓝牙	41
#define SCRN_DVP图片    42
#define SCRN_DVP文件列表    43 
#define SCRN_DVP_VCD    44 
#define SCRN_DVP_DVD1    45 
#define SCRN_DVP_DVD2    46 
#define SCRN_屏幕调节  47
#define SCRN_AVIN2	   48
#define SCRN_MEDIA     49
#define SCRN_MCU_UPDATE 50
#define SCRN_音频调节 51
#define SCRN_DVP_FS 52
#define SCRN_平衡设置  53
#define SCRN_MEDIA_PIC 54
#define SCRN_SDUSB_LOAD 55
#define SCRN_通讯录 56
#define SCRN_新电话本		57
#define SCRN_蓝牙编辑		58
#define SCRN_蓝牙搜索		59
#define SCRN_车身状态		60
#define SCRN_音量平衡		61
#define SCRN_AUX2			62
#define SCRN_行车记录	63
#define SCRN_胎压检测	64
#define SCRN_燃油里程	65
#define SCRN_摄像头状态	66
#define SCRN_燃油2		67
#define SCRN_原车功放控制 68
#define SCRN_PowerOFF	69
#define SCRN_Attention	70
*/

#define SCRN_IPOD		"SCRN_IPOD"
#define SCRN_导航		"SCRN_导航"
#define SCRN_SD			"SCRN_SD"
#define SCRN_数字电视	"SCRN_数字电视"
#define SCRN_我的电脑	"SCRN_我的电脑"

#define SCRN_USB		"SCRN_USB"

#define SCRN_外部输入	"SCRN_外部输入"

#define	SCRN_system		"SCRN_system"
#define	SCRN_DVD_CONTROL		"SCRN_DVD_CONTROL"
#define	SCRN_SYS_DIALOG			"SCRN_SYS_DIALOG"
#define SCRN_MD_CONTROL		"SCRN_MD_CONTROL"
//#define SCRN_GPS_DUMP		1000

#define _F_NULL

void getKeepLines(int *yBegin,int *yEnd);

void upVolume();

void dowVolume();

void upBright();
void downBright();

#endif

void showZHWConsol(bool beFromBackOrBt);


