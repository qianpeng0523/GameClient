#include "LogoLayer.h"
#include "SimpleAudioEngine.h"
#include "AppMacros.h"
#include "GameDataSet.h"
#include "HttpInfo.h"
#include "GameControl.h"
#include "ClientSocket.h"
#include "YLJni.h"
#include "LoginInfo.h"
USING_NS_CC;



LogoLayer::LogoLayer(){
	GameControl::getIns()->setLoginLayer(this);
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(LogoLayer::WXLoginSend), NOTICE_WXLOGIN, NULL);
}

LogoLayer::~LogoLayer(){
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, NOTICE_WXLOGIN);
	RootRegister::getIns()->resetWidget("login.json");
	if (this==GameControl::getIns()->getLoginLayer()){
		GameControl::getIns()->setLoginLayer(NULL);
	}
}

bool LogoLayer::init()
{
	if (!Layer::init())
    {
        return false;
    }

 	m_RootLayer =RootRegister::getIns()->getWidget("login.json");
 	this->addChild(m_RootLayer);
	SEL_TouchEvent selector = toucheventselector(LogoLayer::TouchEvent);
	m_ykloginbtn = GameDataSet::getButton(m_RootLayer, "yklogin_btn", selector, this);
	ShowYKLoginBtn(false);
	HttpInfo::getIns()->requestGateIPAndPort();
    return true;
}

void LogoLayer::ShowYKLoginBtn(bool isshow){
	if (m_ykloginbtn){
		m_ykloginbtn->setVisible(isshow);
	}
}

ui::EditBox *LogoLayer::AddCursorTextField(Layout *parent, int fontsz, bool ispass){
	parent->setClippingEnabled(true);
	parent->setClippingType(Layout::ClippingType::SCISSOR);
	

	CursorItem *pCursorItem = new CursorItem();
	pCursorItem->fontName = "";
	pCursorItem->fontSize = fontsz;
	pCursorItem->dsz = parent->getSize();
	int limit = 100;
	int s = 0;
	ui::EditBox::InputMode mode = ui::EditBox::InputMode::SINGLE_LINE;
	ui::EditBox::InputFlag flag = ui::EditBox::InputFlag::INITIAL_CAPS_WORD;
	if (ispass){
		flag = ui::EditBox::InputFlag::PASSWORD;
	}
	ui::EditBox *pCursorTextField = ui::EditBox::create(pCursorItem->dsz, "touming.png");
	pCursorTextField->setPlaceHolder(pCursorItem->placeholder.c_str());
	pCursorTextField->setTouchEnabled(true);
	pCursorTextField->setAnchorPoint(ccp(0, 0));
	pCursorTextField->setPlaceholderFont(pCursorItem->fontName.c_str(), pCursorItem->fontSize);
	pCursorTextField->setMaxLength(limit);
	pCursorTextField->setInputMode(mode);
	pCursorTextField->setInputFlag(flag);
	pCursorTextField->setFontName(pCursorItem->fontName.c_str());
	pCursorTextField->setFontSize(pCursorItem->fontSize);
	pCursorTextField->setReturnType(ui::EditBox::KeyboardReturnType::DONE);


	parent->addChild(pCursorTextField);


	return pCursorTextField;
}

void LogoLayer::TouchEvent(Object *obj, TouchEventType type){
	if (type == TOUCH_EVENT_ENDED){
		Button *btn = (Button *)obj;
		string name = btn->getName();
		if (name.compare("yklogin_btn") == 0){
			LoginInfo *pLoginInfo = LoginInfo::getIns();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
			pLoginInfo->setLoginType(LOGIN_WX);
			string token = UserDefault::sharedUserDefault()->getStringForKey("token", "");
			if (token.empty()){
				YLJni::WeixinLogin();
			}
			else{
				HttpInfo *p = HttpInfo::getIns();
				ClientSocket::getIns()->connect(p->m_ip.c_str(), p->m_port);
			}
#else
			pLoginInfo->setLoginType(LOGIN_YK);
			HttpInfo *p = HttpInfo::getIns();
			ClientSocket::getIns()->connect(p->m_ip.c_str(), p->m_port);
#endif
			
		}
	}
}

void LogoLayer::WXLoginSend(Object *obj){
	HttpInfo *p = HttpInfo::getIns();
	ClientSocket::getIns()->connect(p->m_ip.c_str(), p->m_port);
}