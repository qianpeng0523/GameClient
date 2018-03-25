#ifndef __ChatLayer_SCENE_H__
#define __ChatLayer_SCENE_H__

#include "AppMacros.h"
#include "BaseLayer.h"
using namespace cocos2d;
using namespace ui;
using namespace std;




class ChatItemLayer : public BaseLayer
{
public:
	ChatItemLayer();
	~ChatItemLayer();
	static ChatItemLayer *create(string uid, string uname, string content);
	virtual bool init(string uid, string uname, string content);

	void TouchEvent(CCObject *obj, TouchEventType type);
	
private:
	string m_uid;
	string m_json;
private:

};














class ChatLayer : public BaseLayer
{
public:
	ChatLayer();
	~ChatLayer();
	static ChatLayer *create(string uid, string uname);
	virtual bool init(string uid, string uname);
	
	void TouchEvent(CCObject *obj, TouchEventType type);
	void AddChatItem(int index, string uid,string name, string content);//0表示自己 1表示别人
private:
	string m_uid;
	string m_uname;
	ui::ScrollView *m_ScrollView;
	Layout *m_sbg;
	ui::EditBox *m_input;
private:
	
};

#endif 