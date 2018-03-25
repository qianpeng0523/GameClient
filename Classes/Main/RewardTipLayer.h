#ifndef __RewardTipLayer_SCENE_H__
#define __RewardTipLayer_SCENE_H__

#include "AppMacros.h"
#include "BaseLayer.h"
using namespace cocos2d;
using namespace ui;
using namespace std;




class RewardTipLayer : public BaseLayer
{
public:
	RewardTipLayer();
	~RewardTipLayer();
	static RewardTipLayer *create(vector<Prop> props);
	virtual bool init(vector<Prop> props);
	
	void TouchEvent(CCObject *obj, TouchEventType type);
	
private:
	
private:
	
};

#endif 