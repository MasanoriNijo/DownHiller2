#include "FstScene.h"
#include "TitleScene.h"

#include "SimpleAudioEngine.h"


USING_NS_CC;


Scene* FstScene::createScene() {

	 auto scene = Scene::create();

	 auto layer = FstScene::create();

	 scene->addChild(layer);

	 // return the scene
	 return scene;

}
FstScene::FstScene() :
		_productTitle(NULL),_ad(NULL) {

}

FstScene::~FstScene() {
	CC_SAFE_RELEASE_NULL(_productTitle);
	CC_SAFE_RELEASE_NULL(_ad);
}

// on "init" you need to initialize your instance
bool FstScene::init() {

	if (!Layer::init()) {
		return false;
	}
	this->scheduleUpdate();
	auto director = Director::getInstance();
	auto oto = CocosDenshion::SimpleAudioEngine::getInstance();
	auto winSize = director->getWinSize();
	this->setProductTitle(Sprite::create("kotokotobokanmark.png")); //��Ŗ߂��Bdebugwaku.png back.png
	_productTitle->setPosition(Vec2(winSize.width / 2.0, winSize.height / 2));
	_productTitle->setOpacity(0);
	auto fadein_ = FadeIn::create(1.0f);
	auto delaytime_ = DelayTime::create(1.0f);
	auto fadeout_ = FadeOut::create(1.0f);
	auto start_ = CallFuncN::create([this](Node* node_) {
		auto scene=TitleScene::createScene();
		auto transition=TransitionCrossFade::create(0.5,scene);
		Director::getInstance()->replaceScene(transition);
	});

	this->_productTitle->runAction(Sequence::create(fadein_,delaytime_,fadeout_,start_,NULL));

	this->setAD(ImovileAd::create());
	//広告をする場合、コメントアウトを外す。
	_ad->FstSet();
	_ad->instFlg=true;
	return true;
}

void FstScene::update(float dt) {

}

void FstScene::onEnterTransitionDidFinish() {

	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(
			"open.mp3", false);
	this->addChild(this->getProductTitle());

}

