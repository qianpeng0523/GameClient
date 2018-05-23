#include "HallInfo.h"
#include "ClientSocket.h"
#include "XXEventDispatcher.h"
#include "XXIconv.h"
#include "MainScene.h"
#include "GameControl.h"
#include "GameDataSet.h"
#include "LoginInfo.h"
#include "YMSocketData.h"
#include "XXHttpRequest.h"
#include "YLJni.h"

HallInfo *HallInfo::m_shareHallInfo=NULL;
HallInfo::HallInfo()
{
	XXEventDispatcher *pe = XXEventDispatcher::getIns();
	SRank sl1;
	pe->registerProto(sl1.cmd(), sl1.GetTypeName());
	SShop sr2;
	pe->registerProto(sr2.cmd(), sr2.GetTypeName());
	SMail sl3;
	pe->registerProto(sl3.cmd(), sl3.GetTypeName());
	pe->addListener(sl3.cmd(), this, Event_Handler(HallInfo::HandlerSMail));
	SFriend sr4;
	pe->registerProto(sr4.cmd(), sr4.GetTypeName());
	SFindFriend sl5;
	pe->registerProto(sl5.cmd(), sl5.GetTypeName());
	SGiveFriend sr6;
	pe->registerProto(sr6.cmd(), sr6.GetTypeName());
	SAddFriend sl7;
	pe->registerProto(sl7.cmd(), sl7.GetTypeName());
	pe->addListener(sl7.cmd(), this, Event_Handler(HallInfo::HandlerSAddFriend));
	SAddFriendList sr8;
	pe->registerProto(sr8.cmd(), sr8.GetTypeName());
	SActive sl9;
	pe->registerProto(sl9.cmd(), sl9.GetTypeName());
	STask sl10;
	pe->registerProto(sl10.cmd(), sl10.GetTypeName());
	SReward sl11;
	pe->registerProto(sl11.cmd(), sl11.GetTypeName());
	SAgreeFriend sl12;
	pe->registerProto(sl12.cmd(), sl12.GetTypeName());
	SExchangeReward sl13;
	pe->registerProto(sl13.cmd(), sl13.GetTypeName());
	SExchangeCode sl14;
	pe->registerProto(sl14.cmd(), sl14.GetTypeName());
	SExchangeRecord sl15;
	pe->registerProto(sl15.cmd(), sl15.GetTypeName());
	pe->addListener(sl15.cmd(), this, Event_Handler(HallInfo::HandlerSExchangeRecord));
	SApplePay sl17;
	pe->registerProto(sl17.cmd(), sl17.GetTypeName());
	SWxpayOrder sl18;
	pe->registerProto(sl18.cmd(), sl18.GetTypeName());
	SWxpayQuery sl19;
	pe->registerProto(sl19.cmd(), sl19.GetTypeName());
	SFirstBuy sl20;
	pe->registerProto(sl20.cmd(), sl20.GetTypeName());
	SFeedBack sl21;
	pe->registerProto(sl21.cmd(), sl21.GetTypeName());
	SSign sl22;
	pe->registerProto(sl22.cmd(), sl22.GetTypeName());
	SSignList sl23;
	pe->registerProto(sl23.cmd(), sl23.GetTypeName());
	SAliPayOrder sl24;
	pe->registerProto(sl24.cmd(), sl24.GetTypeName());

	SAliPayResult sl25;
	pe->registerProto(sl25.cmd(), sl25.GetTypeName());
	SMailAward sl26;
	pe->registerProto(sl26.cmd(), sl26.GetTypeName());

	SFirsyBuyData sl27;
	pe->registerProto(sl27.cmd(), sl27.GetTypeName());

	SExchange sl28;
	pe->registerProto(sl28.cmd(), sl28.GetTypeName());


}

HallInfo::~HallInfo(){
	
}

HallInfo* HallInfo::getIns(){
	if (!m_shareHallInfo){
		m_shareHallInfo = new HallInfo();
		m_shareHallInfo->init();
	}
	return m_shareHallInfo;
}

bool HallInfo::init()
{
	
    return true;
}


void HallInfo::SendCRank(int type, int index){
	CRank cl;
	cl.set_cmd(cl.cmd());
	cl.set_type(type);
	cl.set_index(index);
	XXEventDispatcher::getIns()->addListener(cl.cmd(), this, Event_Handler(HallInfo::HandlerSRankHand));
	ClientSocket::getIns()->sendMsg(cl.cmd(), &cl);

}

