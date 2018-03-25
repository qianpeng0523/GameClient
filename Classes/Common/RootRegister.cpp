#include "RootRegister.h"
#include "JsonRegisterConfig.h"
#include "GameControl.h"
#include "GameDataSet.h"
RootRegister *RootRegister::m_ins=NULL;

RootRegister::RootRegister(){
	m_per = 0;
	m_count = 0;
	m_nowpLayoutItem = NULL;
}

RootRegister::~RootRegister(){
	
}

bool RootRegister::init()
{
	
    return true;
}

void RootRegister::loadJson(int type){
	m_per = 0;
	m_count = 0;
	m_nowpLayoutItem = NULL;
	vector<RegisterItem *>vec = JsonRegisterConfig::shareJsonRegisterConfig()->getAll();
	for (int i = 0; i < vec.size(); i++){
		RegisterItem *p = vec.at(i);
		if (p->_type == type){
			string jsonname = p->_jsonname;
			RegisteJson(jsonname, p->_count,type);
		}
	}
	m_itr = m_dict.find(m_nowpLayoutItem->_jsonname);
	LoadingLayer *pp = GameControl::getIns()->getLoadingLayer();
	if (pp || type == 0){
		CallBack(pp, m_nowpLayoutItem);
	}
}

RootRegister* RootRegister::getIns(){
	if (!m_ins){
		m_ins = new RootRegister();
		m_ins->init();
	}
	return m_ins;
}

void RootRegister::RegisteJson(string jsonname, int count, int type){
	int sz = JsonRegisterConfig::shareJsonRegisterConfig()->getJsonSize(type);
	vector<LayoutItem *>vec;
	for (int i = 0; i < count; i++){
		LayoutItem *p = new LayoutItem();
		p->_jsonname = jsonname;
		p->_type = type;
		p->_count = count;
		p->_index = i;
		vec.push_back(p);
		if (i == 0 && m_nowpLayoutItem == NULL){
			m_nowpLayoutItem = p;
		}
	}
	m_dict.insert(make_pair(jsonname, vec));
}

LayoutItem *RootRegister::FindNext(LayoutItem *p){
	m_count++;
	int sz = JsonRegisterConfig::shareJsonRegisterConfig()->getJsonSize(p->_type);
	m_per = m_count*1.0 / sz * 100;
	LoadingLayer *pp = GameControl::getIns()->getLoadingLayer();
	if (pp){
		pp->update(0);
	}
	LayoutItem *nowp = NULL;
	if (m_dict.find(p->_jsonname) != m_dict.end()){
		if (p->_index < p->_count - 1){
			nowp = m_dict.at(p->_jsonname).at(p->_index + 1);
		}
		else{
			while (1){
				++m_itr;
				if (m_itr != m_dict.end()){
					if (m_itr->second.at(0)->_type == p->_type){
						break;
					}
				}
				else{
					return nowp;
				}
			}
			if (m_itr != m_dict.end()){
				vector<LayoutItem *>vec = m_itr->second;
				if (vec.size()>0){
					nowp = vec.at(0);
				}
			}
		}
	}
	return nowp;
}

void RootRegister::CallBack(Node *node, void *data){
	LayoutItem *p = (LayoutItem *)data;
	
	if (p->_layout){
		FindNext(p);
		return;
	}
	
	string jsonname = p->_jsonname;
	Layout *RootLayer = (Layout *)GUIReader::shareReader()->widgetFromJsonFile(jsonname.c_str());
	RootLayer->retain();
	p->_layout = RootLayer;
	LayoutItem *nowp=FindNext(p);
	if (nowp){
		node->runAction(Sequence::create(DelayTime::create(0.01),
			CCCallFuncND::create(this, callfuncND_selector(RootRegister::CallBack), nowp)
			, NULL));
	}
}

Layout *RootRegister::getWidget(string jsonname){
	if (m_dict.find(jsonname) != m_dict.end()){
		vector<LayoutItem *>vec=m_dict.at(jsonname);
		for (int i = 0; i < vec.size(); i++){
			LayoutItem *p = vec.at(i);
			if (!p->_user){
				p->_user = true;
				return p->_layout;
			}
		}
		Layout *RootLayer = (Layout *)GUIReader::shareReader()->widgetFromJsonFile(jsonname.c_str());
		return RootLayer;
	}
	else{
		Layout *RootLayer = (Layout *)GUIReader::shareReader()->widgetFromJsonFile(jsonname.c_str());
		return RootLayer;
	}
}

void RootRegister::resetWidget(string jsonname){
	if (m_dict.find(jsonname) != m_dict.end()){
		vector<LayoutItem *>vec = m_dict.at(jsonname);
		for (int i = 0; i < vec.size(); i++){
			LayoutItem *p = vec.at(i);
			if (p->_user){
				p->_user = false;
			}
			if (p->_layout&&p->_layout->getParent()){
				p->_layout->removeFromParent();
			}
		}
	}
}

void RootRegister::resetWidget(Layout *rootlayout){
	map<string, vector<LayoutItem *>>::iterator itr= m_dict.begin();
	for (itr; itr != m_dict.end();itr++){
		vector<LayoutItem *>vec = itr->second;
		for (int i = 0; i < vec.size(); i++){
			LayoutItem *p = vec.at(i);
			if (p->_layout == rootlayout){
				p->_user = false;
				p->_layout->removeFromParent();
			}
		}
	}
}