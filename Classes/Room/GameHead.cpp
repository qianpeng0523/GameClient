#include "GameHead.h"
#include "GameControl.h"
#include "GameDataSet.h"
#include "ClientSocket.h"
#include "LoginScene.h"
#include "LoginInfo.h"
#include "PhotoDown.h"


int GameHead::m_mimepos = 1;
RoomUser *GameHead::m_users[4] = {NULL};
GameHead::GameHead(){
	memset(m_users, NULL, sizeof(RoomUser *)*4);
}

GameHead::~GameHead(){
	for (int i = 0; i < 4; i++){
		if (m_users[i]){
			delete m_users[i];
			m_users[i] = NULL;
		}
	}
	m_mimepos = 1;
	RootRegister::getIns()->resetWidget(m_RootLayer);
}

bool GameHead::init()
{             
	if (!Layer::init())
    {
        return false;
    }
	
	m_RootLayer =RootRegister::getIns()->getWidget("headlayer.json");
	this->addChild(m_RootLayer);

	SEL_TouchEvent selector = toucheventselector(GameHead::TouchEvent);

	RoomUser ru;
	char buff[50];
	for (int i = 0; i < 4; i++){
		sprintf(buff, "btn%d", i + 1);
		GameDataSet::getButton(m_RootLayer, buff, selector, this);
		sprintf(buff, "head%d", i + 1);
		m_heads[i] = (ImageView *)GameDataSet::getLayout(m_RootLayer,buff);
		sprintf(buff, "headbg%d", i + 1);
		m_headbgs[i] = (ImageView *)GameDataSet::getLayout(m_RootLayer, buff);
		//m_headbgs[i]->setVisible(false);
		sprintf(buff, "BitmapLabel_off%d", i + 1);
		m_texts[i] = (TextBMFont *)GameDataSet::getLayout(m_RootLayer, buff);

		sprintf(buff, "zhuang%d", i + 1);
		m_zhuangs[i] = (ImageView *)GameDataSet::getLayout(m_RootLayer, buff);

		sprintf(buff, "name%d", i + 1);
		m_names[i] = (Text *)GameDataSet::getLayout(m_RootLayer, buff);
		m_names[i]->setFontSize(16);

		sprintf(buff, "BitmapLabel_%d", i + 1);
		m_scores[i] = (TextBMFont *)GameDataSet::getLayout(m_RootLayer, buff);

		
	}
	offLine(0);
	offLine(1);
	offLine(2);
	offLine(3);
	onLine(3);
	setZhuang(2,true);
	setName(1, "name11111111111");
	setName(2, XXIconv::GBK2UTF("名字五个字是吧"));
	setName(3, XXIconv::GBK2UTF("名字五个字是吧"));
	setName(4, "name22222222222");
	setScore(1, 200);
	setScore(2, 20000);
	setScore(3, 20080);
	setScore(4, 200880);
    return true;
}

void GameHead::TouchEvent(CCObject *obj, TouchEventType type){
	Button *btn = (Button *)obj;
	string name = btn->getName();
	if (type == TOUCH_EVENT_ENDED){
		UserDefault *p = UserDefault::sharedUserDefault();
		if (name.compare("btn1") == 0){
			
		}
		else if (name.compare("btn2") == 0){

		}
		else if (name.compare("btn3") == 0){

		}
		else if (name.compare("btn4") == 0){

		}
	}
}

void GameHead::setZhuang(int pos, bool iszhuang){
	int index = changePos(pos);
	for (int i = 0; i < 4; i++){
		if (i == index){
			m_zhuangs[i]->setVisible(iszhuang);
		}
		else{
			m_zhuangs[i]->setVisible(false);
		}
	}
}

void GameHead::setZhuang(string uid, bool iszhuang){
	int index = getPos(uid);
	for (int i = 0; i < 4; i++){
		if (i == index){
			m_zhuangs[i]->setVisible(iszhuang);
		}
		else{
			m_zhuangs[i]->setVisible(false);
		}
	}
}

