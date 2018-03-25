#include "FirstChargeLayer.h"
#include "GameControl.h"
#include "GameDataSet.h"
#include "ClientSocket.h"
#include "LogoScene.h"
#include "LoginInfo.h"

FirstChargeLayer::FirstChargeLayer(){
	GameControl::getIns()->setFirstChargeLayer(this);
}

FirstChargeLayer::~FirstChargeLayer(){
	RootRegister::getIns()->resetWidget(m_RootLayer);
	if (this == GameControl::getIns()->getFirstChargeLayer()){
		GameControl::getIns()->setFirstChargeLayer(NULL);

	}
}

bool FirstChargeLayer::init()
{             
	if (!Layer::init())
    {
        return false;
    }
	
	m_RootLayer =RootRegister::getIns()->getWidget("firstcharge.json");
	this->addChild(m_RootLayer);

	SEL_TouchEvent selector = toucheventselector(FirstChargeLayer::TouchEvent);
	
	GameDataSet::getButton(m_RootLayer, "close_btn", selector, this);
	GameDataSet::getButton(m_RootLayer, "btn", selector, this);
	
    return true;
}

void FirstChargeLayer::TouchEvent(CCObject *obj, TouchEventType type){
	Button *btn = (Button *)obj;
	string name = btn->getName();
	if (type == TOUCH_EVENT_ENDED){
		UserDefault *p = UserDefault::sharedUserDefault();
		if (name.compare("close_btn") == 0){
			this->removeFromParentAndCleanup(true);
		}
		else if (name.compare("btn") == 0){
			
		}
		
	}
}