#include "RegLayer.h"
#include "SimpleAudioEngine.h"
#include "AppMacros.h"
#include "GameDataSet.h"
#include "HttpInfo.h"
#include "GameControl.h"
#include "ClientSocket.h"
#include "YLJni.h"
#include "LoginInfo.h"
USING_NS_CC;

string RegLayer::m_uname = "";
string RegLayer::m_pwd = "";
string RegLayer::m_pwdmd5 = "";
RegLayer::RegLayer(){
	GameControl::getIns()->setRegLayer(this);
	
}

RegLayer::~RegLayer(){
	m_input1->removeFromParentAndCleanup(true);
	m_input2->removeFromParentAndCleanup(true);
	RootRegister::getIns()->resetWidget(m_RootLayer);
	if (this==GameControl::getIns()->getRegLayer()){
		GameControl::getIns()->setRegLayer(NULL);
	}
}

bool RegLayer::init()
{
	if (!Layer::init())
    {
        return false;
    }

 	m_RootLayer =RootRegister::getIns()->getWidget("reglayer.json");
 	this->addChild(m_RootLayer);
	SEL_TouchEvent selector = toucheventselector(RegLayer::TouchEvent);
	GameDataSet::getButton(m_RootLayer, "registr_btn", selector, this);
	GameDataSet::getButton(m_RootLayer, "close_btn", selector, this);
	
	Layout *in = GameDataSet::getLayout(m_RootLayer, "nickname_edit_bg");
	m_input1 = LoginMainLayer::AddCursorTextField(in, 24);
	m_input1->setPlaceHolder(XXIconv::GBK2UTF("请输入昵称").c_str());
	m_input1->setFontColor(ccc3(0x38, 0x4E, 0x9C));
	m_input1->setInputMode(ui::EditBox::InputMode::ANY);

	Layout *in2 = GameDataSet::getLayout(m_RootLayer, "pass_edit_bg");
	m_input2 = LoginMainLayer::AddCursorTextField(in2, 24);
	m_input2->setPlaceHolder(XXIconv::GBK2UTF("请输入6位以上密码").c_str());
	m_input2->setFontColor(ccc3(0x38, 0x4E, 0x9C));
	m_input2->setInputMode(ui::EditBox::InputMode::ANY);
	m_input2->setInputFlag(ui::EditBox::InputFlag::PASSWORD);
    return true;
}

void RegLayer::TouchEvent(Object *obj, TouchEventType type){
	if (type == TOUCH_EVENT_ENDED){
		Button *btn = (Button *)obj;
		string name = btn->getName();
		LoginInfo *pLoginInfo = LoginInfo::getIns();
		if (name.compare("registr_btn") == 0){
			string nickname = m_input1->getText();
			string pwd = m_input2->getText();
			if (nickname.empty()){
				GameControl::getIns()->ShowTopTip(XXIconv::GBK2UTF("昵称不能为空"));
			}
			else if (pwd.empty()){
				GameControl::getIns()->ShowTopTip(XXIconv::GBK2UTF("密码不能为空"));
			}
			else if (pwd.length() < 6 || pwd.length() > 16){
				GameControl::getIns()->ShowTopTip(XXIconv::GBK2UTF("密码长度须在6-16位"));
			}
			else{
				pLoginInfo->setLoginType(LOGIN_REG);
				m_uname = nickname;
				m_pwd = pwd;
				MD55 md5;
				md5.update(pwd);
				m_pwdmd5 = md5.toString();
				HttpInfo *p = HttpInfo::getIns();
				ClientSocket::getIns()->connect(p->m_ip.c_str(), p->m_port);
				
				//pLoginInfo->SendCRegister("", pwd, nickname);
			}
		}
		else if (name.compare("close_btn") == 0){
			this->removeFromParentAndCleanup(true);
		}
	}
}