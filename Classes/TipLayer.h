#ifndef __TipLayer_SCENE_H__
#define __TipLayer_SCENE_H__

#include "AppMacros.h"
#include "BaseLayer.h"
using namespace cocos2d;
using namespace ui;
using namespace std;

enum TIP_ENUM_TYPE
{
	TIP_TYPE_END=0,
	TIP_TYPE_BACK,
	TIP_TYPE_JIESAN,
	TIP_TYPE_LEAVE
};


class TipLayer : public BaseLayer
{
public:
	TipLayer();
	~TipLayer();
	static TipLayer *create(TIP_ENUM_TYPE type);
	virtual bool init(TIP_ENUM_TYPE type);
	
	void TouchEvent(CCObject *obj, TouchEventType type);
	void setContent(string tip);
private:
	TIP_ENUM_TYPE m_type;
private:
	
};

#endif 