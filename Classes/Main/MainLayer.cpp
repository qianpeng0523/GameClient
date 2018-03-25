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
#include "HallInfo.h"

MainLayer::MainLayer(){
	m_finish = true;
	GameControl::getIns()->setMainLayer(this);
	memset(m_index,0,sizeof(int)*2);
}

MainLayer::~MainLayer(){
	RootRegister::getIns()->resetWidget(m_RootLayer);
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
	
	m_RootLayer =RootRegister::getIns()->getWidget("mainlayer.json");
	this->addChild(m_RootLayer);

	SEL_TouchEvent selector = toucheventselector(MainLayer::TouchEvent);
	
	m_ScrollView = (ui::ScrollView *)GameDataSet::getButton(m_RootLayer, "ScrollView", selector, this);
	m_ScrollView->addEventListenerScrollView(this, scrollvieweventselector(MainLayer::ScrollViewEvent));
	m_sbg = GameDataSet::getLayout(m_RootLayer, "sbg");
	m_ScrollView1 = (ui::ScrollView *)GameDataSet::getButton(m_RootLayer, "ScrollView_1", selector, this);
	m_ScrollView1->addEventListenerScrollView(this, scrollvieweventselector(MainLayer::ScrollViewEvent1));
	m_sbg1 = GameDataSet::getLayout(m_RootLayer, "sbg_1");

	GameDataSet::getButton(m_RootLayer, "head_btn", selector, this);
	GameDataSet::getButton(m_RootLayer, "set_btn", selector, this);
	Button *shopbtn= GameDataSet::getButton(m_RootLayer, "shop_btn", selector, this);
	for (int i = 0; i < 1; i++){
		ImageView *simg = ImageView::create("plaza_shangcheng.png", Widget::TextureResType::PLIST);
		shopbtn->addChild(simg);
		simg->setPosition(shopbtn->getSize() / 2.0);
		simg->setOpacity(0);
		simg->runAction(RepeatForever::create(Sequence::create(FadeIn::create(1.0), DelayTime::create(0.2), FadeOut::create(1.0), DelayTime::create(0.2), NULL)));
	}
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

	m_laba = (Text *)GameDataSet::getLayout(m_RootLayer,"Label_laba");
	
	SelectItem(0);
	m_laba->setPositionX(-m_laba->getSize().width*1.01);
	GameControl::getIns()->PushLaBa(XXIconv::GBK2UTF("测试测试测试测试"),-1);
	GameControl::getIns()->PushLaBa(XXIconv::GBK2UTF("测试测试测试测试11111111"), 3);
	GameControl::getIns()->PushLaBa(XXIconv::GBK2UTF("测试测试测试测试222222222"), 2);
    return true;
}

void MainLayer::ShowLaBa(string content){
	if (m_laba&&m_laba->getPositionX()<=-m_laba->getSize().width*1.01){
		m_finish = false;
		m_laba->stopAllActions();
		Layout *ly = GameDataSet::getLayout(m_RootLayer,"laba");
		m_laba->setPositionX(ly->getSize().width*1.01);
		m_laba->setText(content);
		m_laba->runAction(Sequence::create(MoveTo::create(10.0, ccp(-m_laba->getSize().width*1.02,m_laba->getPositionY())),
			CCCallFunc::create(this, callfunc_selector(MainLayer::LaBaCall))
			,NULL));
	}
}

void MainLayer::LaBaCall(){
	m_finish = true;
}

void MainLayer::ScrollViewEvent(Ref* obj, ScrollviewEventType type){
	if (type == SCROLLVIEW_EVENT_BOUNCE_BOTTOM){
		map<int, Rank> sr = HallInfo::getIns()->getSRank(1);
		if (sr.empty()){
			HallInfo::getIns()->SendCRank(1, m_index[0]++);
		}
	}
}

void MainLayer::ScrollViewEvent1(Ref* obj, ScrollviewEventType type){
	if (type == SCROLLVIEW_EVENT_BOUNCE_BOTTOM){
		map<int, Rank> sr = HallInfo::getIns()->getSRank(2);
		if (sr.empty()){
			HallInfo::getIns()->SendCRank(2, m_index[1]++);
		}
	}
}

void MainLayer::AddFriends(int type){
	Layout *sbg;
	ui::ScrollView *scroll;
	if (type == 1){
		sbg = m_sbg;
		scroll = m_ScrollView;
	}
	else{
		sbg = m_sbg1;
		scroll = m_ScrollView1;
	}
	int count =sbg->getChildrenCount() ;
	map<int, Rank> sr = HallInfo::getIns()->getSRank(type);
	map<int, Rank>::iterator itr = sr.begin();
	int i = 0;
	for (itr; itr!= sr.end();itr++){
		Rank rk =itr->second;
		RankItemLayer *p = RankItemLayer::create(rk);
		GameDataSet::PushScrollItem(sbg, 0, 0, p, i + count, scroll);
		HallInfo::getIns()->eraseRank(type, rk.lv());
		i++;
	}
	
}

void MainLayer::ShowFriends(int type){
	Layout *sbg;
	if (type == 1){
		sbg = m_sbg;
		m_ScrollView->setVisible(true);
		m_ScrollView1->setVisible(false);
	}
	else{
		sbg = m_sbg1;
		m_ScrollView->setVisible(false);
		m_ScrollView1->setVisible(true);
	}
	if (sbg->getChildrenCount() == 0){
		HallInfo::getIns()->SendCRank(type, m_index[type-1]++);
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
	ShowFriends(index+1);
}