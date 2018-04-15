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

	void SelectCheckBox(int type,int index);
private:
	Button *m_btns[2];
	Layout *m_bg[2];
	TextBMFont *m_btntext[2];

	CheckBox *m_typeboxs[2];
	CheckBox *m_anteboxs[4];
	CheckBox *m_timeboxs[2];
	CheckBox *m_baoboxs[3];
	CheckBox *m_bangboxs[5];
	ui::EditBox *m_input[2];
private:
	int m_type;
	int m_ante;
	int m_time;
	int m_bao;
	int m_bang;
};

#endif 