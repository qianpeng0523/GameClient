﻿#ifndef __MainLayer_SCENE_H__
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
private:
	
private:
	
};

#endif 