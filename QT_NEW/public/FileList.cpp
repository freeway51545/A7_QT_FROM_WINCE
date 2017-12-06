
#include "pub.h"
#include "msg.h"

#include "filelist.h"
#include "sdusb_save.h"

#define CUR_IS_FILE	1
#define CUR_IS_DIR	2

bool isExistFile = false;

ZString FileList::getFileNameByType(int i,int type){
	return "";
}
void FileList::clear(){
}
void findOneDirAllFile(TCHAR* src,FileList*fl){
}
void FileList::init(TZString baseDirset){
}
ZString FileList::getName(int i,unsigned char *bType){
	ZString str;
	return str;
}
bool FileList::makeAsDirList(){
	return false;
}

#ifdef ZHWCCC



typedef BOOL (*FileFilter)(WIN32_FIND_DATA &d);
bool findFile(TCHAR* src,FileList*fl,FileFilter f );

BOOL dirFilter(WIN32_FIND_DATA &d){
	return d.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY;
}


BOOL mp3filter(WIN32_FIND_DATA &d){
	if(d.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
		return false;
	static char *mp3Extern[]={
			//audio
	".MP3",	".WMA",	".AC3",	".AAC",	".RA",	".RAM",	".RMM",
	".PCM",	".WAV",	".MP1",	".MP2",	".FLAC",	".APE",	};
	ZString zs;
	zs=d.cFileName;
	zs.upper();
	for(int i=0;i<sizeof(mp3Extern)/sizeof(mp3Extern[0]);i++){
		if(zs.endsWith(mp3Extern[i]))
			return true;
	}
	return false;
}

BOOL picfilter(WIN32_FIND_DATA &d){
	if(d.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
		return false;
	static char *picExtern[]={
		//PIC
		".JPG",	".BMP",".PNG",".GIF",};
		ZString zs;
		zs=d.cFileName;
		zs.upper();
		for(int i=0;i<sizeof(picExtern)/sizeof(picExtern[0]);i++){
			if(zs.endsWith(picExtern[i]))
				return true;
		}
		return false;
}

BOOL mp4filter(WIN32_FIND_DATA &d){
	if(d.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
		return false;
	static char *mp4Extern[]={"AVI","MP4","RMVB","MKV","TS","3GP","MPEG",
							   "MPG","M2V","RM","FLV","WMV","ASF"};
	/*{
	"AVI",	"VID",	"DIVX",	"ASF",	"MP4",	"M4A",	"MPG",	"MPEG",
	"DAT",	"VOB",	"3GP",	"M2V",	"3G2",	"M4V",	"OGG",	"OGM",
	"RM",	"RMV",	"RMVB",	"FLV",	"MKV",	"MOV",	"WMV",	"TS",
	"M2TS",	"MFS",    "DTS",	"MKA",	};*/
	ZString zs;
	zs=d.cFileName;
	zs.upper();
	for(int i=0;i<sizeof(mp4Extern)/sizeof(mp4Extern[0]);i++){
		if(zs.endsWith(mp4Extern[i]))
			return true;
	}
	return false;

}

void playVidoFile(TZString &fileName,unsigned char c);

bool FileList::actionOnDir(int nl){
	if(nl>=this->listAmount){
		return 0;
	}
	if(fileType[nl]==FILE_DIR_SDUSB){
		TZString tzsSelect=this->fileList[nl];
		if(tzsSelect==L".."){
			// 回到上一个目录
			TCHAR *tt=currentDir.getData();
			int baseLen=baseDir.size();
			int begin=wcslen(tt)-2;
			if(begin<=baseLen){
				currentDir=baseDir;
			}else{
				for(int i=begin;i>=baseLen-1;i--){
					TCHAR c=currentDir[i];
					if(c==L'\\'){
						currentDir.setAsSub(i+1);
						break;
					}
				}
			}
		}else{
			currentDir+=tzsSelect;
			currentDir+=L"\\";
		}
		makeAsDirList();
		nListType=CUR_IS_FILE;
		return 1;
	}
	else{
		// ACTION ON 
		// 播放某一个文件。
		TZString fileName;
		fileName=currentDir;
		fileName+=fileList[nl];
		nPlayedNl=nl;
		playVidoFile(fileName,nListMeta);
		TO_SCRN(SCRN_DVD);
		return 0;
	}
}

bool canAutoPlay = false;
void FileList::init(TZString baseDirset){
	canAutoPlay = false;//是否存在能播放的媒体
	isLMinfo = false;//是否是上次存储的信息
	baseDir=baseDirset;
	currentDir=baseDirset;
	nListType=CUR_IS_FILE;//每次进入显示文件类型 非目录
	//nListMeta=CUR_IS_MP4;//显示视频文件
	nListMeta=CUR_IS_MP3;//显示视频文件
	if(!recoverLMInfo(baseDirset)){//如果检测恢复信息失败
		if(!makeAsDirList()){//首次进入先检测视屏文件 如不存在 再去检测音频文件 
							//如果卡上无任何视频文件和音频文件停留在播放列表空界面 YH
			nListMeta=CUR_IS_MP4;
			iInitShowDirInfo = CUR_IS_MP4;//台头信息也要更改
			canAutoPlay=makeAsDirList();
		}else{
			canAutoPlay = true;
		}
	}else{
		isLMinfo = true;
	}
	nPlayedNl=0;
}

void FileList::exchangeMP3MP4(){
	if(nListMeta==CUR_IS_MP3){
		nListMeta=CUR_IS_MP4;
	}else{
		nListMeta=CUR_IS_MP3;
	}
	nListType=CUR_IS_FILE;
	makeAsDirList();
}

TZString FileList::getFileName(){
	return fileList[nPlayedNl];
}

TZString FileList::getNextFileName(){
	TZString tzstring;
	if(nPlayedNl>=listAmount-1){
		//return tzstring;
		nPlayedNl = 0;
	}
	for(int i=nPlayedNl+1;i<listAmount;i++){
		if(fileType[i]==FILE_FILE_SDUSB){
			TZString fileName;
			fileName=currentDir;
			fileName+=fileList[i];
			nPlayedNl=i;
			//playVidoFile(fileName,nListMeta);
			tzstring=fileName;
			break;
		}
	}
	return tzstring;
}

TZString FileList::getPrevFileName(){
	TZString tzstring;
	if(nPlayedNl<=1){
		//return tzstring;
		nPlayedNl=listAmount;
	}
	for(int i=nPlayedNl-1;i>=0;i--){
		//if(fileType[i]==FILE_FILE){
			if(fileType[i]==FILE_FILE_SDUSB){
				TZString fileName;
				fileName=currentDir;
				fileName+=fileList[i];
				nPlayedNl=i;
				//playVidoFile(fileName,nListMeta);
				tzstring=fileName;
				break;
			}
		//}
	}
	return tzstring;
}


bool FileList::makeAsDirList(){
	clear();
	bool reVal = false;
	if(nListType==CUR_IS_DIR){
		reVal=findFile(currentDir,this,dirFilter);
	}else{
		if(nListMeta==CUR_IS_MP3){
			reVal=listAsMp3File();
		}else if(nListMeta==CUR_IS_MP4){
			reVal=listAsMp4File();
		}else if(nListMeta==CUR_IS_PIC)
		{
			reVal=listAsPicFile();
		}
	}
	return reVal;
}



char*getChar1_0(char *buf,int len,TCHAR*toDraw);

ZString FileList::getName(int i,unsigned char *bType){
	ZString str;
	if(i<listAmount){
		char buffer[256];
		str=getChar1_0(buffer,256,fileList[i].getData());
		*bType=fileType[i];
	}
	return str;
}

void FileList::startScroll(int i,int type){
	switch(type){
	case CUR_IS_MP3:
		if(i<nAudioFileAmount){
			return audioFileList[i].beginScrollMe();
		}
		break;
	case CUR_IS_MP4:
		if(i<nVedioFileAmount){
			return vedioFileList[i].beginScrollMe();
		}
		break;
	case CUR_IS_PIC:
		if(i<nPicFileAmount){			
			return picFileList[i].beginScrollMe();
		}
		break;	

	case CUR_IS_DIRE:
		if(i<listAmount){			
			return fileList[i].beginScrollMe();
		}
		break;
	}
}

DWORD FileList::getTime(int i,int type){

	switch(type){
	case CUR_IS_MP3:
		if(i<nAudioFileAmount){
			return audioFileList[i].dTimeToScroll;
		}
		break;
	case CUR_IS_MP4:
		if(i<nVedioFileAmount){
			return vedioFileList[i].dTimeToScroll;
		}
		break;
	case CUR_IS_PIC:
		if(i<nPicFileAmount){			
			return picFileList[i].dTimeToScroll;
		}
		break;	

	case CUR_IS_DIRE:
		if(i<listAmount){			
			return fileList[i].dTimeToScroll;
		}
		break;
	}
	return 0;
}

ZString FileList::getFileNameByType(int i,int type){
	ZString str;
	char buffer[256];
	switch(type){
	case CUR_IS_MP3:
		if(i<nAudioFileAmount){
			str=getChar1_0(buffer,256,audioFileList[i].getData());
		}
		break;
	case CUR_IS_MP4:
		if(i<nVedioFileAmount){
			str=getChar1_0(buffer,256,vedioFileList[i].getData());
		}
		break;
	case CUR_IS_PIC:
		if(i<nPicFileAmount){			
			str=getChar1_0(buffer,256,picFileList[i].getData());
		}
		break;	

	case CUR_IS_DIRE:
		if(i<listAmount){			
			str=getChar1_0(buffer,256,fileList[i].getData());
		}
		break;
	}
	
	return str;
}

void FileList::clear(){
	listAmount=0;
	nOneDirAmount = 0;
	nPicFileAmount = 0;
	nAudioFileAmount = 0;
	nVedioFileAmount = 0;
}

void FileList::setAsShowDir(){
	nListType=CUR_IS_DIR;
	makeAsDirList();
}

void FileList::setAsShowFile(){
	nListType=CUR_IS_FILE;
	listAsMp3File();
}

/*BOOL FileList::GetFileID3(){
	BOOL getFileId3Info();
	getFileId3Info();
}*/
 

bool FileList::listAsMp4File(){
	 return findFile(currentDir,this,mp4filter);
}

bool FileList::listAsMp3File(){
	return findFile(currentDir,this,mp3filter);
}

bool FileList::listAsPicFile(){
	return findFile(currentDir,this,picfilter);
}

void FileList::addOneDirFile(TCHAR *name,unsigned char type){
	if(listAmount>=MAX_LIST)
		return;
	fileList[listAmount]=name;
	fileType[listAmount]=type;
	fileMetaType[listAmount]=nListMeta;
	allFileDirList[listAmount]=fileDirTemp;
	listAmount++;
}

void FileList::addNewFile(TCHAR *name,unsigned char type){
	if(listAmount>=MAX_LIST)
		return;
	fileList[listAmount]=name;
	fileType[listAmount]=type;
	fileMetaType[listAmount]=nListMeta;
	allFileDirList[listAmount]=fileDirTemp;
	switch(nListMeta){
		case CUR_IS_MP3:
			audioFileList[nAudioFileAmount] = name;
			audioFileDirList[nAudioFileAmount] = fileDirTemp;
			nAudioFileAmount++;
			break;
		case CUR_IS_MP4:
			vedioFileList[nVedioFileAmount] = name;
			vedioFileDirList[nVedioFileAmount] = fileDirTemp;
			nVedioFileAmount++;
			break;
		case CUR_IS_PIC:
			picFileList[nPicFileAmount] = name;
			picFileDirList[nPicFileAmount] = fileDirTemp;
			nPicFileAmount++;
			break;
		default:
			break;

	}
	listAmount++;
}


void FileList::addNewFile(TCHAR *name,unsigned char type,int meta){
	switch(meta){
		case CUR_IS_MP3:
			{
				if(nAudioFileAmount>=MAX_LIST){
					return;
				}
				audioFileList[nAudioFileAmount] = name;
				audioFileDirList[nAudioFileAmount] = fileDirTemp;
				nAudioFileAmount++;
			}			
			break;
		case CUR_IS_MP4:
			{
				if(nVedioFileAmount>=MAX_LIST){
					return;
				}
				vedioFileList[nVedioFileAmount] = name;
				vedioFileDirList[nVedioFileAmount] = fileDirTemp;
				nVedioFileAmount++;
			}
			break;
		case CUR_IS_PIC:
			{
				if(nPicFileAmount>=MAX_LIST){
					return;
				}
				picFileList[nPicFileAmount] = name;
				picFileDirList[nPicFileAmount] = fileDirTemp;
				nPicFileAmount++;
			}			
			break;
		default:
			break;

	}
	/*if(listAmount>=MAX_LIST)
		return;
	fileList[listAmount]=name;
	fileType[listAmount]=type;
	fileMetaType[listAmount]=meta;
	allFileDirList[listAmount]=fileDirTemp;
	switch(meta){
		case CUR_IS_MP3:
			audioFileList[nAudioFileAmount] = name;
			audioFileDirList[nAudioFileAmount] = fileDirTemp;
			nAudioFileAmount++;
			break;
		case CUR_IS_MP4:
			vedioFileList[nVedioFileAmount] = name;
			vedioFileDirList[nVedioFileAmount] = fileDirTemp;
			nVedioFileAmount++;
			break;
		case CUR_IS_PIC:
			picFileList[nPicFileAmount] = name;
			picFileDirList[nPicFileAmount] = fileDirTemp;
			nPicFileAmount++;
			break;
		default:
			break;

	}
	listAmount++;*/
}

void FileList::addNewFile(WIN32_FIND_DATA &FindFileData){
	/*addNewFile(FindFileData.cFileName,
		(FindFileData.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)?	FILE_DIR_SDUSB:FILE_FILE_SDUSB);*/
		addOneDirFile(FindFileData.cFileName,
		(FindFileData.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)?	FILE_DIR_SDUSB:FILE_FILE_SDUSB);
}


void FileList::exchangedDirOrFile(){
	if(nListType==CUR_IS_DIR){
		nListType=CUR_IS_FILE;
	}else{
		nListType=CUR_IS_DIR;
	}
	makeAsDirList();
}

bool FileList::isSearchDir(){
	return nListType==CUR_IS_DIR;
}

void setLdPicNo();
void redrawAtOnce_aaa(){
	static DWORD old=GetTickCount();
	if(GetTickCount()-old>200){
		setLdPicNo();
		reDrawAtOnce();
		old=GetTickCount();
	}
}


void search_All_File(TCHAR *rootPath,FileList*fl,FileFilter f)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	BOOL bRet=FALSE;

	TCHAR szFind[MAX_PATH];

	ZeroMemory(szFind,sizeof(TCHAR)*MAX_PATH);
	wcscpy(szFind,rootPath);
	wcscat(szFind,L"\\*.*");
	
	hFind = FindFirstFile(szFind, &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE) 
	{
		return;
	} 

	while(TRUE)
	{
		if(FindFileData.cFileName[0]!=_T('.'))
		{
			redrawAtOnce_aaa();			
			if(FindFileData.dwFileAttributes!=FILE_ATTRIBUTE_DIRECTORY)
			{	
				if(f(FindFileData)){
					isExistFile = true;//只要找到任何一个扩展名中的文件 该类型文件就存在
					fl->fileDirTemp = rootPath;
					fl->addNewFile(FindFileData);
				}
			}
			if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				wcscpy(szFind,rootPath);
				wcscat(szFind,_T("\\"));
				wcscat(szFind,FindFileData.cFileName);
				search_All_File(szFind,fl,f);
			}
		}
		bRet=FindNextFile(hFind,&FindFileData);
		if(!bRet)
		{
			break;
		}

	}
	FindClose(hFind);
}


bool findFile(TCHAR* src,FileList*fl,FileFilter f) 
{ 
	isExistFile = false;
	search_All_File(src,fl,f);
	return isExistFile;
} 

void findOneDirAllFile(TCHAR* src,FileList*fl){
	fl->clear();
	fl->currentDir = src;
	fl->fileDirTemp = src;
	WIN32_FIND_DATA FindFileData; 
	HANDLE hFind; 
	TCHAR tmpsrc[256]; 
	wcscpy(tmpsrc,src); 
	wcscat(tmpsrc,L"\\*.*"); 
	hFind = FindFirstFile(tmpsrc, &FindFileData); 
	if(hFind == INVALID_HANDLE_VALUE) 
		return; 
	do 
	{ 
		if(FindFileData.cFileName[0]!=_T('.'))
		{
			if(dirFilter(FindFileData))
			{
				fl->nListMeta = CUR_IS_DIRE;
				fl->addNewFile(FindFileData);
			}
			else if(mp3filter(FindFileData))
			{
				fl->nListMeta = CUR_IS_MP3;
				fl->addNewFile(FindFileData);
			}else if(mp4filter(FindFileData))
			{
				fl->nListMeta = CUR_IS_MP4;
				fl->addNewFile(FindFileData);
			}else if(picfilter(FindFileData))
			{
				fl->nListMeta = CUR_IS_PIC;
				fl->addNewFile(FindFileData);
			}
		}
	}while(FindNextFile(hFind,&FindFileData)); 
	FindClose(hFind);
}

//===================================20161013=================================================
static char *viedoExtern[]={"AVI","MP4","MPG","MKV","RMVB","3GP","MOV","MPEG","M2V","RM","FLV","WMV","ASF"};
static char *audioExtern[]={".MP3",".WMA",".AC3",".AAC",".RA",".RAM",".RMM",".PCM",".WAV",".MP1",".MP2",".FLAC",".APE"};
static char *pictureExtern[]={".JPG",".PNG",".BMP",".GIF"};
static char *otherExtern[]={".ZIP",".RAR",".TXT",".EXE",".DLL",".APK"};

BOOL otherfilter(ZString zs){
	for(int i=0;i<sizeof(otherExtern)/sizeof(otherExtern[0]);i++){
		if(zs.endsWith(otherExtern[i]))
			return true;
	}
	return false;
}

BOOL audioFilter(ZString zs){
	for(int i=0;i<sizeof(audioExtern)/sizeof(audioExtern[0]);i++){
		if(zs.endsWith(audioExtern[i]))
			return true;
	}
	return false;
}

BOOL pictureFilter(ZString zs){
		for(int i=0;i<sizeof(pictureExtern)/sizeof(pictureExtern[0]);i++){
			if(zs.endsWith(pictureExtern[i]))
				return true;
		}
		return false;
}

BOOL videoFilter(ZString zs){
	for(int i=0;i<sizeof(viedoExtern)/sizeof(viedoExtern[0]);i++){
		if(zs.endsWith(viedoExtern[i]))
			return true;
	}
	return false;

}

void searchAllFile(TCHAR *rootPath,FileList*fl)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	BOOL bRet=FALSE;

	TCHAR szFind[MAX_PATH];

	ZeroMemory(szFind,sizeof(TCHAR)*MAX_PATH);
	wcscpy(szFind,rootPath);
	wcscat(szFind,L"\\*.*");

	hFind = FindFirstFile(szFind, &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE) 
	{
		return;
	} 

	while(TRUE)
	{
		if(FindFileData.cFileName[0]!=_T('.'))
		{		
			if(FindFileData.dwFileAttributes!=FILE_ATTRIBUTE_DIRECTORY)
			{	
				ZString zs;
				zs=FindFileData.cFileName;
				zs.upper();
				if(!otherfilter(zs)){
					fl->fileDirTemp = rootPath;
					if(videoFilter(zs)){						
						fl->addNewFile(FindFileData.cFileName,FILE_FILE_SDUSB,CUR_IS_MP4);
					}else if(audioFilter(zs)){						
						fl->addNewFile(FindFileData.cFileName,FILE_FILE_SDUSB,CUR_IS_MP3);
					}else if(pictureFilter(zs)){						
						fl->addNewFile(FindFileData.cFileName,FILE_FILE_SDUSB,CUR_IS_PIC);
					}
				}
			}
			if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				wcscpy(szFind,rootPath);
				wcscat(szFind,_T("\\"));
				wcscat(szFind,FindFileData.cFileName);
				searchAllFile(szFind,fl);
			}
		}
		bRet=FindNextFile(hFind,&FindFileData);
		if(!bRet)
		{
			break;
		}

	}
	FindClose(hFind);
}


