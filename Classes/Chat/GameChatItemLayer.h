#ifndef __GameChatItemLayer_SCENE_H__
#define __GameChatItemLayer_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Adaptation.h"
#include "XXEventDispatcher.h"
#include "XXHttpRequest.h"
#include "YuYinConfig.h"
#include "BaseLayer.h"

using namespace cocos2d;
using namespace ui;
using namespace std;


class GameChatItemLayer : public BaseLayer
{
public:
	GameChatItemLayer();
	~GameChatItemLayer();
	static GameChatItemLayer *create(YuYinItem *p);
	virtual bool init(YuYinItem *p);
	
	void TouchEvent();
	YuYinItem *getYuYinItem(){
		return m_pYuYinItem;
	}
private:
	
	YuYinItem *m_pYuYinItem;
	
private:
	
};

#endif 