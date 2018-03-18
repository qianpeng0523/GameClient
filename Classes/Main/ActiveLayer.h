#ifndef __ActiveLayer_SCENE_H__
#define __ActiveLayer_SCENE_H__

#include "AppMacros.h"
#include "BaseLayer.h"
using namespace cocos2d;
using namespace ui;
using namespace std;




class ActiveLayer : public BaseLayer
{
public:
	ActiveLayer();
	~ActiveLayer();
	CREATE_FUNC(ActiveLayer);
    virtual bool init();
	
	void TouchEvent(CCObject *obj, TouchEventType type);
	void ShowItem(int type,int index);
private:
	Button *m_btns[3];
	Button *m_titlebtns[2];
	TextBMFont *m_btntext[3];
	int m_type;
private:
	
};

#endif 