/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtGui>

#include "mainwindow.h"


//! [0]
MainWindow *mwThis=NULL;
MainWindow::MainWindow()
{
    resize(1024, 600);
	 //设置窗口的图标和名称
    mwThis=this;
}
//! [0]
#include <qpushbutton.h>



//extern QWidget *wParent;
QPushButton*btnc;
bool beHide=false;

 
class QPushButton0:public QPushButton{
	QDialog *dialog;
	public:
		QPushButton0(const QString &text, QWidget *parent=0):QPushButton(text,parent){
			dialog=NULL;
		}
	void mousePressEvent(QMouseEvent *e)  
	{  
		//效果1实现代码  
		//exit(0);
		QMessageBox msgBox;
		msgBox.setText(tr("The document has been modified."));
		msgBox.setInformativeText(tr("Do you want to save your changes?"));
		//msgBox.setDetailedText(tr("Differences here..."));
		msgBox.setStandardButtons(QMessageBox::Save
								  | QMessageBox::Discard
								  | QMessageBox::Cancel);
		msgBox.setDefaultButton(QMessageBox::Save);
		int ret = msgBox.exec();
		switch (ret) {
		case QMessageBox::Save:
			qDebug() << "Save document!";
			break;
		case QMessageBox::Discard:
			qDebug() << "Discard changes!";
			break;
		case QMessageBox::Cancel:
			qDebug() << "Close document!";
			break;
		}
		if(1)
			return;
		if (QMessageBox::Yes == QMessageBox::question(this,
													  tr("Question"),
													  tr("Are you OK?"),
													  QMessageBox::Yes | QMessageBox::No,
													  QMessageBox::Yes)) {
			QMessageBox::information(this, tr("Hmmm..."), tr("I'm glad to hear that!"));
		} else {
			QMessageBox::information(this, tr("Hmmm..."), tr("I'm sorry!"));
		}
		if(1)
			return;
		if(dialog==NULL){
			dialog=new QDialog (this);
		}
		dialog->setWindowTitle(tr("Hello, dialog!"));
		dialog->show();
		if(1)
			return;
		/*
		if(btnc==NULL){
			btnc=new QPushButton0(QObject::tr("rmvb2"),wParent);

			btnc->setGeometry(200,300,40,20);
		}
		if(beHide){
			btnc->hide();
		}else{
			btnc->show();
		}
		beHide=!beHide;
		//btnc->hide();
//		wParent->setParent(mwThis);
*/
	}  
	  
	void mouseReleaseEvent(QMouseEvent *e)  
	{  
		//exit(1);
	}  
};




	
QScrollBar *qsb1=NULL,*qsb2=NULL;

