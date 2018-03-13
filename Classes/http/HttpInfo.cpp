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

#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include <ws2tcpip.h>
#else
#include<netdb.h>
#endif

USING_NS_CC;
using namespace cocos2d_xx;

#define DECKEY "FQ6M1w0GswdKkTuZWcFmM1rU3bDB/CTiw+KrONdCPOg"

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


int HttpInfo::aes_decrypt(char* in, int inlen, char* key, char* out)
{
	if (!in || !key || !out) return 0;
	unsigned char *iv = new unsigned char[AES_BLOCK_SIZE];
	memcpy(iv, key, AES_BLOCK_SIZE);

	AES_KEY aes;
	if (AES_set_encrypt_key((unsigned char*)key, 128, &aes) < 0)
	{
		return 0;
	}

	int num = 0, en_len = 0;
	AES_cfb128_encrypt((unsigned char*)in, (unsigned char*)out, inlen, &aes, iv, &num, AES_DECRYPT);

	return num;

}

int HttpInfo::aes_encrypt(char* in, int inlen, char* key, char* out)
{
	if (!in || !key || !out) return 0;
	unsigned char *iv = new unsigned char[AES_BLOCK_SIZE];
	memcpy(iv, key, AES_BLOCK_SIZE);
	AES_KEY aes;
	if (AES_set_encrypt_key((unsigned char*)key, 128, &aes) < 0)
	{
		return 0;
	}

	int num = 0, en_len = 0;
	AES_cfb128_encrypt((unsigned char*)in, (unsigned char*)out, inlen, &aes, iv, &num, AES_ENCRYPT);

	return num;

}


void HttpInfo::requestGateIPAndPort(){
	string url = sqlhttp;
	YMSocketData sd;
	sd["cmd"] = 0x0B;
	char buff[4096];
	int sz = 0;
	sd.serializer(buff, &sz);
	buff[sz] = '\0';

	url += buff;
	XXHttpRequest::getIns()->getServerDataFromUrl(url, httpresponse_selector(HttpInfo::GateIPAndPortCallBack));
}

void HttpInfo::GateIPAndPortCallBack(HttpClient* client, HttpResponse* response){
	int sz = 0;
	string str = XXHttpRequest::getIns()->getdata(response, sz);
	YMSocketData sd = XXHttpRequest::getIns()->getSocketDataByStr(str,sz);
	HttpInfo *pHttpInfo = HttpInfo::getIns();
	int err = sd["err"].asInt();
	if (err == 0){
		pHttpInfo->m_port = sd["serverport"].asInt();
		printf("\n/************************************************/\n");
		std::cout << "socket start:" << pHttpInfo->m_ip << pHttpInfo->m_port << std::endl;
		printf("/************************************************/\n");
		pHttpInfo->m_ip = sd["serverip"].asString();
		ClientSocket::getIns()->connect(pHttpInfo->m_ip.c_str(), pHttpInfo->m_port);
	}
	else{
		printf("未获取到数据\n");
	}
}

string HttpInfo::encryptStringFromString(string in, int sz){
	char *out = new char[4096];
	int num = aes_encrypt((char *)in.c_str(), sz, DECKEY, out);
	out[sz + num] = '\0';
	string ss = out;
	int len = ss.length();
	delete out;
	return ss;
}

string HttpInfo::decryptStringFromString(string in, int sz){
	char *out = new char[4096];
	int nn = aes_decrypt((char *)in.c_str(), sz, DECKEY, out);
	out[sz + nn] = '\0';
	string ss = out;
	int len = ss.length();
	delete out;
	return ss;
}