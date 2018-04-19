#include "MJGameScene.h"
#include "GameControl.h"
#include "KeyBoard.h"

USING_NS_CC;

MJGameScene::MJGameScene(){
	m_pMJGameLayer = NULL;
	m_pGameUI = NULL;
	m_pGameHead = NULL;
	GameControl::getIns()->setMJGameScene(this);
}

MJGameScene::~MJGameScene(){
	if (this==GameControl::getIns()->getMJGameScene()){
		GameControl::getIns()->setMJGameScene(NULL);
	}
}

bool MJGameScene::init()
{
	if (!CCScene::init())
	{
		return false;
	}
	KeyBoard::getIns()->setKetPad(BACK_KEYTYPE, this);
	if (!m_pMJGameLayer){
		m_pMJGameLayer = MJGameLayer::create();
		this->addChild(m_pMJGameLayer);
	}

	if (!m_pGameHead){
		m_pGameHead = GameHead::create();
		this->addChild(m_pGameHead, 1);
	}

	if (!m_pGameUI){
		m_pGameUI = GameUI::create();
		this->addChild(m_pGameUI, 2);
	}

	

	return true;
}