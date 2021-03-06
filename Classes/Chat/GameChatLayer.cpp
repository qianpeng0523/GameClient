﻿#include "GameChatLayer.h"
#include "SimpleAudioEngine.h"
#include "AppMacros.h"
#include "Adaptation.h"
#include "GameDataSet.h"
#include "YuYinConfig.h"
#include "GameChatItemLayer.h"
#include "ExpressConfig.h"
#include "LoginMainLayer.h"
#include "GameControl.h"
#include "RootRegister.h"
#include "RoomInfo.h"
#include "GameChatRecordLayer.h"

USING_NS_CC;

string ff[3] = {"LT_TB_liaotian.png","LT_TB_biaoqing.png","LT_TB_history.png"};

GameChatLayer::GameChatLayer(){
	m_pCursorTextField = NULL;
	m_lock = false;
	GameControl::getIns()->setGameChatLayer(this);
}

GameChatLayer::~GameChatLayer(){
	m_sbg1->removeAllChildrenWithCleanup(true);
	m_sbg2->removeAllChildrenWithCleanup(true);
	m_sbg3->removeAllChildrenWithCleanup(true);
	m_pCursorTextField->removeFromParentAndCleanup(true);
	RootRegister::getIns()->resetWidget(m_RootLayer);
	if (this == GameControl::getIns()->getGameChatLayer()){
		GameControl::getIns()->setGameChatLayer(NULL);
	}
}

bool GameChatLayer::init()
{
	if (!Layer::init())
    {
        return false;
    }
	
	m_RootLayer = RootRegister::getIns()->getWidget("chat.json");
	this->addChild(m_RootLayer);

	Size sz = CCDirector::sharedDirector()->getWinSize();
	m_RootLayer->setPositionX(sz.width / 2.0 - m_RootLayer->getSize().width / 2.0);

	//Adaptation::shareAdaptation()->CocosStusioAdaption(m_RootLayer);
	
	SEL_TouchEvent selector = toucheventselector(GameChatLayer::TouchEvent);
	
 	GameDataSet::getButton(m_RootLayer, "chang_btn", selector, this);
	GameDataSet::getButton(m_RootLayer, "biaoqing_btn", selector, this);
	GameDataSet::getButton(m_RootLayer, "send_btn", selector, this);
	GameDataSet::getButton(m_RootLayer, "bg", selector, this);
	GameDataSet::getButton(m_RootLayer, "close_btn", selector, this);
	m_RootLayer->addTouchEventListener(this, selector);

	
	m_ScrollView1 = (ui::ScrollView *)GameDataSet::getButton(m_RootLayer, "ScrollView", selector, this);
	m_sbg1 =GameDataSet::getLayout(m_RootLayer,"s_bg");
	m_ScrollView2 = (ui::ScrollView *)GameDataSet::getButton(m_RootLayer, "ScrollView1", selector, this);
	m_sbg2 = GameDataSet::getLayout(m_RootLayer, "s_bg1");
	m_ScrollView3 = (ui::ScrollView *)GameDataSet::getButton(m_RootLayer, "ScrollView2", selector, this);
	m_sbg3 = GameDataSet::getLayout(m_RootLayer, "s_bg2");
	
	m_btn1 = GameDataSet::getButton(m_RootLayer,"chang_btn",selector,this);
	m_btn2 = GameDataSet::getButton(m_RootLayer, "biaoqing_btn", selector, this);
	m_btn3 = GameDataSet::getButton(m_RootLayer, "record_btn", selector, this);
	
	m_imgicon[0] =(ImageView *) GameDataSet::getLayout(m_RootLayer,"cicon");
	m_imgicon[1] = (ImageView *)GameDataSet::getLayout(m_RootLayer, "eicon");
	m_imgicon[2] = (ImageView *)GameDataSet::getLayout(m_RootLayer, "ricon");
	AddYuYin();
	AddEmotion();
	AddRecord();
	ShowRecord();
	ShowEmotion();
	
	Layout *chat_bg = GameDataSet::getLayout(m_RootLayer,"input_bg");
	m_pCursorTextField = LoginMainLayer::AddCursorTextField(chat_bg, 20);
	m_pCursorTextField->setPlaceHolder(XXIconv::GBK2UTF("请输入聊天内容").c_str());
	m_pCursorTextField->setFontColor(ccc3(120, 120, 120));
	m_pCursorTextField->setMaxLength(20);
	openUI();

	
	return true;
}

