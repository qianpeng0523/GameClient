#include "MJWall.h"
#include "GameControl.h"
#include "GameDataSet.h"
#include "ClientSocket.h"
#include "LoginScene.h"
#include "LoginInfo.h"
#include "RoomControl.h"

MJWall::MJWall(){
	
}

MJWall::~MJWall(){
	RootRegister::getIns()->resetWidget(m_RootLayer);
	
}

bool MJWall::init(int pos)
{             
	if (!Layer::init())
    {
        return false;
    }
	m_position = pos;
	m_index = GameHead::changePos(pos);
	char buff[50];
	sprintf(buff, "mjwall%d.json", m_index+1);
	m_RootLayer =RootRegister::getIns()->getWidget(buff);
	this->addChild(m_RootLayer);
	for (int i = 0; i < MAXWALLCOUNT; i++){
		sprintf(buff,"lp%d",i+1);
		m_imgwall[i] = (ImageView *)GameDataSet::getLayout(m_RootLayer, buff);
	}
	
	//resetCard();
    return true;
}

MJWall* MJWall::create(int pos){
	MJWall *p = new MJWall();
	if (p&&p->init(pos)){
		p->autorelease();
	}
	else{
		CC_SAFE_DELETE(p);
	}
	return p;
}

void MJWall::resetCard(){
	for (int i = 0; i < MAXWALLCOUNT; i++){
		m_imgwall[i]->setVisible(false);
	}
}

void MJWall::initCard(){
	for (int i = 0; i < MAXWALLCOUNT; i++){
		m_imgwall[i]->setVisible(true);
	}
}

void MJWall::PopCard(int index){
	if (index < MAXWALLCOUNT){
		if (m_imgwall[index]->isVisible()){
			m_imgwall[index]->setVisible(false);
		}
		else{
			log("all popcard!!!!!!");
			MJGameScene *scene = GameControl::getIns()->getMJGameScene();
			if (scene){
				scene->resetAllWall();
			}
			RoomControl::shareRoomControl()->setEnd(true);
		}
	}
}
