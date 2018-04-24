#include "MJGameLayer.h"
#include "GameControl.h"
#include "GameDataSet.h"
#include "ClientSocket.h"
#include "LoginScene.h"
#include "LoginInfo.h"





MJGameLayer::MJGameLayer(){
	m_downtime = -1;
	for (int i = 0; i < 4;i++){
		for (int j = 0; j < 4; j++){
			m_facards[i][j] = 0;
		}
	}
	GameControl::getIns()->setMJGameLayer(this);
	Director::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(MJGameLayer::update), this, 1.0, false);
}

MJGameLayer::~MJGameLayer(){
	Director::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(MJGameLayer::update), this);
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
	setTimeVisible(false);
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

void MJGameLayer::update(float dt){
	if (m_downtime > 0){
		setTime(m_downtime--);
	}
}

void MJGameLayer::setTime(int time){
	GameDataSet::setTextBMFont(m_RootLayer, "time", time);
	setTimeVisible(true);
}

void MJGameLayer::setTimeVisible(bool isv){
	Text *tt = (Text *)GameDataSet::getLayout(m_RootLayer, "time");
	tt->setVisible(isv);
}