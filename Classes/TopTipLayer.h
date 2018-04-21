#ifndef __TopTipLayer_SCENE_H__
#define __TopTipLayer_SCENE_H__

#include "AppMacros.h"
#include "BaseLayer.h"
using namespace cocos2d;
using namespace ui;
using namespace std;




class TopTipLayer : public BaseLayer
{
public:
	TopTipLayer();
	~TopTipLayer();
	CREATE_FUNC(TopTipLayer);
    virtual bool init();
	
	void setContent(string tip);
	void PushTip(string tip);
	void CallBack();
	void CallBack(Node *node);
private:
	bool m_lock;
	ImageView *m_bg;
private:
	vector<string >m_tips;
};

#endif 