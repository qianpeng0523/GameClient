#include "MJHu.h"
#include "GameControl.h"
#include "GameDataSet.h"
#include "ClientSocket.h"
#include "LoginScene.h"
#include "LoginInfo.h"


MJHu::MJHu(){
	
}

MJHu::~MJHu(){
	RootRegister::getIns()->resetWidget(m_RootLayer);
	
}

bool MJHu::init(int pos)
{             
	if (!Layer::init())
    {
        return false;
    }
	m_position = pos;
	char buff[50];
	sprintf(buff, "mjhu%d.json", pos);
	m_RootLayer =RootRegister::getIns()->getWidget(buff);
	this->addChild(m_RootLayer);
	this->setVisible(false);
    return true;
}

MJHu* MJHu::create(int pos){
	MJHu *p = new MJHu();
	if (p&&p->init(pos)){
		p->autorelease();
	}
	else{
		CC_SAFE_DELETE(p);
	}
	return p;
}

void MJHu::TouchEvent(CCObject *obj, TouchEventType type){
	Button *btn = (Button *)obj;
	string name = btn->getName();
	if (type == TOUCH_EVENT_ENDED){
		UserDefault *p = UserDefault::sharedUserDefault();
		if (name.compare("close_btn") == 0){
			this->removeFromParentAndCleanup(true);
		}
	}
}