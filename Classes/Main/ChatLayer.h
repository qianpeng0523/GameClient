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
	static ChatItemLayer *create(FriendChat *fc);
	virtual bool init(FriendChat *fc);

	void TouchEvent(CCObject *obj, TouchEventType type);
	
private:
	FriendChat *m_fc;
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
	void AddChatItem(FriendChat *fc);//0表示自己 1表示别人
	void AddAllChat();

	void openExp();
	void closeExp();
	void AddEmotion();
	string getUID(){
		return m_uid;
	}
private:
	string m_uid;
	string m_uname;
	ui::ScrollView *m_ScrollView;
	ui::ScrollView *m_ScrollView1;
	Layout *m_sbg;
	ui::EditBox *m_input;
private:
	
};

#endif 