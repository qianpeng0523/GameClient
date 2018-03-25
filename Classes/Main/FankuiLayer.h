#ifndef __FankuiLayer_SCENE_H__
#define __FankuiLayer_SCENE_H__

#include "AppMacros.h"
#include "BaseLayer.h"
using namespace cocos2d;
using namespace ui;
using namespace std;

class FankuiLayer : public BaseLayer
{
public:
	FankuiLayer();
	~FankuiLayer();
	CREATE_FUNC(FankuiLayer);
    virtual bool init();
	
	void TouchEvent(CCObject *obj, TouchEventType type);

	void FeedBackFinish();
private:
	ui::EditBox *m_input;
	Button *m_btn;
private:
	
};

#endif 