#include "CreateRoomLayer.h"
#include "GameControl.h"
#include "GameDataSet.h"
#include "ClientSocket.h"
#include "LogoScene.h"
#include "LoginInfo.h"
#include "WebViewCommom.h"


const int g_ante[3] = { 1, 2, 5 };
const int g_time[2] = { 8, 16 };
const int g_bang[4] = {0, 1, 2, 5 };


CreateRoomLayer::CreateRoomLayer(){
	GameControl::getIns()->setCreateRoomLayer(this);
}

CreateRoomLayer::~CreateRoomLayer(){
	RootRegister::getIns()->resetWidget(m_RootLayer);
	if (this == GameControl::getIns()->getCreateRoomLayer()){
		GameControl::getIns()->setCreateRoomLayer(NULL);

	}
}

bool CreateRoomLayer::init()
{             
	if (!Layer::init())
    {
        return false;
    }
	
	m_RootLayer =RootRegister::getIns()->getWidget("privatecreate.json");
	this->addChild(m_RootLayer);

	SEL_TouchEvent selector = toucheventselector(CreateRoomLayer::TouchEvent);
	
	GameDataSet::getButton(m_RootLayer, "close_btn", selector, this);
	char buff[30];
	for (int i = 0; i < 2;i++){
		sprintf(buff,"btn1%d",i+1);
		m_btns[i] = GameDataSet::getButton(m_RootLayer, buff, selector, this);
		m_btns[i]->setTouchEnabled(true);
		sprintf(buff, "sbg%d", i + 1);
		m_bg[i] = GameDataSet::getLayout(m_RootLayer,buff);
		sprintf(buff, "BitmapLabel_%d", i + 1);
		m_btntext[i] = (TextBMFont *)GameDataSet::getLayout(m_RootLayer, buff);

		sprintf(buff, "btn%d", i + 1);
		GameDataSet::getButton(m_RootLayer, buff, selector, this);
	}
	for (int i = 0; i < 5; i++){
		if (i < 2){
			sprintf(buff,"CheckBox_j1%d",i+1);
			m_typeboxs[i] = (CheckBox *)GameDataSet::getButton(m_RootLayer, buff, selector, this);

			sprintf(buff, "CheckBox_j3%d", i + 1);
			m_timeboxs[i] = (CheckBox *)GameDataSet::getButton(m_RootLayer, buff, selector, this);
		}
		if (i < 3){
			sprintf(buff, "CheckBox_j4%d", i + 1);
			m_baoboxs[i] = (CheckBox *)GameDataSet::getButton(m_RootLayer, buff, selector, this);
		}
		if (i < 4){
			sprintf(buff, "CheckBox_j2%d", i + 1);
			m_anteboxs[i] = (CheckBox *)GameDataSet::getButton(m_RootLayer, buff, selector, this);
		}
		sprintf(buff, "CheckBox_j5%d", i + 1);
		m_bangboxs[i] = (CheckBox *)GameDataSet::getButton(m_RootLayer, buff, selector, this);
	}
	GameDataSet::getButton(m_RootLayer, "btn", selector, this);

	for (int i = 0; i < 2; i++){
		sprintf(buff,"in%d",i+1);
		Layout *in = GameDataSet::getLayout(m_RootLayer, buff);
		m_input[i] = LogoLayer::AddCursorTextField(in, 24);
		m_input[i]->setFontColor(ccc3(0xFF,0x3C,0x00));
		m_input[i]->setPlaceHolder(XXIconv::GBK2UTF("自定义").c_str());
		m_input[i]->setTouchEnabled(false);
		m_input[i]->setPlaceholderFontColor(ccc3(0xFF, 0x3C, 0x00));
		m_input[i]->setInputMode(ui::EditBox::InputMode::PHONE_NUMBER);
	}
	
	SelectItem(0);
	for (int i = 0; i < 5; i++){
		SelectCheckBox(i, 0);
	}

    return true;
}

