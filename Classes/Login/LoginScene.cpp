#include "LoginScene.h"
#include "SimpleAudioEngine.h"
#include "AppMacros.h"
#include "KeyBoard.h"
USING_NS_CC;

LoginScene::LoginScene(){
	m_pLoginLayer = NULL;
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
	if (!m_pLoginLayer){
		m_pLoginLayer = LoginLayer::create();
		this->addChild(m_pLoginLayer);
	}
   
	return true;
}