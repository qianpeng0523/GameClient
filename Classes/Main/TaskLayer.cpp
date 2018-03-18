#include "TaskLayer.h"
#include "GameControl.h"
#include "GameDataSet.h"
#include "ClientSocket.h"
#include "LogoScene.h"
#include "LoginInfo.h"




TaskItemLayer::TaskItemLayer(){

}

TaskItemLayer::~TaskItemLayer(){

}

TaskItemLayer *TaskItemLayer::create(Rank hall){
	TaskItemLayer *p = new TaskItemLayer();
	if (p&&p->init(hall)){
		p->autorelease();
	}
	else{
		CC_SAFE_DELETE(p);
	}
	return p;
}

bool TaskItemLayer::init(Rank hall)
{
	if (!Layer::init())
	{
		return false;
	}
	m_hall = hall;
	m_RootLayer = (Layout *)GUIReader::shareReader()->widgetFromJsonFile("taskitem.json");
	this->addChild(m_RootLayer);

	this->setContentSize(m_RootLayer->getSize());



	return true;
}

void TaskItemLayer::TouchEvent(){

}





















TaskLayer::TaskLayer(){
	GameControl::getIns()->setTaskLayer(this);
}

TaskLayer::~TaskLayer(){
	if (this == GameControl::getIns()->getTaskLayer()){
		GameControl::getIns()->setTaskLayer(NULL);

	}
}

bool TaskLayer::init()
{             
	if (!Layer::init())
    {
        return false;
    }
	
	m_RootLayer = (Layout *)GUIReader::shareReader()->widgetFromJsonFile("task.json");
	this->addChild(m_RootLayer);

	SEL_TouchEvent selector = toucheventselector(TaskLayer::TouchEvent);
	
	GameDataSet::getButton(m_RootLayer, "close_btn", selector, this);
	char buff[30];
	for (int i = 0; i < 4;i++){
		sprintf(buff, "ScrollView_%d", i);
		m_ScrollView[i] = (ui::ScrollView *)GameDataSet::getButton(m_RootLayer, buff, selector, this);
		sprintf(buff, "sbg_%d", i);
		m_sbg[i] = GameDataSet::getLayout(m_RootLayer, buff);
	}

	m_btns[0] = GameDataSet::getButton(m_RootLayer, "xinshou", selector, this);
	m_btns[1] = GameDataSet::getButton(m_RootLayer, "jinri", selector, this);
	m_btns[2] = GameDataSet::getButton(m_RootLayer, "benzhou", selector, this);
	m_btns[3] = GameDataSet::getButton(m_RootLayer, "dingshi", selector, this);
	m_btntext[0] = (TextBMFont *)GameDataSet::getLayout(m_RootLayer, "BitmapLabel_xinshou");
	m_btntext[1] = (TextBMFont *)GameDataSet::getLayout(m_RootLayer, "BitmapLabel_jinri");
	m_btntext[2] = (TextBMFont *)GameDataSet::getLayout(m_RootLayer, "BitmapLabel_benzhou");
	m_btntext[3] = (TextBMFont *)GameDataSet::getLayout(m_RootLayer, "BitmapLabel_dingshi");

	AddTaskItems(0);
    return true;
}

void TaskLayer::TouchEvent(CCObject *obj, TouchEventType type){
	Button *btn = (Button *)obj;
	string name = btn->getName();
	if (type == TOUCH_EVENT_ENDED){
		UserDefault *p = UserDefault::sharedUserDefault();
		if (name.compare("close_btn") == 0){
			this->removeFromParentAndCleanup(true);
		}
		else if (name.find("ScrollView_") !=-1){
			int index = atoi(name.substr(11,name.length()).c_str());
			TaskItemLayer *p = (TaskItemLayer *)GameDataSet::isTouchInChild(m_ScrollView[index], 10, NULL);
			if (p){
				p->TouchEvent();
			}
		}
		else if (name.compare("xinshou") == 0){
			AddTaskItems(0);
		}
		else if (name.compare("jinri") == 0){
			AddTaskItems(1);
		}
		else if (name.compare("benzhou") == 0){
			AddTaskItems(2);
		}
		else if (name.compare("dingshi") == 0){
			AddTaskItems(3);
		}
	}
}

void TaskLayer::AddTaskItems(int index){
	for (int i = 0; i < 4;i++){
		if (m_btns[i]){
			m_btns[i]->setBright(true);
		}
		if (m_btntext[i]){
			m_btntext[i]->setFntFile("fonts/xiaodan10-1.fnt");
		}
		m_ScrollView[i]->setVisible(i==index?true:false);
	}
	if (m_btns[index]){
		m_btns[index]->setBright(false);
	}
	if (m_btntext[index]){
		m_btntext[index]->setFntFile("fonts/xiaodan10.fnt");
	}
	if (m_sbg[index]->getChildrenCount() == 0){
		for (int i = 0; i < 10; i++){
			Rank rk;
			TaskItemLayer *p = TaskItemLayer::create(rk);
			GameDataSet::PushScrollItem(m_sbg[index], 0, 0, p, i, m_ScrollView[index]);
		}
	}
}