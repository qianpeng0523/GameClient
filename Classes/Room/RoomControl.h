
#ifndef __RoomControl__
#define __RoomControl__

#include "cocos2d.h"
#include "tinyxml2/tinyxml2.h"
#include "LoginInfo.h"
USING_NS_CC;
using namespace std;
using namespace tinyxml2;

struct MJWallData
{
	MJWallData():
	_dirindex(0),
	_index(0)
	{

	}
	int _dirindex;
	int _index;
};

class RoomControl:public Object
{
public:
	RoomControl();
	~RoomControl();
	static RoomControl* shareRoomControl();
	bool init();
	
	void cutCard(int mindice, int maxdice);
	void reset();
	void setZhuang(int zhuang);
	
	void getWallData(bool isfront);
	void PushRoomUser(RoomUser user);
	void setMyPosition(int pos);

	bool isEnd(){
		return m_isend;
	}
	bool setEnd(bool isend){
		m_isend = isend;
	}
private:
	static RoomControl *m_shareRoomControl;
	MJWallData m_frontdata;
	MJWallData m_backdata;
	int m_frontindex;
	int m_backindex;
	
	int m_zhuangpos;
	int m_zhuangindex;
	bool m_isend;
	int m_minepos;
	map<string, RoomUser>m_roomusers;
private:
	void PopCard(bool isfront);
};

#endif 
