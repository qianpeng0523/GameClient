#include "LoginScene.h"
#include "SimpleAudioEngine.h"
#include "AppMacros.h"
#include "KeyBoard.h"
USING_NS_CC;

LoginScene::LoginScene(){
	m_pLoginMainLayer = NULL;
}

LoginScene::~LoginScene(){
	
}

bool LoginScene::init()
{
	if (!CCScene::init())
	{
		return false;
	}
	KeyBoard::getIns()->setKetPad(EXIT_KEYTYPE, this);
	if (!m_pLoginMainLayer){
		m_pLoginMainLayer = LoginMainLayer::create();
		this->addChild(m_pLoginMainLayer);
	}
   
	return true;
}