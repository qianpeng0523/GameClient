#include "MJCPH.h"
#include "GameControl.h"
#include "GameDataSet.h"
#include "ClientSocket.h"
#include "LoginScene.h"
#include "LoginInfo.h"
#include "GameHead.h"
#include "CardsStr.h"

string MJCPH::g_beistr[4][16] = { 
{ 
"majiang_pai_bj_cpg_b_10.png","majiang_pai_bj_cpg_b_10.png","majiang_pai_bj_cpg_b_10.png","majiang_pai_bj_cpg_b_10.png",
"majiang_pai_bj_cpg_b_10.png", "majiang_pai_bj_cpg_b_10.png", "majiang_pai_bj_cpg_b_10.png", "majiang_pai_bj_cpg_b_10.png",
"majiang_pai_bj_cpg_b_10.png", "majiang_pai_bj_cpg_b_10.png", "majiang_pai_bj_cpg_b_10.png", "majiang_pai_bj_cpg_b_10.png",
"majiang_pai_bj_cpg_b_10.png", "majiang_pai_bj_cpg_b_10.png", "majiang_pai_bj_cpg_b_10.png", "majiang_pai_bj_cpg_b_10.png"
}, 
{
"majiang_pai_sj_cpg_b_06.png", "majiang_pai_sj_cpg_b_06.png", "majiang_pai_sj_cpg_b_06.png", "majiang_pai_sj_cpg_b_06.png",
"majiang_pai_sj_cpg_b_05.png", "majiang_pai_sj_cpg_b_05.png", "majiang_pai_sj_cpg_b_05.png", "majiang_pai_sj_cpg_b_05.png",
"majiang_pai_sj_cpg_b_01.png", "majiang_pai_sj_cpg_b_01.png", "majiang_pai_sj_cpg_b_01.png", "majiang_pai_sj_cpg_b_01.png",
"majiang_pai_sj_cpg_b_02.png", "majiang_pai_sj_cpg_b_02.png", "majiang_pai_sj_cpg_b_02.png", "majiang_pai_sj_cpg_b_02.png",
},
{ 
"majiang_pai_dj_pd_04.png","majiang_pai_dj_pd_04.png","majiang_pai_dj_pd_04.png","majiang_pai_dj_pd_04.png",
"majiang_pai_dj_pd_04.png", "majiang_pai_dj_pd_04.png", "majiang_pai_dj_pd_04.png", "majiang_pai_dj_pd_04.png",
"majiang_pai_dj_pd_04.png", "majiang_pai_dj_pd_04.png", "majiang_pai_dj_pd_04.png", "majiang_pai_dj_pd_04.png",
"majiang_pai_dj_pd_04.png", "majiang_pai_dj_pd_04.png", "majiang_pai_dj_pd_04.png", "majiang_pai_dj_pd_04.png"
},
{
"majiang_pai_xj_cpg_b_00.png", "majiang_pai_xj_cpg_b_00.png", "majiang_pai_xj_cpg_b_00.png", "majiang_pai_xj_cpg_b_00.png",
"majiang_pai_xj_cpg_b_03.png", "majiang_pai_xj_cpg_b_03.png", "majiang_pai_xj_cpg_b_03.png", "majiang_pai_xj_cpg_b_03.png",
"majiang_pai_xj_cpg_b_10.png", "majiang_pai_xj_cpg_b_10.png", "majiang_pai_xj_cpg_b_10.png", "majiang_pai_xj_cpg_b_10.png",
"majiang_pai_xj_cpg_b_09.png", "majiang_pai_xj_cpg_b_09.png", "majiang_pai_xj_cpg_b_09.png", "majiang_pai_xj_cpg_b_09.png",
}
};

