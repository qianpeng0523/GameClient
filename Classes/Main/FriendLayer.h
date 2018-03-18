#ifndef __FriendLayer_SCENE_H__
#define __FriendLayer_SCENE_H__

#include "AppMacros.h"
#include "BaseLayer.h"
using namespace cocos2d;
using namespace ui;
using namespace std;



class FriendChatItemLayer : public BaseLayer
{
public:
	FriendChatItemLayer();
	~FriendChatItemLayer();
	static FriendChatItemLayer *create(Rank hall);
	virtual bool init(Rank hall);

	void TouchEvent();
private:
	Rank m_hall;
private:

};



class FriendNoticeLayer : public BaseLayer
{
public:
	FriendNoticeLayer();
	~FriendNoticeLayer();
	static FriendNoticeLayer *create(Rank hall);
	virtual bool init(Rank hall);

	void TouchEvent();
private:
	Rank m_hall;
private:

};






class FriendLayer : public BaseLayer
{
public:
	FriendLayer();
	~FriendLayer();
	static FriendLayer *create();
	virtual bool init();
	
	void TouchEvent(CCObject *obj, TouchEventType type);
	void SelectItem(int index);

	void ShowFriendEvent(int index);
private:
	Button *m_btns[3];
	TextBMFont *m_btntext[3];
	Layout *m_bg[3];
	ui::ScrollView *m_ScrollView[2];
	Layout *m_sbg[2];
	ui::EditBox *m_input;
private:
	
};

#endif 