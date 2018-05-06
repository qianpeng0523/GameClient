#include "JoinRoomLayer.h"
#include "GameControl.h"
#include "GameDataSet.h"
#include "ClientSocket.h"
#include "LoginScene.h"
#include "LoginInfo.h"
#include "WebViewCommom.h"
#include "RoomInfo.h"




JoinRoomLayer::JoinRoomLayer(){
	m_index = 0;
	GameControl::getIns()->setJoinRoomLayer(this);
}

JoinRoomLayer::~JoinRoomLayer(){
	RootRegister::getIns()->resetWidget(m_RootLayer);
	if (this == GameControl::getIns()->getJoinRoomLayer()){
		GameControl::getIns()->setJoinRoomLayer(NULL);

	}
}

bool JoinRoomLayer::init()
{             
	if (!Layer::init())
    {
        return false;
    }
	
	m_RootLayer =RootRegister::getIns()->getWidget("privatejoin.json");
	this->addChild(m_RootLayer);

	SEL_TouchEvent selector = toucheventselector(JoinRoomLayer::TouchEvent);
	GameDataSet::getButton(m_RootLayer, "btn", selector, this);
	GameDataSet::getButton(m_RootLayer, "close_btn", selector, this);
	GameDataSet::getButton(m_RootLayer, "btn_del", selector, this);
	GameDataSet::getButton(m_RootLayer, "btn_reput", selector, this);
	char buff[30];
	for (int i = 0; i < 10; i++){
		sprintf(buff,"btn_%d",i);
		GameDataSet::getButton(m_RootLayer, buff,selector,this);
		if (i < 6){
			sprintf(buff, "BitmapLabel_%d", i+1);
			m_number[i] = (TextBMFont *)GameDataSet::getLayout(m_RootLayer,buff);
			m_number[i]->setText("");
		}
	}
    return true;
}

void JoinRoomLayer::TouchEvent(CCObject *obj, TouchEventType type){
	Button *btn = (Button *)obj;
	string name = btn->getName();
	if (type == TOUCH_EVENT_ENDED){
		UserDefault *p = UserDefault::sharedUserDefault();
		if (name.compare("close_btn") == 0){
			this->removeFromParentAndCleanup(true);
		}
		else if (name.compare("btn") == 0){
			//加入
			string number;
			for (int i = 0; i<6; i++){
				string t = m_number[i]->getString();
				if (t.empty()){
					log("%s",XXIconv::GBK2UTF("房间号为6位数").c_str());
					return ;
				}
				number.append(t);
			}
			log("number:%s",number.c_str());
			RoomInfo::getIns()->SendCHMMJEnterRoom(1, number);
		}
		else if (name.compare("btn_del") == 0){
			if (m_index > 0){
				m_number[--m_index]->setText("");
			}
		}
		else if (name.compare("btn_reput") == 0){
			for (int i = 0; i < 6; i++){
				m_number[i]->setText("");
			}
			m_index = 0;
		}
		else if(name.find("btn_")!=-1){
			int ind = name.find("btn_");
			if (m_index<6){
				int index = atoi(name.substr(4, name.length()).c_str());
				char buff[30];
				sprintf(buff, "%d", index);
				m_number[m_index++]->setText(buff);
			}
		}
		
	}
}