void HallInfo::HandlerSRankHand(ccEvent *event){
	SRank cl;

	cl.CopyFrom(*event->msg);
	XXEventDispatcher::getIns()->removeListener(cl.cmd(), this, Event_Handler(HallInfo::HandlerSRankHand));
	int err = cl.err();
	if (err == 0){
		log("%s", XXIconv::GBK2UTF("获取排行成功").c_str());
		int type = cl.type();
		for (int i = 0; i < cl.list_size(); i++){
			Rank rr = cl.list(i);
			map<int, Rank> list;
			if (m_pSRanks.find(type) == m_pSRanks.end()){
				list.insert(make_pair(rr.lv(),rr));
				m_pSRanks.insert(make_pair(type, list));
			}
			else{
				list = m_pSRanks.at(type);
				list.insert(make_pair(rr.lv(), rr));
				m_pSRanks.at(type) = list;
			}
		}
		MainLayer *layer = GameControl::getIns()->getMainLayer();
		if (layer){
			layer->AddFriends(type);
		}
	}
	else{
		log("%s", XXIconv::GBK2UTF("获取排行失败").c_str());
	}
}

map<int, Rank> HallInfo::getSRank(int type){
	map<int, Rank> sr;
	if (m_pSRanks.find(type) == m_pSRanks.end()){
		return sr;
	}
	else{
		return m_pSRanks.at(type);
	}
}

void HallInfo::eraseRank(int type, int lv){
	if (m_pSRanks.find(type) != m_pSRanks.end()){
		map<int, Rank> sr=m_pSRanks.at(type);
		if (sr.find(lv) != sr.end()){
			sr.erase(sr.find(lv));
			m_pSRanks.at(type) = sr;
		}
	}
}

void HallInfo::SendCShop(int type){
	CShop cl;
	cl.set_cmd(cl.cmd());
	cl.set_type(type);
	XXEventDispatcher::getIns()->addListener(cl.cmd(), this, Event_Handler(HallInfo::HandlerSShop));
	ClientSocket::getIns()->sendMsg(cl.cmd(), &cl);
}

void HallInfo::HandlerSShop(ccEvent *event){
	SShop cl;
	cl.CopyFrom(*event->msg);
	XXEventDispatcher::getIns()->removeListener(cl.cmd(), this, Event_Handler(HallInfo::HandlerSShop));
	int err = cl.err();
	if (err == 0){
		int type = cl.type();
		if (m_pSShops.find(type) != m_pSShops.end()){
			m_pSShops.at(type) = cl;
		}
		else{
			m_pSShops.insert(make_pair(type,cl));
		}
		ShopLayer *p = GameControl::getIns()->getShopLayer();
		if (p){
			if (type == 1){
				p->addShopItem(1);
			}
			else if (type == 3){
				p->addShopItem(0);
			}
		}
	}
	else{
		log("%s",XXIconv::GBK2UTF("获取商城列表失败").c_str());
	}
}

SShop HallInfo::getSShop(int type){
	if (m_pSShops.find(type) != m_pSShops.end()){
		return m_pSShops.at(type);
	}
	SShop ss;
	return ss;
}

void HallInfo::SendCMail(){
	CMail cl;
	cl.set_cmd(cl.cmd());
	//XXEventDispatcher::getIns()->addListener(cl.cmd(), this, Event_Handler(HallInfo::HandlerSMail));
	ClientSocket::getIns()->sendMsg(cl.cmd(), &cl);
}

void HallInfo::HandlerSMail(ccEvent *event){
	SMail cl;
	cl.CopyFrom(*event->msg);
	//XXEventDispatcher::getIns()->removeListener(cl.cmd(), this, Event_Handler(HallInfo::HandlerSMail));
	int err = cl.err();
	if (err == 0){
		m_pSMail = cl;
		MailLayer *p = GameControl::getIns()->getMailLayer();
		if (p){
			p->AddMailItems();
		}
	}
	else{
		log("%s", XXIconv::GBK2UTF("获取邮箱列表失败").c_str());
	}
}


void HallInfo::SendCMailAward(int eid){
	CMailAward cl;
	cl.set_cmd(cl.cmd());
	cl.set_id(eid);
	XXEventDispatcher::getIns()->addListener(cl.cmd(), this, Event_Handler(HallInfo::HandlerSMailAward));
	ClientSocket::getIns()->sendMsg(cl.cmd(), &cl);
}

