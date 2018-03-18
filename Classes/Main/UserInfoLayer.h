#ifndef __UserInfoLayer_SCENE_H__
#define __UserInfoLayer_SCENE_H__

#include "AppMacros.h"
#include "BaseLayer.h"
using namespace cocos2d;
using namespace ui;
using namespace std;

class UserInfoLayer : public BaseLayer
{
public:
	UserInfoLayer();
	~UserInfoLayer();
	CREATE_FUNC(UserInfoLayer);
    virtual bool init();
	
	void TouchEvent(CCObject *obj, TouchEventType type);
private:
	
private:
	
};

#endif 