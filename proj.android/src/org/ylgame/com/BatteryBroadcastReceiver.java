package org.ylgame.com;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;


public class BatteryBroadcastReceiver extends BroadcastReceiver{
	//电量数值
    
    public static int batteryLevel = 0;
	
	//获取电量信息
	public static int getBatteryLevel() {
	    return batteryLevel;
	} 
    @Override
    public void onReceive(Context context, Intent intent) {
        // TODO Auto-generated method stub
        //判断它是否是为电量变化的Broadcast Action
        if(Intent.ACTION_BATTERY_CHANGED.equals(intent.getAction())){
            //获取当前电量
            int level = intent.getIntExtra("level", 0);
            //电量的总刻度
            int scale = intent.getIntExtra("scale", 100);
            //把它转成百分比
            batteryLevel =  level * 100 / scale;
        }
    }

   
};

