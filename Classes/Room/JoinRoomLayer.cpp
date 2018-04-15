#include "JoinRoomLayer.h"
#include "GameControl.h"
#include "GameDataSet.h"
#include "ClientSocket.h"
#include "LogoScene.h"
#include "LoginInfo.h"
#include "WebViewCommom.h"





JoinRoomLayer::JoinRoomLayer(){
	GameControl::getIns()->setJoinRoomLayer(this);
}

JoinRoomLayer::~JoinRoomLayer(){
	RootRegister::getIns()->resetWidget(m_RootLayer);
	if (this == GameControl::getIns()->getJoinRoomLayer()){
		GameControl::getIns()->setJoinRoomLayer(NULL);

	}
}

bool JoinRoomLayer::init()
{             
	if (!Layer::init())
    {
        return false;
    }
	
	m_RootLayer =RootRegister::getIns()->getWidget("privatejoin.json");
	this->addChild(m_RootLayer);

	SEL_TouchEvent selector = toucheventselector(JoinRoomLayer::TouchEvent);
	
	GameDataSet::getButton(m_RootLayer, "close_btn", selector, this);
	char buff[30];
	for (int i = 0; i < 10; i++){
		sprintf(buff,"btn_%d",i);
		GameDataSet::getButton(m_RootLayer, buff,selector,this);
	}
    return true;
}

void JoinRoomLayer::TouchEvent(CCObject *obj, TouchEventType type){
	Button *btn = (Button *)obj;
	string name = btn->getName();
	if (type == TOUCH_EVENT_ENDED){
		UserDefault *p = UserDefault::sharedUserDefault();
		if (name.compare("close_btn") == 0){
			this->removeFromParentAndCleanup(true);
		}
		
	}
}