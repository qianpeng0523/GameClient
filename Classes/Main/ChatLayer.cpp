#include "ChatLayer.h"
#include "GameControl.h"
#include "GameDataSet.h"
#include "ClientSocket.h"
#include "LoginScene.h"
#include "LoginInfo.h"
#include "PhotoDown.h"
#include "MainChatRecord.h"
#include "HallInfo.h"
#include "ExpressConfig.h"
#include "RoomInfo.h"

ChatItemLayer::ChatItemLayer(){
	
}

ChatItemLayer::~ChatItemLayer(){
	RootRegister::getIns()->resetWidget(m_RootLayer);
}

ChatItemLayer *ChatItemLayer::create(FriendChat *fc){
	ChatItemLayer *p = new ChatItemLayer();
	if (p&&p->init(fc)){
		p->autorelease();
	}
	else{
		CC_SAFE_DELETE(p);
	}
	return p;
}

bool ChatItemLayer::init(FriendChat *fc)
{
	if (!Layer::init())
	{
		return false;
	}
	m_fc = fc;
	UserBase user = LoginInfo::getIns()->getMyUserBase();
	int type = 0;
	m_json = "dchatitem1.json";
	if (fc->uname().compare(user.username()) == 0){
		m_json = "dchatitem2.json";
		type = 1;
	}
	m_RootLayer = RootRegister::getIns()->getWidget(m_json.c_str());
	this->addChild(m_RootLayer);

	this->setContentSize(m_RootLayer->getSize());

	ImageView *icon = (ImageView *)GameDataSet::getLayout(m_RootLayer, "icon");
	PhotoDown::getIns()->PushPhoto(this, fc->uid(), icon, "", 1);
	string time = fc->time();
	time = time.replace(10,1," ");
	Text *timet = GameDataSet::setText(m_RootLayer, "time", time);

	ImageView *img = (ImageView *)GameDataSet::getLayout(m_RootLayer,"conbg");
	Size bgsz = img->getSize();
	Text *tt =GameDataSet::setText(m_RootLayer, "content", fc->content());

	ImageView *expimg = (ImageView *)GameDataSet::getLayout(m_RootLayer,"exp");
	string tt1 = fc->content().substr(2, fc->content().length());
	ExpressItem *p = ExpressConfig::shareExpressConfig()->getExpressItemByName(tt1);
	if (p){
		tt->setVisible(false);
		expimg->setVisible(true);
		img->setVisible(false);
		expimg->loadTexture(p->file, Widget::TextureResType::PLIST);
	}
	else{
		tt->setVisible(true);
		expimg->setVisible(false);
		img->setVisible(true);
	}

	float w = tt->getSize().width;
	if (w + 30 > bgsz.width){
		img->setSize(Size(w+30,bgsz.height));
	}
	return true;
}

void ChatItemLayer::TouchEvent(CCObject *obj, TouchEventType type){
	Button *btn = (Button *)obj;
	string name = btn->getName();
	if (type == TOUCH_EVENT_ENDED){
		UserDefault *p = UserDefault::sharedUserDefault();
		if (name.compare("close_btn") == 0){
			this->removeFromParentAndCleanup(true);
		}
	}
}























ChatLayer::ChatLayer(){
	GameControl::getIns()->setChatLayer(this);
}

ChatLayer::~ChatLayer(){
	m_sbg->removeAllChildrenWithCleanup(true);
	m_input->removeAllChildrenWithCleanup(true);
	RootRegister::getIns()->resetWidget(m_RootLayer);
	if (this == GameControl::getIns()->getChatLayer()){
		GameControl::getIns()->setChatLayer(NULL);

	}
}

ChatLayer *ChatLayer::create(string uid, string uname){
	ChatLayer *p = new ChatLayer();
	if (p&&p->init(uid,uname)){
		p->autorelease();
	}
	else{
		CC_SAFE_DELETE(p);
	}
	return p;
}

bool ChatLayer::init(string uid, string uname)
{             
	if (!Layer::init())
    {
        return false;
    }
	m_uid = uid;
	m_uname = uname;
	m_RootLayer =RootRegister::getIns()->getWidget("dchat.json");
	this->addChild(m_RootLayer);

	SEL_TouchEvent selector = toucheventselector(ChatLayer::TouchEvent);
	
	GameDataSet::getButton(m_RootLayer, "close_btn", selector, this);
	GameDataSet::getButton(m_RootLayer, "send", selector, this);
	GameDataSet::getButton(m_RootLayer, "bqbtn", selector, this);
	m_ScrollView1=(ui::ScrollView *)GameDataSet::getButton(m_RootLayer, "ScrollView_2", selector, this);
	Button *bb= GameDataSet::getButton(m_RootLayer, "inbg", selector, this);
	bb->setTouchEnabled(false);
	Button *cdbtn= GameDataSet::getButton(m_RootLayer, "cdbtn", selector, this);
	cdbtn->setTag(0);
	GameDataSet::setImageView(m_RootLayer,"cdicon","voiceChat/voicebg0.png",Widget::TextureResType::PLIST);

	GameDataSet::setText(m_RootLayer, "name", uname);
	m_ScrollView = (ui::ScrollView *)GameDataSet::getButton(m_RootLayer, "ScrollView", selector, this);
	m_sbg = GameDataSet::getLayout(m_RootLayer, "sbg");

	UserBase user = LoginInfo::getIns()->getMyUserBase();
	string myuid = user.userid();

	Layout *in = GameDataSet::getLayout(m_RootLayer, "in");
	m_input = LoginMainLayer::AddCursorTextField(in, 20);
	m_input->setPlaceHolder(XXIconv::GBK2UTF("请输入聊天内容").c_str());
	m_input->setFontColor(ccc3(0x38, 0x4E, 0x9C));
	m_input->setMaxLength(20);

	Layout *expbg = (Layout *)GameDataSet::getButton(m_RootLayer, "bqbg", selector, this);
	expbg->setTag(0);
	expbg->setVisible(false);
	expbg->setScale(0.0);
	AddEmotion();
	AddAllChat();
	
    return true;
}

