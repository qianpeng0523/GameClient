#ifndef __GameChatLayer_SCENE_H__
#define __GameChatLayer_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Adaptation.h"
#include "XXEventDispatcher.h"
#include "XXHttpRequest.h"
#include "BaseLayer.h"
#include "ChatRecord.h"

using namespace cocos2d;
using namespace ui;
using namespace std;
#define MAXCHATCOUNT 50

class GameChatLayer : public BaseLayer
{
public:
	GameChatLayer();
	~GameChatLayer();
	CREATE_FUNC(GameChatLayer);
    virtual bool init();
	
	void TouchEvent(Object *obj, TouchEventType type);
	static GameChatLayer *open();

	void AddYuYin();
	void AddEmotion();
	void AddRecord();
	void PushRecord(ChatRD *p);
	void ShowYuYin();
	void ShowEmotion();
	void ShowRecord();
	bool isYuYin();
	void close();
	
	void CallBack(CCNode *node);
	void openUI();
	void closeUI();
private:
	
	ui::ScrollView *m_ScrollView1;
	ui::ScrollView *m_ScrollView2;
	ui::ScrollView *m_ScrollView3;
	Layout *m_sbg1;
	Layout *m_sbg2;
	Layout *m_sbg3;
	Button *m_btn1;
	Button *m_btn2;
	Button *m_btn3;
	ImageView *m_imgicon[3];
	ui::EditBox *m_pCursorTextField;
private:
	
};

#endif 