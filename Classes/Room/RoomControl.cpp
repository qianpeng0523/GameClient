#include "RoomControl.h"
#include "AppMacros.h"
#include "GameHead.h"
#include "MJWall.h"
#include "MJGameScene.h"
#include "GameControl.h"
#include "LoginInfo.h"

RoomControl *RoomControl::m_shareRoomControl=NULL;
RoomControl::RoomControl()
{
	reset();
}

RoomControl::~RoomControl(){
	
}

RoomControl* RoomControl::shareRoomControl(){
	if (!m_shareRoomControl){
		m_shareRoomControl = new RoomControl();
		m_shareRoomControl->init();
	}
	return m_shareRoomControl;
}

bool RoomControl::init()
{
	
    return true;
}

void RoomControl::reset(){
	m_frontindex = 0;
	m_backindex = 0;
	m_frontdata._dirindex = 0;
	m_frontdata._index = 0;
	m_backdata._dirindex = 0;
	m_backdata._index = 0;
	m_zhuangpos = 0;
	m_isend = false;
}

void RoomControl::cutCard(int mindice, int maxdice){
	int count = mindice + maxdice;
	int index = (count - 1 + m_zhuangindex) % 4;
	if (index == m_zhuangindex){
		index += 2;
		index %= 4;
	}
	m_frontdata._dirindex = index;
	m_frontdata._index = mindice * 2 + 1;
	m_backdata._dirindex = m_frontdata._dirindex;
	m_backdata._index = m_frontdata._index - 2;
}

void RoomControl::setZhuang(int zhuang){
	m_zhuangpos = zhuang;
	m_zhuangindex = GameHead::changePos(zhuang);
}

void RoomControl::PopCard(bool isfront){
	if (!m_isend){
		isfront ? (m_frontindex++) : (m_backindex++);
		if (isfront){
			m_frontdata._index++;
			if (m_frontdata._index > MAXWALLCOUNT){
				m_frontdata._index = 1;
				m_frontdata._dirindex++;
				m_frontdata._dirindex = m_frontdata._dirindex % 4;
			}
		}
		else{ 
			int d = m_backdata._index % 2;
			if (d == 1){
				m_backdata._index++;
			}
			else{
				m_backdata._index -= 3;
				if (m_backdata._index < 0){
					m_backdata._index += 30;
					m_backdata._dirindex--;
					m_backdata._dirindex = (m_backdata._dirindex + 4) % 4;
				}
			}

		}

		int count = m_frontindex + m_backindex;
		if (count >= MAXWALLCOUNT * 4){
			//没牌了
			m_isend = true;
		}
		
	}
	else{
		log("end!!!!!!");
		log("/**************************************/");
	}
}

void RoomControl::getWallData(bool isfront){
	MJWallData wd = isfront ? m_frontdata : m_backdata;
	MJGameScene *p = GameControl::getIns()->getMJGameScene();
	if (p){
		p->setMJWall(wd._dirindex, wd._index,isfront);
	}
	PopCard(isfront);
}

void RoomControl::PushRoomUser(RoomUser user){
	string uid = user.userid();
	if (m_roomusers.find(uid) != m_roomusers.end()){
		m_roomusers.at(uid) = user;
	}
	else{
		m_roomusers.insert(make_pair(uid, user));
	}
	UserBase ubase = LoginInfo::getIns()->getMyUserBase();
	if (ubase.userid().compare(uid) == 0){
		m_minepos = user.position();
		MJGameScene *p = GameControl::getIns()->getMJGameScene();
		if (p){
			p->setMyPosition(m_minepos);
		}
	}
}

void RoomControl::setMyPosition(int pos){
	m_minepos = pos;
	MJGameScene *p = GameControl::getIns()->getMJGameScene();
	if (p){
		p->setMyPosition(m_minepos);
	}
}