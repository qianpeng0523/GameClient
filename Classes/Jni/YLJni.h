
#ifndef __YLJni_H__
#define __YLJni_H__

#include "cocos2d.h"
#include "Adaptation.h"

using namespace cocos2d;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include <jni.h>
#include "platform/android/jni/JniHelper.h"

#endif

extern "C" {
	class	YLJni{
	public:
		static void WeixinLogin();
		static void WeixinPay(const char* prepayid, const char* noncestr, const char* timestamp, const char* sign);
	};
}

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#ifdef __cplusplus
extern "C" {
#endif
	
	JNIEXPORT void JNICALL Java_org_ylgame_com_CppHelper_WXLoginSucess
		(JNIEnv *, jclass, jstring);
#ifdef __cplusplus
}
#endif
#endif

#endif // __ANDROID_COCOS2D_YLJni_H__
