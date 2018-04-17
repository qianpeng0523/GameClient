/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
 
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
package org.ylgame.com;

import java.util.Map;

import org.cocos2dx.lib.Cocos2dxActivity;

import com.alipay.sdk.app.EnvUtils;
import com.alipay.sdk.app.PayTask;
import com.tencent.mm.opensdk.modelmsg.SendAuth;
import com.tencent.mm.opensdk.modelpay.PayReq;
import com.tencent.mm.opensdk.openapi.WXAPIFactory;

import android.annotation.SuppressLint;
import android.content.Context;
import android.media.MediaRecorder;
//import cn.cmgame.billing.api.BillingResult;
//import cn.cmgame.billing.api.GameInterface;
//import cn.cmgame.billing.api.LoginResult;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.os.PowerManager;
import android.os.PowerManager.WakeLock;
import android.util.Log;
import android.widget.Toast;

public class AppActivity extends Cocos2dxActivity{
	public static AppActivity main;
	public static DeviceInfo deviinfo;
    PowerManager powerManager = null;
    WakeLock wakeLock = null;
    
    public static final String APP_ID="wxd5d25d59ae13ac95";
    public static final String partnerId="1501106141";
    public static com.tencent.mm.opensdk.openapi.IWXAPI api;
    private static final int SDK_PAY_FLAG = 1;
    public static String _weixincode;
    public String _uid;
   
	@SuppressWarnings("deprecation")
	@Override
	public void onCreate(Bundle savedInstanceState) {
		EnvUtils.setEnv(EnvUtils.EnvEnum.SANDBOX);
		super.onCreate(savedInstanceState);
		main=AppActivity.this;
		
		this.powerManager = (PowerManager) this.getSystemService(Context.POWER_SERVICE);  
		this.wakeLock = this.powerManager.newWakeLock(PowerManager.FULL_WAKE_LOCK, "My Lock");
		//Login("123456789012345");
		
		//	
		AppActivity.api=WXAPIFactory.createWXAPI(this, AppActivity.APP_ID);
    	AppActivity.api.registerApp(AppActivity.APP_ID);
    	
        MediaRecorder mRecorders = new MediaRecorder();
        mRecorders.setAudioSource(MediaRecorder.AudioSource.MIC);
        
        deviinfo=new DeviceInfo(main);
	}
	
	public void WeixinLogin() {
		SendAuth.Req req = new SendAuth.Req();
	    req.scope = "snsapi_userinfo";
	    req.state = "wechat_sdk_demo_test";
	    req.transaction="login";
	    boolean flag = AppActivity.api.sendReq(req);
	    if(flag){
	    	System.out.println("微信启动成功");
	    }else{
	    	System.out.println("微信启动失败");
	    }
		//Toast.makeText(_context, "launch result = " + AppActivity.api.openWXApp(), Toast.LENGTH_LONG).show();
	}
	public void WeixinPay(String payreq, String noncestr,String timestamp, String sign){
		PayReq request = new PayReq();
		request.appId = APP_ID;
		request.partnerId = partnerId;
		request.prepayId= payreq;
		request.packageValue = "Sign=WXPay";
		request.nonceStr= noncestr;
		
		request.timeStamp= timestamp;
		request.sign= sign;
		
		api.sendReq(request);
	}
	
	
	@SuppressLint("HandlerLeak") 
	private Handler mHandler = new Handler() {
		@SuppressWarnings("unused")
		public void handleMessage(Message msg) {
			switch (msg.what) {
			case SDK_PAY_FLAG: {
				@SuppressWarnings("unchecked")
				PayResult payResult = new PayResult((Map<String, String>) msg.obj);
				
				String resultInfo = payResult.getResult();//
				String resultStatus = payResult.getResultStatus();
				//
				if (resultStatus.equalsIgnoreCase("9000")) {
					//
					Toast.makeText(AppActivity.this, "֧支付成功", Toast.LENGTH_SHORT).show();
				} else {
					//
					Toast.makeText(AppActivity.this, "֧支付失败", Toast.LENGTH_SHORT).show();
				}
				break;
			}
			
			default:
				break;
			}
		};
	};
	
	public void AliPay(String appid,String timestamp,String orderinfo,String privatekey,String notifyurl){
		Map<String, String> params = OrderInfoUtil2_0.buildOrderParamMap(appid,orderinfo,timestamp,notifyurl, true);
		String orderParam = OrderInfoUtil2_0.buildOrderParam(params);

		String sign = OrderInfoUtil2_0.getSign(params, privatekey, true);
		final String orderInfo = orderParam + "&" + sign;
		
		Runnable payRunnable = new Runnable() {

			@Override
			public void run() {
				PayTask alipay = new PayTask(AppActivity.this);
				Map<String, String> result = alipay.payV2(orderInfo, true);
				Log.i("msp", result.toString());
				
				Message msg = new Message();
				msg.what = SDK_PAY_FLAG;
				msg.obj = result;
				mHandler.sendMessage(msg);
			}
		};

		Thread payThread = new Thread(payRunnable);
		payThread.start();
	}
	
    @Override 
    protected void onResume(){  
    	super.onResume();  
    	this.wakeLock.acquire(); 
    	
    }
    @Override 
    protected void onPause(){
    	super.onPause();  
    	this.wakeLock.release(); 
    	
    }

    
   
}
