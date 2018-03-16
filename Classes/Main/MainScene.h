#ifndef __MainScene_SCENE_H__
#define __MainScene_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Adaptation.h"
#include "MainLayer.h"

class MainScene : public CCScene
{
public:
	MainScene();
	~MainScene();
    virtual bool init();
	CREATE_FUNC(MainScene);
	
private:
	MainLayer *m_pMainLayer;
};

#endif // __MainScene_SCENE_H__
