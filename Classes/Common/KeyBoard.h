
#ifndef _KeyBoard_h
#define _KeyBoard_h
#include "cocos2d.h"
#include "cocos-ext.h"
#include "BaseLayer.h"
using namespace cocos2d;
using namespace ui;

enum KEYTYPE
{
	EXIT_KEYTYPE=1,
	BACK_KEYTYPE
};

class KeyLayer :public BaseLayer{
public:
	KeyLayer();
	~KeyLayer();
	static KeyLayer *create(KEYTYPE type);
	bool init(KEYTYPE type);

	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	
	void setKeyType(KEYTYPE type){
		m_type = type;
	}
private:
	KEYTYPE m_type;
};

class KeyBoard :public Object
{
public:
	KeyBoard();
	~KeyBoard();
	virtual bool init();
	static KeyBoard* getIns();
	void setKetPad(KEYTYPE type, Node *parent);
	void setKeyLayer(KeyLayer *p){
		m_pKeyLayer = p;
	}
	KeyLayer *getKeyLayer(){
		return m_pKeyLayer;
	}
	void setMainBack(bool isMainback){
		m_isMainback = isMainback;
	}
	bool isMainBack(){
		return m_isMainback;
	}
private:
	static KeyBoard *m_ins;
	KeyLayer *m_pKeyLayer;
	bool m_isMainback;
};
#endif
