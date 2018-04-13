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

#ifndef __UIWebViewCommom__
#define __UIWebViewCommom__
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "cocos/base/CCRef.h"
#include "ui/UILayout.h"
#include "BaseLayer.h"


#if(CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
#include "ui/UIWebView.h"
using namespace cocos2d;
using namespace cocos2d::ui;
using namespace cocos2d::experimental::ui;
class WebViewCommom : public BaseLayer
{
public:
	WebViewCommom();
	~WebViewCommom();
	static WebViewCommom *create(string url);
    
	virtual bool init(string url);
    bool onWebViewShouldStartLoading(WebView *sender,const std::string &url);
	void onWebViewDidFinishLoading(WebView *sender, const std::string &url);
	void onWebViewDidFailLoading(WebView *sender, const std::string &url);
    
	void TouchEvent(Object *obj, TouchEventType type);
	void removeWebView();
private:
   WebView *_webView;
    
};
#endif
#endif /* defined(__cocos2d_tests__UIWebViewCommom__) */
