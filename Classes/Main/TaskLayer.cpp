#include "TaskLayer.h"
#include "GameControl.h"
#include "GameDataSet.h"
#include "ClientSocket.h"
#include "LoginScene.h"
#include "LoginInfo.h"
#include "HallInfo.h"



TaskItemLayer::TaskItemLayer(){

}

TaskItemLayer::~TaskItemLayer(){
	RootRegister::getIns()->resetWidget(m_RootLayer);
}

TaskItemLayer *TaskItemLayer::create(Task task){
	TaskItemLayer *p = new TaskItemLayer();
	if (p&&p->init(task)){
		p->autorelease();
	}
	else{
		CC_SAFE_DELETE(p);
	}
	return p;
}

bool TaskItemLayer::init(Task task)
{
	if (!Layer::init())
	{
		return false;
	}
	m_task = task;
	m_RootLayer =RootRegister::getIns()->getWidget("taskitem.json");
	this->addChild(m_RootLayer);

	this->setContentSize(m_RootLayer->getSize());

	SEL_TouchEvent selector = toucheventselector(TaskItemLayer::TouchEvent);
	Button *btn= GameDataSet::getButton(m_RootLayer, "btn", selector, this);

	string title = task.title();
	string content = task.content();
	int taskid = task.taskid();

	Status status = task.status();
	int count = status.count();
	int fcount = status.fcount();
	int finish = status.finished();

	int sz = task.rewardlist_size();
	if (sz < 1){
		return true;
	}
	Reward rd = task.rewardlist(0);
	int number = rd.number();

	Prop prop = rd.prop();
	int id = prop.id();
	string name = prop.name();
	
	GameDataSet::setText(m_RootLayer, "content", content);
	GameDataSet::setTextBMFont(m_RootLayer, "title", title);
	char buff[100];
	sprintf(buff,"%d/%d",fcount,count);
	GameDataSet::setText(m_RootLayer, "pro", buff);
	int pro = fcount*1.0/count*100;
	LoadingBar *bar = (LoadingBar *)GameDataSet::getLayout(m_RootLayer, "ProgressBar");
	bar->setPercent(pro);
	sprintf(buff, "%d%s",number,name.c_str());
	GameDataSet::setText(m_RootLayer, "jiangli", buff);

	Layout *biao = GameDataSet::getLayout(m_RootLayer,"qd");
	if (finish == 2){
		btn->setVisible(false);
		biao->setVisible(true);
	}
	else if (finish == 0){
		btn->setBright(false);
		biao->setVisible(false);
	}
	else{
		biao->setVisible(false);
		btn->setVisible(true);
	}

	

	return true;
}

void TaskItemLayer::TouchEvent(CCObject *obj, TouchEventType type){
	Button *btn = (Button *)obj;
	string name = btn->getName();
	if (type == TOUCH_EVENT_ENDED){
		if (name.compare("btn") == 0){
			int type = m_task.type();
			int id = m_task.taskid();
			log("task:type:%d,id:%d",type,id);
			HallInfo::getIns()->SendCReward(id);
		}
	}
}





















TaskLayer::TaskLayer(){
	GameControl::getIns()->setTaskLayer(this);
}

TaskLayer::~TaskLayer(){
	RootRegister::getIns()->resetWidget(m_RootLayer);
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
	
	m_RootLayer =RootRegister::getIns()->getWidget("task.json");
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
	HallInfo::getIns()->SendCTask();
	
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
				p->TouchEvent(p,TOUCH_EVENT_ENDED);
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
		char buff[100];
		STask st = HallInfo::getIns()->getSTask();
		int sz = st.list_size();
		int count = 0;
		for (int i = 0; i < sz; i++){
			Task rk=st.list(i);
			if (rk.type() == index + 1){
				TaskItemLayer *p = TaskItemLayer::create(rk);
				GameDataSet::PushScrollItem(m_sbg[index], 0, 0, p, count, m_ScrollView[index]);
				count++;
			}
		}
	}
}