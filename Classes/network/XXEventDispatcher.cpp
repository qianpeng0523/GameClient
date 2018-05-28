#include "XXEventDispatcher.h"

XXEventDispatcher* XXEventDispatcher::m_ins = NULL;

XXEventDispatcher::XXEventDispatcher(){
	m_lock = false;
}

XXEventDispatcher::~XXEventDispatcher(){
	
}

bool XXEventDispatcher::init()
{
	
    return true;
}

XXEventDispatcher *XXEventDispatcher::getIns(){
	if (!m_ins){
		m_ins = new XXEventDispatcher();
		m_ins->init();
	}
	return m_ins;
}

void XXEventDispatcher::addListener(int cmd, Object *target, EventHandler handler){
	if (m_eventLists.find(cmd) == m_eventLists.end()){
		CallList *clist = new CallList();
		clist->cmd = cmd;
		clist->obj = target;
		clist->handler = handler;
		clist->m_count = 1;
		m_eventLists.insert(make_pair(cmd, clist));
	}
	else{
		CallList *clist = m_eventLists.at(cmd);
		clist->m_count++;
	}
}

void XXEventDispatcher::removeListener(int cmd, Object *target, EventHandler handler){
	if (m_eventLists.find(cmd) != m_eventLists.end()){
		CallList *clist = m_eventLists.at(cmd);
		if (clist && clist->obj == target && clist->handler == handler){
			if (clist->m_count <= 0){
				delete clist;
				clist = NULL;
				m_eventLists.erase(m_eventLists.find(cmd));
			}
			else{
				clist->m_count--;
			}
		}
	}
	
}

void XXEventDispatcher::removeAllKistener(){
	auto eitr = m_eventLists.begin();
	while (eitr!=m_eventLists.end()){
		CallList *clist = eitr->second;
		delete clist;
		eitr= m_eventLists.erase(eitr);
	}
}

void XXEventDispatcher::disEventDispatcher(ccEvent *event){
	if (event&&event->cmd > 0){
		m_Events.push_back(event);
		if (!m_lock){
			EventPathch();
			
		}
	}
}

void XXEventDispatcher::EventPathch(){
	Director::getInstance()->getScheduler()->performFunctionInCocosThread([&]()
	{
		m_lock = true;
		while (!m_Events.empty()){
			auto itr = m_Events.begin();
			if (itr != m_Events.end()){
				ccEvent *event = *itr;
				int cmd = event->cmd;
				if (m_eventLists.find(cmd) != m_eventLists.end()){
					CallList *clist = m_eventLists.at(cmd);
					if (clist && clist->obj && clist->handler){
						(clist->obj->*clist->handler)(event);
					}
				}
				m_Events.erase(itr);
				delete event;
			}
		}
		m_lock = false;
	});
}

void XXEventDispatcher::registerProto(int cmd, string tname){
	if (m_protos.find(cmd) == m_protos.end()){
		m_protos.insert(make_pair(cmd,tname));
	}
}

string XXEventDispatcher::getProtoName(int cmd){
	if (m_protos.find(cmd) != m_protos.end()){
		return m_protos.at(cmd);
	}
	return "";
}