void addScrollBar(QWidget *pWidget){
	if(qsb1==NULL){
		qsb1=new QScrollBar();
		qsb1->setParent(pWidget);
		qsb1->move(750,100);
		qsb1->resize(44,300);
		qsb1->setRange(0,1000);
		qsb1->setSingleStep(1);
		qsb1->setStyleSheet("QScrollBar:vertical"
                                                   "{"
                                                   "width:40px;"
                                                   "background:rgba(0,0,0,0%);"
                                                   "margin:0px,0px,0px,0px;"
                                                   "padding-top:40px;"
                                                   "padding-bottom:40px;"
                                                   "}"
												   "QScrollBar::handle:vertical{"
												   "border-image: url(/A7_QT_FROM_WINCE/WORK_DIR/png_resource/img/public/loc_1.png);"
												   "min-height:38px;"
												   "}"
                                                   "QScrollBar::add-line:vertical"
                                                   "{"
                                                   "height:36px;width:36px;"
                                                   "border-image:url(/A7_QT_FROM_WINCE/WORK_DIR/png_resource/img/radio/list/down.png);"
                                                   "subcontrol-position:bottom;"
                                                   "}"
                                                   "QScrollBar::sub-line:vertical"
                                                   "{"
                                                   "height:36px;width:36px;"
                                                   "border-image:url(/A7_QT_FROM_WINCE/WORK_DIR/png_resource/img/radio/list/up.png);"
                                                   "subcontrol-position:top;"
                                                   "}"
                                                   "QScrollBar::add-line:vertical:hover"
                                                   "{"
                                                   "height:36px;width:36px;"
                                                   "border-image:url(/A7_QT_FROM_WINCE/WORK_DIR/png_resource/img/radio/list/up.png);"
                                                   "subcontrol-position:bottom;"
                                                   "}"
                                                   "QScrollBar::sub-line:vertical:hover"
                                                   "{"
                                                   "height:36px;width:36px;"
                                                   "border-image:url(/A7_QT_FROM_WINCE/WORK_DIR/png_resource/img/radio/list/down.png);"
                                                   "subcontrol-position:top;"
                                                   "}"
                                                   "QScrollBar::add-page:vertical,QScrollBar::sub-page:vertical"
                                                   "{"
													   "background:rgba(0,0,0,0);"
													   "border-radius:0px;"
                                                   "}"
                                                   );


						qsb2=new QScrollBar();
						qsb2->setOrientation(Qt::Horizontal);
						qsb2->setParent(pWidget);
						qsb2->move(30,430);
						qsb2->resize(740,42);
						qsb2->setRange(0,10000);
						// 不能设置太小；不然会出现 滑块太大的问题
						qsb2->setSingleStep(1);
						qsb2->setStyleSheet("QScrollBar:Horizontal"
                                                   "{"
                                                   "width:40px;"
                                                   "background:rgba(0,0,0,0%);"
                                                   "margin:0px,0px,0px,0px;"
                                                   "padding-left:40px;"
                                                   "padding-right:40px;"
                                                   "}"
												   "QScrollBar::handle:Horizontal{"
												   "border-image: url(/A7_QT_FROM_WINCE/WORK_DIR/png_resource/img/public/loc_2.png);"
												   "min-width:44px;"
												   "}"
                                                   "QScrollBar::add-line:Horizontal"
                                                   "{"
                                                   "height:36px;width:36px;"
                                                   "border-image:url(/A7_QT_FROM_WINCE/WORK_DIR/png_resource/img/radio/list/down.png);"
                                                   "subcontrol-position:right;"
                                                   "}"
                                                   "QScrollBar::sub-line:Horizontal"
                                                   "{"
                                                   "height:36px;width:36px;"
                                                   "border-image:url(/A7_QT_FROM_WINCE/WORK_DIR/png_resource/img/radio/list/up.png);"
                                                   "subcontrol-position:left;"
                                                   "}"
                                                   "QScrollBar::add-line:Horizontal:hover"
                                                   "{"
                                                   "height:36px;width:36px;"
                                                   "border-image:url(/A7_QT_FROM_WINCE/WORK_DIR/png_resource/img/radio/list/up.png);"
                                                   "subcontrol-position:right;"
                                                   "}"
                                                   "QScrollBar::sub-line:Horizontal:hover"
                                                   "{"
                                                   "height:36px;width:36px;"
                                                   "border-image:url(/A7_QT_FROM_WINCE/WORK_DIR/png_resource/img/radio/list/down.png);"
                                                   "subcontrol-position:left;"
                                                   "}"
                                                   "QScrollBar::add-page:Horizontal,QScrollBar::sub-page:Horizontal"
                                                   "{"
													   "background:rgba(0,0,0,0);"
													   "border-radius:0px;"
                                                   "}"
                                                   );
	}
}

void initWindow(){
	QWidget *pWidget = new QWidget;

	QLabel label(pWidget);
	QFont ft;
	ft.setPointSize(12);
	label.setFont(ft);
	//设置颜色
	QPalette pa;
	pa.setColor(QPalette::WindowText,Qt::red);
	label.setPalette(pa);


	label.setText(QObject::tr("abc："));

	label.setGeometry(10,10,20,20);

	QLineEdit namedLineEdit("text",pWidget);

	namedLineEdit.setGeometry(100,300,50,20);

	//QPushButton*btn=new QPushButton0(QObject::tr("rmvb"),wParent);

	//btn->setGeometry(100,300,40,20);
	
	

	
	//wParent->setParent(mwThis);
//	wParent->hide();
	//addScrollBar(wParent);
	//mwThis->setCentralWidget(wParent);
}

