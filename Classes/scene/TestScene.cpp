#include "TestScene.h"
#include "scene/base/GameScene.h"
#include "cocos2d.h"
USING_NS_CC;
#include "audio/include/AudioEngine.h"

Scene* TestScene::createScene() {
	auto scene = Scene::create();
	auto layer = TestScene::create();
    scene->addChild(layer);
	// return the scene
	return scene;
}

TestScene::TestScene():_productTitle(NULL){}

TestScene::~TestScene() {
	CC_SAFE_RELEASE_NULL(_productTitle);
}

// on "init" you need to initialize your instance
bool TestScene::init() {

	if (!Layer::init()) {
		return false;
	}
	this->scheduleUpdate();
	auto director = Director::getInstance();
	auto winSize = director->getWinSize();

	auto udf = UserDefault::getInstance();

	int hh = 95;


	this->GetPrm(this->index);

	this->SetTouchListenner();
    this->getAD()->AdShow(true, true, true, true, true, true);
	return true;
}

void TestScene::SetPrm() {


}
void TestScene::SetPrm(int index_) {


}

void TestScene::GetPrm(int index_) {

	auto udf = UserDefault::getInstance();

}

void TestScene::SetTouchListenner() {



}

void TestScene::update(float dt) {

//	if (_slider->Value_ == 0 && _slider2->Value_ == 0
//			&& _slider3->Value_ == 0) {
//		this->addChild(_productTitle, 3);
//	}

}

void TestScene::onEnterTransitionDidFinish() {
    AudioEngine::play2d("btnon.mp3", false, 0.2, nullptr);//ループON、音量：0.5
}

