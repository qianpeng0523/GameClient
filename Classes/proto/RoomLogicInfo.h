
#ifndef __RoomLogicInfo__
#define __RoomLogicInfo__

#include "AppMacros.h"
#include "ccEvent.h"

class RoomLogicInfo:public Ref
{
public:
	RoomLogicInfo();
	~RoomLogicInfo();
	static RoomLogicInfo* getIns();
	bool init();
public:
	void SendCDice();
	void HandlerSDice(ccEvent *event);

private:
	static RoomLogicInfo *m_shareRoomLogicInfo;
	
};

#endif 
