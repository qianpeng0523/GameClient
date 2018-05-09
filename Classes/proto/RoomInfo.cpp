#include "RoomInfo.h"
#include "ClientSocket.h"
#include "XXEventDispatcher.h"
#include "XXIconv.h"
#include "MainScene.h"
#include "GameControl.h"
#include "LoadingLayer.h"
#include "YLJni.h"
#include "GameDataSet.h"
#include "LoginInfo.h"
#include "RoomControl.h"

RoomInfo *RoomInfo::m_shareRoomInfo=NULL;
RoomInfo::RoomInfo()
{
	XXEventDispatcher *pe = XXEventDispatcher::getIns();
	SHMMJCreateRoom sl;
	pe->registerProto(sl.cmd(), sl.GetTypeName());

	SHMMJEnterRoom sl1;
	pe->registerProto(sl1.cmd(), sl1.GetTypeName());

	SComein sl2;
	pe->registerProto(sl2.cmd(), sl2.GetTypeName());
	pe->addListener(sl2.cmd(), this, Event_Handler(RoomInfo::HandSComein));

	SBegin sl3;
	pe->registerProto(sl3.cmd(), sl3.GetTypeName());

	SReady sl4;
	pe->registerProto(sl4.cmd(), sl4.GetTypeName());
	pe->addListener(sl4.cmd(), this, Event_Handler(RoomInfo::HandSReady));

	SLeave sl5;
	pe->registerProto(sl5.cmd(), sl5.GetTypeName());
	pe->addListener(sl5.cmd(), this, Event_Handler(RoomInfo::HandSLeave));

	SLine sl6;
	pe->registerProto(sl6.cmd(), sl6.GetTypeName());
	pe->addListener(sl6.cmd(), this, Event_Handler(RoomInfo::HandSLine));

	SDissolveRoom sl7;
	pe->registerProto(sl7.cmd(), sl7.GetTypeName());
	pe->addListener(sl7.cmd(), this, Event_Handler(RoomInfo::HandSDissolveRoom));

	SVote sl8;
	pe->registerProto(sl8.cmd(), sl8.GetTypeName());
	pe->addListener(sl8.cmd(), this, Event_Handler(RoomInfo::HandSVote));

	SRChat sl9;
	pe->registerProto(sl9.cmd(), sl9.GetTypeName());
	pe->addListener(sl9.cmd(), this, Event_Handler(RoomInfo::HandSRChat));

	SVoteResult sl10;
	pe->registerProto(sl10.cmd(), sl10.GetTypeName());
	pe->addListener(sl10.cmd(), this, Event_Handler(RoomInfo::HandSVoteResult));
}

RoomInfo::~RoomInfo(){
	
}

RoomInfo* RoomInfo::getIns(){
	if (!m_shareRoomInfo){
		m_shareRoomInfo = new RoomInfo();
		m_shareRoomInfo->init();
	}
	return m_shareRoomInfo;
}

bool RoomInfo::init()
{
	
    return true;
}

void RoomInfo::SendCHMMJCreateRoom(CHMMJCreateRoom cl){
	string uid= LoginInfo::getIns()->getMyUserBase().userid();
	cl.set_uid(uid);
	XXEventDispatcher::getIns()->addListener(cl.cmd(), this, Event_Handler(RoomInfo::HandlerSHMMJCreateRoom));
	ClientSocket::getIns()->sendMsg(cl.cmd(),&cl);
}

void RoomInfo::HandlerSHMMJCreateRoom(ccEvent *event){
	SHMMJCreateRoom cl;
	cl.CopyFrom(*event->msg);
	XXEventDispatcher::getIns()->removeListener(cl.cmd(), this, Event_Handler(RoomInfo::HandlerSHMMJCreateRoom));
	int err = cl.err();
	if (err==0){
		m_pRoomData.CopyFrom(cl.roomdata());
		RoomUser user = cl.roomuser();
		RoomControl::shareRoomControl()->setMyPosition(user.position());
		PushRoomUser(user);
		Scene *scene = LoadingLayer::createScene(3);
		GameControl::getIns()->replaceScene(scene);
	}
	else{
		log("create room error:%d",err);
	}
}

