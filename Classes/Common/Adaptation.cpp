#include "Adaptation.h"
#include "SimpleAudioEngine.h"
#include "AppMacros.h"

Adaptation* Adaptation::m_pShareAdaptation=NULL;

Adaptation::Adaptation()
{
	m_scaleFactor = 1.0;
	m_designResolutionSize = designResolutionSize;
	m_screensize = SCREEN_SIZE;

}

Adaptation::~Adaptation(){
	
}

Adaptation* Adaptation::shareAdaptation(){
	if (!m_pShareAdaptation){
		m_pShareAdaptation = new Adaptation();
		m_pShareAdaptation->init();
	}
	return m_pShareAdaptation;
}

void Adaptation::removeAdaptation(){
	if (m_pShareAdaptation){
		delete m_pShareAdaptation;
		m_pShareAdaptation = NULL;
	}
}

bool Adaptation::init()
{
	ScreenAdaptationInit();
	float sx = RESOURCE_SCALEX;
	float sy = RESOURCE_SCALEY;
	m_scaleFactor = RESOURCE_SCALEX<RESOURCE_SCALEY?RESOURCE_SCALEX:RESOURCE_SCALEY;
	m_designResolutionSize = designResolutionSize;
	m_screensize = SCREEN_SIZE;

	m_AddSize = m_designResolutionSize - m_screensize;

	return true;
}

void Adaptation::ScreenAdaptationInit(){
	
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if (!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
		glview = GLViewImpl::createWithRect(XXIconv::GBK2UTF("ÓÀÀÖÂé½«"), Rect(0, 0, 1280*0.6, 720*0.6));
		//glview = GLViewImpl::createWithRect("gzmj", Rect(0, 0, 1136, 852));
#else
		glview = GLViewImpl::create(XXIconv::GBK2UTF("ÓÀÀÖÂé½«"));
#endif
		director->setOpenGLView(glview);
	}

	// turn on display FPS
	director->setDisplayStats(false);

	// set FPS. the default value is 1.0/60 if you don't call this
	director->setAnimationInterval(1.0 / 60);

	// Set the design resolution
	glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::EXACT_FIT);
	Size frameSize = glview->getFrameSize();
	// if the frame's height is larger than the height of medium size.
// #if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
// 	glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionShowAll);
// #else
// 	//pEGLView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionShowAll);
// 	glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionFixedHeight);
// #end

}