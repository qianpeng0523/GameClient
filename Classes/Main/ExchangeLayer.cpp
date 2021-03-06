﻿#include "ExchangeLayer.h"
#include "GameControl.h"
#include "GameDataSet.h"
#include "ClientSocket.h"
#include "LoginScene.h"
#include "HallInfo.h"
#include "LoginInfo.h"



ExchangeItemLayer::ExchangeItemLayer(){

}

ExchangeItemLayer::~ExchangeItemLayer(){
	Text *tt1 = (Text *)GameDataSet::getLayout(m_RootLayer, "num");
	tt1->setPositionY(m_posy);
	RootRegister::getIns()->resetWidget(m_RootLayer);
}

ExchangeItemLayer *ExchangeItemLayer::create(ExAward hall){
	ExchangeItemLayer *p = new ExchangeItemLayer();
	if (p&&p->init(hall)){
		p->autorelease();
	}
	else{
		CC_SAFE_DELETE(p);
	}
	return p;
}

bool ExchangeItemLayer::init(ExAward hall)
{
	if (!Layer::init())
	{
		return false;
	}
	m_hall = hall;
	m_RootLayer =RootRegister::getIns()->getWidget("exchangeitem.json");
	this->addChild(m_RootLayer);

	this->setContentSize(m_RootLayer->getSize());

	
	string title = hall.title();
	int pid = hall.eid();
	int gold = LoginInfo::getIns()->getMyUserBase().gold();
	Reward rd = hall.award();
	Reward rd1 = hall.buy();
	int number = rd.number();

	char buff[50];
	Prop p = rd.prop();
	int id = p.id();

	ImageView *img = (ImageView *)GameDataSet::getLayout(m_RootLayer, "icon");
	GameDataSet::setVirProp(img, id);

	Text *tt1 = (Text *)GameDataSet::getLayout(m_RootLayer, "num");
	m_posy = tt1->getPositionY();
	if (id == 4){
		sprintf(buff, XXIconv::GBK2UTF("%d元").c_str(), number);
	}
	else if (id == 5){
		sprintf(buff, XXIconv::GBK2UTF("%d个").c_str(), number);
	}
	else if (id == 3){
		sprintf(buff, XXIconv::GBK2UTF("%d张").c_str(), number);
	}
	if (tt1){
		tt1->setText(buff);
	}

	int number1 = rd1.number();
	
	sprintf(buff, "%d/%d", gold, number1);
	GameDataSet::setText(m_RootLayer, "pro", buff);

	bool can = gold >= number1;
	Layout *ly = GameDataSet::getLayout(m_RootLayer, "hot");
	ly->setVisible(can);

	GameDataSet::setText(m_RootLayer, "title", title);

	LoadingBar *bar = (LoadingBar *)GameDataSet::getLayout(m_RootLayer, "ProgressBar");
	bar->setPercent(gold*1.0 / number1 * 100);
	
	SEL_TouchEvent selector = toucheventselector(ExchangeItemLayer::TouchEvent);
	Button *btn = GameDataSet::getButton(m_RootLayer, "btn", selector, this);
	btn->setBright(can);
	return true;
}

void ExchangeItemLayer::TouchEvent(CCObject *obj, TouchEventType type){
	Button *btn = (Button *)obj;
	string name = btn->getName();
	if (type == TOUCH_EVENT_ENDED){
		if (name.compare("btn") == 0){
			int id = m_hall.eid();
			HallInfo::getIns()->SendCExchange(id);
		}
	}
}










ExchangeRecordItemLayer::ExchangeRecordItemLayer(){

}

ExchangeRecordItemLayer::~ExchangeRecordItemLayer(){
	RootRegister::getIns()->resetWidget(m_RootLayer);
}

ExchangeRecordItemLayer *ExchangeRecordItemLayer::create(ExRecord hall){
	ExchangeRecordItemLayer *p = new ExchangeRecordItemLayer();
	if (p&&p->init(hall)){
		p->autorelease();
	}
	else{
		CC_SAFE_DELETE(p);
	}
	return p;
}

