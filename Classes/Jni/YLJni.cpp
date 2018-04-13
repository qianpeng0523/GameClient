#include "YLJni.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "GameControl.h"
#include "deprecated/CCNotificationCenter.h"
#include "LoginInfo.h"

#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "IosUtils.h"
#endif

#define JAVA_CPP_HALPER_CLASS "org/ylgame/com/CppHelper"

using namespace cocos2d;
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
static JniMethodInfo minfo;
#endif

void YLJni::WeixinLogin(){
	
}

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

JNIEXPORT void JNICALL Java_org_ylgame_com_CppHelper_WXLoginSucess
(JNIEnv * env, jclass c, jstring acctoken)
{
	const char* token = env->GetStringUTFChars(acctoken, 0);
	LoginInfo::getIns()->setWxToken(token);
	CCNotificationCenter::sharedNotificationCenter()->postNotification(NOTICE_WXLOGIN,NULL);
}

#endif