void HallInfo::HandlerSMailAward(ccEvent *event){
	SMailAward cl;
	cl.CopyFrom(*event->msg);
	XXEventDispatcher::getIns()->removeListener(cl.cmd(), this, Event_Handler(HallInfo::HandlerSMailAward));
	int err = cl.err();
	if (err == 0){
		MailTipLayer *p = GameControl::getIns()->getMailTipLayer();
		if (p){
			p->removeFromParentAndCleanup(true);
		}
		int id = cl.id();
		auto vec = m_pSMail.mutable_list();
		for (int i = 0; i < vec->size(); i++){
			Mail p = vec->Get(i);
			if (p.eid() == id){
				vec->DeleteSubrange(i,1);
				//查找到了  然后提示奖励界面
				MailLayer *ml = GameControl::getIns()->getMailLayer();
				if (ml){
					ml->AddMailItems();
				}
				RewardTipLayer *pp = GameControl::getIns()->getRewardTipLayer();
				if (!pp){
					vector<Reward > vecs;
					for (int j = 0; j < p.rewardlist_size(); j++){
						vecs.push_back(p.rewardlist(j));
					}
					pp = RewardTipLayer::create(vecs);
					Director::sharedDirector()->getRunningScene()->addChild(pp,10);
				}

				break;
			}
		}
	}
}

void HallInfo::SendCFriend(){
	CFriend cl;
	cl.set_cmd(cl.cmd());
	XXEventDispatcher::getIns()->addListener(cl.cmd(), this, Event_Handler(HallInfo::HandlerSFriend));
	ClientSocket::getIns()->sendMsg(cl.cmd(), &cl);

	//test
	SFriend sf;
	for (int i = 0; i < 4;i++){
		Friend *fri=sf.add_list();
		fri->set_acttype(i%3+1);
		fri->set_time(GameDataSet::getTime());
		char buff[100];
		UserBase *user = fri->mutable_info();
		sprintf(buff, "10000%d", i);
		user->set_userid(buff);
		user->set_picurl("http://www.lesharecs.com/1.jpg");
		user->set_username(buff);
	}
	int sz = sf.ByteSize();
	char *buffer = new char[sz];
	sf.SerializePartialToArray(buffer, sz);
	ccEvent *ev = new ccEvent(sf.cmd(),buffer,sz);
	HandlerSFriend(ev);
}

void HallInfo::HandlerSFriend(ccEvent *event){
	SFriend cl;
	cl.CopyFrom(*event->msg);
	XXEventDispatcher::getIns()->removeListener(cl.cmd(), this, Event_Handler(HallInfo::HandlerSFriend));
	int err = cl.err();
	if (err == 0){
		m_pSFriend = cl;
		FriendLayer *p = GameControl::getIns()->getFriendLayer();
		if (p){
			p->ShowFriendEvent(1);
		}
	}
	else{
		log("%s",XXIconv::GBK2UTF("获取朋友列表失败").c_str());
	}
	GameControl::getIns()->HideLoading();
}


void HallInfo::SendCFindFriend(string uid, int type){
	CFindFriend cl;
	cl.set_cmd(cl.cmd());
	cl.set_uid(uid);
	cl.set_type(type);
	XXEventDispatcher::getIns()->addListener(cl.cmd(), this, Event_Handler(HallInfo::HandlerSFindFriend));
	ClientSocket::getIns()->sendMsg(cl.cmd(), &cl);

	//test
	char buff[100];
	SFindFriend fris;
	for (int i = 0; i < 2; i++){
		Friend *fri = fris.add_list();
		fri->set_acttype(i % 3 + 1);
		fri->set_online(i % 2);
		fri->set_time(GameDataSet::getTime());
		UserBase *user= fri->mutable_info();
		sprintf(buff, "10000%d", i);
		user->set_username(buff);
		user->set_userid(buff);
		user->set_picurl("http://www.lesharecs.com/1.jpg");
	}
	int sz = fris.ByteSize();
	char *buffer = new char[sz];
	fris.SerializePartialToArray(buffer, sz);
	ccEvent *ev = new ccEvent(fris.cmd(), buffer, sz);
	HandlerSFindFriend(ev);
}

