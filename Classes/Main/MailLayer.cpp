#include "MailLayer.h"
#include "GameControl.h"
#include "GameDataSet.h"
#include "ClientSocket.h"
#include "LogoScene.h"
#include "LoginInfo.h"
#include "HallInfo.h"



MailItemLayer::MailItemLayer(){

}

MailItemLayer::~MailItemLayer(){
	RootRegister::getIns()->resetWidget(m_RootLayer);
}

MailItemLayer *MailItemLayer::create(Mail mail){
	MailItemLayer *p = new MailItemLayer();
	if (p&&p->init(mail)){
		p->autorelease();
	}
	else{
		CC_SAFE_DELETE(p);
	}
	return p;
}

bool MailItemLayer::init(Mail mail)
{
	if (!Layer::init())
	{
		return false;
	}
	m_mail = mail;
	m_RootLayer =RootRegister::getIns()->getWidget("mailitem.json");
	this->addChild(m_RootLayer);

	this->setContentSize(m_RootLayer->getSize());

	SEL_TouchEvent selector = toucheventselector(MailItemLayer::TouchEvent);
	GameDataSet::getButton(m_RootLayer, "btn", selector, this);

	string title = mail.title();
	string content = mail.content();
	string ctime = mail.time();
	int id = mail.id();
	GameDataSet::setText(m_RootLayer, "title",title);
	GameDataSet::setText(m_RootLayer, "content", content);
	GameDataSet::setText(m_RootLayer, "time", ctime);

	char buff[30];
	sprintf(buff,"100000%d",id);
	bool iskan = UserDefault::sharedUserDefault()->getBoolForKey(buff,false);
	Layout *ly = GameDataSet::getLayout(m_RootLayer, "chakan");
	ly->setVisible(iskan);
	return true;
}

void MailItemLayer::TouchEvent(CCObject *obj, TouchEventType type){
	Button *btn = (Button *)obj;
	string name = btn->getName();
	if (type == TOUCH_EVENT_ENDED){
		UserDefault *p = UserDefault::sharedUserDefault();
		if (name.compare("btn") == 0){
			char buff[30];
			sprintf(buff, "100000%d", m_mail.id());
			bool iskan = UserDefault::sharedUserDefault()->getBoolForKey(buff, false);
			if (!iskan){
				UserDefault::sharedUserDefault()->setBoolForKey(buff, true);
			}
			Layout *ly = GameDataSet::getLayout(m_RootLayer, "chakan");
			ly->setVisible(true);

			MailTipLayer *p = GameControl::getIns()->getMailTipLayer();
			if (!p){
				p = MailTipLayer::create(m_mail);
				Director::sharedDirector()->getRunningScene()->addChild(p);
			}
		}
	}
}





















MailLayer::MailLayer(){
	GameControl::getIns()->setMailLayer(this);
}

MailLayer::~MailLayer(){
	RootRegister::getIns()->resetWidget(m_RootLayer);
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
	
	m_RootLayer =RootRegister::getIns()->getWidget("mail.json");
	this->addChild(m_RootLayer);

	SEL_TouchEvent selector = toucheventselector(MailLayer::TouchEvent);
	
	GameDataSet::getButton(m_RootLayer, "close_btn", selector, this);
	m_ScrollView = (ui::ScrollView *)GameDataSet::getButton(m_RootLayer, "ScrollView", selector, this);
	m_sbg = GameDataSet::getLayout(m_RootLayer, "sbg");
	HallInfo::getIns()->SendCMail();
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
			
		}
	}
}

void MailLayer::AddMailItems(){
	SMail mail = HallInfo::getIns()->getSMail();
	int sz = mail.list_size();
	for (int i = 0; i < sz;i++){
		Mail rk=mail.list(i);
		MailItemLayer *p = MailItemLayer::create(rk);
		GameDataSet::PushScrollItem(m_sbg, 0, 0, p, i, m_ScrollView);
	}
	if (sz>0){
		Layout *tip = GameDataSet::getLayout(m_RootLayer,"tip");
		tip->setVisible(false);
	}
}