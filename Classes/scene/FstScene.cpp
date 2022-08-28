#include "FstScene.h"
#include "scene/TitleScene.h"

FstScene::FstScene():_productTitle(NULL){}

FstScene::~FstScene() {
    CC_SAFE_RELEASE_NULL(_productTitle);
}

Scene* FstScene::createScene() {
    auto scene = Scene::create();
    auto layer = FstScene::create();
    scene->addChild(layer);
    NJLOG("FstScene:Count1");
    NJLOG(ST_INT(scene->getReferenceCount()).c_str());
    return scene;
}

bool FstScene::init() {
    if (!GameScene::init()) {
        return false;
    }
    setSoundEffect("btnon.mp3");
    this->setProductTitle(Sprite::create("kotokotobokanmark.png"));
    this->getProductTitle()->setOpacity(0);
    auto fadein_ = FadeIn::create(1.0f);
    auto delaytime_ = DelayTime::create(1.0f);
    auto fadeout_ = FadeOut::create(1.0f);
    auto start_ = CallFuncN::create([this](Node* node_) {
//        auto transition=TransitionCrossFade::create(0.5,TitleScene::createScene());
//        auto transition=TransitionFade::create(0.5,TitleScene::createScene());
//        Director::getInstance()->replaceScene(transition);
        this->transitonScene(TitleScene::createScene());
    });

    this->_productTitle->runAction(Sequence::create(fadein_,delaytime_,fadeout_,start_,NULL));
// for android
//    this->setAD(ImovileAd::create());
//    this->getAD()->FstSet();
    NJLOG("hogehoge");
    
    return true;
}

void FstScene::onEnterTransitionDidFinish() {
//    callSoundEffect("ME017-100125-logo02-wav.mp3",0.01f);
    callSoundEffect(SOUND_OPENING,1.0f);
    GameScene::onEnterTransitionDidFinish();
    this->mountNode(this->getProductTitle(),this->ctPt,OBJ_LAYER_TOP);
//    NJLOG("FstScene:Count2");
//    NJLOG(ST_INT(this->getReferenceCount()).c_str());
}

void FstScene::update(float dt) {
    // todo
}

/** パラメータサンプル
 this->setProductTitle(Sprite::create());
 this->getProductTitle();
 */
