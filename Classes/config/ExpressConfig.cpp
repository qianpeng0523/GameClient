#include "ExpressConfig.h"

ExpressConfig *ExpressConfig::m_shareExpressConfig=NULL;
ExpressConfig::ExpressConfig():
m_dict(NULL)
{
	m_dict = new Dictionary();
}

ExpressConfig::~ExpressConfig(){
	m_dict->removeAllObjects();
	CC_SAFE_DELETE(m_dict);
}

ExpressConfig* ExpressConfig::shareExpressConfig(){
	if (!m_shareExpressConfig){
		m_shareExpressConfig = new ExpressConfig();
		m_shareExpressConfig->init();
	}
	return m_shareExpressConfig;
}

bool ExpressConfig::init()
{
	
	readXML();
    return true;
}

void ExpressConfig::readXML(){
	ssize_t size;
	tinyxml2::XMLDocument xmlDoc;
	char *xmlFileContent = (char*)CCFileUtils::sharedFileUtils()->getFileData("config/express.xml", "rb", &size);

	xmlDoc.Parse(xmlFileContent, size);

	XMLElement *xmlNode = xmlDoc.RootElement();
	if (xmlNode != NULL) {
		XMLElement *currNode = xmlNode->FirstChildElement();
		while (currNode){
			ExpressItem *pExpressItem = new ExpressItem();
			pExpressItem->id = currNode->IntAttribute("id");
			pExpressItem->count = currNode->IntAttribute("count");
			pExpressItem->name = currNode->Attribute("name");
			pExpressItem->file = currNode->Attribute("file");
			pExpressItem->anifile = currNode->Attribute("ani");

			m_dict->setObject(pExpressItem, pExpressItem->id);
			currNode = currNode->NextSiblingElement();
		}
	}

	//释放内存
	delete[] xmlFileContent;
}

ExpressItem *ExpressConfig::getExpressItemById(int id){
	return (ExpressItem *)m_dict->objectForKey(id);
}

ExpressItem *ExpressConfig::getExpressItemByName(string name){
	return NULL;
}