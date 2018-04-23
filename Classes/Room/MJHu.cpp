#include "MJHu.h"
#include "GameControl.h"
#include "GameDataSet.h"
#include "ClientSocket.h"
#include "LoginScene.h"
#include "LoginInfo.h"
#include "CardsStr.h"

MJHu::MJHu(){
	
}

MJHu::~MJHu(){
	RootRegister::getIns()->resetWidget(m_RootLayer);
	
}

bool MJHu::init(int pos)
{             
	if (!Layer::init())
    {
        return false;
    }
	m_position = pos;
	m_index = GameHead::changePos(pos);
	char buff[50];
	sprintf(buff, "mjhu%d.json", m_index + 1);
	m_RootLayer =RootRegister::getIns()->getWidget(buff);
	this->addChild(m_RootLayer);
	for (int i = 0; i < 14;i++){
		sprintf(buff,"c%d",i+1);
		m_cardbgs[i] = (ImageView *)GameDataSet::getLayout(m_RootLayer, buff);
		m_cardimgs[i] = (ImageView *)m_cardbgs[i]->getChildren().at(0);
	}
	resetCard();
// 	int sz = rand()%7+7;
// 	char a[14] = { 0 };
// 	for (int i = 0; i < sz; i++){
// 		int va = CardStr::g_cards[rand()%34];
// 		a[i] = va;
// 	}
// 	setCards(a);
    return true;
}

MJHu* MJHu::create(int pos){
	MJHu *p = new MJHu();
	if (p&&p->init(pos)){
		p->autorelease();
	}
	else{
		CC_SAFE_DELETE(p);
	}
	return p;
}

void MJHu::TouchEvent(CCObject *obj, TouchEventType type){
	Button *btn = (Button *)obj;
	string name = btn->getName();
	if (type == TOUCH_EVENT_ENDED){
		
	}
}

void MJHu::resetCard(){
	for (int i = 0; i < 14; i++){
		m_cardbgs[i]->setVisible(false);
	}
}

void MJHu::setCard(int index, int card){
	if (card>0){
		m_cardbgs[index]->setVisible(true);
		m_cardimgs[index]->loadTexture(CardStr::getCardStr(card),Widget::TextureResType::PLIST);
	}
	else{
		m_cardbgs[index]->setVisible(false);
	}
}

void MJHu::setCards(string cards){
	int len = cards.length();
	for (int i = 0; i < len;i++){
		int va = cards[i];
		setCard(i, va);
	}
}