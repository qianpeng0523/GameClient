#include "ActionConfig.h"
#include "AppMacros.h"

ActionConfig *ActionConfig::m_shareActionConfig=NULL;
ActionConfig::ActionConfig()
{
	
}

ActionConfig::~ActionConfig(){
	auto itr = m_actmap.begin();
	for (itr; itr != m_actmap.end();){
		vector<ActionItem *>vec = itr->second;
		auto it = vec.begin();
		for (it; it != vec.end();){
			delete *it;
			it = vec.erase(it);
		}
		if (vec.empty()){
			itr = m_actmap.erase(itr);
		}
		else{
			itr++;
		}
	}
}

ActionConfig* ActionConfig::shareActionConfig(){
	if (!m_shareActionConfig){
		m_shareActionConfig = new ActionConfig();
		m_shareActionConfig->init();
	}
	return m_shareActionConfig;
}

bool ActionConfig::init()
{
	
	readXML();
    return true;
}

void ActionConfig::readXML(){
	ssize_t size;
	tinyxml2::XMLDocument xmlDoc;
	char *xmlFileContent = (char*)CCFileUtils::sharedFileUtils()->getFileData("config/action.xml", "rb", &size);

	xmlDoc.Parse(xmlFileContent, size);

	XMLElement *xmlNode = xmlDoc.RootElement();
	if (xmlNode != NULL) {
		XMLElement *currNode = xmlNode->FirstChildElement();
		while (currNode){
			ActionItem *pActionItem = new ActionItem();
			pActionItem->_id = currNode->IntAttribute("id");
			pActionItem->_name = currNode->Attribute("name");
			pActionItem->_file = currNode->Attribute("file");
			pActionItem->_count = currNode->IntAttribute("count");
			pActionItem->_begin = currNode->IntAttribute("begin");
			pActionItem->_type = currNode->IntAttribute("type");
			pActionItem->_scenetype = currNode->IntAttribute("scenetype");
			pActionItem->_dur = currNode->FloatAttribute("dur");
			pActionItem->_time = currNode->IntAttribute("time");
			auto itr = m_actmap.find(pActionItem->_scenetype);
			if (itr == m_actmap.end()){
				vector<ActionItem*> vec;
				vec.push_back(pActionItem);
				m_actmap.insert(make_pair(pActionItem->_scenetype, vec));
			}
			else{
				vector<ActionItem*> vec = itr->second;
				vec.push_back(pActionItem);
				m_actmap.at(pActionItem->_scenetype) = vec;
			}

			currNode = currNode->NextSiblingElement();
		}
	}

	//释放内存
	delete[] xmlFileContent;
}

ActionItem *ActionConfig::getActionItem(string key){
	auto itr = m_actmap.begin();
	for (itr; itr != m_actmap.end();itr++){
		vector<ActionItem*> vec = itr->second;
		auto it = vec.begin();
		for (it; it != vec.end(); it++){
			if ((*it)->_name.compare(key)==0){
				return *it;
			}
		}
	}
	return NULL;
}

vector<ActionItem*> ActionConfig::getActionItems(int type){
	vector<ActionItem*> vec;
	auto itr = m_actmap.find(type);
	if (itr != m_actmap.end()){
		vec = itr->second;
		return vec;
	}
	return vec;
}