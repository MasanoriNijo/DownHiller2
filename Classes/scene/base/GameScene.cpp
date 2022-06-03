#include "GameScene.h"

GameScene::GameScene():
_backColor(NULL), _ad(NULL), _colorChanger(NULL)
{}

GameScene::~GameScene() {
    CC_SAFE_RELEASE_NULL(_backColor);
    CC_SAFE_RELEASE_NULL(_ad);
    CC_SAFE_RELEASE_NULL(_colorChanger);
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

  return true;
}


void GameScene::setBackGroundColor(){
    this->setBackGroundColor(DEFAULT_COLOR_H,DEFAULT_COLOR_S,DEFAULT_COLOR_V);
}

void GameScene::setBackGroundColor(float h, float s, float v){
    this->setColorChanger(ColorChanger::create());
    this->getColorChanger()->SetColor(h, s, v);
    this->setBackColor(
            LayerColor::create(
                    Color4B(this->getColorChanger()->getR(),
                            this->getColorChanger()->getG(),
                            this->getColorChanger()->getB(),
                            255)));
    this->addChild(this->_backColor);
}

void GameScene::onEnterTransitionDidFinish() {
  // todo
}

void GameScene::update(float dt) {
  // todo
}

/** パラメータサンプル
this->setBackColor(LayerColor::create());
this->getBackColor();
this->setAD(ImovileAd::create());
this->getAD();
this->setColorChanger(ColorChanger::create());
this->getColorChanger();
*/
