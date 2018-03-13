#ifndef __APPMACROS_H__
#define __APPMACROS_H__

#include "cocos2d.h"
#include "string.h"
#include "DBProto.h"
#include "YSEventDispatcher.h"

//design screen size
static cocos2d::Size designResolutionSize = cocos2d::Size(1136, 640);
static cocos2d::Size smallResolutionSize = cocos2d::Size(852, 480);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1136, 640);
static cocos2d::Size largeResolutionSize = cocos2d::Size(1136, 640);
//Screen Size
#define SCREEN_SIZE cocos2d::CCDirector::sharedDirector()->getVisibleSize();

//Resource Scale
#define RESOURCE_SCALE	((CCDirector::sharedDirector()->getVisibleSize().width/designResolutionSize.width) > (CCDirector::sharedDirector()->getVisibleSize().height/designResolutionSize.height) ?\
						 (CCDirector::sharedDirector()->getVisibleSize().width/designResolutionSize.width) : (CCDirector::sharedDirector()->getVisibleSize().height/designResolutionSize.height))

#define RESOURCE_SCALEX (CCDirector::sharedDirector()->getVisibleSize().width/designResolutionSize.width)

#define RESOURCE_SCALEY (CCDirector::sharedDirector()->getVisibleSize().height/designResolutionSize.height)


#define FONTS1 "fonts/yahei.ttf"
#define  FONTS2 "fonts/STXingkai.ttf"
#define sqlhttp "http://192.168.1.103:8080/"

using namespace std;
using namespace protocol;
static string g_version = cocos2d::cocos2dVersion();

/************************************************************************/
/* 包头                                                                 */
/************************************************************************/
typedef struct _Head
{
	char _req[3];//服务器序列号
	char _stamp;
	char _bodylen[2];//长度
	char _cmd[4];//cmd
}Head, *PHead;

#define HEADLEN sizeof(_Head)
#define REPLACESTRR "||||&***#@"
#define REPLACESTRN "%^&*():"
#endif /* __APPMACROS_H__ */
