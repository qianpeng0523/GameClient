#include "MainScene.h"
#include "KeyBoard.h"
USING_NS_CC;

MainScene::MainScene(){
	m_pMainLayer = NULL;
}

MainScene::~MainScene(){
	
}

bool MainScene::init()
{
	if (!CCScene::init())
	{
		return false;
	}
	KeyBoard::getIns()->setKetPad(EXIT_KEYTYPE, this);
	if (!m_pMainLayer){
		m_pMainLayer = MainLayer::create();
		this->addChild(m_pMainLayer);
	}

	return true;
}