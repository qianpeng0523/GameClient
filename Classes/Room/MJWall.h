#ifndef __MJWall_SCENE_H__
#define __MJWall_SCENE_H__

#include "AppMacros.h"
#include "BaseLayer.h"
using namespace cocos2d;
using namespace ui;
using namespace std;

#define MAXWALLCOUNT 30


class MJWall : public BaseLayer
{
public:
	MJWall();
	~MJWall();
	static MJWall* create(int pos);
	virtual bool init(int pos);
	
	void resetCard();
	void initCard();
	void PopCard(int index);
	int getIndex(){
		return m_index;
	}
private:
	int m_position;
	int m_index;
	ImageView *m_imgwall[MAXWALLCOUNT];
private:
	
};

#endif 