void HallInfo::HandlerSFindFriend(ccEvent *event){
	SFindFriend cl;
	cl.CopyFrom(*event->msg);
	int type = cl.type();
	XXEventDispatcher::getIns()->removeListener(cl.cmd(), this, Event_Handler(HallInfo::HandlerSFindFriend));
	int err = cl.err();
	if (err == 0){
		m_pSFindFriend = cl;
		FriendLayer *p = GameControl::getIns()->getFriendLayer();
		if (p){
			if (cl.list_size() > 0){
				p->ShowFriendEvent(0);
			}
		}
	}
	else{
		log("%s", XXIconv::GBK2UTF("查找朋友失败").c_str());
	}
}


void HallInfo::SendCGiveFriend(string uid){
	CGiveFriend cl;
	cl.set_cmd(cl.cmd());
	cl.set_uid(uid);
	XXEventDispatcher::getIns()->addListener(cl.cmd(), this, Event_Handler(HallInfo::HandlerSGiveFriend));
	ClientSocket::getIns()->sendMsg(cl.cmd(), &cl);
}

void HallInfo::HandlerSGiveFriend(ccEvent *event){
	SFindFriend cl;
	cl.CopyFrom(*event->msg);
	XXEventDispatcher::getIns()->removeListener(cl.cmd(), this, Event_Handler(HallInfo::HandlerSGiveFriend));
	int err = cl.err();
	if (err == 0){
		log("%s", XXIconv::GBK2UTF("赠送好友金币成功").c_str());
	}
	else{
		log("%s",XXIconv::GBK2UTF("赠送好友金币失败").c_str());
	}
}


void HallInfo::SendCAddFriend(string uid){
	CAddFriend cl;
	cl.set_cmd(cl.cmd());
	cl.set_uid(uid);
	//XXEventDispatcher::getIns()->addListener(cl.cmd(), this, Event_Handler(HallInfo::HandlerSAddFriend));
	ClientSocket::getIns()->sendMsg(cl.cmd(), &cl);
}

void HallInfo::HandlerSAddFriend(ccEvent *event){
	SAddFriend cl;
	cl.CopyFrom(*event->msg);
	//XXEventDispatcher::getIns()->removeListener(cl.cmd(), this, Event_Handler(HallInfo::HandlerSAddFriend));
	int err = cl.err();
	if (err == 0){
		SendCAddFriendList();
		log("%s", XXIconv::GBK2UTF("发送好友请求成功").c_str());
	}
	else{
		log("%s", XXIconv::GBK2UTF("发送好友请求失败").c_str());
	}
}


void HallInfo::SendCAddFriendList(){
	CAddFriendList cl;
	cl.set_cmd(cl.cmd());
	XXEventDispatcher::getIns()->addListener(cl.cmd(), this, Event_Handler(HallInfo::HandlerSAddFriendList));
	ClientSocket::getIns()->sendMsg(cl.cmd(), &cl);
}

void HallInfo::HandlerSAddFriendList(ccEvent *event){
	SAddFriendList cl;
	cl.CopyFrom(*event->msg);
	XXEventDispatcher::getIns()->removeListener(cl.cmd(), this, Event_Handler(HallInfo::HandlerSAddFriendList));
	int err = cl.err();
	if (err == 0){
		m_pSAddFriendList = cl;
		FriendLayer *p = GameControl::getIns()->getFriendLayer();
		if (p){
			p->ShowFriendEvent(2);
		}
		log("%s", XXIconv::GBK2UTF("获取列表成功").c_str());
	}
	else{
		log("%s", XXIconv::GBK2UTF("获取列表失败").c_str());
	}
}


void HallInfo::SendCActive(int type){
	CActive cl;
	cl.set_cmd(cl.cmd());
	cl.set_type(type);
	XXEventDispatcher::getIns()->addListener(cl.cmd(), this, Event_Handler(HallInfo::HandlerSActive));
	ClientSocket::getIns()->sendMsg(cl.cmd(), &cl);
}

void HallInfo::HandlerSActive(ccEvent *event){
	SActive cl;
	cl.CopyFrom(*event->msg);
	XXEventDispatcher::getIns()->removeListener(cl.cmd(), this, Event_Handler(HallInfo::HandlerSActive));
	int err = cl.err();
	if (err == 0){
		m_pSActive = cl;
		ActiveLayer *p = GameControl::getIns()->getActiveLayer();
		if (p){
			p->ShowItem(1, 0);
		}
	}
	else{
		log("%s", XXIconv::GBK2UTF("获取活动列表失败").c_str());
	}
}

