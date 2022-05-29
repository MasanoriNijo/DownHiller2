#include "FstScene.h"
#include "scene/TestScene.h"
#include "audio/include/AudioEngine.h"

USING_NS_CC;
using namespace cocos2d;

Scene* FstScene::createScene() {

	 auto scene = Scene::create();

	 auto layer = FstScene::create();

	 scene->addChild(layer);

	 // return the scene
	 return scene;

}
FstScene::FstScene() :
		_productTitle(NULL) {
}

FstScene::~FstScene() {
	CC_SAFE_RELEASE_NULL(_productTitle);
}

// on "init" you need to initialize your instance
bool FstScene::init() {

	if (!Scene::init()) {
		return false;
	}
	this->scheduleUpdate();
	auto director = Director::getInstance();
	auto winSize = director->getWinSize();
//	this->setProductTitle(Sprite::create("HelloWorld.png"));
    this->setProductTitle(Sprite::create("Kotokotobokanmark.png"));
	this->getProductTitle()->setPosition(Vec2(winSize.width / 2.0, winSize.height / 2));
    this->getProductTitle()->setOpacity(0);
	auto fadein_ = FadeIn::create(1.0f);
	auto delaytime_ = DelayTime::create(1.0f);
	auto fadeout_ = FadeOut::create(1.0f);
	auto start_ = CallFuncN::create([this](Node* node_) {
		auto scene=TestScene::createScene();
		auto transition=TransitionCrossFade::create(0.5,scene);
		Director::getInstance()->replaceScene(transition);
	});

	this->_productTitle->runAction(Sequence::create(fadein_,delaytime_,fadeout_,start_,NULL));

	return true;
}

void FstScene::update(float dt) {

}

void FstScene::onEnterTransitionDidFinish() {
    AudioEngine::play2d("open.mp3", false, 0.5, nullptr);//ループON、音量：0.5
//    AudioEngine::stop(sound_id);
	this->addChild(this->getProductTitle());
}

