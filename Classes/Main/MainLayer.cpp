#include "MainLayer.h"
#include "GameControl.h"
#include "GameDataSet.h"
#include "ClientSocket.h"
#include "LoginScene.h"
#include "LoginInfo.h"
#include "UserInfoLayer.h"
#include "ShopLayer.h"
#include "RankItemLayer.h"
#include "SignLayer.h"
#include "FriendLayer.h"
#include "HallInfo.h"
#include "ConfigInfo.h"
#include "PhotoDown.h"
#include "CreateRoomLayer.h"
#include "RoomInfo.h"
MainLayer::MainLayer(){
	m_finish = true;
	GameControl::getIns()->setMainLayer(this);
	RoomInfo::getIns()->setBegin(false);
	memset(m_index,0,sizeof(int)*2);
}

MainLayer::~MainLayer(){
	PhotoDown::getIns()->erasePhoto(this);
	ImageView *bg = (ImageView *)GameDataSet::getLayout(m_RootLayer, "bg");
	char buff[50];
	for (int i = 0; i < 6; i++){
		sprintf(buff,"particle%d",i+1);
		bg->removeChildByName(buff);
		m_pParticleSystem[i] = NULL;
	}
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
	GameDataSet::getButton(m_RootLayer, "game1", selector, this);
	GameDataSet::getButton(m_RootLayer, "game2", selector, this);
	GameDataSet::getButton(m_RootLayer, "game3", selector, this);
	GameDataSet::getButton(m_RootLayer, "game4", selector, this);
	GameDataSet::getButton(m_RootLayer, "mail_btn", selector, this);


	m_friendbtns[0] = GameDataSet::getButton(m_RootLayer, "caifu", selector, this);
	m_friendbtns[1] = GameDataSet::getButton(m_RootLayer, "shengju", selector, this);
	GameDataSet::getButton(m_RootLayer, "haoyou_btn", selector, this);

	setData();

	m_laba = (Text *)GameDataSet::getLayout(m_RootLayer,"Label_laba");
	
	SelectItem(0);
	m_laba->setPositionX(-m_laba->getSize().width*1.1);
	GameControl *pGameControl = GameControl::getIns();
	pGameControl->PushLaBa(XXIconv::GBK2UTF("测试测试测试测试"), -1);
	pGameControl->PushLaBa(XXIconv::GBK2UTF("测试测试测试测试11111111"), 3);
	pGameControl->PushLaBa(XXIconv::GBK2UTF("测试测试测试测试222222222"), 2);

	char buff[50];
	for (int i = 0; i < 6; i++){
		m_pParticleSystem[i] = CCParticleSystemQuad::create("particle/guangxiao3.plist");
		ImageView *bg = (ImageView *)GameDataSet::getLayout(m_RootLayer, "bg");
		bg->addChild(m_pParticleSystem[i], 0);
		sprintf(buff,"particle%d",i+1);
		m_pParticleSystem[i]->setName(buff);
		m_pParticleSystem[i]->setPosition(ccp(320 * i, 640));
	}

	this->runAction(Sequence::create(DelayTime::create(0.5),
		CCCallFunc::create(this, callfunc_selector(MainLayer::test))
		,NULL));

	m_pointmail = (ImageView *)GameDataSet::getLayout(m_RootLayer, "pointmail");
	m_pointshouchong = (ImageView *)GameDataSet::getLayout(m_RootLayer, "pointshouchong");
	m_pointactive = (ImageView *)GameDataSet::getLayout(m_RootLayer, "pointactive");
	m_pointshop = (ImageView *)GameDataSet::getLayout(m_RootLayer, "pointshop");
	m_pointmianfei = (ImageView *)GameDataSet::getLayout(m_RootLayer, "pointmianfei");
	m_pointhaoyou = (ImageView *)GameDataSet::getLayout(m_RootLayer, "pointhaoyou");
	m_pointduihuan = (ImageView *)GameDataSet::getLayout(m_RootLayer, "pointduihuan");
	m_pointreuwu = (ImageView *)GameDataSet::getLayout(m_RootLayer, "pointrenwu");
	m_pointsign = (ImageView *)GameDataSet::getLayout(m_RootLayer, "pointsign");
	setPointTipShow();
	ConfigInfo::getIns()->SendCConfig();
	HallInfo::getIns()->SendCExchangeReward();
	HallInfo::getIns()->SendCFirsyBuyData();
	HallInfo::getIns()->SendCFriend();
	HallInfo::getIns()->SendCFriendChatList();
	
    return true;
}

