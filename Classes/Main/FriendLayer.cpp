#include "FriendLayer.h"
#include "GameControl.h"
#include "GameDataSet.h"
#include "ClientSocket.h"
#include "LoginScene.h"
#include "LoginInfo.h"
#include "HallInfo.h"
#include "PhotoDown.h"


FriendChatItemLayer::FriendChatItemLayer(){

}

FriendChatItemLayer::~FriendChatItemLayer(){
	PhotoDown::getIns()->erasePhoto(this);
	RootRegister::getIns()->resetWidget(m_RootLayer);
}

FriendChatItemLayer *FriendChatItemLayer::create(Friend hall){
	FriendChatItemLayer *p = new FriendChatItemLayer();
	if (p&&p->init(hall)){
		p->autorelease();
	}
	else{
		CC_SAFE_DELETE(p);
	}
	return p;
}

bool FriendChatItemLayer::init(Friend hall)
{
	if (!Layer::init())
	{
		return false;
	}
	m_hall = hall;
	m_RootLayer =RootRegister::getIns()->getWidget("friendchatitem.json");
	this->addChild(m_RootLayer);

	this->setContentSize(m_RootLayer->getSize());

	SEL_TouchEvent selector = toucheventselector(FriendChatItemLayer::TouchEvent);
	GameDataSet::getButton(m_RootLayer, "chat", selector, this);
	GameDataSet::getButton(m_RootLayer, "zeng", selector, this);

	bool online = hall.online();
	UserBase user = hall.info();
	string username = user.username();
	long time = hall.time();
	char buff[100];
	sprintf(buff,"[%s]%s",online?XXIconv::GBK2UTF("在线").c_str():XXIconv::GBK2UTF("离线").c_str(),username.c_str());
	GameDataSet::setText(m_RootLayer, "name", buff);
	if (time < 60){
		sprintf(buff,XXIconv::GBK2UTF("上次在线%d秒前").c_str(),time);
	}
	else if (time < 60 * 60){
		sprintf(buff, XXIconv::GBK2UTF("上次在线%d分前").c_str(), time / 60);
	}
	else if (time<60*60*24){
		sprintf(buff, XXIconv::GBK2UTF("上次在线%d小时前").c_str(), time / (60 * 60));
	}
	else{
		sprintf(buff, XXIconv::GBK2UTF("上次在线%d天前").c_str(), time / (60 * 60*24));
	}
	GameDataSet::setText(m_RootLayer, "time", buff);
	
	ImageView *img = (ImageView *)GameDataSet::getLayout(m_RootLayer, "icon");
	PhotoDown::getIns()->PushPhoto(this, user.userid(), img, user.picurl(), user.picid());

	return true;
}

void FriendChatItemLayer::TouchEvent(CCObject *obj, TouchEventType type){
	Button *btn = (Button *)obj;
	string name = btn->getName();
	if (type == TOUCH_EVENT_ENDED){
		if (name.compare("chat") == 0){
			log("chat");
			ChatLayer *p = GameControl::getIns()->getChatLayer();
			if (!p){
				p = ChatLayer::create(m_hall.info().userid(),m_hall.info().username());
				Director::sharedDirector()->getRunningScene()->addChild(p);
			}
		}
		else if (name.compare("zeng") == 0){
			log("zeng");
			HallInfo::getIns()->SendCGiveFriend(m_hall.info().username());
		}
	}
}







FriendNoticeLayer::FriendNoticeLayer(){

}

FriendNoticeLayer::~FriendNoticeLayer(){
	RootRegister::getIns()->resetWidget(m_RootLayer);
}

FriendNoticeLayer *FriendNoticeLayer::create(FriendNotice hall){
	FriendNoticeLayer *p = new FriendNoticeLayer();
	if (p&&p->init(hall)){
		p->autorelease();
	}
	else{
		CC_SAFE_DELETE(p);
	}
	return p;
}

bool FriendNoticeLayer::init(FriendNotice hall)
{
	if (!Layer::init())
	{
		return false;
	}
	m_hall = hall;
	m_RootLayer =RootRegister::getIns()->getWidget("friendtongzhi.json");
	this->addChild(m_RootLayer);

	this->setContentSize(m_RootLayer->getSize());

	SEL_TouchEvent selector = toucheventselector(FriendNoticeLayer::TouchEvent);
	GameDataSet::getButton(m_RootLayer, "btn1", selector, this);
	GameDataSet::getButton(m_RootLayer, "btn2", selector, this);

	string content = hall.content();
	string time = hall.time();
	GameDataSet::setText(m_RootLayer, "content", content);
	GameDataSet::setText(m_RootLayer, "time", time);

	int status = hall.status();
	Layout *bg = GameDataSet::getLayout(m_RootLayer,"btnbg");
	if (bg){
		bg->setVisible(status==1);
	}

	return true;
}

