#ifndef __XXEventDispatcher_SCENE_H__
#define __XXEventDispatcher_SCENE_H__

#include "AppMacros.h"





class CallList{
public:
	int cmd;
	Object *obj;
	EventHandler handler;
	int m_count;
};

//typedef std::vector<CallList *> CallList_Vec;

class XXEventDispatcher : public Object
{
public:
	XXEventDispatcher();
	~XXEventDispatcher();
	
	static XXEventDispatcher *getIns();
	bool init();
	
	void addListener(int cmd, Object *target, EventHandler handler);//添加监听
	void removeListener(int cmd, Object *target, EventHandler handler);//移除监听
	void removeAllKistener();
	void disEventDispatcher(ccEvent *event);
	
	void registerProto(int cmd,string tname);
	string getProtoName(int cmd);
	
private:
	void EventPathch();
private:
	static XXEventDispatcher* m_ins;
	std::map<int, CallList *> m_eventLists;
	std::vector<ccEvent *> m_Events;
	map<int, string> m_protos;
	bool m_lock;
private:

};

#endif 