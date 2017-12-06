#ifndef ZMyMessage_H
#define ZMyMessage_H

const QEvent::Type MyEvent = (QEvent::Type)30049;
class ZMyMessage: public QEvent
{
public:
	WPARAM msgId;
	LPARAM lparam;
public:
	ZMyMessage(Type type,WPARAM msgIdSet,LPARAM lparamSet):QEvent(type){
		msgId=msgIdSet;
		lparam=lparamSet;
	}
	~ZMyMessage(){
	}
};


#endif