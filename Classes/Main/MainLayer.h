#ifndef __MainLayer_SCENE_H__
#define __MainLayer_SCENE_H__

#include "AppMacros.h"
#include "BaseLayer.h"
using namespace cocos2d;
using namespace ui;
using namespace std;

class MainLayer : public BaseLayer
{
public:
	MainLayer();
	~MainLayer();
	CREATE_FUNC(MainLayer);
    virtual bool init();
	
	void TouchEvent(CCObject *obj, TouchEventType type);
	void AddFriends(int type);
	void ShowFriends(int type);
private:
	void SelectItem(int index);
	void ScrollViewEvent(Ref* obj, ScrollviewEventType type);
	void ScrollViewEvent1(Ref* obj, ScrollviewEventType type);
private:
	Button *m_friendbtns[2];
	ui::ScrollView *m_ScrollView;
	Layout *m_sbg;
	ui::ScrollView *m_ScrollView1;
	Layout *m_sbg1;
	int m_index[2];
};

#endif 