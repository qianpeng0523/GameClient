#include "GameHead.h"
#include "GameControl.h"
#include "GameDataSet.h"
#include "ClientSocket.h"
#include "LoginScene.h"
#include "LoginInfo.h"


GameHead::GameHead(){
	
}

GameHead::~GameHead(){
	RootRegister::getIns()->resetWidget(m_RootLayer);
	
}

bool GameHead::init()
{             
	if (!Layer::init())
    {
        return false;
    }
	
	m_RootLayer =RootRegister::getIns()->getWidget("headlayer.json");
	this->addChild(m_RootLayer);

	SEL_TouchEvent selector = toucheventselector(GameHead::TouchEvent);
	GameDataSet::getButton(m_RootLayer, "btn", selector, this);
	GameDataSet::getButton(m_RootLayer, "close_btn", selector, this);
	GameDataSet::getButton(m_RootLayer, "btn_del", selector, this);
	GameDataSet::getButton(m_RootLayer, "btn_reput", selector, this);
	
    return true;
}

void GameHead::TouchEvent(CCObject *obj, TouchEventType type){
	Button *btn = (Button *)obj;
	string name = btn->getName();
	if (type == TOUCH_EVENT_ENDED){
		UserDefault *p = UserDefault::sharedUserDefault();
		if (name.compare("close_btn") == 0){
			this->removeFromParentAndCleanup(true);
		}
	}
}