#include "CreateRoomLayer.h"
#include "GameControl.h"
#include "GameDataSet.h"
#include "ClientSocket.h"
#include "LogoScene.h"
#include "LoginInfo.h"
#include "WebViewCommom.h"





CreateRoomLayer::CreateRoomLayer(){
	GameControl::getIns()->setCreateRoomLayer(this);
}

CreateRoomLayer::~CreateRoomLayer(){
	RootRegister::getIns()->resetWidget(m_RootLayer);
	if (this == GameControl::getIns()->getCreateRoomLayer()){
		GameControl::getIns()->setCreateRoomLayer(NULL);

	}
}

bool CreateRoomLayer::init()
{             
	if (!Layer::init())
    {
        return false;
    }
	
	m_RootLayer =RootRegister::getIns()->getWidget("privatecreate.json");
	this->addChild(m_RootLayer);

	SEL_TouchEvent selector = toucheventselector(CreateRoomLayer::TouchEvent);
	
	GameDataSet::getButton(m_RootLayer, "close_btn", selector, this);
	char buff[30];
	for (int i = 0; i < 2;i++){
		sprintf(buff,"btn%d",i+1);
		m_btns[i]= GameDataSet::getButton(m_RootLayer, buff, selector, this);
		m_btns[i]->setTouchEnabled(true);
		sprintf(buff, "sbg%d", i + 1);
		m_bg[i] = GameDataSet::getLayout(m_RootLayer,buff);
		sprintf(buff, "BitmapLabel_%d", i + 1);
		m_btntext[i] = (TextBMFont *)GameDataSet::getLayout(m_RootLayer, buff);
	}

	SelectItem(0);
    return true;
}

void CreateRoomLayer::TouchEvent(CCObject *obj, TouchEventType type){
	Button *btn = (Button *)obj;
	string name = btn->getName();
	if (type == TOUCH_EVENT_ENDED){
		UserDefault *p = UserDefault::sharedUserDefault();
		if (name.compare("close_btn") == 0){
			this->removeFromParentAndCleanup(true);
		}
		else if (btn == m_btns[0]){
			SelectItem(0);
		}
		else if (btn == m_btns[1]){
			SelectItem(1);
		}
		
		
	}
}

void CreateRoomLayer::SelectItem(int index){
	for (int i = 0; i < 2; i++){
		m_bg[i]->setVisible(false);
		if (m_btns[i]){
			m_btns[i]->setBright(true);
		}
// 		if (m_btntext[i]){
// 			m_btntext[i]->setFntFile("fonts/xiaodan10-1.fnt");
// 		}
	}
	if (m_btns[index]){
		m_btns[index]->setBright(false);
	}
// 	if (m_btntext[index]){
// 		m_btntext[index]->setFntFile("fonts/xiaodan10.fnt");
// 	}
	m_bg[index]->setVisible(true);
}