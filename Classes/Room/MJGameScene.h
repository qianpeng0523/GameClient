#ifndef __MJGameScene_SCENE_H__
#define __MJGameScene_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Adaptation.h"
#include "MJGameLayer.h"
#include "GameUI.h"
#include "GameHead.h"
#include "MJHand.h"
#include "MJHu.h"
#include "MJCPH.h"
#include "MJChu.h"
#include "MJWall.h"
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
	MJHand *m_pMJHand[4];
	MJHu *m_pMJHu[4];
	MJCPH *m_pMJCPH[4];
	MJChu *m_pMJChu[4];
	MJWall *m_pMJWall[4];
};

#endif // __MJGameScene_SCENE_H__
