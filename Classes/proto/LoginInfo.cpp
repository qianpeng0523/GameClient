#include "LoginInfo.h"
#include "ClientSocket.h"
#include "XXEventDispatcher.h"
#include "XXIconv.h"
#include "MainScene.h"
#include "GameControl.h"
#include "LoadingLayer.h"
#include "YLJni.h"
#include "GameDataSet.h"

LoginInfo *LoginInfo::m_shareLoginInfo=NULL;
LoginInfo::LoginInfo()
{
	m_logintype = LOGIN_WX;
	m_lasttime = 0;
	m_pingcount = 0;
	XXEventDispatcher *pe = XXEventDispatcher::getIns();
	SLogin sl;
	pe->registerProto(sl.cmd(), sl.GetTypeName());
	SRegister sr;
	pe->registerProto(sr.cmd(), sr.GetTypeName());

	SWXLogin sl1;
	pe->registerProto(sl1.cmd(), sl1.GetTypeName());

	SPing sl2;
	pe->registerProto(sl2.cmd(), sl2.GetTypeName());
	Director::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(LoginInfo::update), this, 1, false);
}

LoginInfo::~LoginInfo(){
	Director::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(LoginInfo::update),this);
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

void LoginInfo::setMyUserBase(UserBase ub){
	m_myinfo = ub;
	GameControl *pGameControl = GameControl::getIns();
	MainLayer *p = pGameControl->getMainLayer();
	if (p){
		p->setData();
	}
	ShopLayer *pshop = pGameControl->getShopLayer();
	if (pshop){
		pshop->setData();
	}
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
		m_myinfo = cl.info();
		log("%s",XXIconv::GBK2UTF("登录成功!").c_str());

		UserDefault *pUserDefault = UserDefault::sharedUserDefault();
		string uid = pUserDefault->getStringForKey("abc1");
		string pwd = pUserDefault->getStringForKey("ccc1");
		if (uid.compare(LoginLayer::m_uid) != 0){
			pUserDefault->setStringForKey("abc1", LoginLayer::m_uid);
			pUserDefault->setStringForKey("ccc1", LoginLayer::m_pwd);
		}
		LoginMainLayer *p = GameControl::getIns()->getLoginMainLayer();
		if (p){
			Scene *scene = LoadingLayer::createScene(2);
			GameControl::getIns()->replaceScene(scene);
		}
	}
	else{
		log("%s", XXIconv::GBK2UTF("账号密码错误").c_str());
		ClientSocket::getIns()->close();
		//SendCRegister("100001","123456","qp0001");
	}
}

void LoginInfo::SendCRegister(string uid, string pwd, string uname){
	CRegister cl;
	cl.set_uid(uid);
	MD55 md5;
	md5.update(pwd);
	cl.set_pwd(md5.toString());
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
		m_myinfo = cl.info();
		LoginLayer::m_uid = m_myinfo.userid();
		LoginLayer::m_pwd = RegLayer::m_pwd;

		UserDefault *pUserDefault = UserDefault::sharedUserDefault();
		string uid = pUserDefault->getStringForKey("abc1");
		string pwd = pUserDefault->getStringForKey("ccc1");
		if (uid.compare(LoginLayer::m_uid) != 0){
			pUserDefault->setStringForKey("abc1", LoginLayer::m_uid);
			pUserDefault->setStringForKey("ccc1", LoginLayer::m_pwd);
		}

		log("%s", XXIconv::GBK2UTF("注册成功!").c_str());
		setLoginType(LOGIN_YK);
		LoginMainLayer *p = GameControl::getIns()->getLoginMainLayer();
		if (p){
			Scene *scene = LoadingLayer::createScene(2);
			GameControl::getIns()->replaceScene(scene);
		}
	}
	else if(err==1){
		log("%s", XXIconv::GBK2UTF("注册失败!").c_str());
		ClientSocket::getIns()->close();
	}
	else if(err==2){
		log("%s", XXIconv::GBK2UTF("用户已存在!").c_str());
		ClientSocket::getIns()->close();
	}
}

void LoginInfo::SendCWXLogin(string code, string token){
	CWXLogin cl;
	cl.set_code(code);
	cl.set_token(token);
	XXEventDispatcher::getIns()->addListener(cl.cmd(), this, Event_Handler(LoginInfo::HandlerSWXLogin));
	ClientSocket::getIns()->sendMsg(cl.cmd(), &cl);
}

void LoginInfo::HandlerSWXLogin(ccEvent *event){
	SWXLogin cl;
	cl.CopyFrom(*event->msg);
	UserDefault *pUserDefault = UserDefault::sharedUserDefault();
	XXEventDispatcher::getIns()->removeListener(cl.cmd(), this, Event_Handler(LoginInfo::HandlerSWXLogin));
	int err = cl.err();
	if (err == 0){
		m_myinfo = cl.info();
		string token = cl.token();
		string tk = pUserDefault->getStringForKey("token", "");
		if (tk.compare(token) != 0){
			pUserDefault->setStringForKey("token", token);
		}
		log("%s", XXIconv::GBK2UTF("微信登录成功!").c_str());
		LoginMainLayer *p = GameControl::getIns()->getLoginMainLayer();
		if (p){
			Scene *scene = LoadingLayer::createScene(2);
			GameControl::getIns()->replaceScene(scene);
		}
	}
	else{
		log("%s", XXIconv::GBK2UTF("微信登录失败!").c_str());
		ClientSocket::getIns()->close();
		pUserDefault->setStringForKey("token", "");
		YLJni::WeixinLogin();
	}
}

void LoginInfo::SendCPing(){
	m_pingcount++;
	CPing cl;
	XXEventDispatcher::getIns()->addListener(cl.cmd(), this, Event_Handler(LoginInfo::HandlerSPing));
	ClientSocket::getIns()->sendMsg(cl.cmd(), &cl);
}

void LoginInfo::HandlerSPing(ccEvent *event){
	m_pingcount = 0;
	SPing cl;
	cl.CopyFrom(*event->msg);
	XXEventDispatcher::getIns()->removeListener(cl.cmd(), this, Event_Handler(LoginInfo::HandlerSPing));
}

void LoginInfo::setTime(){
	m_lasttime = GameDataSet::getTime();
}

void LoginInfo::update(float dt){
	time_t t = GameDataSet::getTime();
	if (m_lasttime!=0&&t - m_lasttime >= 13){
		m_lasttime=t;
		SendCPing();
	}
	if (m_pingcount >= 4 && m_lasttime!=0&& t - m_lasttime >= 0){
		log("pingocunt[%d]--t[%ld]---lasttime[%ld]",m_pingcount,t,m_lasttime);
		m_lasttime = t;
		m_pingcount = 0;
		//判定客户端已经与服务器端断开
		ClientSocket::getIns()->close();
	}
}