
#ifndef __RoomInfo__
#define __RoomInfo__

#include "AppMacros.h"
#include "ccEvent.h"

class RoomInfo :public Ref
{
public:
	RoomInfo();
	~RoomInfo();
	static RoomInfo* getIns();
	bool init();
public:
	void SendCHMMJCreateRoom(CHMMJCreateRoom cl);
	void HandlerSHMMJCreateRoom(ccEvent *event);

	void SendCHMMJEnterRoom(int rtype, string rid);
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

	void eraseRoomUser(string uid);
	void clearRoomUser();
	void PushRoomUser(RoomUser user);
	RoomData getRoomData(){
		return m_pRoomData;
	}
	void PushAllRoomUser();
	RoomUser getRoomInfo(string uid);
	map<string, RoomUser> getRoomUsers(){
		return m_pRoomUsers;
	}
	bool isBegin(){
		return m_isbegin;
	}
	void setBegin(bool isb){
		m_isbegin = isb;
	}
	SDissolveRoom getSDissolveRoom(){
		return m_pSDissolveRoom;
	}
	map<string, SVote> getSVotes(){
		return m_pvotes;
	}

	void disTime(float dt);
	void openDiaTime(bool isopen);
	int getTime(){
		return m_time;
	}
private:
	static RoomInfo *m_shareRoomInfo;
	SHMMJEnterRoom m_pSHMMJEnterRoom;
	RoomData m_pRoomData;
	map<string, RoomUser>m_pRoomUsers;
	bool m_isbegin;
	SDissolveRoom m_pSDissolveRoom;
	map<string,SVote> m_pvotes;
	int m_time;
	bool m_disopen;
};

#endif 
