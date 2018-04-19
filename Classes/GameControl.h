#ifndef __GameControl_SCENE_H__
#define __GameControl_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "LoginLayer.h"
#include "MainLayer.h"
#include "UserInfoLayer.h"
#include "SetLayer.h"
#include "ShopLayer.h"
#include "SignLayer.h"
#include "FriendLayer.h"
#include "FankuiLayer.h"
#include "FreeLayer.h"
#include "ExchangeLayer.h"
#include "TaskLayer.h"
#include "MailLayer.h"
#include "ActiveLayer.h"
#include "FirstChargeLayer.h"
#include "AboutLayer.h"
#include "HelpLayer.h"
#include "ChatLayer.h"
#include "MailTipLayer.h"
#include "RewardTipLayer.h"
#include "RootRegister.h"
#include "LoadingLayer.h"
#include "LoadLayer.h"
#include "CreateRoomLayer.h"
#include "JoinRoomLayer.h"
#include "MJGameLayer.h"
#include "GameUI.h"
#include "MJGameScene.h"
#include "TipLayer.h"

using namespace cocos2d;
using namespace ui;
using namespace std;

struct LaBaItem
{
	string _content;
	int _times;
};

class GameControl : public CCObject
{
public:
	GameControl();
	~GameControl();
    virtual bool init();
    CREATE_FUNC(GameControl);
	static GameControl* getIns();
	
public:
	void setLoginLayer(LoginLayer *p){
		m_pLoginLayer = p;
	}
	LoginLayer *getLoginLayer(){
		return m_pLoginLayer;
	}

	void setMainLayer(MainLayer *p){
		m_pMainLayer = p;
	}
	MainLayer *getMainLayer(){
		return m_pMainLayer;
	}

	void setUserInfoLayer(UserInfoLayer *p){
		m_pUserInfoLayer = p;
	}
	UserInfoLayer *getUserInfoLayer(){
		return m_pUserInfoLayer;
	}

	void setSetLayer(SetLayer *p){
		m_pSetLayer = p;
	}
	SetLayer *getSetLayer(){
		return m_pSetLayer;
	}

	void setShopLayer(ShopLayer *p){
		m_pShopLayer = p;
	}
	ShopLayer *getShopLayer(){
		return m_pShopLayer;
	}

	void setSignLayer(SignLayer *p){
		m_pSignLayer = p;
	}
	SignLayer *getSignLayer(){
		return m_pSignLayer;
	}

	void setFriendLayer(FriendLayer *p){
		m_pFriendLayer = p;
	}
	FriendLayer *getFriendLayer(){
		return m_pFriendLayer;
	}

	void setFankuiLayer(FankuiLayer *p){
		m_pFankuiLayer = p;
	}
	FankuiLayer *getFankuiLayer(){
		return m_pFankuiLayer;
	}

	void setFreeLayer(FreeLayer *p){
		m_pFreeLayer = p;
	}
	FreeLayer *getFreeLayer(){
		return m_pFreeLayer;
	}

	void setExchangeLayer(ExchangeLayer *p){
		m_pExchangeLayer = p;
	}
	ExchangeLayer *getExchangeLayer(){
		return m_pExchangeLayer;
	}

	void setTaskLayer(TaskLayer *p){
		m_pTaskLayer = p;
	}
	TaskLayer *getTaskLayer(){
		return m_pTaskLayer;
	}

	void setMailLayer(MailLayer *p){
		m_pMailLayer = p;
	}
	MailLayer *getMailLayer(){
		return m_pMailLayer;
	}

	void setActiveLayer(ActiveLayer *p){
		m_pActiveLayer = p;
	}
	ActiveLayer *getActiveLayer(){
		return m_pActiveLayer;
	}

	void setFirstChargeLayer(FirstChargeLayer *p){
		m_pFirstChargeLayer = p;
	}
	FirstChargeLayer *getFirstChargeLayer(){
		return m_pFirstChargeLayer;
	}

