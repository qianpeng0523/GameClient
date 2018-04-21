#include "GameChatItemLayer.h"
#include "SimpleAudioEngine.h"
#include "AppMacros.h"
#include "Adaptation.h"
#include "GameControl.h"
#include "GameDataSet.h"
#include "LoginScene.h"
#include "YuYinConfig.h"
#include "RootRegister.h"

USING_NS_CC;

GameChatItemLayer::GameChatItemLayer(){
	
}

GameChatItemLayer::~GameChatItemLayer(){
	RootRegister::getIns()->resetWidget(m_RootLayer);
}

GameChatItemLayer *GameChatItemLayer::create(YuYinItem *p){
	GameChatItemLayer *pRet = new GameChatItemLayer();
	if (pRet&&pRet->init(p)){
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
	}
	return pRet;
}

bool GameChatItemLayer::init(YuYinItem *p)
{
	if (!Layer::init())
    {
        return false;
    }
	m_pYuYinItem = p;

	m_RootLayer = RootRegister::getIns()->getWidget("chatitem.json");
	this->addChild(m_RootLayer);

	this->setContentSize(m_RootLayer->getSize());
	GameDataSet::setText(m_RootLayer, "content", "                                                                                             ");
	GameDataSet::setText(m_RootLayer,"content",p->content);
	
    return true;
}

void GameChatItemLayer::TouchEvent(){
	//发送系统语音给服务器
	
}