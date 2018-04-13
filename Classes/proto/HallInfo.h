
#ifndef __HallInfo__
#define __HallInfo__

#include "AppMacros.h"
#include "ccEvent.h"


class HallInfo:public Object
{
public:
	HallInfo();
	~HallInfo();
	static HallInfo* getIns();
	bool init();
public:
	//rank
	void SendCRank(int type,int index);
	void HandlerSRankHand(ccEvent *event);

	//shop
	void SendCShop(int type);
	void HandlerSShop(ccEvent *event);

	//mail
	void SendCMail();
	void HandlerSMail(ccEvent *event);

	void SendCMailAward(int eid);
	void HandlerSMailAward(ccEvent *event);

	//friend
	void SendCFriend();
	void HandlerSFriend(ccEvent *event);

	void SendCFindFriend(string uid,int type);
	void HandlerSFindFriend(ccEvent *event);

	void SendCGiveFriend(string uid);
	void HandlerSGiveFriend(ccEvent *event);

	void SendCAddFriend(string uid);
	void HandlerSAddFriend(ccEvent *event);

	void SendCAddFriendList();
	void HandlerSAddFriendList(ccEvent *event);

	void SendCAgreeFriend(string uid, bool agree);
	void HandlerSAgreeFriend(ccEvent *event);

	//active
	void SendCActive(int type);
	void HandlerSActive(ccEvent *event);

	//task
	void SendCTask();
	void HandlerSTask(ccEvent *event);

	///////////exchange
	void SendCReward(int id);
	void HandlerSReward(ccEvent *event);

	void SendCExchangeReward();
	void HandlerSExchangeReward(ccEvent *event);

	void SendCExchangeCode(string excode,string yzcode);
	void HandlerSExchangeCode(ccEvent *event);

	void SendCExchangeRecord();
	void HandlerSExchangeRecord(ccEvent *event);

	void SendCExchange(int id);
	void HandlerSExchange(ccEvent *event);

	//////////pay
	void SendCApplePay(int id, string receipt);
	void HandlerSApplePay(ccEvent *event);

	void SendCWxpayOrder(int id,string body);
	void HandlerSWxpayOrder(ccEvent *event);

	void SendCWxpayQuery(string transid);
	void HandlerSWxpayQuery(ccEvent *event);

	void SendCFirstBuy(int type);
	void HandlerSFirstBuy(ccEvent *event);

	//feedback
	void SendCFeedBack(string uid,string uname,string content);
	void HandlerSFeedBack(ccEvent *event);

	//sign
	void SendCSign();
	void HandlerSSign(ccEvent *event);

	void SendCSignList();
	void HandlerSSignList(ccEvent *event);

	map<int, Rank> getSRank(int type);
	void eraseRank(int type,int lv);

	SShop getSShop(int type);
	SMail getSMail(){
		return m_pSMail;
	}
	SFindFriend getSFindFriend(){
		return m_pSFindFriend;
	}
	SFriend getSFriend(){
		return m_pSFriend;
	}
	SAddFriendList getSAddFriendList(){
		return m_pSAddFriendList;
	}
	STask getSTask(){
		return m_pSTask;
	}
	SExchangeReward getSExchangeReward(){
		return m_pSExchangeReward;
	}
	SExchangeRecord getSExchangeRecord(){
		return m_pSExchangeRecord;
	}
	SSignList getSSignList(){
		return m_pSSignList;
	}
	SSign getSSign(){
		return m_pSSign;
	}
private:
	static HallInfo *m_shareHallInfo;
	map<int, map<int,Rank>> m_pSRanks;
	map<int, SShop>m_pSShops;
	SActive m_pSActive;
	SMail m_pSMail;
	SFindFriend m_pSFindFriend;
	SFriend m_pSFriend;
	SAddFriendList m_pSAddFriendList;
	STask m_pSTask;
	SExchangeReward m_pSExchangeReward;
	SExchangeRecord m_pSExchangeRecord;
	SSignList m_pSSignList;
	SSign m_pSSign;
};

#endif 
