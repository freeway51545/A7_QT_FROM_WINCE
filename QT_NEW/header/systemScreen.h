#ifndef _SYSTEMSCREEN_
#define _SYSTEMSCREEN_

#include "screeneventmanager.h"

#define MAX_SETTING_VAL 100

#define PHONE_BRIGHTNESS 35
#define PHONE_CONTRAST 30
#define PHONE_HUE 40
#define PHONE_SATURATION 45 
#define PHONE_BACKLIGHT 100 //RANGE(0,10)100

/*
#define DEFAULT_HUE 55
#define DEFAULT_CONTRAST 30
#define DEFAULT_SATURATION 52 
#define DEFAULT_BRIGHTNESS 48
#define DEFAULT_BACKLIGHT 100

#define BRIGHT_HUE 57
#define BRIGHT_CONTRAST 42
#define BRIGHT_SATURATION 60 
#define BRIGHT_BRIGHTNESS 53
#define BRIGHT_BACKLIGHT 100*/


#define DEFAULT_HUE 55
#define DEFAULT_CONTRAST 30
#define DEFAULT_SATURATION 52 
#define DEFAULT_BRIGHTNESS 48
#define DEFAULT_BACKLIGHT 100

//#define AVIN_HUE 48
//#define AVIN_CONTRAST 53
//#define AVIN_SATURATION 54 
//#define AVIN_BRIGHTNESS 72
//#define AVIN_BACKLIGHT 100

#define AVIN_HUE 72
#define AVIN_CONTRAST 42
#define AVIN_SATURATION 65 
#define AVIN_BRIGHTNESS 70
#define AVIN_BACKLIGHT 100



#define BRIGHT_HUE 55
#define BRIGHT_CONTRAST 55
#define BRIGHT_SATURATION 56 
#define BRIGHT_BRIGHTNESS 74
#define BRIGHT_BACKLIGHT 100




#define SEC_MEDIA	0
#define SEC_AVIN	1
#define SEC_DVD		2
#define SEC_BACK	3
#define SEC_SYSTEM	4

#define SYS_CONFIG_LEN 5

class CSystemScreen{
public:
	int iBrightness;
	int iContrast;
	int iHue;
	int iSaturation;
	int iBackLight;

public:
	CSystemScreen();
	void setConfigVal();
	void useScreenDefault();
	void useMainScreenDefault();
	void useScreenBright();
	void useScreenPhone();

	int getiBrightness();
	int getiContrast();
	int getiHue();
	int getiSaturation();
	int getiBackLight();
	void setiBrightness(int iBrightness);
	void setiContrast(int iContrast);
	void setiHue(int iHue);
	void setiSaturation(int iSaturation);
	void setiBackLight(int iBackLight);

	void setiBrightnessValue(int iBrightness);
	void setiContrastValue(int iContrast);
	void setiHueValue(int iHue);
	void setiSaturationValue(int iSaturation);
	void setiBackLightValue(int iBackLight);
	void setDefault();
	void setDefaultAvin();
	void useAvinDefault();
};


class SystemConfig{
public:
	CSystemScreen css[SYS_CONFIG_LEN];
	SystemConfig();
	void screenEnterInit();

	///////////
	void setConfigVal();
	void useScreenDefault();

	int getGiBrightness();
	int getGiContrast();
	int getGiHue();
	int getGiSaturation();
	int getGiBackLight();
	void setGiBrightness(int iBrightness);
	void setGiContrast(int iContrast);
	void setGiHue(int iHue);
	void setGiSaturation(int iSaturation);
	void setGiBackLight(int iBackLight);
	void useGScreenDefault();
	void useGScreenBright();

};
extern SystemConfig sysCon;

#endif _SYSTEMSCREEN_