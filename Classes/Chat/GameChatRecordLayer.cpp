#include "GameChatRecordLayer.h"
#include "GameDataSet.h"
#include "LoginInfo.h"
#include "RootRegister.h"
#include "ExpressConfig.h"
#include "YuYinConfig.h"
#include "Common.h"
#include "PhotoDown.h"

GameChatRecordLayer::GameChatRecordLayer(){
	
}

GameChatRecordLayer::~GameChatRecordLayer(){
	RootRegister::getIns()->resetWidget(m_RootLayer);
}

GameChatRecordLayer *GameChatRecordLayer::create(string uid, string uname, string content, string time){
	GameChatRecordLayer *p = new GameChatRecordLayer();
	if (p&&p->init(uid, uname,content,time)){
		p->autorelease();
	}
	else{
		CC_SAFE_DELETE(p);
	}
	return p;
}

bool GameChatRecordLayer::init(string uid, string uname, string content, string time)
{
	if (!Layer::init())
	{
		return false;
	}
	m_uid = uid;
	UserBase user = LoginInfo::getIns()->getMyUserBase();
	
	m_json = "gchatitem1.json";
	if (uid.compare(user.userid()) == 0){
		m_json = "gchatitem2.json";
	}
	m_RootLayer = RootRegister::getIns()->getWidget(m_json.c_str());
	this->addChild(m_RootLayer);

	this->setContentSize(m_RootLayer->getSize());

	ImageView *icon = (ImageView *)GameDataSet::getLayout(m_RootLayer, "icon");
	PhotoDown::getIns()->PushPhoto(this, uid, icon, "", 1);

	Text *namet= GameDataSet::setText(m_RootLayer, "name",uname.empty()?uid:uname);
	Text *timet = GameDataSet::setText(m_RootLayer, "time", time);
	
	m_conbg = (ImageView *)GameDataSet::getLayout(m_RootLayer, "conbg");
	Size bgsz = m_conbg->getSize();
	m_content = GameDataSet::setText(m_RootLayer, "content", Common::sub(content,12,"..."));
	float w = m_content->getSize().width;
	if (w + 30 > bgsz.width){
		m_conbg->setSize(Size(w + 30, bgsz.height));
	}

	m_yuyin = (ImageView *)GameDataSet::getLayout(m_RootLayer, "yuyin");
	m_exp = (ImageView *)GameDataSet::getLayout(m_RootLayer, "exp");
	string tt = content.substr(2,content.length());
	ExpressItem *p = ExpressConfig::shareExpressConfig()->getExpressItemByName(tt);
	if (p){
		m_exp->loadTexture(p->file, Widget::TextureResType::PLIST);
		m_exp->setVisible(true);
		m_conbg->setVisible(false);
		m_content->setVisible(false);
		m_yuyin->setVisible(false);
	}
	else if (content.compare("//record_") == 0){
		m_exp->setVisible(false);
		m_conbg->setVisible(false);
		m_content->setVisible(false);
		m_yuyin->setVisible(true);
	}
	else{
		m_exp->setVisible(false);
		m_yuyin->setVisible(false);
	}
	
	return true;
}

void GameChatRecordLayer::TouchEvent(CCObject *obj, TouchEventType type){
	Button *btn = (Button *)obj;
	string name = btn->getName();
	if (type == TOUCH_EVENT_ENDED){
		
	}
}