#include "MJDice.h"
#include "GameControl.h"
#include "GameDataSet.h"
#include "ClientSocket.h"
#include "LoginScene.h"
#include "LoginInfo.h"
#include "CardsStr.h"
#include "MayaAction.h"

MJDice::MJDice(){
	
}

MJDice::~MJDice(){
	RootRegister::getIns()->resetWidget(m_RootLayer);
	
}

bool MJDice::init()
{             
	if (!Layer::init())
    {
        return false;
    }
	
	m_RootLayer =RootRegister::getIns()->getWidget("mjdice.json");
	this->addChild(m_RootLayer);
	
	m_diceimg = (ImageView *)GameDataSet::getLayout(m_RootLayer,"touzi");
	char buff[30];
	for (int i = 0; i < 2;i++){
		sprintf(buff,"t%d",i+1);
		m_dices[i] = (ImageView *)GameDataSet::getLayout(m_RootLayer,buff);
	}
	resetCard();
	
    return true;
}

MJDice* MJDice::create(){
	MJDice *p = new MJDice();
	if (p&&p->init()){
		p->autorelease();
	}
	else{
		CC_SAFE_DELETE(p);
	}
	return p;
}

void MJDice::TouchEvent(CCObject *obj, TouchEventType type){
	Button *btn = (Button *)obj;
	string name = btn->getName();
	if (type == TOUCH_EVENT_ENDED){
		
	}
}

void MJDice::test(){
	int a[2] = { 3, 1 };
	startDice(a);
}

void MJDice::resetCard(){
	m_diceimg->setVisible(false);
	m_diceimg->loadTexture("tx_youxi_shaizi_xuanzhuang_00.png",Widget::TextureResType::PLIST);
	for (int i = 0; i < 2; i++){
		m_dices[i]->setVisible(false);
	}
}

void MJDice::startDice(int *dice){
	memcpy(m_dice,dice,sizeof(int)*2);
	MayaAction::getIns()->Play(m_diceimg, "touzi", CCCallFuncND::create(this, callfuncND_selector(MJDice::ShowResult),NULL));
}

void MJDice::ShowResult(Node *node,void *data){
	char buff[30];
	for (int i = 0; i < 2; i++){
		sprintf(buff,"tx_youxi_shaizi_%02d.png",m_dice[i]);
		m_dices[i]->loadTexture(buff, Widget::TextureResType::PLIST);
		m_dices[i]->setVisible(true);
		m_dices[i]->runAction(Sequence::create(DelayTime::create(0.5),Hide::create(),NULL));
	}
}