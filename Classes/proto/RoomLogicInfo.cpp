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
	pe->addListener(sl.cmd(), this, Event_Handler(RoomLogicInfo::HandlerSDice));

	SSelectZhuang sl1;
	pe->registerProto(sl1.cmd(), sl1.GetTypeName());
	pe->addListener(sl1.cmd(), this, Event_Handler(RoomLogicInfo::HandSSelectZhuang));

	SZhuangCard sl2;
	pe->registerProto(sl2.cmd(), sl2.GetTypeName());
	pe->addListener(sl2.cmd(), this, Event_Handler(RoomLogicInfo::HandSZhuangCard));

	SCard sl3;
	pe->registerProto(sl3.cmd(), sl3.GetTypeName());
	pe->addListener(sl3.cmd(), this, Event_Handler(RoomLogicInfo::HandSCard));

	SDiscard sl4;
	pe->registerProto(sl4.cmd(), sl4.GetTypeName());
	pe->addListener(sl4.cmd(), this, Event_Handler(RoomLogicInfo::HandSDiscard));

	SDraw sl5;
	pe->registerProto(sl5.cmd(), sl5.GetTypeName());
	pe->addListener(sl5.cmd(), this, Event_Handler(RoomLogicInfo::HandSDraw));

	SOtherDraw sl6;
	pe->registerProto(sl6.cmd(), sl6.GetTypeName());
	pe->addListener(sl6.cmd(), this, Event_Handler(RoomLogicInfo::HandSOtherDraw));

	SChi sl7;
	pe->registerProto(sl7.cmd(), sl7.GetTypeName());
	pe->addListener(sl7.cmd(), this, Event_Handler(RoomLogicInfo::HandSChi));

	SPeng sl8;
	pe->registerProto(sl8.cmd(), sl8.GetTypeName());
	pe->addListener(sl8.cmd(), this, Event_Handler(RoomLogicInfo::HandSPeng));

	SMingGang sl9;
	pe->registerProto(sl9.cmd(), sl9.GetTypeName());
	pe->addListener(sl9.cmd(), this, Event_Handler(RoomLogicInfo::HandSMingGang));

	SAnGang sl10;
	pe->registerProto(sl10.cmd(), sl10.GetTypeName());
	pe->addListener(sl10.cmd(), this, Event_Handler(RoomLogicInfo::HandSAnGang));

	SFa sl11;
	pe->registerProto(sl11.cmd(), sl11.GetTypeName());
	pe->addListener(sl11.cmd(), this, Event_Handler(RoomLogicInfo::HandSFa));

	SHu sl12;
	pe->registerProto(sl12.cmd(), sl12.GetTypeName());
	pe->addListener(sl12.cmd(), this, Event_Handler(RoomLogicInfo::HandSHu));

	SGameover sl13;
	pe->registerProto(sl13.cmd(), sl13.GetTypeName());
	pe->addListener(sl13.cmd(), this, Event_Handler(RoomLogicInfo::HandSGameover));

	SRoundOver sl14;
	pe->registerProto(sl14.cmd(), sl14.GetTypeName());
	pe->addListener(sl14.cmd(), this, Event_Handler(RoomLogicInfo::HandSRoundOver));

	SDissolveTip sl15;
	pe->registerProto(sl15.cmd(), sl15.GetTypeName());
	pe->addListener(sl15.cmd(), this, Event_Handler(RoomLogicInfo::HandSDissolveTip));
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

void RoomLogicInfo::HandSSelectZhuang(ccEvent *event){
	SSelectZhuang cl;
	cl.CopyFrom(*event->msg);
	
	
}

void RoomLogicInfo::HandSZhuangCard(ccEvent *event){
	SZhuangCard cl;
	cl.CopyFrom(*event->msg);
	
}

void RoomLogicInfo::HandSCard(ccEvent *event){
	SCard cl;
	cl.CopyFrom(*event->msg);
	
}

void RoomLogicInfo::SendCDiscard(int card){
	CDiscard cl;
	cl.set_card(card);
	ClientSocket::getIns()->sendMsg(cl.cmd(), &cl);
}

void RoomLogicInfo::HandSDiscard(ccEvent *event){
	SDiscard cl;
	cl.CopyFrom(*event->msg);
}

void RoomLogicInfo::HandSDraw(ccEvent *event){
	SDraw cl;
	cl.CopyFrom(*event->msg);
}

void RoomLogicInfo::HandSOtherDraw(ccEvent *event){
	SOtherDraw cl;
	cl.CopyFrom(*event->msg);
}

void RoomLogicInfo::SendChi(string chi){
	CChi cl;
	cl.set_card(chi);
	ClientSocket::getIns()->sendMsg(cl.cmd(), &cl);
}

void RoomLogicInfo::HandSChi(ccEvent *event){
	SChi cl;
	cl.CopyFrom(*event->msg);
}

void RoomLogicInfo::SendCPeng(int card){
	CPeng cl;
	cl.set_card(card);
	ClientSocket::getIns()->sendMsg(cl.cmd(), &cl);
}

void RoomLogicInfo::HandSPeng(ccEvent *event){
	SPeng cl;
	cl.CopyFrom(*event->msg);
}

void RoomLogicInfo::SendCMingGang(int card, int type){
	CMingGang cl;
	cl.set_card(card);
	ClientSocket::getIns()->sendMsg(cl.cmd(), &cl);
}

void RoomLogicInfo::HandSMingGang(ccEvent *event){
	SMingGang cl;
	cl.CopyFrom(*event->msg);
}

void RoomLogicInfo::SendCAnGang(int card, int type){
	CAnGang cl;
	cl.set_card(card);
	ClientSocket::getIns()->sendMsg(cl.cmd(), &cl);
}

void RoomLogicInfo::HandSAnGang(ccEvent *event){
	SAnGang cl;
	cl.CopyFrom(*event->msg);
}

void RoomLogicInfo::HandSFa(ccEvent *event){
	SFa cl;
	cl.CopyFrom(*event->msg);
}

void RoomLogicInfo::SendCHu(){
	CHu cl;
	ClientSocket::getIns()->sendMsg(cl.cmd(), &cl);
}

void RoomLogicInfo::HandSHu(ccEvent *event){
	SHu cl;
	cl.CopyFrom(*event->msg);
}

void RoomLogicInfo::HandSGameover(ccEvent *event){
	SGameover cl;
	cl.CopyFrom(*event->msg);
}

void RoomLogicInfo::HandSRoundOver(ccEvent *event){
	SRoundOver cl;
	cl.CopyFrom(*event->msg);
}

void RoomLogicInfo::HandSDissolveTip(ccEvent *event){
	SDissolveTip cl;
	cl.CopyFrom(*event->msg);
}