void RoomInfo::SendCHMMJEnterRoom(int rtype, string rid){
	CHMMJEnterRoom cr;
	string uid = LoginInfo::getIns()->getMyUserBase().userid();
	cr.set_uid(uid);
	cr.set_rtype(rtype);
	cr.set_roomid(rid);
	XXEventDispatcher::getIns()->addListener(cr.cmd(), this, Event_Handler(RoomInfo::HandSHMMJEnterRoom));
	ClientSocket::getIns()->sendMsg(cr.cmd(), &cr);
}

void RoomInfo::HandSHMMJEnterRoom(ccEvent *event){
	SHMMJEnterRoom cl;
	cl.CopyFrom(*event->msg);
	XXEventDispatcher::getIns()->removeListener(cl.cmd(), this, Event_Handler(RoomInfo::HandSHMMJEnterRoom));
	int err = cl.err();
	if (err == 0){
		m_pSHMMJEnterRoom = cl;
		m_pRoomData.CopyFrom(cl.roomdata());
		auto itr = cl.roomusers().begin();
		string uid = LoginInfo::getIns()->getUID();
		for (itr; itr != cl.roomusers().end(); itr++){
			RoomUser user = *itr;
			if (user.userid().compare(uid) == 0){
				RoomControl::shareRoomControl()->setMyPosition(user.position());
				break;
			}
		}
		itr = cl.roomusers().begin();
		for (itr; itr != cl.roomusers().end(); itr++){
			RoomUser user = *itr;
			PushRoomUser(user);
		}
		
		Scene *scene = LoadingLayer::createScene(3);
		GameControl::getIns()->replaceScene(scene);
	}
	else{
		log("enter room error:%d", err);
	}
}

void RoomInfo::HandSComein(ccEvent *event){
	SComein cl;
	cl.CopyFrom(*event->msg);
	RoomUser user = cl.roomuser();
	PushRoomUser(user);
}

void RoomInfo::SendCBegin(int rtype){
	CBegin cr;
	string uid = LoginInfo::getIns()->getUID();
	cr.set_uid(uid);
	cr.set_type(rtype);
	XXEventDispatcher::getIns()->addListener(cr.cmd(), this, Event_Handler(RoomInfo::HandSBegin));
	ClientSocket::getIns()->sendMsg(cr.cmd(), &cr);
}

void RoomInfo::HandSBegin(ccEvent *event){
	SBegin cl;
	cl.CopyFrom(*event->msg);
	XXEventDispatcher::getIns()->removeListener(cl.cmd(), this, Event_Handler(RoomInfo::HandSBegin));
	int err = cl.err();
	if (err == 0){

	}
	else{

	}
}

void RoomInfo::SendCReady(bool isready){
	CReady cr;
	string uid = LoginInfo::getIns()->getUID();
	cr.set_uid(uid);
	cr.set_ready(isready);
	ClientSocket::getIns()->sendMsg(cr.cmd(), &cr);
}

void RoomInfo::HandSReady(ccEvent *event){
	SReady cl;
	cl.CopyFrom(*event->msg);
	int err = cl.err();
	if (err == 0){
		MJGameScene *scene = GameControl::getIns()->getMJGameScene();
		if (scene){
			string uid = cl.uid();
			int pos = cl.position();
			string puid = LoginInfo::getIns()->getUID();
			if (uid.compare(puid) == 0){
				GameUI *pui = GameControl::getIns()->getGameUI();
				if (pui){
					pui->ShowReady(!cl.ready());
				}
			}
			GameHead *phead = scene->getGameHead();
			if (phead){
				phead->ShowReady(pos, cl.ready());
			}
		}
	}
	else{

	}
}

void RoomInfo::SendCLeave(){
	CLeave cr;
	string uid = LoginInfo::getIns()->getUID();
	cr.set_uid(uid);
	cr.set_zhudong(true);
	ClientSocket::getIns()->sendMsg(cr.cmd(), &cr);
}

