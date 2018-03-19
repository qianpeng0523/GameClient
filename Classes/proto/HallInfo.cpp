#include "HallInfo.h"
#include "ClientSocket.h"
#include "XXEventDispatcher.h"
#include "XXIconv.h"
#include "MainScene.h"
#include "GameControl.h"
#include "GameDataSet.h"

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

}

void HallInfo::HandlerSGiveFriend(ccEvent *event){

}


void HallInfo::SendCAddFriend(string uid){

}

void HallInfo::HandlerSAddFriend(ccEvent *event){

}


void HallInfo::SendCAddFriendList(){

}

void HallInfo::HandlerSAddFriendList(ccEvent *event){

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
