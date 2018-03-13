#include "LogoLayer.h"
#include "SimpleAudioEngine.h"
#include "AppMacros.h"
#include "GameDataSet.h"
#include "HttpInfo.h"

USING_NS_CC;



LogoLayer::LogoLayer(){
	
}

LogoLayer::~LogoLayer(){
	
}

bool LogoLayer::init()
{
	if (!Layer::init())
    {
        return false;
    }

// 	m_RootLayer = (Layout *)GUIReader::shareReader()->widgetFromJsonFile("sqlserver.json");
// 	this->addChild(m_RootLayer);
	HttpInfo::getIns()->requestGateIPAndPort();
    return true;
}

ui::EditBox *LogoLayer::AddCursorTextField(Layout *parent, int fontsz, bool ispass){
	parent->setClippingEnabled(true);
	parent->setClippingType(Layout::ClippingType::SCISSOR);
	

	CursorItem *pCursorItem = new CursorItem();
	pCursorItem->fontName = "";
	pCursorItem->fontSize = fontsz;
	pCursorItem->dsz = parent->getSize();
	int limit = 100;
	int s = 0;
	ui::EditBox::InputMode mode = ui::EditBox::InputMode::SINGLE_LINE;
	ui::EditBox::InputFlag flag = ui::EditBox::InputFlag::INITIAL_CAPS_WORD;
	if (ispass){
		flag = ui::EditBox::InputFlag::PASSWORD;
	}
	ui::EditBox *pCursorTextField = ui::EditBox::create(pCursorItem->dsz, "touming.png");
	pCursorTextField->setPlaceHolder(pCursorItem->placeholder.c_str());
	pCursorTextField->setTouchEnabled(true);
	pCursorTextField->setAnchorPoint(ccp(0, 0));
	pCursorTextField->setPlaceholderFont(pCursorItem->fontName.c_str(), pCursorItem->fontSize);
	pCursorTextField->setMaxLength(limit);
	pCursorTextField->setInputMode(mode);
	pCursorTextField->setInputFlag(flag);
	pCursorTextField->setFontName(pCursorItem->fontName.c_str());
	pCursorTextField->setFontSize(pCursorItem->fontSize);
	pCursorTextField->setReturnType(ui::EditBox::KeyboardReturnType::DONE);


	parent->addChild(pCursorTextField);


	return pCursorTextField;
}

void LogoLayer::TouchEvent(Object *obj, TouchEventType type){
	if (type == TOUCH_EVENT_ENDED){
		Button *btn = (Button *)obj;
		string name = btn->getName();
		
	}
}