#ifndef __ShopLayer_SCENE_H__
#define __ShopLayer_SCENE_H__

#include "AppMacros.h"
#include "BaseLayer.h"
using namespace cocos2d;
using namespace ui;
using namespace std;



class ShopItemLayer : public BaseLayer
{
public:
	ShopItemLayer();
	~ShopItemLayer();
	static ShopItemLayer *create(ShopItem item);
	virtual bool init(ShopItem item);

	void TouchEvent(CCObject *obj, TouchEventType type);
private:
	ShopItem m_item;
private:

};











class ShopLayer : public BaseLayer
{
public:
	ShopLayer();
	~ShopLayer();
	CREATE_FUNC(ShopLayer);
    virtual bool init();
	
	void TouchEvent(CCObject *obj, TouchEventType type);
	void SelectItem(int index);

	void addShopItem(int index);
private:
	Button *m_btns[2];
	TextBMFont *m_btntext[2];
	ui::ScrollView *m_ScrollView;
	Layout *m_sbg;
	ui::ScrollView *m_ScrollView1;
	Layout *m_sbg1;
private:
	
};

#endif 