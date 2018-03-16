#include "GameControl.h"




GameControl *GameControl::m_ins=NULL;

GameControl::GameControl(){
	m_pLoginLayer = NULL;
	m_pMainLayer = NULL;
}

GameControl::~GameControl(){
	
}

bool GameControl::init()
{
	
    return true;
}

GameControl* GameControl::getIns(){
	if (!m_ins){
		m_ins = new GameControl();
		m_ins->init();
	}
	return m_ins;
}