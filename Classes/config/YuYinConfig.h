
#ifndef __YuYinConfig__
#define __YuYinConfig__

#include "cocos2d.h"
#include "tinyxml2/tinyxml2.h"

USING_NS_CC;
using namespace std;
using namespace tinyxml2;

struct YuYinItem:public Object
{
	int id;
	string name;
	string content;
};

class YuYinConfig:public Object
{
public:
	YuYinConfig();
	~YuYinConfig();
	static YuYinConfig* shareYuYinConfig();
	bool init();
	void readXML();
	
	Dictionary* getDict()
	{
		return m_dict;
	}

	YuYinItem *getYuYinItemByKey(int id);
private:
	static YuYinConfig *m_shareYuYinConfig;
	Dictionary *m_dict;
};

#endif 