void MainLayer::test(){
// 	char buff[50];
// 	GameControl *pGameControl = GameControl::getIns();
// 	for (int i = 0; i < 4; i++){
// 		sprintf(buff, "%s%d", XXIconv::GBK2UTF("测试消息").c_str(), rand() % 100000 + 1);
// 		pGameControl->ShowTopTip(buff);
// 	}
// 	this->runAction(Sequence::create(DelayTime::create(4),
// 		CCCallFunc::create(this, callfunc_selector(MainLayer::test))
// 		, NULL));
	GameControl::getIns()->ShowTopTip(" ");
}

void MainLayer::setData(){
	UserBase user = LoginInfo::getIns()->getMyUserBase();
	string uname = user.username();
	string uid = user.userid();
	int card = user.card();
	long gold = user.gold();
	Text *TT= GameDataSet::setText(m_RootLayer, "id", XXIconv::getU8SubString("ID:" + uid, 0, 13, ""));
	TT->setFontSize(18);
	GameDataSet::setText(m_RootLayer, "name", XXIconv::getU8SubString(uname, 0, 9, ""));
	GameDataSet::setTextBMFont(m_RootLayer, "card", card);
	GameDataSet::setTextBMFont(m_RootLayer, "gold", GameDataSet::getCNStringByInteger(gold));
	ImageView *img =(ImageView *)GameDataSet::getLayout(m_RootLayer,"head");
	PhotoDown::getIns()->PushPhoto(this, uid,img,user.picurl(), user.picid());
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
		int tag = ((ui::ScrollView *)obj)->getTag();
		if (tag == 1){
			map<int, Rank> sr = HallInfo::getIns()->getSRank(1);
			if (sr.empty()){
				HallInfo::getIns()->SendCRank(1, m_index[0]++);
			}
			((ui::ScrollView *)obj)->setTag(0);
		}
	}
}

