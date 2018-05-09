
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
	void setMyPosition(int pos);
	int getMyPosition(){
		return m_minepos;
	}

	bool isEnd(){
		return m_isend;
	}
	void setEnd(bool isend){
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
	
private:
	void PopCard(bool isfront);
};

#endif 
