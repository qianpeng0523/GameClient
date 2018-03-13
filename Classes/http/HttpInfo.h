#ifndef __HttpInfo_SCENE_H__
#define __HttpInfo_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "AppMacros.h"
#include "XXHttpRequest.h"
#include "YMSocketData.h"

using namespace cocos2d;
using namespace ui;
using namespace std;


class HttpInfo:public Ref
{
public:
	HttpInfo();
	~HttpInfo();
    virtual bool init();
	static HttpInfo *getIns();
	
	void requestGateIPAndPort();
	void GateIPAndPortCallBack(HttpClient* client, HttpResponse* response);

	int aes_encrypt(char* in, int inlen, char* key, char* out);
	int aes_decrypt(char* in, int inlen, char* key, char* out);
	
	void update(float dt);
	void openUpdate();
	void closeUpdate();
private:
	
	string encryptStringFromString(string in, int sz);
	string decryptStringFromString(string in, int sz);
public:
	static HttpInfo *m_Ins;
	bool m_isopen;
	string m_ip;
	int m_port;
};

#endif 