#include "ChatLayer.h"
#include "GameControl.h"
#include "GameDataSet.h"
#include "ClientSocket.h"
#include "LogoScene.h"
#include "LoginInfo.h"



ChatItemLayer::ChatItemLayer(){
	
}

ChatItemLayer::~ChatItemLayer(){
	RootRegister::getIns()->resetWidget(m_RootLayer);
}

ChatItemLayer *ChatItemLayer::create(string uid, string uname, string content){
	ChatItemLayer *p = new ChatItemLayer();
	if (p&&p->init(uid, uname,content)){
		p->autorelease();
	}
	else{
		CC_SAFE_DELETE(p);
	}
	return p;
}

bool ChatItemLayer::init(string uid, string uname,string content)
{
	if (!Layer::init())
	{
		return false;
	}
	m_uid = uid;
	DBUserInfo user = LoginInfo::getIns()->getMyDBUserInfo();
	m_json = "chatitem1.json";
	if (uid.compare(user.userid()) == 0){
		m_json = "chatitem2.json";
	}
	m_RootLayer = RootRegister::getIns()->getWidget(m_json.c_str());
	this->addChild(m_RootLayer);

	this->setContentSize(m_RootLayer->getSize());

	GameDataSet::setText(m_RootLayer, "name", uname);
	ImageView *img = (ImageView *)GameDataSet::getLayout(m_RootLayer,"conbg");
	Size bgsz = img->getSize();
	Text *tt =GameDataSet::setText(m_RootLayer, "content", content);
	float w = tt->getSize().width;
	if (w + 30 > bgsz.width){
		img->setSize(Size(w+30,bgsz.height));
	}
	return true;
}

void ChatItemLayer::TouchEvent(CCObject *obj, TouchEventType type){
	Button *btn = (Button *)obj;
	string name = btn->getName();
	if (type == TOUCH_EVENT_ENDED){
		UserDefault *p = UserDefault::sharedUserDefault();
		if (name.compare("close_btn") == 0){
			this->removeFromParentAndCleanup(true);
		}
	}
}























ChatLayer::ChatLayer(){
	GameControl::getIns()->setChatLayer(this);
}

ChatLayer::~ChatLayer(){
	RootRegister::getIns()->resetWidget(m_RootLayer);
	if (this == GameControl::getIns()->getChatLayer()){
		GameControl::getIns()->setChatLayer(NULL);

	}
}

ChatLayer *ChatLayer::create(string uid, string uname){
	ChatLayer *p = new ChatLayer();
	if (p&&p->init(uid,uname)){
		p->autorelease();
	}
	else{
		CC_SAFE_DELETE(p);
	}
	return p;
}

bool ChatLayer::init(string uid, string uname)
{             
	if (!Layer::init())
    {
        return false;
    }
	m_uid = uid;
	m_uname = uname;
	m_RootLayer =RootRegister::getIns()->getWidget("chat.json");
	this->addChild(m_RootLayer);

	SEL_TouchEvent selector = toucheventselector(ChatLayer::TouchEvent);
	
	GameDataSet::getButton(m_RootLayer, "close_btn", selector, this);
	GameDataSet::getButton(m_RootLayer, "send", selector, this);
	
	GameDataSet::setText(m_RootLayer, "name", uname);
	m_ScrollView = (ui::ScrollView *)GameDataSet::getButton(m_RootLayer, "ScrollView", selector, this);
	m_sbg = GameDataSet::getLayout(m_RootLayer, "sbg");

	DBUserInfo user = LoginInfo::getIns()->getMyDBUserInfo();
	char buff[100];
	for (int i = 0; i < 20;i++){
		int index = i%2;
		sprintf(buff,"qwert %06d %07d %08d",i*201,i*666,i*789);
		AddChatItem(index, index == 0 ? user.userid() : uid, index == 0 ? user.username() : uname, buff);
	}

	Layout *in = GameDataSet::getLayout(m_RootLayer, "in");
	m_input = LogoLayer::AddCursorTextField(in, 20);
	m_input->setPlaceHolder(XXIconv::GBK2UTF("请输入聊天内容").c_str());
	m_input->setFontColor(ccc3(0x38, 0x4E, 0x9C));
	m_input->setMaxLength(20);
    return true;
}

void ChatLayer::TouchEvent(CCObject *obj, TouchEventType type){
	Button *btn = (Button *)obj;
	string name = btn->getName();
	if (type == TOUCH_EVENT_ENDED){
		UserDefault *p = UserDefault::sharedUserDefault();
		if (name.compare("close_btn") == 0){
			this->removeFromParentAndCleanup(true);
		}
		else if (name.compare("send") == 0){
			string content = m_input->getText();
			if (!content.empty()){
				DBUserInfo user = LoginInfo::getIns()->getMyDBUserInfo();
				AddChatItem(0, user.userid(),user.username(), content);
			}
			else{
				log("%s",XXIconv::GBK2UTF("输入的聊天内容为空").c_str());
			}
		}
	}
}

void ChatLayer::AddChatItem(int index, string uid, string name, string content){
	int count = m_sbg->getChildrenCount();
	ChatItemLayer *p = ChatItemLayer::create(uid,name,content);
	GameDataSet::PushScrollItem(m_sbg, 0, 0, p, count, m_ScrollView);
	m_ScrollView->scrollToBottom(0.01, false);
}