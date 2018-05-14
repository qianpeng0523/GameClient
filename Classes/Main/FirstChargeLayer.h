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
	void setData();
	void setButton(int index,bool iss);
private:
	int m_type;
	ImageView *m_btnbgs[3];
private:
	
};

#endif 