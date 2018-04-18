#include "LoadingLayer.h"
#include "GameControl.h"
#include "GameDataSet.h"
#include "ClientSocket.h"
#include "LogoScene.h"
#include "LoginInfo.h"
#include "MainScene.h"
Scene *LoadingLayer::createScene(int type){
	Scene *scene = Scene::create();
	if (scene){
		LoadingLayer *p = LoadingLayer::create(type);
		scene->addChild(p);
	}
	return scene;
}


LoadingLayer::LoadingLayer(){
	GameControl::getIns()->setLoadingLayer(this);
	m_isupdate = false;
	openUpdate(true);
}

LoadingLayer::~LoadingLayer(){
	m_isupdate = false;
	openUpdate(false);
	char buff[50];
	sprintf(buff, XXIconv::GBK2UTF("正在加载资源%d%%").c_str(), 0);
	log("%s", buff);
	GameDataSet::setText(m_RootLayer, "pro", buff);
	RootRegister::getIns()->initPercent();
	m_pParticleSystem->removeFromParentAndCleanup(true);
	RootRegister::getIns()->resetWidget(m_RootLayer);
	if (this == GameControl::getIns()->getLoadingLayer()){
		GameControl::getIns()->setLoadingLayer(NULL);
	}
}

LoadingLayer *LoadingLayer::create(int type){
	LoadingLayer *p = new LoadingLayer();
	if (p&&p->init(type)){
		p->autorelease();
	}
	else{
		CC_SAFE_DELETE(p);
	}
	return p;
}

bool LoadingLayer::init(int type)
{             
	if (!Layer::init())
    {
        return false;
    }
	m_type = type;
	m_RootLayer =RootRegister::getIns()->getWidget("loading.json");
	this->addChild(m_RootLayer);

	this->setContentSize(m_RootLayer->getSize());
	LoadingBar *bar = (LoadingBar *)GameDataSet::getLayout(m_RootLayer, "ProgressBar");
	bar->setPercent(0);
	this->runAction(Sequence::create(DelayTime::create(0.5), CCCallFunc::create(this, callfunc_selector(LoadingLayer::CallBack)), NULL));

	m_pParticleSystem = CCParticleSystemQuad::create("particle/Zjjjjjjjjjjq.plist");
	Point pos = bar->getPosition();
	m_pParticleSystem->setPositionY(pos.y);
	m_pParticleSystem->setPositionX(pos.x - bar->getSize().width / 2.0);
	m_pParticleSystem->setAutoRemoveOnFinish(true);
	bar->getParent()->addChild(m_pParticleSystem, 2);

    return true;
}

void LoadingLayer::CallBack(){
	RootRegister::getIns()->loadJson(m_type);
}

void LoadingLayer::update(float dt){
	float per = RootRegister::getIns()->getPercent();
	LoadingBar *bar = (LoadingBar *)GameDataSet::getLayout(m_RootLayer, "ProgressBar");
	bar->setPercent(per);
	char buff[50];
	sprintf(buff, XXIconv::GBK2UTF("正在加载资源%d%%").c_str(), (int)per);
	GameDataSet::setText(m_RootLayer, "pro", buff);
	int w = bar->getSize().width;
	m_pParticleSystem->setPositionX(bar->getPositionX() - w / 2.0+w*per/100.0);
	if(per>=100){
		openUpdate(false);
		this->runAction(Sequence::create(DelayTime::create(0.3),
			CCCallFunc::create(this, callfunc_selector(LoadingLayer::replaceScene))
			,NULL));
	}
}

void LoadingLayer::replaceScene(){
	Scene *scene = NULL;
	switch (m_type)
	{
	case 1:
		scene = LogoScene::create();
		break;
	case 2:
		scene = MainScene::create();
		break;
	case 3:
		scene = MJGameScene::create();
		break;
	default:
		break;
	}
	Director::sharedDirector()->replaceScene(scene);
}

void LoadingLayer::openUpdate(bool isopen){
// 	if (!isopen){
// 		if (m_isupdate){
// 			m_isupdate = false;
// 			Director::sharedDirector()->getScheduler()->unscheduleUpdate(this);
// 		}
// 	}
// 	else{
// 		if (!m_isupdate){
// 			m_isupdate = true;
// 			Director::sharedDirector()->getScheduler()->scheduleUpdate(this, 1, true);
// 		}
// 	}
}