#ifndef __MayaAction_H__
#define __MayaAction_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "ActionConfig.h"
#include "AppMacros.h"
#include "BaseLayer.h"

USING_NS_CC;

class MayaAction:public Object{
public:
	MayaAction();
	~MayaAction();
	static MayaAction *getIns();
	virtual bool init();

	void initLoad(int scenetype);

	void Play(Node *node, string key);
	void Play(Node *node,string key,CCCallFuncND *selector);
	void Play(ImageView *node, string key);
	void Play(ImageView *node, string key, CCCallFuncND *selector);
	void update(float dt);
protected:
	CCAnimate* preloadAction(string key);
	CCAnimate* preloadAction(ActionItem *p);
private:
	static MayaAction *m_ins;
	vector<ActionItem *>m_curact;
	SpriteFrameCache *m_SpriteFrameCache;
	bool m_lock;
	Dictionary *m_dict;
};

#endif