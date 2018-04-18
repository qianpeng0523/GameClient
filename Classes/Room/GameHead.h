#ifndef __GameHead_SCENE_H__
#define __GameHead_SCENE_H__

#include "AppMacros.h"
#include "BaseLayer.h"
using namespace cocos2d;
using namespace ui;
using namespace std;




class GameHead : public BaseLayer
{
public:
	GameHead();
	~GameHead();
	CREATE_FUNC(GameHead);
    virtual bool init();
	
	void TouchEvent(CCObject *obj, TouchEventType type);
	
private:
	
private:
	
};

#endif 