string MJCPH::g_paistr[4][16] = { { "majiang_pai_bj_cpg_z_12.png", "majiang_pai_bj_cpg_z_12.png", "majiang_pai_bj_cpg_z_12.png", "majiang_pai_bj_cpg_z_12.png" 
, "majiang_pai_bj_cpg_z_12.png", "majiang_pai_bj_cpg_z_12.png", "majiang_pai_bj_cpg_z_12.png", "majiang_pai_bj_cpg_z_12.png" 
, "majiang_pai_bj_cpg_z_12.png", "majiang_pai_bj_cpg_z_12.png", "majiang_pai_bj_cpg_z_12.png", "majiang_pai_bj_cpg_z_12.png" 
,"majiang_pai_bj_cpg_z_12.png", "majiang_pai_bj_cpg_z_12.png", "majiang_pai_bj_cpg_z_12.png", "majiang_pai_bj_cpg_z_12.png" },
{ "majiang_pai_sj_cpg_z_12.png", "majiang_pai_sj_cpg_z_13.png", "majiang_pai_sj_cpg_z_14.png", "majiang_pai_sj_cpg_z_15.png",
"majiang_pai_sj_cpg_z_08.png", "majiang_pai_sj_cpg_z_09.png", "majiang_pai_sj_cpg_z_10.png", "majiang_pai_sj_cpg_z_11.png",
"majiang_pai_sj_cpg_z_04.png", "majiang_pai_sj_cpg_z_05.png", "majiang_pai_sj_cpg_z_06.png", "majiang_pai_sj_cpg_z_07.png",
"majiang_pai_sj_cpg_z_00.png", "majiang_pai_sj_cpg_z_01.png", "majiang_pai_sj_cpg_z_02.png", "majiang_pai_sj_cpg_z_03.png"},
{ "majiang_pai_dj_dp_09.png", "majiang_pai_dj_dp_09.png", "majiang_pai_dj_dp_09.png", "majiang_pai_dj_dp_09.png" ,
"majiang_pai_dj_dp_09.png", "majiang_pai_dj_dp_09.png", "majiang_pai_dj_dp_09.png", "majiang_pai_dj_dp_09.png", 
"majiang_pai_dj_dp_09.png", "majiang_pai_dj_dp_09.png", "majiang_pai_dj_dp_09.png", "majiang_pai_dj_dp_09.png", 
"majiang_pai_dj_dp_09.png", "majiang_pai_dj_dp_09.png", "majiang_pai_dj_dp_09.png", "majiang_pai_dj_dp_09.png"},
{"majiang_pai_xj_cpg_z_02.png","majiang_pai_xj_cpg_z_02.png","majiang_pai_xj_cpg_z_01.png","majiang_pai_xj_cpg_z_00.png",
 "majiang_pai_xj_cpg_z_06.png", "majiang_pai_xj_cpg_z_06.png" , "majiang_pai_xj_cpg_z_06.png", "majiang_pai_xj_cpg_z_07.png", 
 "majiang_pai_xj_cpg_z_10.png", "majiang_pai_xj_cpg_z_10.png" , "majiang_pai_xj_cpg_z_09.png", "majiang_pai_xj_cpg_z_08.png", 
 "majiang_pai_xj_cpg_z_14.png", "majiang_pai_xj_cpg_z_14.png" , "majiang_pai_xj_cpg_z_13.png", "majiang_pai_xj_cpg_z_12.png", }
};

MJCPH::MJCPH(){
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			m_cardimgs[i][j] = NULL;
			m_cardbgs[i][j] = NULL;
			m_cards[i][j] = 0;
		}
	}
}

MJCPH::~MJCPH(){
	RootRegister::getIns()->resetWidget(m_RootLayer);
	
}

bool MJCPH::init(int pos)
{             
	if (!Layer::init())
    {
        return false;
    }
	m_position = pos;
	m_index = GameHead::changePos(pos);
	char buff[50];
	sprintf(buff, "mjcpg%d.json", pos);
	m_json = buff;
	m_RootLayer =RootRegister::getIns()->getWidget(buff);
	this->addChild(m_RootLayer);

	for (int i = 0; i < 16; i++){
		int index = i / 4;
		int zindex = i % 4;
		sprintf(buff,"c%d",i+1);
		ImageView *img = (ImageView *)GameDataSet::getLayout(m_RootLayer,buff);
		m_cardbgs[index][zindex] = img;
		m_cardimgs[index][zindex] = (ImageView *)img->getChildren().at(0);
	}
	resetCards();
// 	char a[4] = { 0, 0, 0, 0 };
// 	for (int i = 0; i < 4; i++){
// 		CPGCardData cpg;
// 		cpg.set_type(i + 1);
// 		int index = rand()%34;
// 		for (int j = 0; j < 4; j++){
// 			a[j] = CardStr::g_cards[index];
// 			log("%d", a[j]);
// 		}
// 		
// 		cpg.set_cards(a, 4);
// 		setValue(i,cpg);
// 	}
    return true;
}

MJCPH* MJCPH::create(int pos){
	MJCPH *p = new MJCPH();
	if (p&&p->init(pos)){
		p->autorelease();
	}
	else{
		CC_SAFE_DELETE(p);
	}
	return p;
}

void MJCPH::TouchEvent(CCObject *obj, TouchEventType type){
	Button *btn = (Button *)obj;
	string name = btn->getName();
	if (type == TOUCH_EVENT_ENDED){
		
	}
}

void MJCPH::resetCards(){
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			m_cardbgs[i][j]->loadTexture(g_paistr[m_index][i*4+j], Widget::TextureResType::PLIST);
			m_cardbgs[i][j]->setVisible(false);
			m_cardimgs[i][j]->setVisible(true);
		}
	}
}
//1吃 2碰 3明杠 4暗杠 5明杠（宝娘） 6暗杠（宝娘）
void MJCPH::setValue(int index, CPGCardData data){
	int type = data.type();
	int cards[4] = { 0 };
	string cd = data.cards();
	for (int i = 0; i < cd.length();i++){
		int va = cd[i];
		if (type == 4 || type == 6){
			setValue(index, i, va, i<3?true:false, true);
		}
		else{
			setValue(index, i, va, false, true);
		}
		
	}
}

void MJCPH::setValue(int index, int zindex, int card, bool bei, bool isv){
	string beistr;
	if (bei){
		beistr = g_beistr[m_index][index*4+zindex];
	}
	m_cardbgs[index][zindex]->setVisible(isv);
	if (!bei&&isv){
		beistr = CardStr::getCardStr(card);
		m_cardimgs[index][zindex]->loadTexture(beistr, Widget::TextureResType::PLIST);
	}
	else if (bei&&isv){
		m_cardbgs[index][zindex]->loadTexture(beistr, Widget::TextureResType::PLIST);
		m_cardimgs[index][zindex]->setVisible(false);
	}
	
}