void RoomInfo::HandSLeave(ccEvent *event){
	SLeave cl;
	cl.CopyFrom(*event->msg);
	int err = cl.err();
	if (err == 0){
		string uid = cl.uid();
		eraseRoomUser(uid);
		string muid = LoginInfo::getIns()->getUID();
		if (uid.compare(muid) == 0){
			MainScene *main = MainScene::create();
			GameControl::getIns()->replaceScene(main);
		}
	}
	else{
		GameControl::getIns()->ShowTopTip(XXIconv::GBK2UTF("离开房间出错"));
	}
}

void RoomInfo::SendCLine(bool online){
	CLine cr;
	string uid = LoginInfo::getIns()->getMyUserBase().userid();
	cr.set_uid(uid);
	cr.set_online(online);
	ClientSocket::getIns()->sendMsg(cr.cmd(), &cr);
}

void RoomInfo::HandSLine(ccEvent *event){
	SLine cl;
	cl.CopyFrom(*event->msg);
	int err = cl.err();
	if (err == 0){

	}
	else{

	}
}

void RoomInfo::SendCDissolveRoom(string rid){
	CDissolveRoom cr;
	string uid = LoginInfo::getIns()->getMyUserBase().userid();
	cr.set_uid(uid);
	cr.set_rid(rid);
	ClientSocket::getIns()->sendMsg(cr.cmd(), &cr);
}

void RoomInfo::HandSDissolveRoom(ccEvent *event){
	SDissolveRoom cl;
	cl.CopyFrom(*event->msg);
	int err = cl.err();
	if (err == 0){

	}
	else{

	}
}

void RoomInfo::SendCVote(bool agree){
	CVote cr;
	string uid = LoginInfo::getIns()->getMyUserBase().userid();
	cr.set_uid(uid);
	cr.set_agree(agree);
	ClientSocket::getIns()->sendMsg(cr.cmd(), &cr);
}

void RoomInfo::HandSVote(ccEvent *event){
	SVote cl;
	cl.CopyFrom(*event->msg);
	
}

void RoomInfo::HandSVoteResult(ccEvent *event){
	SVoteResult cl;
	cl.CopyFrom(*event->msg);
}

void RoomInfo::SendCRChat(string content){
	CRChat cr;
	string uid = LoginInfo::getIns()->getMyUserBase().userid();
	cr.set_uid(uid);
	cr.set_content(content);
	ClientSocket::getIns()->sendMsg(cr.cmd(), &cr);
}

void RoomInfo::HandSRChat(ccEvent *event){
	SRChat cl;
	cl.CopyFrom(*event->msg);
}

void RoomInfo::eraseRoomUser(string uid){
	auto itr = m_pRoomUsers.find(uid);
	if (itr != m_pRoomUsers.end()){
		m_pRoomUsers.erase(itr);
		MJGameScene *p = GameControl::getIns()->getMJGameScene();
		if (p){
			GameHead *head = p->getGameHead();
			head->PopRoomUser(uid);
		}
	}
}

void RoomInfo::clearRoomUser(){
	m_pRoomUsers.clear();
}

void RoomInfo::PushRoomUser(RoomUser user){
	string uid = user.userid();
	if (m_pRoomUsers.find(uid) == m_pRoomUsers.end()){
		m_pRoomUsers.insert(make_pair(uid, user));
	}
	MJGameScene *p = GameControl::getIns()->getMJGameScene();
	if (p){
		GameHead *head = p->getGameHead();
		head->PushRoomUser(user);
	}
}

void RoomInfo::PushAllRoomUser(){
	auto itr = m_pRoomUsers.begin();
	for (itr; itr != m_pRoomUsers.end();itr++){
		PushRoomUser(itr->second);
	}
}

RoomUser RoomInfo::getRoomInfo(string uid){
	RoomUser ru;
	if (m_pRoomUsers.find(uid) != m_pRoomUsers.end()){
		ru = m_pRoomUsers.at(uid);
	}
	return ru;
}