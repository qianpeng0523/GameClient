#include "ChatRecord.h"
#include "SimpleAudioEngine.h"
#include "AppMacros.h"
#include "Adaptation.h"
#include "GameControl.h"
#include "GameDataSet.h"
#include "LoginScene.h"
#include "YuYinConfig.h"
#include "RootRegister.h"
#include "LoginInfo.h"

USING_NS_CC;
ChatRecord *ChatRecord::m_ins = NULL;
ChatRecord::ChatRecord(){
	m_index = 0;
	string tt = getFile();
	m_pChatRD=Read(tt);
	m_lastfilename = tt;
}

ChatRecord::~ChatRecord(){
	CC_SAFE_DELETE(m_ins);
}

bool ChatRecord::init()
{
	
    return true;
}

ChatRecord *ChatRecord::getIns(){
	if (!m_ins){
		m_ins = new ChatRecord();
		m_ins->init();
	}
	return m_ins;
}

void ChatRecord::PushChat(string uid, string content){
	string time = GameDataSet::getLocalTime();
	ChatRD *p = new ChatRD();
	p->_uid = uid;
	p->_time = time;
	p->_content = content;
	PushChatRD(p);
	Write(uid, content, time);
}

void ChatRecord::PushChatRD(ChatRD *p){
	m_pChatRD.push_back(p);
}

void ChatRecord::Write(string uid, string content, string time){
	string tt = "<?xml version=\"1.0\" encoding=\"UTF - 8\" standalone=\"yes\"?>\n";
	string lastfilename = getFile();
	char buff[500];
	sprintf(buff, "<item uid=\"%s\" content=\"%s\" time=\"%s\"/>\n", uid.c_str(), content.c_str(), time.c_str());
	FileUtils *pFileUtils = FileUtils::sharedFileUtils();
	bool isexit = pFileUtils->isFileExist(lastfilename);
	if (m_lastfilename.compare(lastfilename) != 0){
		clearChatRD(m_pChatRD);
		m_lastfilename = lastfilename;
	}
	string tp;
	if (!isexit){
		tp = tt+buff;
	}
	else{
		tp = buff;
	}
	FILE *fp = fopen(m_lastfilename.c_str(), "a+");
	fwrite(tp.c_str(), tp.length(), 1, fp);
	fclose(fp);
}

void ChatRecord::clearChatRD(vector<ChatRD *> &vec){
	auto itr = vec.begin();
	for (itr; itr != vec.end();){
		ChatRD *p = *itr;
		delete p;
		p = NULL;
		itr = vec.erase(itr);
	}
}

vector<ChatRD *> ChatRecord::Read(string file){
	if (file.empty()){
		return m_pChatRD;
	}
	else{
		if (file.compare(m_lastfilename) == 0){
			return m_pChatRD;
		}
		else{
			readXML(file);
			return m_pChatRD1;
		}
	}
}

string ChatRecord::getFile(){
	string uid = LoginInfo::getIns()->getUID();
	string file = FileUtils::sharedFileUtils()->getWritablePath()+"CHAT"+uid;
	file += GameDataSet::getLocalTimeDay() + ".INFO";
	return file;
}


void ChatRecord::readXML(string file){
	clearChatRD(m_pChatRD1);
	ssize_t size;
	tinyxml2::XMLDocument xmlDoc;
	char *xmlFileContent = (char*)CCFileUtils::sharedFileUtils()->getFileData(file, "rb", &size);

	xmlDoc.Parse(xmlFileContent, size);

	XMLElement *xmlNode = xmlDoc.RootElement();
	int index = 0;
	while (xmlNode){
		ChatRD *pChatRD = new ChatRD();
		pChatRD->_uid = xmlNode->Attribute("uid");
		pChatRD->_time = xmlNode->Attribute("time");
		pChatRD->_content = xmlNode->Attribute("content");

		m_pChatRD1.push_back(pChatRD);
		xmlNode = xmlNode->NextSiblingElement();
	}

	//释放内存
	delete[] xmlFileContent;
}

vector<ChatRD *> ChatRecord::getChat(int index){
	time_t t1 = GameDataSet::getTime();
	time_t subt = 24*60*60*index;
	t1 = t1-subt;
	string time = GameDataSet::getLocalTimeDay(t1);
	log("time:%s",time.c_str());
	string uid = LoginInfo::getIns()->getUID();
	string file = FileUtils::sharedFileUtils()->getWritablePath() + "CHAT" + uid+time+".INFO";
	return Read(file);
}