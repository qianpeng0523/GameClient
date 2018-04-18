#ifndef __MJGameScene_SCENE_H__
#define __MJGameScene_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Adaptation.h"
#include "MJGameLayer.h"
#include "GameUI.h"
#include "GameHead.h"

class MJGameScene : public CCScene
{
public:
	MJGameScene();
	~MJGameScene();
    virtual bool init();
	CREATE_FUNC(MJGameScene);
	
private:
	MJGameLayer *m_pMJGameLayer;
	GameUI *m_pGameUI;
	GameHead *m_pGameHead;
};

#endif // __MJGameScene_SCENE_H__
