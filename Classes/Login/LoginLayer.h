#ifndef __LoginLayer_SCENE_H__
#define __LoginLayer_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Adaptation.h"
#include "string.h"
#include "BaseLayer.h"

using namespace cocos2d;
using namespace ui;
using namespace std;

class LoginLayer : public BaseLayer
{
public:
	LoginLayer();
	~LoginLayer();
	CREATE_FUNC(LoginLayer);
    virtual bool init();
	void TouchEvent(Object *obj, TouchEventType type);

	static string m_uid;
	static string m_pwd;
	static string m_pwdmd5;
private:
	ui::EditBox *m_input1;
	ui::EditBox *m_input2;
	
};

#endif // __LoginLayer_SCENE_H__
