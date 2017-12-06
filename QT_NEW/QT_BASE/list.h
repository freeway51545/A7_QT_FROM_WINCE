#ifndef QLISTVIEW_MY
#define QLISTVIEW_MY
#include "pub.h"

class QListViewMy:public QListView{
public:
	 QStandardItemModel*standardItemModel ;
	QListViewMy():QListView(){
	}
	QListViewMy(QWidget *parent):QListView(parent){
	}
protected:

	void itemClicked(const QModelIndex &index){
	}
};

QListViewMy*  makeListView();

#endif
