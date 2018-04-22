#include "MJChu.h"
#include "GameControl.h"
#include "GameDataSet.h"
#include "ClientSocket.h"
#include "LoginScene.h"
#include "LoginInfo.h"
#include "GameHead.h"
#include "CardsStr.h"

MJChu::MJChu(){
	
}

MJChu::~MJChu(){
	RootRegister::getIns()->resetWidget(m_RootLayer);
	
}

bool MJChu::init(int pos)
{             
	if (!Layer::init())
    {
        return false;
    }
	m_position = pos;
	m_index = GameHead::changePos(pos);
	char buff[50];
	sprintf(buff, "mjchu%d.json", pos);
	m_RootLayer =RootRegister::getIns()->getWidget(buff);
	this->addChild(m_RootLayer);
	for (int i = 0; i < MAX_COUNT; i++){
		sprintf(buff, "c%d", i+1);
		m_cardbgs[i] = (ImageView *)GameDataSet::getLayout(m_RootLayer,buff);
		m_cardimgs[i] = (ImageView *)m_cardbgs[i]->getChildren().at(0);
		float sx = m_cardimgs[i]->getScaleX();
		float sy = m_cardimgs[i]->getScaleY();
		m_cardimgs[i]->setScaleX(sx*0.85);
		m_cardimgs[i]->setScaleY(sy*0.85);
	}
	resetCard();
// 	char a[MAX_COUNT] = { 0 };
// 	int sz = rand()%9+13;
// 	for (int i = 0; i < sz;i++){
// 		int va = CardStr::g_cards[rand() % 34];
// 		a[i] = va;
// 	}
// 	PushCard(a);
    return true;
}

MJChu* MJChu::create(int pos){
	MJChu *p = new MJChu();
	if (p&&p->init(pos)){
		p->autorelease();
	}
	else{
		CC_SAFE_DELETE(p);
	}
	return p;
}

void MJChu::TouchEvent(CCObject *obj, TouchEventType type){
	Button *btn = (Button *)obj;
	string name = btn->getName();
	if (type == TOUCH_EVENT_ENDED){
		
	}
}

void MJChu::resetCard(){
	for (int i = 0; i < MAX_COUNT; i++){
		m_cardbgs[i]->setVisible(false);
	}
}

void MJChu::PushCard(int index, int card){
	if (card>0){
		m_cardbgs[index]->setVisible(true);
		m_cardimgs[index]->loadTexture(CardStr::getCardStr(card), Widget::TextureResType::PLIST);
	}
	else{
		m_cardbgs[index]->setVisible(false);
	}
}

void MJChu::PushCard(string cards){
	int len = cards.length();
	for (int i = 0; i < len; i++){
		int va = cards[i];
		PushCard(i, va);
	}
}
