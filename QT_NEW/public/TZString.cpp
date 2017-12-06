#include "pub.h"

#include "zstring.h"
#include "tzstring.h"
#include "screenmem.h"
#include "stdio.h"
#include "stdlib.h"

#ifndef WINCE

#endif






TCHAR*zhw_clone_tstr(TCHAR*str);
TZString TZString::convertBig(char *cc){
	TZString tzs;
	//tzs.setCData(cc);
	int n=strlen(cc);
	TCHAR *mm=(TCHAR*)zhw_malloc((n+1)*sizeof(TCHAR));
	if(mm==NULL){
		return tzs;
	}
	for(int i=0;i<n;i++){
		mm[i]=cc[i];
	}
	mm[n]=0;
	tzs.setData(mm);
	ZHW_FREE(mm);
	return tzs;
}

TZString TZString::convert(char *cc){
	TZString tzs;
	tzs.setCData(cc);
	return tzs;
}

TZString TZString::convert(ZString &c){
	TZString tzs;
	tzs.setCData(c);
	return tzs;
}

TZString::TZString(){
//	maxLen=0;
	data=NULL;
}

void TZString::destory(){
#ifdef TEST_DEBUG_TCHAR
	if(data!=NULL)
		fprintf(getTFileHandle(),"free obj[%x] %d\r\n",this,wcslen(data));
	fflush(getTFileHandle());
#endif
	ZHW_FREE(data);
//	maxLen=0;
}

TCHAR *TZString::getData(){
	return data;
}

TZString& TZString::operator=( TZString& zs)
{
	setData(zs.getData());
	return *this;
}

TZString& TZString::operator=( TCHAR*c){
	setData(c);
	return *this;
}

/*
TCHAR *TZString::getDataMinLen(int len){
	if(maxLen>=len)
		return getData();
	TCHAR *newData=(TCHAR*)zhw_malloc(len*sizeof(TCHAR));
	if(newData==NULL){
		maxLen=0;
		return NULL;
	}
	//wcscpy(newData,data);
	destory();
	data=newData;
	maxLen=len;
#ifdef TEST_DEBUG_TCHAR
	fprintf(getTFileHandle(),"malloc obj[%x] %d\r\n",this,maxLen);
	fflush(getTFileHandle());
#endif
	return getData();
}

TZString::TZString(int len){
#ifdef TEST_DEBUG_TCHAR
	fprintf(getTFileHandle(),"malloc obj[%x] %d\r\n",this,len);
	fflush(getTFileHandle());
#endif
	data=(TCHAR*)zhw_malloc(len*sizeof(TCHAR));
	if(data==NULL){
		maxLen=0;
		return;
	}
	data[0]=0;
	maxLen=len;
}
*/


TZString::TZString(const TZString& strSrc){
	//maxLen=0;
	data=NULL;
	setData(strSrc.data);
}

TZString::TZString(TCHAR *c){
	data=NULL;
	data=zhw_clone_tstr(c);
	if(data==NULL)
	{
//		maxLen=0;
		return;
	}
//	maxLen=wcslen(c)+1;
#ifdef TEST_DEBUG_TCHAR
	fprintf(getTFileHandle(),"malloc obj[%x] %d\r\n",this,wcslen(data));
	fflush(getTFileHandle());
#endif
}


TZString::~TZString(){
	destory();
	//ZHW_FREE(data);
}


