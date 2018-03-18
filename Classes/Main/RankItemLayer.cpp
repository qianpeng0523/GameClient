#include "RankItemLayer.h"
#include "GameControl.h"
#include "GameDataSet.h"
#include "ClientSocket.h"
#include "LogoScene.h"
#include "LoginInfo.h"

RankItemLayer::RankItemLayer(){
	
}

RankItemLayer::~RankItemLayer(){
	
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
	m_RootLayer = (Layout *)GUIReader::shareReader()->widgetFromJsonFile("frienditem.json");
	this->addChild(m_RootLayer);

	this->setContentSize(m_RootLayer->getSize());

	string uname = m_hall.uname();
	string picurl = m_hall.picurl();
	int picid = m_hall.picid();
	int number = m_hall.number();
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

	
    return true;
}

void RankItemLayer::TouchEvent(){
	
}