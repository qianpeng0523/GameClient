#include "MainLayer.h"
#include "GameControl.h"
#include "GameDataSet.h"
#include "ClientSocket.h"
#include "LogoScene.h"

MainLayer::MainLayer(){
	GameControl::getIns()->setMainLayer(this);
}

MainLayer::~MainLayer(){
	if (this == GameControl::getIns()->getMainLayer()){
		GameControl::getIns()->setMainLayer(NULL);

	}
}

bool MainLayer::init()
{             
	if (!Layer::init())
    {
        return false;
    }
	
	m_RootLayer = (Layout *)GUIReader::shareReader()->widgetFromJsonFile("mainlayer.json");
	this->addChild(m_RootLayer);

	SEL_TouchEvent selector = toucheventselector(MainLayer::TouchEvent);
	
	GameDataSet::getButton(m_RootLayer, "back_btn", selector, this);
	GameDataSet::getButton(m_RootLayer, "guize_btn", selector, this);
	GameDataSet::getButton(m_RootLayer, "card_bg", selector, this);
	GameDataSet::getButton(m_RootLayer, "head_btn", selector, this);
	GameDataSet::getButton(m_RootLayer, "create", selector, this);
	GameDataSet::getButton(m_RootLayer, "join", selector, this);
	GameDataSet::getButton(m_RootLayer, "zhanji_btn", selector, this);
	GameDataSet::getButton(m_RootLayer, "set_btn", selector, this);

	GameDataSet::setTextStrokLabel(m_RootLayer, "name", XXIconv::GBK2UTF("名字5个字"), ccc3(255, 255, 255), ccc3(0, 0, 0), "fonts/DFYuanW7-GB2312.ttf");
	GameDataSet::setTextStrokLabel(m_RootLayer, "id", "", ccc3(255, 255, 255), ccc3(0, 0, 0), "fonts/DFYuanW7-GB2312.ttf");
	GameDataSet::setTextStrokLabel(m_RootLayer, "num", "", ccc3(255, 255, 255), ccc3(0, 0, 0), "fonts/DFYuanW7-GB2312.ttf");

    return true;
}

void MainLayer::TouchEvent(CCObject *obj, TouchEventType type){
	Button *btn = (Button *)obj;
	string name = btn->getName();
	if (type == TOUCH_EVENT_ENDED){
		if (name.compare("back_btn") == 0){
			ClientSocket::getIns()->close();
			auto director = Director::getInstance();
			Scene *scene = LogoScene::create();
			director->replaceScene(scene);
		}
		else if (name.compare("guize_btn") == 0){
			
		}
		else if (name.compare("card_bg") == 0){
			
		}
		else if (name.compare("head_btn") == 0){
			
		}
		else if (name.compare("create") == 0){
			
		}
		else if (name.compare("join") == 0){
			
		}
		else if (name.compare("set_btn") == 0){
			
		}
		else if (name.compare("zhanji_btn") == 0){
			
		}
		
	}
}