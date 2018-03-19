#include "AboutLayer.h"
#include "GameControl.h"
#include "GameDataSet.h"
#include "ClientSocket.h"
#include "LogoScene.h"
#include "LoginInfo.h"






AboutLayer::AboutLayer(){
	GameControl::getIns()->setAboutLayer(this);
}

AboutLayer::~AboutLayer(){
	if (this == GameControl::getIns()->getAboutLayer()){
		GameControl::getIns()->setAboutLayer(NULL);

	}
}

bool AboutLayer::init()
{             
	if (!Layer::init())
    {
        return false;
    }
	
	m_RootLayer = (Layout *)GUIReader::shareReader()->widgetFromJsonFile("about.json");
	this->addChild(m_RootLayer);

	SEL_TouchEvent selector = toucheventselector(AboutLayer::TouchEvent);
	
	GameDataSet::getButton(m_RootLayer, "close_btn", selector, this);
	
    return true;
}

void AboutLayer::TouchEvent(CCObject *obj, TouchEventType type){
	Button *btn = (Button *)obj;
	string name = btn->getName();
	if (type == TOUCH_EVENT_ENDED){
		UserDefault *p = UserDefault::sharedUserDefault();
		if (name.compare("close_btn") == 0){
			this->removeFromParentAndCleanup(true);
		}
	}
}