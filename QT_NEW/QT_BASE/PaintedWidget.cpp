#include <QtGui>
#include "PaintedWidget.h"
#include "basestateeventitem2.h"


QPainter *qpThis;

QPaintEvent *pwThisEvent;

PaintedWidget::PaintedWidget(BaseStateEventItemV2 *b){
		pBined=b;
        resize(1024, 600); 
        setWindowTitle(tr("Paint Demo")); 
//		makeListView();
}
QImage *grayImg=NULL;
unsigned char *graydata=NULL;
int width=800;//ͼ���
int height=480;//ͼ���
int bytePerLine=( width * 32 + 31 )/32 * 4;;//ͼ��ÿ���ֽڶ���
static int n;
void changedData(){
	unsigned char r=0,g=0,b=0;
	for (int i=0;i<height;i++)
	{
		for (int j=0;j<width;j++)
		{
			r = j+n;
			//g = i+n;
			//b = i+n;

			graydata[i*bytePerLine+j*4]  =0;
			graydata[i*bytePerLine+j*4+1]=0;
			graydata[i*bytePerLine+j*4+2]=0;

//			data+=4;
		}
	}
	
}

QImage *getImage(){
	n++;
	if(grayImg!=NULL){
		changedData();
		return grayImg;
	}
	graydata=new unsigned char[bytePerLine*height];//�洢����������
	changedData();
	grayImg=new QImage(graydata,width,height,bytePerLine,QImage::Format_RGB32);
	return grayImg;
}


//Ȼ����run�������棨ʵ������ָ���κ�����Ҫ�͸��߳̽���ͨ�ŵĵط����������Ϊ������run�����ڲ��ˣ�ͨ����

#include "pub.h"
#include "ZMyMessage.h"
#include "BaseStateEventItem2.h"
ZMyMessage *zmm;
//extern BaseStateEventItemV1 *activeBsei;
extern BaseStateEventItemV2 *activeBsei;
void PostMessageZhw(WPARAM msgId,LPARAM lparam){	
	zmm=new ZMyMessage(MyEvent,msgId,lparam);
	if(activeBsei!=NULL){
		QApplication::postEvent(activeBsei->getPaintedWidget(), zmm);
	}
//	delete zmm;
}
void redraw(){
	activeBsei->redraw();
}
void sendOne10PSMesage(void){
	PostMessageZhw(_TIMMER_10PS,0);
}




void processMouseEvent(BaseStateEventItemV2*pBined,QEvent*event);

void PaintedWidget::mousePressEvent(QMouseEvent*event){
	processMouseEvent(pBined,event);
}
void PaintedWidget::mouseMoveEvent(QMouseEvent*event){
	processMouseEvent(pBined,event);
};//�����ƶ�  
void PaintedWidget::mouseReleaseEvent(QMouseEvent*event){
	processMouseEvent(pBined,event);
};//�ɿ�  

QListView* listView=NULL;



void PaintedWidget::itemClicked(const QModelIndex &index){
//	k11++;
}


void PaintedWidget::pointClicked(){
//	k11++;
}


bool PaintedWidget::event(QEvent*ev){
	//processMouseEvent(ev);
	if(ev->type()==MyEvent){
		//delete ev;
		pBined->activeTraslateMsg(ev);
		return 1;
	}
	return QWidget::event(ev);
};//�ɿ�  



void PaintedWidget::paintEvent(QPaintEvent *event) 
{ 
        QPainter painter(this); 
		qpThis=&painter;
		pwThisEvent=event;
		QRectF qr(0,0,1024,600);
		//painter.drawImage(qr,*getImage(),qr);
		//void drawCurrentView();
		//drawCurrentView();
		pBined->drawBackGround(qpThis);
		pBined->drawOnScreen(qpThis);
		qpThis=NULL;
		pwThisEvent=NULL;
		/*
        painter.drawLine(80, 100, 650, 500); 
        painter.setPen(Qt::red); 
        painter.drawRect(10, 10, 100, 400); 
        painter.setPen(QPen(Qt::green, 5)); 
        painter.setBrush(Qt::blue); 
        painter.drawEllipse(50, 150, 400, 200); 
		*/
}

#include "pub.h"

void updateShowRect(unsigned char *workBuf,RECT rChangedRect){
	if(qpThis==NULL){
		return;
	}
	int pLine=(1024* 32 + 31 )/32 * 4;;//ͼ��ÿ���ֽڶ���
	QRectF qr(0,0,1024,600);
	QImage	*grayImg1=new QImage(workBuf,width,height,bytePerLine,QImage::Format_RGB32);
	qpThis->drawImage(qr,*grayImg1,qr);
}