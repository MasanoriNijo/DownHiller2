#include "FstScene.h"
#include "scene/TitleScene.h"

FstScene::FstScene():_productTitle(NULL),_ad(NULL){}

FstScene::~FstScene() {
    CC_SAFE_RELEASE_NULL(_productTitle);
    CC_SAFE_RELEASE_NULL(_ad);
}

Scene* FstScene::createScene() {
    return FstScene::create();
}

bool FstScene::init() {
    if (!Scene::init()) {
        return false;
    }
    this->scheduleUpdate();
    auto director = Director::getInstance();
    auto winSize = director->getWinSize();

    this->setProductTitle(Sprite::create("kotokotobokanmark.png"));
    this->getProductTitle()->setPosition(Vec2(winSize.width / 2.0, winSize.height / 2));
    this->getProductTitle()->setOpacity(0);
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
    this->getAD()->FstSet();
    NJLOG("hogehoge");
    
    return true;
}

void FstScene::onEnterTransitionDidFinish() {
    this->addChild(this->getProductTitle());
}

void FstScene::update(float dt) {
    // todo
}

/** パラメータサンプル
 this->setProductTitle(Sprite::create());
 this->getProductTitle();
 */
