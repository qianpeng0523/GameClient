#ifndef __RootRegister_SCENE_H__
#define __RootRegister_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "LoginLayer.h"

using namespace cocos2d;
using namespace ui;
using namespace std;

struct LayoutItem
{
	LayoutItem(){
		_user = false;
		_index = 0;
		_layout = NULL;
	}
	Layout *_layout;
	bool _user;
	string _jsonname;
	int _type;
	int _count;
	int _index;
};

class RootRegister : public CCObject
{
public:
	RootRegister();
	~RootRegister();
    virtual bool init();
    CREATE_FUNC(RootRegister);
	static RootRegister* getIns();
	
	void RegisteJson(string jsonname, int count, int type);
	Layout *getWidget(string jsonname);
	void resetWidget(string jsonname);
	void resetWidget(Layout *rootlayout);

	void loadJson(int type);
	float getPercent(){
		return m_per;
	}
	void initPercent(){
		m_per = 0;
		m_count = 0;
		m_nowpLayoutItem = NULL;
		m_itr = m_dict.begin();
	}
	void CallBack(Node *node,void *data);
	LayoutItem * FindNext(LayoutItem *p);
public:
	
private:
	static RootRegister *m_ins;
	map<string, vector<LayoutItem *>>m_dict;
	float m_per;
	int m_count;
	LayoutItem *m_nowpLayoutItem;
	map<string, vector<LayoutItem *>>::iterator m_itr;
};

#endif // __RootRegister_SCENE_H__