void ScanOneDirAllFile(TCHAR* src,FileList*fl){
	fl->listAmount=0;
	fl->currentDir = src;
	fl->fileDirTemp = src;
	WIN32_FIND_DATA FindFileData; 
	HANDLE hFind; 
	TCHAR tmpsrc[256]; 
	wcscpy(tmpsrc,src); 
	wcscat(tmpsrc,L"\\*.*"); 
	hFind = FindFirstFile(tmpsrc, &FindFileData); 
	if(hFind == INVALID_HANDLE_VALUE) 
		return; 
	do 
	{ 
		if(FindFileData.cFileName[0]!=_T('.'))
		{

			ZString zs;
			zs=FindFileData.cFileName;
			zs.upper();			
			if(dirFilter(FindFileData))
			{
				fl->nListMeta = CUR_IS_DIRE;
				fl->addNewFile(FindFileData);
			}else{
				if(!otherfilter(zs)){
					if(videoFilter(zs)){						
						fl->nListMeta = CUR_IS_MP4;
						fl->addNewFile(FindFileData);
					}else if(audioFilter(zs)){						
						fl->nListMeta = CUR_IS_MP3;
						fl->addNewFile(FindFileData);
					}else if(pictureFilter(zs)){						
						fl->nListMeta = CUR_IS_PIC;
						fl->addNewFile(FindFileData);
					}
				}
			}			
		}
	}while(FindNextFile(hFind,&FindFileData)); 
	FindClose(hFind);

	/*for(int i=0;i<fList.listAmount;i++){
		RETAILMSG(1,(L"LIST-NAME[%s]\r\n",fList.fileList[i]));
	}*/
}

#endif