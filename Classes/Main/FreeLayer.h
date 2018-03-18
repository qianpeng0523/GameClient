#ifndef __FreeLayer_SCENE_H__
#define __FreeLayer_SCENE_H__

#include "AppMacros.h"
#include "BaseLayer.h"
using namespace cocos2d;
using namespace ui;
using namespace std;



class FreeItemLayer : public BaseLayer
{
public:
	FreeItemLayer();
	~FreeItemLayer();
	static FreeItemLayer *create(Rank hall);
	virtual bool init(Rank hall);

	void TouchEvent();
private:
	Rank m_hall;
private:

};












class FreeLayer : public BaseLayer
{
public:
	FreeLayer();
	~FreeLayer();
	CREATE_FUNC(FreeLayer);
    virtual bool init();
	
	void TouchEvent(CCObject *obj, TouchEventType type);
	void AddFreeItems();
private:
	ui::ScrollView *m_ScrollView;
	Layout *m_sbg;
private:
	
};

#endif 