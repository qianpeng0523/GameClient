#ifndef __LoginScene_SCENE_H__
#define __LoginScene_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "LoginMainLayer.h"

using namespace cocos2d;
using namespace ui;
using namespace std;


class LoginScene : public CCScene
{
public:
	LoginScene();
	~LoginScene();
    virtual bool init();
	CREATE_FUNC(LoginScene);
	
private:
	LoginMainLayer *m_pLoginMainLayer;
};

#endif // __LoginScene_SCENE_H__
