#ifndef __GameHelpLayer_SCENE_H__
#define __GameHelpLayer_SCENE_H__

#include "AppMacros.h"
#include "BaseLayer.h"
using namespace cocos2d;
using namespace ui;
using namespace std;




class GameHelpLayer : public BaseLayer
{
public:
	GameHelpLayer();
	~GameHelpLayer();
	CREATE_FUNC(GameHelpLayer);
    virtual bool init();
	
	void TouchEvent(CCObject *obj, TouchEventType type);
	
private:
	
private:
	
};

#endif 