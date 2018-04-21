#include "MJCPH.h"
#include "GameControl.h"
#include "GameDataSet.h"
#include "ClientSocket.h"
#include "LoginScene.h"
#include "LoginInfo.h"


MJCPH::MJCPH(){
	
}

MJCPH::~MJCPH(){
	RootRegister::getIns()->resetWidget(m_RootLayer);
	
}

bool MJCPH::init(int pos)
{             
	if (!Layer::init())
    {
        return false;
    }
	m_position = pos;
	char buff[50];
	sprintf(buff, "mjcpg%d.json", pos);
	m_RootLayer =RootRegister::getIns()->getWidget(buff);
	this->addChild(m_RootLayer);

    return true;
}

MJCPH* MJCPH::create(int pos){
	MJCPH *p = new MJCPH();
	if (p&&p->init(pos)){
		p->autorelease();
	}
	else{
		CC_SAFE_DELETE(p);
	}
	return p;
}

void MJCPH::TouchEvent(CCObject *obj, TouchEventType type){
	Button *btn = (Button *)obj;
	string name = btn->getName();
	if (type == TOUCH_EVENT_ENDED){
		UserDefault *p = UserDefault::sharedUserDefault();
		if (name.compare("close_btn") == 0){
			this->removeFromParentAndCleanup(true);
		}
	}
}