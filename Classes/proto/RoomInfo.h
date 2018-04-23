
#ifndef __RoomInfo__
#define __RoomInfo__

#include "AppMacros.h"
#include "ccEvent.h"

class RoomInfo:public Ref
{
public:
	RoomInfo();
	~RoomInfo();
	static RoomInfo* getIns();
	bool init();
public:
	void SendCHMMJCreateRoom(CHMMJCreateRoom cl);
	void HandlerSHMMJCreateRoom(ccEvent *event);

	void SendCHMMJEnterRoom(int rtype,string rid);
	void HandSHMMJEnterRoom(ccEvent *event);

	void HandSComein(ccEvent *event);

	void SendCBegin(int rtype);
	void HandSBegin(ccEvent *event);

	void SendCReady(bool isready);
	void HandSReady(ccEvent *event);

	void SendCLeave();
	void HandSLeave(ccEvent *event);

	void SendCLine(bool online);
	void HandSLine(ccEvent *event);

	void SendCDissolveRoom(string rid);
	void HandSDissolveRoom(ccEvent *event);

	void SendCVote(bool agree);
	void HandSVote(ccEvent *event);

	void HandSVoteResult(ccEvent *event);

	void SendCRChat(string content);
	void HandSRChat(ccEvent *event);
private:
	static RoomInfo *m_shareRoomInfo;
	
};

#endif 
