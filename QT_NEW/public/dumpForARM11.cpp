#include  "pub.h"

void initGPIOFromDLL(){
}
void  startCameraService(void){
}
void  closeCamWindow(void){}


void  restoreWin0Phr(void){};
void  openCamWindow(void){};
void  powerKeyPressed(unsigned long,unsigned long *){};



void strcpy_s_zhw(char *buffer,int lenToCopy,char *sss){
	if(buffer==NULL)
		return;
	if(sss==NULL){
		*buffer=0;
		return;
	}
	int max=strlen(sss);
	while(*sss&&lenToCopy>0&&max>0){
		*buffer=*sss;
		buffer++;
		sss++;
		lenToCopy--;
		max--;
	}
	*buffer=0;
}

void strncpy_s_zhw(char *buffer,int lenToCopy,char *sss,int max){
	if(buffer==NULL)
		return;
	if(sss==NULL){
		*buffer=0;
		return;
	}
	while(*sss&&lenToCopy>0&&max>0){
		*buffer=*sss;
		buffer++;
		sss++;
		lenToCopy--;
		max--;
	}
	*buffer=0;
}


void closeBtWave(){};
void openBtWave(){};
void  setWindowRange(struct tagRECT){};


void setVolumeRect(RECT ){}

bool  useShareUsbAndSd(void){return 0;};

void  changeMetaScreen(int){};

void  waitForDVDStoped(bool){};

void  ifInMetaScrollBarGotoSyj(void){}
int  executeSTM8IC(unsigned long,unsigned char,unsigned char){return 0;}




void  setU194052_AS_BT_proxy(void){}
void  setU194052_AS_GPS_proxy(void){}
bool  getIsCaramCopying(void){return 0;}
void  stopCameraCopy(void){}
void  execute8202CMD_Native(unsigned char,unsigned char,unsigned short){}
void  setCurrentIsPlayingMpg(void){}
void  setCurrentIsPlayingMp4(void){}
void  sendResumeCmd(void){}
int  executeSTM8IC0_A2(unsigned long,unsigned char,unsigned char){return 0;}
void  postTouchCmd(int,int){}
void  setNoCopyWhenCloseCam(void){}


void  openCameraCopy(void){};
void  execute8202CMD(unsigned char){}
bool canLoadProcessBar=0;
unsigned char *  getScreenBuffer(void){return NULL;}
void  setMayº¸≈Ã…®√Ë(void){}
void  startKeyScan(void){}
bool  beStartCopyData(void){return 0;}
void  startCameraRun(void){}
bool  stopCameraRun(void){return 0;}
void drawBackGroud(){};


int nMalloced=0;

extern "C"{

	void *zhw_malloc(int size);

	char*zhw_clone_str(char*str){
		if(str==NULL)
			return NULL;
		int n=strlen(str)+1;
		char *ss=(char*)zhw_malloc(n);
		strcpy_s_zhw(ss,n,str);
		return ss;
	}


		void *zhw_malloc(int size){
			if(size<=0){
				size=1;
			}
			void *p=malloc(size);
			if(p==NULL)
				return NULL;
			nMalloced++;

			memset(p,0,size);
	#ifdef WINCE
			//RETAILMSG_DC(1,(L"malloc address 0x%08X SIZE:%d malloc:%d \r\n",(UINT)p,size,nMalloced));
	#else
			printf("malloc address %08X \r\n",(UINT)p);
	#endif
			return p;
		}

		void reportNewReleaseCoutern(){
	#ifdef WINCE
		printf("malloc nMalloced=%d \r\n",nMalloced);
	#endif
		}



	void zhw_free_handle(void**a){
			if(*a==NULL)
				return;

			try
			{ 
				free(*a);
			}
			catch(...)
			{
				
				RETAILMSG_DC(1,(L" FEEE ERROR \r\n"));
			}
			nMalloced--;
	#ifdef WINCE 
			//RETAILMSG_DC(1,(L"free address %08X malloced:%d\r\n",(UINT)(*a),nMalloced));
	#else
			printf("free address %08X \r\n",(UINT)(*a));
	#endif
			try
			{
				*a=NULL;
			}
			catch(...)
			{
				
				RETAILMSG_DC(1,(L" SET A = NULL ERROR \r\n"));
			}

	}

}
ZString backGroundName("G:\\A7_QT_FROM_WINCE\\WORK_DIR\\img_work\\BKG\\2.jpg");


	TCHAR*zhw_clone_tstr(TCHAR*str){
		int n=wcslen(str)+1;
		TCHAR *ss=(TCHAR*)zhw_malloc(n*sizeof(TCHAR));
		wcscpy(ss,str);
		return ss;
	}
		