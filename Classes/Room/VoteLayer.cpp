#include "VoteLayer.h"
#include "GameControl.h"
#include "GameDataSet.h"
#include "ClientSocket.h"
#include "LoginScene.h"
#include "LoginInfo.h"
#include "CardsStr.h"
#include "RoomInfo.h"

VoteLayer::VoteLayer(){
	GameControl::getIns()->setVoteLayer(this);
}

VoteLayer::~VoteLayer(){
	RootRegister::getIns()->resetWidget(m_RootLayer);
	if (GameControl::getIns()->getVoteLayer() == this){
		GameControl::getIns()->setVoteLayer(NULL);
	}
}

bool VoteLayer::init()
{             
	if (!Layer::init())
    {
        return false;
    }
	m_RootLayer =RootRegister::getIns()->getWidget("vote.json");
	this->addChild(m_RootLayer);
	
	auto users = RoomInfo::getIns()->getRoomUsers();
	char buff[100];
	for (int i = 0; i < 4; i++){
		if (i == 0){
			sprintf(buff,"%s" ,"disuid");
		}
		else{
			sprintf(buff, "uid%d", i);
		}
		m_texts[i] = (Text*)GameDataSet::getLayout(m_RootLayer,buff);
		m_texts[i]->setVisible(false);
	}
	SDissolveRoom sdr = RoomInfo::getIns()->getSDissolveRoom();
	string disuid = sdr.uid();
	int index = 1;
	auto votes = RoomInfo::getIns()->getSVotes();
	for (auto itr=users.begin(); itr != users.end();itr++){
		string uid = itr->first;
		RoomUser ru = itr->second;
		if (disuid.compare(uid) == 0){
			sprintf(buff, XXIconv::GBK2UTF("【%s】：申请解散房间").c_str(), ru.username().c_str());
			m_texts[0]->setVisible(true);
			m_texts[0]->setText(buff);
			m_uids[0] = uid;
			m_names[0] = ru.username();
		}
		else{
			if (votes.find(uid) != votes.end()){
				auto it = votes.at(uid);
				bool agree = it.agree();
				sprintf(buff, XXIconv::GBK2UTF("【%s】：%s").c_str(), ru.username().c_str(), agree ? XXIconv::GBK2UTF("同意解散").c_str() : XXIconv::GBK2UTF("拒绝解散").c_str());
			}
			else{
				sprintf(buff, XXIconv::GBK2UTF("【%s】：未选择").c_str(), ru.username().c_str());
			}
			m_uids[index] = uid;
			m_texts[index]->setVisible(true);
			m_texts[index]->setText(buff);
			m_names[index] = ru.username();
			index++;
		}
	}
	SEL_TouchEvent selector = toucheventselector(VoteLayer::TouchEvent);
	Button *btn1 = GameDataSet::getButton(m_RootLayer,"ok_btn",selector,this);
	Button *btn2 = GameDataSet::getButton(m_RootLayer, "cancle_btn", selector, this);
	Button *btn3= GameDataSet::getButton(m_RootLayer, "close_btn", selector, this);
	btn3->setVisible(false);
	string myuid = LoginInfo::getIns()->getUID();
	if (myuid.compare(disuid) == 0){
		btn1->setVisible(false);
		btn2->setVisible(false);
	}

	RoomData rd = RoomInfo::getIns()->getRoomData();
	int round = rd.round();
	int left = rd.left();
	bool isbein = RoomInfo::getIns()->isBegin();
	string content = XXIconv::GBK2UTF("房间解散后，房卡不返还，是否确定解散房间？");
	if (!(isbein || round > left)){
		content = XXIconv::GBK2UTF("房间解散后，房卡返还，是否确定解散房间？");
	}
	GameDataSet::setText(m_RootLayer, "tip", content);
	setTime(RoomInfo::getIns()->getTime());

    return true;
}

VoteLayer* VoteLayer::create(){
	VoteLayer *p = new VoteLayer();
	if (p&&p->init()){
		p->autorelease();
	}
	else{
		CC_SAFE_DELETE(p);
	}
	return p;
}

void VoteLayer::TouchEvent(CCObject *obj, TouchEventType type){
	Button *btn = (Button *)obj;
	string name = btn->getName();
	if (type == TOUCH_EVENT_ENDED){
		if (name.compare("close_btn") == 0){
			this->removeFromParentAndCleanup(true);
		}
		else if (name.compare("ok_btn") == 0){
			RoomInfo::getIns()->SendCVote(true);
		}
		else if (name.compare("cancle_btn") == 0){
			RoomInfo::getIns()->SendCVote(false);
		}
	}
}

void VoteLayer::setVote(string uid, bool agree){
	char buff[100];
	for (int i = 1; i < 4; i++){
		string puid = m_uids[i];
		string uname = m_names[i];
		if (puid.compare(uid) == 0){
			sprintf(buff, XXIconv::GBK2UTF("【%s】：%s").c_str(), uname.c_str(), agree ? XXIconv::GBK2UTF("同意解散").c_str() : XXIconv::GBK2UTF("拒绝解散").c_str());
			m_texts[i]->setVisible(true);
			m_texts[i]->setText(buff);
			break;
		}
	}
}

void VoteLayer::setTime(int time){
	int fen = time / 60;
	int miao = time % 60;
	char buff[10];
	sprintf(buff,"%02d",fen);
	GameDataSet::setTextBMFont(m_RootLayer, "BitmapLabel_time1", buff);

	sprintf(buff, "%02d", miao);
	GameDataSet::setTextBMFont(m_RootLayer, "BitmapLabel_time2", buff);
}