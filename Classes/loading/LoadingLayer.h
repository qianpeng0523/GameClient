#ifndef __LoadingLayer_SCENE_H__
#define __LoadingLayer_SCENE_H__

#include "AppMacros.h"
#include "BaseLayer.h"
using namespace cocos2d;
using namespace ui;
using namespace std;

class LoadingLayer : public BaseLayer
{
public:
	LoadingLayer();
	~LoadingLayer();
	static LoadingLayer *create(int type);
	virtual bool init(int type);
	
	static Scene *createScene(int type);
	void update(float dt);
	void openUpdate(bool isopen);
	void CallBack();
	void replaceScene();
private:
	int m_type;
	bool m_isupdate;
	CCParticleSystem* m_pParticleSystem;
private:
	
};

#endif 