#ifndef __HelpLayer_SCENE_H__
#define __HelpLayer_SCENE_H__

#include "AppMacros.h"
#include "BaseLayer.h"
using namespace cocos2d;
using namespace ui;
using namespace std;




class HelpLayer : public BaseLayer
{
public:
	HelpLayer();
	~HelpLayer();
	CREATE_FUNC(HelpLayer);
    virtual bool init();
	
	void TouchEvent(CCObject *obj, TouchEventType type);
	
private:
	
private:
	
};

#endif 