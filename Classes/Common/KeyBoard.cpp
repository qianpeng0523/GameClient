#include "KeyBoard.h"
#include "TipLayer.h"
#include "GameControl.h"
#include "LoginMainLayer.h"


KeyLayer::KeyLayer(){
	//对手机返回键的监听 
	auto listener = EventListenerKeyboard::create();
	//和回调函数绑定 
	listener->onKeyPressed = CC_CALLBACK_2(KeyLayer::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(KeyLayer::onKeyReleased, this);
	//添加到事件分发器中 
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

KeyLayer::~KeyLayer(){
	if (KeyBoard::getIns()->getKeyLayer() == this){
		KeyBoard::getIns()->setKeyLayer(NULL);
	}
}

KeyLayer *KeyLayer::create(KEYTYPE type){
	KeyLayer *pRet = new KeyLayer();
	if (pRet&&pRet->init(type)){
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
	}

	return pRet;
}

bool KeyLayer::init(KEYTYPE type){
	if (!Layer::init()){
		return false;
	}
	m_type = type;
	return true;
}

void KeyLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event){
	log("press:%c", keyCode);
}

void KeyLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event){
	log("end:%c", keyCode);
	if (keyCode == EventKeyboard::KeyCode::KEY_BACK){
		GameControl *p = GameControl::getIns();
		TipLayer *tip = p->getTipLayer();
		if (tip){
			tip->removeFromParentAndCleanup(true);
		}
		else{
			string content;
			TIP_ENUM_TYPE type;
			if (m_type == EXIT_KEYTYPE){
				type = TIP_TYPE_END;
				content = XXIconv::GBK2UTF("是否确定要退出游戏?");
				
			}
			else if (m_type == BACK_KEYTYPE){
				type = TIP_TYPE_BACK;
				content = XXIconv::GBK2UTF("是否确定返回?");
			}
			tip = TipLayer::create(type);
			this->addChild(tip);
			tip->setContent(content);
		}
	}
}




















KeyBoard *KeyBoard::m_ins = NULL;

KeyBoard::KeyBoard(){
	m_pKeyLayer = NULL;
	m_isMainback = false;
}

KeyBoard::~KeyBoard(){
	m_ins = NULL;
}

bool KeyBoard::init(){
	
	return true;
}

KeyBoard* KeyBoard::getIns(){
	if (!m_ins){
		m_ins = new KeyBoard();
		m_ins->init();
	}
	return m_ins;
}

void KeyBoard::setKetPad(KEYTYPE type,Node *parent){
	if (!m_pKeyLayer){
		m_pKeyLayer = KeyLayer::create(type);
		m_pKeyLayer->retain();
	}
	else{
		m_pKeyLayer->removeFromParent();
	}
	if (m_pKeyLayer&&!m_pKeyLayer->getParent()){
		m_pKeyLayer->setKeyType(type);
		parent->addChild(m_pKeyLayer,2000);
	}
}