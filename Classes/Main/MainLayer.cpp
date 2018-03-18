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
#include "FriendLayer.h"

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
	m_ScrollView1 = (ui::ScrollView *)GameDataSet::getButton(m_RootLayer, "ScrollView_1", selector, this);
	m_sbg1 = GameDataSet::getLayout(m_RootLayer, "sbg_1");

	GameDataSet::getButton(m_RootLayer, "head_btn", selector, this);
	GameDataSet::getButton(m_RootLayer, "set_btn", selector, this);
	GameDataSet::getButton(m_RootLayer, "shop_btn", selector, this);
	GameDataSet::getButton(m_RootLayer, "cardadd", selector, this);
	GameDataSet::getButton(m_RootLayer, "goldadd", selector, this);
	GameDataSet::getButton(m_RootLayer, "sign_btn", selector, this);
	GameDataSet::getButton(m_RootLayer, "fankui_btn", selector, this);
	GameDataSet::getButton(m_RootLayer, "duihuan_btn", selector, this);
	GameDataSet::getButton(m_RootLayer, "mianfei_btn", selector, this);
	GameDataSet::getButton(m_RootLayer, "huodong_btn", selector, this);
	GameDataSet::getButton(m_RootLayer, "shouchong_btn", selector, this);
	GameDataSet::getButton(m_RootLayer, "renwu_btn", selector, this);
	GameDataSet::getButton(m_RootLayer, "mail_btn", selector, this);


	m_friendbtns[0] = GameDataSet::getButton(m_RootLayer, "caifu", selector, this);
	m_friendbtns[1] = GameDataSet::getButton(m_RootLayer, "shengju", selector, this);
	GameDataSet::getButton(m_RootLayer, "haoyou_btn", selector, this);

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
	
    return true;
}

void MainLayer::AddFriends(int type){
	Layout *sbg;
	ui::ScrollView *scroll;
	if (type == 0){
		sbg = m_sbg;
		scroll = m_ScrollView;
		m_ScrollView->setVisible(true);
		m_ScrollView1->setVisible(false);
	}
	else{
		sbg = m_sbg1;
		scroll = m_ScrollView1;
		m_ScrollView->setVisible(false);
		m_ScrollView1->setVisible(true);
	}
	if (sbg->getChildrenCount() == 0){
		for (int i = 0; i < 10; i++){
			Rank rk;
			rk.set_lv(i + 1);
			RankItemLayer *p = RankItemLayer::create(rk);
			GameDataSet::PushScrollItem(sbg, 0, 0, p, i, scroll);
		}
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
		}
		else if (name.compare("shengju") == 0){
			SelectItem(1);
		}
		else if (name.compare("sign_btn") == 0){
			SignLayer *p = GameControl::getIns()->getSignLayer();
			if (!p){
				p = SignLayer::create();
				this->addChild(p);
			}
		}
		else if (name.compare("haoyou_btn") == 0){
			FriendLayer *p = GameControl::getIns()->getFriendLayer();
			if (!p){
				p = FriendLayer::create();
				this->addChild(p);
			}
		}
		else if (name.compare("fankui_btn") == 0){
			FankuiLayer *p = GameControl::getIns()->getFankuiLayer();
			if (!p){
				p = FankuiLayer::create();
				this->addChild(p);
			}
		}
		else if (name.compare("mianfei_btn") == 0){
			FreeLayer *p = GameControl::getIns()->getFreeLayer();
			if (!p){
				p = FreeLayer::create();
				this->addChild(p);
			}
		}
		else if (name.compare("duihuan_btn") == 0){
			ExchangeLayer *p = GameControl::getIns()->getExchangeLayer();
			if (!p){
				p = ExchangeLayer::create();
				this->addChild(p);
			}
		}
		else if (name.compare("renwu_btn") == 0){
			TaskLayer *p = GameControl::getIns()->getTaskLayer();
			if (!p){
				p = TaskLayer::create();
				this->addChild(p);
			}
		}
		else if (name.compare("mail_btn") == 0){
			MailLayer *p = GameControl::getIns()->getMailLayer();
			if (!p){
				p = MailLayer::create();
				this->addChild(p);
			}
		}
		else if (name.compare("huodong_btn") == 0){
			ActiveLayer *p = GameControl::getIns()->getActiveLayer();
			if (!p){
				p = ActiveLayer::create();
				this->addChild(p);
			}
		}
		else if (name.compare("shouchong_btn") == 0){
			FirstChargeLayer *p = GameControl::getIns()->getFirstChargeLayer();
			if (!p){
				p = FirstChargeLayer::create();
				this->addChild(p);
			}
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
	AddFriends(index);
}