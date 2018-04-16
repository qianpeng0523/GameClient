/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
*/
package org.ylgame.com;

import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.telephony.PhoneStateListener;
import android.telephony.SignalStrength;
import android.telephony.TelephonyManager;
import android.util.Log;


public class DeviceInfo {
	//缃戠粶鐘舵�寮哄�?
    public static final int NETLEVEL_STRENGTH_NONE_OR_UNKNOWN = 0;
    public static final int NETLEVEL_STRENGTH_POOR = 1;
    public static final int NETLEVEL_STRENGTH_MODERATE = 2;
    public static final int NETLEVEL_STRENGTH_GOOD = 3;
    public static final int NETLEVEL_STRENGTH_GREAT = 4;

    //淇�?�彿鐩戝�?
    TelephonyManager        Tel;  
    MyPhoneStateListener    MyListener; 
    public static int singnalLevel;

    //Wifi鐩戝�?
    private static WifiInfo wifiInfo = null;
    private static WifiManager wifiManager = null; 
    public static int wifiLevel;
  //瀹氫箟鏁扮粍鐢ㄤ簬杩斿洖
    static int[] netInfo = new int[2];
    
    BatteryBroadcastReceiver receiver = new BatteryBroadcastReceiver();
    IntentFilter filter = new IntentFilter(Intent.ACTION_BATTERY_CHANGED);
	static private Context appactivity;
	
	public DeviceInfo(Context con){
		appactivity=con;
		//娣诲姞淇″彿寮哄害鐩戝惉
        MyListener = new MyPhoneStateListener();
        Tel = (TelephonyManager)con.getSystemService(Context.TELEPHONY_SERVICE);
        Tel.listen(MyListener, PhoneStateListener.LISTEN_SIGNAL_STRENGTHS);

        //娣诲姞wifi寮哄害鐩戝惉
        wifiManager = (WifiManager)con.getSystemService(Context.WIFI_SERVICE);
        
        con.registerReceiver(receiver, filter);
	}
	
	public void onPause() {
        Tel.listen(MyListener, PhoneStateListener.LISTEN_NONE);
        appactivity.unregisterReceiver(receiver);
    }
    
	public void onResume() {
        Tel.listen(MyListener, PhoneStateListener.LISTEN_SIGNAL_STRENGTHS);
        appactivity.registerReceiver(receiver,filter);
    }
	
	//--------------------------------------缃戠粶绫诲�?�鍙婂己搴� begin------------------------------------------
    

    //netType   -1: 娌℃湁缃戠粶    1: WIFI     2: 绉诲姩鏁版嵁
    //netLevel  1: None 2:poor  3:moderate  4:good  5:great 
    public static String getNetInfo() {
        Log.d("getNetInfo", "enter the function getNetInfo ----- ");
        //鏍规嵁Android鐨勫畨鍏ㄦ満鍒讹紝鍦ㄤ娇鐢�?�onnectivityManager鏃讹紝蹇呴�?�鍦ˋndroidManifest.xml涓坊鍔�uses-permission android:name="android.permission.ACCESS_NETWORK_STATE" /> 鍚﹀垯鏃犳硶鑾峰緱绯荤粺鐨勮鍙�
        ConnectivityManager connMgr = (ConnectivityManager)appactivity.getSystemService(Context.CONNECTIVITY_SERVICE);
        NetworkInfo networkInfo = connMgr.getActiveNetworkInfo();
        if( null == networkInfo)
            return "";
        int nType = networkInfo.getType();
        if (nType == ConnectivityManager.TYPE_MOBILE) {
            netInfo[0] = 2;
        }
        else if (nType == ConnectivityManager.TYPE_WIFI) {
            netInfo[0] = 1;
        }
        Log.d("getNetInfo", "java ---- netType --- "+ netInfo[0]);

        //according to netType. set the value of netLevel
        switch (netInfo[0]) {
        case 1:
            netInfo[1] = getWifiLevel();
            break;
        case 2:
            netInfo[1] = getSingnalLevel();
            break;
        default:
            break;
        }
        Log.d("getNetInfo", "java ---- netLevel --- "+ netInfo[1]);
        String ss=netInfo[0]+"#"+netInfo[1];
        return ss;
    }
	
  //鑾峰彇淇″彿寮哄�?
    public static int getSingnalLevel() {
         return singnalLevel;
    }

    //鑾峰彇wifi寮哄�?
    public static int getWifiLevel() {
        wifiInfo = wifiManager.getConnectionInfo();
        int wifiStrength = wifiInfo.getRssi();
        if (wifiStrength <= 0 && wifiStrength >= -50) {  
            wifiLevel = NETLEVEL_STRENGTH_GREAT;
        } else if (wifiStrength < -50 && wifiStrength >= -70) {  
            wifiLevel = NETLEVEL_STRENGTH_GOOD; 
        } else if (wifiStrength < -70 && wifiStrength >= -80) {  
            wifiLevel = NETLEVEL_STRENGTH_MODERATE;
        } else if (wifiStrength < -80 && wifiStrength >= -100) {  
            wifiLevel = NETLEVEL_STRENGTH_POOR; 
        } else {  
            wifiLevel = NETLEVEL_STRENGTH_NONE_OR_UNKNOWN; 
        } 
        return wifiLevel;
    }
    
	//淇�?�彿寮哄害绛夌骇
    private class MyPhoneStateListener extends PhoneStateListener  
    {  
      @Override  
      public void onSignalStrengthsChanged(SignalStrength signalStrength)  
      {  
         super.onSignalStrengthsChanged(signalStrength);  
         int asu = signalStrength.getGsmSignalStrength();
         if (asu <= 2 || asu == 99) singnalLevel = NETLEVEL_STRENGTH_NONE_OR_UNKNOWN;
         else if (asu >= 12) singnalLevel = NETLEVEL_STRENGTH_GREAT;
         else if (asu >= 8)  singnalLevel = NETLEVEL_STRENGTH_GOOD;
         else if (asu >= 5)  singnalLevel = NETLEVEL_STRENGTH_MODERATE;
         else singnalLevel = NETLEVEL_STRENGTH_POOR;
      }  
    };/* End of private Class */  
  //--------------------------------------缃戠粶绫诲�?�鍙婂己搴� end------------------------------------------  
    
    
}
