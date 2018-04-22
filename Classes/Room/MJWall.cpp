#include "MJWall.h"
#include "GameControl.h"
#include "GameDataSet.h"
#include "ClientSocket.h"
#include "LoginScene.h"
#include "LoginInfo.h"


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
	sprintf(buff, "mjwall%d.json", pos);
	m_RootLayer =RootRegister::getIns()->getWidget(buff);
	this->addChild(m_RootLayer);
	for (int i = 0; i < MAXWALLCOUNT; i++){
		sprintf(buff,"lp%d",i+1);
		m_imgwall[i] = (ImageView *)GameDataSet::getLayout(m_RootLayer,buff);
	}
	resetCard();
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

void MJWall::PopCard(int index){

}

void MJWall::cutCard(int mindice, int maxdice){

}