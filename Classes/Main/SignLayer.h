#ifndef __SignLayer_SCENE_H__
#define __SignLayer_SCENE_H__

#include "AppMacros.h"
#include "BaseLayer.h"
using namespace cocos2d;
using namespace ui;
using namespace std;

class SignLayer : public BaseLayer
{
public:
	SignLayer();
	~SignLayer();
	static SignLayer *create();
	virtual bool init();
	
	void TouchEvent(CCObject *obj, TouchEventType type);
	void OpenRun(bool isopen);

	void Run();//点击抽奖转
	void RunCall(Node *node);
	void RunEnd();

	void setSignData();
private:
	void RunLight(float dt);
	void ShowLight(bool isshow);
	void RunPoint(bool isrun);
	void CallFun();
	void RunEndCall();
private:
	bool m_isopen;
	bool m_isupdate;
	Layout *m_light;
	Layout *m_point;
	Button *m_btn;
	int m_index;
	int m_curindex;
};

#endif 