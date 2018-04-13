#ifndef __Adaptation_SCENE_H__
#define __Adaptation_SCENE_H__
#include "cocos2d.h"
#include "cocos-ext.h"
#include "AppMacros.h"
#include "cocos/ui/UILayout.h"
#include "cocos/ui/UIImageView.h"
#include "cocos/ui/UIButton.h"
#include "cocos/ui/UIScrollView.h"
#include "cocos/ui/UIPageView.h"
#include "cocos/ui/UITextAtlas.h"
#include "cocos/ui/UICheckBox.h"
#include "cocos/ui/UISlider.h"
#include "cocos/ui/UILoadingBar.h"
#include "cocos/ui/UITextBMFont.h"
#include "cocostudio/CCSGUIReader.h"
#include "cocos/ui/UIHelper.h"
#include "cocos/ui/UIText.h"
#include "SimpleAudioEngine.h"





using namespace cocos2d;
using namespace ui;
using namespace extension;
using namespace std;
using namespace cocostudio;

enum POSTYPE
{
	LEFT_TOP=0,
	LEFT_BOTTOM,
	RIGHT_TOP,
	RIGHT_BOTTOM
};

class Adaptation : public Ref{
public:
	Adaptation();
	~Adaptation();
	static Adaptation* shareAdaptation();
	void removeAdaptation();
    virtual bool init();
public:
	float getScaleFactor()//获取缩放因子
	{
		return m_scaleFactor;
	}
	Size getDesignSize(){//设计大小
		return m_designResolutionSize;
	}
	Size getScreenSize(){//屏幕大小
		return m_screensize;
	}
	Size getAddSize(){
		return m_AddSize;
	}

private:
	
	void ScreenAdaptationInit();//屏幕适配初始化
	
private:
	static Adaptation* m_pShareAdaptation;
	float m_scaleFactor;
	Size m_designResolutionSize;
	Size m_screensize;
	Size m_AddSize;

};

#endif // __Adaptation_SCENE_H__
