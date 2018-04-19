#include "LoadLayer.h"
#include "GameControl.h"
#include "GameDataSet.h"
#include "ClientSocket.h"
#include "LoginScene.h"
#include "LoginInfo.h"
#include "MainScene.h"

LoadLayer::LoadLayer(){
	
}

LoadLayer::~LoadLayer(){
	
}

LoadLayer *LoadLayer::create(Layout *ly){
	LoadLayer *p = new LoadLayer();
	if (p&&p->init(ly)){
		p->autorelease();
	}
	else{
		CC_SAFE_DELETE(p);
	}
	return p;
}

bool LoadLayer::init(Layout *ly)
{             
	if (!Layer::init())
    {
        return false;
    }
	ImageView *img = ImageView::create("loading.png");
	img->setName("loading");
	this->addChild(img);
	Size sz;
	if (ly){
		sz = ly->getSize();
	}
	else{
		sz = Director::sharedDirector()->getWinSize();
	}

	this->setContentSize(sz);
	img->setPosition(sz / 2.0);

	img->runAction(RepeatForever::create(RotateBy::create(0.2,60)));
    return true;
}