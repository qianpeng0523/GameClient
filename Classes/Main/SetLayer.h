#ifndef __SetLayer_SCENE_H__
#define __SetLayer_SCENE_H__

#include "AppMacros.h"
#include "BaseLayer.h"
using namespace cocos2d;
using namespace ui;
using namespace std;

class SetLayer : public BaseLayer
{
public:
	SetLayer();
	~SetLayer();
	CREATE_FUNC(SetLayer);
    virtual bool init();
	
	void TouchEvent(CCObject *obj, TouchEventType type);
private:
	void SelectCheckBox(int index,bool isopen);
private:
	
};

#endif 