#ifndef __TaskLayer_SCENE_H__
#define __TaskLayer_SCENE_H__

#include "AppMacros.h"
#include "BaseLayer.h"
using namespace cocos2d;
using namespace ui;
using namespace std;



class TaskItemLayer : public BaseLayer
{
public:
	TaskItemLayer();
	~TaskItemLayer();
	static TaskItemLayer *create(Task task);
	virtual bool init(Task task);

	void TouchEvent(CCObject *obj, TouchEventType type);
private:
	Task m_task;
private:

};












class TaskLayer : public BaseLayer
{
public:
	TaskLayer();
	~TaskLayer();
	CREATE_FUNC(TaskLayer);
    virtual bool init();
	
	void TouchEvent(CCObject *obj, TouchEventType type);
	void AddTaskItems(int index);
private:
	ui::ScrollView *m_ScrollView[4];
	Layout *m_sbg[4];
	Button *m_btns[4];
	TextBMFont *m_btntext[4];
private:
	
};

#endif 