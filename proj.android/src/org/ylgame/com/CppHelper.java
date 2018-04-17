package org.ylgame.com;


public class CppHelper {
	
	public native static void WXLoginSucess(String code);
	public native static void AliPaySucess(String content);
	public static void WeixinLogin(){
		System.out.println("WeixinLogin:");
		AppActivity.main.WeixinLogin();
	}
	
	public static void WeixinPay(String prepayid,String noncestr,String timestamp,String sign){
		System.out.println("WeixinPay:"+prepayid+","+noncestr+","+timestamp+","+sign);
		AppActivity.main.WeixinPay(prepayid,noncestr,timestamp,sign);
	}
	
	public static void AliPay(String appid,String timestamp,String orderinfo,String privatekey){
		System.out.println("AliPay:"+appid+","+timestamp+","+orderinfo+","+privatekey);
		AppActivity.main.AliPay(appid,timestamp,orderinfo,privatekey,"http://www.lesharecs.com/alipaycallback");
	}
}


