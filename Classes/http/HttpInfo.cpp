#include "HttpInfo.h"
#include "SimpleAudioEngine.h"
#include "AppMacros.h"
#include "XXIconv.h"
#include "LogoLayer.h"
#include "aes.h"
#include "crypto_wrapper.h"
#include "YMSocketDataEvent.h"
#include "ClientSocket.h"
#include "Common.h"
#include "GameControl.h"
#include "GameDataSet.h"
#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include <ws2tcpip.h>
#else
#include<netdb.h>
#endif

USING_NS_CC;




HttpInfo *HttpInfo::m_Ins = NULL;


HttpInfo::HttpInfo(){
	m_isopen = false;
}
HttpInfo::~HttpInfo(){
	
}

bool HttpInfo::init()
{
	
    return true;
}

HttpInfo *HttpInfo::getIns(){
	if (!m_Ins){
		m_Ins = new HttpInfo();
		m_Ins->init();
	}
	return m_Ins;
}



void HttpInfo::aes_decrypt(char* in, int inlen, char* out)
{
	if (!in || !out) return;
	unsigned char *iv = new unsigned char[AES_BLOCK_SIZE];
	memcpy(iv, DECKEY, AES_BLOCK_SIZE);

	AES_KEY aes;
	if (AES_set_encrypt_key((unsigned char*)DECKEY, 128, &aes) < 0)
	{
		return;
	}

	int num = 0;
	AES_cfb128_encrypt((unsigned char*)in, (unsigned char*)out, inlen, &aes, iv, &num, AES_DECRYPT);
	inlen = inlen / AES_BLOCK_SIZE*AES_BLOCK_SIZE;
	out[inlen + num] = '\0';

}

void HttpInfo::aes_encrypt(char* in, int inlen, char* out)
{
	if (!in || !out) return;
	unsigned char *iv = new unsigned char[AES_BLOCK_SIZE];
	memcpy(iv, DECKEY, AES_BLOCK_SIZE);
	AES_KEY aes;
	if (AES_set_encrypt_key((unsigned char*)DECKEY, 128, &aes) < 0)
	{
		return;
	}
	int num = 0;
	AES_cfb128_encrypt((unsigned char*)in, (unsigned char*)out, inlen, &aes, iv, &num, AES_ENCRYPT);
	inlen = inlen / AES_BLOCK_SIZE*AES_BLOCK_SIZE;
	out[inlen + num] = '\0';

}


void HttpInfo::CharPtrToString(string &str, char *buff,int sz){
	int len = str.length();
	str.resize(len+sz);
	for (int i = 0; i < sz;i++){
		str[len + i] = buff[i];
	}
}

void HttpInfo::requestGateIPAndPort(){
	string url = sqlhttp;
	YMSocketData sd;
	sd["cmd"] = 0x0B;
	sd["type"] = 3;
	MD55 md5;
	md5.update("123456");
	string pwd = md5.toString();
	sd["pwd"] = pwd;

	XXHttpRequest::getIns()->postServerDataFromUrl(url,sd, httpresponse_selector(HttpInfo::GateIPAndPortCallBack));
}

void HttpInfo::GateIPAndPortCallBack(HttpClient* client, HttpResponse* response){
	int sz = 0;
	char* str = XXHttpRequest::getIns()->getdata(response, sz);
	char *data = new char[sz + 1];
	HttpInfo::getIns()->aes_decrypt(str,sz,data);
	YMSocketData sd = XXHttpRequest::getIns()->getSocketDataByStr(data,sz);
	delete str;
	delete data;
	HttpInfo *pHttpInfo = HttpInfo::getIns();
	int err = sd["err"].asInt();
	if (err == 0){
		pHttpInfo->m_port = sd["port"].asInt();
		printf("\n/************************************************/\n");
		std::cout << "socket start:" << pHttpInfo->m_ip << pHttpInfo->m_port << std::endl;
		printf("/************************************************/\n");
		pHttpInfo->m_ip =GameDataSet::getHostNameIp(sd["ip"].asString());
		LogoLayer *p = GameControl::getIns()->getLoginLayer();
		if (p){
			p->ShowYKLoginBtn(true);
		}
	}
	else{
		printf("未获取到数据\n");
	}
}