void HallInfo::SendCTask(){
	CTask cl;
	cl.set_cmd(cl.cmd());
	XXEventDispatcher::getIns()->addListener(cl.cmd(), this, Event_Handler(HallInfo::HandlerSTask));
	ClientSocket::getIns()->sendMsg(cl.cmd(), &cl);

	//test
	char buff[50];
	STask st;
	for (int i = 0; i < 20;i++){
		Task *ts = st.add_list();
		sprintf(buff,"%s%d",XXIconv::GBK2UTF("登录奖励").c_str(),i%4+1);
		ts->set_title(buff);
		ts->set_content(XXIconv::GBK2UTF("完成任务可获得大量金币"));
		ts->set_taskid(i + 1);
		int count = 3 * (i % 4) + 1;
		Status *st = ts->mutable_status();
		st->set_count(count);
		int fcount = 2 * (i % 3) + 1;
		st->set_fcount(fcount);
		if (count <= fcount){
			st->set_finished(i % 2 + 1);
		}
		else{
			st->set_finished(0);
		}
		ts->set_type(i / 4 + 1);

		Reward *rd = ts->add_rewardlist();
		Prop *prop = rd->mutable_prop();
		prop->set_id(1);
		prop->set_name(XXIconv::GBK2UTF("金币"));
		rd->set_number((i+1)*(i / 4+1) * 1500);
	}
	int sz = st.ByteSize();
	char *buffer = new char[sz];
	st.SerializePartialToArray(buffer, sz);
	ccEvent *ev = new ccEvent(st.cmd(), buffer, sz);
	HandlerSTask(ev);
}

void HallInfo::HandlerSTask(ccEvent *event){
	STask cl;
	cl.CopyFrom(*event->msg);
	XXEventDispatcher::getIns()->removeListener(cl.cmd(), this, Event_Handler(HallInfo::HandlerSTask));
	int err = cl.err();
	if (err == 0){
		m_pSTask = cl;
		TaskLayer *p = GameControl::getIns()->getTaskLayer();
		if (p){
			p->AddTaskItems(0);
		}
	}
	else{
		log("%s", XXIconv::GBK2UTF("获取活动列表失败").c_str());
	}
}

void HallInfo::SendCReward(int id){
	CReward cl;
	cl.set_id(id);
	XXEventDispatcher::getIns()->addListener(cl.cmd(), this, Event_Handler(HallInfo::HandlerSReward));
	ClientSocket::getIns()->sendMsg(cl.cmd(), &cl);
}

void HallInfo::HandlerSReward(ccEvent *event){
	SReward cl;
	cl.CopyFrom(*event->msg);
	XXEventDispatcher::getIns()->removeListener(cl.cmd(), this, Event_Handler(HallInfo::HandlerSReward));
	int err = cl.err();
	if (err == 0){
		log("%s", XXIconv::GBK2UTF("领取奖励成功").c_str());
	}
	else{
		log("%s", XXIconv::GBK2UTF("领取奖励失败").c_str());
	}
}

void HallInfo::SendCAgreeFriend(string uid, int nid, bool agree){
	CAgreeFriend cl;
	cl.set_cmd(cl.cmd());
	cl.set_userid(uid);
	cl.set_agree(agree);
	cl.set_nid(nid);
	XXEventDispatcher::getIns()->addListener(cl.cmd(), this, Event_Handler(HallInfo::HandlerSAgreeFriend));
	ClientSocket::getIns()->sendMsg(cl.cmd(), &cl);
}

void HallInfo::HandlerSAgreeFriend(ccEvent *event){
	SAgreeFriend cl;
	cl.CopyFrom(*event->msg);
	XXEventDispatcher::getIns()->removeListener(cl.cmd(), this, Event_Handler(HallInfo::HandlerSAgreeFriend));
	int err = cl.err();
	if (err == 0){
		log("%s", XXIconv::GBK2UTF("同意拒绝成功").c_str());
	}
	else{
		log("%s", XXIconv::GBK2UTF("同意拒绝失败").c_str());
	}
}

void HallInfo::SendCExchangeReward(){
	CExchangeReward cl;
	cl.set_cmd(cl.cmd());
	XXEventDispatcher::getIns()->addListener(cl.cmd(), this, Event_Handler(HallInfo::HandlerSExchangeReward));
	ClientSocket::getIns()->sendMsg(cl.cmd(), &cl);
}

