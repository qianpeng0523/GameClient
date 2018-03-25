
#ifndef __JsonRegisterConfig__
#define __JsonRegisterConfig__

#include "cocos2d.h"
#include "tinyxml2/tinyxml2.h"
#include "AppMacros.h"
USING_NS_CC;
using namespace std;
using namespace tinyxml2;

struct RegisterItem
{
	string _jsonname;
	int _count;
	int _type;
};

class JsonRegisterConfig:public Object
{
public:
	JsonRegisterConfig();
	~JsonRegisterConfig();
	static JsonRegisterConfig* shareJsonRegisterConfig();
	bool init();
	void readXML();
	vector<RegisterItem *> getAll(){
		return m_vecs;
	}
	int getJsonSize(int type);
private:
	static JsonRegisterConfig *m_shareJsonRegisterConfig;
	vector<RegisterItem *>m_vecs;
};

#endif 