TZString& TZString::rightTrim(){
	if(data==NULL)
		return *this;
	int n=wcslen(data)-1;
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

void TZString::setAsSub(int len){
	if(data==NULL)
		return;
	int lenOld=wcslen(data);
	if(len>=lenOld)
		return;
	data[len]=0;
}

int TZString::size(){
	if(data==NULL)
		return 0;
	return wcslen(data);
}

/*
void TZString::setSubString(TCHAR *c,int len){
	if(c==NULL||len<0){
		destory();
		return;
	}
	int strLen=wcslen(c);
	if(len>strLen){
		len=strLen;
	}
	TCHAR *newData=(TCHAR*)zhw_malloc((len+1)*sizeof(TCHAR));
	if(newData==NULL){
		maxLen=0;
		return;
	}
	strcpy_s_zhw(newData,len,c);
	destory();
	data=newData;
	maxLen=len+1;
#ifdef TEST_DEBUG_TCHAR
	fprintf(getTFileHandle(),"malloc obj[%x] %d\r\n",this,maxLen);
	fflush(getTFileHandle());
#endif
}

void TZString::setPartData(TCHAR *c,int begin,int end){
	if(begin<0){
		destory();
	}
	setSubString(c+begin,end-begin);
}
*/
void  TZString::setData(TCHAR*c){
	if(c==NULL){
		destory();
		return;
	}
	int n=wcslen(c);
	TCHAR *newData=zhw_clone_tstr(c);
	if(newData==NULL){
//		maxLen=0;
		return;
	}
	destory();
	data=newData;
//	maxLen=wcslen(c)+1;
#ifdef TEST_DEBUG_TCHAR
	fprintf(getTFileHandle(),"malloc obj[%x] %d\r\n",this,wcslen(data));
	fflush(getTFileHandle());
#endif
}


void TZString::setCData(char*c){
	destory();
	if(c==0){
		return;
	}

}

TZString &TZString::cat(TZString&c){
	return cat(c.getData());
}

void TZString::removeEndChar(TCHAR c){
	if(data==NULL)
		return;
	int n=wcslen(data);
	if(n==0)
		return;
	if(data[n-1]==c){
		data[n-1]=0;
	}
}

bool TZString::isEmpty(){
	return data==NULL;
}

TCHAR *TZString::strstr(TCHAR*part){
	if(data==NULL)
		return NULL;
	if(part==NULL)
		return NULL;
	return wcsstr(data,part);
}

bool TZString::startsWith(TCHAR *pref)
{
#ifdef TEST_DEBUG_TCHAR
	fprintf(getTFileHandle(),"start with [%x] %s %s \r\n",this,data,pref);
	fflush(getTFileHandle());
#endif
	if(data==NULL){
#ifdef TEST_DEBUG_TCHAR
		fprintf(getTFileHandle(),"false data is null\r\n");
		fflush(getTFileHandle());
#endif
		return false;
	}
	int len=wcslen(pref);
	if(len>wcslen(data)){
#ifdef TEST_DEBUG_TCHAR
		fprintf(getTFileHandle(),"false pref > data \r\n");
		fflush(getTFileHandle());
#endif
		return false;
	}
	for(int i=0;i<len;i++){
		if(data[i]!=pref[i]){
#ifdef TEST_DEBUG_TCHAR
		fprintf(getTFileHandle(),"false 3\r\n");
		fflush(getTFileHandle());
#endif
			return false;
		}
	}
#ifdef TEST_DEBUG_TCHAR
		fprintf(getTFileHandle(),"TRUE\r\n");
		fflush(getTFileHandle());
#endif
	return true;
}

TZString &TZString::cat(TCHAR*c){
	if(data==NULL){
		//setData(c);
		// 什么也不做
		setData(L"");
		//return *this;
	}
	if(c==NULL){
		return *this;
	}
	// 看空间是否够大
	int n=wcslen(data)+wcslen(c)+1;
	TCHAR *newData=(TCHAR*)zhw_malloc(n*sizeof(TCHAR));
	if(newData==NULL){
		destory();
//		maxLen=0;
		return *this;
	}
	wcscpy(newData,data);
	wcscat(newData,c);
	//maxLen=n;
#ifdef TEST_DEBUG_TCHAR
	//fprintf(getTFileHandle(),"======cat \"%s\"\r\n",c);
	fprintf(getTFileHandle(),"malloc obj[%x] %d\r\n",this,wcslen(data));
	fflush(getTFileHandle());
#endif
	destory();
	data=newData;
	//maxLen=n;
	return *this;
	//ZHW_FREE(newData)
}

TZString TZString::format(TCHAR* pszFormat, ... ){
	//::swprintf(
	TZString tzs;
	va_list argList;
	va_start( argList, pszFormat );
	tzs.formatV( pszFormat, argList );
	va_end( argList );
	return tzs;
}
#define MAX_STR_LEN	0x1000

void TZString::formatV( TCHAR* pszFormat, va_list args )
{
	destory();
	if(pszFormat!=NULL){
		const size_t maxcount = MAX_STR_LEN;
		TCHAR string[MAX_STR_LEN+1];
		//int len = _vsnprintf(string, maxcount, pszFormat, args);
		int len = _vsnwprintf(string, maxcount, pszFormat, args);
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

char*getChar1_0(char *buf,int len,TCHAR*toDraw);
void sendBySerial(char *);
#define MAX_STR_LEN_RETAIL	1000
void toSerialPrintV(TCHAR* pszFormat, va_list args ){
	if(pszFormat!=NULL){
		const size_t maxcount = MAX_STR_LEN_RETAIL;
		TCHAR string[MAX_STR_LEN_RETAIL+1];
		//int len = _vsnprintf(string, maxcount, pszFormat, args);
		int len = _vsnwprintf(string, maxcount, pszFormat, args);
		// _vsnprintf returns -1 if buffer is not big enough (or an error occurs)
		if(len < 0)
		{
			// null terminate the string
			// note that maximum size is 1024 characters plus terminating null.
			string[len = maxcount] = 0;
		}
		//setData(string);
		RETAILMSG(1,(L"%s",string));
		// send to 串口
		char cBuffer[MAX_STR_LEN_RETAIL*2];
		getChar1_0(cBuffer,MAX_STR_LEN_RETAIL*2,string);
		//sendBySerial(cBuffer);
	}
}
int seh_filera(int code,struct _EXCEPTION_POINTERS *infor,int module){
	return 1;	
}
void toSerialPrint(TCHAR* pszFormat, ... ){
	va_list argList;
	va_start( argList, pszFormat );
	try{
		toSerialPrintV( pszFormat, argList );
	}catch(...)
	{
		//
		//RETAILMSG(1,(L" sendStartUpCmd MEE A EXCEPTION \r\n"));
	}
	
	va_end( argList );
}

	/////////// CAT FORMAT 
	 void TZString::setChar(int n,TCHAR c){
		 if(data==NULL)
			 return;
		 if(n>=wcslen(data))
			 return;
		 data[n]=c;
	 }
	 //////////
	
	//重载=操作符，一般=操作符和拷贝构造函数是成对出现的。

	

	 TCHAR TZString::operator[](int nIndex){
		 if(data==NULL){
			 return 0;
		 }
		 if(nIndex>=wcslen(data)){
			 return 0;
		 }
		 return data[nIndex];
	 }


	void TZString::operator+=(TCHAR*data){
		cat(data);
	}
	void TZString::operator+=(TZString& zs){
		cat(zs.getData());
	}



	bool TZString::compare(TCHAR *compareData) {
		if(this->data==NULL){
			if(compareData==NULL){
				return true;
			}
			return false;
		}
		if(compareData==NULL){
			return false;
		}
		return wcscmp(getData(),compareData)==0;
	}

	bool TZString::operator==( TCHAR*c) {
		return compare(c);
	}


	bool TZString::operator==( TZString& cEqual) {
		return compare(cEqual.getData());
	}

	
	bool TZString::operator!=( TZString& cEqual) {
		return !compare(cEqual.getData());
	}
	



	
#ifdef TEST_DEBUG_TCHAR

static TZString getACString(){
	TZString c=L"AAAA";
	return c;
}

static void ttestBase1(){

	TZString za(L"aa");

	za.cat(za);
	za.cat(za.getData());

	za.cat(za.getData()+3);


	TZString zs;
	//fflush(getTFileHandle());
	//zs.cat("old active png is ").cat("3000").cat("-----------------1123232 3232  --- \r\n");

	zs=getACString();
	
	zs+=10;
	zs+=L"all right";
	fprintf(getTFileHandle(),"======cat \"%s\"\r\n",zs.getData());
	fflush(getTFileHandle());

	zs=L"";

	zs=zs+L"abcdefg "+L" all right long "+getACString();
	fprintf(getTFileHandle(),"======cat \"%s\"\r\n",zs.getData());
	fflush(getTFileHandle());

}

static void testBase2(){
	TZString s(L"AB");
	TZString s1;
	s1.startsWith(L"A");
	s1.startsWith(L"AB");
	s.startsWith(L"A");
	s.startsWith(L"AB");
	s.startsWith(L"ABC");
}





void selfTZStringTest(){
	//TZString before;
	//before=getACString();
	ttestBase1();
	//testBase2();
	//ttestBase3();
	//ttestBase4();


}
#endif
