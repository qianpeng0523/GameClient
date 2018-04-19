#include "TopTipLayer.h"
#include "GameControl.h"
#include "GameDataSet.h"
#include "ClientSocket.h"
#include "LoginScene.h"
#include "LoginInfo.h"
#include "MainScene.h"





TopTipLayer::TopTipLayer(){
	m_lock = false;
	GameControl::getIns()->setTopTipLayer(this);
}

TopTipLayer::~TopTipLayer(){
	RootRegister::getIns()->resetWidget(m_RootLayer);
	if (this == GameControl::getIns()->getTopTipLayer()){
		GameControl::getIns()->setTopTipLayer(NULL);

	}
}

bool TopTipLayer::init()
{             
	if (!Layer::init())
    {
        return false;
    }
	
	m_RootLayer =RootRegister::getIns()->getWidget("toptiplayer.json");
	this->addChild(m_RootLayer);
	this->setContentSize(m_RootLayer->getSize());
    return true;
}

void TopTipLayer::setContent(string tip){
	m_lock = true;
	Text *tt =GameDataSet::setText(m_RootLayer, "tip", tip);
	tt->setPositionY(tt->getParent()->getContentSize().height/2.0);
	Size sz = m_RootLayer->getSize();
	m_RootLayer->runAction(Sequence::create(Show::create(),MoveTo::create(0.2, ccp(0, 0)), 
		DelayTime::create(0.5),
		 MoveTo::create(0.2, ccp(0, sz.height))
		 , Hide::create(), CCCallFunc::create(this, callfunc_selector(TopTipLayer::CallBack))
		, NULL));
}

void TopTipLayer::PushTip(string tip){
	m_tips.push_back(tip);
	if (!m_lock){
		auto itr = m_tips.begin();
		if (itr != m_tips.end()){
			setContent(*itr);
			m_tips.erase(itr);
		}
	}
}

void TopTipLayer::CallBack(){
	m_lock = false;
	auto itr = m_tips.begin();
	if (itr != m_tips.end()){
		setContent(*itr);
		m_tips.erase(itr);
	}
}