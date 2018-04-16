package org.ylgame.com.wxapi;






import org.ylgame.com.AppActivity;
import com.tencent.mm.opensdk.constants.ConstantsAPI;
import com.tencent.mm.opensdk.modelbase.BaseReq;
import com.tencent.mm.opensdk.modelbase.BaseResp;
import com.tencent.mm.opensdk.modelpay.PayResp;
import com.tencent.mm.opensdk.openapi.IWXAPI;
import com.tencent.mm.opensdk.openapi.IWXAPIEventHandler;
import com.tencent.mm.opensdk.openapi.WXAPIFactory;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;

public class WXPayEntryActivity extends Activity implements IWXAPIEventHandler{
	
	private static final String TAG = "MicroMsg.SDKSample.WXPayEntryActivity";
	
    private IWXAPI api;
	
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        
    	api = WXAPIFactory.createWXAPI(this, AppActivity.APP_ID);
        api.handleIntent(getIntent(), this);
    }

	@Override
	protected void onNewIntent(Intent intent) {
		super.onNewIntent(intent);
		setIntent(intent);
        api.handleIntent(intent, this);
	}

	@Override
	public void onReq(BaseReq req) {
	}

	@Override
	public void onResp(BaseResp resp) {
		Log.d(TAG, "onPayFinish, errCode = " + resp.errCode);
		switch(resp.errCode) {
		case BaseResp.ErrCode.ERR_OK:
			if (resp.getType() == ConstantsAPI.COMMAND_PAY_BY_WX) {
				PayResp reques=(PayResp)resp;
				System.out.println("微信支付成功");
				//CppHelper.payResult(Integer.valueOf(reques.prepayId), reques.returnKey);
			}
			break;
		case BaseResp.ErrCode.ERR_USER_CANCEL:
			System.out.println("用户取消微信支付");
			break;
		case BaseResp.ErrCode.ERR_AUTH_DENIED:
			System.out.println("֧微信支付结束");
			break;
		default:
			System.out.println("֧其他未知错误");
			break;
		}
	}
}