void FriendNoticeLayer::TouchEvent(CCObject *obj, TouchEventType type){
	Button *btn = (Button *)obj;
	string name = btn->getName();
	if (type == TOUCH_EVENT_ENDED){
		string uid = m_hall.uid();
		if (name.compare("btn1") == 0){
			log("%s",XXIconv::GBK2UTF("拒绝").c_str());
			HallInfo::getIns()->SendCAgreeFriend(uid, m_hall.nid(), false);
		}else if (name.compare("btn2") == 0){
			log("%s", XXIconv::GBK2UTF("同意").c_str());
			HallInfo::getIns()->SendCAgreeFriend(uid,m_hall.nid(), true);
		}
	}
}



















FriendLayer::FriendLayer(){
	memset(m_sbg,NULL,sizeof(Layout *));
	GameControl::getIns()->setFriendLayer(this);
}

FriendLayer::~FriendLayer(){
	PhotoDown::getIns()->erasePhoto(this);
	m_input->removeFromParentAndCleanup(true);
	RootRegister::getIns()->resetWidget(m_RootLayer);
	if (this == GameControl::getIns()->getFriendLayer()){
		GameControl::getIns()->setFriendLayer(NULL);
	}
}

FriendLayer *FriendLayer::create(){
	FriendLayer *p = new FriendLayer();
	if (p&&p->init()){
		p->autorelease();
	}
	else{
		CC_SAFE_DELETE(p);
	}
	return p;
}

bool FriendLayer::init()
{             
	if (!Layer::init())
    {
        return false;
    }
	
	m_RootLayer =RootRegister::getIns()->getWidget("friend.json");
	this->addChild(m_RootLayer);

	this->setContentSize(m_RootLayer->getSize());
	SEL_TouchEvent selector = toucheventselector(FriendLayer::TouchEvent);
	GameDataSet::getButton(m_RootLayer, "close_btn", selector, this);
	
	m_btns[0] = GameDataSet::getButton(m_RootLayer, "find", selector, this);
	m_btns[1] = GameDataSet::getButton(m_RootLayer, "friend", selector, this);
	m_btns[2] = GameDataSet::getButton(m_RootLayer, "tongzhi", selector, this);
	GameDataSet::getButton(m_RootLayer, "search", selector, this);
	GameDataSet::getButton(m_RootLayer, "huan", selector, this);

	m_btntext[0] = (TextBMFont *)GameDataSet::getLayout(m_RootLayer, "BitmapLabel_find");
	m_btntext[1] = (TextBMFont *)GameDataSet::getLayout(m_RootLayer, "BitmapLabel_friend");
	m_btntext[2] = (TextBMFont *)GameDataSet::getLayout(m_RootLayer, "BitmapLabel_tongzhi");

	m_bg[0] = GameDataSet::getLayout(m_RootLayer,"findbg");
	m_bg[1] = GameDataSet::getLayout(m_RootLayer, "friendbg");
	m_bg[2] = GameDataSet::getLayout(m_RootLayer, "tongzhibg");
	

	UserBase user = LoginInfo::getIns()->getMyUserBase();
	string uid = user.userid();
	GameDataSet::setTextBMFont(m_RootLayer, "BitmapLabel_id", uid);

	char buff[30];
	for (int i = 0; i < 2; i++){
		sprintf(buff,"ScrollView%d",i+1);
		m_ScrollView[i] = (ui::ScrollView *)GameDataSet::getButton(m_RootLayer, buff, selector, this);
		sprintf(buff, "sbg%d", i + 1);
		m_sbg[i] = GameDataSet::getLayout(m_RootLayer, buff);
	}
	for (int i = 0; i < 4; i++){
		sprintf(buff, "smallbg%d", i + 1);
		Layout *ly = GameDataSet::getLayout(m_RootLayer, buff);
		GameDataSet::getButton(ly, "btn", selector, this);

		ImageView *img = (ImageView *)GameDataSet::getLayout(ly, "icon");
		PhotoDown::getIns()->PushPhoto(this, user.userid(), img, user.picurl(), user.picid());
	}
	SelectItem(0);
	Layout *in = GameDataSet::getLayout(m_RootLayer,"in");
	m_input = LoginMainLayer::AddCursorTextField(in,20);
	m_input->setPlaceHolder(XXIconv::GBK2UTF("请输入对方id号").c_str());
	m_input->setFontColor(ccc3(0x38,0x4E,0x9C));
	m_input->setInputMode(ui::EditBox::InputMode::PHONE_NUMBER);
	HallInfo::getIns()->SendCFindFriend("",2);

	
    return true;
}

