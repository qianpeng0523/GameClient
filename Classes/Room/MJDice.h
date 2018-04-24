#ifndef __MJDice_SCENE_H__
#define __MJDice_SCENE_H__

#include "AppMacros.h"
#include "BaseLayer.h"
using namespace cocos2d;
using namespace ui;
using namespace std;




class MJDice : public BaseLayer
{
public:
	MJDice();
	~MJDice();
	static MJDice* create();
	virtual bool init();
	
	void TouchEvent(CCObject *obj, TouchEventType type);
	
	void test();

	void resetCard();
	void startDice(int *dice);
	void ShowResult(Node *node, void *data);
private:
	int m_dice[2];
	ImageView *m_diceimg;
	ImageView *m_dices[2];
};

#endif 