#ifndef __ccEvent_H__
#define __ccEvent_H__

#include "Login.h"
#include "cocos2d.h"


// #pragma comment(lib,"../Server1/Debug/libprotobuf.lib") 
// 
// #pragma comment(lib,"../Server1/Debug/libprotoc.lib") 
using namespace cocos2d;
using namespace std;

class ccEvent :public Ref{
public:
	ccEvent(int pcmd, const char* data, int size);
	int cmd;
	::google::protobuf::Message* msg;
private:
	void parse(const char* data, int size);
public:
	static google::protobuf::Message* create_message(const std::string& type_name);
};

#endif // __ccccEvent_H__
