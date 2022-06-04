#include "GameScene.h"

GameScene::GameScene():
_backColor(NULL), _ad(NULL), _colorChanger(NULL), _calc(NULL)
{}

GameScene::~GameScene() {
    CC_SAFE_RELEASE_NULL(_backColor);
    CC_SAFE_RELEASE_NULL(_ad);
    CC_SAFE_RELEASE_NULL(_colorChanger);
    CC_SAFE_RELEASE_NULL(_calc);
}

Scene* GameScene::createScene() {
    auto scene = Scene::create();
    auto layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}

bool GameScene::init() {
    
    if (!Layer::init()) {
        return false;
    }
    
    //画面のサイズをセットする
    auto director = Director::getInstance();
    this->winSize = director->getWinSize();
    this->ctPt.set(winSize.width / 2, winSize.height / 2);
    
    //imovileAdをセットする。
    this->setAD(ImovileAd::create());
    this->getAD()->txtFlg = true;
    this->getAD()->instFlg = true;
    
    // Calclaterをセット
    this->setCalc(Calclater::create());
    
    return true;
}

void GameScene::setBackGroundColor(){
    this->setBackGroundColor(DEFAULT_COLOR_H,DEFAULT_COLOR_S,DEFAULT_COLOR_V);
}

void GameScene::setBackGroundColor(float h, float s, float v){
    this->setColorChanger(ColorChanger::create());
    this->getColorChanger()->SetColor(h, s, v);
    this->setBackColor(LayerColor::create(this->getColorChanger()->getColor4B()));
    this->_backColor->setGlobalZOrder(OBJ_LAYER_BUTTOM);
    this->addChild(this->_backColor);
}

void GameScene::onEnterTransitionDidFinish() {
    // todo
}

void GameScene::update(float dt) {
    switch (this->getGameState()) {
        case GameState::READY: {
            // todo
            break;
        }
        case GameState::PLAY: {
            // todo
            break;
        }
        case GameState::CLEAR: {
            // todo
            break;
        }
        case GameState::MISS: {
            // todo
            break;
        }
    }
}

void GameScene::transitonScene(Scene* scene){
    auto transition_ = CallFuncN::create([scene](Node* node_) {
        auto transition=TransitionCrossFade::create(0.5,scene);
        Director::getInstance()->replaceScene(transition);
    });
    this->runAction(transition_);
}

void GameScene::setSprite(Node* sp, Vec2 pt, float lvl){
    sp->setPosition(pt);
    sp->setGlobalZOrder(lvl);
    this->addChild(sp);
}

/** パラメータサンプル
 this->setBackColor(LayerColor::create());
 this->getBackColor();
 this->setAD(ImovileAd::create());
 this->getAD();
 this->setColorChanger(ColorChanger::create());
 this->getColorChanger();
 */
