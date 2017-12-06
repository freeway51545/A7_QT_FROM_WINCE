/*
 * Project Name JPEG DRIVER IN WINCE
 * Copyright  2007 Samsung Electronics Co, Ltd. All Rights Reserved. 
 *
 * This software is the confidential and proprietary information
 * of Samsung Electronics  ("Confidential Information").   
 * you shall not disclose such Confidential Information and shall use
 * it only in accordance with the terms of the license agreement
 * you entered into with Samsung Electronics 
 *
 * This file implements JPEG Test Application.
 *
 * @name JPEG Test Application Module (jpg_app.c)
 * @author Jiyoung Shin (idon.shin@samsung.com)
 * @date 28-05-07
 */
#include "pub.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
//#include "SVEDriverAPI.h"
#include "PUB.H"
//#include "image_cfg.h"
#include "msg.h"
#include "volumdef.h"




extern int inGps;
void closeVolMuteWindow();
void closeTurnBar();

void prevHidehGlobal();
void openAVinWhenLeaveGPS();

void setCamerInGps();
void setCamerNotInGps();
void setOpenedGPSWhenShowBack();


//#include "CeCriticalSelection.h"
//CeCriticalSelection * getGpsDataAccess();
	
//#define TO_GPS_BLACK_SCREEN
extern int isGpsRunBack;
void closeAVinWhenEntenGPS();

void showGPS(){
		
}
extern HWND hGlobal;

void showWINDOWMax();

extern HWND g_hVideoWnd;
void showGgggInGps(){
	
}

#define showedCamera() true
DWORD dShowZhwConsol=0;
extern int phone_map;
void showZHWConsol(bool beFromGpsOrBack){
	
}





#include "msg.h"
void reShowWindow();
//extern bool beShowVolumne;
void sendVolClose();
void setVolumeRect(RECT );

void closeVolMuteWindow(){
	//beShowVolumne=false;
	hideVolumeWindow();
	PostMessageZhw(MSG_UPDATE_OVERLAY);
	static RECT r={0,0,0,0};
	setVolumeRect(r);
	RE_DRAW;
	hideMuteWindow();
	sendVolClose();
}

bool isCameraOn();


void closeVolWin(){
	//beShowVolumne=false;
	hideVolumeWindow();
	PostMessageZhw(MSG_UPDATE_OVERLAY);
	sendVolClose();
}



void hideTaskBar(){

}

void showTaskBar(){
}