void FriendLayer::TouchEvent(CCObject *obj, TouchEventType type){
	Button *btn = (Button *)obj;
	string name = btn->getName();
	if (type == TOUCH_EVENT_ENDED){
		if (name.compare("close_btn") == 0){
			this->removeFromParentAndCleanup(true);
		}
		else if (name.compare("find") == 0){
			SelectItem(0);
		}
		else if (name.compare("friend") == 0){
			SelectItem(1);
		}
		else if (name.compare("tongzhi") == 0){
			SelectItem(2);
		}
		else if (name.compare("search") == 0){
			string id = m_input->getText();
			if (!id.empty()){
				string myuid = LoginInfo::getIns()->getUID();
				if (myuid.compare(id)==0){
					GameControl::getIns()->ShowTopTip(XXIconv::GBK2UTF("不能搜索自己的id"));
				}
				else{
					HallInfo::getIns()->SendCFindFriend(id, 1);
				}
			}
			else{
				GameControl::getIns()->ShowTopTip(XXIconv::GBK2UTF("您输入的id空"));
			}
		}
		else if (name.compare("huan") == 0){
			HallInfo::getIns()->SendCFindFriend("", 2);
		}
		else if (name.compare("btn")==0){
			string pname = btn->getParent()->getName();
			
			int index = 0;
			if (pname.compare("smallbg1") == 0){
				index = 0;
			}
			else if (pname.compare("smallbg2") == 0){
				index = 1;
			}
			else if (pname.compare("smallbg3") == 0){
				index = 2;
			}
			else if (pname.compare("smallbg4") == 0){
				index = 3;
			}
			SFindFriend fris = HallInfo::getIns()->getSFindFriend();
			int sz = fris.list_size();
			if (index < sz){
				Friend fri = fris.list(index);
				log("userid:%s", fri.info().userid().c_str());
				HallInfo::getIns()->SendCAddFriend(fri.info().userid());
			}
		}
	}
}


void FriendLayer::SelectItem(int index){
	for (int i = 0; i < 3; i++){
		m_bg[i]->setVisible(false);
		if (m_btns[i]){
			m_btns[i]->setBright(true);
		}
		if (m_btntext[i]){
			m_btntext[i]->setFntFile("fonts/xiaodan10-1.fnt");
		}
	}
	if (m_btns[index]){
		m_btns[index]->setBright(false);
	}
	if (m_btntext[index]){
		m_btntext[index]->setFntFile("fonts/xiaodan10.fnt");
	}
	m_bg[index]->setVisible(true);
	int count = 0;
	if (index>0&& m_sbg[index-1]){
		count=m_sbg[index-1]->getChildrenCount();
	}
	if (index==1&&count == 0){
		HallInfo::getIns()->SendCFriend();
	}
	else if (index == 2 && count == 0){
		HallInfo::getIns()->SendCAddFriendList();
	}
	else{
		ShowFriendEvent(index);
	}
	if (m_sbg[index - 1]){
		log("sbgname:%s",m_sbg[index-1]->getName().c_str());
	}
	//ShowFriendEvent(index);
}

void FriendLayer::ShowFriendEvent(int index){
	if (index > 0){
		ui::ScrollView *scroll = m_ScrollView[index-1];
		Layout *sbg = m_sbg[index-1];
		if (sbg->getChildrenCount() == 0){
			if (index == 1){
				SFriend sf = HallInfo::getIns()->getSFriend();
				int sz = sf.list_size();
				for (int i = 0; i < sz; i++){
					Friend hall=sf.list(i);
					FriendChatItemLayer *p = FriendChatItemLayer::create(hall);
					GameDataSet::PushScrollItem(sbg, 1, 0, p, i, scroll);
				}
				Layout *tip = GameDataSet::getLayout(m_RootLayer,"haoyoutip");
				if (sz == 0){
					tip->setVisible(true);
				}
				else{
					tip->setVisible(false);
				}
			}
			else{
				SAddFriendList sff = HallInfo::getIns()->getSAddFriendList();
				int sz = sff.list_size();
				for (int i = 0; i < sz; i++){
					FriendNotice hall=sff.list(i);
					FriendNoticeLayer *p = FriendNoticeLayer::create(hall);
					GameDataSet::PushScrollItem(sbg, 0, 0, p, i, scroll);
				}
				Layout *tip = GameDataSet::getLayout(m_RootLayer, "tongzhitip");
				if (sz == 0){
					tip->setVisible(true);
				}
				else{
					tip->setVisible(false);
				}
			}
		}
	}
	else{
		char buff[100];
		SFindFriend fris = HallInfo::getIns()->getSFindFriend();
		int sz = fris.list_size();
		for (int i = 0; i < 4;i++){
			sprintf(buff,"smallbg%d",i+1);
			Layout *ly = GameDataSet::getLayout(m_RootLayer,buff);
			if (i < sz){
				Friend fri=fris.list(i);
				UserBase user = fri.info();
				string name = user.username();
				bool online = fri.online();
				int act = fri.acttype();
				GameDataSet::setText(ly, "name", name);
				sprintf(buff,"friend/HY_LY%d.png",act);
				GameDataSet::setImageView(ly, "tt", buff, cocos2d::ui::Widget::TextureResType::PLIST);
				ly->setVisible(true);
			}
			else{
				ly->setVisible(false);
			}
		}
		Layout *tip = GameDataSet::getLayout(m_RootLayer, "findtip");
		if (sz == 0){
			tip->setVisible(true);
		}
		else{
			tip->setVisible(false);
		}
	}
}