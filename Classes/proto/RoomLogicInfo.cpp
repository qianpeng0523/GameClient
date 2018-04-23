#include "RoomLogicInfo.h"
#include "ClientSocket.h"
#include "XXEventDispatcher.h"
#include "XXIconv.h"
#include "MainScene.h"
#include "GameControl.h"
#include "LoadingLayer.h"
#include "YLJni.h"
#include "GameDataSet.h"

RoomLogicInfo *RoomLogicInfo::m_shareRoomLogicInfo=NULL;
RoomLogicInfo::RoomLogicInfo()
{
	
	XXEventDispatcher *pe = XXEventDispatcher::getIns();
	SDice sl;
	pe->registerProto(sl.cmd(), sl.GetTypeName());
	
}

RoomLogicInfo::~RoomLogicInfo(){
	
}

RoomLogicInfo* RoomLogicInfo::getIns(){
	if (!m_shareRoomLogicInfo){
		m_shareRoomLogicInfo = new RoomLogicInfo();
		m_shareRoomLogicInfo->init();
	}
	return m_shareRoomLogicInfo;
}

bool RoomLogicInfo::init()
{
	
    return true;
}

void RoomLogicInfo::SendCDice(){
	CDice cl;
	XXEventDispatcher::getIns()->addListener(cl.cmd(), this, Event_Handler(RoomLogicInfo::HandlerSDice));
	ClientSocket::getIns()->sendMsg(cl.cmd(),&cl);
}

void RoomLogicInfo::HandlerSDice(ccEvent *event){
	SDice cl;
	cl.CopyFrom(*event->msg);
	XXEventDispatcher::getIns()->removeListener(cl.cmd(), this, Event_Handler(RoomLogicInfo::HandlerSDice));
	int err = cl.err();
	if (err==0){
		
	}
	else{
		
	}
}