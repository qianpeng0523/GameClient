#include "CardsStr.h"


string CardStr::g_cardswan[9] = {
	"1wan", "2wan", "3wan", "4wan", "5wan", "6wan", "7wan", "8wan", "9wan"
};

string CardStr::g_cardstiao[9] = {
	"1tiao", "2tiao", "3tiao", "4tiao", "5tiao", "6tiao", "7tiao", "8tiao", "9tiao"
};

string CardStr::g_cardstong[9] = {
	"1tong", "2tong", "3tong", "4tong", "5tong", "6tong", "7tong", "8tong", "9tong"
};

string CardStr::g_cardsfeng[7] = {
	"mj_dong", "mj_nan", "mj_xi", "mj_bei",
	"mj_zhong", "mj_fa", "baiban"
};

int CardStr::g_cards[34] = {
	0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,
	0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19,
	0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29,
	0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37
};

string CardStr::getCardStr(int card){
	int type = card / 16;
	int va = card % 16;
	char buff[50];
	string t;
	if (type == 0){
		t = CardStr::g_cardswan[va - 1];
	}
	else if (type == 1){
		t = CardStr::g_cardstiao[va - 1];
	}
	else if (type == 2){
		t = CardStr::g_cardstong[va - 1];
	}
	else if (type == 3){
		t = CardStr::g_cardsfeng[va - 1];
	}
	sprintf(buff, "%s.png", t.c_str());
	return buff;
}
