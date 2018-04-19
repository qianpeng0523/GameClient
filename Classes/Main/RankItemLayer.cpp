#include "RankItemLayer.h"
#include "GameControl.h"
#include "GameDataSet.h"
#include "ClientSocket.h"
#include "LoginScene.h"
#include "LoginInfo.h"
#include "PhotoDown.h"

RankItemLayer::RankItemLayer(){
	
}

RankItemLayer::~RankItemLayer(){
	PhotoDown::getIns()->erasePhoto(this);
	RootRegister::getIns()->resetWidget(m_RootLayer);
}

RankItemLayer *RankItemLayer::create(Rank hall){
	RankItemLayer *p = new RankItemLayer();
	if (p&&p->init(hall)){
		p->autorelease();
	}
	else{
		CC_SAFE_DELETE(p);
	}
	return p;
}

bool RankItemLayer::init(Rank hall)
{             
	if (!Layer::init())
    {
        return false;
    }
	m_hall = hall;
	m_RootLayer =RootRegister::getIns()->getWidget("frienditem.json");
	this->addChild(m_RootLayer);

	this->setContentSize(m_RootLayer->getSize());

	int type = hall.type();
	UserBase user = hall.info();

	string uname = user.username();
	string picurl = user.picurl();
	int picid = user.picid();
	int number = type==1? user.gold():user.win();
	int lv = m_hall.lv();
	GameDataSet::setText(m_RootLayer, "name", uname);
	GameDataSet::setTextBMFont(m_RootLayer, "BitmapLabel_fri", GameDataSet::getCNStringByInteger(number));
	ImageView *lvimg = (ImageView *)GameDataSet::getLayout(m_RootLayer,"ph");
	TextBMFont *lvtext = (TextBMFont *)GameDataSet::getLayout(m_RootLayer,"BitmapLabel_lv");
	char buff[50];
	if (lv > 0 && lv < 4){
		lvtext->setVisible(false);
		sprintf(buff,"paihangb_no%d.png",lv);
		lvimg->loadTexture(buff, Widget::TextureResType::PLIST);
	}
	else{
		lvimg->setVisible(false);
		lvtext->setVisible(true);
		GameDataSet::setTextBMFont(m_RootLayer, "BitmapLabel_lv",lv);
	}

	ImageView *img = (ImageView *)GameDataSet::getLayout(m_RootLayer, "head");
	PhotoDown::getIns()->PushPhoto(this, user.userid(), img, user.picurl(), user.picid());
    return true;
}

void RankItemLayer::TouchEvent(){
	
}