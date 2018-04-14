#include "PhotoDown.h"



PhotoDown *PhotoDown::m_ins=NULL;

PhotoDown::PhotoDown(){
	m_lock = false;
	Director::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(PhotoDown::update), this, 0.2, false);
}

PhotoDown::~PhotoDown(){
	Director::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(PhotoDown::update),this);
	eraseAll();
}

bool PhotoDown::init()
{
	
    return true;
}

PhotoDown* PhotoDown::getIns(){
	if (!m_ins){
		m_ins = new PhotoDown();
		m_ins->init();
	}
	return m_ins;
}

void PhotoDown::update(float dt){
	if (!m_lock){
		auto itr = m_pPhotos.begin();
		for (itr; itr != m_pPhotos.end(); itr++){
			vector<PhotoItem *>pvec = itr->second;
			auto itr1 = pvec.begin();
			bool ist = false;
			for (itr1; itr1 != pvec.end(); itr1++){
				PhotoItem *p = *itr1;
				if (p&&!p->_islock){
					p->_islock = true;
					m_lock = true;
					DownPic(p);
					ist = true;
					break;
				}
				else{
					break;
				}
			}
			break;
		}
	}
}

void PhotoDown::PushPhoto(BaseLayer *target, string uid, ImageView *img, string picurl, int picid){
	PhotoItem *p = new PhotoItem();
	p->_img = img;
	p->_picid = picid;
	p->_picurl = picurl;
	p->_uid = uid;
	p->_islock = false;
	if (m_pPhotos.find(target) == m_pPhotos.end()){
		vector<PhotoItem*> ps;
		ps.push_back(p);
		m_pPhotos.insert(make_pair(target,ps));
	}
	else{
		vector<PhotoItem*> ps=m_pPhotos.at(target);
		ps.push_back(p);
		m_pPhotos.at(target) = ps;
	}
}

void PhotoDown::erasePhoto(PhotoItem *p){
	auto itr = m_pPhotos.begin();
	for (itr; itr != m_pPhotos.end();){
		vector<PhotoItem *>pvec = itr->second;
		auto itr1 = pvec.begin();
		for (itr1; itr1 != pvec.end();){
			PhotoItem *p1 = *itr1;
			if (p1==p){
				delete p1;
				itr1 = pvec.erase(itr1);
				itr->second = pvec;
				break;
			}
			else{
				itr1++;
			}
		}
		if (pvec.empty()){
			itr = m_pPhotos.erase(itr);
			break;
		}
		else{
			itr++;
		}
	}
}

bool PhotoDown::saveFile(unsigned char *pContent, string pFileName, int length){
	log("save file path = %s", pFileName.c_str());
	FILE* file = fopen(pFileName.c_str(), "wb");
	if (file) {
		fwrite(pContent, sizeof(unsigned char), length, file);
		fclose(file);
		return true;
	}
	else
	{
		log("save file error.");
	}
	return false;
}

void PhotoDown::LoadPic(PhotoItem *p){
	string path = CCFileUtils::sharedFileUtils()->getWritablePath() + p->_uid + ".png";
	auto itr = m_pPhotos.begin();
	for (itr; itr != m_pPhotos.end();){
		vector<PhotoItem *>pvec = itr->second;
		auto itr1 = pvec.begin();
		bool ist = false;
		for (itr1; itr1 != pvec.end();){
			PhotoItem *p1 = *itr1;
			if (p==p1){
				ImageView *img = p->_img;
				img->loadTexture(path);
				itr1 = pvec.erase(itr1);
				itr->second = pvec;
				delete p1;
				m_lock = false;
				ist = true;
				break;
			}
			else{
				itr1++;
			}
		}
		if (pvec.empty()){
			itr = m_pPhotos.erase(itr);
		}
		else{
			itr++;
		}
		if (ist){
			break;
		}
	}
}

void PhotoDown::DownPicCallBack(HttpClient* client, HttpResponse* response){
	vector<char > *v = response->getResponseData();
	char *temp=new char[v->size()];
	std::copy(v->begin(), v->end(), temp);
	int sz = v->size();
	string tag = response->getHttpRequest()->getTag();
	string path = CCFileUtils::sharedFileUtils()->getWritablePath() + tag + ".png";
	PhotoDown *p = PhotoDown::getIns();
	bool ist = p->saveFile((unsigned char*)temp, path, sz);
	if (ist){
		PhotoItem *pi = (PhotoItem *)response->getHttpRequest()->getUserData();
		if (pi){
			p->LoadPic(pi);
		}
	}
}

void PhotoDown::DownPic(PhotoItem *p){
	string uid = p->_uid;
	int picid = p->_picid;
	string picurl = p->_picurl;
	if (picurl.empty()){
		ImageView *img = p->_img;
		if (img){
			p->_islock = true;
			m_lock = false;
			char buff[300];
			sprintf(buff,"head%d0.png",picid);
			img->loadTexture(buff);
			erasePhoto(p);
		}
	}
	else{
		string path = CCFileUtils::sharedFileUtils()->getWritablePath() + uid + ".png";
		bool ishave = FileUtils::sharedFileUtils()->isFileExist(path);
		if (!ishave){
			p->_islock = true;
			XXHttpRequest::getIns()->getServerDataFromUrl(picurl, httpresponse_selector(PhotoDown::DownPicCallBack), uid,p);
		}
		else{
			p->_islock = true;
			LoadPic(p);
		}
	}
}

void PhotoDown::erasePhoto(BaseLayer *target){
	auto itr = m_pPhotos.begin();
	for (itr; itr != m_pPhotos.end();){
		if (itr->first == target){
			vector<PhotoItem *>pvec = itr->second;
			auto itr1 = pvec.begin();
			for (itr1; itr1 != pvec.end();){
				PhotoItem *p = *itr1;
				if (p){
					delete p;
				}
				itr1 = pvec.erase(itr1);
			}
			itr = m_pPhotos.erase(itr);
			break;
		}
	}
}

void PhotoDown::eraseAll(){
	auto itr = m_pPhotos.begin();
	for (itr; itr != m_pPhotos.end();){
		vector<PhotoItem *>pvec = itr->second;
		auto itr1 = pvec.begin();
		for (itr1; itr1 != pvec.end();){
			PhotoItem *p = *itr1;
			if (p){
				delete p;
			}
			itr1 = pvec.erase(itr1);
		}
		itr = m_pPhotos.erase(itr);
	}
}