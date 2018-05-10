#include "GameHead.h"
#include "GameControl.h"
#include "GameDataSet.h"
#include "ClientSocket.h"
#include "LoginScene.h"
#include "LoginInfo.h"
#include "PhotoDown.h"
#include "RoomInfo.h"
#include "RoomControl.h"
RoomUser *GameHead::m_users[4] = {NULL};
GameHead::GameHead(){
	memset(m_users, NULL, sizeof(RoomUser *)*4);
}

GameHead::~GameHead(){
	RoomInfo::getIns()->clearRoomUser();
	for (int i = 0; i < 4; i++){
		if (m_users[i]){
			delete m_users[i];
			m_users[i] = NULL;
		}
	}
	
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

	m_pRoomData = RoomInfo::getIns()->getRoomData();

	char buff[50];
	for (int i = 0; i < 4; i++){
		sprintf(buff, "btn%d", i + 1);
		GameDataSet::getButton(m_RootLayer, buff, selector, this);
		sprintf(buff, "head%d", i + 1);
		m_heads[i] = (ImageView *)GameDataSet::getLayout(m_RootLayer,buff);
		
		sprintf(buff, "headbg%d", i + 1);
		m_headbgs[i] = (ImageView *)GameDataSet::getLayout(m_RootLayer, buff);
		m_headbgs[i]->setVisible(false);
		sprintf(buff, "BitmapLabel_off%d", i + 1);
		m_texts[i] = (TextBMFont *)GameDataSet::getLayout(m_RootLayer, buff);

		sprintf(buff, "zhuang%d", i + 1);
		m_zhuangs[i] = (ImageView *)GameDataSet::getLayout(m_RootLayer, buff);

		sprintf(buff, "name%d", i + 1);
		m_names[i] = (Text *)GameDataSet::getLayout(m_RootLayer, buff);
		m_names[i]->setFontSize(16);

		sprintf(buff, "BitmapLabel_%d", i + 1);
		m_scores[i] = (TextBMFont *)GameDataSet::getLayout(m_RootLayer, buff);

		sprintf(buff, "ready%d", i + 1);
		m_readyimgs[i] = (ImageView *)GameDataSet::getLayout(m_RootLayer, buff);

		setWin(i + 1, false);
		
	}
	reset();
	
    return true;
}

void GameHead::reset(){
	for (int i = 0; i < 4; i++){
		setTipVisible(i + 1, false);
		setZhuang(i + 1, false);
		setWinVisible(i + 1, false);
		onLine(i + 1);
		ShowReady(i + 1, false);
	}
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

void GameHead::setTip(int pos,string uid, int time){
	int index = changePos(pos);
	char buff[500];
	sprintf(buff, "%s%s%s%02d:%02d%s", XXIconv::GBK2UTF("玩家").c_str(), uid.c_str(), XXIconv::GBK2UTF("玩家已经离线，等待玩家上线，还有").c_str(),
		time / 60, time % 60, XXIconv::GBK2UTF("房间解散").c_str()
		);
	char buff1[30];
	sprintf(buff1, "tip%d", index + 1);
	Text *t= GameDataSet::setText(m_RootLayer, buff1, buff);
	if (index >= 0){
		t->setFontSize(18);
		setTipVisible(pos, true);
	}
}

void GameHead::setTip(string uid, int time){
	int pos = getPosition1(uid);
	setTip(pos, uid,time);
}

void GameHead::setTipVisible(int pos, bool isv){
	int index = changePos(pos);
	char buff[50];
	sprintf(buff, "tipbg%d", index + 1);
	Layout *ly = GameDataSet::getLayout(m_RootLayer, buff);
	ly->setVisible(isv);
}

void GameHead::ShowReady(int pos, bool isr){
	int index = changePos(pos);
	if (m_readyimgs[index]){
		m_readyimgs[index]->setVisible(isr);
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
	m_names[index]->setText(XXIconv::getU8SubString(XXIconv::GBK2UTF(name.c_str()), 0, num, ""));
}

void GameHead::setName(string uid, string name){
	int index = getPos(uid);
	int num = index % 2 == 0 ? 10 : 8;
	m_names[index]->setText(XXIconv::getU8SubString(XXIconv::GBK2UTF(name.c_str()), 0, num, ""));
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

void GameHead::setWin(int pos, int win){
	int index = changePos(pos);
	char buff[50];
	sprintf(buff,"BitmapLabel_win%d",index+1);
	string fnt = "fonts/jiesuan_shu_shuzi.fnt";
	char buff1[30];
	if (win > 0){
		fnt = "fonts/jiesuan_ying_shuzi.fnt";
		sprintf(buff1, "+%d",win);
	}
	else if(win<0){
		sprintf(buff1, "%d", win);
	}
	TextBMFont *t= (TextBMFont *)GameDataSet::getLayout(m_RootLayer, buff);
	t->setFntFile(fnt);
	t->setText(buff1);
	setWinVisible(pos,win!=0? true:false);
}

void GameHead::setWinVisible(int pos, bool isv){
	int index = changePos(pos);
	char buff[50];
	sprintf(buff, "BitmapLabel_win%d", index + 1);
	Layout *ly = GameDataSet::getLayout(m_RootLayer, buff);
	ly->setVisible(isv);
}

void GameHead::PushRoomUser(RoomUser ru){
	int position = ru.position();
	string uid = ru.userid();
	int index = changePos(position);
	if (!m_users[index]){
		m_users[index] = (RoomUser *)ccEvent::create_message(ru.GetTypeName());
	}
	m_users[index]->CopyFrom(ru);
	PhotoDown::getIns()->PushPhoto(this, uid, m_heads[index], ru.picurl(), ru.picid());
	m_headbgs[index]->setVisible(true);
	setName(position, ru.username());
	if (m_pRoomData.type() == 1){
		setScore(position, ru.score());
	}
	else{
		setScore(position, ru.gold());
	}
	ShowReady(position,ru.ready());
	ru.online() ? onLine(uid) : offLine(uid);
	setZhuang(uid, ru.zhuang() == ru.position());
}

void GameHead::PopRoomUser(string uid){
	for (int i = 0; i < 4; i++){
		RoomUser *ru = m_users[i];
		if (ru&&ru->userid().compare(uid) == 0){
			int pos = ru->position();
			ShowReady(pos, false);
			offLine(uid);
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
	int mypos = RoomControl::shareRoomControl()->getMyPosition();
	int pp = (4 - (pos - mypos + 4) % 4) % 4;
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

int GameHead::getPosition1(string uid){
	for (int i = 0; i < 4; i++){
		if (m_users[i] && m_users[i]->userid().compare(uid) == 0){
			return m_users[i]->position();
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
	Sprite *spr = ((ui::Scale9Sprite *)img->getVirtualRenderer())->getSprite();
	std::string str = "ShaderPositionTextureColor_noMVP";
	GLProgram * pProgram = ShaderCache::getInstance()->getGLProgram(str);
	spr->setShaderProgram(pProgram);
	CHECK_GL_ERROR_DEBUG();
}