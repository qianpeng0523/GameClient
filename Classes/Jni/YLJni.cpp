#include "YLJni.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "GameControl.h"
#include "deprecated/CCNotificationCenter.h"
#include "LoginInfo.h"
#include "HallInfo.h"
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "IosUtils.h"
#endif

#define JAVA_CPP_HALPER_CLASS "org/ylgame/com/CppHelper"

using namespace cocos2d;
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
static JniMethodInfo minfo;
#endif

void YLJni::WeixinLogin(){
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo minfo;
	bool isHave = JniHelper::getStaticMethodInfo(minfo, JAVA_CPP_HALPER_CLASS, "WeixinLogin", "()V");
	if(isHave){
		minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
	}
#elif(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32||CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	
#endif
}

void YLJni::WeixinPay(const char* prepayid, const char* noncestr, const char* timestamp, const char* sign){
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo minfo;
	bool isHave = JniHelper::getStaticMethodInfo(minfo, JAVA_CPP_HALPER_CLASS, "WeixinPay", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
	if (isHave){
		jstring jstr = minfo.env->NewStringUTF(prepayid);
		jstring jstr1 = minfo.env->NewStringUTF(noncestr);
		jstring jstr2 = minfo.env->NewStringUTF(timestamp);
		jstring jstr3 = minfo.env->NewStringUTF(sign);
		minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, jstr, jstr1, jstr2, jstr3);
	}
#elif(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32||CC_TARGET_PLATFORM == CC_PLATFORM_WP8)

#endif
}


void YLJni::AliPay(const char* appid, const char* timestamp, const char* orderinfo, const char* privatekey){
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo minfo;
	bool isHave = JniHelper::getStaticMethodInfo(minfo, JAVA_CPP_HALPER_CLASS, "AliPay", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
	if (isHave){
		jstring jstr = minfo.env->NewStringUTF(appid);
		jstring jstr1 = minfo.env->NewStringUTF(timestamp);
		jstring jstr2 = minfo.env->NewStringUTF(orderinfo);
		jstring jstr3 = minfo.env->NewStringUTF(privatekey);
		minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, jstr, jstr1, jstr2, jstr3);
	}
#elif(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32||CC_TARGET_PLATFORM == CC_PLATFORM_WP8)

#endif
}





















#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

JNIEXPORT void JNICALL Java_org_ylgame_com_CppHelper_WXLoginSucess
(JNIEnv * env, jclass c, jstring acctoken)
{
	const char* token = env->GetStringUTFChars(acctoken, 0);
	log("111:%s",token);
	LoginInfo::getIns()->setWxToken(token);
	CCNotificationCenter::sharedNotificationCenter()->postNotification(NOTICE_WXLOGIN,NULL);
}

JNIEXPORT void JNICALL Java_org_ylgame_com_CppHelper_AliPaySucess
(JNIEnv * env, jclass c, jstring content)
{
	const char* content1 = env->GetStringUTFChars(content, 0);
	HallInfo::getIns()->SendCAliPayResult(content1);
}

#endif
