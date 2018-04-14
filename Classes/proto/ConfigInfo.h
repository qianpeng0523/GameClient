
#ifndef __ConfigInfo__
#define __ConfigInfo__

#include "AppMacros.h"
#include "ccEvent.h"

class ConfigInfo:public Object
{
public:
	ConfigInfo();
	~ConfigInfo();
	static ConfigInfo* getIns();
	bool init();
public:
	void SendCConfig();
	void HandlerSConfig(ccEvent *event);

	void HandlerSPushCurrency(ccEvent *event);
private:
	static ConfigInfo *m_shareConfigInfo;
	SConfig m_pSConfig;
	SPushCurrency m_pSPushCurrency;
};

#endif 
