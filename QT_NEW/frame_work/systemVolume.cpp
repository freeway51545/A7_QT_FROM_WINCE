#include <QtGui>

#include "pubtype.h"
#include "sdconfig.h"
#include "zstring.h"
#include "tzstring.h"
#include "systemVolume.h"	
#include "pub.h"


void initMeta();
//BOOL //setFrontVolume(UINT32 pSetValue);
bool isCallStateInComing(){
	return 0;
}

/*const static int matchToGain[]={0,//30+1
1,2,3,4,5,6,7,8,9,10,//1
13,16,19,22,25,28,31,34,37,40,//3
48,56,64,72,80,88,96,102,110,120};//8*/

const static int matchToGain[]={0,//30+1
1,2,3,4,5,6,7,8,9,10,//1
13,16,19,22,25,28,31,34,37,40,//3
47,54,61,68,75,82,89,96,103,110};//7

/*const static int matchToRadioGain[]={0,//30+1
1,2,3,4,5,6,7,8,9,10,//1
12,16,20,24,28,32,36,40,44,48,//3
53,60,67,74,81,88,89,96,103,110};//6*/

const static int matchToRadioGain[]={0,//30+1
1,2,3,4,5,6,7,8,9,10,//1
12,16,20,24,28,32,36,40,44,48,//4
53,58,63,68,73,78,83,88,93,98};//5

void clearnLastChanel(int nVolumeTypeSet){
}

#define MM_SET_MUTE_UNMUTE_GPS_STREAM   (WM_USER + 0x14) 
enum 
{ 
	MUTE_NO_MUTE_CH = 0X0, 
	MUTE_RIGHT_CH = 0X1, 
	MUTE_LEFT_CH = 0X2, 
	MUTE_LEFT_AND_RIGHT_CH = 0X3,//不起用
}; 
bool isNowBTCalling()
{
 	 if(willData.IsHaveCalling||
		willData.IsInTalking||
		willData.IsTelDialing){
			return true;
	 }else{
		return false;
	 }	
}


//================================================================================
typedef enum
{
	AUD_NORMAL_MODE = 0,
	AUD_BT_CALL_MODE, //蓝牙通话专用
}AUD_OUTPUT_MODE;

typedef enum
{
	DSP_MIX_FRONT_LR_CH = 1<<0, //前左，前右(默认配置)
	DSP_MIX_SURROUND_CH = 1<<1, //后左，后右
	DSP_MIX_CENTER_CH = 1<<2, //中置
	DSP_MIX_SUBWOOFER_CH= 1<<3, //重低音
}DSP_MIX_OUTPUT_CH;

#define MM_SET_DSP_MIX_OUTPUT_CH (WM_USER + 0x17)

void setGpsBtALlChannel(){	
	
}

//================================================================================
void setGPSvolume(int volSet){
	
}

void setCarlifeVolume(int volSet){
	
	
	
}


 



