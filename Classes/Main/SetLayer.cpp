#include "SetLayer.h"
#include "GameControl.h"
#include "GameDataSet.h"
#include "ClientSocket.h"
#include "LoginScene.h"
#include "LoginInfo.h"
#include "PhotoDown.h"

SetLayer::SetLayer(){
	GameControl::getIns()->setSetLayer(this);
}

SetLayer::~SetLayer(){
	PhotoDown::getIns()->erasePhoto(this);
	RootRegister::getIns()->resetWidget(m_RootLayer);
	if (this == GameControl::getIns()->getSetLayer()){
		GameControl::getIns()->setSetLayer(NULL);

	}
}

bool SetLayer::init()
{             
	if (!Layer::init())
    {
        return false;
    }
	
	m_RootLayer =RootRegister::getIns()->getWidget("set.json");
	this->addChild(m_RootLayer);

	SEL_TouchEvent selector = toucheventselector(SetLayer::TouchEvent);
	
	GameDataSet::getButton(m_RootLayer, "close_btn", selector, this);
	GameDataSet::getButton(m_RootLayer, "exchange", selector, this);
	GameDataSet::getButton(m_RootLayer, "help", selector, this);
	GameDataSet::getButton(m_RootLayer, "fankui", selector, this);
	GameDataSet::getButton(m_RootLayer, "guanyu", selector, this);
	
	UserBase user = LoginInfo::getIns()->getMyUserBase();
	string uname = user.username();
	string picurl = user.picurl();
	int picid = user.picid();
	
	GameDataSet::setText(m_RootLayer, "name", "ID:"+ uname);

	UserDefault *p = UserDefault::sharedUserDefault();
	char buff[100];
	for (int i = 1; i <= 4;i++){
		sprintf(buff,"set%d",i);
		bool isopen = p->getBoolForKey(buff,true);
		sprintf(buff,"CheckBox_%d",i);
		CheckBox *cb = (CheckBox *)GameDataSet::getButton(m_RootLayer, buff, selector, this);
		SelectCheckBox(i,isopen);
	}

	ImageView *img = (ImageView *)GameDataSet::getLayout(m_RootLayer, "head");
	PhotoDown::getIns()->PushPhoto(this, user.userid(), img, user.picurl(), user.picid());
    return true;
}

void SetLayer::SelectCheckBox(int index, bool isopen){
	char buff[100];
	sprintf(buff, "CheckBox_%d", index);
	CheckBox *cb = (CheckBox *)GameDataSet::getLayout(m_RootLayer, buff);
	cb->setSelectedState(isopen);
	sprintf(buff, "point%d", index);
	Layout *ly = GameDataSet::getLayout(m_RootLayer,buff);
	ly->setPosition(!isopen ? Point(99,25):Point(18,25));
}

void SetLayer::TouchEvent(CCObject *obj, TouchEventType type){
	Button *btn = (Button *)obj;
	string name = btn->getName();
	if (type == TOUCH_EVENT_ENDED){
		UserDefault *p = UserDefault::sharedUserDefault();
		if (name.compare("close_btn") == 0){
			this->removeFromParentAndCleanup(true);
		}
		else if (name.compare("exchange") == 0){
			int err=ClientSocket::getIns()->close();
			if (err == 0){
				ClientSocket::getIns()->setBegin(false);
				GameControl::getIns()->replaceScene(LoginScene::create());
			}
		}
		else if (name.compare("help") == 0){
			HelpLayer *p = GameControl::getIns()->getHelpLayer();
			if (!p){
				p = HelpLayer::create();
				Director::sharedDirector()->getRunningScene()->addChild(p);
			}
		}
		else if (name.compare("fankui") == 0){
			FankuiLayer *p = GameControl::getIns()->getFankuiLayer();
			if (!p){
				p = FankuiLayer::create();
				Director::sharedDirector()->getRunningScene()->addChild(p);
			}
		}
		else if (name.compare("guanyu") == 0){
			AboutLayer *p = GameControl::getIns()->getAboutLayer();
			if (!p){
				p = AboutLayer::create();
				Director::sharedDirector()->getRunningScene()->addChild(p);
			}
		}
		else if (name.compare("CheckBox_1") == 0){
			bool isopen = ((CheckBox *)btn)->getSelectedState();
			SelectCheckBox(1,isopen);
			p->setBoolForKey("set1", isopen);
		}
		else if (name.compare("CheckBox_2") == 0){
			bool isopen = ((CheckBox *)btn)->getSelectedState();
			SelectCheckBox(2, isopen);
			p->setBoolForKey("set2", isopen);
		}
		else if (name.compare("CheckBox_3") == 0){
			bool isopen = ((CheckBox *)btn)->getSelectedState();
			SelectCheckBox(3, isopen);
			p->setBoolForKey("set3", isopen);
		}
		else if (name.compare("CheckBox_4") == 0){
			bool isopen = ((CheckBox *)btn)->getSelectedState();
			SelectCheckBox(4, isopen);
			p->setBoolForKey("set4", isopen);
		}
	}
}