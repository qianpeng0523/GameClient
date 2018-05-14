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
	static RewardTipLayer *create(vector<Reward> props);
	virtual bool init(vector<Reward> props);
	
	void TouchEvent(CCObject *obj, TouchEventType type);
	void setTip(string tip);
private:
	float m_posx[2];
private:
	
};

#endif 