void ChatLayer::TouchEvent(CCObject *obj, TouchEventType type){
	Button *btn = (Button *)obj;
	string name = btn->getName();
	if (type == TOUCH_EVENT_BEGAN){
		if (name.compare("inbg") == 0){
			//开始录音
			log("begin voice");
		}
	}
	else if (type == TOUCH_EVENT_ENDED){
		UserDefault *p = UserDefault::sharedUserDefault();
		if (name.compare("close_btn") == 0){
			this->removeFromParentAndCleanup(true);
		}
		else if (name.compare("send") == 0){
			string content = m_input->getText();
			if (!content.empty()){
				HallInfo::getIns()->SendCFriendChat(m_uid, content);
			}
			else{
				log("%s",XXIconv::GBK2UTF("输入的聊天内容为空").c_str());
			}
		}
		else if (name.compare("bqbtn") == 0){
			Layout *expbg = GameDataSet::getLayout(m_RootLayer, "bqbg");
			int tag = expbg->getTag();
			if (tag == 1){
				closeExp();
			}
			else{
				openExp();
			}
		}
		else if (name.compare("cdbtn") == 0){
			int tag = btn->getTag();
			if (tag == 0){
				GameDataSet::setImageView(m_RootLayer, "cdicon", "speakFace/LT_TB_liaotian2.png", Widget::TextureResType::PLIST);
				btn->setTag(1);
				m_input->setTouchEnabled(false);
				m_input->setText(XXIconv::GBK2UTF("按住说话，松开手发送,滑出按住外取消").c_str());
				Layout *inputbg = GameDataSet::getLayout(m_RootLayer,"inbg");
				inputbg->setTouchEnabled(true);
			}
			else{
				GameDataSet::setImageView(m_RootLayer, "cdicon", "voiceChat/voicebg0.png", Widget::TextureResType::PLIST);
				btn->setTag(0);
				m_input->setTouchEnabled(true);
				m_input->setText("");
				Layout *inputbg = GameDataSet::getLayout(m_RootLayer, "inbg");
				inputbg->setTouchEnabled(false);
			}
		}
		else if (name.compare("inbg") == 0){
			//发送语音
			log("send voice");
		}
		else if (name.compare("ScrollView_2") == 0){
			//发送语音
			Layout *ly = (Layout *)GameDataSet::isTouchInChild(m_ScrollView1,10.0,NULL);
			if (ly){
				ExpressItem *p = (ExpressItem *)ly->getUserObject();
				if (p){
					HallInfo::getIns()->SendCFriendChat(m_uid,"//" + p->name);
					closeExp();
				}
			}
		}
	}
}

void ChatLayer::openExp(){
	Layout *expbg = GameDataSet::getLayout(m_RootLayer, "bqbg");
	expbg->runAction(Sequence::create(Show::create(),ScaleTo::create(0.01,1.0),NULL));
	expbg->setTag(1);
}

void ChatLayer::closeExp(){
	Layout *expbg = GameDataSet::getLayout(m_RootLayer, "bqbg");
	expbg->runAction(Sequence::create(ScaleTo::create(0.01, 0.0),Hide::create(), NULL));
	expbg->setTag(0);
}

void ChatLayer::AddEmotion(){
	Dictionary *dict = ExpressConfig::shareExpressConfig()->getDict();
	DictElement *elt;
	int index = 0;
	Layout *expbg = GameDataSet::getLayout(m_RootLayer, "bqsbg");
	CCDICT_FOREACH(dict, elt){
		ExpressItem *p = (ExpressItem *)elt->getObject();
		if (p->name.compare("vo") != 0){
			Layout *ly = Layout::create();
			ly->setSize(Size(83, 83));

			ImageView *img = ImageView::create(p->file, Widget::TextureResType::PLIST);
			ly->setUserObject(p);
			img->setPosition(ly->getSize() / 2.0);
			img->setName("123");
			img->setScale(0.6);

			ly->addChild(img);

			GameDataSet::PushScrollItem(expbg, 7, 0, ly, index,m_ScrollView1);
			index++;
		}
	}
	Layout *bg = GameDataSet::getLayout(m_RootLayer, "bqsbg");
	Size isz = m_ScrollView1->getInnerContainerSize();
	bg->setPositionY(isz.height - bg->getSize().height);
}

void ChatLayer::AddChatItem(FriendChat *fc){
	int count = m_sbg->getChildrenCount();
	ChatItemLayer *p = ChatItemLayer::create(fc);
	GameDataSet::PushScrollItem(m_sbg, 0, 0, p, count, m_ScrollView);
	m_ScrollView->scrollToBottom(0.01, false);
}

void ChatLayer::AddAllChat(){
	m_sbg->removeAllChildrenWithCleanup(true);
	MainChatRecord *pUserDefault = MainChatRecord::getIns();
	auto vec = pUserDefault->getChat(m_uid);
	for (int i = 0; i < vec.size(); i++){
		FriendChat *pp = vec.at(i);
		AddChatItem(pp);
	}
	auto vecs = HallInfo::getIns()->getFriendChat(m_uid);
	for (int i = 0; i < vecs.size();i++){
		FriendChat *fc = vecs.at(i);
		MainChatRecord::getIns()->PushChat(*fc);
		HallInfo::getIns()->SendCFriendChatRead(*fc);
		AddChatItem(fc);
	}
}