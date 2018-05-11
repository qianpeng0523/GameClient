#include "GameHelpLayer.h"
#include "GameControl.h"
#include "GameDataSet.h"
#include "ClientSocket.h"
#include "LoginScene.h"
#include "LoginInfo.h"
#include "RoomInfo.h"





GameHelpLayer::GameHelpLayer(){
	GameControl::getIns()->setGameHelpLayer(this);
}

GameHelpLayer::~GameHelpLayer(){
	RootRegister::getIns()->resetWidget(m_RootLayer);
	if (this == GameControl::getIns()->getGameHelpLayer()){
		GameControl::getIns()->setGameHelpLayer(NULL);

	}
}

bool GameHelpLayer::init()
{             
	if (!Layer::init())
    {
        return false;
    }
	
	m_RootLayer =RootRegister::getIns()->getWidget("gamehelp.json");
	this->addChild(m_RootLayer);

	SEL_TouchEvent selector = toucheventselector(GameHelpLayer::TouchEvent);
	
	GameDataSet::getButton(m_RootLayer, "close_btn", selector, this);
	
	RoomData rd = RoomInfo::getIns()->getRoomData();
	char buff[200];
	
	GameDataSet::setText(m_RootLayer, "rid", XXIconv::GBK2UTF("房间号:")+rd.roomid());
	string type = rd.type() == 1 ? XXIconv::GBK2UTF("积分") : XXIconv::GBK2UTF("金币");
	GameDataSet::setText(m_RootLayer, "type", XXIconv::GBK2UTF("结算方式:")+type);
	sprintf(buff, "%d",rd.ante());
	GameDataSet::setText(m_RootLayer, "ante", XXIconv::GBK2UTF("底分:")+buff);
	sprintf(buff, "%d", rd.round());
	GameDataSet::setText(m_RootLayer, "round", XXIconv::GBK2UTF("时长:") + buff);
	GameDataSet::setText(m_RootLayer, "uid", XXIconv::GBK2UTF("房主:") + rd.uid());
	string content;
	int bao = rd.bao();
	if (bao == 0){
		content += XXIconv::GBK2UTF("无宝");
	}
	else if (bao == 1){
		content += XXIconv::GBK2UTF("有宝不可打");
	}
	else if (bao == 2){
		content += XXIconv::GBK2UTF("有宝可打");
	}

	sprintf(buff, "%d%s%d%s%d", rd.ante(), XXIconv::GBK2UTF("漂").c_str(), 0, XXIconv::GBK2UTF("绑").c_str(),rd.bang());

	GameDataSet::setText(m_RootLayer, "wanfa", XXIconv::GBK2UTF("玩法:黄梅麻将，") + type + XXIconv::GBK2UTF("场，")+buff);
    return true;
}

void GameHelpLayer::TouchEvent(CCObject *obj, TouchEventType type){
	Button *btn = (Button *)obj;
	string name = btn->getName();
	if (type == TOUCH_EVENT_ENDED){
		UserDefault *p = UserDefault::sharedUserDefault();
		if (name.compare("close_btn") == 0){
			this->removeFromParentAndCleanup(true);
		}
	}
}