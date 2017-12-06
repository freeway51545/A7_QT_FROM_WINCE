#ifndef HZPY_H
#define HZPY_H
typedef struct _cc{
	unsigned char cc[2];
	unsigned char py[6];
	unsigned char mapNo[6];
}HZ_MAP;

class HzPySearch{
	FILE*fpPy;
public:
	int readHz(HZ_MAP&hzMap,unsigned char *hz);
	bool matchAfter(char *str1,char *str2);
	void search(char *searchStr);
	void getSearchChars(unsigned char *data,char *searchKey);
};
#endif