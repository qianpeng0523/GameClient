#ifndef __MailTipLayer_SCENE_H__
#define __MailTipLayer_SCENE_H__

#include "AppMacros.h"
#include "BaseLayer.h"
using namespace cocos2d;
using namespace ui;
using namespace std;

class MailTipLayer : public BaseLayer
{
public:
	MailTipLayer();
	~MailTipLayer();
	static MailTipLayer *create(Mail mail);
	virtual bool init(Mail mail);
	
	void TouchEvent(CCObject *obj, TouchEventType type);

private:
	Button *m_btn;
	Mail m_mail;
private:
	
};

#endif 