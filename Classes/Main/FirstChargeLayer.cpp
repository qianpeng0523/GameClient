#include "FirstChargeLayer.h"
#include "GameControl.h"
#include "GameDataSet.h"
#include "ClientSocket.h"
#include "LoginScene.h"
#include "LoginInfo.h"
#include "HallInfo.h"


FirstChargeLayer::FirstChargeLayer(){
	m_type = 2;
	GameControl::getIns()->setFirstChargeLayer(this);
}

FirstChargeLayer::~FirstChargeLayer(){
	RootRegister::getIns()->resetWidget(m_RootLayer);
	if (this == GameControl::getIns()->getFirstChargeLayer()){
		GameControl::getIns()->setFirstChargeLayer(NULL);

	}
}

bool FirstChargeLayer::init()
{             
	if (!Layer::init())
    {
        return false;
    }
	
	m_RootLayer =RootRegister::getIns()->getWidget("firstcharge.json");
	this->addChild(m_RootLayer);

	SEL_TouchEvent selector = toucheventselector(FirstChargeLayer::TouchEvent);
	
	GameDataSet::getButton(m_RootLayer, "close_btn", selector, this);
	GameDataSet::getButton(m_RootLayer, "btn", selector, this);
	GameDataSet::getButton(m_RootLayer, "ali", selector, this);
	GameDataSet::getButton(m_RootLayer, "weixin", selector, this);
	GameDataSet::getButton(m_RootLayer, "apple", selector, this);

	m_btnbgs[2] = (ImageView *)GameDataSet::getLayout(m_RootLayer, "alibg");
	m_btnbgs[1] =  (ImageView *)GameDataSet::getLayout(m_RootLayer, "weixinbg");
	m_btnbgs[0] = (ImageView *)GameDataSet::getLayout(m_RootLayer, "applebg");
	setButton(2,true);
	char buff[50];
	for (int i = 0; i < 2; i++){
		sprintf(buff, "give%d", i + 1);
		ImageView *img = (ImageView *)GameDataSet::getLayout(m_RootLayer,buff);
		img->setVisible(false);

		sprintf(buff, "prop%d", i + 1);
		ImageView *img1 = (ImageView *)GameDataSet::getLayout(m_RootLayer, buff);
		img1->setVisible(false);

		sprintf(buff, "BitmapLabel_give%d", i + 1);
		Layout *tt= GameDataSet::getLayout(m_RootLayer, buff);
		tt->setVisible(false);
	}
	setData();
    return true;
}

void FirstChargeLayer::TouchEvent(CCObject *obj, TouchEventType type){
	Button *btn = (Button *)obj;
	string name = btn->getName();
	if (type == TOUCH_EVENT_ENDED){
		UserDefault *p = UserDefault::sharedUserDefault();
		if (name.compare("close_btn") == 0){
			this->removeFromParentAndCleanup(true);
		}
		else if (name.compare("btn") == 0){
			HallInfo::getIns()->SendCFirstBuy(m_type);
		}
		else if (name.compare("ali") == 0){
			m_type = 3;
			setButton(m_type,true);
		}
		else if (name.compare("weixin") == 0){
			m_type = 2;
			setButton(m_type, true);
		}
		else if (name.compare("apple") == 0){
			m_type = 1;
			setButton(m_type, true);
		}
		
	}
}

void FirstChargeLayer::setButton(int index, bool iss){
	for (int i = 0; i < 3; i++){
		m_btnbgs[i]->setVisible((index - 1) == i ? iss : false);
	}
}

void FirstChargeLayer::setData(){
	SFirsyBuyData sfbd = HallInfo::getIns()->getSFirsyBuyData();
	Reward con = sfbd.consume();
	Prop conprop = con.prop();
	int id = conprop.id();
	int number = con.number();
	GameDataSet::setTextBMFont(m_RootLayer, "BitmapLabel", number);

	char buff[50];
	char buff1[50];
	for (int i = 0; i < sfbd.reward_size(); i++){
		Reward jiang = sfbd.reward(i);
		Prop jiangprop = jiang.prop();
		int id = jiangprop.id();
		int number = jiang.number();
		sprintf(buff, "propnumber%d", i + 1);
		TextBMFont *t= GameDataSet::setTextBMFont(m_RootLayer, buff, GameDataSet::getCNStringByInteger(number,true));
		t->setVisible(true);
		sprintf(buff, "prop%d", i + 1);
		ImageView *img = (ImageView *)GameDataSet::getLayout(m_RootLayer, buff);
		img->setVisible(true);
		GameDataSet::setVirProp(img, id);
	}
	for (int j = 0; j < sfbd.give_size(); j++){
		Reward give = sfbd.give(j);
		Prop giveprop = give.prop();
		int id = giveprop.id();
		int number = give.number();
		sprintf(buff, "BitmapLabel_give%d", j + 1);
		sprintf(buff1, "X%s", GameDataSet::getCNStringByInteger(number,true).c_str());
		TextBMFont *t = GameDataSet::setTextBMFont(m_RootLayer, buff, buff1);
		t->setVisible(true);
		sprintf(buff, "give%d", j + 1);
		ImageView *img = (ImageView *)GameDataSet::getLayout(m_RootLayer, buff);
		GameDataSet::setVirProp(img, id);
		img->setVisible(true);
	}
}