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
	m_bg = (ImageView *)GameDataSet::getLayout(m_RootLayer, "bg");
    return true;
}

void TopTipLayer::setContent(string tip){
	m_lock = true;
	Text *tt =GameDataSet::setText(m_RootLayer, "tip", tip);
	float y = m_bg->getPositionY();
	Size sz = m_bg->getSize();
	float dt1 = 0.5;
	float dt2 = 1.0;
	if (m_tips.empty()){
		if (y == sz.height / 2.0){
			tt->setTag(1);
			tt->setPositionY(tt->getSize().height + sz.height / 2.0);
			tt->runAction(Sequence::create(Show::create(), MoveTo::create(dt1, ccp(tt->getPositionX(), sz.height / 2.0)),
				DelayTime::create(dt2),
				CCCallFuncN::create(this, callfuncN_selector(TopTipLayer::CallBack)),
				NULL));
		}
		else{
			m_bg->setTag(2);
			tt->setPositionY(sz.height / 2.0);
			m_bg->runAction(Sequence::create(Show::create(), MoveTo::create(dt1, sz/2.0),
				DelayTime::create(dt2),
				 CCCallFuncN::create(this, callfuncN_selector(TopTipLayer::CallBack))
				, NULL));
		}
	}
	else{
		if (y == sz.height / 2.0){
			tt->setTag(3);
			tt->setPositionY(tt->getSize().height + sz.height / 2.0);
			tt->runAction(Sequence::create(Show::create(), MoveTo::create(dt1, ccp(tt->getPositionX(), sz.height / 2.0)),
				DelayTime::create(dt2),
				MoveTo::create(dt1, ccp(tt->getPositionX(), -tt->getSize().height - sz.height / 2.0)),
				CCCallFuncN::create(this, callfuncN_selector(TopTipLayer::CallBack)), NULL));
		}
		else{
			m_bg->setTag(4);
			tt->setPositionY(sz.height / 2.0);
			m_bg->runAction(Sequence::create(Show::create(), MoveTo::create(dt1, sz/2.0),
				DelayTime::create(dt2),
				CCCallFuncN::create(this, callfuncN_selector(TopTipLayer::CallBack))
				, NULL));
		}
	}
	
}

void TopTipLayer::PushTip(string tip){
	m_tips.push_back(tip);
	if (!m_lock){
		auto itr = m_tips.begin();
		if (itr != m_tips.end()){
			string tt = *itr;
			m_tips.erase(itr);
			setContent(tt);
		}
	}
}

void TopTipLayer::CallBack(){
	m_lock = false;
	auto itr = m_tips.begin();
	if (itr != m_tips.end()){
		string tt = *itr;
		m_tips.erase(itr);
		setContent(tt);
	}
}

void TopTipLayer::CallBack(Node *node){
	int tag = node->getTag();
	//log("tag:%d,empty:%s",tag,m_tips.empty()?"true":"false");
	Size sz = m_bg->getSize();
	if (m_tips.empty()){
		m_lock = false;
		m_bg->runAction(Sequence::create(
			MoveTo::create(0.5, ccp(sz.width/2.0, sz.height*1.5))
			, Hide::create()
			,NULL));
	}
	else{
		if (tag == 2){
			Text *tt = (Text *)GameDataSet::getLayout(m_RootLayer, "tip");
			tt->runAction(Sequence::create(
				MoveTo::create(0.5, ccp(tt->getPositionX(), -tt->getSize().height - sz.height / 2.0)),
				CCCallFunc::create(this, callfunc_selector(TopTipLayer::CallBack)),NULL));
		}
		else{
			CallBack();
		}
	}
}