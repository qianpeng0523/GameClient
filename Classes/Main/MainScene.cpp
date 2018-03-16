#include "MainScene.h"

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

	if (!m_pMainLayer){
		m_pMainLayer = MainLayer::create();
		this->addChild(m_pMainLayer);
	}

	return true;
}