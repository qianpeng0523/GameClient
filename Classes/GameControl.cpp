#include "GameControl.h"



GameControl *GameControl::m_ins=NULL;

GameControl::GameControl(){
	m_pLoginLayer = NULL;
	m_pMainLayer = NULL;
	m_pUserInfoLayer = NULL;
	m_pSetLayer = NULL;
	m_pShopLayer = NULL;
	m_pSignLayer = NULL;
	m_pFriendLayer = NULL;
	m_pFankuiLayer = NULL;
	m_pFreeLayer = NULL;
	m_pExchangeLayer = NULL;
	m_pTaskLayer = NULL;
	m_pMailLayer = NULL;
	m_pActiveLayer = NULL;
}

GameControl::~GameControl(){
	
}

bool GameControl::init()
{
	
    return true;
}

GameControl* GameControl::getIns(){
	if (!m_ins){
		m_ins = new GameControl();
		m_ins->init();
	}
	return m_ins;
}

void GameControl::replaceScene(Scene *scene){
	Director *p = Director::sharedDirector();
	CCTransitionFade *reScene = CCTransitionFade::create(0.3, scene);
	p->replaceScene(reScene);
}