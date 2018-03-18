#include "MailLayer.h"
#include "GameControl.h"
#include "GameDataSet.h"
#include "ClientSocket.h"
#include "LogoScene.h"
#include "LoginInfo.h"




MailItemLayer::MailItemLayer(){

}

MailItemLayer::~MailItemLayer(){

}

MailItemLayer *MailItemLayer::create(Rank hall){
	MailItemLayer *p = new MailItemLayer();
	if (p&&p->init(hall)){
		p->autorelease();
	}
	else{
		CC_SAFE_DELETE(p);
	}
	return p;
}

bool MailItemLayer::init(Rank hall)
{
	if (!Layer::init())
	{
		return false;
	}
	m_hall = hall;
	m_RootLayer = (Layout *)GUIReader::shareReader()->widgetFromJsonFile("mailitem.json");
	this->addChild(m_RootLayer);

	this->setContentSize(m_RootLayer->getSize());



	return true;
}

void MailItemLayer::TouchEvent(){

}





















MailLayer::MailLayer(){
	GameControl::getIns()->setMailLayer(this);
}

MailLayer::~MailLayer(){
	if (this == GameControl::getIns()->getMailLayer()){
		GameControl::getIns()->setMailLayer(NULL);

	}
}

bool MailLayer::init()
{             
	if (!Layer::init())
    {
        return false;
    }
	
	m_RootLayer = (Layout *)GUIReader::shareReader()->widgetFromJsonFile("mail.json");
	this->addChild(m_RootLayer);

	SEL_TouchEvent selector = toucheventselector(MailLayer::TouchEvent);
	
	GameDataSet::getButton(m_RootLayer, "close_btn", selector, this);
	m_ScrollView = (ui::ScrollView *)GameDataSet::getButton(m_RootLayer, "ScrollView", selector, this);
	m_sbg = GameDataSet::getLayout(m_RootLayer, "sbg");
	AddMailItems();
    return true;
}

void MailLayer::TouchEvent(CCObject *obj, TouchEventType type){
	Button *btn = (Button *)obj;
	string name = btn->getName();
	if (type == TOUCH_EVENT_ENDED){
		UserDefault *p = UserDefault::sharedUserDefault();
		if (name.compare("close_btn") == 0){
			this->removeFromParentAndCleanup(true);
		}
		else if (name.compare("ScrollView") == 0){
			MailItemLayer *p = (MailItemLayer *)GameDataSet::isTouchInChild(m_ScrollView, 10, NULL);
			if (p){
				p->TouchEvent();
			}
		}
	}
}

void MailLayer::AddMailItems(){
	for (int i = 0; i < 10;i++){
		Rank rk;
		MailItemLayer *p = MailItemLayer::create(rk);
		GameDataSet::PushScrollItem(m_sbg, 0, 0, p, i, m_ScrollView);
	}
}