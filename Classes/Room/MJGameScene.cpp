#include "MJGameScene.h"
#include "GameControl.h"
#include "KeyBoard.h"
#include "RoomControl.h"
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

	if (!m_pGameHead){
		m_pGameHead = GameHead::create();
		this->addChild(m_pGameHead, 4);
	}
	//test
	RoomControl::shareRoomControl()->setMyPosition(1);
	if (!m_pMJGameLayer){
		m_pMJGameLayer = MJGameLayer::create();
		this->addChild(m_pMJGameLayer);
	}

	if (!m_pGameUI){
		m_pGameUI = GameUI::create();
		this->addChild(m_pGameUI, 5);
	}

	for (int i = 0; i < 4;i++){
		int pos =i+1 ;
		int index = GameHead::changePos(pos);

		m_pMJWall[index] = MJWall::create(pos);
		this->addChild(m_pMJWall[index]);
		if (index == 2){
			m_pMJWall[index]->setZOrder(3);
		}
		m_pMJChu[index] = MJChu::create(pos);
		this->addChild(m_pMJChu[index]);

		m_pMJHand[index] = MJHand::create(pos);
		this->addChild(m_pMJHand[index]);
		if (index == 2){
			m_pMJHand[index]->setZOrder(2);
		}

		m_pMJCPH[index] = MJCPH::create(pos);
		this->addChild(m_pMJCPH[index]);

		m_pMJHu[index] = MJHu::create(pos);
		this->addChild(m_pMJHu[index]);
	}

	m_index = 0;
	RoomControl *pRoomControl = RoomControl::shareRoomControl();
	pRoomControl->setZhuang(1);
	pRoomControl->cutCard(3, 4);
	this->runAction(Sequence::create(DelayTime::create(0.5),
		CCCallFunc::create(this, callfunc_selector(MJGameScene::testCallBack))
		,NULL));
	return true;
}

void MJGameScene::setMJWall(int dir, int index){
	m_pMJWall[dir]->PopCard(index - 1);
}

void MJGameScene::testCallBack(){
	RoomControl *pRoomControl = RoomControl::shareRoomControl();
	if (m_index > 128){

	}
	else{
		pRoomControl->getWallData((m_index++)%5!=4);
		this->runAction(Sequence::create(DelayTime::create(0.5),
			CCCallFunc::create(this, callfunc_selector(MJGameScene::testCallBack))
			, NULL));
	}
}

void MJGameScene::setMyPosition(int pos){
	if (m_pGameHead){
		m_pGameHead->setMyPosition(pos);
	}
}