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

}

void RoomInfo::SendCBegin(int rtype){
	CBegin cr;
	string uid = LoginInfo::getIns()->getMyUserBase().userid();
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
	string uid = LoginInfo::getIns()->getMyUserBase().userid();
	cr.set_uid(uid);
	cr.set_ready(isready);
	ClientSocket::getIns()->sendMsg(cr.cmd(), &cr);
}

void RoomInfo::HandSReady(ccEvent *event){
	SReady cl;
	cl.CopyFrom(*event->msg);
	int err = cl.err();
	if (err == 0){

	}
	else{

	}
}

void RoomInfo::SendCLeave(){
	CLeave cr;
	string uid = LoginInfo::getIns()->getMyUserBase().userid();
	cr.set_uid(uid);
	ClientSocket::getIns()->sendMsg(cr.cmd(), &cr);
}

void RoomInfo::HandSLeave(ccEvent *event){
	SLeave cl;
	cl.CopyFrom(*event->msg);
	int err = cl.err();
	if (err == 0){

	}
	else{

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