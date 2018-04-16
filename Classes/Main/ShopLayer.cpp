#include "ShopLayer.h"
#include "GameControl.h"
#include "GameDataSet.h"
#include "ClientSocket.h"
#include "LogoScene.h"
#include "LoginInfo.h"
#include "HallInfo.h"


ShopItemLayer::ShopItemLayer(){

}

ShopItemLayer::~ShopItemLayer(){
	RootRegister::getIns()->resetWidget(m_RootLayer);
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
	m_RootLayer =RootRegister::getIns()->getWidget("shopitem.json");
	this->addChild(m_RootLayer);

	this->setContentSize(m_RootLayer->getSize());

	bool hot = item.hot();
	Reward rd = item.prop();
	int number = rd.number();
	Prop prop = rd.prop();
	int id = prop.id();
	string name = prop.name();

	Reward consume = item.consume();
	int buynumber = consume.number();

	Reward give = item.give();
	int givenum = give.number();

	Layout *hotly = GameDataSet::getLayout(m_RootLayer,"hot");
	hotly->setVisible(hot);
	char buff[30];
	sprintf(buff, XXIconv::GBK2UTF("%d元").c_str(), buynumber);
	GameDataSet::setTextBMFont(m_RootLayer,"BitmapLabel",buff);

	sprintf(buff, "%s%s", GameDataSet::getCNStringByInteger(number, true).c_str(), name.c_str());
	m_body = buff;
	GameDataSet::setTextBMFont(m_RootLayer, "BitmapLabel_name", buff);

	sprintf(buff, XXIconv::GBK2UTF("赠%s").c_str(), GameDataSet::getCNStringByInteger(givenum, true).c_str());
	Text *tt =GameDataSet::setText(m_RootLayer,"zeng",buff);
	if (givenum == 0){
		tt->getParent()->setVisible(false);
	}
	string icon;
	if (id == 3){
		GameDataSet::setImageView(m_RootLayer, "icon", "card1.png");
	}

	SEL_TouchEvent selector = toucheventselector(ShopItemLayer::TouchEvent);
	GameDataSet::getButton(m_RootLayer, "btn", selector, this);
	return true;
}

void ShopItemLayer::TouchEvent(CCObject *obj, TouchEventType type){
	Button *btn = (Button *)obj;
	string name = btn->getName();
	if (type == TOUCH_EVENT_ENDED){
		if (name.compare("btn") == 0){
			int id = m_item.id();
			HallInfo::getIns()->SendCAliPayOrder(id, m_body);
			//HallInfo::getIns()->SendCWxpayOrder(id, m_body);
		}
	}
}


























ShopLayer::ShopLayer(){
	GameControl::getIns()->setShopLayer(this);
}

ShopLayer::~ShopLayer(){
	m_sbg->removeAllChildrenWithCleanup(true);
	m_sbg1->removeAllChildrenWithCleanup(true);
	RootRegister::getIns()->resetWidget(m_RootLayer);
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
	
	m_RootLayer =RootRegister::getIns()->getWidget("shop.json");
	this->addChild(m_RootLayer);

	SEL_TouchEvent selector = toucheventselector(ShopLayer::TouchEvent);
	
	GameDataSet::getButton(m_RootLayer, "close_btn", selector, this);
	m_btns[0] = GameDataSet::getButton(m_RootLayer, "card", selector, this);
	m_btns[1] = GameDataSet::getButton(m_RootLayer, "gold", selector, this);
	
	m_btntext[0] = (TextBMFont *)GameDataSet::getLayout(m_RootLayer, "BitmapLabel_card");
	m_btntext[1] = (TextBMFont *)GameDataSet::getLayout(m_RootLayer, "BitmapLabel_gold");

	setData();

	m_ScrollView = (ui::ScrollView *)GameDataSet::getButton(m_RootLayer, "ScrollView", selector, this);
	m_sbg = GameDataSet::getLayout(m_RootLayer, "sbg");

	m_ScrollView1 = (ui::ScrollView *)GameDataSet::getButton(m_RootLayer, "ScrollView_1", selector, this);
	m_sbg1 = GameDataSet::getLayout(m_RootLayer, "sbg_1");


	SelectItem(0);
	HallInfo::getIns()->SendCShop(3);
    return true;
}

void ShopLayer::setData(){
	UserBase user = LoginInfo::getIns()->getMyUserBase();
	string uname = user.username();
	string uid = user.userid();
	int card = user.card();
	long gold = user.gold();

	GameDataSet::setTextBMFont(m_RootLayer, "cardnum", GameDataSet::getCNStringByInteger(card, true));
	GameDataSet::setTextBMFont(m_RootLayer, "goldnum", GameDataSet::getCNStringByInteger(gold, true));
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
			SShop sp = HallInfo::getIns()->getSShop(1);
			int sz = sp.list_size();
			if (sz == 0){
				HallInfo::getIns()->SendCShop(1);
			}
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
		int type = 1;
		if (index == 0){
			type = 3;
		}
		
		SShop sp = HallInfo::getIns()->getSShop(type);
		int sz = sp.list_size();
		for (int i = 0; i < sz; i++){
			ShopItem rk=sp.list(i);
			ShopItemLayer *p = ShopItemLayer::create(rk);
			GameDataSet::PushScrollItem(sbg, 2, 0, p, i, scroll);
		}
	}
}