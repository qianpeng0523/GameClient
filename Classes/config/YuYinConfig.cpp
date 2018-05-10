#include "YuYinConfig.h"
#include "AppMacros.h"

YuYinConfig *YuYinConfig::m_shareYuYinConfig=NULL;
YuYinConfig::YuYinConfig():
m_dict(NULL)
{
	m_dict = new Dictionary();
}

YuYinConfig::~YuYinConfig(){
	m_dict->removeAllObjects();
	CC_SAFE_DELETE(m_dict);
}

YuYinConfig* YuYinConfig::shareYuYinConfig(){
	if (!m_shareYuYinConfig){
		m_shareYuYinConfig = new YuYinConfig();
		m_shareYuYinConfig->init();
	}
	return m_shareYuYinConfig;
}

bool YuYinConfig::init()
{
	
	readXML();
    return true;
}

void YuYinConfig::readXML(){
	ssize_t size;
	tinyxml2::XMLDocument xmlDoc;
	char *xmlFileContent = (char*)CCFileUtils::sharedFileUtils()->getFileData("config/yuyin.xml", "rb", &size);

	xmlDoc.Parse(xmlFileContent, size);

	XMLElement *xmlNode = xmlDoc.RootElement();
	if (xmlNode != NULL) {
		XMLElement *currNode = xmlNode->FirstChildElement();
		while (currNode){
			YuYinItem *pYuYinItem = new YuYinItem();
			pYuYinItem->id = currNode->IntAttribute("id");
			pYuYinItem->name = currNode->Attribute("name");
			pYuYinItem->content = currNode->Attribute("content");
			
			m_dict->setObject(pYuYinItem, pYuYinItem->name);
			currNode = currNode->NextSiblingElement();
		}
	}

	//释放内存
	delete[] xmlFileContent;
}

YuYinItem *YuYinConfig::getYuYinItemByKey(string name){
	return (YuYinItem *)m_dict->objectForKey(name);
}