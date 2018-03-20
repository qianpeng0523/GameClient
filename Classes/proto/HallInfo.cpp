#include "HallInfo.h"
#include "ClientSocket.h"
#include "XXEventDispatcher.h"
#include "XXIconv.h"
#include "MainScene.h"
#include "GameControl.h"
#include "GameDataSet.h"
#include "LoginInfo.h"

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
	cl.set_type(type);
	cl.set_index(index);
	XXEventDispatcher::getIns()->addListener(cl.cmd(), this, Event_Handler(HallInfo::HandlerSRankHand));
	ClientSocket::getIns()->sendMsg(cl.cmd(), &cl);

	//test
	SRank cl1;
	cl1.set_type(type);
	if (index < 5){
		char buff1[30];
		for (int i = 0; i < 10; i++){
			Rank rk;
			rk.set_lv(index * 10 + (i + 1));
			rk.set_number(10000 * type + 1000 * i);
			sprintf(buff1, "1%d%d0%02d", type, index, i);
			rk.set_uid(buff1);
			sprintf(buff1, "qp1%d%d0%02d", type, index, i);
			rk.set_uname(buff1);
			rk.set_type(type);
			Rank *rk1 = cl1.add_list();
			rk1->CopyFrom(rk);
		}
	}
	int sz = cl1.ByteSize();
	char *buff=new char[sz];
	cl1.SerializePartialToArray(buff, sz);
	ccEvent *ev =new ccEvent(cl1.cmd(),buff,sz);
	HandlerSRankHand(ev);
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
	XXEventDispatcher::getIns()->addListener(cl.cmd(), this, Event_Handler(HallInfo::HandlerSMail));
	ClientSocket::getIns()->sendMsg(cl.cmd(), &cl);

	//test
	char buff[100];
	SMail sl;
	for (int i = 0; i < 8; i++){
		Mail *ml= sl.add_list();
		ml->set_id(i + 1);
		sprintf(buff, XXIconv::GBK2UTF("邮件内容测试%d").c_str(),i+1);
		ml->set_content(buff);
		sprintf(buff, XXIconv::GBK2UTF("邮件标题%d").c_str(), i + 1);
		ml->set_title(buff);
		ml->set_time(GameDataSet::getLocalTime().c_str());
		ml->set_type(1);
	}
	int sz = sl.ByteSize();
	char *buffer = new char[sz];
	sl.SerializePartialToArray(buffer, sz);
	ccEvent *ev = new ccEvent(sl.cmd(),buffer,sz);
	HandlerSMail(ev);
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

void HallInfo::SendCFriend(){
	CFriend cl;
	XXEventDispatcher::getIns()->addListener(cl.cmd(), this, Event_Handler(HallInfo::HandlerSFriend));
	ClientSocket::getIns()->sendMsg(cl.cmd(), &cl);

	//test
	SFriend sf;
	for (int i = 0; i < 7;i++){
		Friend *fri=sf.add_list();
		fri->set_acttype(i%3+1);
		fri->set_time(GameDataSet::getTime());
		char buff[100];
		DBUserInfo us;
		DBUserInfo *user = (DBUserInfo *)ccEvent::create_message(us.GetTypeName());
		sprintf(buff, "10000%d", i);
		user->set_username(buff);
		fri->set_allocated_userinfo(user);
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
		DBUserInfo us;
		DBUserInfo *user= (DBUserInfo *)ccEvent::create_message(us.GetTypeName());
		sprintf(buff, "10000%d", i);
		user->set_username(buff);
		user->set_userid(buff);
		fri->set_allocated_userinfo(user);

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
	XXEventDispatcher::getIns()->addListener(cl.cmd(), this, Event_Handler(HallInfo::HandlerSAddFriendList));
	ClientSocket::getIns()->sendMsg(cl.cmd(), &cl);

	//test
	char buff[100];
	SAddFriendList fris;
	for (int i = 0; i < 5; i++){
		FriendNotice *fri = fris.add_list();
		fri->set_add(i%2);
		sprintf(buff, "1000%02d", i);
		fri->set_uid(buff);
		Mail ml1;
		Mail *ml = (Mail *)ccEvent::create_message(ml1.GetTypeName());
		ml->set_id(i + 1);
		sprintf(buff, XXIconv::GBK2UTF("%s添加您为好友").c_str(), buff);
		ml->set_content(buff);
		sprintf(buff, XXIconv::GBK2UTF("邮件标题%d").c_str(), i + 1);
		ml->set_title(buff);
		ml->set_time(GameDataSet::getLocalTime().c_str());
		ml->set_type(1);
		fri->set_allocated_notice(ml);
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
		ts->set_count(count);
		int fcount = 2 * (i % 3) + 1;
		ts->set_fcount(fcount);
		if (count <= fcount){
			ts->set_finish(i%2+1);
		}
		else{
			ts->set_finish(0);
		}
		ts->set_type(i / 4 + 1);
		Prop *prop = ts->add_award();
		prop->set_id(1);
		prop->set_name(XXIconv::GBK2UTF("金币"));
		prop->set_number(i*(i / 4) * 1500);
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

void HallInfo::SendCReward(int type, int id){
	CReward cl;
	cl.set_type(type);
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
	XXEventDispatcher::getIns()->addListener(cl.cmd(), this, Event_Handler(HallInfo::HandlerSExchangeReward));
	ClientSocket::getIns()->sendMsg(cl.cmd(), &cl);

	//test
	char buff[100];
	int gold = LoginInfo::getIns()->getMyDBUserInfo().gold();
	SExchangeReward se;
	for (int i = 0; i < 8; i++){
		ExAward *ea = se.add_list();
		ea->set_eid(i+1);
		ea->set_pid(1);
		int number = 28000*i;
		sprintf(buff,XXIconv::GBK2UTF("%d元红包").c_str(),i*5+5);
		ea->set_title(buff);
		ea->set_can(gold>=number);
		Prop prop;
		prop.set_id(1);
		prop.set_name(XXIconv::GBK2UTF("金币"));
		prop.set_number(number);
		Prop *prop1=(Prop *)ccEvent::create_message(prop.GetTypeName());
		prop1->CopyFrom(prop);

		ea->set_allocated_award(prop1);
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
	XXEventDispatcher::getIns()->addListener(cl.cmd(), this, Event_Handler(HallInfo::HandlerSExchangeRecord));
	ClientSocket::getIns()->sendMsg(cl.cmd(), &cl);

	//test
	char buff[100];
	int gold = LoginInfo::getIns()->getMyDBUserInfo().gold();
	SExchangeRecord se;
	for (int i = 0; i < 8; i++){
		ExRecord *ea = se.add_list();
		sprintf(buff, XXIconv::GBK2UTF("%d元红包").c_str(), i * 5 + 5);
		ea->set_title(buff);
		ea->set_id(i+1);
		sprintf(buff,"201803201%04d",i);
		ea->set_orderid(buff);
		ea->set_status(i%2);
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