extern int btCallVol;
void inithMediaGraphAudio();
int nCurrentChanel=10;
int nLastChanel=1;
void changedChanelVolume(int nChanel,int nSecondChanel,int volSet){
	//initMeta();
	if(volSet>MAX_VOL){
		volSet=MAX_VOL;
	}			
	int volumeValue=matchToGain[volSet]*(FULL_VOLUME_GAIN/5)/MAX_VOL;
	if(volumeValue<0){
		volumeValue=0;
	}
	setGpsBtALlChannel();//20160722

	static bool bSetSystemVolMax=true;
	if(bSetSystemVolMax){
		if(!isCallStateInComing()){
			//waveOutSetVolume(0,0xCCCCCCCC);//系统音量
			bSetSystemVolMax=false;
			RETAILMSG_DC(1,(L"max system volume\r\n"));
		}
	}
	ZString zs;
	zs.format("[VOL:]%d\r\n",volSet);
	RETAILMSG(1,(zs.getTChar()));
	if(!isNowBTCalling()){
		//RETAILMSG_DC(1,(L"SEND GPS volume!"));
		if(willData.isMute()){
			RETAILMSG_DC(1,(L"GPS is MUTE"));
			setGPSvolume(0);//fix bug 20151204 yinhong gps mute时却换媒体源 gps会发声
		}else{
			if(!willData.beGps独立){
				if(volSet!=0){//忽略vc.vol=0
					
					if(willData.isIisInOutputing()){
						RETAILMSG_DC(1,(L"GPS normal %d!",volSet+8));
						setGPSvolume(volSet+8);
						/*int v1=volSet+8;
						if(v1>MAX_VOL){
							v1=MAX_VOL;
						}
						*/
						//DWORD ringValue=(MAX_VOL*0xFFFF/MAX_VOL)<<16|(v1*0xFFFF/MAX_VOL);				
						//if(waveOutSetVolume(0,0xFFFFFFFF) == MMSYSERR_NOERROR){}
					}					
				}
			}else{
				RETAILMSG_DC(1,(L"GPS independent %d!",willData.n独立声音大小));
				setGPSvolume(willData.n独立声音大小);
			}
		}
		
	}
	if(nSecondChanel!=-1){
		RETAILMSG_DC(1,(L"---------   small vol\r\n"));		
		volumeValue=matchToGain[volSet/2]*(FULL_VOLUME_GAIN/5)/MAX_VOL;
	}

	switch(nChanel){
		case VOL_DVD_2313:
		case VOL_CDC_2313:
		//case VOL_BT_MUSIC_2313_BT:		
			//setFrontVolume(volumeValue);
			//nCurrentChanel=MSDK_AVIN_ANONE;		
			//nCurrentChanel=AVIN_CHANNEL_NONE;
			break;

		case VOL_BT_MUSIC_2313_BT://2015-1-5
			////setFrontVolume(volumeValue*4);//*4
			////setFrontVolume(volumeValue*3);//*4
			//nCurrentChanel=MSDK_AVIN_ANONE;
			//nCurrentChanel=AVIN_CHANNEL_NONE;
			break;

		case VOL_IIS_2313:
			// 当前没有任何媒体播放，只有GPS 发声
			//setFrontVolume(0);//test
			//nCurrentChanel=nLastChanel;
			break;

		case VOL_RADIO_2313:
			extern unsigned char radioVolAmp;
			if(nSecondChanel!=-1){//导航监听  //2014-12-31
				volSet=(unsigned int)volSet/2;
			}		

			if(radioVolAmp){//Si47xx  //FULL_VOLUME_GAIN最大0xfffff 2015-5-11
				volumeValue=matchToRadioGain[volSet]*(0xfffff/5)/MAX_VOL;
				if(volumeValue>0xfffff){
					volumeValue=0xfffff;
				}
			}else{//nxp6621
				volumeValue=matchToRadioGain[volSet]*(FULL_VOLUME_GAIN/5)/MAX_VOL;
				volumeValue=volumeValue*4;
			}
			//setFrontVolume(volumeValue);//收音声音小了
			//nCurrentChanel=MSDK_AVIN_A2;
			break;
		case VOL_AUX_2313:
			//setFrontVolume(volumeValue*6);//*4 2014-12-31
			//nCurrentChanel=MSDK_AVIN_A1;//后aux
			break;
		case VOL_AUX2_2313://2015-03-24 yh
			//setFrontVolume(volumeValue*6);
			//nCurrentChanel=MSDK_AVIN_A0;//前aux
			break;
		case VOL_IPOD_2313:
			//setFrontVolume(volumeValue);
			//nCurrentChanel=MSDK_AVIN_A4;
			break;

		case VOL_BT_2313://HSS
			//setFrontVolume(0);
			if(isNowBTCalling()){
				setGPSvolume(0);
			}
			//nCurrentChanel=MSDK_AVIN_ANONE;
			if(isCallStateInComing()){
				//waveOutSetVolume(0,(btCallVol*0xFFFF/MAX_VOL)<<16|(btCallVol*0xFFFF/MAX_VOL));//set low
				RETAILMSG(1,(L" btcallvol>>%d\r\n",btCallVol));
				/*DWORD ringValue=(volSet*0xFFFF/MAX_VOL)<<16|(volSet*0xFFFF/MAX_VOL);
				if(waveOutSetVolume(0,ringValue) != MMSYSERR_NOERROR){
					RETAILMSG_DC(1,(L"set system vol fail! \r\n"));
				}*/
				bSetSystemVolMax=true;
			}
			//else	//cancle else 铃声时同时设置通话音量 2015-1-16
			{
				volumeValue=volSet*FULL_BT_PHONE_GAIN/MAX_VOL;
				//waveOutMessage((HWAVEOUT)0, (WM_USER + 0x12), volumeValue,0);//#define MM_SPH_SETVOLUME        (WM_USER + 0x12)		//不会受系统音量的影响
			}
			break;

		case VOL_CARLIFE_SYSTEM:
			{	
				DWORD ringValue=(volSet*0xFFFF/MAX_VOL)<<16|(volSet*0xFFFF/MAX_VOL);				
				//if(waveOutSetVolume(0,ringValue) == MMSYSERR_NOERROR){}			
			}
			break;

		default:
			//setFrontVolume(volumeValue);			
			//nCurrentChanel=nLastChanel;
			break;
	}	
	
	if(nCurrentChanel!=nLastChanel)
	{
		RETAILMSG_DC(1,(L"==Audio Chanel Changed==: %d-->%d \r\n",nLastChanel,nCurrentChanel));
		//i//f(NULL!=m_hMediaGraphAudio){
			//changedToDvdVolumeChanelForc();	
			//ChangeCurrentVolumeChannel(nCurrentChanel,&t_AVIN_SINK_INFO);
			//rt=MediaGraph_SetAudioInSource(m_hMediaGraphAudio, nCurrentChanel, &t_AVIN_SINK_INFO);
			nLastChanel=nCurrentChanel;
		//}
	}
	//GCloseAudioDev(hAudioDev);
	
}

