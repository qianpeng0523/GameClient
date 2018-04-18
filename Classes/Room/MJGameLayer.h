#ifndef __MJGameLayer_SCENE_H__
#define __MJGameLayer_SCENE_H__

#include "AppMacros.h"
#include "BaseLayer.h"
using namespace cocos2d;
using namespace ui;
using namespace std;




class MJGameLayer : public BaseLayer
{
public:
	MJGameLayer();
	~MJGameLayer();
	CREATE_FUNC(MJGameLayer);
    virtual bool init();
	
	void TouchEvent(CCObject *obj, TouchEventType type);
	
private:
	
private:
	
};

#endif 