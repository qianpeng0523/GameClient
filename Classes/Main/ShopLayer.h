#ifndef __ShopLayer_SCENE_H__
#define __ShopLayer_SCENE_H__

#include "AppMacros.h"
#include "BaseLayer.h"
using namespace cocos2d;
using namespace ui;
using namespace std;

class ShopLayer : public BaseLayer
{
public:
	ShopLayer();
	~ShopLayer();
	CREATE_FUNC(ShopLayer);
    virtual bool init();
	
	void TouchEvent(CCObject *obj, TouchEventType type);
	void SelectItem(int index);
private:
	Button *m_btns[2];
	TextBMFont *m_btntext[2];
private:
	
};

#endif 