#ifndef __MJCPH_SCENE_H__
#define __MJCPH_SCENE_H__

#include "AppMacros.h"
#include "BaseLayer.h"
using namespace cocos2d;
using namespace ui;
using namespace std;




class MJCPH : public BaseLayer
{
public:
	MJCPH();
	~MJCPH();
	static MJCPH* create(int pos);
	virtual bool init(int pos);
	
	void TouchEvent(CCObject *obj, TouchEventType type);
	
	void resetCards();
	void setValue(int index, CPGCardData data);
	void setValue(int index,int zindex,int card, bool bei,bool isv);
private:
	int m_position;
	int m_index;
	ImageView *m_cardbgs[4][4];
	ImageView *m_cardimgs[4][4];
	int m_cards[4][4];
	string m_json;
private:
	static string g_beistr[4][16];
	static string g_paistr[4][16];
};

#endif 