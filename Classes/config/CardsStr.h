#ifndef __CARDSTR_SCENE_H__
#define __CARDSTR_SCENE_H__

#include "AppMacros.h"
#include "BaseLayer.h"
using namespace cocos2d;
using namespace ui;
using namespace std;


class CardStr{
public:
	static string g_cardswan[9];
	static string g_cardstiao[9];
	static string g_cardstong[9];
	static string g_cardsfeng[7];
	static int g_cards[34];

	static string getCardStr(int card);
};




#endif 