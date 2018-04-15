#ifndef __PhotoDown_SCENE_H__
#define __PhotoDown_SCENE_H__

#include "AppMacros.h"
#include "ui/UIImageView.h"
#include "BaseLayer.h"
#include "XXHttpRequest.h"

using namespace cocos2d;
using namespace ui;
using namespace std;

struct PhotoItem
{
	string _uid;
	ImageView *_img;
	string _picurl;
	int _picid;
	bool _islock;
};

class PhotoDown : public CCObject
{
public:
	PhotoDown();
	~PhotoDown();
    virtual bool init();
    CREATE_FUNC(PhotoDown);
	static PhotoDown* getIns();
	
	void PushPhoto(BaseLayer *target,string uid,ImageView *img,string picurl,int picid);
	void erasePhoto(BaseLayer *target);

	void DownPic(PhotoItem *p);
	void DownPicCallBack(HttpClient* client, HttpResponse* response);
public:
	bool saveFile(unsigned char *pContent, string pFileName, int length);
	void update(float dt);
	void LoadPic(PhotoItem *p);
	void eraseAll();
	void erasePhoto(PhotoItem *p);
private:
	static PhotoDown *m_ins;
	map<BaseLayer*, vector<PhotoItem*>>m_pPhotos;
	bool m_lock;
};

#endif // __PhotoDown_SCENE_H__
