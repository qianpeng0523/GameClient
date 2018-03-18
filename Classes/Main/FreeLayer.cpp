#include "FreeLayer.h"
#include "GameControl.h"
#include "GameDataSet.h"
#include "ClientSocket.h"
#include "LogoScene.h"
#include "LoginInfo.h"




FreeItemLayer::FreeItemLayer(){

}

FreeItemLayer::~FreeItemLayer(){

}

FreeItemLayer *FreeItemLayer::create(Rank hall){
	FreeItemLayer *p = new FreeItemLayer();
	if (p&&p->init(hall)){
		p->autorelease();
	}
	else{
		CC_SAFE_DELETE(p);
	}
	return p;
}

bool FreeItemLayer::init(Rank hall)
{
	if (!Layer::init())
	{
		return false;
	}
	m_hall = hall;
	m_RootLayer = (Layout *)GUIReader::shareReader()->widgetFromJsonFile("freeitem.json");
	this->addChild(m_RootLayer);

	this->setContentSize(m_RootLayer->getSize());



	return true;
}

void FreeItemLayer::TouchEvent(){

}





















FreeLayer::FreeLayer(){
	GameControl::getIns()->setFreeLayer(this);
}

FreeLayer::~FreeLayer(){
	if (this == GameControl::getIns()->getFreeLayer()){
		GameControl::getIns()->setFreeLayer(NULL);

	}
}

bool FreeLayer::init()
{             
	if (!Layer::init())
    {
        return false;
    }
	
	m_RootLayer = (Layout *)GUIReader::shareReader()->widgetFromJsonFile("free.json");
	this->addChild(m_RootLayer);

	SEL_TouchEvent selector = toucheventselector(FreeLayer::TouchEvent);
	
	GameDataSet::getButton(m_RootLayer, "close_btn", selector, this);
	m_ScrollView = (ui::ScrollView *)GameDataSet::getButton(m_RootLayer, "ScrollView", selector, this);
	m_sbg = GameDataSet::getLayout(m_RootLayer, "sbg");
	AddFreeItems();
    return true;
}

void FreeLayer::TouchEvent(CCObject *obj, TouchEventType type){
	Button *btn = (Button *)obj;
	string name = btn->getName();
	if (type == TOUCH_EVENT_ENDED){
		UserDefault *p = UserDefault::sharedUserDefault();
		if (name.compare("close_btn") == 0){
			this->removeFromParentAndCleanup(true);
		}
		else if (name.compare("ScrollView") == 0){
			FreeItemLayer *p = (FreeItemLayer *)GameDataSet::isTouchInChild(m_ScrollView, 10, NULL);
			if (p){
				p->TouchEvent();
			}
		}
	}
}

void FreeLayer::AddFreeItems(){
	for (int i = 0; i < 10;i++){
		Rank rk;
		FreeItemLayer *p = FreeItemLayer::create(rk);
		GameDataSet::PushScrollItem(m_sbg, 0, 0, p, i, m_ScrollView);
	}
}