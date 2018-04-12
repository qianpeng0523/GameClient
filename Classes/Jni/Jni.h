
#ifndef __Jni_H__
#define __Jni_H__

#include "cocos2d.h"
#include "Adaptation.h"

using namespace cocos2d;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include <jni.h>
#include "platform/android/jni/JniHelper.h"

#endif

extern "C" {
	class	Jni{
	public:
		static void IOSWeixinPaySuccess(const char*  transid);
		static void ReceivePlatformMsg(bool isSuccess, int payCode);//返回支付结果
		static void pay(int payCode, SEL_CallFuncN selector = NULL, Object *target = NULL, SEL_CallFuncN Faildselector = NULL, Object *Faildtarget = NULL);//支付
		static void call();//打电话
		static void exitGame();//退出游戏接口
		static void LoginSucess(const char* userid);//登录成功

		static void openUrl(string url);

		static void WeixinLogin();
		static bool isWeixinAvilible();
		static void shareWeixin(string url,string code ,string title,string content);
		static void InviteWeixinFriend(string url, string code, string title, string content);
		static void InviteFriend(string url, string code, string title, string content);
		static void shareBillToFriend(string path, string title);
		static void shareSecondFriend(string path,string title);
		static void shareFriends(string url, string code, string title, string content);
		static void ShowLoading();
		static void HideLoading();

		static void restartApp();
		static string getVersion();

        static void WexinPay(string payreq, string noncestr, string timestamp, string sign);
	
		static void getNetInfo(int &netType, int &netLevel);
		static int getBatteryLevel();
	};
}

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#ifdef __cplusplus
extern "C" {
#endif
	JNIEXPORT void JNICALL Java_org_lxqcgame_com_CppHelper_payResult
		(JNIEnv *, jclass, jboolean, jint);
	
	JNIEXPORT void JNICALL Java_org_lxqcgame_com_CppHelper_LoginSucess
		(JNIEnv *, jclass, jstring);

	JNIEXPORT void JNICALL Java_org_lxqcgame_com_CppHelper_WeixinCode
		(JNIEnv *, jclass, jstring);
	JNIEXPORT void JNICALL Java_org_lxqcgame_com_CppHelper_InviteFriendSucess
		(JNIEnv *, jclass);
	JNIEXPORT void JNICALL Java_org_lxqcgame_com_CppHelper_WeixinPaySuccess
		(JNIEnv *, jclass,jstring transid);
	
#ifdef __cplusplus
}
#endif
#endif

#endif // __ANDROID_COCOS2D_JNI_H__
