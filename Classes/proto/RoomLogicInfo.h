
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

	void HandSSelectZhuang(ccEvent *event);

	void HandSZhuangCard(ccEvent *event);

	void HandSCard(ccEvent *event);

	void SendCDiscard(int card);
	void HandSDiscard(ccEvent *event);

	void HandSDraw(ccEvent *event);

	void HandSOtherDraw(ccEvent *event);

	void SendChi(string chi);
	void HandSChi(ccEvent *event);

	void SendCPeng(int card);
	void HandSPeng(ccEvent *event);

	void SendCMingGang(int card,int type);
	void HandSMingGang(ccEvent *event);

	void SendCAnGang(int card, int type);
	void HandSAnGang(ccEvent *event);

	void HandSFa(ccEvent *event);

	void SendCHu();
	void HandSHu(ccEvent *event);

	void HandSGameover(ccEvent *event);

	void HandSRoundOver(ccEvent *event);

	void HandSDissolveTip(ccEvent *event);
private:
	static RoomLogicInfo *m_shareRoomLogicInfo;
	
};

#endif 
