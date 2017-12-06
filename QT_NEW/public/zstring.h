#ifndef		ZString_h
#define 	ZString_h

#include "pubtype.h"

class TZString;

class ZString{
private:
	char *data;
	int maxLen;
	void formatV( char* pszFormat, va_list args );
	void setData(char*c);
public:
	ZString();
	//ZString(char* pszFormat, ... );

	DWORD dTimeToScroll;
	bool beScrollMe;
	void beginScrollMe(){
		if(beScrollMe){
			return;
		}
		beScrollMe=true;
		dTimeToScroll=GetTickCount();
	}
	ZString(int toCovert);
	ZString(const ZString& strSrc );
	ZString(char*c);
	ZString(TCHAR*c);
	bool isEmpty();
	void removeEndChar(char c);
	int size();
	inline int length(){return size();};
	~ZString();
	char *getData();
	//char *getDataMinLen(int len);
	void destory();
	void upper();
	bool endsWith(char*c2);
	void setPartData(char *,int begin ,int end);
	void setSubString(char *,int len);
	ZString &cat(char*c);
	ZString &append(char*c);
	bool startsWith(char *pref);
	char *strstr(char*part);
	inline ZString &cat(ZString&c){cat(c.getData());return *this;};
	/* */
	ZString &catFormat(char* pszFormat, ... );
	ZString &format(char* pszFormat, ... );
	static ZString Format(char* pszFormat, ... );

	//+=
	void setChar(int n,char c);
	//重载=操作符，一般=操作符和拷贝构造函数是成对出现的。
	ZString& operator=( ZString& zs);
	ZString& operator=( char*);
	ZString& operator=( TCHAR*);

	///////// OPERATOR
	char operator[](int nIndex);
	inline ZString& operator+(char*c){cat(c);return *this;};
	inline ZString& operator+(ZString& zs){cat(zs);return *this;};
	inline ZString& operator+(int i){catFormat("%d",i);return *this;};
	inline ZString& operator+(float f){catFormat("%f",f);return *this;};
	inline ZString& operator+(double d){catFormat("%f",d);return *this;};
	inline void operator+=(char*c){cat(c);};
	inline void operator+=(ZString& zs){cat(zs);};
	inline void operator+=(int n){catFormat("%d",n);};
	inline void operator+=(float f){catFormat("%f",f);};
	inline void operator+=(double d){catFormat("%f",d);};
	bool compare(char *compareData) ;
	inline bool operator==(char*c ){return compare(c);};
	inline bool operator==( ZString& cEqual){return compare(cEqual.getData());};
	friend bool operator ==(char *c,  ZString& cEqual){
		cEqual.compare(c);
	};
	friend bool operator ==(  ZString& cEqual,const char *c){
		return cEqual.compare((char*)c);
	};
	bool operator!=( ZString& cEqual) ;
	friend bool operator !=(char *,  ZString& cEqual);
	friend bool operator !=(char *c,  ZString& cEqual){
		return cEqual.compare(c);
	};
	operator char*() { return getData(); };
	ZString& rightTrim();
	TZString getTChar();
	int getInt();
};



class StringToken{
private:
	char *data;
	char *brek;
	int breakLen;
	int nCurrentLoc;
	bool beGotOver;
private:
	StringToken(){
		data=NULL;
		brek=NULL;
		breakLen=NULL;
		nCurrentLoc=0;
	}
public:
	StringToken(char *init,char *brek);
	ZString next();
	~StringToken();
};



#endif