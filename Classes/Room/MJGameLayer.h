#ifndef __MJGameLayer_SCENE_H__
#define __MJGameLayer_SCENE_H__

#include "AppMacros.h"
#include "BaseLayer.h"
using namespace cocos2d;
using namespace ui;
using namespace std;




class MJGameLayer : public BaseLayer
{
public:
	MJGameLayer();
	~MJGameLayer();
	CREATE_FUNC(MJGameLayer);
    virtual bool init();
	
	void TouchEvent(CCObject *obj, TouchEventType type);
	
	void resetFa();
	void setFa(int pos,int count);
	void update(float dt);
	void setTime(int time);
	void setTimeVisible(bool isv);
private:
	ImageView *m_faimgs[4];
	TextBMFont *m_facounts[4];
	int m_facards[4][4];
	int m_downtime;
private:
	
};

#endif 