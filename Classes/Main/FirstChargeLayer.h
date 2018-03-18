#ifndef __FirstChargeLayer_SCENE_H__
#define __FirstChargeLayer_SCENE_H__

#include "AppMacros.h"
#include "BaseLayer.h"
using namespace cocos2d;
using namespace ui;
using namespace std;

class FirstChargeLayer : public BaseLayer
{
public:
	FirstChargeLayer();
	~FirstChargeLayer();
	CREATE_FUNC(FirstChargeLayer);
    virtual bool init();
	
	void TouchEvent(CCObject *obj, TouchEventType type);
private:
	
private:
	
};

#endif 