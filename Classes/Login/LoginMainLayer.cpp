#include "LoginMainLayer.h"
#include "SimpleAudioEngine.h"
#include "AppMacros.h"
#include "GameDataSet.h"
#include "HttpInfo.h"
#include "GameControl.h"
#include "ClientSocket.h"
#include "YLJni.h"
#include "LoginInfo.h"
USING_NS_CC;



LoginMainLayer::LoginMainLayer(){
	GameControl::getIns()->setLoginMainLayer(this);
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(LoginMainLayer::WXLoginSend), NOTICE_WXLOGIN, NULL);
}

LoginMainLayer::~LoginMainLayer(){
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, NOTICE_WXLOGIN);
	RootRegister::getIns()->resetWidget(m_RootLayer);
	if (this==GameControl::getIns()->getLoginMainLayer()){
		GameControl::getIns()->setLoginMainLayer(NULL);
	}
}

bool LoginMainLayer::init()
{
	if (!Layer::init())
    {
        return false;
    }

 	m_RootLayer =RootRegister::getIns()->getWidget("login.json");
 	this->addChild(m_RootLayer);
	SEL_TouchEvent selector = toucheventselector(LoginMainLayer::TouchEvent);
	m_ykloginbtn = GameDataSet::getButton(m_RootLayer, "yklogin_btn", selector, this);
	m_wxloginbtn = GameDataSet::getButton(m_RootLayer, "wxlogin_btn", selector, this);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	m_wxloginbtn->setVisible(false);
#else
	m_ykloginbtn->setVisible(false);
#endif

	ShowYKLoginBtn(false);
	HttpInfo::getIns()->requestGateIPAndPort();
    return true;
}

void LoginMainLayer::ShowYKLoginBtn(bool isshow){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	if (m_ykloginbtn){
		m_ykloginbtn->setVisible(isshow);
	}
#else
	if (m_wxloginbtn){
		m_wxloginbtn->setVisible(isshow);
	}
#endif
}

ui::EditBox *LoginMainLayer::AddCursorTextField(Layout *parent, int fontsz, bool ispass){
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

void LoginMainLayer::TouchEvent(Object *obj, TouchEventType type){
	if (type == TOUCH_EVENT_ENDED){
		Button *btn = (Button *)obj;
		string name = btn->getName();
		LoginInfo *pLoginInfo = LoginInfo::getIns();
		if (name.compare("yklogin_btn") == 0){
			LoginLayer *p = GameControl::getIns()->getLoginLayer();
			if (!p){
				p = LoginLayer::create();
				this->addChild(p);
			}
		}
		else if (name.compare("wxlogin_btn") == 0){
			pLoginInfo->setLoginType(LOGIN_WX);
			string token = UserDefault::sharedUserDefault()->getStringForKey("token", "");
			if (token.empty()){
				YLJni::WeixinLogin();
			}
			else{
				HttpInfo *p = HttpInfo::getIns();
				ClientSocket::getIns()->connect(p->m_ip.c_str(), p->m_port);
			}
		}
	}
}

void LoginMainLayer::WXLoginSend(Object *obj){
	HttpInfo *p = HttpInfo::getIns();
	ClientSocket::getIns()->connect(p->m_ip.c_str(), p->m_port);
}