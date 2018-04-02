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

using namespace cocos2d_xx;
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
	SFriend sr4;
	pe->registerProto(sr4.cmd(), sr4.GetTypeName());
	SFindFriend sl5;
	pe->registerProto(sl5.cmd(), sl5.GetTypeName());
	SGiveFriend sr6;
	pe->registerProto(sr6.cmd(), sr6.GetTypeName());
	SAddFriend sl7;
	pe->registerProto(sl7.cmd(), sl7.GetTypeName());
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
	
	pe->addListener(sl19.cmd(), this, Event_Handler(HallInfo::HandlerSWxpayQuery));
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
			p->addShopItem(type);
		}
	}
	else{
		log("%s",XXIconv::GBK2UTF("获取商城列表失败"));
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
	XXEventDispatcher::getIns()->addListener(cl.cmd(), this, Event_Handler(HallInfo::HandlerSMail));
	ClientSocket::getIns()->sendMsg(cl.cmd(), &cl);
}

void HallInfo::HandlerSMail(ccEvent *event){
	SMail cl;
	cl.CopyFrom(*event->msg);
	XXEventDispatcher::getIns()->removeListener(cl.cmd(), this, Event_Handler(HallInfo::HandlerSMail));
	int err = cl.err();
	if (err == 0){
		m_pSMail = cl;
		MailLayer *p = GameControl::getIns()->getMailLayer();
		if (p){
			p->AddMailItems();
		}
	}
	else{
		log("%s", XXIconv::GBK2UTF("获取邮箱列表失败"));
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
		int id = cl.id();
		for (int i = 0; i < m_pSMail.list_size();i++){
			Mail p = m_pSMail.list(i);
			if (p.eid() == id){
				//查找到了  然后提示奖励界面

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
	for (int i = 0; i < 7;i++){
		Friend *fri=sf.add_list();
		fri->set_acttype(i%3+1);
		fri->set_time(GameDataSet::getTime());
		char buff[100];
		UserBase *user = fri->mutable_info();
		sprintf(buff, "10000%d", i);
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
	XXEventDispatcher::getIns()->removeListener(cl.cmd(), this, Event_Handler(HallInfo::HandlerSFindFriend));
	int err = cl.err();
	if (err == 0){
		m_pSFindFriend = cl;
		FriendLayer *p = GameControl::getIns()->getFriendLayer();
		if (p){
			p->ShowFriendEvent(0);
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
	XXEventDispatcher::getIns()->addListener(cl.cmd(), this, Event_Handler(HallInfo::HandlerSAddFriend));
	ClientSocket::getIns()->sendMsg(cl.cmd(), &cl);
}

void HallInfo::HandlerSAddFriend(ccEvent *event){
	SAddFriend cl;
	cl.CopyFrom(*event->msg);
	XXEventDispatcher::getIns()->removeListener(cl.cmd(), this, Event_Handler(HallInfo::HandlerSAddFriend));
	int err = cl.err();
	if (err == 0){
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

	//test
	char buff[100];
	SAddFriendList fris;
	for (int i = 0; i < 5; i++){
		FriendNotice *fri = fris.add_list();
		fri->set_status(i%2);
		sprintf(buff, "1000%02d", i);
		fri->set_uid(buff);
		fri->set_nid(i + 1);
		sprintf(buff, XXIconv::GBK2UTF("%s添加您为好友").c_str(), buff);
		fri->set_content(buff);
		fri->set_time(GameDataSet::getLocalTime().c_str());
	}
	int sz = fris.ByteSize();
	char *buffer = new char[sz];
	fris.SerializePartialToArray(buffer, sz);
	ccEvent *ev = new ccEvent(fris.cmd(), buffer, sz);
	HandlerSAddFriendList(ev);
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
		log("%s", XXIconv::GBK2UTF("获取活动列表失败"));
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
		sprintf(buff,XXIconv::GBK2UTF("登录奖励%d").c_str(),i%4+1);
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
		log("%s", XXIconv::GBK2UTF("获取活动列表失败"));
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
		log("%s", XXIconv::GBK2UTF("领取奖励成功"));
	}
	else{
		log("%s", XXIconv::GBK2UTF("领取奖励失败"));
	}
}

void HallInfo::SendCAgreeFriend(string uid, bool agree){
	CAgreeFriend cl;
	cl.set_cmd(cl.cmd());
	cl.set_userid(uid);
	cl.set_agree(agree);
	XXEventDispatcher::getIns()->addListener(cl.cmd(), this, Event_Handler(HallInfo::HandlerSAgreeFriend));
	ClientSocket::getIns()->sendMsg(cl.cmd(), &cl);
}

void HallInfo::HandlerSAgreeFriend(ccEvent *event){
	SAgreeFriend cl;
	cl.CopyFrom(*event->msg);
	XXEventDispatcher::getIns()->removeListener(cl.cmd(), this, Event_Handler(HallInfo::HandlerSAgreeFriend));
	int err = cl.err();
	if (err == 0){
		log("%s", XXIconv::GBK2UTF("同意拒绝成功"));
	}
	else{
		log("%s", XXIconv::GBK2UTF("同意拒绝失败"));
	}
}

void HallInfo::SendCExchangeReward(){
	CExchangeReward cl;
	cl.set_cmd(cl.cmd());
	XXEventDispatcher::getIns()->addListener(cl.cmd(), this, Event_Handler(HallInfo::HandlerSExchangeReward));
	ClientSocket::getIns()->sendMsg(cl.cmd(), &cl);

	//test
	char buff[100];
	int gold = LoginInfo::getIns()->getMyUserBase().gold();
	SExchangeReward se;
	for (int i = 0; i < 8; i++){
		ExAward *ea = se.add_list();
		ea->set_eid(i+1);
		sprintf(buff, XXIconv::GBK2UTF("%d元红包").c_str(), i * 5 + 5);
		ea->set_title(buff);

		Reward *rd = ea->mutable_award();
		rd->set_rid(1);
		int number = 28000*i;
		rd->set_number(number);
		
		Prop *prop=rd->mutable_prop();
		prop->set_id(1);
		prop->set_name(XXIconv::GBK2UTF("金币"));
		
	}
	int sz = se.ByteSize();
	char *buffer = new char[sz];
	se.SerializePartialToArray(buffer, sz);
	ccEvent *ev = new ccEvent(se.cmd(), buffer, sz);
	HandlerSExchangeReward(ev);
}

void HallInfo::HandlerSExchangeReward(ccEvent *event){
	SExchangeReward cl;
	cl.CopyFrom(*event->msg);
	XXEventDispatcher::getIns()->removeListener(cl.cmd(), this, Event_Handler(HallInfo::HandlerSExchangeReward));
	int err = cl.err();
	if (err == 0){
		m_pSExchangeReward = cl;
		log("%s", XXIconv::GBK2UTF("获取兑换奖品成功"));
		ExchangeLayer *p = GameControl::getIns()->getExchangeLayer();
		if (p){
			p->SelectItem(0);
		}
	}
	else{
		log("%s", XXIconv::GBK2UTF("获取兑换奖品失败"));
	}
}

void HallInfo::SendCExchangeCode(string excode, string yzcode){
	CExchangeCode cl;
	cl.set_cmd(cl.cmd());
	XXEventDispatcher::getIns()->addListener(cl.cmd(), this, Event_Handler(HallInfo::HandlerSExchangeCode));
	ClientSocket::getIns()->sendMsg(cl.cmd(), &cl);
}

void HallInfo::HandlerSExchangeCode(ccEvent *event){
	SExchangeCode cl;
	cl.CopyFrom(*event->msg);
	XXEventDispatcher::getIns()->removeListener(cl.cmd(), this, Event_Handler(HallInfo::HandlerSExchangeCode));
	int err = cl.err();
	if (err == 0){
		log("%s", XXIconv::GBK2UTF("兑换码兑换成功"));
	}
	else{
		log("%s", XXIconv::GBK2UTF("兑换码兑换失败"));
	}
}

void HallInfo::SendCExchangeRecord(){
	CExchangeRecord cl;
	cl.set_cmd(cl.cmd());
	XXEventDispatcher::getIns()->addListener(cl.cmd(), this, Event_Handler(HallInfo::HandlerSExchangeRecord));
	ClientSocket::getIns()->sendMsg(cl.cmd(), &cl);

	//test
	char buff[100];
	int gold = LoginInfo::getIns()->getMyUserBase().gold();
	SExchangeRecord se;
	for (int i = 0; i < 8; i++){
		ExRecord *ea = se.add_list();
		sprintf(buff, XXIconv::GBK2UTF("%d元红包").c_str(), i * 5 + 5);
		ea->set_title(buff);
		ea->set_eid(i+1);
		sprintf(buff,"201803201%04d",i);
		ea->set_orderid(buff);
		ea->set_status(i%3);
		ea->set_time(GameDataSet::getLocalTime());
	}
	int sz = se.ByteSize();
	char *buffer = new char[sz];
	se.SerializePartialToArray(buffer, sz);
	ccEvent *ev = new ccEvent(se.cmd(), buffer, sz);
	HandlerSExchangeRecord(ev);
}

void HallInfo::HandlerSExchangeRecord(ccEvent *event){
	SExchangeRecord cl;
	cl.CopyFrom(*event->msg);
	XXEventDispatcher::getIns()->removeListener(cl.cmd(), this, Event_Handler(HallInfo::HandlerSExchangeRecord));
	int err = cl.err();
	if (err == 0){
		m_pSExchangeRecord = cl;
		log("%s", XXIconv::GBK2UTF("获取兑换记录成功"));
	}
	else{
		log("%s", XXIconv::GBK2UTF("获取兑换记录失败"));
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
		string orderid = cl.orderid();
		string payreq = cl.payreq();
		YMSocketData sd = XXHttpRequest::getIns()->getSocketDataByStr((char *)payreq.c_str(),payreq.length());

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
		int id = cl.id();
		string transid = cl.transid();
		
	}
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

	//test
	SFeedBack ss;
	int sz = ss.ByteSize();
	char *buffer = new char[sz];
	ss.SerializePartialToArray(buffer, sz);
	ccEvent *ev = new ccEvent(ss.cmd(), buffer, sz);
	HandlerSFeedBack(ev);
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

	//test
	SSign ss;
	ss.set_index(rand()%12);
	ss.set_count(4);
	int sz = ss.ByteSize();
	char *buffer = new char[sz];
	ss.SerializePartialToArray(buffer, sz);
	ccEvent *ev = new ccEvent(ss.cmd(), buffer, sz);
	HandlerSSign(ev);
}

void HallInfo::HandlerSSign(ccEvent *event){
	SSign cl;
	cl.CopyFrom(*event->msg);
	XXEventDispatcher::getIns()->removeListener(cl.cmd(), this, Event_Handler(HallInfo::HandlerSSign));
	int err = cl.err();
	if (err == 0){
		m_pSSign = cl;
		SignLayer *p = GameControl::getIns()->getSignLayer();
		if (p){
			p->Run();
		}
		m_pSSignList.set_count(cl.count());
		m_pSSignList.set_sign(1);
	}
}


void HallInfo::SendCSignList(){
	CSignList cl;
	cl.set_cmd(cl.cmd());
	XXEventDispatcher::getIns()->addListener(cl.cmd(), this, Event_Handler(HallInfo::HandlerSSignList));
	ClientSocket::getIns()->sendMsg(cl.cmd(), &cl);

	//test
	SSignList sl;
	sl.set_count(3);
	sl.set_sign(0);
	int dd[8] = { 3, 5, 7, 10, 14, 18, 22, 30 };
	for (int i = 0; i < 8;i++){
		SignAward *sa = sl.add_reward();
		sa->set_id(i+1);
		sa->set_day(dd[i]);

		int pid = i % 2 + 1;
		Reward *rd = sa->mutable_reward();
		rd->set_number(pid == 1 ? 500 * dd[i] : i / 2);

		Prop *p = rd->mutable_prop();
		p->set_id(pid);
		
	}
	int sz = sl.ByteSize();
	char *buffer = new char[sz];
	sl.SerializePartialToArray(buffer, sz);
	ccEvent *ev = new ccEvent(sl.cmd(), buffer, sz);
	HandlerSSignList(ev);
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
