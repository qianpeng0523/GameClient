#ifndef __JoinRoomLayer_SCENE_H__
#define __JoinRoomLayer_SCENE_H__

#include "AppMacros.h"
#include "BaseLayer.h"
using namespace cocos2d;
using namespace ui;
using namespace std;




class JoinRoomLayer : public BaseLayer
{
public:
	JoinRoomLayer();
	~JoinRoomLayer();
	CREATE_FUNC(JoinRoomLayer);
    virtual bool init();
	
	void TouchEvent(CCObject *obj, TouchEventType type);
	
private:
	TextBMFont *m_number[6];
	int m_index;
private:
	
};

#endif 