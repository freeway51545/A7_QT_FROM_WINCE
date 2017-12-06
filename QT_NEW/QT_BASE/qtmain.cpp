
#include <QtGui>

#include "window_temp.h"

#include "mainwindow.h"

#include "PaintedWidget.h"
void initWINCEEntery();


//QWidget *wParent;
QMainWindow *qmw;
void initWindow();
//moc PaintedWidget.h -o moc_PaintedWidget.cpp
//moc button.h -o moc_youfilename.cpp


/////// https://wenku.baidu.com/view/95f916c708a1284ac850432a.html
//  GStreamer


// …Ë÷√ audio equalizer 

// Linux Audio Subsystem …Ë÷√“Ù–ß

// 

void traslateMsgPressingM();
void Sleep(int ms);
void sendOne10PSMesage();
class TimmerThread:public QThread
{
protected:
    void  run();
};

void TimmerThread::run(){
	while(true){
		Sleep(100);
		//run();
		sendOne10PSMesage();	
		traslateMsgPressingM();
	}
}

int main(int argc, char *argv[]) 
{ 
		TimmerThread tt;
        QApplication app(argc, argv); 
		MainWindow mw;
		qmw=&mw;
		//PaintedWidget w; 
		//mw.setCentralWidget(&w);
        //wParent=&w;
		initWindow();
		initWINCEEntery();
		tt.start();
		mw.show(); 
        return app.exec(); 
}