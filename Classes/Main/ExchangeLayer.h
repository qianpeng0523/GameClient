#ifndef __ExchangeLayer_SCENE_H__
#define __ExchangeLayer_SCENE_H__

#include "AppMacros.h"
#include "BaseLayer.h"
using namespace cocos2d;
using namespace ui;
using namespace std;



class ExchangeItemLayer : public BaseLayer
{
public:
	ExchangeItemLayer();
	~ExchangeItemLayer();
	static ExchangeItemLayer *create(Rank hall);
	virtual bool init(Rank hall);

	void TouchEvent();
private:
	Rank m_hall;
private:

};


class ExchangeRecordItemLayer : public BaseLayer
{
public:
	ExchangeRecordItemLayer();
	~ExchangeRecordItemLayer();
	static ExchangeRecordItemLayer *create(Rank hall);
	virtual bool init(Rank hall);

	void TouchEvent();
private:
	Rank m_hall;
private:

};









class ExchangeLayer : public BaseLayer
{
public:
	ExchangeLayer();
	~ExchangeLayer();
	CREATE_FUNC(ExchangeLayer);
    virtual bool init();
	
	void TouchEvent(CCObject *obj, TouchEventType type);
	void AddExchangeItems();
	void SelectItem(int index);
	void AddRecords();
private:
	ui::ScrollView *m_ScrollView1;
	Layout *m_sbg1;
	Layout *m_sbg2;
	ui::ScrollView *m_ScrollView3;
	Layout *m_sbg3;
	Button *m_btns[3];
	TextBMFont *m_btntext[3];
	Layout *m_top;
	ui::EditBox *m_input;
private:
	
};

#endif 