#include "UserInfoLayer.h"
#include "GameControl.h"
#include "GameDataSet.h"
#include "ClientSocket.h"
#include "LogoScene.h"
#include "LoginInfo.h"
#include "PhotoDown.h"
UserInfoLayer::UserInfoLayer(){
	GameControl::getIns()->setUserInfoLayer(this);
}

UserInfoLayer::~UserInfoLayer(){
	PhotoDown::getIns()->erasePhoto(this);
	RootRegister::getIns()->resetWidget(m_RootLayer);
	if (this == GameControl::getIns()->getUserInfoLayer()){
		GameControl::getIns()->setUserInfoLayer(NULL);

	}
}

bool UserInfoLayer::init()
{             
	if (!Layer::init())
    {
        return false;
    }
	
	m_RootLayer =RootRegister::getIns()->getWidget("userinfo.json");
	this->addChild(m_RootLayer);

	SEL_TouchEvent selector = toucheventselector(UserInfoLayer::TouchEvent);
	
	GameDataSet::getButton(m_RootLayer, "close_btn", selector, this);
	
	UserBase user = LoginInfo::getIns()->getMyUserBase();
	string uname = user.username();
	string uid = user.userid();
	int card = user.card();
	long gold = user.gold();
	int sex = user.sex();
	string ip = user.ip();
	int win = user.win();
	int lose = user.lose();
	int ping = user.ping();
	int vip = user.vip();
	GameDataSet::setText(m_RootLayer,"uid","ID:  "+uid);
	GameDataSet::setText(m_RootLayer, "uname", XXIconv::GBK2UTF("昵称:  ")+ uname);
	GameDataSet::setText(m_RootLayer, "ip", "IP:  "+ip);
	GameDataSet::setText(m_RootLayer, "sex", sex == 1 ? XXIconv::GBK2UTF("性别:  男") : XXIconv::GBK2UTF("性别:  女"));
	char buff[100];
	if (win + lose + ping > 0){
		sprintf(buff, XXIconv::GBK2UTF("胜率：%d%% (%d胜%d负%d平)").c_str(), (int)(win*1.0 / (win + lose + ping) * 100), win, lose, ping);
	}
	else{
		sprintf(buff, XXIconv::GBK2UTF("胜率：0%% (%d胜%d负%d平)").c_str(), win, lose, ping);
	}
	GameDataSet::setText(m_RootLayer, "shenglv", buff);
	sprintf(buff,"%s%d", XXIconv::GBK2UTF("等级：LV").c_str(), vip);
	GameDataSet::setText(m_RootLayer, "vip", buff);

	LoadingBar *bar = (LoadingBar *)GameDataSet::getLayout(m_RootLayer,"ProgressBar");
	bar->setPercent(vip*1.0/10.0*100);
	sprintf(buff,"%d/%d",vip,10);
	GameDataSet::setText(m_RootLayer, "pro", buff);

	ImageView *img = (ImageView *)GameDataSet::getLayout(m_RootLayer, "head");
	PhotoDown::getIns()->PushPhoto(this, user.userid(), img, user.picurl(), user.picid());
    return true;
}

void UserInfoLayer::TouchEvent(CCObject *obj, TouchEventType type){
	Button *btn = (Button *)obj;
	string name = btn->getName();
	if (type == TOUCH_EVENT_ENDED){
		if (name.compare("close_btn") == 0){
			this->removeFromParentAndCleanup(true);
		}
	}
}