#include "pub.h"
#include "msg.h"
#include "ScreenEventManager.h"
#include "keyEvent.h"



unsigned char remoteKeyValue[5];
unsigned char keyLoc=0;


#define IR_BYTE_HEAD		0XFE
#define IR_REPEAT_BYTE		0xFD
#define REPLACE_BYTE		0xFC
#define CHAR_FF				0xF0
#define CHAR_REPLACE		0xF1


bool recivedReplaceChar=false;


#define BACK_UP_VALUE		0xFB
#define BACK_DOWN_VALUE		0xFA
extern bool beGot倒车镜像;
//extern bool changedCamera镜像;
void reInitCamera(int newLine=-1);

LPARAM tranlsate(unsigned char key0){
	// 64 位的数据
	long key=key0;
	if(key==0xff){
		return NULL_KEY;
	}
	if(key==REPLACE_BYTE){
		recivedReplaceChar=true;
		return NULL_KEY;
	}
	if(recivedReplaceChar){
		switch(key){
			case CHAR_FF:
				key=0xFF;
				break;
			case CHAR_REPLACE:
				key=REPLACE_BYTE;
				break;
			default:
				/** 替换码，除了 ,0XFF REPLACE_BYTE 就是方向盘键
				0~50，51~100 */
				if(IS_IN_FXP_SHE_ZHI)
					key+=FANGXPAN_BASE;
				else
					key=getFxpKey(key+FANGXPAN_BASE);
				break;
		}
		recivedReplaceChar=false;
	}

	if(keyLoc==0){
		if(key==IR_BYTE_HEAD){
			keyLoc=1;
			remoteKeyValue[0]=IR_BYTE_HEAD;
			return NULL_KEY;
		}if(key==IR_REPEAT_BYTE ){
			// 忽略不处理
			return NULL_KEY;// NULL KEY
		}else{
			return key;
		}
	}else{
		remoteKeyValue[keyLoc++]=(unsigned char)key;
		if(keyLoc>=5){
			unsigned long removeKey=0;
				removeKey=remoteKeyValue[1]<<24;
				removeKey|=remoteKeyValue[3]<<16;
				removeKey|=remoteKeyValue[2]<<8;
				removeKey|=remoteKeyValue[4];
				//PostMessageZhw(MSG_KEY_EVENT,removeKey);
				RETAILMSG_DC(1, (L"recive key \r\n#define RT_KEY_XXX 0X%08X\r\n",removeKey));
				keyLoc=0;
				return removeKey;
		}
		return NULL_KEY;
	}
}


bool isKeyEvent(LPARAM lParam){
	if(NULL_KEY==lParam)
		return false;
	if(lParam>0xFF){//方向盘控制键，遥控		
		return false;
	}
	return true;// 或者按钮
}

