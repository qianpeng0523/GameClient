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
#include "FriendLayer.h"
#include "FankuiLayer.h"
#include "FreeLayer.h"
#include "ExchangeLayer.h"
#include "TaskLayer.h"
#include "MailLayer.h"
#include "ActiveLayer.h"


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

	void setFriendLayer(FriendLayer *p){
		m_pFriendLayer = p;
	}
	FriendLayer *getFriendLayer(){
		return m_pFriendLayer;
	}

	void setFankuiLayer(FankuiLayer *p){
		m_pFankuiLayer = p;
	}
	FankuiLayer *getFankuiLayer(){
		return m_pFankuiLayer;
	}

	void setFreeLayer(FreeLayer *p){
		m_pFreeLayer = p;
	}
	FreeLayer *getFreeLayer(){
		return m_pFreeLayer;
	}

	void setExchangeLayer(ExchangeLayer *p){
		m_pExchangeLayer = p;
	}
	ExchangeLayer *getExchangeLayer(){
		return m_pExchangeLayer;
	}

	void setTaskLayer(TaskLayer *p){
		m_pTaskLayer = p;
	}
	TaskLayer *getTaskLayer(){
		return m_pTaskLayer;
	}

	void setMailLayer(MailLayer *p){
		m_pMailLayer = p;
	}
	MailLayer *getMailLayer(){
		return m_pMailLayer;
	}

	void setActiveLayer(ActiveLayer *p){
		m_pActiveLayer = p;
	}
	ActiveLayer *getActiveLayer(){
		return m_pActiveLayer;
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
	FriendLayer *m_pFriendLayer;
	FankuiLayer *m_pFankuiLayer;
	FreeLayer *m_pFreeLayer;
	ExchangeLayer *m_pExchangeLayer;
	TaskLayer *m_pTaskLayer;
	MailLayer *m_pMailLayer;
	ActiveLayer *m_pActiveLayer;
};

#endif // __GameControl_SCENE_H__
