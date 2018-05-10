#ifndef __GameChatRecordLayer_SCENE_H__
#define __GameChatRecordLayer_SCENE_H__

#include "AppMacros.h"
#include "BaseLayer.h"

using namespace cocos2d;
using namespace ui;
using namespace std;




class GameChatRecordLayer : public BaseLayer
{
public:
	GameChatRecordLayer();
	~GameChatRecordLayer();
	static GameChatRecordLayer *create(string uid, string uname, string content,string time);
	virtual bool init(string uid, string uname, string content, string time);

	void TouchEvent(CCObject *obj, TouchEventType type);
	
private:
	string m_uid;
	string m_json;
	ImageView *m_conbg;
	Text *m_content;
	ImageView *m_yuyin;
	ImageView *m_exp;
private:

};

#endif 