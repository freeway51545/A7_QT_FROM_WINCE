#include "pub.h"
#include "zstring.h"
#include "stdio.h"
#include "stdlib.h"
#include "tzstring.h"

#ifndef WINCE
//#define TEST_DEBUG
#endif

#ifdef TEST_DEBUG
FILE *fpThis=NULL;

FILE *getFileHandle(){
	if(fpThis==NULL){
		fpThis=fopen("d:\\aa.txt","wb");
	}
	return fpThis;
}

#endif




ZString &ZString::format(char* pszFormat, ... ){
	va_list argList;
	va_start( argList, pszFormat );
	formatV( pszFormat, argList );
	va_end( argList );
	return *this;
}


#define MAX_STR_LEN	0x1000

void ZString::formatV( char* pszFormat, va_list args )
{
	destory();
	if(pszFormat!=NULL){
		const size_t maxcount = MAX_STR_LEN;
		char string[MAX_STR_LEN+1];
		int len = _vsnprintf(string, maxcount, pszFormat, args);
		// _vsnprintf returns -1 if buffer is not big enough (or an error occurs)
		if(len < 0)
		{
			// null terminate the string
			// note that maximum size is 1024 characters plus terminating null.
			string[len = maxcount] = 0;
		}
		setData(string);
	}
}


ZString::ZString(){
	maxLen=0;
	data=NULL;
}

void ZString::destory(){
#ifdef TEST_DEBUG
	if(data!=NULL)
		fprintf(getFileHandle(),"free obj[%x] %d\r\n",this,strlen(data));
	fflush(getFileHandle());
#endif
	ZHW_FREE(data);
	maxLen=0;
}

char *ZString::getData(){
	return data;
}

#define TO_UPPER(c1) ((c1>='a'&&c1<='z')? c1-'a'+'A':c1)


bool endsWith(char*c1,char*c2);


bool ZString::endsWith(char*c2){
	return ::endsWith(data,c2);
}

void ZString::upper(){
	if(data==NULL)
		return;
	int len=strlen(data);
	for(int i=0;i<len;i++){
		data[i]=TO_UPPER(data[i]);
	}
}

  ZString& ZString::operator=( ZString& zs)
{
	if(this==&zs){
		return *this;
	}
	//dstory();
	//data=NULL;
	//maxLen=0;
	setData(zs.getData());
	return *this;
}

char*getChar1_0(char *buf,int len,TCHAR*toDraw);
ZString& ZString::operator=(TCHAR*c)
{
	char buffer[1000];
	getChar1_0(buffer,1000,c);
	setData(buffer);
	return *this;
}

ZString& ZString::operator=( char*c){
	setData(c);
	return *this;
}

/*
char *ZString::getDataMinLen(int len){
	if(maxLen>=len)
		return getData();
	char *newData=(char*)zhw_malloc(len);
	if(newData==NULL){
		maxLen=0;
		return NULL;
	}
	strcpy(newData,data);
	destory();
	data=newData;
	maxLen=len;
#ifdef TEST_DEBUG
	fprintf(getFileHandle(),"malloc obj[%x] %d\r\n",this,maxLen);
	fflush(getFileHandle());
#endif
	return getData();
}
* /

ZString::ZString(int len){
#ifdef TEST_DEBUG
	fprintf(getFileHandle(),"malloc obj[%x] %d\r\n",this,len);
	fflush(getFileHandle());
#endif
	data=(char*)zhw_malloc(len);
	if(data==NULL){
		maxLen=0;
		return;
	}
	data[0]=0;
	maxLen=len;
}
*/


ZString::ZString(const ZString& strSrc){
	maxLen=0;
	data=NULL;
	setData(strSrc.data);
}
ZString::ZString(int toCovert){
	maxLen=0;
	data=NULL;
	format("%d",toCovert);
}
/*
ZString::ZString(char *pszFormat, ... ){
	maxLen=0;
	data=NULL;
	if(pszFormat!=NULL){
		va_list argList;
		va_start( argList, pszFormat );
		formatV( pszFormat, argList );
		va_end( argList );
	}
}
*/
ZString::ZString(char *c){
	maxLen=0;
	data=NULL;
	setData(c);
}

ZString::ZString(TCHAR *c){
	maxLen=0;
	data=NULL;
	char buffer[5000];
	getChar1_0(buffer,5000,c);
	setData(buffer);
}



