#include "pub.h"

#include "stdio.h"
#include "stdlib.h"
#include "PNGStruct.h"
#include "msg.h"
#include "pub.h"



int readInt(FILE *fp){
	int n=0;
	unsigned char cc[4];
	DWORD readed;
//	file.read((char*)cc,4);
//	ReadFile(fHandle,cc,4,&readed,0);
	fread(cc,1,4,fp);
	n=cc[0]<<24;
	n+=cc[1]<<1;
	n+=cc[2]<<8;
	n+=cc[3];
	return n;
}



void fillSubNames(PNG_STRUCT&png){
	if(png.nNumberPic>0){
		//png.zhwPartInit.setName(png.getName());
		//png.zhwPartInit.readPartInit();
		png.nNumberPic=0;
	}

}









/*

unsigned char* PNG_STRUCT::getData(){
	if(data!=NULL)
		return data;
	char fileName[100];
	char header[5];
#ifdef WINCE
	sprintf(fileName,"/"ROOT_LOC"/img_work/%s_files/Part_%d",parent->name,picNo);
#else
	sprintf(fileName,"img_work\\%s_files\\Part_%d.zzip",parent->name,picNo);
#endif
	FILE *fp=fopen(fileName,"rb");
	if(fp==NULL)
		return NULL;
	for(int i=0;i<4;i++){
		header[i]=getc(fp);
	}
	header[4]=0;
	if(strcmp(header,"ZHW0")!=0){
		fclose(fp);
		return NULL;
	}

	aliasName=NULL;
	RECT r;
	r.left=readInt(fp);
	r.right=readInt(fp);
	r.top=readInt(fp);
	r.bottom=readInt(fp);
	xLoc=r.left+parent->xLoc;
	yLoc=r.top+parent->yLoc;
	width=r.right-r.left+1;
	height=r.bottom-r.top+1;
	showCondition=parent->showCondition;
	unsigned char*dataTemp=(unsigned char*)zhw_malloc(width*height*4);
	long nCurrent=ftell(fp);
	fseek(fp,0,SEEK_END);
	long nEnd=ftell(fp);
	long pressedSize=nEnd-nCurrent;
	unsigned char*fileData=(unsigned char*)zhw_malloc((int)pressedSize);
	fseek(fp,nCurrent,SEEK_SET);
	fread(fileData,1,pressedSize,fp);
	unsigned long uncomprLen;
	int err = uncompress(dataTemp, &uncomprLen, fileData, pressedSize);
	zhw_free_handle((void**)&fileData);
	data=(unsigned char*)dataTemp;
	bytePerPixel=4;
	fclose(fp);
	return data;
}
*/





void PNG_STRUCT::draw(QPainter *qp){
	//public void draw(Canvas c, int xBegin, int ybegin) {
		// TODO Auto-generated method stub
	//	Paint p = new Paint();
		QImage* bitmap = (QImage*)fetchImageBitmap();
		
		
		if (bitmap != NULL) {
			QRectF qr(0,0,bitmap->width(),bitmap->height());		
			QRectF qrTarget(xLoc,yLoc,bitmap->width(),bitmap->height());
			qp->drawImage(qrTarget,*bitmap,qr);
			// c.drawBitmap(bitmap, xLoc, yLoc+200, p);
			// c.drawBitmap(imageBitmap, 200, 200,p);
		}
	//}
}

void TXT_STRUCT::setTextBeginScroll(DWORD time){
	lBeginScrollTime=time;
	beScrollMe=true;
}
bool debugDrawBox=false;

void TXT_STRUCT::draw(QPainter *qp){
	int size=0;
	if(this->fontSize!=0){
		size=this->fontSize;
	}else{
		size=this->height;
	}

	QFont font("Arial",size,0,false);  
	char *toDraw=name;
	if(this->replaceValue!=NULL){
		toDraw=replaceValue;
	}
	int r=rgb&0xFF;
	int g=(rgb>>8)&0xFF;
	int b=(rgb>>16)&0xff;
	qp->setPen(QColor(r,g,b));//设置画笔颜色为红色  
	qp->setFont(font);
	int fontWidth=qp->fontMetrics().width(toDraw);
	if(layOutMode==MIDDLE){
		int x0=xLoc;
		x0+=((int)width-fontWidth)/2;		
		
		if(debugDrawBox){
			QRectF qrf(xLoc,yLoc,width,fontSize);
			qp->drawRect(qrf); 
		}
		//qp->fillRect(qrf,QBrush::Black);
		qp->drawText(x0,yLoc+fontSize,toDraw);
	}else{
		qp->drawText(xLoc,yLoc+fontSize,toDraw);
	}

	//qp->setco

}
void TXT_STRUCT::setTextBeginScroll(){
	lBeginScrollTime=GetTickCount();
	beScrollMe=true;
}


char *TXT_STRUCT::getShowString(){
	if(IS_RUN_MODE){
		if(replaceValue!=NULL){
			return replaceValue;
		}
	}
	return name;
}


void  PNG_STRUCT::unLoadPNG(){
	if(imageBitmap!=NULL){
		imageBitmap->detach();
	}
	imageBitmap=NULL;
}


void * PNG_STRUCT::fetchImageBitmap(void){
	if (imageBitmap != NULL)
			return imageBitmap;
		// 先读入 ASSSI 文件
		QImage* image = NULL;
		ZString zs("G:\\A7_QT_FROM_WINCE\\WORK_DIR\\png_resource\\");
		zs.cat("img/").cat(name);
		//fileNameNew = fileNameNew.replace('\\', '/');
		image=new QImage;
		if(! (image->load(zs.getData()) ) ) //加载图像
		{
			delete image;
			image=NULL;
			return NULL;
		}
		//return image;

		imageBitmap = image;
		if (imageBitmap == NULL) {
			// return imageBitmap;
			/*
			 * String fileName = IShowCondistionConst.dirBase + name; fileName =
			 * fileName.replace('\\', '/'); if (imageBitmap == null) {
			 * imageBitmap = BitmapFactory.decodeFile(fileName); //
			 * fillSubNames(); }
			 */
		}
		if (imageBitmap != NULL) {
			width = imageBitmap->width();
			height = imageBitmap->height();
		}
	return imageBitmap;
}

#define MAX_X_RANG	80
#define MAX_Y_RANG	60

bool BaseItem::inBox(int x,int y){
	if(getShowCondition()==5)
		return false;
	int pngWidth=getWidth();
	int pngHeight=getHeight();
	int x0=getX();
	int y0=getY();
	//RETAILMSG(1,(L"Find %s %d,%d-%d,%d (x,y)=(%d,%d)\r\n",getTCHAR1_0(tBuf,sizeof(tBuf),this->name),x0,y0,x0+pngWidth,y0+pngWidth,x,y));
	// 避免操作，
	// 最大图标范围 40
	if(actScrnNo==SCRN_MAIN1){
		// MAIN 容易重叠 的部分
		if(pngWidth>MAX_X_RANG){
			int cutOff=(pngWidth-MAX_X_RANG)/2;
			x0+=cutOff;
			pngWidth=MAX_X_RANG;
		}
		if(pngHeight>MAX_Y_RANG){
			int cutOff=(pngHeight-MAX_Y_RANG)/2;
			y0+=cutOff;
			pngHeight=MAX_Y_RANG;
		}
	}
	if(x<x0)
		return false;
	if(x>x0+pngWidth)
		return false;
	if(y<y0)
		return false;
	if(y>y0+pngHeight)
		return false;
	return true;
}
