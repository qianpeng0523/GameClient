#include "LoginInfo.h"
#include "ClientSocket.h"
#include "XXEventDispatcher.h"
#include "XXIconv.h"

using namespace cocos2d_xx;
LoginInfo *LoginInfo::m_shareLoginInfo=NULL;
LoginInfo::LoginInfo()
{
	XXEventDispatcher *pe = XXEventDispatcher::getIns();
	SLogin sl;
	pe->registerProto(sl.cmd(), sl.GetTypeName());
	
}

LoginInfo::~LoginInfo(){
	
}

LoginInfo* LoginInfo::getIns(){
	if (!m_shareLoginInfo){
		m_shareLoginInfo = new LoginInfo();
		m_shareLoginInfo->init();
	}
	return m_shareLoginInfo;
}

bool LoginInfo::init()
{
	
    return true;
}

void LoginInfo::SendCLogin(string uid,string pwd){
	CLogin cl;
	cl.set_uid(uid);
	cl.set_pwd(pwd);
	XXEventDispatcher::getIns()->addListener(cl.cmd(), this, Event_Handler(LoginInfo::HandlerSLoginHand));
	ClientSocket::getIns()->sendMsg(cl.cmd(),&cl);
}

void LoginInfo::HandlerSLoginHand(ccEvent *event){
	SLogin cl;
	cl.CopyFrom(*event->msg);
	XXEventDispatcher::getIns()->removeListener(cl.cmd(), this, Event_Handler(LoginInfo::HandlerSLoginHand));
	int err = cl.err();
	if (err==0){
		log("%s",XXIconv::GBK2UTF("连接成功!").c_str());
	}
	else{
		log("%s", XXIconv::GBK2UTF("数据有问题").c_str());
	}
}