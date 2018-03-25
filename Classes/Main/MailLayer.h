#ifndef __MailLayer_SCENE_H__
#define __MailLayer_SCENE_H__

#include "AppMacros.h"
#include "BaseLayer.h"
using namespace cocos2d;
using namespace ui;
using namespace std;



class MailItemLayer : public BaseLayer
{
public:
	MailItemLayer();
	~MailItemLayer();
	static MailItemLayer *create(Mail mail);
	virtual bool init(Mail mail);

	void TouchEvent(CCObject *obj, TouchEventType type);
private:
	Mail m_mail;
private:

};












class MailLayer : public BaseLayer
{
public:
	MailLayer();
	~MailLayer();
	CREATE_FUNC(MailLayer);
    virtual bool init();
	
	void TouchEvent(CCObject *obj, TouchEventType type);
	void AddMailItems();
private:
	ui::ScrollView *m_ScrollView;
	Layout *m_sbg;
private:
	
};

#endif 