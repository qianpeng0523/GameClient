#include "Common.h"
#include "XXIconv.h"

using namespace cocos2d_xx;

Common::Common(){

}

Common::~Common() {

}

std::string& Common::replace_all(std::string& str, const std::string& old_value, const std::string& new_value)
{
	while (true)   {
		std::string::size_type   pos(0);
		if ((pos = str.find(old_value)) != std::string::npos)
			str.replace(pos, old_value.length(), new_value);
		else   break;
	}
	return   str;
}
std::string& Common::replace_all_distinct(std::string&   str, const   std::string&   old_value, const   std::string&   new_value)
{
	for (std::string::size_type pos(0); pos != std::string::npos; pos += new_value.length())   {
		if ((pos = str.find(old_value, pos)) != std::string::npos)
			str.replace(pos, old_value.length(), new_value);
		else   break;
	}
	return   str;
}

std::vector<std::string> Common::getStrings(std::string str, std::string findstr){
	std::vector<std::string> vecs;
	int index = str.find(findstr);
	int len = findstr.length();
	while (index != -1){
		std::string temp;
		temp = str.substr(0,index);
		if (!temp.empty()){
			vecs.push_back(temp);
		}
		str = str.substr(index + len, str.length());
		index = str.find(findstr);
	}
	vecs.push_back(str);
	return vecs;
}

bool Common::isHave(std::vector<std::string> vecs, std::string value){
	for (int i = 0; i < vecs.size(); i++){
		if (value == vecs.at(i)){
			return true;
		}
	}
	return false;
}

int Common::is_zh_ch(char p)
{
	/*汉字的两个字节的最高为都为1,这里采用判断最高位的方法
	将p字节进行移位运算，右移8位，这样，如果移位后是0，
	则说明原来的字节最高位为0，不是1那么也就不是汉字的一个字节
	*/
	if (~(p >> 8) == 0)
	{
		return 1;//代表不是汉字
	}
	return -1;
}

string Common::sub(string str, int count, string replace)
{

	if (typeid(str) == typeid(string) && str.length() > 0)
	{
		int len = str.length();
		string one = XXIconv::GBK2UTF("中");
		int ll = one.length();
		string tmp = "";

		//先把str里的汉字和英文分开
		vector <string> dump;
		int i = 0;
		int ct = 0;
		while (i < len)
		{
			if (is_zh_ch(str.at(i)) == 1)
			{
				dump.push_back(str.substr(i, ll));
				i = i + ll;
				ct++;
			}
			else
			{
				dump.push_back(str.substr(i, 1));
				i = i + 1;
				ct++;
			}
		}
		//直接从dump里取即可
		int co = count<ct?count:ct;
		for (int j = 0; j < co; j++)
		{
			tmp += dump[j];
		}
		if (ct-count>=3){
			tmp +=replace;
		}
		return tmp;
	}
	else
	{
		printf("str is not string\n");
		return "";

	}
}