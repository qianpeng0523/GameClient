#include "MainLayer.h"
#include "GameControl.h"
#include "GameDataSet.h"
#include "ClientSocket.h"
#include "LogoScene.h"
#include "LoginInfo.h"
#include "UserInfoLayer.h"
#include "ShopLayer.h"
#include "RankItemLayer.h"
#include "SignLayer.h"

MainLayer::MainLayer(){
	GameControl::getIns()->setMainLayer(this);
}

MainLayer::~MainLayer(){
	if (this == GameControl::getIns()->getMainLayer()){
		GameControl::getIns()->setMainLayer(NULL);

	}
}

bool MainLayer::init()
{             
	if (!Layer::init())
    {
        return false;
    }
	
	m_RootLayer = (Layout *)GUIReader::shareReader()->widgetFromJsonFile("mainlayer.json");
	this->addChild(m_RootLayer);

	SEL_TouchEvent selector = toucheventselector(MainLayer::TouchEvent);
	
	m_ScrollView = (ui::ScrollView *)GameDataSet::getButton(m_RootLayer, "ScrollView", selector, this);
	m_sbg = GameDataSet::getLayout(m_RootLayer, "sbg");
	GameDataSet::getButton(m_RootLayer, "head_btn", selector, this);
	GameDataSet::getButton(m_RootLayer, "set_btn", selector, this);
	GameDataSet::getButton(m_RootLayer, "shop_btn", selector, this);
	GameDataSet::getButton(m_RootLayer, "cardadd", selector, this);
	GameDataSet::getButton(m_RootLayer, "goldadd", selector, this);
	GameDataSet::getButton(m_RootLayer, "sign_btn", selector, this);
	m_friendbtns[0] = GameDataSet::getButton(m_RootLayer, "caifu", selector, this);
	m_friendbtns[1] = GameDataSet::getButton(m_RootLayer, "shengju", selector, this);
	
	DBUserInfo user = LoginInfo::getIns()->getMyDBUserInfo();
	string uname = user.username();
	string uid = user.userid();
	int card = user.card();
	long gold = user.gold();
	GameDataSet::setText(m_RootLayer,"id","ID:"+uid);
	GameDataSet::setText(m_RootLayer, "name", uname);
	GameDataSet::setTextBMFont(m_RootLayer, "card", card);
	GameDataSet::setTextBMFont(m_RootLayer, "gold", GameDataSet::getCNStringByInteger(gold));

	SelectItem(0);
	AddFriends(1);
    return true;
}

void MainLayer::AddFriends(int type){
	m_sbg->removeAllChildrenWithCleanup(true);
	m_ScrollView->setInnerContainerSize(m_sbg->getSize());
	for (int i = 0; i < 10;i++){
		Rank rk;
		rk.set_lv(i+1);
		RankItemLayer *p = RankItemLayer::create(rk);
		GameDataSet::PushScrollItem(m_sbg, 0, 0, p, i, m_ScrollView);
	}
}

void MainLayer::TouchEvent(CCObject *obj, TouchEventType type){
	Button *btn = (Button *)obj;
	string name = btn->getName();
	if (type == TOUCH_EVENT_ENDED){
		if (name.compare("head_btn") == 0){
			UserInfoLayer *p = GameControl::getIns()->getUserInfoLayer();
			if (!p){
				p = UserInfoLayer::create();
				this->addChild(p);
			}
		}
		else if (name.compare("set_btn") == 0){
			SetLayer *p = GameControl::getIns()->getSetLayer();
			if (!p){
				p = SetLayer::create();
				this->addChild(p);
			}
		}
		else if (name.compare("shop_btn") == 0){
			ShopLayer *p = GameControl::getIns()->getShopLayer();
			if (!p){
				p = ShopLayer::create();
				this->addChild(p);
			}
		}
		else if (name.compare("cardadd") == 0){
			ShopLayer *p = GameControl::getIns()->getShopLayer();
			if (!p){
				p = ShopLayer::create();
				this->addChild(p);
			}
		}
		else if (name.compare("goldadd") == 0){
			ShopLayer *p = GameControl::getIns()->getShopLayer();
			if (!p){
				p = ShopLayer::create();
				this->addChild(p);
				p->SelectItem(1);
			}
		}
		else if (name.compare("caifu") == 0){
			SelectItem(0);
			AddFriends(0);
		}
		else if (name.compare("shengju") == 0){
			SelectItem(1);
			AddFriends(1);
		}
		else if (name.compare("sign_btn") == 0){
			SignLayer *p = GameControl::getIns()->getSignLayer();
			if (!p){
				p = SignLayer::create();
				this->addChild(p);
			}
		}
		else if (name.compare("shengju") == 0){

		}
	}
}


void MainLayer::SelectItem(int index){
	for (int i = 0; i < 2; i++){
		if (m_friendbtns[i]){
			m_friendbtns[i]->setBright(true);
		}
	}
	if (m_friendbtns[index]){
		m_friendbtns[index]->setBright(false);
	}
}