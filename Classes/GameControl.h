#ifndef __GameControl_SCENE_H__
#define __GameControl_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "LogoLayer.h"
#include "MainLayer.h"
using namespace cocos2d;
using namespace ui;
using namespace std;

class GameControl : public CCObject
{
public:
	GameControl();
	~GameControl();
    virtual bool init();
    CREATE_FUNC(GameControl);
	static GameControl* getIns();
	
public:
	void setLoginLayer(LogoLayer *p){
		m_pLoginLayer = p;
	}
	LogoLayer *getLoginLayer(){
		return m_pLoginLayer;
	}

	void setMainLayer(MainLayer *p){
		m_pMainLayer = p;
	}
	MainLayer *getMainLayer(){
		return m_pMainLayer;
	}
private:
	static GameControl *m_ins;
	LogoLayer *m_pLoginLayer;
	MainLayer *m_pMainLayer;
};

#endif // __GameControl_SCENE_H__
