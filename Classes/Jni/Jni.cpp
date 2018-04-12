#include "Jni.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "GameControl.h"



#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "IosUtils.h"
#endif

#define JAVA_CPP_HALPER_CLASS "org/lxqcgame/com/CppHelper"
#define JAVA_CPP_HALPER_CLASS_POTHO "org/lxqcgame/com/JniInterface"
#define JAVA_CPP_HALPER_CLASS_AUDIO "com/example/weixinrecord/AudioCppHelper"

using namespace cocos2d;
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
static JniMethodInfo minfo;
#endif

void Jni::ReceivePlatformMsg(bool isSuccess, int payCode)
{
	
}

void Jni::LoginSucess(const char * userid){
	//登录成功，需要发送信息给服务器验证
	
}

void Jni::IOSWeixinPaySuccess(const char* transid){
   
}

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
JNIEXPORT void JNICALL Java_org_lxqcgame_com_CppHelper_payResult
(JNIEnv * env, jclass c, jboolean isSuccess, jint payCode)
{
	Jni::ReceivePlatformMsg((bool)isSuccess, (int)payCode);
}

JNIEXPORT void JNICALL Java_org_lxqcgame_com_CppHelper_WeixinPaySuccess
(JNIEnv *env, jclass c,jstring transid){
	const char* chars = env->GetStringUTFChars(transid, NULL);
	string ret=chars;
	env->ReleaseStringUTFChars(transid, chars);
	BuyHandInfo::getIns()->SendCWxpayQuery();
}


JNIEXPORT void JNICALL Java_org_lxqcgame_com_CppHelper_WeixinCode
(JNIEnv * env, jclass c,jstring code){
	log("WeixinCode!!!!!!!!!!!");
	const char* chars = env->GetStringUTFChars(code, NULL);
	string ret=chars;
	env->ReleaseStringUTFChars(code, chars);
	log("WeixinCode!!!!!!!!!!!:%s",ret.c_str());
	GameControl::getIns()->setWeixinCodeAndOpenid(ret);
}

JNIEXPORT void JNICALL Java_org_lxqcgame_com_CppHelper_InviteFriendSucess
(JNIEnv * env, jclass c){
	log("InviteFriendSucess!!!!!!!!!!!");
	GameControl::getIns()->ShareFriendSucess();
}

JNIEXPORT void JNICALL Java_org_lxqcgame_com_CppHelper_LoginSucess
(JNIEnv * env, jclass c, jstring userid)
{
	const char* uid = env->GetStringUTFChars(userid, 0);
	Jni::LoginSucess(uid);
}

#endif


void Jni::pay(int payCode, SEL_CallFuncN selector, Object *target, SEL_CallFuncN Faildselector, Object *Faildtarget)
{
	
}

void Jni::call(){
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo minfo;
	bool isHave = JniHelper::getStaticMethodInfo(minfo,JAVA_CPP_HALPER_CLASS, "call", "()V");
	if(isHave){
		minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
	}
#elif(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32||CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	//ReceivePlatformMsg(true, payType, payCode);
#endif
}

void Jni::exitGame(){
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo minfo;
	bool isHave = JniHelper::getStaticMethodInfo(minfo, JAVA_CPP_HALPER_CLASS, "exitGame", "()V");
	if (isHave){
		minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
	}
#endif
}

void Jni::openUrl(string url){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo t;
	bool isgetMethod = JniHelper::getStaticMethodInfo(t,
		JAVA_CPP_HALPER_CLASS_POTHO, "openUrl",
		"(Ljava/lang/String;)V");
	if (isgetMethod) {
		jstring jstr1 = t.env->NewStringUTF(url.c_str());
		t.env->CallStaticVoidMethod(t.classID, t.methodID, jstr1);
	}
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    IosUtils::openUrl(url.c_str());
#endif	
}

void Jni::shareBillToFriend(string path,string title){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo t;
	bool isgetMethod = JniHelper::getStaticMethodInfo(t,
		JAVA_CPP_HALPER_CLASS, "shareBillToFriend",
		"(Ljava/lang/String;Ljava/lang/String;)V");
	if (isgetMethod) {
		jstring jstr1 = t.env->NewStringUTF(path.c_str());
		jstring jstr2 = t.env->NewStringUTF(title.c_str());
		t.env->CallStaticVoidMethod(t.classID, t.methodID, jstr1, jstr2);
	}
#elif(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    IosUtils::shareBillToFriend((char *)path.c_str(),(char *)title.c_str());
#endif
}