void GameHead::setName(int pos, string name){
	int index = changePos(pos);
	int num = index%2==0?10:8;
	m_names[index]->setText(XXIconv::getU8SubString(name, 0, num, ""));
}

void GameHead::setName(string uid, string name){
	int index = getPos(uid);
	int num = index % 2 == 0 ? 10 : 8;
	m_names[index]->setText(XXIconv::getU8SubString(name, 0, num, ""));
}

void GameHead::setScore(int pos, int score){
	int index = changePos(pos);
	string tp = GameDataSet::getCNStringByInteger(score);
	m_scores[index]->setText(tp.c_str());
	float s = (tp.length()-4)/10.0;
	if (s > 0 && tp.length()>4){
		m_scores[index]->setScale(1.0 - s);
	}
}

void GameHead::setScore(string uid, int score){
	int index = getPos(uid);
	string tp = GameDataSet::getCNStringByInteger(score);
	m_scores[index]->setText(tp.c_str());
	float s = (tp.length() - 4) / 10.0;
	if (s > 0 && tp.length()>4){
		m_scores[index]->setScale(1.0 - s);
	}
}

void GameHead::PushRoomUser(RoomUser ru){
	int position = ru.position();
	int index = changePos(position);
	if (!m_users[index]){
		m_users[index] = (RoomUser *)ccEvent::create_message(ru.GetTypeName());
	}
	m_users[index]->CopyFrom(ru);
	if (index == 0){
		m_mimepos = position;
	}
	PhotoDown::getIns()->PushPhoto(this, ru.userid(), m_heads[index], ru.picurl(), ru.picid());
	m_headbgs[index]->setVisible(false);
}

void GameHead::PopRoomUser(string uid){
	for (int i = 0; i < 4; i++){
		if (m_users[i]->userid().compare(uid) == 0){
			delete m_users[i];
			m_users[i] = NULL;
			m_headbgs[i]->setVisible(false);
			break;
		}
	}

}

void GameHead::PopRoomUser(int pos){
	int i = changePos(pos);
	delete m_users[i];
	m_users[i] = NULL;
	m_headbgs[i]->setVisible(false);
}

int GameHead::changePos(int pos){
	int pp = (pos-m_mimepos+4)%4;
	return pp;
}

void GameHead::onLine(int pos){
	int index = changePos(pos);
	removeGray(m_heads[index]);
	m_texts[index]->setVisible(false);
}

void GameHead::onLine(string uid){
	int index = getPos(uid);
	if (index >= 0){
		removeGray(m_heads[index]);
		m_texts[index]->setVisible(false);
	}
}

void GameHead::offLine(int pos){
	int index = changePos(pos);
	setGray(m_heads[index]);
	m_texts[index]->setVisible(true);
}

void GameHead::offLine(string uid){
	int index = getPos(uid);
	if (index >= 0){
		setGray(m_heads[index]);
		m_texts[index]->setVisible(true);
	}
}

int GameHead::getPos(string uid){
	for (int i = 0; i < 4; i++){
		if (m_users[i]&&m_users[i]->userid().compare(uid)==0){
			return changePos(m_users[i]->position());
		}
	}
	return -1;
}

void GameHead::setGray(ImageView *img){
	auto program = CCGLProgram::createWithFilenames("gray.vsh", "gray.fsh"); //装配一个shader文件
	program->link();
	program->updateUniforms();
	Sprite *spr = ((ui::Scale9Sprite *)img->getVirtualRenderer())->getSprite();
	spr->setShaderProgram(program);
}

void GameHead::removeGray(ImageView *img){
	auto program = CCGLProgram::createWithFilenames("", ""); //装配一个shader文件
	program->link();
	program->updateUniforms();
	Sprite *spr = ((ui::Scale9Sprite *)img->getVirtualRenderer())->getSprite();
	spr->setShaderProgram(program);
}