#ifndef __GameControl_SCENE_H__
#define __GameControl_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "LogoLayer.h"
#include "MainLayer.h"
#include "UserInfoLayer.h"
#include "SetLayer.h"
#include "ShopLayer.h"
#include "SignLayer.h"

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

	void setUserInfoLayer(UserInfoLayer *p){
		m_pUserInfoLayer = p;
	}
	UserInfoLayer *getUserInfoLayer(){
		return m_pUserInfoLayer;
	}

	void setSetLayer(SetLayer *p){
		m_pSetLayer = p;
	}
	SetLayer *getSetLayer(){
		return m_pSetLayer;
	}

	void setShopLayer(ShopLayer *p){
		m_pShopLayer = p;
	}
	ShopLayer *getShopLayer(){
		return m_pShopLayer;
	}

	void setSignLayer(SignLayer *p){
		m_pSignLayer = p;
	}
	SignLayer *getSignLayer(){
		return m_pSignLayer;
	}

	void replaceScene(Scene *scene);
private:
	static GameControl *m_ins;
	LogoLayer *m_pLoginLayer;
	MainLayer *m_pMainLayer;
	UserInfoLayer *m_pUserInfoLayer;
	SetLayer *m_pSetLayer;
	ShopLayer *m_pShopLayer;
	SignLayer *m_pSignLayer;
};

#endif // __GameControl_SCENE_H__