void HallInfo::HandlerSExchangeReward(ccEvent *event){
	SExchangeReward cl;
	cl.CopyFrom(*event->msg);
	XXEventDispatcher::getIns()->removeListener(cl.cmd(), this, Event_Handler(HallInfo::HandlerSExchangeReward));
	int err = cl.err();
	if (err == 0){
		m_pSExchangeReward = cl;
		log("%s", XXIconv::GBK2UTF("获取兑换奖品成功").c_str());
		ExchangeLayer *p = GameControl::getIns()->getExchangeLayer();
		if (p){
			p->SelectItem(0);
		}
	}
	else{
		log("%s", XXIconv::GBK2UTF("获取兑换奖品失败").c_str());
	}
}

void HallInfo::SendCExchangeCode(string excode, string yzcode){
	CExchangeCode cl;
	cl.set_cmd(cl.cmd());
	cl.set_excode(excode);
	cl.set_yzcode(yzcode);
	XXEventDispatcher::getIns()->addListener(cl.cmd(), this, Event_Handler(HallInfo::HandlerSExchangeCode));
	ClientSocket::getIns()->sendMsg(cl.cmd(), &cl);
}

void HallInfo::HandlerSExchangeCode(ccEvent *event){
	SExchangeCode cl;
	cl.CopyFrom(*event->msg);
	XXEventDispatcher::getIns()->removeListener(cl.cmd(), this, Event_Handler(HallInfo::HandlerSExchangeCode));
	int err = cl.err();
	if (err == 0){
		vector<Reward >rds;
		for (int i = 0; i < cl.rd_size(); i++){
			rds.push_back(cl.rd(i));
		}
		RewardTipLayer *pp = GameControl::getIns()->getRewardTipLayer();
		if (!pp){
			pp = RewardTipLayer::create(rds);
			Director::sharedDirector()->getRunningScene()->addChild(pp, 10);
		}
		log("%s", XXIconv::GBK2UTF("兑换码兑换成功").c_str());
	}
	else{
		log("%s", XXIconv::GBK2UTF("兑换码兑换失败").c_str());
	}
}

void HallInfo::SendCExchangeRecord(){
	CExchangeRecord cl;
	cl.set_cmd(cl.cmd());
	//XXEventDispatcher::getIns()->addListener(cl.cmd(), this, Event_Handler(HallInfo::HandlerSExchangeRecord));
	ClientSocket::getIns()->sendMsg(cl.cmd(), &cl);
}

void HallInfo::HandlerSExchangeRecord(ccEvent *event){
	SExchangeRecord cl;
	cl.CopyFrom(*event->msg);
	//XXEventDispatcher::getIns()->removeListener(cl.cmd(), this, Event_Handler(HallInfo::HandlerSExchangeRecord));
	int err = cl.err();
	if (err == 0){
		m_pSExchangeRecord = cl;
		ExchangeLayer *p = GameControl::getIns()->getExchangeLayer();
		if (p){
			p->AddRecords();
		}
		GameControl::getIns()->ShowTopTip(XXIconv::GBK2UTF("获取兑换记录成功").c_str());
	}
	else{
		GameControl::getIns()->ShowTopTip(XXIconv::GBK2UTF("获取兑换记录失败").c_str());
	}
}

void HallInfo::SendCExchange(int id){
	CExchange cl;
	cl.set_cmd(cl.cmd());
	cl.set_id(id);
	XXEventDispatcher::getIns()->addListener(cl.cmd(), this, Event_Handler(HallInfo::HandlerSExchange));
	ClientSocket::getIns()->sendMsg(cl.cmd(), &cl);
}

void HallInfo::HandlerSExchange(ccEvent *event){
	SExchange cl;
	cl.CopyFrom(*event->msg);
	XXEventDispatcher::getIns()->removeListener(cl.cmd(), this, Event_Handler(HallInfo::HandlerSExchange));
	int err = cl.err();
	if (err == 0){
		int id = cl.id();
		string code = cl.code();
		GameControl::getIns()->ShowTopTip(XXIconv::GBK2UTF("兑换奖品成功，奖品将在0-7个工作内发放"));

		SendCExchangeRecord();
		ExchangeLayer *p = GameControl::getIns()->getExchangeLayer();
		if (p){
			p->AddExchangeItems();
		}
	}
}

