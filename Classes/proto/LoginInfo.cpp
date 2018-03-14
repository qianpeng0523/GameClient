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
	SRegister sr;
	pe->registerProto(sr.cmd(), sr.GetTypeName());
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
	MD55 md5;
	md5.update(pwd);
	cl.set_pwd(md5.toString());
	XXEventDispatcher::getIns()->addListener(cl.cmd(), this, Event_Handler(LoginInfo::HandlerSLoginHand));
	ClientSocket::getIns()->sendMsg(cl.cmd(),&cl);
}

void LoginInfo::HandlerSLoginHand(ccEvent *event){
	SLogin cl;
	cl.CopyFrom(*event->msg);
	XXEventDispatcher::getIns()->removeListener(cl.cmd(), this, Event_Handler(LoginInfo::HandlerSLoginHand));
	int err = cl.err();
	if (err==0){
		log("%s",XXIconv::GBK2UTF("登录成功!").c_str());
	}
	else{
		log("%s", XXIconv::GBK2UTF("账号密码错误").c_str());
	}
}

void LoginInfo::SendCRegister(string uid, string pwd, string uname){
	CRegister cl;
	cl.set_uid(uid);
	MD55 md5;
	md5.update(pwd);
	cl.set_pwd(/*md5.toString()*/pwd);
	cl.set_uname(uname);
	XXEventDispatcher::getIns()->addListener(cl.cmd(), this, Event_Handler(LoginInfo::HandlerSRegister));
	ClientSocket::getIns()->sendMsg(cl.cmd(), &cl);
}

void LoginInfo::HandlerSRegister(ccEvent *event){
	SRegister cl;
	cl.CopyFrom(*event->msg);
	XXEventDispatcher::getIns()->removeListener(cl.cmd(), this, Event_Handler(LoginInfo::HandlerSRegister));
	int err = cl.err();
	if (err == 0){
		log("%s", XXIconv::GBK2UTF("注册成功!").c_str());
	}
	else if(err==1){
		log("%s", XXIconv::GBK2UTF("注册失败!").c_str());
	}
	else if(err==2){
		log("%s", XXIconv::GBK2UTF("用户已存在!").c_str());
	}
}