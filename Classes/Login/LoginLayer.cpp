#include "LoginLayer.h"
#include "SimpleAudioEngine.h"
#include "AppMacros.h"
#include "GameDataSet.h"
#include "HttpInfo.h"
#include "GameControl.h"
#include "ClientSocket.h"
#include "YLJni.h"
#include "LoginInfo.h"
#include "RegLayer.h"

USING_NS_CC;

string LoginLayer::m_uid = "";
string LoginLayer::m_pwd = "";
string LoginLayer::m_pwdmd5 = "";
LoginLayer::LoginLayer(){
	GameControl::getIns()->setLoginLayer(this);
}

LoginLayer::~LoginLayer(){
	if (m_input1){
		m_input1->removeFromParentAndCleanup(true);
	}
	if (m_input2){
		m_input2->removeFromParentAndCleanup(true);
	}
	RootRegister::getIns()->resetWidget(m_RootLayer);
	if (this==GameControl::getIns()->getLoginLayer()){
		GameControl::getIns()->setLoginLayer(NULL);
	}
}

bool LoginLayer::init()
{
	if (!Layer::init())
    {
        return false;
    }

 	m_RootLayer =RootRegister::getIns()->getWidget("Loginlayer.json");
 	this->addChild(m_RootLayer);
	SEL_TouchEvent selector = toucheventselector(LoginLayer::TouchEvent);
	
	GameDataSet::getButton(m_RootLayer, "registr_btn", selector, this);
	GameDataSet::getButton(m_RootLayer, "login_btn", selector, this);
	GameDataSet::getButton(m_RootLayer, "close_btn", selector, this);


	Layout *in = GameDataSet::getLayout(m_RootLayer, "name_edit_bg");
	m_input1 = LoginMainLayer::AddCursorTextField(in, 24);
	m_input1->setPlaceHolder(XXIconv::GBK2UTF("请输入ID").c_str());
	m_input1->setFontColor(ccc3(0x38, 0x4E, 0x9C));
	m_input1->setInputMode(ui::EditBox::InputMode::ANY);

	Layout *in2 = GameDataSet::getLayout(m_RootLayer, "pass_edit_bg");
	m_input2 = LoginMainLayer::AddCursorTextField(in2, 24);
	m_input2->setPlaceHolder(XXIconv::GBK2UTF("请输入6位以上密码").c_str());
	m_input2->setFontColor(ccc3(0x38, 0x4E, 0x9C));
	m_input2->setInputMode(ui::EditBox::InputMode::ANY);

	UserDefault *pUserDefault = UserDefault::sharedUserDefault();
	string uid = pUserDefault->getStringForKey("abc1","");
	string pwd = pUserDefault->getStringForKey("ccc1","");
	if (!uid.empty()){
		m_input1->setText(uid.c_str());
		m_input2->setText(pwd.c_str());
	}

    return true;
}

void LoginLayer::TouchEvent(Object *obj, TouchEventType type){
	if (type == TOUCH_EVENT_ENDED){
		Button *btn = (Button *)obj;
		string name = btn->getName();
		LoginInfo *pLoginInfo = LoginInfo::getIns();
		if (name.compare("registr_btn") == 0){
			RegLayer *p = GameControl::getIns()->getRegLayer();
			if (!p){
				p = RegLayer::create();
				this->addChild(p);
			}
		}
		else if (name.compare("login_btn") == 0){
			string uid = m_input1->getText();
			string pwd = m_input2->getText();
			if (uid.empty()){
				GameControl::getIns()->ShowTopTip(XXIconv::GBK2UTF("ID不能为空"));
			}
			else if (pwd.empty()){
				GameControl::getIns()->ShowTopTip(XXIconv::GBK2UTF("密码不能为空"));
			}
			else{
				pLoginInfo->setLoginType(LOGIN_YK);
				m_uid = uid;
				m_pwd = pwd;
				MD55 md5;
				md5.update(pwd);
				m_pwdmd5 = md5.toString();
				HttpInfo *p = HttpInfo::getIns();
				ClientSocket::getIns()->connect(p->m_ip.c_str(), p->m_port);
			}
		}
		else if (name.compare("close_btn") == 0){
			this->removeFromParentAndCleanup(true);
		}
	}
}