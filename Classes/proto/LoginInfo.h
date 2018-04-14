
#ifndef __LoginInfo__
#define __LoginInfo__

#include "AppMacros.h"
#include "ccEvent.h"

enum LOGINTYPE
{
	LOGIN_WX = 0,
	LOGIN_YK   ,
};

class LoginInfo:public Object
{
public:
	LoginInfo();
	~LoginInfo();
	static LoginInfo* getIns();
	bool init();
public:
	void SendCLogin(string uid, string pwd);
	void HandlerSLoginHand(ccEvent *event);

	void SendCRegister(string uid,string pwd,string uname);
	void HandlerSRegister(ccEvent *event);

	////////微信登录
	void SendCWXLogin(string code,string token);
	void HandlerSWXLogin(ccEvent *event);

	UserBase getMyUserBase(){
		return m_myinfo;
	}

	void setMyUserBase(UserBase ub);

	void setWxToken(string token){
		setLoginType(LOGIN_WX);
		m_wxtoken = token;
	}
	string getWXToken(){
		return m_wxtoken;
	}

	void setLoginType(LOGINTYPE type){
		m_logintype = type;
	}
	LOGINTYPE getLoginType(){
		return m_logintype;
	}
private:
	static LoginInfo *m_shareLoginInfo;
	UserBase m_myinfo;
	string m_wxtoken;
	LOGINTYPE m_logintype;
};

#endif 
