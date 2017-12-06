#ifndef		TZString_h
#define 	TZString_h

class ZString;

class TZString{
private:
	TCHAR *data;
	//int maxLen;
public:
	DWORD dTimeToScroll;
	bool beScrollMe;
	void beginScrollMe(){
		if(beScrollMe){
			return;
		}
		beScrollMe=true;
		dTimeToScroll=GetTickCount();
	}
	TZString();
	//TZString(int len);
	TZString(TCHAR *c);
	TZString(const TZString& strSrc );
	bool isEmpty();
	void TZString::removeEndChar(TCHAR c);
	int size();
	void setAsSub(int len);
	~TZString();
	TCHAR *getData();
	TCHAR *getDataMinLen(int len);
	void destory();
	void setData(TCHAR*c);
	void setCData(char*c);
	void setPartData(TCHAR *,int begin ,int end);
	void setSubString(TCHAR *,int len);
	TZString &cat(TCHAR*c);
	bool startsWith(TCHAR *pref);
	TCHAR *strstr(TCHAR*part);
	TZString &cat(TZString&c);
	
	//TZString &catFormat(TCHAR*format,int data);
	//TZString &catFormat(TCHAR*format,double data);
	//TZString &catFormat(TCHAR*format,float data);
	//TZString &catFormat(TCHAR*format,DWORD data);
	//TZString &catFormat(TCHAR*format,unsigned int data);
	//TZString &format(TCHAR*format,int data);
	//TZString &format(TCHAR*format,double data);
	//TZString &format(TCHAR*format,float data);
	//TZString &format(TCHAR*format,DWORD data);
	//TZString &format(TCHAR*format,unsigned int data);
	
	void formatV( TCHAR* pszFormat, va_list args );
	TZString format(TCHAR* pszFormat, ... );
	//+=

	void setChar(int n,TCHAR c);
	//重载=操作符，一般=操作符和拷贝构造函数是成对出现的。
	
	TZString& operator=( TZString& zs);
	TZString& operator=( TCHAR*);
	static TZString convert(ZString &c);
	static TZString convert(char *);
	static TZString convertBig(char *);
	///////// OPERATOR
	TCHAR operator[](int nIndex);
	TZString& operator+(TCHAR*);
	TZString& operator+(TZString& zs);
	TZString& operator+(int);
	TZString& operator+(float);
	TZString& operator+(double);
	void operator+=(TCHAR*);
	void operator+=(TZString& zs);
	void operator+=(int);
	void operator+=(float);
	void operator+=(double);
	


	bool operator==( TZString& cEqual) ;
	bool operator==( TCHAR*) ;
	friend bool operator ==(TCHAR *c,  TZString& cEqual){
		cEqual.compare(c);
	};
	bool operator!=( TZString& cEqual) ;
	friend bool operator !=(TCHAR *,  TZString& cEqual);
	bool compare(TCHAR *compareData) ;
	friend bool operator !=(TCHAR *c,  TZString& cEqual){
		return cEqual.compare(c);
	};
	operator TCHAR*() { return getData(); };
	TZString& rightTrim();
};


#endif