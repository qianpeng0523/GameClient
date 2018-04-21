
#ifndef __ExpressConfig__
#define __ExpressConfig__

#include "cocos2d.h"
#include "tinyxml2/tinyxml2.h"

using namespace cocos2d;
using namespace std;
using namespace tinyxml2;

struct ExpressItem:public Object
{
	int id;//表情id
	string file;//表情静态文件
	int count;//表情动画总共多少张
	string name;//表情名称
	string anifile;//动画文件
};

class ExpressConfig:public Object
{
public:
	ExpressConfig();
	~ExpressConfig();
	static ExpressConfig* shareExpressConfig();
	bool init();
	void readXML();
	
	Dictionary* getDict()
	{
		return m_dict;
	}

	ExpressItem *getExpressItemById(int id);
	ExpressItem *getExpressItemByName(string name);
	int getExpressItemCount(){
		return m_dict->count();
	}
public:
	static ExpressConfig *m_shareExpressConfig;
private:
	Dictionary *m_dict;
};

#endif 
