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

TipLayer *TipLayer::create(TIP_ENUM_TYPE type){
	TipLayer *p = new TipLayer();
	if (p&&p->init(type)){
		p->autorelease();
	}
	else{
		CC_SAFE_DELETE(p);
	}
	return p;
}

bool TipLayer::init(TIP_ENUM_TYPE type)
{             
	if (!Layer::init())
    {
        return false;
    }
	m_type = type;
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
			string rid = RoomInfo::getIns()->getRoomData().roomid();
			MainScene *main = NULL;
			switch (m_type)
			{
			case TIP_TYPE_END:
				ClientSocket::getIns()->close();
				Director::sharedDirector()->end();
				break;
			case TIP_TYPE_BACK:
				main = MainScene::create();
				GameControl::getIns()->replaceScene(main);
				break;
			case TIP_TYPE_JIESAN:
				RoomInfo::getIns()->SendCDissolveRoom(rid);
				break;
			case TIP_TYPE_LEAVE:
				RoomInfo::getIns()->SendCLeave();
				break;
			default:
				break;
			}
			this->removeFromParentAndCleanup(true);
		}
	}
}

void TipLayer::setContent(string tip){
	GameDataSet::setText(m_RootLayer, "tip", tip);
}