package org.ylgame.com;

import java.io.UnsupportedEncodingException;
import java.net.URLEncoder;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Date;
import java.util.HashMap;
import java.util.List;
import java.util.Locale;
import java.util.Map;
import java.util.Random;

public class OrderInfoUtil2_0 {
	/**
	 * 閺嬪嫰锟界姵鏁禒妯款吂閸楁洖寮弫鏉垮灙鐞涳拷
	 * @param pid
	 * @param app_id
	 * @param target_id
	 * @return
	 */
	public static Map<String, String> buildOrderParamMap(String app_id,String content,String timestamp,String notifyurl, boolean rsa2) {
		Map<String, String> keyValues = new HashMap<String, String>();
		keyValues.put("app_id", app_id);
		keyValues.put("biz_content", content);
		keyValues.put("charset", "utf-8");
		keyValues.put("method", "alipay.trade.app.pay");
		keyValues.put("notify_url", notifyurl);
		keyValues.put("return_url", notifyurl);
		keyValues.put("sign_type", rsa2 ? "RSA2" : "RSA");
		keyValues.put("timestamp", timestamp);
		keyValues.put("version", "1.0");
		return keyValues;
	}
	
	/**
	 * 閺嬪嫰锟界姵鏁禒妯款吂閸楁洖寮弫棰佷繆閹拷
	 * 
	 * @param map
	 * 閺�垯绮拋銏犲礋閸欏倹鏆�
	 * @return
	 */
	public static String buildOrderParam(Map<String, String> map) {
		List<String> keys = new ArrayList<String>(map.keySet());

		StringBuilder sb = new StringBuilder();
		for (int i = 0; i < keys.size() - 1; i++) {
			String key = keys.get(i);
			String value = map.get(key);
			sb.append(buildKeyValue(key, value, true));
			sb.append("&");
		}

		String tailKey = keys.get(keys.size() - 1);
		String tailValue = map.get(tailKey);
		sb.append(buildKeyValue(tailKey, tailValue, true));

		return sb.toString();
	}
	
	/**
	 * 閹峰吋甯撮柨顔硷拷鐓庮嚠
	 * 
	 * @param key
	 * @param value
	 * @param isEncode
	 * @return
	 */
	private static String buildKeyValue(String key, String value, boolean isEncode) {
		StringBuilder sb = new StringBuilder();
		sb.append(key);
		sb.append("=");
		if (isEncode) {
			try {
				sb.append(URLEncoder.encode(value, "UTF-8"));
			} catch (UnsupportedEncodingException e) {
				sb.append(value);
			}
		} else {
			sb.append(value);
		}
		return sb.toString();
	}
	
	/**
	 * 鐎佃鏁禒妯哄棘閺侀淇婇幁顖濈箻鐞涘瞼顒烽崥锟�
	 * 
	 * @param map
	 *            瀵板懐顒烽崥宥嗗房閺夊啩淇婇幁锟�
	 * 
	 * @return
	 */
	public static String getSign(Map<String, String> map, String rsaKey, boolean rsa2) {
		List<String> keys = new ArrayList<String>(map.keySet());
		// key閹烘帒绨�
		Collections.sort(keys);

		StringBuilder authInfo = new StringBuilder();
		for (int i = 0; i < keys.size() - 1; i++) {
			String key = keys.get(i);
			String value = map.get(key);
			authInfo.append(buildKeyValue(key, value, false));
			authInfo.append("&");
		}

		String tailKey = keys.get(keys.size() - 1);
		String tailValue = map.get(tailKey);
		authInfo.append(buildKeyValue(tailKey, tailValue, false));

		String oriSign = SignUtils.sign(authInfo.toString(), rsaKey, rsa2);
		String encodedSign = "";
		if(oriSign!=null){
			try {
				encodedSign = URLEncoder.encode(oriSign, "UTF-8");
			} catch (UnsupportedEncodingException e) {
				e.printStackTrace();
			}
		}
		return "sign=" + encodedSign;
	}
	
	/**
	 * 鐟曚焦鐪版径鏍劥鐠併垹宕熼崣宄扮箑妞よ鏁稉锟介妴锟�
	 * @return
	 */
	private static String getOutTradeNo() {
		SimpleDateFormat format = new SimpleDateFormat("MMddHHmmss", Locale.getDefault());
		Date date = new Date();
		String key = format.format(date);

		Random r = new Random();
		key = key + r.nextInt();
		key = key.substring(0, 15);
		return key;
	}

}
