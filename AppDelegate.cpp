#include "AppDelegate.h"
//#include "HelloWorldScene.h"
#include "FstScene.h"
//#include "TitleScene.h"
#include "IMobileCocos2dxModule.h"
#include "SimpleAudioEngine.h"



USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() {
}

bool AppDelegate::applicationDidFinishLaunching() {
	// initialize director
	// initialize director
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if (!glview) {
		glview = GLView::create("My Game");
		director->setOpenGLView(glview);
	}
	glview->setDesignResolutionSize(720, 1280, ResolutionPolicy::SHOW_ALL);

	FileUtils::getInstance()->addSearchPath("images");
	FileUtils::getInstance()->addSearchPath("gcharactors");
	FileUtils::getInstance()->addSearchPath("sounds");
	FileUtils::getInstance()->addSearchPath("fonts");

	// turn on display FPS
//	director->setDisplayStats(true);

	// set FPS. the default value is 1.0/60 if you don't call this
	director->setAnimationInterval(1.0 / 60);

	//������h�~:false�ɂ���B
	CCDirector::sharedDirector()->setDepthTest(false);

	//�X�v���C�g�L���b�V���𐶐��B
	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("cources.plist");

	// create a scene. it's an autorelease object
	//auto scene = HelloWorld::createScene();
	auto scene = FstScene::createScene();
	//auto scene = TitleScene::createScene();
	// run
	director->runWithScene(scene);


	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
	Director::getInstance()->stopAnimation();

	// if you use SimpleAudioEngine, it must be pause
	// SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
	Director::getInstance()->startAnimation();

	// if you use SimpleAudioEngine, it must resume here
	// SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
