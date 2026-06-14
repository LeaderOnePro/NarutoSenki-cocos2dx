#include "AppDelegate.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;



AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}


bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
	
    pDirector->setOpenGLView(pEGLView);
	pEGLView->setDesignResolutionSize(480,320,kResolutionFixedHeight);
	pEGLView->setFrameZoomFactor(2.0f); // enlarge win32 window to 960x640 (2x); game logic stays at 480x320 design res

    // turn on display FPS
    pDirector->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // unlock HardCore mode by default (original needed manual unlock; ad/unlock flow is dead)
    CCUserDefault::sharedUserDefault()->setBoolForKey("isHardCore", true);
    CCUserDefault::sharedUserDefault()->flush();

    // create a scene. it's an autorelease object
    CCScene *pScene = GameScene::create();

    // run
    pDirector->runWithScene(pScene);

    return true;
}


// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
    void AppDelegate::applicationDidEnterBackground() {


		

    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();

	

}

// this function will be called when the app is active again
    void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();

}
