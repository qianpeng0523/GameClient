#include "MailTipLayer.h"
#include "GameControl.h"
#include "GameDataSet.h"
#include "ClientSocket.h"
#include "LogoScene.h"
#include "LoginInfo.h"
#include "HallInfo.h"

MailTipLayer::MailTipLayer(){
	GameControl::getIns()->setMailTipLayer(this);
}

MailTipLayer::~MailTipLayer(){
	RootRegister::getIns()->resetWidget(m_RootLayer);
	if (this == GameControl::getIns()->getMailTipLayer()){
		GameControl::getIns()->setMailTipLayer(NULL);

	}
}

MailTipLayer *MailTipLayer::create(Mail mail){
	MailTipLayer *p = new MailTipLayer();
	if (p&&p->init(mail)){
		p->autorelease();
	}
	else{
		CC_SAFE_DELETE(p);
	}
	return p;
}

bool MailTipLayer::init(Mail mail)
{             
	if (!Layer::init())
    {
        return false;
    }
	m_mail = mail;
	m_RootLayer =RootRegister::getIns()->getWidget("mailtip.json");
	this->addChild(m_RootLayer);

	SEL_TouchEvent selector = toucheventselector(MailTipLayer::TouchEvent);
	
	m_btn= GameDataSet::getButton(m_RootLayer, "btn", selector, this);
	GameDataSet::getButton(m_RootLayer, "close_btn", selector, this);

	string title = m_mail.title();
	string content = m_mail.content();
	GameDataSet::setText(m_RootLayer, "title", title);
	GameDataSet::setText(m_RootLayer, "content", content);

	char buff[50];
	bool get = m_mail.get();
	int sz = m_mail.prop_size();
	for (int i = 0; i < 2;i++){
		if (i < sz){
			Prop p = m_mail.prop(i);
			sprintf(buff, "BitmapLabel_%d", i + 1);
			GameDataSet::setTextBMFont(m_RootLayer, buff, p.number());
		}
		else{
			sprintf(buff, "icon%d", i + 1);
			Layout *ly = GameDataSet::getLayout(m_RootLayer, buff);
			ly->setVisible(false);
		}
	}
	if (sz == 0){
		m_btn->setVisible(false);
		Layout *ly = GameDataSet::getLayout(m_RootLayer,"awardbg");
		ly->setVisible(false);
	}
	else{
		m_btn->setBright(!get);
	}
    return true;
}

void MailTipLayer::TouchEvent(CCObject *obj, TouchEventType type){
	Button *btn = (Button *)obj;
	string name = btn->getName();
	if (type == TOUCH_EVENT_ENDED){
		UserDefault *p = UserDefault::sharedUserDefault();
		if (name.compare("close_btn") == 0){
			this->removeFromParentAndCleanup(true);
		}
		else if (name.compare("btn") == 0){
			//领取邮件奖励
			int id = m_mail.id();
			HallInfo::getIns()->SendCMailAward(id);
		}
		
	}
}