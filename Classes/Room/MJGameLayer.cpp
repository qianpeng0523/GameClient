#include "MJGameLayer.h"
#include "GameControl.h"
#include "GameDataSet.h"
#include "ClientSocket.h"
#include "LoginScene.h"
#include "LoginInfo.h"





MJGameLayer::MJGameLayer(){
	for (int i = 0; i < 4;i++){
		for (int j = 0; j < 4; j++){
			m_facards[i][j] = 0;
		}
	}
	GameControl::getIns()->setMJGameLayer(this);
}

MJGameLayer::~MJGameLayer(){
	RootRegister::getIns()->resetWidget(m_RootLayer);
	if (this == GameControl::getIns()->getMJGameLayer()){
		GameControl::getIns()->setMJGameLayer(NULL);

	}
}

bool MJGameLayer::init()
{             
	if (!Layer::init())
    {
        return false;
    }
	
	m_RootLayer =RootRegister::getIns()->getWidget("mjgamescene.json");
	this->addChild(m_RootLayer);

	SEL_TouchEvent selector = toucheventselector(MJGameLayer::TouchEvent);
	GameDataSet::getButton(m_RootLayer, "btn", selector, this);
	
	char buff[50];
	for (int i = 0; i < 4; i++){
		sprintf(buff,"fa%d",i+1);
		m_faimgs[i] = (ImageView *)GameDataSet::getLayout(m_RootLayer, buff);
		m_facounts[i] = (TextBMFont *)GameDataSet::getLayout((Layout *)m_faimgs[i], "BitmapLabel_num");
	}
	resetFa();
// 	setFa(1, 1);
// 	setFa(2, 2);
// 	setFa(3, 3);
// 	setFa(4, 0);
    return true;
}

void MJGameLayer::TouchEvent(CCObject *obj, TouchEventType type){
	Button *btn = (Button *)obj;
	string name = btn->getName();
	if (type == TOUCH_EVENT_ENDED){
		
	}
}

void MJGameLayer::resetFa(){
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			m_facards[i][j] = 0;
		}
		m_faimgs[i]->setVisible(false);
	}

}

void MJGameLayer::setFa(int pos, int count){
	int index = GameHead::changePos(pos);
	if (count>0){
		m_faimgs[index]->setVisible(true);
		char buff[30];
		sprintf(buff,"x%d",count);
		m_facounts[index]->setText(buff);
	}
	else{
		m_faimgs[index]->setVisible(false);
	}
}