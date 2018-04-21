#include "MJChu.h"
#include "GameControl.h"
#include "GameDataSet.h"
#include "ClientSocket.h"
#include "LoginScene.h"
#include "LoginInfo.h"


MJChu::MJChu(){
	
}

MJChu::~MJChu(){
	RootRegister::getIns()->resetWidget(m_RootLayer);
	
}

bool MJChu::init(int pos)
{             
	if (!Layer::init())
    {
        return false;
    }
	m_position = pos;
	char buff[50];
	sprintf(buff, "mjchu%d.json", pos);
	m_RootLayer =RootRegister::getIns()->getWidget(buff);
	this->addChild(m_RootLayer);

    return true;
}

MJChu* MJChu::create(int pos){
	MJChu *p = new MJChu();
	if (p&&p->init(pos)){
		p->autorelease();
	}
	else{
		CC_SAFE_DELETE(p);
	}
	return p;
}

void MJChu::TouchEvent(CCObject *obj, TouchEventType type){
	Button *btn = (Button *)obj;
	string name = btn->getName();
	if (type == TOUCH_EVENT_ENDED){
		UserDefault *p = UserDefault::sharedUserDefault();
		if (name.compare("close_btn") == 0){
			this->removeFromParentAndCleanup(true);
		}
	}
}