void Jni::shareSecondFriend(string path,string title){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo t;
	bool isgetMethod = JniHelper::getStaticMethodInfo(t,
		JAVA_CPP_HALPER_CLASS, "shareSecondFriend",
		"(Ljava/lang/String;Ljava/lang/String;)V");
	if (isgetMethod) {
		jstring jstr1 = t.env->NewStringUTF(path.c_str());
		jstring jstr2 = t.env->NewStringUTF(title.c_str());
		t.env->CallStaticVoidMethod(t.classID, t.methodID, jstr1,jstr2);
	}
#elif(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	IosUtils::shareSecondFriend((char *)path.c_str(),(char *)title.c_str());
#endif
}

void Jni::WeixinLogin(){
	log("Jni::WeixinLogin");
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		JniMethodInfo t;
		bool isgetMethod = JniHelper::getStaticMethodInfo(t,
			JAVA_CPP_HALPER_CLASS, "WeixinLogin",
			"()V");
		if (isgetMethod) {
			t.env->CallStaticVoidMethod(t.classID, t.methodID);
		}
#elif(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        IosUtils::WeixinLogin();
#else
        
#endif
}

void Jni::InviteWeixinFriend(string url, string code, string title, string content){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		JniMethodInfo t;
		bool isgetMethod = JniHelper::getStaticMethodInfo(t,
			JAVA_CPP_HALPER_CLASS, "InviteWeixinFriend",
			"(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
		if (isgetMethod) {
			jstring str = t.env->NewStringUTF(url.c_str());
			jstring str1 = t.env->NewStringUTF(code.c_str());
			jstring str2 = t.env->NewStringUTF(title.c_str());
			jstring str3 = t.env->NewStringUTF(content.c_str());
			t.env->CallStaticVoidMethod(t.classID, t.methodID,str,str1,str2,str3);
		}
#elif(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        IosUtils::InviteWeixinFriend(url.c_str(),code.c_str(),title.c_str(),content.c_str());
#else
        
#endif
}

void Jni::InviteFriend(string url, string code, string title, string content){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo t;
	bool isgetMethod = JniHelper::getStaticMethodInfo(t,
		JAVA_CPP_HALPER_CLASS, "InviteFriend",
		"(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
	if (isgetMethod) {
		jstring str = t.env->NewStringUTF(url.c_str());
		jstring str1 = t.env->NewStringUTF(code.c_str());
		jstring str2 = t.env->NewStringUTF(title.c_str());
		jstring str3 = t.env->NewStringUTF(content.c_str());
		t.env->CallStaticVoidMethod(t.classID, t.methodID, str, str1, str2, str3);
	}
#elif(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	IosUtils::InviteFriend(url.c_str(), code.c_str(), title.c_str(), content.c_str());
#else

#endif
}

bool Jni::isWeixinAvilible(){
	bool voice = false;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo t;
	bool isgetMethod = JniHelper::getStaticMethodInfo(t,
		JAVA_CPP_HALPER_CLASS, "isWeixinAvilible",
		"()Z");
	if (isgetMethod) {
		jboolean v = t.env->CallStaticBooleanMethod(t.classID, t.methodID);
		voice = (bool)v;
	}
#elif(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    voice=IosUtils::isWeixinAvilible();
#endif
	log("voice:%d", voice);
	return voice;
}

void Jni::shareWeixin(string url, string code,string title,string content){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)


		JniMethodInfo t;
		bool isgetMethod = JniHelper::getStaticMethodInfo(t,
			JAVA_CPP_HALPER_CLASS, "shareWeixin",
			"(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
		if (isgetMethod) {
			jstring str = t.env->NewStringUTF(url.c_str());
			jstring str1 = t.env->NewStringUTF(code.c_str());
			jstring str2 = t.env->NewStringUTF(title.c_str());
			jstring str3 = t.env->NewStringUTF(content.c_str());
			t.env->CallStaticVoidMethod(t.classID, t.methodID,str,str1,str2,str3);
		}
#elif(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	IosUtils::shareWeixin(url.c_str(), code.c_str(),title.c_str(), content.c_str());
#endif
}

void Jni::shareFriends(string url, string code, string title, string content){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo t;
	bool isgetMethod = JniHelper::getStaticMethodInfo(t,
		JAVA_CPP_HALPER_CLASS, "shareFriends",
		"(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
	if (isgetMethod) {
		jstring str = t.env->NewStringUTF(url.c_str());
		jstring str1 = t.env->NewStringUTF(code.c_str());
		jstring str2 = t.env->NewStringUTF(title.c_str());
		jstring str3 = t.env->NewStringUTF(content.c_str());
		t.env->CallStaticVoidMethod(t.classID, t.methodID,str,str1,str2,str3);
	}
#elif(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	IosUtils::shareFriends(url.c_str(), code.c_str(), title.c_str(), content.c_str());
#endif
}

void Jni::ShowLoading(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

	JniMethodInfo t;
	bool isgetMethod = JniHelper::getStaticMethodInfo(t,
		JAVA_CPP_HALPER_CLASS, "ShowLoading",
		"()V");
	if (isgetMethod) {
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
	}
#elif(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#endif
}

void Jni::HideLoading(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

	JniMethodInfo t;
	bool isgetMethod = JniHelper::getStaticMethodInfo(t,
		JAVA_CPP_HALPER_CLASS, "HideLoading",
		"()V");
	if (isgetMethod) {
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
	}
#elif(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#endif
}

void Jni::restartApp(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

	JniMethodInfo t;
	bool isgetMethod = JniHelper::getStaticMethodInfo(t,
		JAVA_CPP_HALPER_CLASS, "restartApp",
		"()V");
	if (isgetMethod) {
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
	}
#elif(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#endif
}


string Jni::getVersion(){
	string version;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

	JniMethodInfo t;
	bool isgetMethod = JniHelper::getStaticMethodInfo(t,
		JAVA_CPP_HALPER_CLASS, "getVersion",
		"()Ljava/lang/String;");
	if (isgetMethod) {
		jstring filepath = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
		version = t.env->GetStringUTFChars(filepath, NULL);
	}
#elif(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	version = IosUtils::getVersion();
#endif
	return version;
}

void Jni::WexinPay(string payreq, string noncestr, string timestamp, string sign){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    
    JniMethodInfo t;
    bool isgetMethod = JniHelper::getStaticMethodInfo(t,
                                                      JAVA_CPP_HALPER_CLASS, "WexinPay",
                                                      "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
    if (isgetMethod) {
        jstring str = t.env->NewStringUTF(payreq.c_str());
        jstring str1 = t.env->NewStringUTF(noncestr.c_str());
        jstring str2 = t.env->NewStringUTF(timestamp.c_str());
        jstring str3 = t.env->NewStringUTF(sign.c_str());
        t.env->CallStaticVoidMethod(t.classID, t.methodID,str,str1,str2,str3);
    }
#elif(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    IosUtils::WexinPay(payreq.c_str(), noncestr.c_str(), timestamp.c_str(), sign.c_str());
#endif
}

void Jni::getNetInfo(int &netType, int &netLevel)
{
	string ni;
	netType = 1;
	netLevel = 0;
#if( CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo t;
	bool isHave = JniHelper::getStaticMethodInfo(t, JAVA_CPP_HALPER_CLASS, "getNetInfo", "()Ljava/lang/String;");
	if (isHave)
	{
		jstring ss = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
		ni = t.env->GetStringUTFChars(ss, NULL);
		
	}
	else
	{
		log("JniFun call getNetInfo error!");
	}
#elif(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	ni= IosUtils::getNetInfo();
	
#endif
	int index =ni.find("#");
	if (index != -1){
		netType = atoi(ni.substr(0, index).c_str());
		netLevel = atoi(ni.substr(index + 1, ni.length()).c_str());
		log("netType:%d,netLevel:%d", netType, netLevel);
	}
}

int Jni::getBatteryLevel(){
	int  level = 100;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo t;
	bool isgetMethod = JniHelper::getStaticMethodInfo(t,
		JAVA_CPP_HALPER_CLASS, "getBatteryLevel",
		"()I");
	if (isgetMethod) {
		jint jb = (jint)t.env->CallStaticIntMethod(t.classID, t.methodID);
		level = (int)jb;
	}
#elif(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    level = extracted();
#endif
	return level;
}