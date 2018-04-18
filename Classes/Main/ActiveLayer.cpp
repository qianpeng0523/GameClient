#include "ActiveLayer.h"
#include "GameControl.h"
#include "GameDataSet.h"
#include "ClientSocket.h"
#include "LogoScene.h"
#include "LoginInfo.h"
#include "WebViewCommom.h"





ActiveLayer::ActiveLayer(){
	m_type = 1;
#if(CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
	memset(m_pWebViewCommom,NULL,sizeof(WebViewCommom *)*4);
#endif
	GameControl::getIns()->setActiveLayer(this);
}

ActiveLayer::~ActiveLayer(){
#if(CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
	for (int i = 0; i < 4; i++){
		if (m_pWebViewCommom[i]){
			m_pWebViewCommom[i]->removeFromParentAndCleanup(true);
			m_pWebViewCommom[i] = NULL;
		}
	}
#endif
	RootRegister::getIns()->resetWidget(m_RootLayer);
	if (this == GameControl::getIns()->getActiveLayer()){
		GameControl::getIns()->setActiveLayer(NULL);

	}
}

bool ActiveLayer::init()
{             
	if (!Layer::init())
    {
        return false;
    }
	
	m_RootLayer =RootRegister::getIns()->getWidget("activity.json");
	this->addChild(m_RootLayer);

	SEL_TouchEvent selector = toucheventselector(ActiveLayer::TouchEvent);
	
	GameDataSet::getButton(m_RootLayer, "close_btn", selector, this);
	m_btns[0] = GameDataSet::getButton(m_RootLayer, "zhoumo", selector, this);
	m_btns[1] = GameDataSet::getButton(m_RootLayer, "denglu", selector, this);
	m_btns[2] = GameDataSet::getButton(m_RootLayer, "gongzhong", selector, this);
	m_titlebtns[0] = GameDataSet::getButton(m_RootLayer, "btn1", selector, this);
	m_titlebtns[1] = GameDataSet::getButton(m_RootLayer, "btn2", selector, this);
	
	m_btntext[0] = (TextBMFont *)GameDataSet::getLayout(m_RootLayer, "BitmapLabel_zhoumo");
	m_btntext[1] = (TextBMFont *)GameDataSet::getLayout(m_RootLayer, "BitmapLabel_denglu");
	m_btntext[2] = (TextBMFont *)GameDataSet::getLayout(m_RootLayer, "BitmapLabel_gongzhong");
	ShowItem(m_type,0);
    return true;
}

void ActiveLayer::TouchEvent(CCObject *obj, TouchEventType type){
	Button *btn = (Button *)obj;
	string name = btn->getName();
	if (type == TOUCH_EVENT_ENDED){
		UserDefault *p = UserDefault::sharedUserDefault();
		if (name.compare("close_btn") == 0){
			this->removeFromParentAndCleanup(true);
		}
		else if (name.compare("zhoumo") == 0){
			ShowItem(m_type, 0);
		}
		else if (name.compare("denglu") == 0){
			ShowItem(m_type, 1);
		}
		else if (name.compare("gongzhong") == 0){
			ShowItem(m_type, 2);
		}
		else if (name.compare("btn1") == 0){
			m_type = 1;
			ShowItem(m_type, 0);
		}
		else if (name.compare("btn2") == 0){
			m_type = 2;
			ShowItem(m_type, 0);
		}
	}
}

void ActiveLayer::ShowItem(int type, int index){
	char buff[30];
	for (int i = 0; i < 2; i++){
		m_titlebtns[i]->setBright(type-1==i?false:true);
		sprintf(buff,"bg%d",i+1);
		Layout *ly = GameDataSet::getLayout(m_RootLayer,buff);
		ly->setVisible(type-1==i?true:false);
	}
	if (type == 1){
		for (int i = 0; i < 3; i++){
			if (m_btns[i]){
				m_btns[i]->setBright(true);
			}
			if (m_btntext[i]){
				m_btntext[i]->setFntFile("fonts/xiaodan10-1.fnt");
			}
		}
		if (m_btns[index]){
			m_btns[index]->setBright(false);
		}
		if (m_btntext[index]){
			m_btntext[index]->setFntFile("fonts/xiaodan10.fnt");
		}
	}
	else{
		SEL_TouchEvent selector = toucheventselector(ActiveLayer::TouchEvent);
		Button *btn = GameDataSet::getButton(m_RootLayer,"gonggao1",selector,this);
		btn->setBright(false);
		TextBMFont *text = (TextBMFont *)GameDataSet::getLayout(m_RootLayer,"BitmapLabel_gonggao1");
		text->setFntFile("fonts/xiaodan10.fnt");
	}
	
	sprintf(buff,"sbg%d",type);
	Layout *sbg=GameDataSet::getLayout(m_RootLayer,buff);
#if(CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
	int ii=(type-1)*3+index;
	if(!m_pWebViewCommom[ii]){
		m_pWebViewCommom[ii] = WebViewCommom::create("http://www.lesharecs.com");
		sbg->addChild(m_pWebViewCommom[ii]);
	}
#endif
}