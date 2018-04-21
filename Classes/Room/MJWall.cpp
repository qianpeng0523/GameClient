#include "MJWall.h"
#include "GameControl.h"
#include "GameDataSet.h"
#include "ClientSocket.h"
#include "LoginScene.h"
#include "LoginInfo.h"


MJWall::MJWall(){
	
}

MJWall::~MJWall(){
	RootRegister::getIns()->resetWidget(m_RootLayer);
	
}

bool MJWall::init(int pos)
{             
	if (!Layer::init())
    {
        return false;
    }
	m_position = pos;
	char buff[50];
	sprintf(buff, "mjwall%d.json", pos);
	m_RootLayer =RootRegister::getIns()->getWidget(buff);
	this->addChild(m_RootLayer);

    return true;
}

MJWall* MJWall::create(int pos){
	MJWall *p = new MJWall();
	if (p&&p->init(pos)){
		p->autorelease();
	}
	else{
		CC_SAFE_DELETE(p);
	}
	return p;
}

void MJWall::TouchEvent(CCObject *obj, TouchEventType type){
	Button *btn = (Button *)obj;
	string name = btn->getName();
	if (type == TOUCH_EVENT_ENDED){
		UserDefault *p = UserDefault::sharedUserDefault();
		if (name.compare("close_btn") == 0){
			this->removeFromParentAndCleanup(true);
		}
	}
}