#include "FankuiLayer.h"
#include "GameControl.h"
#include "GameDataSet.h"
#include "ClientSocket.h"
#include "LoginScene.h"
#include "LoginInfo.h"
#include "HallInfo.h"

FankuiLayer::FankuiLayer(){
	GameControl::getIns()->setFankuiLayer(this);
}

FankuiLayer::~FankuiLayer(){
	m_input->setText("");
	RootRegister::getIns()->resetWidget(m_RootLayer);
	if (this == GameControl::getIns()->getFankuiLayer()){
		GameControl::getIns()->setFankuiLayer(NULL);

	}
}

bool FankuiLayer::init()
{             
	if (!Layer::init())
    {
        return false;
    }
	
	m_RootLayer =RootRegister::getIns()->getWidget("fankui.json");
	this->addChild(m_RootLayer);

	SEL_TouchEvent selector = toucheventselector(FankuiLayer::TouchEvent);
	
	GameDataSet::getButton(m_RootLayer, "close_btn", selector, this);
	m_btn=GameDataSet::getButton(m_RootLayer, "send", selector, this);
	
	Layout *in = GameDataSet::getLayout(m_RootLayer, "in");
	m_input = LoginLayer::AddCursorTextField(in, 24);
	m_input->setPlaceHolder(XXIconv::GBK2UTF("请输入您的反馈意见").c_str());
	m_input->setFontColor(ccc3(0x38, 0x4E, 0x9C));
	m_input->setInputMode(ui::EditBox::InputMode::PHONE_NUMBER);

    return true;
}

void FankuiLayer::TouchEvent(CCObject *obj, TouchEventType type){
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
				UserBase user = LoginInfo::getIns()->getMyUserBase();
				HallInfo::getIns()->SendCFeedBack(user.userid(),user.username() ,content);
			}
			else{
				log("%s",XXIconv::GBK2UTF("您输入的内容为空").c_str());
			}
		}
		
	}
}

void FankuiLayer::FeedBackFinish(){
	m_btn->setVisible(false);
	m_input->setTouchEnabled(false);
	m_input->setText(XXIconv::GBK2UTF("您的反馈已经成功发送，我们会尽快根据您反馈的意见进行修改和优化，谢谢！").c_str());
}