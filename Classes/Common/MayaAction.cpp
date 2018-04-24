#include "MayaAction.h"
#include "AppMacros.h"
#include "XXIconv.h"


MayaAction *MayaAction::m_ins=NULL;

MayaAction::MayaAction(){
	m_dict = new Dictionary();
	m_lock = false;
	m_SpriteFrameCache = SpriteFrameCache::sharedSpriteFrameCache();
	Director::sharedDirector()->getScheduler()->scheduleUpdate(this, 1, false);
}

MayaAction::~MayaAction(){
	CC_SAFE_DELETE(m_dict);
	Director::sharedDirector()->getScheduler()->unscheduleUpdate(this);
}

MayaAction *MayaAction::getIns() {
	if(!m_ins){
		m_ins=new MayaAction();
		m_ins->init();
	}
	return m_ins;
}

bool MayaAction::init() {
	m_SpriteFrameCache->addSpriteFramesWithFile("majiangtu/tx_youxi_shaizi.plist","majiangtu/tx_youxi_shaizi.png");
	return true;
}

void MayaAction::update(float dt){
	if (!m_lock&&!m_curact.empty()){
		m_lock = true;
		auto itr = m_curact.begin();
		ActionItem *p = *itr;
		m_curact.erase(itr);
		preloadAction(p);
	}
}

void MayaAction::initLoad(int scenetype){
	auto vec = ActionConfig::shareActionConfig()->getActionItems(scenetype);
	auto itr = vec.begin();
	for (itr; itr != vec.end(); itr++){
		ActionItem *p = *itr;
		m_curact.push_back(p);
	}
}

void MayaAction::Play(ImageView *node, string key){
	Sprite *spr1 = ((ui::Scale9Sprite *)node->getVirtualRenderer())->getSprite();
	Sprite *spr = Sprite::create();
	spr->setSpriteFrame(spr1->getSpriteFrame());
	node->getParent()->addChild(spr);
	node->setVisible(false);
	spr->setPosition(node->getPosition());
	Play(spr, key);
}

void MayaAction::Play(ImageView *node, string key, CCCallFuncND *selector){
	Sprite *spr1 = ((ui::Scale9Sprite *)node->getVirtualRenderer())->getSprite();
	Sprite *spr = Sprite::create();
	spr->setSpriteFrame(spr1->getSpriteFrame());
	node->getParent()->addChild(spr);
	node->setVisible(false);
	spr->setPosition(node->getPosition());
	Play(spr, key, selector);
}

void MayaAction::Play(Node *node, string key){
	Play(node, key, NULL);
}

void MayaAction::Play(Node *node, string key, CCCallFuncND *selector){
	ActionItem *p = ActionConfig::shareActionConfig()->getActionItem(key);
	if (p){
		CCAnimate *ani = (CCAnimate *)m_dict->objectForKey(key);
		if (!ani){
			ani = preloadAction(p);
		}
		if (ani){
			int times = p->_time;
			if (times == 1){
				if (selector){
					node->runAction(Sequence::create(ani, selector,RemoveSelf::create(true), NULL));
				}
				else{
					node->runAction(Sequence::create(ani, RemoveSelf::create(true), NULL));
				}
			}
			else if (times == -1){
				if (selector){
					node->runAction(RepeatForever::create(Sequence::create(ani, selector, NULL)));
				}
				else{
					node->runAction(RepeatForever::create(Sequence::create(ani, NULL)));
				}
			}
			else{
				if (selector){
					node->runAction(Sequence::create(Repeat::create(Sequence::create(ani, NULL), times), selector, RemoveSelf::create(true), NULL));
				}
				else{
					node->runAction(Sequence::create(Repeat::create(Sequence::create(ani, NULL), times), RemoveSelf::create(true), NULL));
				}
				
			}
		}
		else{
			log("no load!!! no action");
		}
	}
	else{
		log("key not exit!!!");
	}
}

CCAnimate* MayaAction::preloadAction(string key){
	ActionItem *p = ActionConfig::shareActionConfig()->getActionItem(key);
	if (p){
		return preloadAction(p);
	}
	return NULL;
}

CCAnimate* MayaAction::preloadAction(ActionItem *p){
	string name = p->_name;
	CCAnimate *ani = (CCAnimate *)m_dict->objectForKey(name);
	if (!ani){
		CCAnimation *an = CCAnimation::create();
		an->setRestoreOriginalFrame(true);
		int count = p->_count;
		int begin = p->_begin;
		char buff[300];
		for (int i = begin; i < begin+count; i++){
			sprintf(buff,p->_file.c_str(),i);
			log("%s",buff);
			SpriteFrame *frame = m_SpriteFrameCache->getSpriteFrameByName(buff);
			if (!frame){
				log("not exit!!!");
			}
			an->addSpriteFrame(frame);
		}
		an->setDelayPerUnit(p->_dur/count);
		ani = CCAnimate::create(an);
		//ani->setDuration(p->_dur);
		m_dict->setObject(ani,name);
	}
	return ani;
}