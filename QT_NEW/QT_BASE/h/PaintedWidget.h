
#ifndef PAINTED_WIDG_H
#define PAINTED_WIDG_H

#include <QList>
#include <QMainWindow>
#include<QMouseEvent>
#include<QWheelEvent>
#include "qlistview.h"
class BaseStateEventItemV2;
class PaintedWidget : public QWidget 
{ 
	BaseStateEventItemV2 *pBined;
		Q_OBJECT
public: 
	PaintedWidget(BaseStateEventItemV2 *b);
 
protected: 
		void makeListView();
        void paintEvent(QPaintEvent *event);
private slots:
		void pointClicked();
		void itemClicked(const QModelIndex &index);

protected:  
    void mousePressEvent(QMouseEvent*event);//按下  
    void mouseMoveEvent(QMouseEvent*event);//按下移动  
    void mouseReleaseEvent(QMouseEvent*event);//松开  
	bool event(QEvent *event);
};

#endif