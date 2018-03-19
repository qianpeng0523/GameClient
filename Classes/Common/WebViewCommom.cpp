/****************************************************************************
 Copyright (c) 2013-2017 Chukong Technologies Inc.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "WebViewCommom.h"
#include "GameDataSet.h"
#include "Adaptation.h"
#include "GameControl.h"
USING_NS_CC;
#if(CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)

WebViewCommom::WebViewCommom()
{
	
}

WebViewCommom::~WebViewCommom()
{
	
}

bool WebViewCommom::init(string url)
{
    if (!BaseLayer::init()) {
       
        return false;
    }
	m_RootLayer = (Layout *)GUIReader::shareReader()->widgetFromJsonFile("webview.json");
	this->addChild(m_RootLayer);

	SEL_TouchEvent selector = toucheventselector(WebViewCommom::TouchEvent);
	Layout *ly=GameDataSet::getLayout(m_RootLayer,"webbg");
	GameDataSet::getButton(m_RootLayer, "close_btn", selector, this);
	
	Size winSize = ly->getSize();

	_webView = WebView::create();
	_webView->setContentSize(winSize);
	_webView->loadURL(url.c_str());
	_webView->setScalesPageToFit(true);
	

	_webView->setOnShouldStartLoading(CC_CALLBACK_2(WebViewCommom::onWebViewShouldStartLoading, this));
	_webView->setOnDidFinishLoading(CC_CALLBACK_2(WebViewCommom::onWebViewDidFinishLoading, this));
	_webView->setOnDidFailLoading(CC_CALLBACK_2(WebViewCommom::onWebViewDidFailLoading, this));

	ly->addChild(_webView);
	_webView->setPosition(winSize/2.0);
	//this->setPositionY(-this->getContentSize().height);
	//this->runAction(Sequence::create(MoveTo::create(0.3, ccp(0,0)), NULL));

    return true;
}

WebViewCommom *WebViewCommom::create(string url){
	WebViewCommom *p=new WebViewCommom();
	if(p&&p->init(url,sz)){
		p->autorelease();
	}else{
		CC_SAFE_DELETE(p);
	}
	return p;
}

void WebViewCommom::TouchEvent(Object *obj, TouchEventType type){
	if (type == TOUCH_EVENT_ENDED){
		Button *btn = (Button *)obj;
		string name = btn->getName();
		if (name.compare("close_btn") == 0){
			removeWebView();
		}
	}
}

void WebViewCommom::removeWebView(){
	this->runAction(Sequence::create(MoveTo::create(0.3, ccp(0,-this->getContentSize().height)),RemoveSelf::create(true), NULL));
}

bool WebViewCommom::onWebViewShouldStartLoading(WebView *sender, const std::string &url)
{
    CCLOG("onWebViewShouldStartLoading, url is %s", url.c_str());
	
    //don't do any OpenGL operation here!! It's forbidden!
    return true;
}

void WebViewCommom::onWebViewDidFinishLoading(WebView *sender, const std::string &url)
{
    //auto node = (ui::Button*)this->getChildByName("evalJs");
	
    CCLOG("onWebViewDidFinishLoading, url is %s", url.c_str());
}

void WebViewCommom::onWebViewDidFailLoading(WebView *sender,const std::string &url)
{
    CCLOG("onWebViewDidFailLoading, url is %s", url.c_str());
}

#endif
