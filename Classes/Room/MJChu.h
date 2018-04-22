#ifndef __MJChu_SCENE_H__
#define __MJChu_SCENE_H__

#include "AppMacros.h"
#include "BaseLayer.h"
using namespace cocos2d;
using namespace ui;
using namespace std;

#define MAX_COUNT 22


class MJChu : public BaseLayer
{
public:
	MJChu();
	~MJChu();
	static MJChu* create(int pos);
	virtual bool init(int pos);
	
	void TouchEvent(CCObject *obj, TouchEventType type);
	
	void resetCard();
	void PushCard(int index,int card);
	void PushCard(string cards);
private:
	int m_position;
	int m_index;
	ImageView *m_cardbgs[MAX_COUNT];
	ImageView *m_cardimgs[MAX_COUNT];
private:
	
};

#endif 