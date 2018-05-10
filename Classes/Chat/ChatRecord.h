#ifndef __ChatRecord_SCENE_H__
#define __ChatRecord_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Adaptation.h"
#include "XXEventDispatcher.h"
#include "XXHttpRequest.h"
#include "YuYinConfig.h"
#include "BaseLayer.h"

using namespace cocos2d;
using namespace ui;
using namespace std;

struct ChatRD
{
	string _uid;
	string _content;
	string _time;
};

class ChatRecord : public Object
{
public:
	ChatRecord();
	~ChatRecord();
	virtual bool init();
	
	static ChatRecord *getIns();
	void PushChat(string uid,string content);
	vector<ChatRD *> getChat(int index);
private:
	void Write(string uid,string content,string time);
	vector<ChatRD *> Read(string file);
	string getFile();
	void clearChatRD(vector<ChatRD *> &vec);
	void PushChatRD(ChatRD *p);
	void readXML(string file);
private:
	static ChatRecord *m_ins;
	int m_index;
	string m_lastfilename;
	vector<ChatRD *> m_pChatRD;
	vector<ChatRD *> m_pChatRD1;
};

#endif 