#ifndef __AboutLayer_SCENE_H__
#define __AboutLayer_SCENE_H__

#include "AppMacros.h"
#include "BaseLayer.h"
using namespace cocos2d;
using namespace ui;
using namespace std;




class AboutLayer : public BaseLayer
{
public:
	AboutLayer();
	~AboutLayer();
	CREATE_FUNC(AboutLayer);
    virtual bool init();
	
	void TouchEvent(CCObject *obj, TouchEventType type);
	
private:
	
private:
	
};

#endif 