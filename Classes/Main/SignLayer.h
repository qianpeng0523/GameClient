#ifndef __SignLayer_SCENE_H__
#define __SignLayer_SCENE_H__

#include "AppMacros.h"
#include "BaseLayer.h"
using namespace cocos2d;
using namespace ui;
using namespace std;

class SignLayer : public BaseLayer
{
public:
	SignLayer();
	~SignLayer();
	static SignLayer *create();
	virtual bool init();
	
	void TouchEvent(CCObject *obj, TouchEventType type);
	void OpenRun(bool isopen);
private:
	void RunLight(float dt);
	void ShowLight(bool isshow);
	void RunPoint(bool isrun);
	void CallFun();
private:
	bool m_isopen;
	Layout *m_light;
	Layout *m_point;
};

#endif 