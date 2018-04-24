
#ifndef __ActionConfig__
#define __ActionConfig__

#include "cocos2d.h"
#include "tinyxml2/tinyxml2.h"

USING_NS_CC;
using namespace std;
using namespace tinyxml2;

struct ActionItem:public Object
{
	int _id;
	string _name;
	string _file;
	int _count;
	int _begin;
	int _type;
	int _scenetype;
	float _dur;
	int _time;
};

class ActionConfig:public Object
{
public:
	ActionConfig();
	~ActionConfig();
	static ActionConfig* shareActionConfig();
	bool init();
	void readXML();

	ActionItem *getActionItem(string key);
	vector<ActionItem*> getActionItems(int type);
private:
	static ActionConfig *m_shareActionConfig;
	map<int, vector<ActionItem*>>m_actmap;
};

#endif 
