#ifndef __MJWall_SCENE_H__
#define __MJWall_SCENE_H__

#include "AppMacros.h"
#include "BaseLayer.h"
using namespace cocos2d;
using namespace ui;
using namespace std;




class MJWall : public BaseLayer
{
public:
	MJWall();
	~MJWall();
	static MJWall* create(int pos);
	virtual bool init(int pos);
	
	void TouchEvent(CCObject *obj, TouchEventType type);
	
private:
	int m_position;
private:
	
};

#endif 