	void setAboutLayer(AboutLayer *p){
		m_pAboutLayer = p;
	}
	AboutLayer *getAboutLayer(){
		return m_pAboutLayer;
	}

	void setHelpLayer(HelpLayer *p){
		m_pHelpLayer = p;
	}
	HelpLayer *getHelpLayer(){
		return m_pHelpLayer;
	}

	void setChatLayer(ChatLayer *p){
		m_pChatLayer = p;
	}
	ChatLayer *getChatLayer(){
		return m_pChatLayer;
	}

	void setMailTipLayer(MailTipLayer *p){
		m_pMailTipLayer = p;
	}
	MailTipLayer *getMailTipLayer(){
		return m_pMailTipLayer;
	}

	void setRewardTipLayer(RewardTipLayer *p){
		m_pRewardTipLayer = p;
	}
	RewardTipLayer *getRewardTipLayer(){
		return m_pRewardTipLayer;
	}

	void setLoadingLayer(LoadingLayer *p){
		m_pLoadingLayer = p;
	}
	LoadingLayer *getLoadingLayer(){
		return m_pLoadingLayer;
	}

	void setCreateRoomLayer(CreateRoomLayer *p){
		m_pCreateRoomLayer = p;
	}
	CreateRoomLayer *getCreateRoomLayer(){
		return m_pCreateRoomLayer;
	}

	void setJoinRoomLayer(JoinRoomLayer *p){
		m_pJoinRoomLayer = p;
	}
	JoinRoomLayer *getJoinRoomLayer(){
		return m_pJoinRoomLayer;
	}

	void setMJGameLayer(MJGameLayer *p){
		m_pMJGameLayer = p;
	}
	MJGameLayer *getMJGameLayer(){
		return m_pMJGameLayer;
	}

	void setGameUI(GameUI *p){
		m_pGameUI = p;
	}
	GameUI *getGameUI(){
		return m_pGameUI;
	}

	void setMJGameScene(MJGameScene *p){
		m_pMJGameScene = p;
	}
	MJGameScene *getMJGameScene(){
		return m_pMJGameScene;
	}

	void setTipLayer(TipLayer *p){
		m_pTipLayer = p;
	}
	TipLayer *getTipLayer(){
		return m_pTipLayer;
	}

	void ShowLoading();
	void HideLoading();
	void ShowLoading(BaseLayer *layer,Layout *ly);
	void HideLoading(BaseLayer *layer);
	void HideLoading(BaseLayer *layer,Layout *ly);

	void replaceScene(Scene *scene);

	void PushLaBa(string content,int times);
	void update(float dt);

private:
	static GameControl *m_ins;
	LoginLayer *m_pLoginLayer;
	MainLayer *m_pMainLayer;
	UserInfoLayer *m_pUserInfoLayer;
	SetLayer *m_pSetLayer;
	ShopLayer *m_pShopLayer;
	SignLayer *m_pSignLayer;
	FriendLayer *m_pFriendLayer;
	FankuiLayer *m_pFankuiLayer;
	FreeLayer *m_pFreeLayer;
	ExchangeLayer *m_pExchangeLayer;
	TaskLayer *m_pTaskLayer;
	MailLayer *m_pMailLayer;
	ActiveLayer *m_pActiveLayer;
	FirstChargeLayer *m_pFirstChargeLayer;
	AboutLayer *m_pAboutLayer;
	HelpLayer *m_pHelpLayer;
	ChatLayer *m_pChatLayer;
	MailTipLayer *m_pMailTipLayer;
	RewardTipLayer *m_pRewardTipLayer;
	LoadingLayer *m_pLoadingLayer;
	CreateRoomLayer *m_pCreateRoomLayer;
	JoinRoomLayer *m_pJoinRoomLayer;
	MJGameLayer *m_pMJGameLayer;
	GameUI *m_pGameUI;
	MJGameScene *m_pMJGameScene;
	TipLayer *m_pTipLayer;
	vector<LaBaItem *> m_contents;
	map<BaseLayer *, map<Layout *,LoadLayer *>>m_pLoadings;
};

#endif // __GameControl_SCENE_H__