ZString ZString::Format(char* pszFormat, ... ){
	ZString zs;
	va_list argList;
	va_start( argList, pszFormat );
	zs.formatV( pszFormat, argList );
	va_end( argList );
	return zs;
}
/*

ZString::ZString(char *f,int toCovert,int toCovert2){
	maxLen=0;
	data=NULL;
	format(f,toCovert,toCovert2);
}

ZString::ZString(char *f,int toCovert){
	maxLen=0;
	data=NULL;
	format(f,toCovert);
}

ZString::ZString(int toCovert){
	maxLen=0;
	data=NULL;
	format("%d",toCovert);
}
*/
/*
ZString::ZString(char *c){
	maxLen=0;
	data=NULL;
	setData(c);
}
*/

ZString::~ZString(){
	destory();
	//ZHW_FREE(data);
}
/*
TZString ZString::getTChar(){
	TZString tzs;
	if(data==NULL){
		return tzs;
	}
	tsz.setData(getData());
	return tzs;
}
*/
ZString& ZString::rightTrim(){
	if(data==NULL)
		return *this;
	int n=strlen(data)-1;
	while(n>=0){
		if(data[n]==' ')	  {data[n]=0;}
		else if(data[n]=='\r'){data[n]=0;}
		else if(data[n]=='\n'){data[n]=0;}
		else{
			break;
		}
		n--;
	}
	return *this;
}

int ZString::size(){
	if(data==NULL)
		return 0;
	return strlen(data);
}

int ZString::getInt(){
	int n;
	if(data==NULL)
		return -1;
	sscanf(data,"%d",&n);
	return n;
}

void strcpy_s_zhw(char *buffer,int lenToCopy,char *sss);

void ZString::setSubString(char *c,int len){
	if(c==NULL||len<0){
		destory();
		return;
	}
	int strLen=strlen(c);
	if(len>strLen){
		len=strLen;
	}
	int toMalloc=len+1;
	if(toMalloc<100){
		toMalloc=100;
	}
	char *newData=(char*)zhw_malloc(toMalloc);
	if(newData==NULL){
#ifdef WINCE
		RETAILMSG_DC(1,(L"zhw_malloc false in setSubString\r\n"));
#endif
		destory();
		maxLen=0;
		return;
	}
	strcpy_s_zhw(newData,len,c);
	destory();
	data=newData;
	maxLen=toMalloc;
#ifdef TEST_DEBUG
	fprintf(getFileHandle(),"malloc obj[%x] %d\r\n",this,strlen(data));
	fflush(getFileHandle());
#endif
}

void ZString::setPartData(char *c,int begin,int end){
	if(begin<0){
		destory();
	}
	setSubString(c+begin,end-begin);
}

void  ZString::setData(char*c){
	if(c==NULL){
		destory();
		return;
	}
	bool beNeedReMalloc=false;
	int toMalloc=strlen(c)+1;
	if(data==NULL){
		beNeedReMalloc=true;
	}
	if(toMalloc>maxLen){
		beNeedReMalloc=true;
	}
	if(c>=data&&c<=data+maxLen){
		// 是自己的字符串
		beNeedReMalloc=true;
	}
	if(maxLen>1000&&maxLen>toMalloc/3){
		// 太多剩余空间
		beNeedReMalloc=true;
	}
	if(!beNeedReMalloc){
		strcpy(data,c);
		return;
	}

	//int toMalloc=n+1;
	if(toMalloc<100){
		toMalloc=100;
	}
	char *newData=(char*)zhw_malloc(toMalloc);
	if(newData==NULL){
#ifdef WINCE
		RETAILMSG_DC(1,(L"zhw_malloc false in setData\r\n"));
#endif
		destory();
		return;
	}
	destory();
	strcpy(newData,c);
	data=newData;
	maxLen=toMalloc;
#ifdef TEST_DEBUG
	fprintf(getFileHandle(),"malloc obj[%x] %d\r\n",this,strlen(data));
	fflush(getFileHandle());
#endif
}



void ZString::removeEndChar(char c){
	if(data==NULL)
		return;
	int n=strlen(data);
	if(n==0)
		return;
	if(data[n-1]==c){
		data[n-1]=0;
	}
}

bool ZString::isEmpty(){
	return data==NULL;
}

char *ZString::strstr(char*part){
	if(data==NULL)
		return NULL;
	if(part==NULL)
		return NULL;
	return ::strstr(data,part);
}