void GameChatLayer::openUI(){
	ImageView *img = (ImageView *)GameDataSet::getLayout(m_RootLayer,"bg");
	Size winsz = Director::sharedDirector()->getWinSize();
	Point pos = ccp(winsz.width- img->getSize().width / 2.0, img->getPositionY());
	img->runAction(CCSequence::create(CCMoveTo::create(0.1,pos),NULL));
	m_RootLayer->setTouchEnabled(true);
}

void GameChatLayer::closeUI(){
	ImageView *img = (ImageView *)GameDataSet::getLayout(m_RootLayer, "bg");
	Size winsz = Director::sharedDirector()->getWinSize();
	Point pos = ccp(winsz.width + img->getSize().width / 2.0, img->getPositionY());
	img->runAction(CCSequence::create(CCMoveTo::create(0.1, pos),
		//CCCallFunc::create(this, callfunc_selector(GameChatLayer::close)),
		NULL));
	m_RootLayer->setTouchEnabled(false);
}

GameChatLayer *GameChatLayer::open(){
	GameChatLayer *p = GameChatLayer::create();
	CCScene *scene = CCDirector::sharedDirector()->getRunningScene();
	if (scene){
		scene->addChild(p, 1000);
	}
	return p;
}

void GameChatLayer::TouchEvent(Object *obj, TouchEventType type){
	if (type == TOUCH_EVENT_ENDED){
		Button *btn = (Button *)obj;
		string name = btn->getName();
		
		if (name.compare("chang_btn") == 0){
			ShowYuYin();
		}
		else if (name.compare("biaoqing_btn") == 0){
			ShowEmotion();
		}
		else if (name.compare("record_btn") == 0){
			ShowRecord();
		}
		else if (name.compare("send_btn") == 0){
			if (!m_lock){
				string content = m_pCursorTextField->getText();
				if (content.empty()){
					GameControl::getIns()->ShowTopTip(XXIconv::GBK2UTF("发送的内容不能为空"));
				}
				else{
					m_lock = true;
					RoomInfo::getIns()->SendCRChat(content);
					this->runAction(Sequence::create(DelayTime::create(2.0), CCCallFunc::create(this, callfunc_selector(GameChatLayer::ChatCall)),NULL));
				}
			}
			else{
				GameControl::getIns()->ShowTopTip(XXIconv::GBK2UTF("您发送的信息太频繁"));
			}
		}
		else if (name.compare("Panel_22") == 0){
			Layout *bg = GameDataSet::getLayout(m_RootLayer,"bg");
			Point pos = btn->getTouchEndPos();
			bool ist= GameDataSet::isPosInNode(bg,pos);
			if (!ist){
				closeUI();
			}
		}
		else if(name.compare("ScrollView1")==0){
			Layout *ly = (Layout *)GameDataSet::isTouchInChild(m_ScrollView2,10.0,NULL);
			if (ly){
				if (!m_lock){
					m_lock = true;
					ExpressItem *p = (ExpressItem *)ly->getUserObject();
					RoomInfo::getIns()->SendCRChat("//" + p->name);
					this->runAction(Sequence::create(DelayTime::create(2.0), CCCallFunc::create(this, callfunc_selector(GameChatLayer::ChatCall)), NULL));
				}
				else{
					GameControl::getIns()->ShowTopTip(XXIconv::GBK2UTF("您发送的信息太频繁"));
				}
			}
		}
		else if (name.compare("ScrollView") == 0){
			GameChatItemLayer *ly = (GameChatItemLayer *)GameDataSet::isTouchInChild(m_ScrollView1, 10.0, NULL);
			if (ly){
				if (!m_lock){
					m_lock = true;
					YuYinItem *p = ly->getYuYinItem();
					RoomInfo::getIns()->SendCRChat(p->content);
					this->runAction(Sequence::create(DelayTime::create(2.0), CCCallFunc::create(this, callfunc_selector(GameChatLayer::ChatCall)), NULL));
				}
				else{
					GameControl::getIns()->ShowTopTip(XXIconv::GBK2UTF("您发送的信息太频繁"));
				}
			}
		}
		else if (name.compare("ScrollView2") == 0){
			ChatItemLayer *ly = (ChatItemLayer *)GameDataSet::isTouchInChild(m_ScrollView3, 10.0, NULL);
			if (ly){
				
			}
		}
		
	}
}

void GameChatLayer::ChatCall(){
	m_lock = false;
}

void GameChatLayer::CallBack(CCNode *node){
	
}

bool GameChatLayer::isYuYin(){
	return m_ScrollView1->getScale() == 1.0;
}

