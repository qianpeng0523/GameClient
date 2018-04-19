#include "RewardTipLayer.h"
#include "GameControl.h"
#include "GameDataSet.h"
#include "ClientSocket.h"
#include "LoginScene.h"
#include "LoginInfo.h"






RewardTipLayer::RewardTipLayer(){
	GameControl::getIns()->setRewardTipLayer(this);
}

RewardTipLayer::~RewardTipLayer(){
	RootRegister::getIns()->resetWidget(m_RootLayer);
	if (this == GameControl::getIns()->getRewardTipLayer()){
		GameControl::getIns()->setRewardTipLayer(NULL);

	}
}

RewardTipLayer *RewardTipLayer::create(RepeatedPtrField<SignAward> props){
	RewardTipLayer *p = new RewardTipLayer();
	if (p&&p->init(props)){
		p->autorelease();
	}
	else{
		CC_SAFE_DELETE(p);
	}
	return p;
}

bool RewardTipLayer::init(RepeatedPtrField<SignAward> props)
{             
	if (!Layer::init())
    {
        return false;
    }
	
	m_RootLayer =RootRegister::getIns()->getWidget("rewardtip.json");
	this->addChild(m_RootLayer);

	SEL_TouchEvent selector = toucheventselector(RewardTipLayer::TouchEvent);
	
	GameDataSet::getButton(m_RootLayer, "btn", selector, this);
	char buff[50];
	char buff1[50];
	int sz = props.size();
	for (int i = 0; i < 2;i++){
		sprintf(buff,"iconbg%d",i+1);
		Layout *ly = GameDataSet::getLayout(m_RootLayer,buff);
		if (i < sz){
			SignAward p = props.Get(i);
			Reward reward = p.reward();
			Prop prop = reward.prop();
			int id = prop.id();
			int number = reward.number();
			sprintf(buff,"icon%d",i+1);
			GameDataSet::setImageView(m_RootLayer, buff, id==1?"mall_SC_TB_jinbi2.png":"card1.png");
			sprintf(buff,"BitmapLabel_%d",i+1);
			sprintf(buff1,"x%d",number);
			GameDataSet::setTextBMFont(m_RootLayer, buff, buff1);
		}
		else{
			ly->setVisible(false);
		}
		
	}
	if (sz == 1){
		Layout *ly1 = GameDataSet::getLayout(m_RootLayer, "iconbg1");
		Layout *ly2 = GameDataSet::getLayout(m_RootLayer, "iconbg2");
		ly1->setPositionX((ly1->getPositionX()+ly2->getPositionX())/2.0);
	}

	Layout *bg = GameDataSet::getLayout(m_RootLayer,"bg");
	bg->runAction(RepeatForever::create(Sequence::create(RotateBy::create(7.0,360),NULL)));

	Layout *bgbg = GameDataSet::getLayout(m_RootLayer,"bgbg");
	bgbg->setScale(0);
	bgbg->runAction(Sequence::create(ScaleTo::create(0.3, 1.0), NULL));
    return true;
}

void RewardTipLayer::TouchEvent(CCObject *obj, TouchEventType type){
	Button *btn = (Button *)obj;
	string name = btn->getName();
	if (type == TOUCH_EVENT_ENDED){
		UserDefault *p = UserDefault::sharedUserDefault();
		if (name.compare("btn") == 0){
			this->removeFromParentAndCleanup(true);
		}
	}
}