bool ZString::startsWith(char *pref)
{
#ifdef TEST_DEBUG
	fprintf(getFileHandle(),"start with [%x] %s %s \r\n",this,data,pref);
	fflush(getFileHandle());
#endif
	if(data==NULL){
#ifdef TEST_DEBUG
		fprintf(getFileHandle(),"false data is null\r\n");
		fflush(getFileHandle());
#endif
		return false;
	}
	int len=strlen(pref);
	if(len>strlen(data)){
#ifdef TEST_DEBUG
		fprintf(getFileHandle(),"false pref > data \r\n");
		fflush(getFileHandle());
#endif
		return false;
	}
	for(int i=0;i<len;i++){
		if(data[i]!=pref[i]){
#ifdef TEST_DEBUG
		fprintf(getFileHandle(),"false 3\r\n");
		fflush(getFileHandle());
#endif
			return false;
		}
	}
#ifdef TEST_DEBUG
		fprintf(getFileHandle(),"TRUE\r\n");
		fflush(getFileHandle());
#endif
	return true;
}

ZString &ZString::cat(char*c){
	if(c==NULL){
		return *this;
	}
	if(data==NULL){
		//setData(c);
		// 什么也不做
		setData("");
		//return *this;
	}
	// 看空间是否够大
	int n=strlen(data)+strlen(c)+1;
	bool beNeedReMalloc=false;
	if(n>maxLen){
		beNeedReMalloc=true;
	}
	if(c>=data&&c<=data+maxLen){
		// 是自己的字符串
		beNeedReMalloc=true;
	}
	if(maxLen>1000&&maxLen>n/3){
		// 太多剩余空间
		beNeedReMalloc=true;
	}
	if(!beNeedReMalloc){
		strcat(data,c);
		return *this;
	}
	if(n<100){
		n=100;
	}
	int nToMalloc=n*2;// 2倍的空间
	char *newData=(char*)zhw_malloc(nToMalloc);
	if(newData==NULL){
#ifdef WINCE
		RETAILMSG_DC(1,(L"zhw_malloc false in cat\r\n"));
#endif
		destory();
		maxLen=0;
		return *this;
	}
	strcpy(newData,data);
	strcat(newData,c);
#ifdef TEST_DEBUG
	fprintf(getFileHandle(),"======cat \"%s\"\r\n",c);
	fprintf(getFileHandle(),"malloc obj[%x] %d\r\n",this,maxLen);
	fflush(getFileHandle());
#endif
	destory();
	data=newData;
	maxLen=nToMalloc;
	return *this;
	//ZHW_FREE(newData)
}

	/////////// CAT FORMAT 
	 void ZString::setChar(int n,char c){
		 if(data==NULL)
			 return;
		 if(n>=strlen(data))
			 return;
		 data[n]=c;
	 }
	 //////////
	 ZString &ZString::catFormat(char* pszFormat, ... ){
			ZString newZs;
		 	va_list argList;
			va_start( argList, pszFormat );
			newZs.formatV( pszFormat, argList );
			va_end( argList );
			this->cat(newZs);
			return *this;
	 }

	 char ZString::operator[](int nIndex){
		 if(data==NULL){
			 return 0;
		 }
		 if(nIndex>=strlen(data)){
			 return 0;
		 }
		 return data[nIndex];
	 }
	
TZString ZString::getTChar(){
	TZString tzs;
	tzs.setCData(this->getData());
	return tzs;
}

	bool ZString::compare(char *compareData) {
		if(this->data==NULL){
			if(compareData==NULL){
				return true;
			}
			return false;
		}
		if(compareData==NULL){
			return false;
		}
		return strcmp(getData(),compareData)==0;
	}
	/*
	bool ZString::operator==( char*c) {
		return compare(c);
	}


	bool ZString::operator==( ZString& cEqual) {
		return compare(cEqual.getData());
	}
	*/
	
	bool ZString::operator!=( ZString& cEqual) {
		return !compare(cEqual.getData());
	}
	



StringToken::~StringToken(){

}
StringToken::StringToken(char *init,char *brekSet){
	data=init;
	brek=brekSet;
	breakLen=strlen(brek);
	nCurrentLoc=0;
	beGotOver=false;
}

