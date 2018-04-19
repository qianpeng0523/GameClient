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
	GameControl::getIns()->setTopTips(m_tips);
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
	float y = m_RootLayer->getPositionY();
	Size sz = m_RootLayer->getSize();
	float dt1 = 0.5;
	float dt2 = 1.0;
	if (m_tips.empty()){
		if (y == 0){
			tt->setTag(1);
			tt->setPositionY(-tt->getSize().height-sz.height/2.0);
			tt->runAction(Sequence::create(Show::create(), MoveTo::create(dt1, ccp(tt->getPositionX(), sz.height / 2.0)),
				DelayTime::create(dt2),
				CCCallFuncN::create(this, callfuncN_selector(TopTipLayer::CallBack)),
				NULL));
		}
		else{
			m_RootLayer->setTag(2);
			tt->setPositionY(sz.height / 2.0);
			m_RootLayer->runAction(Sequence::create(Show::create(), MoveTo::create(dt1, ccp(0, 0)),
				DelayTime::create(dt2),
				 CCCallFuncN::create(this, callfuncN_selector(TopTipLayer::CallBack))
				, NULL));
		}
	}
	else{
		if (y == 0){
			tt->setPositionY(tt->getSize().height + sz.height / 2.0);
			tt->runAction(Sequence::create(Show::create(), MoveTo::create(dt1, ccp(tt->getPositionX(), sz.height / 2.0)),
				DelayTime::create(dt2),
				MoveTo::create(dt1, ccp(tt->getPositionX(), -tt->getSize().height - sz.height / 2.0)),
				CCCallFuncN::create(this, callfuncN_selector(TopTipLayer::CallBack)), NULL));
		}
		else{
			tt->setPositionY(sz.height / 2.0);
			m_RootLayer->runAction(Sequence::create(Show::create(), MoveTo::create(dt1, ccp(0, 0)),
				DelayTime::create(dt2),
				CCCallFunc::create(this, callfunc_selector(TopTipLayer::CallBack))
				, NULL));
		}
	}
	
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

void TopTipLayer::CallBack(Node *node){
	int tag = node->getTag();
	Size sz = m_RootLayer->getSize();
	if (m_tips.empty()){
		m_lock = false;
		m_RootLayer->runAction(Sequence::create(
			MoveTo::create(0.5, ccp(0, sz.height))
			, Hide::create()
			,NULL));
	}
	else{
		CallBack();
	}
}