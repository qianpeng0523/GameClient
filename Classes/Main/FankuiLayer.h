#ifndef __FankuiLayer_SCENE_H__
#define __FankuiLayer_SCENE_H__

#include "AppMacros.h"
#include "BaseLayer.h"
using namespace cocos2d;
using namespace ui;
using namespace std;

class FankuiLayer : public BaseLayer
{
public:
	FankuiLayer();
	~FankuiLayer();
	CREATE_FUNC(FankuiLayer);
    virtual bool init();
	
	void TouchEvent(CCObject *obj, TouchEventType type);
private:
	ui::EditBox *m_input;
private:
	
};

#endif 