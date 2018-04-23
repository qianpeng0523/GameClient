#include "RoomInfo.h"
#include "ClientSocket.h"
#include "XXEventDispatcher.h"
#include "XXIconv.h"
#include "MainScene.h"
#include "GameControl.h"
#include "LoadingLayer.h"
#include "YLJni.h"
#include "GameDataSet.h"

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
	XXEventDispatcher::getIns()->addListener(cl.cmd(), this, Event_Handler(RoomInfo::HandlerSHMMJCreateRoom));
	ClientSocket::getIns()->sendMsg(cl.cmd(),&cl);
}

void RoomInfo::HandlerSHMMJCreateRoom(ccEvent *event){
	SHMMJCreateRoom cl;
	cl.CopyFrom(*event->msg);
	XXEventDispatcher::getIns()->removeListener(cl.cmd(), this, Event_Handler(RoomInfo::HandlerSHMMJCreateRoom));
	int err = cl.err();
	if (err==0){
		
	}
	else{
		
	}
}

void RoomInfo::SendCHMMJEnterRoom(int rtype, string rid){
	CHMMJEnterRoom cr;
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

	}
	else{

	}
}

void RoomInfo::HandSComein(ccEvent *event){
	SComein cl;
	cl.CopyFrom(*event->msg);
	RoomUser user = cl.roomuser();

}

void RoomInfo::SendCBegin(int rtype){
	CBegin cr;
	cr.set_rtype(rtype);
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