void HallInfo::SendCApplePay(int id, string receipt){
	CApplePay cl;
	cl.set_cmd(cl.cmd());
	cl.set_id(id);
	cl.set_receipt(receipt);
	XXEventDispatcher::getIns()->addListener(cl.cmd(), this, Event_Handler(HallInfo::HandlerSApplePay));
	ClientSocket::getIns()->sendMsg(cl.cmd(), &cl);
}

void HallInfo::HandlerSApplePay(ccEvent *event){
	SApplePay cl;
	cl.CopyFrom(*event->msg);
	XXEventDispatcher::getIns()->removeListener(cl.cmd(), this, Event_Handler(HallInfo::HandlerSApplePay));
	int err = cl.err();
	if (err == 0){

	}
}


void HallInfo::SendCWxpayOrder(int id, string body){
	CWxpayOrder cl;
	cl.set_cmd(cl.cmd());
	cl.set_id(id);
	cl.set_body(body);
	XXEventDispatcher::getIns()->addListener(cl.cmd(), this, Event_Handler(HallInfo::HandlerSWxpayOrder));
	ClientSocket::getIns()->sendMsg(cl.cmd(), &cl);
}

void HallInfo::HandlerSWxpayOrder(ccEvent *event){
	SWxpayOrder cl;
	cl.CopyFrom(*event->msg);
	XXEventDispatcher::getIns()->removeListener(cl.cmd(), this, Event_Handler(HallInfo::HandlerSWxpayOrder));
	int err = cl.err();
	if (err == 0){
		//调用sdk支付
		string prepayid = cl.payreq();
		string noncestr = cl.noncestr();
		string timestamp = cl.timestamp();
		string sign = cl.sign();
		YLJni::WeixinPay(prepayid.c_str(), noncestr.c_str(), timestamp.c_str(), sign.c_str());
	}
}


void HallInfo::SendCWxpayQuery(string transid){
	CWxpayQuery cl;
	cl.set_cmd(cl.cmd());
	cl.set_transid(transid);
	ClientSocket::getIns()->sendMsg(cl.cmd(), &cl);
}

void HallInfo::HandlerSWxpayQuery(ccEvent *event){
	SWxpayQuery cl;
	cl.CopyFrom(*event->msg);
	int err = cl.err();
	if (err == 0){
		string transid = cl.transid();
	}
}


void HallInfo::SendCFirstBuy(int type){
	CFirstBuy cl;
	cl.set_cmd(cl.cmd());
	cl.set_type(type);
	XXEventDispatcher::getIns()->addListener(cl.cmd(), this, Event_Handler(HallInfo::HandlerSFirstBuy));
	ClientSocket::getIns()->sendMsg(cl.cmd(), &cl);
}

void HallInfo::HandlerSFirstBuy(ccEvent *event){
	SFirstBuy cl;
	cl.CopyFrom(*event->msg);
	XXEventDispatcher::getIns()->removeListener(cl.cmd(), this, Event_Handler(HallInfo::HandlerSFirstBuy));
	int err = cl.err();
	if (err == 0){
		int type = cl.type();
		string prepayid = cl.payreq();
		string noncestr = cl.noncestr();
		string timestamp = cl.timestamp();
		string sign = cl.sign();
		if (type == 2){
			YLJni::WeixinPay(prepayid.c_str(), noncestr.c_str(), timestamp.c_str(), sign.c_str());
		}
		else if (type == 3){
			YLJni::AliPay(prepayid.c_str(), timestamp.c_str(), noncestr.c_str(), sign.c_str());
		}
		else if (type == 1){
			
		}
		
	}
}

void HallInfo::SendCAliPayOrder(int id, string body){
	CAliPayOrder cpo;
	cpo.set_id(id);
	cpo.set_body(body);
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cpo.set_type(1);
#else
	cpo.set_type(2);
#endif
	XXEventDispatcher::getIns()->addListener(cpo.cmd(), this, Event_Handler(HallInfo::HandlerSAliPayOrder));
	ClientSocket::getIns()->sendMsg(cpo.cmd(), &cpo);
}

void HallInfo::HandlerSAliPayOrder(ccEvent *event){
	SAliPayOrder cl;
	cl.CopyFrom(*event->msg);
	XXEventDispatcher::getIns()->removeListener(cl.cmd(), this, Event_Handler(HallInfo::HandlerSAliPayOrder));
	int err = cl.err();
	if (err == 0){
		string orderinfo = cl.orderinfo();
		string timestamp=cl.timestamp();
		string appid = cl.appid();
		string privatekey = cl.privatekey();
		
		YLJni::AliPay(appid.c_str(), timestamp.c_str(), orderinfo.c_str(), privatekey.c_str());
	}
}

