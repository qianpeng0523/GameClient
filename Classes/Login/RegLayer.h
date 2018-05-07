#ifndef __RegLayer_SCENE_H__
#define __RegLayer_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Adaptation.h"
#include "string.h"
#include "BaseLayer.h"
using namespace cocos2d;
using namespace ui;
using namespace std;

class RegLayer : public BaseLayer
{
public:
	RegLayer();
	~RegLayer();
	CREATE_FUNC(RegLayer);
    virtual bool init();
	void TouchEvent(Object *obj, TouchEventType type);
	
	static string m_uname;
	static string m_pwd;
	static string m_pwdmd5;
private:
	ui::EditBox *m_input1;
	ui::EditBox *m_input2;
	
};

#endif // __RegLayer_SCENE_H__
