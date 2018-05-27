#ifndef __MainChatRecord_SCENE_H__
#define __MainChatRecord_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Adaptation.h"
#include "XXEventDispatcher.h"
#include "XXHttpRequest.h"
#include "YuYinConfig.h"
#include "BaseLayer.h"
#include "AppMacros.h"

using namespace cocos2d;
using namespace ui;
using namespace std;

class MainChatRecord : public Object
{
public:
	MainChatRecord();
	~MainChatRecord();
	virtual bool init();
	
	static MainChatRecord *getIns();
	void PushChat(FriendChat fc);
	vector<FriendChat *> getChat(string uid);
private:
	void Write(string uid, string content, string time, string uname);
	map<string, vector<FriendChat *>> Read();
	string getFile();
	void clearChatRD(string uid,vector<FriendChat *> &vec);
	void clearChatRD(map<string, vector<FriendChat *>> &maps);
	void PushChatRD(FriendChat *p);
	void readXML();
private:
	static MainChatRecord *m_ins;
	map<string,vector<FriendChat *>> m_pChatRD;
};

#endif 