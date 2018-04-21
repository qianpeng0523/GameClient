#include "MJHand.h"
#include "GameControl.h"
#include "GameDataSet.h"
#include "ClientSocket.h"
#include "LoginScene.h"
#include "LoginInfo.h"


MJHand::MJHand(){
	
}

MJHand::~MJHand(){
	RootRegister::getIns()->resetWidget(m_RootLayer);
	
}

bool MJHand::init(int pos)
{             
	if (!Layer::init())
    {
        return false;
    }
	m_position = pos;
	
	char buff[50];
	sprintf(buff,"mjhand%d.json",pos);
	m_RootLayer =RootRegister::getIns()->getWidget(buff);
	this->addChild(m_RootLayer);

	SEL_TouchEvent selector = toucheventselector(MJHand::TouchEvent);
	
    return true;
}

MJHand* MJHand::create(int pos){
	MJHand *p = new MJHand();
	if (p&&p->init(pos)){
		p->autorelease();
	}
	else{
		CC_SAFE_DELETE(p);
	}
	return p;
}

void MJHand::TouchEvent(CCObject *obj, TouchEventType type){
	Button *btn = (Button *)obj;
	string name = btn->getName();
	if (type == TOUCH_EVENT_ENDED){
		if (name.compare("close_btn") == 0){
			
		}
	}
}