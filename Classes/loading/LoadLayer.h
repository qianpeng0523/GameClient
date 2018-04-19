#ifndef __LoadLayer_SCENE_H__
#define __LoadLayer_SCENE_H__

#include "AppMacros.h"
#include "BaseLayer.h"
using namespace cocos2d;
using namespace ui;
using namespace std;

class LoadLayer : public BaseLayer
{
public:
	LoadLayer();
	~LoadLayer();
	static LoadLayer *create(Layout *ly);
	virtual bool init(Layout *ly);
	
private:
	
private:
	
};

#endif 