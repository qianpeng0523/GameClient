package org.ylgame.com.wxapi;

import org.ylgame.com.AppActivity;
import org.ylgame.com.CppHelper;

import com.tencent.mm.opensdk.constants.ConstantsAPI;
import com.tencent.mm.opensdk.modelbase.BaseReq;
import com.tencent.mm.opensdk.modelbase.BaseResp;
import com.tencent.mm.opensdk.modelmsg.SendAuth;
import com.tencent.mm.opensdk.openapi.IWXAPIEventHandler;

import android.app.Activity;
import android.os.Bundle;
import android.widget.Toast;

public class WXEntryActivity extends Activity implements IWXAPIEventHandler{
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
    	AppActivity.api.handleIntent(getIntent(), this);
	}

	@Override
	public void onReq(BaseReq arg0) {
		Toast.makeText(this, "launch result = 111111111", Toast.LENGTH_LONG).show();
	}
	
	@Override
	public void onResp(BaseResp resp) {
		switch(resp.errCode) {
			case BaseResp.ErrCode.ERR_OK:
				if(resp.getType()==ConstantsAPI.COMMAND_SENDAUTH){
					SendAuth.Resp sendResp = (SendAuth.Resp) resp;
					AppActivity._weixincode=sendResp.code;
					System.out.println(AppActivity._weixincode+":"+sendResp.openId);
					CppHelper.WXLoginSucess(AppActivity._weixincode);
				}else if(resp.getType()==ConstantsAPI.COMMAND_JUMP_BIZ_TEMPSESSION){
					
					
				}else if(resp.getType()==ConstantsAPI.COMMAND_SENDMESSAGE_TO_WX){
					
				}
				break;
			case BaseResp.ErrCode.ERR_USER_CANCEL:
				System.out.println("用户取消操作");
				break;
			case BaseResp.ErrCode.ERR_AUTH_DENIED:
				System.out.println("用户拒绝授权");
				break;
			case BaseResp.ErrCode.ERR_UNSUPPORT:
				System.out.println("不支持该设备");
				break;
			case BaseResp.ErrCode.ERR_BAN:
				System.out.println("签名错误");
				break;
			default:
				System.out.println("其他错误");
				break;
		}
		
		finish();
	}
	
}
