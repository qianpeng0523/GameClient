#include "JsonRegisterConfig.h"

JsonRegisterConfig *JsonRegisterConfig::m_shareJsonRegisterConfig=NULL;
JsonRegisterConfig::JsonRegisterConfig()
{
	
}

JsonRegisterConfig::~JsonRegisterConfig(){
	
}

JsonRegisterConfig* JsonRegisterConfig::shareJsonRegisterConfig(){
	if (!m_shareJsonRegisterConfig){
		m_shareJsonRegisterConfig = new JsonRegisterConfig();
		m_shareJsonRegisterConfig->init();
	}
	return m_shareJsonRegisterConfig;
}

bool JsonRegisterConfig::init()
{
	
	readXML();
    return true;
}

void JsonRegisterConfig::readXML(){
	ssize_t size;
	tinyxml2::XMLDocument xmlDoc;
	char *xmlFileContent = (char*)CCFileUtils::sharedFileUtils()->getFileData("config/jsonregister.xml", "rb", &size);

	xmlDoc.Parse(xmlFileContent, size);

	XMLElement *xmlNode = xmlDoc.RootElement();
	if (xmlNode != NULL) {
		XMLElement *currNode = xmlNode->FirstChildElement();
		while (currNode){
			string jsonname = currNode->Attribute("json");
			int count = currNode->IntAttribute("count");
			RegisterItem *item = new RegisterItem();
			item->_jsonname = jsonname;
			item->_count = count;
			item->_type = currNode->IntAttribute("type");
			m_vecs.push_back(item);
			currNode = currNode->NextSiblingElement();
		}
	}

	//释放内存
	delete[] xmlFileContent;
}

int JsonRegisterConfig::getJsonSize(int type){
	int sz = 0;
	for (int i = 0; i < m_vecs.size(); i++){
		RegisterItem *p = m_vecs.at(i);
		if (p->_type == type){
			sz += p->_count;
		}
	}
	return sz;
}