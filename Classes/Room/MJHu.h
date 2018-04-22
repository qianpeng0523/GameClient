#ifndef __MJHu_SCENE_H__
#define __MJHu_SCENE_H__

#include "AppMacros.h"
#include "BaseLayer.h"
using namespace cocos2d;
using namespace ui;
using namespace std;




class MJHu : public BaseLayer
{
public:
	MJHu();
	~MJHu();
	static MJHu* create(int pos);
	virtual bool init(int pos);
	
	void TouchEvent(CCObject *obj, TouchEventType type);
	
	void resetCard();
	void setCard(int index,int card);
	void setCards(string cards);
private:
	int m_position;
	ImageView *m_cardbgs[14];
	ImageView *m_cardimgs[14];
	int m_index;
private:
	
};

#endif 