ZString StringToken::next(){
	ZString zs((char*)NULL);
	if(beGotOver){
		return zs;	
	}
	if(data==NULL)
		return zs;
	int strLen=strlen(data);
	if(nCurrentLoc>=strLen){
		zs="";
		beGotOver=true;
		return zs;
	}
	int begin=nCurrentLoc;
	for(;nCurrentLoc<strLen;nCurrentLoc++){
		bool beMatched=false;
		for(int i=0;i<breakLen;i++){
			if(data[nCurrentLoc]==brek[i]){
				beMatched=true;
				break;
			}
		}
		if(beMatched){
			// COPY FROM BEGIN TO nCurrentLoc;
			zs.setPartData(data,begin,nCurrentLoc);
			// 从下一个字符开始
			nCurrentLoc++;
			beGotOver=false;
			return zs;
		}
	}
	zs.setPartData(data,begin,nCurrentLoc);
	beGotOver=true;
	return zs;
}
	



#ifdef TEST_DEBUG

ZString getACString(){
	ZString c="AAAA";
	return c;
}
void   heapdump(   HWND hwnd ,char *fileName  ) ;
void testBase1(){
	{
		ZString za("aa");

		ZString zk=za;

		za.cat(za);
		za.cat(za.getData());

		za.cat(za.getData()+3);

		//heapdump(0,"f:/heap_init.txt");
		
		//fflush(getFileHandle());
		//zs.cat("old active png is ").cat("3000").cat("-----------------1123232 3232  --- \r\n");
	}
	{
		ZString zs=getACString();
		
		zs+=10;
		zs+="all right";
		fprintf(getFileHandle(),"======cat \"%s\"\r\n",zs.getData());
		fflush(getFileHandle());

		zs="";

		zs=zs+"abcdefg "+" all right long "+getACString();
		fprintf(getFileHandle(),"======cat \"%s\"\r\n",zs.getData());
		fflush(getFileHandle());
		//heapdump(0,"f:/heap_init.txt");
	}

}

void testBase2(){
	ZString s("AB");
	ZString s1;
	s1.startsWith("A");
	s1.startsWith("AB");
	s.startsWith("A");
	s.startsWith("AB");
	s.startsWith("ABC");
}

void testBase3(){
	StringToken st("ABCDE.1 2 3     ,4 5        ,6 7",",.");
	ZString zs=st.next();
	zs.rightTrim();
	zs=st.next();
	zs.rightTrim();
	zs=st.next();
	zs.rightTrim();
	zs=st.next();
	zs.rightTrim();
	zs=st.next();
	zs.rightTrim();
}

void testBase4(){
	StringToken st("[INFOR]WAINTFOR:CMD-VGQ\n","\r\n");
#ifdef TEST_DEBUG
	fprintf(getFileHandle(),"found ======print %s\r\n",st.next().getData());
	fprintf(getFileHandle(),"found ======print %s\r\n",st.next().getData());
	fprintf(getFileHandle(),"found ======print %s\r\n",st.next().getData());
	fprintf(getFileHandle(),"found ======print %s\r\n",st.next().getData());
	fflush(getFileHandle());
#endif
}

void testBase5(){
	ZString ss("[cd_type_loaded]1\n aa ,Out,\n");
	char *s1=strstr(ss,",Out,\n");
	if(s1!=NULL){
		ss=ZString(s1+2);
	}
#ifdef TEST_DEBUG
	fprintf(getFileHandle(),"found ======print %s\r\n",(char*)ss);
	fflush(getFileHandle());
#endif
}

extern 	int nMalloced;
void selfZStringTest(){
	//heapdump(0,"f:/heap_init0.txt");
	//ZString before;
	//before=getACString();
#ifdef TEST_DEBUG
	fprintf(getFileHandle(),"nMalloced= %d\r\n",nMalloced);
	fflush(getFileHandle());
#endif

	//heapdump(0,"f:/heap_init.txt");

	testBase1();
#ifdef TEST_DEBUG
	fprintf(getFileHandle(),"nMalloced after1= %d\r\n",nMalloced);
	fflush(getFileHandle());
#endif
	//testBase2();
	testBase3();
#ifdef TEST_DEBUG
	fprintf(getFileHandle(),"nMalloced after2= %d\r\n",nMalloced);
	fflush(getFileHandle());
#endif
	testBase4();
#ifdef TEST_DEBUG
	fprintf(getFileHandle(),"nMalloced after3= %d\r\n",nMalloced);
	fflush(getFileHandle());
#endif
	testBase5();
#ifdef TEST_DEBUG
	fprintf(getFileHandle(),"nMalloced after4= %d\r\n",nMalloced);
	fflush(getFileHandle());

//	fprintf(getFileHandle(),"work %s\r\n",buffer);
	fflush(getFileHandle());
#endif
	//heapdump(0,"f:/heap_initf.txt");

}
#endif