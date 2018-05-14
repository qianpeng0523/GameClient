#include "ConfigInfo.h"
#include "YLJni.h"
#include "XXEventDispatcher.h"
#include "ClientSocket.h"
#include "LoginInfo.h"
#include "GameControl.h"


ConfigInfo *ConfigInfo::m_shareConfigInfo=NULL;
ConfigInfo::ConfigInfo()
{
	XXEventDispatcher *pe = XXEventDispatcher::getIns();
	SConfig sl;
	pe->registerProto(sl.cmd(), sl.GetTypeName());
	XXEventDispatcher::getIns()->addListener(sl.cmd(), this, Event_Handler(ConfigInfo::HandlerSConfig));

	SPushCurrency sr;
	pe->registerProto(sr.cmd(), sr.GetTypeName());
	pe->addListener(sr.cmd(), this, Event_Handler(ConfigInfo::HandlerSPushCurrency));
}

ConfigInfo::~ConfigInfo(){
	
}

ConfigInfo* ConfigInfo::getIns(){
	if (!m_shareConfigInfo){
		m_shareConfigInfo = new ConfigInfo();
		m_shareConfigInfo->init();
	}
	return m_shareConfigInfo;
}

bool ConfigInfo::init()
{
	
    return true;
}

void ConfigInfo::SendCConfig(){
	CConfig cl;
	cl.set_cmd(cl.cmd());
	//XXEventDispatcher::getIns()->addListener(cl.cmd(), this, Event_Handler(ConfigInfo::HandlerSConfig));
	ClientSocket::getIns()->sendMsg(cl.cmd(),&cl);
}

void ConfigInfo::HandlerSConfig(ccEvent *event){
	SConfig cl;
	cl.CopyFrom(*event->msg);
	//XXEventDispatcher::getIns()->removeListener(cl.cmd(), this, Event_Handler(ConfigInfo::HandlerSConfig));
	m_pSConfig = cl;
	MainLayer *p = GameControl::getIns()->getMainLayer();
	if (p){
		p->setPointTipShow();
	}
}

void ConfigInfo::HandlerSPushCurrency(ccEvent *event){
	SPushCurrency cl;
	cl.CopyFrom(*event->msg);
	m_pSPushCurrency = cl;
	int diamond = cl.diamond();
	int card = cl.card();
	int gold = cl.gold();

	int cdiamond = cl.cdiamond();
	int ccard = cl.ccard();
	int cgold = cl.cgold();

	LoginInfo *p = LoginInfo::getIns();
	UserBase ub =p->getMyUserBase();
	ub.set_diamond(diamond);
	ub.set_card(card);
	ub.set_gold(gold);

	p->setMyUserBase(ub);
}