
#ifndef STR_FILELIST_H
#define STR_FILELIST_H


#include "zstring.h"
#include "tzstring.h"
//#include "ADOPlayer.h"

#define CUR_IS_FILE	1
#define CUR_IS_DIR	2

#define CUR_IS_MP3	0
#define CUR_IS_MP4	1
#define CUR_IS_PIC  2
#define CUR_IS_DIRE  4

#define FILE_DIR_SDUSB	10
#define FILE_FILE_SDUSB	11

#define MAX_LIST	10000
#define ALl_LIST_LEN 30000//20161013 存储整个磁盘的最大文件数

class FileList{
public:
	int nListType;
	int nPlayedNl;
	int nListMeta;
	TZString baseDir;
	TZString currentDir;
	//============20140512==========
	TZString fileDirTemp;

	TZString allFileDirList[MAX_LIST];


	int nOneDirAmount;
	TZString oneDirList[MAX_LIST];

	int nPicFileAmount;
	int nAudioFileAmount;
	int nVedioFileAmount;
	TZString audioFileList[MAX_LIST];
	TZString picFileList[MAX_LIST];
	TZString vedioFileList[MAX_LIST];
	TZString audioFileDirList[MAX_LIST];
	TZString picFileDirList[MAX_LIST];
	TZString vedioFileDirList[MAX_LIST];
	//==============================
	bool isSearchDir();
public:
	void init(TZString baseDir);
	int listAmount;
	TZString fileList[MAX_LIST];	
	unsigned char fileType[MAX_LIST];
	unsigned char fileMetaType[MAX_LIST];
	bool makeAsDirList();
	void exchangeMP3MP4();
	bool actionOnDir(int nl);
	void upDir();
	void clear();
	bool listAsMp4File();
	bool listAsMp3File();
	bool listAsPicFile();
	//void addNewFile(WIN32_FIND_DATA &FindFileData);
	void addNewFile(TCHAR *name,unsigned char type);
	void addNewFile(TCHAR *name,unsigned char type,int meta);
	void addOneDirFile(TCHAR *name,unsigned char type);
	void exchangedDirOrFile();
	void setAsShowDir();
	void setAsShowFile();
	int getShowCout(){return listAmount;};
	ZString getName(int i,unsigned char *bType);
	ZString getFileNameByType(int i,int type);
	TZString getNextFileName();
	TZString getPrevFileName();
	TZString getFileName();
	void startScroll(int i,int type);
	DWORD getTime(int i,int type);


};

#endif STR_FILELIST_H