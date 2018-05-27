#include "MainChatRecord.h"
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
MainChatRecord *MainChatRecord::m_ins = NULL;
MainChatRecord::MainChatRecord(){
	string tt = getFile();
	m_pChatRD=Read();
}

MainChatRecord::~MainChatRecord(){
	CC_SAFE_DELETE(m_ins);
}

bool MainChatRecord::init()
{
	
    return true;
}

MainChatRecord *MainChatRecord::getIns(){
	if (!m_ins){
		m_ins = new MainChatRecord();
		m_ins->init();
	}
	return m_ins;
}

void MainChatRecord::PushChat(FriendChat fc){
	FriendChat *fc1 = (FriendChat *)ccEvent::create_message(fc.GetTypeName());
	fc1->CopyFrom(fc);
	PushChatRD(fc1);
	Write(fc.uid(), fc.content(), fc.time(),fc.uname());
}

void MainChatRecord::PushChatRD(FriendChat *p){
	string uid = p->uid();
	if (m_pChatRD.find(uid) != m_pChatRD.end()){
		auto vec = m_pChatRD.at(uid);
		vec.push_back(p);
		m_pChatRD.at(uid) = vec;
	}
	else{
		vector<FriendChat *> vec;
		vec.push_back(p);
		m_pChatRD.insert(make_pair(uid, vec));
	}
}

void MainChatRecord::Write(string uid, string content, string time,string uname){
	string tt = "<?xml version=\"1.0\" encoding=\"UTF - 8\" standalone=\"yes\"?>\n";
	string file = getFile();
	char buff[500];
	sprintf(buff, "<item uid=\"%s\" content=\"%s\" time=\"%s\" uname=\"%s\"/>\n", uid.c_str(), content.c_str(), time.c_str(),uname.c_str());
	FileUtils *pFileUtils = FileUtils::sharedFileUtils();
	bool isexit = pFileUtils->isFileExist(file);
	string tp;
	if (!isexit){
		tp = tt+buff;
	}
	else{
		tp = buff;
	}
	FILE *fp = fopen(file.c_str(), "a+");
	fwrite(tp.c_str(), tp.length(), 1, fp);
	fclose(fp);
}

void MainChatRecord::clearChatRD(string uid, vector<FriendChat *> &vec){
	auto itr = vec.begin();
	for (itr; itr != vec.end();){
		FriendChat *p = *itr;
		delete p;
		p = NULL;
		itr = vec.erase(itr);
	}
}

void MainChatRecord::clearChatRD(map<string, vector<FriendChat *>> &maps){
	auto itr = maps.begin();
	for (itr; itr != maps.end();){
		string uid = itr->first;
		vector<FriendChat *> vec = itr->second;
		clearChatRD(uid,vec);
		itr=maps.erase(itr);
	}
}

map<string, vector<FriendChat *>> MainChatRecord::Read(){
	if (!m_pChatRD.empty()){
		return m_pChatRD;
	}
	readXML();
	return m_pChatRD;
}

string MainChatRecord::getFile(){
	string uid = LoginInfo::getIns()->getUID();
	string file = FileUtils::sharedFileUtils()->getWritablePath()+"FRIENDCHAT"+uid+".INFO";
	return file;
}


void MainChatRecord::readXML(){
	clearChatRD(m_pChatRD);
	ssize_t size;
	tinyxml2::XMLDocument xmlDoc;
	char *xmlFileContent = (char*)CCFileUtils::sharedFileUtils()->getFileData(getFile(), "rb", &size);
	
	xmlDoc.Parse(xmlFileContent, size);
	
	XMLElement *xmlNode = xmlDoc.RootElement();
	
	int index = 0;
	FriendChat fc;
	
	while (xmlNode){
		FriendChat *pChatRD = (FriendChat *)ccEvent::create_message(fc.GetTypeName());
		pChatRD->set_uid(xmlNode->Attribute("uid"));
		pChatRD->set_time(xmlNode->Attribute("time"));
		pChatRD->set_content(xmlNode->Attribute("content"));
		pChatRD->set_uname(xmlNode->Attribute("uname"));
		PushChatRD(pChatRD);
		xmlNode = xmlNode->NextSiblingElement();
	}
	
	//释放内存
	delete[] xmlFileContent;
}

vector<FriendChat *> MainChatRecord::getChat(string uid){
	if (m_pChatRD.find(uid)!=m_pChatRD.end()){
		return m_pChatRD.at(uid);
	}
	vector<FriendChat *> vec;
	return vec;
}