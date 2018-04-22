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
	void update(float dt);

	void ShowReady(bool isv);
	void ShowBegin(bool isv);
private:
	void openMenu();
	void closeMenu();
	void menuCallBack();
private:
	bool m_isopenmenu;
	Layout *m_menubg;
	Button *m_menubtn;
	Button *m_beginbtn;
	Button *m_readybtn;
};

#endif 