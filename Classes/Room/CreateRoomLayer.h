#ifndef __CreateRoomLayer_SCENE_H__
#define __CreateRoomLayer_SCENE_H__

#include "AppMacros.h"
#include "BaseLayer.h"

using namespace cocos2d;
using namespace ui;
using namespace std;




class CreateRoomLayer : public BaseLayer
{
public:
	CreateRoomLayer();
	~CreateRoomLayer();
	CREATE_FUNC(CreateRoomLayer);
    virtual bool init();
	
	void TouchEvent(CCObject *obj, TouchEventType type);
	void SelectItem(int index);
private:
	Button *m_btns[2];
	Layout *m_bg[2];
	TextBMFont *m_btntext[2];
private:
	
};

#endif 