#ifndef __TipLayer_SCENE_H__
#define __TipLayer_SCENE_H__

#include "AppMacros.h"
#include "BaseLayer.h"
using namespace cocos2d;
using namespace ui;
using namespace std;




class TipLayer : public BaseLayer
{
public:
	TipLayer();
	~TipLayer();
	CREATE_FUNC(TipLayer);
    virtual bool init();
	
	void TouchEvent(CCObject *obj, TouchEventType type);
	void setContent(string tip);
private:
	
private:
	
};

#endif 