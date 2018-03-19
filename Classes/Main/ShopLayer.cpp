#include "ShopLayer.h"
#include "GameControl.h"
#include "GameDataSet.h"
#include "ClientSocket.h"
#include "LogoScene.h"
#include "LoginInfo.h"



ShopItemLayer::ShopItemLayer(){

}

ShopItemLayer::~ShopItemLayer(){

}

ShopItemLayer *ShopItemLayer::create(ShopItem item){
	ShopItemLayer *p = new ShopItemLayer();
	if (p&&p->init(item)){
		p->autorelease();
	}
	else{
		CC_SAFE_DELETE(p);
	}
	return p;
}

bool ShopItemLayer::init(ShopItem item)
{
	if (!Layer::init())
	{
		return false;
	}
	m_item = item;
	m_RootLayer = (Layout *)GUIReader::shareReader()->widgetFromJsonFile("shopitem.json");
	this->addChild(m_RootLayer);

	this->setContentSize(m_RootLayer->getSize());

	int buynumber = item.number();
	bool hot = item.hot();
	int type = item.type();
	Prop prop = item.prop();
	int id = prop.id();
	string name = prop.name();
	int number = prop.number();

	Layout *hotly = GameDataSet::getLayout(m_RootLayer,"hot");
	hotly->setVisible(hot);
	char buff[30];
	sprintf(buff, XXIconv::GBK2UTF("%d元").c_str(), buynumber);
	GameDataSet::setTextBMFont(m_RootLayer,"BitmapLabel",buff);

	sprintf(buff, "%s%s", GameDataSet::getCNStringByInteger(number).c_str(),name.c_str());
	GameDataSet::setTextBMFont(m_RootLayer, "BitmapLabel_name", buff);

	int znumber = item.givenum();
	sprintf(buff, XXIconv::GBK2UTF("增%s").c_str(), GameDataSet::getCNStringByInteger(znumber).c_str());
	GameDataSet::setText(m_RootLayer,"zeng",buff);

	string icon;
	if (id == 2){

	}
	else if (id == 1){
		GameDataSet::setImageView(m_RootLayer, "icon", "card.png");
	}

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
			ShopItem rk;
			rk.set_type(index+1);
			Prop ppp;
			Prop *pp = (Prop *)ccEvent::create_message(ppp.GetTypeName());
			pp->set_id(index + 1);
			rk.set_allocated_prop(pp);
			ShopItemLayer *p = ShopItemLayer::create(rk);
			GameDataSet::PushScrollItem(sbg, 2, 0, p, i, scroll);
		}
	}
}