void HallInfo::SendCAliPayResult(string content){
	CAliPayResult cpo;
	cpo.set_content(content);
	XXEventDispatcher::getIns()->addListener(cpo.cmd(), this, Event_Handler(HallInfo::HandlerSAliPayResult));
	ClientSocket::getIns()->sendMsg(cpo.cmd(), &cpo);
}

void HallInfo::HandlerSAliPayResult(ccEvent *event){
	SAliPayResult cpo;
	cpo.CopyFrom(*event->msg);
	XXEventDispatcher::getIns()->removeListener(cpo.cmd(), this, Event_Handler(HallInfo::HandlerSAliPayResult));
}

//反馈
void HallInfo::SendCFeedBack(string uid, string uname, string content){
	CFeedBack cl;
	cl.set_cmd(cl.cmd());
	cl.set_uid(uid);
	cl.set_uname(uname);
	cl.set_content(content);
	XXEventDispatcher::getIns()->addListener(cl.cmd(), this, Event_Handler(HallInfo::HandlerSFeedBack));
	ClientSocket::getIns()->sendMsg(cl.cmd(), &cl);
}

void HallInfo::HandlerSFeedBack(ccEvent *event){
	SFeedBack cl;
	cl.CopyFrom(*event->msg);
	XXEventDispatcher::getIns()->removeListener(cl.cmd(), this, Event_Handler(HallInfo::HandlerSFeedBack));
	int err = cl.err();
	if (err == 0){
		FankuiLayer *p = GameControl::getIns()->getFankuiLayer();
		if (p){
			p->FeedBackFinish();
		}

	}
}


//签到
void HallInfo::SendCSign(){
	CSign cl;
	cl.set_cmd(cl.cmd());
	XXEventDispatcher::getIns()->addListener(cl.cmd(), this, Event_Handler(HallInfo::HandlerSSign));
	ClientSocket::getIns()->sendMsg(cl.cmd(), &cl);
}

void HallInfo::HandlerSSign(ccEvent *event){
	SSign cl;
	cl.CopyFrom(*event->msg);
	XXEventDispatcher::getIns()->removeListener(cl.cmd(), this, Event_Handler(HallInfo::HandlerSSign));
	int err = cl.err();
	if (err == 0){
		m_pSSign = cl;
		m_pSSignList.set_sign(true);
		SignLayer *p = GameControl::getIns()->getSignLayer();
		if (p){
			p->setSignData();
			p->Run();
		}
		MainLayer *pp = GameControl::getIns()->getMainLayer();
		if (pp){
			pp->ShowTip(POINT_SIGN, false);
		}
	}
}


void HallInfo::SendCSignList(){
	CSignList cl;
	cl.set_cmd(cl.cmd());
	XXEventDispatcher::getIns()->addListener(cl.cmd(), this, Event_Handler(HallInfo::HandlerSSignList));
	ClientSocket::getIns()->sendMsg(cl.cmd(), &cl);

}

void HallInfo::HandlerSSignList(ccEvent *event){
	SSignList cl;
	cl.CopyFrom(*event->msg);
	XXEventDispatcher::getIns()->removeListener(cl.cmd(), this, Event_Handler(HallInfo::HandlerSSignList));
	int err = cl.err();
	if (err == 0){
		m_pSSignList = cl;
		
		SignLayer *p = GameControl::getIns()->getSignLayer();
		if (p){
			p->setSignData();
		}
	}
}

void HallInfo::SendCFirsyBuyData(){
	CFirsyBuyData cl;
	cl.set_cmd(cl.cmd());
	XXEventDispatcher::getIns()->addListener(cl.cmd(), this, Event_Handler(HallInfo::HandSFirsyBuyData));
	ClientSocket::getIns()->sendMsg(cl.cmd(), &cl);
}

void HallInfo::HandSFirsyBuyData(ccEvent *event){
	SFirsyBuyData cl;
	cl.CopyFrom(*event->msg);
	XXEventDispatcher::getIns()->removeListener(cl.cmd(), this, Event_Handler(HallInfo::HandSFirsyBuyData));
	int err = cl.err();
	if (err == 0){
		m_pSFirsyBuyData = cl;

		FirstChargeLayer *p = GameControl::getIns()->getFirstChargeLayer();
		if (p){
			p->setData();
		}
	}
}