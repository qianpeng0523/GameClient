#ifndef __GameUI_SCENE_H__
#define __GameUI_SCENE_H__

#include "AppMacros.h"
#include "BaseLayer.h"
using namespace cocos2d;
using namespace ui;
using namespace std;




class GameUI : public BaseLayer
{
public:
	GameUI();
	~GameUI();
	CREATE_FUNC(GameUI);
    virtual bool init();
	
	void TouchEvent(CCObject *obj, TouchEventType type);
	
private:
	void openMenu();
	void closeMenu();
	void menuCallBack();
private:
	bool m_isopenmenu;
	Layout *m_menubg;
	Button *m_menubtn;
};

#endif 