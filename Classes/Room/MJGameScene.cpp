#include "MJGameScene.h"
#include "GameControl.h"
#include "KeyBoard.h"

USING_NS_CC;

MJGameScene::MJGameScene(){
	m_pMJGameLayer = NULL;
	m_pGameUI = NULL;
	m_pGameHead = NULL;

	memset(m_pMJChu,NULL,sizeof(MJHu *)*4);
	memset(m_pMJHu, NULL, sizeof(MJHand *)* 4);
	memset(m_pMJCPH, NULL, sizeof(MJCPH *)* 4);
	memset(m_pMJChu, NULL, sizeof(MJChu *)* 4);

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
		this->addChild(m_pGameHead, 4);
	}

	if (!m_pGameUI){
		m_pGameUI = GameUI::create();
		this->addChild(m_pGameUI, 5);
	}

	for (int i = 0; i < 4;i++){
		m_pMJWall[i]=MJWall::create(i + 1);
		this->addChild(m_pMJWall[i]);
		if (i == 2){
			m_pMJWall[i]->setZOrder(3);
		}
		m_pMJChu[i] = MJChu::create(i+1);
		this->addChild(m_pMJChu[i]);

		m_pMJHand[i] = MJHand::create(i + 1);
		this->addChild(m_pMJHand[i]);
		if (i == 2){
			m_pMJHand[i]->setZOrder(2);
		}

		m_pMJCPH[i] = MJCPH::create(i + 1);
		this->addChild(m_pMJCPH[i]);

		m_pMJHu[i] = MJHu::create(i + 1);
		this->addChild(m_pMJHu[i]);
	}

	return true;
}