void MainLayer::ScrollViewEvent1(Ref* obj, ScrollviewEventType type){
	if (type == SCROLLVIEW_EVENT_BOUNCE_BOTTOM){
		int tag = ((ui::ScrollView *)obj)->getTag();
		if (tag == 1){
			map<int, Rank> sr = HallInfo::getIns()->getSRank(2);
			if (sr.empty()){
				HallInfo::getIns()->SendCRank(2, m_index[1]++);
			}
			((ui::ScrollView *)obj)->setTag(0);
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
				this->addChild(p,3);
			}
		}
		else if (name.compare("shop_btn") == 0){
			ShopLayer *p = GameControl::getIns()->getShopLayer();
			if (!p){
				p = ShopLayer::create();
				this->addChild(p);
				ShowTip(POINT_SHOP, false);
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
			ShowTip(POINT_ACTIVE, false);
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
			ShowTip(POINT_ACTIVE, false);
		}
		else if (name.compare("shouchong_btn") == 0){
			FirstChargeLayer *p = GameControl::getIns()->getFirstChargeLayer();
			if (!p){
				p = FirstChargeLayer::create();
				this->addChild(p);
			}
		}
		else if (name.compare("game1") == 0){
			
		}
		else if (name.compare("game2") == 0){

		}
		else if (name.compare("game3") == 0){
			CreateRoomLayer *p = GameControl::getIns()->getCreateRoomLayer();
			if (!p){
				p = CreateRoomLayer::create();
				this->addChild(p);
			}
		}
		else if (name.compare("game4") == 0){
			JoinRoomLayer *p = GameControl::getIns()->getJoinRoomLayer();
			if (!p){
				p = JoinRoomLayer::create();
				this->addChild(p);
			}
		}
		
	}
	else if (type == TOUCH_EVENT_BEGAN){
		if (name.compare("ScrollView") == 0){
			btn->setTag(1);
		}
		else if (name.compare("ScrollView_1") == 0){
			btn->setTag(1);
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

void MainLayer::ShowTip(POINTTIP type, bool isshow){
	UserDefault *puser = UserDefault::sharedUserDefault();
	string tt = GameDataSet::getLocalTimeDay();
	string ttlast = GameDataSet::getLocalTimeDay(GameDataSet::getTime() - 24 * 60 * 60);
	int ist = puser->getIntegerForKey((tt+g_pointstr[type]).c_str(),-1);
	if (ist == -1){
		puser->deleteValueForKey((ttlast + g_pointstr[type]).c_str());
	}
	if (ist!=isshow){
		puser->setIntegerForKey((tt + g_pointstr[type]).c_str(), isshow);
	}
	switch (type)
	{
	case POINT_MAIL:
		m_pointmail->setVisible(isshow);
		break;
	case POINT_SHOUCHONG:
		m_pointshouchong->setVisible(isshow);
		break;
	case POINT_ACTIVE:
		m_pointactive->setVisible(isshow);
		break;
	case POINT_SHOP:
		m_pointshop->setVisible(isshow);
		break;
	case POINT_MAINFEI:
		m_pointmianfei->setVisible(isshow);
		break;
	case POINT_HAOYOU:
		m_pointhaoyou->setVisible(isshow);
		break;
	case POINT_DUIHUAN:
		m_pointduihuan->setVisible(isshow);
		break;
	case POINT_RENWU:
		m_pointreuwu->setVisible(isshow);
		break;
	case POINT_SIGN:
		m_pointsign->setVisible(isshow);
		break;
	default:
		break;
	}
}

void MainLayer::setPointTipShow(){
	UserDefault *pUser = UserDefault::sharedUserDefault();
	string tt = GameDataSet::getLocalTimeDay();
	string ttlast = GameDataSet::getLocalTimeDay(GameDataSet::getTime()-24*60*60);
	int ist1 = pUser->getIntegerForKey((tt + g_pointstr[POINT_SHOP]).c_str(), -1);
	if (ist1 == -1){
		pUser->deleteValueForKey((ttlast+g_pointstr[POINT_SHOP]).c_str());
	}
	ShowTip(POINT_SHOP,ist1);

	ist1 = false;
	
	//计算有没有兑换
	int gold = LoginInfo::getIns()->getMyUserBase().gold();
	SExchangeReward ser = HallInfo::getIns()->getSExchangeReward();
	for (int i = 0; i < ser.list_size(); i++){
		Reward rd = ser.list(i).buy();
		int number = rd.number();
		if (gold >= number){
			ist1 = true;
			break;
		}
	}
	ShowTip(POINT_DUIHUAN, ist1);

	SConfig sc=ConfigInfo::getIns()->getSConfig();
	if (sc.active()){
		int ist2 = pUser->getIntegerForKey((tt + g_pointstr[POINT_ACTIVE]).c_str(), -1);
		if (ist2 == -1){
			pUser->deleteValueForKey((ttlast + g_pointstr[POINT_ACTIVE]).c_str());
		}
		ShowTip(POINT_ACTIVE, ist2);
	}
	else{
		ShowTip(POINT_ACTIVE, sc.active());
	}
	ShowTip(POINT_MAIL, sc.mail());
	ShowTip(POINT_SHOUCHONG, sc.firstbuy());
	ShowTip(POINT_RENWU, sc.task());
	ShowTip(POINT_MAINFEI, sc.free());
	ShowTip(POINT_HAOYOU, sc.fri());
	ShowTip(POINT_SIGN, sc.yqs());
}