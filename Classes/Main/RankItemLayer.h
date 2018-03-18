#ifndef __RankItemLayer_SCENE_H__
#define __RankItemLayer_SCENE_H__

#include "AppMacros.h"
#include "BaseLayer.h"
using namespace cocos2d;
using namespace ui;
using namespace std;

class RankItemLayer : public BaseLayer
{
public:
	RankItemLayer();
	~RankItemLayer();
	static RankItemLayer *create(Rank hall);
	virtual bool init(Rank hall);
	
	void TouchEvent();
private:
	Rank m_hall;
private:
	
};

#endif 