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
#define SCRN_��Ļ����		"SCRN_��Ļ����"
#define SCRN_GPS����	    "SCRN_GPS����"
#define SCRN_DVR_FULL_DEL   "SCRN_DVR_FULL_DEL"
#define SCRN_LOG_PASS	    "SCRN_LOG_PASS"
#define SCRN_LOG_SWITCH     "SCRN_LOG_SWITCH"
#define SCRN_SHOW_DLG	    "SCRN_SHOW_DLG"
//===============================================================================
#define SCRN_DVD		"SCRN_DVD"
#define SCRN_DVD1		"SCRN_DVD1"
#define SCRN_����������	"SCRN_����������"
#define SCRN_����	"SCRN_����"
#define SCRN_�绰��	"SCRN_�绰��"
#define SCRN_������		"SCRN_������"
#define SCRN_��ʾ����	"SCRN_��ʾ����"
#define SCRN_���ֲ���	"SCRN_���ֲ���"
#define SCRN_��Ƶ����	"SCRN_��Ƶ����"
#define SCRN_��������	"SCRN_��������"
#define SCRN_����_2		 "SCRN_����_2"
#define SCRN_ͼƬԤ��	"SCRN_ͼƬԤ��"
#define SCRN_��ý��		"SCRN_��ý��"
#define SCRN_����		"SCRN_����"
#define SCRN_�����б�	"SCRN_�����б�"
#define SCRN_����		"SCRN_����"
#define SCRN_��������	"SCRN_��������"
#define SCRN_NullScreen	"SCRN_NullScreen"
#define SCRN_������2		"SCRN_������2"
#define SCRN_LOAD_PROCESS "SCRN_LOAD_PROCESS"
#define SCRN_������� "SCRN_�������"
#define SCRN_ʱ�����	"SCRN_ʱ�����"
#define SCRN_ϵͳ����	"SCRN_ϵͳ����"
#define SCRN_GPS����	"SCRN_GPS����"
#define SCRN_��������	"SCRN_��������"
#define SCRN_TXTSHOW	"SCRN_TXTSHOW"
#define SCRN_�Ի���		"SCRN_�Ի���"	
#define SCRN_�յ�		"SCRN_�յ�"
#define SCRN_����11		"SCRN_����11"
#define SCRN_����	"SCRN_����"


#define SCRN_��������	"SCRN_��������"
#define SCRN_������		"SCRN_������"
#define SCRN_������Ϣ	"SCRN_������Ϣ"
#define SCRN_�����		"SCRN_�����"
#define SCRN_��־�Ǳ����	"SCRN_��־�Ǳ����"
#define SCRN_ԭ��������USB	"SCRN_ԭ��������USB"
#define SCRN_ԭ������	"SCRN_ԭ������"
#define SCRN_DVPͼƬ    "SCRN_DVPͼƬ"
#define SCRN_DVP�ļ��б� "SCRN_DVP�ļ��б�"
//#define SCRN_��Ļ���� 77+30
//#define SCRN_AVIN2	   78+30
#define SCRN_MEDIA     "SCRN_MEDIA"
#define SCRN_��Ƶ���� "SCRN_��Ƶ����"
#define SCRN_DVP_FS  "SCRN_DVP_FS"
#define SCRN_ƽ������  "SCRN_ƽ������"
#define SCRN_MEDIA_PIC "SCRN_MEDIA_PIC"
#define SCRN_SDUSB_LOAD "SCRN_SDUSB_LOAD"
#define SCRN_ͨѶ¼		"SCRN_ͨѶ¼"
#define SCRN_�µ绰��		"SCRN_�µ绰��"
#define SCRN_�����༭		"SCRN_�����༭"
#define SCRN_��������		"SCRN_��������"
#define SCRN_����״̬		"SCRN_����״̬"
#define SCRN_����ƽ��		"SCRN_����ƽ��"
#define SCRN_AUX2 "SCRN_AUX2"
#define SCRN_�г���¼	"SCRN_�г���¼"
#define SCRN_̥ѹ���	"SCRN_̥ѹ���"
#define SCRN_ȼ�����	"SCRN_ȼ�����"
#define SCRN_����ͷ״̬ "SCRN_����ͷ״̬"
#define SCRN_ȼ��2		"SCRN_ȼ��2"
#define SCRN_ԭ�����ſ���	"SCRN_ԭ�����ſ���"
#define SCRN_PowerOFF		"SCRN_PowerOFF"

/*
#define SCRN_MAIN1		0
#define SCRN_DVD		1
#define SCRN_DVD1		2
#define	SCRN_����������	3
#define SCRN_����		4
#define SCRN_�绰��		5
#define SCRN_������		6
#define	SCRN_��ʾ����	7
#define SCRN_���ֲ���	8
#define	SCRN_��Ƶ����	9
#define SCRN_��������	11
#define SCRN_����_2		12
#define SCRN_ͼƬԤ��	13
#define SCRN_��ý��		14
#define SCRN_����		15
#define SCRN_�����б�	16
#define SCRN_����		17
#define SCRN_��������	18
#define SCRN_DVD_����	19
#define SCRN_NullScreen	20
#define SCRN_������2		21
#define SCRN_LOAD_PROCESS	22
#define SCRN_�������	23
#define SCRN_ʱ�����	24
#define	SCRN_ϵͳ����	25
#define SCRN_GPS����	26
#define SCRN_��������	27
#define SCRN_TXTSHOW	28
#define SCRN_�Ի���		29
#define SCRN_�յ�		30
#define SCRN_����11		31
#define SCRN_����		32
#define SCRN_��������1  33
#define SCRN_GPS����	34
#define SCRN_��������	35
#define SCRN_������		36
#define SCRN_������Ϣ	37
#define SCRN_�����		38
#define SCRN_��־�Ǳ����	39
#define SCRN_ԭ��������USB	40
#define SCRN_ԭ������	41
#define SCRN_DVPͼƬ    42
#define SCRN_DVP�ļ��б�    43 
#define SCRN_DVP_VCD    44 
#define SCRN_DVP_DVD1    45 
#define SCRN_DVP_DVD2    46 
#define SCRN_��Ļ����  47
#define SCRN_AVIN2	   48
#define SCRN_MEDIA     49
#define SCRN_MCU_UPDATE 50
#define SCRN_��Ƶ���� 51
#define SCRN_DVP_FS 52
#define SCRN_ƽ������  53
#define SCRN_MEDIA_PIC 54
#define SCRN_SDUSB_LOAD 55
#define SCRN_ͨѶ¼ 56
#define SCRN_�µ绰��		57
#define SCRN_�����༭		58
#define SCRN_��������		59
#define SCRN_����״̬		60
#define SCRN_����ƽ��		61
#define SCRN_AUX2			62
#define SCRN_�г���¼	63
#define SCRN_̥ѹ���	64
#define SCRN_ȼ�����	65
#define SCRN_����ͷ״̬	66
#define SCRN_ȼ��2		67
#define SCRN_ԭ�����ſ��� 68
#define SCRN_PowerOFF	69
#define SCRN_Attention	70
*/

#define SCRN_IPOD		"SCRN_IPOD"
#define SCRN_����		"SCRN_����"
#define SCRN_SD			"SCRN_SD"
#define SCRN_���ֵ���	"SCRN_���ֵ���"
#define SCRN_�ҵĵ���	"SCRN_�ҵĵ���"

#define SCRN_USB		"SCRN_USB"

#define SCRN_�ⲿ����	"SCRN_�ⲿ����"

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


