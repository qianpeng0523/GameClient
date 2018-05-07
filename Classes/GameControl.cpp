#include "GameControl.h"



GameControl *GameControl::m_ins=NULL;

GameControl::GameControl(){
	m_pLoginMainLayer = NULL;
	m_pMainLayer = NULL;
	m_pUserInfoLayer = NULL;
	m_pSetLayer = NULL;
	m_pShopLayer = NULL;
	m_pSignLayer = NULL;
	m_pFriendLayer = NULL;
	m_pFankuiLayer = NULL;
	m_pFreeLayer = NULL;
	m_pExchangeLayer = NULL;
	m_pTaskLayer = NULL;
	m_pMailLayer = NULL;
	m_pActiveLayer = NULL;
	m_pFirstChargeLayer = NULL;
	m_pAboutLayer = NULL;
	m_pHelpLayer = NULL;
	m_pChatLayer = NULL;
	m_pMailTipLayer = NULL;
	m_pRewardTipLayer = NULL;
	m_pLoadingLayer = NULL;
	m_pCreateRoomLayer = NULL;
	m_pJoinRoomLayer = NULL;
	m_pMJGameLayer = NULL;
	m_pGameUI = NULL;
	m_pMJGameScene = NULL;
	m_pTipLayer = NULL;
	m_pTopTipLayer = NULL;
	m_pGameChatLayer = NULL;
	m_pLoginLayer = NULL;
	m_RegLayer = NULL;
	m_topcopy = false;
	m_index = 0;
	CCDirector::sharedDirector()->getScheduler()->scheduleUpdate(this, 1, false);
}

GameControl::~GameControl(){
	CCDirector::sharedDirector()->getScheduler()->unscheduleUpdate(this);
}

bool GameControl::init()
{
	
    return true;
}

GameControl* GameControl::getIns(){
	if (!m_ins){
		m_ins = new GameControl();
		m_ins->init();
	}
	return m_ins;
}

void GameControl::replaceScene(Scene *scene){
	TextureCache::sharedTextureCache()->removeUnusedTextures();
	Director *p = Director::sharedDirector();
	CCTransitionFade *reScene = CCTransitionFade::create(0.3, scene);
	p->replaceScene(reScene);
}

void GameControl::PushLaBa(string content, int times){
	LaBaItem *item = new LaBaItem();
	item->_content = content;
	item->_times = times;
	m_contents.push_back(item);
}

void GameControl::update(float dt){
	if (m_pMainLayer&&m_pMainLayer->isFinished() && !m_contents.empty()){
		int sz = m_contents.size();
		if (m_index >= sz){
			m_index = 0;
		}
		m_itr = m_contents.begin()+m_index++;
		if (m_itr != m_contents.end()){
			LaBaItem *item = *m_itr;
			string content = item->_content;
			int times = item->_times;
			if (m_pMainLayer){
				m_pMainLayer->ShowLaBa(content);
				if (times != -1){
					times -= 1;
					item->_times = times;
					if (times <= 0){
						delete item;
						m_contents.erase(m_itr);
					}
				}
			}
		}
	}
	if (m_topcopy){
		m_topcopy = false;
		for (auto itr = m_toptips.begin(); itr != m_toptips.end();){
			ShowTopTip(*itr);
			itr = m_toptips.erase(itr);
		}
	}
}

void GameControl::ShowLoading(){
	Scene *scene = Director::sharedDirector()->getRunningScene();
	if (scene){
		LoadLayer *p = (LoadLayer *)scene->getChildByName("g_loading");
		if (!p){
			p = LoadLayer::create(NULL);
			p->setName("g_loading");
			scene->addChild(p);
		}
		else if (!p->isVisible()){
			p->setVisible(true);
		}
	}
}

void GameControl::HideLoading(){
	Scene *scene = Director::sharedDirector()->getRunningScene();
	if (scene){
		scene->removeChildByName("g_loading", true);
	}
}

void GameControl::ShowLoading(BaseLayer *layer, Layout *ly){
	if (m_pLoadings.find(layer)!=m_pLoadings.end()){
		map<Layout *, LoadLayer*> mp=m_pLoadings.at(layer);
		LoadLayer *p = NULL;
		if (mp.find(ly) != mp.end()){
			p = mp.at(ly);
			p->setVisible(true);
		}
		else{
			p = LoadLayer::create(ly);
			ly->addChild(p);
			mp.insert(make_pair(ly, p));
		}
	}
}

void GameControl::HideLoading(BaseLayer *layer){
	if (m_pLoadings.find(layer) != m_pLoadings.end()){
		map<Layout *, LoadLayer*> mp = m_pLoadings.at(layer);
		for (auto itr = mp.begin(); itr != mp.end();){
			LoadLayer *p = itr->second;
			p->removeFromParentAndCleanup(true);
			itr = mp.erase(itr);
		}
		m_pLoadings.clear();
	}
}

void GameControl::HideLoading(BaseLayer *layer, Layout *ly){
	if (m_pLoadings.find(layer) != m_pLoadings.end()){
		map<Layout *, LoadLayer*> mp = m_pLoadings.at(layer);
		for (auto itr = mp.begin(); itr != mp.end();){
			Layout *parent = itr->first;
			if (parent == ly){
				LoadLayer *p = itr->second;
				p->removeFromParentAndCleanup(true);
				itr = mp.erase(itr);
				break;
			}
			else{
				itr++;
			}
		}
		if (mp.empty()){
			m_pLoadings.erase(m_pLoadings.find(layer));
		}
	}
}

void GameControl::ShowTopTip(string tip){
	if (!m_pTopTipLayer){
		m_pTopTipLayer = TopTipLayer::create();
		Director *pDirector = Director::sharedDirector();
		pDirector->getRunningScene()->addChild(m_pTopTipLayer, 2);
		Size sz = pDirector->getWinSize();
		m_pTopTipLayer->setPositionX(m_pTopTipLayer->getContentSize().width / 2.0);
		if(m_pMainLayer){
			m_pTopTipLayer->setPositionX(m_pTopTipLayer->getPositionX()+60);
			m_pTopTipLayer->setPositionY(sz.height - m_pTopTipLayer->getContentSize().height-66);
		}else{
			m_pTopTipLayer->setPositionY(sz.height - m_pTopTipLayer->getContentSize().height);
		}
		
		m_pTopTipLayer->PushTip(tip);
	}
	else{
		m_pTopTipLayer->PushTip(tip);
	}
}

void GameControl::setTopTip(bool istop){
	if (m_pTopTipLayer){
		Director *pDirector = Director::sharedDirector();
		Size sz = pDirector->getWinSize();
		m_pTopTipLayer->setPositionY(istop ? (sz.height - m_pTopTipLayer->getContentSize().height) : (sz.height - m_pTopTipLayer->getContentSize().height - 66));
	}
}

void GameControl::setTopTips(vector<string> vec){
	std::copy(vec.begin(), vec.end(), std::back_inserter(m_toptips));
	m_topcopy = true;
}