bool ExchangeRecordItemLayer::init(ExRecord hall)
{
	if (!Layer::init())
	{
		return false;
	}
	m_hall = hall;
	m_RootLayer =RootRegister::getIns()->getWidget("exchangerecorditem.json");
	this->addChild(m_RootLayer);

	this->setContentSize(m_RootLayer->getSize());

	string title = hall.title();
	string orderid = hall.orderid();
	string time = hall.time();
	int status = hall.status();
	GameDataSet::setText(m_RootLayer,"name",title);
	GameDataSet::setText(m_RootLayer, "orderid", orderid);
	GameDataSet::setText(m_RootLayer, "time", time);
	string str;
	Color3B c3;
	if (status == 0){
		str = "正在处理";
		c3 = ccc3(255,0,0);
	}
	else if (status == 1){
		str = "已兑换";
		c3 = ccc3(0, 255, 0);
	}
	else{
		str = "兑换失败";
		c3 = ccc3(120, 120, 120);
	}
	Text *tt= GameDataSet::setText(m_RootLayer, "statu", XXIconv::GBK2UTF(str.c_str()));
	tt->setColor(c3);
	return true;
}

void ExchangeRecordItemLayer::TouchEvent(){
	
}










ExchangeLayer::ExchangeLayer(){
	GameControl::getIns()->setExchangeLayer(this);
}

ExchangeLayer::~ExchangeLayer(){
	m_input->removeFromParentAndCleanup(true);
	RootRegister::getIns()->resetWidget(m_RootLayer);
	if (this == GameControl::getIns()->getExchangeLayer()){
		GameControl::getIns()->setExchangeLayer(NULL);

	}
}

bool ExchangeLayer::init()
{             
	if (!Layer::init())
    {
        return false;
    }
	
	m_RootLayer =RootRegister::getIns()->getWidget("exchange.json");
	this->addChild(m_RootLayer);

	SEL_TouchEvent selector = toucheventselector(ExchangeLayer::TouchEvent);
	
	GameDataSet::getButton(m_RootLayer, "close_btn", selector, this);
	m_ScrollView1 = (ui::ScrollView *)GameDataSet::getButton(m_RootLayer, "ScrollView_0", selector, this);
	m_sbg1 = GameDataSet::getLayout(m_RootLayer, "sbg_0");
	m_ScrollView3 = (ui::ScrollView *)GameDataSet::getButton(m_RootLayer, "ScrollView_2", selector, this);
	m_sbg3 = GameDataSet::getLayout(m_RootLayer, "sbg_2");
	m_sbg2 = GameDataSet::getLayout(m_RootLayer, "sbg_1");

	m_btns[0] = GameDataSet::getButton(m_RootLayer, "jiang", selector, this);
	m_btns[1] = GameDataSet::getButton(m_RootLayer, "duihuan", selector, this);
	m_btns[2] = GameDataSet::getButton(m_RootLayer, "records", selector, this);
	m_btntext[0] = (TextBMFont *)GameDataSet::getLayout(m_RootLayer, "BitmapLabel_jiang");
	m_btntext[1] = (TextBMFont *)GameDataSet::getLayout(m_RootLayer, "BitmapLabel_duihuan");
	m_btntext[2] = (TextBMFont *)GameDataSet::getLayout(m_RootLayer, "BitmapLabel_records");
	GameDataSet::getButton(m_RootLayer, "btn", selector, this);
	m_top = GameDataSet::getLayout(m_RootLayer,"top");

	Layout *in = GameDataSet::getLayout(m_RootLayer, "in");
	m_input = LoginMainLayer::AddCursorTextField(in, 20);
	m_input->setPlaceHolder(XXIconv::GBK2UTF("请输入兑换码").c_str());
	m_input->setFontColor(ccc3(0x98, 0x4E, 0x9C));
	
	UserBase user = LoginInfo::getIns()->getMyUserBase();
	int gold = user.gold();
	GameDataSet::setTextBMFont(m_RootLayer, "goldnum", GameDataSet::getCNStringByInteger(gold));
	ShowTip(false);
	SExchangeReward ser = HallInfo::getIns()->getSExchangeReward();
	if (ser.list_size() == 0){
		HallInfo::getIns()->SendCExchangeReward();
	}
	else{
		AddExchangeItems();
		SelectItem(0);
	}
	
	//SelectItem(0);
    return true;
}

