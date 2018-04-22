#include "MJHand.h"
#include "GameControl.h"
#include "GameDataSet.h"
#include "ClientSocket.h"
#include "LoginScene.h"
#include "LoginInfo.h"
#include "CardsStr.h"

MJHand::MJHand(){
	memset(m_cardbgs, NULL, sizeof(ImageView *)* 14);
	memset(m_cards, NULL, sizeof(ImageView *)* 14);
}

MJHand::~MJHand(){
	RootRegister::getIns()->resetWidget(m_RootLayer);
	
}

bool MJHand::init(int pos)
{             
	if (!Layer::init())
    {
        return false;
    }
	m_position = pos;
	
	char buff[50];
	sprintf(buff,"mjhand%d.json",pos);
	m_RootLayer =RootRegister::getIns()->getWidget(buff);
	this->addChild(m_RootLayer);

	SEL_TouchEvent selector = toucheventselector(MJHand::TouchEvent);
	
	for (int i = 0; i < 14;i++){
		sprintf(buff,"s%d",i+1);
		m_cardbgs[i] = (ImageView *)GameDataSet::getLayout(m_RootLayer,buff);
		if (m_cardbgs[i]->getChildrenCount()>0){
			m_cards[i] = (ImageView *)m_cardbgs[i]->getChildren().at(0);
		}
	}
	resetCards();

    return true;
}

MJHand* MJHand::create(int pos){
	MJHand *p = new MJHand();
	if (p&&p->init(pos)){
		p->autorelease();
	}
	else{
		CC_SAFE_DELETE(p);
	}
	return p;
}

void MJHand::TouchEvent(CCObject *obj, TouchEventType type){
	Button *btn = (Button *)obj;
	string name = btn->getName();
	if (type == TOUCH_EVENT_ENDED){
		if (name.compare("close_btn") == 0){
			
		}
	}
}

void MJHand::resetCards(){
	for (int i = 0; i < 14; i++){
		m_cardbgs[i]->setVisible(false);
	}
}

void MJHand::setValue(int index, int card){
	if (card <= 0){
		m_cardbgs[index]->setVisible(false);
	}
	else{
		m_cardbgs[index]->setVisible(true);
	}
	if (m_cards[index]){
		m_cards[index]->loadTexture(CardStr::getCardStr(card), Widget::TextureResType::PLIST);
	}
}

void MJHand::setValue(int index, bool isvisible){
	m_cardbgs[index]->setVisible(isvisible);
}