void initWindow0(){
	
	mwThis-> setWindowTitle(QString("新闻推荐系统"));

    //自定义QLabel控件
    QLabel *m_lblLeft = new QLabel(QString("<b>文章关键字列表 </b>"));
    QLabel *m_lblRight =new QLabel(QString("<b>关键字向量 </b>"));
    QLabel *m_lblRcmd1 = new QLabel(QString("<b>推荐结果1 </b>"));
    QLabel *m_lblRcmd2 = new QLabel(QString("<b>推荐结果2 </b>"));

     //主窗口中添加一个Widget，将所有控件放入Widget，其中setCentralWidget()设置该widget为当前窗口的widget
	QWidget *  m_widget = new QWidget();
     mwThis->setCentralWidget(m_widget);

     //设置窗口的布局，QGridLayout中的参数分别是(控件名称，控件所在的行号，控件所在的列号)
     QGridLayout* gridLayout = new QGridLayout;
     gridLayout->addWidget(m_lblLeft,0,0);
     gridLayout->addWidget(m_lblRight,0,1);
     gridLayout->addWidget(m_lblRcmd1,2,0);
     gridLayout->addWidget(m_lblRcmd2,2,1);

     //把新建的Widget的布局设置为gridLayout
     m_widget->setLayout(gridLayout);
}
//! [1]
void MainWindow::closeEvent(QCloseEvent *event)
//! [1] //! [2]
{

}
//! [2]

//! [3]
void MainWindow::open()
//! [3] //! [4]
{
    
}
//! [4]

//! [5]
void MainWindow::save()
//! [5] //! [6]
{

}
//! [6]

//! [11]
void MainWindow::about()
//! [11] //! [12]
{
    QMessageBox::about(this, tr("About Scribble"),
            tr("<p>The <b>Scribble</b> example shows how to use QMainWindow as the "
               "base widget for an application, and how to reimplement some of "
               "QWidget's event handlers to receive the events generated for "
               "the application's widgets:</p><p> We reimplement the mouse event "
               "handlers to facilitate drawing, the paint event handler to "
               "update the application and the resize event handler to optimize "
               "the application's appearance. In addition we reimplement the "
               "close event handler to intercept the close events before "
               "terminating the application.</p><p> The example also demonstrates "
               "how to use QPainter to draw an image in real time, as well as "
               "to repaint widgets.</p>"));
}
//! [12]

//! [13]


void MainWindow::mousePressEvent(QMouseEvent*event){  
    if(event->buttons()==Qt::LeftButton){//如果鼠标按下的是左键  
        //则改变鼠标形状为手掌，表示拖动状态。  
   
    }  
}  
void MainWindow::mouseMoveEvent(QMouseEvent*event){  
    if(event->buttons()==Qt::LeftButton){//如果鼠标按下的是左键  
    }  
}  
   
void MainWindow::mouseReleaseEvent(QMouseEvent*event){  
    //拖动完成后，光标恢复默认形状  
//    setCursor(cursor);  
    //或者直接用自带恢复鼠标指针形状的函数为：QApplication::restoreOverrideCursor();  
    //但是需要前面设置哪个是默认的光标形状，用这个函数setOverrideCursor()函数  
}  
   
void MainWindow::mouseDoubleClickEvent(QMouseEvent*event){  
     if(event->buttons()==Qt::LeftButton){//如果鼠标按下的是左键  
     }  
}  
void MainWindow::wheelEvent(QWheelEvent*event){  
    QRect tmp=this->geometry();//获取窗口的位置以及大小并保存在tmp中。  
    if(event->delta()>0){//如果滚轮往上滚  
   
    }else{//同样的  
    }  
}  

void MainWindow::paintEvent(QPaintEvent * /* event */)
{
}



////////////////

/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Tue Oct 31 11:33:22 2017
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      19,   11,   11,   11, 0x08,
      26,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0open()\0save()\0about()\0"
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: open(); break;
        case 1: save(); break;
        case 2: about(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
