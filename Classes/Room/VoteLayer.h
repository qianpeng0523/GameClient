#ifndef __VoteLayer_SCENE_H__
#define __VoteLayer_SCENE_H__

#include "AppMacros.h"
#include "BaseLayer.h"
using namespace cocos2d;
using namespace ui;
using namespace std;




class VoteLayer : public BaseLayer
{
public:
	VoteLayer();
	~VoteLayer();
	static VoteLayer* create();
	virtual bool init();
	
	void TouchEvent(CCObject *obj, TouchEventType type);
	void setVote(string uid,bool agree);
	void setTime(int time);
private:
	Text *m_texts[4];
	string m_uids[4];
	string m_names[4];
	TextBMFont *m_timedown;
};

#endif 