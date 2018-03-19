﻿#include "ShopLayer.h"
#include "GameControl.h"
#include "GameDataSet.h"
#include "ClientSocket.h"
#include "LogoScene.h"
#include "LoginInfo.h"



ShopItemLayer::ShopItemLayer(){

}

ShopItemLayer::~ShopItemLayer(){

}

ShopItemLayer *ShopItemLayer::create(Rank hall){
	ShopItemLayer *p = new ShopItemLayer();
	if (p&&p->init(hall)){
		p->autorelease();
	}
	else{
		CC_SAFE_DELETE(p);
	}
	return p;
}

bool ShopItemLayer::init(Rank hall)
{
	if (!Layer::init())
	{
		return false;
	}
	m_hall = hall;
	m_RootLayer = (Layout *)GUIReader::shareReader()->widgetFromJsonFile("shopitem.json");
	this->addChild(m_RootLayer);

	this->setContentSize(m_RootLayer->getSize());

	

	return true;
}

void ShopItemLayer::TouchEvent(){

}


























ShopLayer::ShopLayer(){
	GameControl::getIns()->setShopLayer(this);
}

ShopLayer::~ShopLayer(){
	if (this == GameControl::getIns()->getShopLayer()){
		GameControl::getIns()->setShopLayer(NULL);

	}
}

bool ShopLayer::init()
{             
	if (!Layer::init())
    {
        return false;
    }
	
	m_RootLayer = (Layout *)GUIReader::shareReader()->widgetFromJsonFile("shop.json");
	this->addChild(m_RootLayer);

	SEL_TouchEvent selector = toucheventselector(ShopLayer::TouchEvent);
	
	GameDataSet::getButton(m_RootLayer, "close_btn", selector, this);
	m_btns[0] = GameDataSet::getButton(m_RootLayer, "card", selector, this);
	m_btns[1] = GameDataSet::getButton(m_RootLayer, "gold", selector, this);
	
	m_btntext[0] = (TextBMFont *)GameDataSet::getLayout(m_RootLayer, "BitmapLabel_card");
	m_btntext[1] = (TextBMFont *)GameDataSet::getLayout(m_RootLayer, "BitmapLabel_gold");

	DBUserInfo user = LoginInfo::getIns()->getMyDBUserInfo();
	string uname = user.username();
	string uid = user.userid();
	int card = user.card();
	long gold = user.gold();
	
	GameDataSet::setTextBMFont(m_RootLayer, "cardnum", GameDataSet::getCNStringByInteger(card));
	GameDataSet::setTextBMFont(m_RootLayer, "goldnum", GameDataSet::getCNStringByInteger(gold));


	m_ScrollView = (ui::ScrollView *)GameDataSet::getButton(m_RootLayer, "ScrollView", selector, this);
	m_sbg = GameDataSet::getLayout(m_RootLayer, "sbg");

	m_ScrollView1 = (ui::ScrollView *)GameDataSet::getButton(m_RootLayer, "ScrollView_1", selector, this);
	m_sbg1 = GameDataSet::getLayout(m_RootLayer, "sbg_1");


	SelectItem(0);
	
    return true;
}

void ShopLayer::SelectItem(int index){
	for (int i = 0; i < 2; i++){
		if (m_btns[i]){
			m_btns[i]->setBright(true);
		}
		if (m_btntext[i]){
			m_btntext[i]->setFntFile("fonts/xiaodan10-1.fnt");
		}
	}
	if (m_btns[index]){
		m_btns[index]->setBright(false);
	}
	if (m_btntext[index]){
		m_btntext[index]->setFntFile("fonts/xiaodan10.fnt");
	}
	addShopItem(index);
}

void ShopLayer::TouchEvent(CCObject *obj, TouchEventType type){
	Button *btn = (Button *)obj;
	string name = btn->getName();
	if (type == TOUCH_EVENT_ENDED){
		if (name.compare("close_btn") == 0){
			this->removeFromParentAndCleanup(true);
		}
		else if (name.compare("card") == 0){
			SelectItem(0);
		}
		else if (name.compare("gold") == 0){
			SelectItem(1);
		}
	}
}

void ShopLayer::addShopItem(int index){
	Layout *sbg;
	ui::ScrollView *scroll;
	if (index == 0){
		sbg = m_sbg;
		scroll = m_ScrollView;
		m_ScrollView->setVisible(true);
		m_ScrollView1->setVisible(false);
	}
	else{
		sbg = m_sbg1;
		scroll = m_ScrollView1;
		m_ScrollView->setVisible(false);
		m_ScrollView1->setVisible(true);
	}
	if (sbg->getChildrenCount() == 0){
		for (int i = 0; i < 10; i++){
			Rank rk;
			rk.set_lv(i + 1);
			ShopItemLayer *p = ShopItemLayer::create(rk);
			GameDataSet::PushScrollItem(sbg, 2, 0, p, i, scroll);
		}
	}
}