#include "GameUI.h"
#include "GameControl.h"
#include "GameDataSet.h"
#include "ClientSocket.h"
#include "LoginScene.h"
#include "LoginInfo.h"
#include "MainScene.h"
#include "GameChatLayer.h"


GameUI::GameUI(){
	m_isopenmenu = false;
	GameControl::getIns()->setGameUI(this);
	Director::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(GameUI::update), this, 1.0, false);
}

GameUI::~GameUI(){
	Director::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(GameUI::update), this);
	RootRegister::getIns()->resetWidget(m_RootLayer);
	if (this == GameControl::getIns()->getGameUI()){
		GameControl::getIns()->setGameUI(NULL);

	}
}

bool GameUI::init()
{             
	if (!Layer::init())
    {
        return false;
    }
	
	m_RootLayer =RootRegister::getIns()->getWidget("gameui.json");
	this->addChild(m_RootLayer);

	SEL_TouchEvent selector = toucheventselector(GameUI::TouchEvent);
	m_menubtn=GameDataSet::getButton(m_RootLayer, "menubtn", selector, this);
	GameDataSet::getButton(m_RootLayer, "exit_btn", selector, this);
	GameDataSet::getButton(m_RootLayer, "task_btn", selector, this);
	GameDataSet::getButton(m_RootLayer, "chat_btn", selector, this);
	GameDataSet::getButton(m_RootLayer, "yuyin_btn", selector, this);
	GameDataSet::getButton(m_RootLayer, "set_btn", selector, this);
	GameDataSet::getButton(m_RootLayer, "help_btn", selector, this);
	m_menubg =(Layout *) GameDataSet::getButton(m_RootLayer, "menubg", selector, this);
	update(0);
    return true;
}

void GameUI::TouchEvent(CCObject *obj, TouchEventType type){
	Button *btn = (Button *)obj;
	string name = btn->getName();
	if (type == TOUCH_EVENT_ENDED){
		UserDefault *p = UserDefault::sharedUserDefault();
		if (name.compare("menubtn") == 0){
			m_isopenmenu ? closeMenu() : openMenu();
		}
		else if (name.compare("exit_btn") == 0){
			TipLayer *tip = GameControl::getIns()->getTipLayer();
			if (!tip){
				tip = TipLayer::create();
				this->addChild(tip);
				tip->setContent(XXIconv::GBK2UTF("是否退出游戏返回大厅?"));
			}
		}
		else if (name.compare("task_btn") == 0){
			TaskLayer *p = GameControl::getIns()->getTaskLayer();
			if (!p){
				p = TaskLayer::create();
				this->addChild(p);
			}
		}
		else if (name.compare("chat_btn") == 0){
			GameChatLayer *p = GameControl::getIns()->getGameChatLayer();
			if (!p){
				p = GameChatLayer::create();
				this->addChild(p);
			}
			else{
				p->openUI();
			}
		}
		else if (name.compare("yuyin_btn") == 0){

		}
		else if (name.compare("menubg") == 0){
			closeMenu();
		}
		else if (name.compare("set_btn") == 0){
			SetLayer *p = GameControl::getIns()->getSetLayer();
			if (!p){
				p = SetLayer::create();
				this->addChild(p);
			}
		}
		else if (name.compare("help_btn") == 0){
			HelpLayer *p = GameControl::getIns()->getHelpLayer();
			if (!p){
				p = HelpLayer::create();
				this->addChild(p);
			}
		}
		
	}
}

void GameUI::openMenu(){
	if (!m_isopenmenu){
		m_menubtn->setTouchEnabled(false);
		m_isopenmenu = true;
		Point pos = m_menubg->getPosition();
		Size sz = m_menubg->getSize();
		m_menubg->runAction(Sequence::create(MoveTo::create(0.2, ccp(1280 - sz.width, pos.y)), CCCallFunc::create(this, callfunc_selector(GameUI::menuCallBack)), NULL));
	}
}

void GameUI::closeMenu(){
	if (m_isopenmenu){
		m_menubtn->setTouchEnabled(false);
		m_isopenmenu = false;
		Point pos = m_menubg->getPosition();
		Size sz = m_menubg->getSize();
		m_menubg->runAction(Sequence::create(MoveTo::create(0.2, ccp(1280, pos.y)), CCCallFunc::create(this, callfunc_selector(GameUI::menuCallBack)), NULL));
	}
}

void GameUI::menuCallBack(){
	m_menubtn->setTouchEnabled(true);
}

void GameUI::update(float dt){
	string tt = GameDataSet::getLocalTime1();
	GameDataSet::setText(m_RootLayer, "localtime", tt);
}