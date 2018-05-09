#ifndef __GameHead_SCENE_H__
#define __GameHead_SCENE_H__

#include "AppMacros.h"
#include "BaseLayer.h"
using namespace cocos2d;
using namespace ui;
using namespace std;




class GameHead : public BaseLayer
{
public:
	GameHead();
	~GameHead();
	CREATE_FUNC(GameHead);
    virtual bool init();
	
	void TouchEvent(CCObject *obj, TouchEventType type);
	
	void PushRoomUser(RoomUser ru);
	void PopRoomUser(string uid);
	void PopRoomUser(int pos);

	void onLine(int pos);
	void onLine(string uid);
	void offLine(int pos);
	void offLine(string uid);

	void setZhuang(int pos,bool iszhuang);
	void setZhuang(string uid, bool iszhuang);

	void setName(int pos,string name);
	void setName(string uid,string name);

	void setScore(int pos,int score);
	void setScore(string uid,int score);

	void setWin(int pos,int win);
	void setWinVisible(int pos, bool isv);

	void setTip(int pos, string uid, int time);
	void setTip(string uid, int time);
	
	void setTipVisible(int pos,bool isv);

	void reset();

	void ShowReady(int pos,bool isr);

	static int changePos(int pos);
	static void setGray(ImageView *img);
	static void removeGray(ImageView *img);
	static int getPos(string uid);
	static int getPosition1(string uid);
private:
	static RoomUser *m_users[4];
	ImageView *m_heads[4];
	ImageView *m_headbgs[4];
	TextBMFont *m_texts[4];
	ImageView *m_zhuangs[4];
	Text *m_names[4];
	TextBMFont *m_scores[4];
	RoomData m_pRoomData;
	ImageView *m_readyimgs[4];
public:
	
};

#endif 