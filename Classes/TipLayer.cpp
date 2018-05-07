#include "TipLayer.h"
#include "GameControl.h"
#include "GameDataSet.h"
#include "ClientSocket.h"
#include "LoginScene.h"
#include "LoginInfo.h"
#include "MainScene.h"
#include "RoomInfo.h"




TipLayer::TipLayer(){
	GameControl::getIns()->setTipLayer(this);
}

TipLayer::~TipLayer(){
	RootRegister::getIns()->resetWidget(m_RootLayer);
	if (this == GameControl::getIns()->getTipLayer()){
		GameControl::getIns()->setTipLayer(NULL);

	}
}

bool TipLayer::init()
{             
	if (!Layer::init())
    {
        return false;
    }
	
	m_RootLayer =RootRegister::getIns()->getWidget("tiplayer.json");
	this->addChild(m_RootLayer);

	SEL_TouchEvent selector = toucheventselector(TipLayer::TouchEvent);
	
	GameDataSet::getButton(m_RootLayer, "close_btn", selector, this);
	GameDataSet::getButton(m_RootLayer, "ok_btn", selector, this);
	GameDataSet::getButton(m_RootLayer, "cancle_btn", selector, this);
	
    return true;
}

void TipLayer::TouchEvent(CCObject *obj, TouchEventType type){
	Button *btn = (Button *)obj;
	string name = btn->getName();
	if (type == TOUCH_EVENT_ENDED){
		UserDefault *p = UserDefault::sharedUserDefault();
		if (name.compare("close_btn") == 0){
			this->removeFromParentAndCleanup(true);
		}
		else if (name.compare("cancle_btn") == 0){
			this->removeFromParentAndCleanup(true);
		}
		else if (name.compare("ok_btn") == 0){
			this->removeFromParentAndCleanup(true);
			MJGameScene *p = GameControl::getIns()->getMJGameScene();
			MainLayer *mainlayer = GameControl::getIns()->getMainLayer();
			LoginMainLayer *loginscene = GameControl::getIns()->getLoginMainLayer();
			if (p){
				RoomInfo::getIns()->SendCLeave();
			}
			else if (mainlayer){
				ClientSocket::getIns()->close();
				Director::sharedDirector()->end();
			}
			else if (loginscene){
				ClientSocket::getIns()->close();
				Director::sharedDirector()->end();
			}
		}
	}
}

void TipLayer::setContent(string tip){
	GameDataSet::setText(m_RootLayer, "tip", tip);
}