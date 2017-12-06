#include "pub.h"
#include "math.h"

#include "HzPy.h"
#include "stdio.h"


int HzPySearch::readHz(HZ_MAP&hzMap,unsigned char *hz){
	int begin=0;
	int end=6244;
	unsigned short nShortValue=(hz[0]<<8)+hz[1];
	while(begin<=end){
		int mid=(begin+end)/2;
		fseek(fpPy,sizeof(HZ_MAP)*mid*1L,0);
		HZ_MAP hzMap0;
		fread(&hzMap0,sizeof(HZ_MAP),1,fpPy);
		unsigned short nShortValue1=(hzMap0.cc[0]<<8)+hzMap0.cc[1];
		if(nShortValue1==nShortValue){
			memcpy(&hzMap,&hzMap0,sizeof(hzMap));
			return 1;
		}
		if(nShortValue1>nShortValue){
			end=mid-1;
		}else{
			begin=mid+1;
		}
	}
	return 0;
}

bool HzPySearch::matchAfter(char *str1,char *str2){
	char c=str2[0];
	if(c==0)
		return true;
	int nLen=strlen(str1);
	for(int i=0;i<nLen;i++){
		if(str1[i]>='a'&&(str1[i]<='z')){//转为大写 HSS
			str1[i]-=32;
		}
		if(str1[i]==c){
			if(matchAfter(str1+i+1,str2+1))
				return true;
		}
	}
	return false;
}


static char *mapTable[]={""/*0*/,""/*1*/,"abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};

int getMapNumber(char cs){
	cs=(char)tolower(cs);
	for(int i=0;i<10;i++){
		char *c=mapTable[i];
		for(unsigned int j=0;j<strlen(c);j++){
			if(cs==c[j])
				return i;
		}
	}
	return -1;
}


void HzPySearch::getSearchChars(unsigned char *data,char *searchKey){
	searchKey[0]=0;
	int nLen=strlen((char*)data);
	char ccOne[2];
	ccOne[1]=0;
	for(int i=0;i<nLen;i++){
		if(data[i]>0x80&&data[i+1]>0x80){
			HZ_MAP hzMap;
			if(readHz(hzMap,(unsigned char *)data+i)){
				//zhw_strcat_s(searchKey,100,(char*)hzMap.mapNo);
				zhw_strcat_s(searchKey,100,(char*)hzMap.py);//拼音 hss
			}
			i++;
		}else{
			char c=data[i];
			ccOne[0]=0;// 没有匹配的
			if(c>='0'&&c<='9')
			{
				ccOne[0]=c;
			}else {
				int n=getMapNumber(c);
				if(n!=-1){
					ccOne[0]='0'+n;
				}
			}
			zhw_strcat_s(searchKey,100,ccOne);
		}
	}
}