void ExchangeLayer::TouchEvent(CCObject *obj, TouchEventType type){
	Button *btn = (Button *)obj;
	string name = btn->getName();
	if (type == TOUCH_EVENT_ENDED){
		if (name.compare("close_btn") == 0){
			this->removeFromParentAndCleanup(true);
		}
		else if (name.compare("ScrollView_0") == 0){
			
		}
		else if (name.compare("jiang") == 0){
			SelectItem(0);
		}
		else if (name.compare("duihuan") == 0){
			SelectItem(1);
		}
		else if (name.compare("records") == 0){
			SExchangeRecord se = HallInfo::getIns()->getSExchangeRecord();
			if (se.list_size() == 0){
				HallInfo::getIns()->SendCExchangeRecord();
			}
			SelectItem(2);
		}
		else if (name.compare("btn") == 0){
			string code = m_input->getText();
			if (!code.empty()){
				HallInfo::getIns()->SendCExchangeCode(code, "");
			}
			else{
				log("%s",XXIconv::GBK2UTF("兑换码不能为空").c_str());
			}
		}
	}
}

void ExchangeLayer::AddExchangeItems(){
	m_sbg1->removeAllChildrenWithCleanup(true);
	if (m_sbg1->getChildrenCount() == 0){
		SExchangeReward ser = HallInfo::getIns()->getSExchangeReward();
		int sz = ser.list_size();
		for (int i = 0; i < sz; i++){
			ExAward rk=ser.list(i);
			ExchangeItemLayer *p = ExchangeItemLayer::create(rk);
			GameDataSet::PushScrollItem(m_sbg1, 3, 0, p, i, m_ScrollView1);
		}
	}
}

void ExchangeLayer::AddRecords(){
	m_sbg3->removeAllChildrenWithCleanup(true);
	if (m_sbg3->getChildrenCount() == 0){
		SExchangeRecord ser = HallInfo::getIns()->getSExchangeRecord();
		int sz = ser.list_size();
		for (int i = 0; i < sz; i++){
			ExRecord rk=ser.list(i);
			ExchangeRecordItemLayer *p = ExchangeRecordItemLayer::create(rk);
			GameDataSet::PushScrollItem(m_sbg3, 0, 0, p, i, m_ScrollView3);
		}
		if (sz == 0){
			ShowTip(true);
		}
		else{
			ShowTip(false);
		}
	}
}

void ExchangeLayer::SelectItem(int index){
	for (int i = 0; i < 3; i++){
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
	if (index != 2){
		ShowTip(false);
	}
	m_ScrollView1->setVisible(false);
	m_ScrollView3->setVisible(false);
	m_sbg2->setVisible(false);
	if (index == 0){
		m_ScrollView1->setVisible(true);
		m_top->setVisible(false);
		AddExchangeItems();
		ShowTip(false);
	}
	else if (index == 1){
		m_sbg2->setVisible(true);
		m_top->setVisible(false);
		ShowTip(false);
	}
	else if (index == 2){
		m_ScrollView3->setVisible(true);
		AddRecords();
		m_top->setVisible(true);
	}
}

void ExchangeLayer::ShowTip(bool iss){
	ImageView *img = (ImageView *)GameDataSet::getLayout(m_RootLayer,"tip2");
	img->setVisible(iss);
}