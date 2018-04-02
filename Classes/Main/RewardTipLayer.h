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
	static RewardTipLayer *create(RepeatedPtrField<SignAward> props);
	virtual bool init(RepeatedPtrField<SignAward> props);
	
	void TouchEvent(CCObject *obj, TouchEventType type);
	
private:
	
private:
	
};

#endif 