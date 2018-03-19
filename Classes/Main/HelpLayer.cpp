#include "HelpLayer.h"
#include "GameControl.h"
#include "GameDataSet.h"
#include "ClientSocket.h"
#include "LogoScene.h"
#include "LoginInfo.h"






HelpLayer::HelpLayer(){
	GameControl::getIns()->setHelpLayer(this);
}

HelpLayer::~HelpLayer(){
	if (this == GameControl::getIns()->getHelpLayer()){
		GameControl::getIns()->setHelpLayer(NULL);

	}
}

bool HelpLayer::init()
{             
	if (!Layer::init())
    {
        return false;
    }
	
	m_RootLayer = (Layout *)GUIReader::shareReader()->widgetFromJsonFile("help.json");
	this->addChild(m_RootLayer);

	SEL_TouchEvent selector = toucheventselector(HelpLayer::TouchEvent);
	
	GameDataSet::getButton(m_RootLayer, "close_btn", selector, this);
	
    return true;
}

void HelpLayer::TouchEvent(CCObject *obj, TouchEventType type){
	Button *btn = (Button *)obj;
	string name = btn->getName();
	if (type == TOUCH_EVENT_ENDED){
		UserDefault *p = UserDefault::sharedUserDefault();
		if (name.compare("close_btn") == 0){
			this->removeFromParentAndCleanup(true);
		}
	}
}