void GameChatLayer::AddYuYin(){
	Dictionary *dict = YuYinConfig::shareYuYinConfig()->getDict();
	DictElement *elt;
	int index = 0;
	CCDICT_FOREACH(dict,elt){
		YuYinItem *p = (YuYinItem *)elt->getObject();

		GameChatItemLayer *pp = GameChatItemLayer::create(p);
		
		GameDataSet::PushScrollItem(m_sbg1, 0, 0, pp, index, m_ScrollView1);
		index++;
	}
}

void GameChatLayer::AddEmotion(){
	Dictionary *dict = ExpressConfig::shareExpressConfig()->getDict();
	DictElement *elt;
	int index = 0;
	CCDICT_FOREACH(dict, elt){
		ExpressItem *p = (ExpressItem *)elt->getObject();
		if (p->name.compare("vo") != 0){
			Layout *ly = Layout::create();
			ly->setSize(Size(104,107));

			ImageView *img = ImageView::create(p->file,Widget::TextureResType::PLIST);
			ly->setUserObject(p);
			img->setPosition(ly->getSize()/2.0);
			img->setName("123");

			ly->addChild(img);
			
			GameDataSet::PushScrollItem(m_sbg2, 4, 0, ly, index, m_ScrollView2);
			index++;
		}
	}
	Layout *bg = GameDataSet::getLayout(m_RootLayer,"Panel_18");
	Size isz = m_ScrollView2->getInnerContainerSize();
	bg->setPositionY(isz.height - bg->getSize().height);

}

void GameChatLayer::AddRecord(){
	ChatRecord *pChatRecord = ChatRecord::getIns();
	int count = 0;
	for (int i = 0;i<7; i++){
		auto vec = pChatRecord->getChat(i);
		for (int j = 0; j < vec.size(); j++){
			ChatRD *p = vec.at(j);
			PushRecord(p);
			count++;
			if (count>MAXCHATCOUNT){
				m_ScrollView3->scrollToBottom(0.01, false);
				return;
			}
		}
	}
	m_ScrollView3->scrollToBottom(0.01, false);
}

void GameChatLayer::PushRecord(ChatRD *p){
	int count = m_sbg3->getChildrenCount();
	GameChatRecordLayer *pc = GameChatRecordLayer::create(p->_uid, "", p->_content, p->_time);
	GameDataSet::PushScrollItem(m_sbg3, 1, 0, pc, count, m_ScrollView3);
	m_ScrollView3->scrollToBottom(0.01, false);
}

void GameChatLayer::ShowYuYin(){
	m_ScrollView1->setScale(1.0);
	m_ScrollView2->setScale(0.0);
	m_ScrollView3->setScale(0.0);

	m_btn2->setBright(false);
	m_btn1->setBright(true);
	m_btn3->setBright(false);

	for (int i = 0; i < 3; i++){
		ImageView *img = m_imgicon[i];
		if (i == 0){
			img->loadTexture("speakFace/LT_TB_liaotian2.png", Widget::TextureResType::PLIST);
		}
		else{
			img->loadTexture("speakFace/"+ff[i], Widget::TextureResType::PLIST);
		}
	}
}

void GameChatLayer::ShowEmotion(){
	m_ScrollView1->setScale(0.0);
	m_ScrollView2->setScale(1.0);
	m_ScrollView3->setScale(0.0);

	m_btn1->setBright(false);
	m_btn2->setBright(true);
	m_btn3->setBright(false);

	for (int i = 0; i < 3; i++){
		ImageView *img = m_imgicon[i];
		if (i == 1){
			img->loadTexture("speakFace/LT_TB_biaoqing2.png", Widget::TextureResType::PLIST);
		}
		else{
			img->loadTexture("speakFace/" + ff[i], Widget::TextureResType::PLIST);
		}
	}
}

void GameChatLayer::ShowRecord(){
	m_ScrollView1->setScale(0.0);
	m_ScrollView2->setScale(0.0);
	m_ScrollView3->setScale(1.0);

	m_btn1->setBright(false);
	m_btn2->setBright(false);
	m_btn3->setBright(true);

	for (int i = 0; i < 3; i++){
		ImageView *img = m_imgicon[i];
		if (i == 2){
			img->loadTexture("speakFace/LT_TB_history2.png", Widget::TextureResType::PLIST);
			img->setFlippedY(true);
		}
		else{
			img->loadTexture("speakFace/" + ff[i], Widget::TextureResType::PLIST);
		}
		
	}
}

void GameChatLayer::close(){
	this->removeFromParentAndCleanup(true);
}