void CreateRoomLayer::TouchEvent(CCObject *obj, TouchEventType type){
	Button *btn = (Button *)obj;
	string name = btn->getName();
	if (type == TOUCH_EVENT_ENDED){
		UserDefault *p = UserDefault::sharedUserDefault();
		if (name.compare("close_btn") == 0){
			this->removeFromParentAndCleanup(true);
		}
		else if (btn == m_btns[0]){
			SelectItem(0);
		}
		else if (btn == m_btns[1]){
			SelectItem(1);
		}
		else if (name.compare("btn") == 0){
			log("%d,%d,%d,%d,%d\n",m_type,m_ante,m_time,m_bao,m_bang);
		}
		else if (name.find("CheckBox_j1") == 0){
			int in = name.find("CheckBox_j1");
			int index = atoi(name.substr(strlen("CheckBox_j1"),name.length()).c_str());
			SelectCheckBox(0, index-1);
		}
		else if (name.find("CheckBox_j2") == 0){
			int in = name.find("CheckBox_j2");
			int index = atoi(name.substr(strlen("CheckBox_j2"), name.length()).c_str());
			SelectCheckBox(1, index - 1);
		}
		else if (name.find("CheckBox_j3") == 0){
			int in = name.find("CheckBox_j3");
			int index = atoi(name.substr(strlen("CheckBox_j3"), name.length()).c_str());
			SelectCheckBox(2, index - 1);
		}
		else if (name.find("CheckBox_j4") == 0){
			int in = name.find("CheckBox_j4");
			int index = atoi(name.substr(strlen("CheckBox_j4"), name.length()).c_str());
			SelectCheckBox(3, index - 1);
		}
		else if (name.find("CheckBox_j5") == 0){
			int in = name.find("CheckBox_j5");
			int index = atoi(name.substr(strlen("CheckBox_j5"), name.length()).c_str());
			SelectCheckBox(4, index - 1);
		}
		else if (name.compare("btn1")==0){
			m_input[0]->touchDownAction(NULL, Widget::TouchEventType::ENDED);
			SelectCheckBox(1, 3);
		}
		else if (name.compare("btn2") == 0){
			m_input[1]->touchDownAction(NULL, Widget::TouchEventType::ENDED);
			SelectCheckBox(4, 4);
		}
		
		
	}
}

void CreateRoomLayer::SelectItem(int index){
	for (int i = 0; i < 2; i++){
		m_bg[i]->setVisible(false);
		if (m_btns[i]){
			m_btns[i]->setBright(true);
		}
	}
	if (m_btns[index]){
		m_btns[index]->setBright(false);
	}
	m_bg[index]->setVisible(true);
}

void CreateRoomLayer::SelectCheckBox(int type, int index){
	char buff[30];
	if (type == 0){
		for (int i = 0; i < 2; i++){
			m_typeboxs[i]->setSelectedState(false);
		}
		m_typeboxs[index]->setSelectedState(true);
		m_type = index+1;
	}
	else if (type == 1){
		for (int i = 0; i < 4; i++){
			m_anteboxs[i]->setSelectedState(false);
		}
		m_anteboxs[index]->setSelectedState(true);
		if (index < 3){
			m_ante =g_ante[index];
			m_input[0]->setText("");
		}
		else{
			string t = m_input[0]->getText();
			if (t.empty()){
				t = "10";
				m_input[0]->setText(t.c_str());
			}
			m_ante = atoi(t.c_str());
		}
	}
	else if (type == 2){
		for (int i = 0; i < 2; i++){
			m_timeboxs[i]->setSelectedState(false);
		}
		m_timeboxs[index]->setSelectedState(true);
		m_time = g_time[index];
		sprintf(buff,"x%d",index+1);
		GameDataSet::setTextBMFont(m_RootLayer, "BitmapLabel_card", buff);
	}
	else if (type == 3){
		for (int i = 0; i < 3; i++){
			m_baoboxs[i]->setSelectedState(false);
		}
		m_baoboxs[index]->setSelectedState(true);
		m_bao = index+1;
	}
	else if (type == 4){
		for (int i = 0; i < 5; i++){
			m_bangboxs[i]->setSelectedState(false);
		}
		m_bangboxs[index]->setSelectedState(true);
		if (index < 4){
			m_bang = g_bang[index];
			m_input[1]->setText("");
		}
		else{
			string t = m_input[1]->getText();
			if (t.empty()){
				t = "10";
				m_input[1]->setText(t.c_str());
			}
			m_bang = atoi(t.c_str());
		}
	}
}