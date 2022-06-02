#include "ColorChanger.h"

ColorChanger::ColorChanger():
_lc(NULL)
{}

ColorChanger::~ColorChanger() {
    CC_SAFE_RELEASE_NULL(_lc);
}

Scene* ColorChanger::createScene() {
  auto scene = Scene::create();
  auto layer = ColorChanger::create();
//    scene->addChild(layer);
  return scene;
}

bool ColorChanger::init() {
  // todo
  return true;
}

void ColorChanger::onEnterTransitionDidFinish() {
  // todo
}

void ColorChanger::update(float dt) {
  // todo
}

/** パラメータサンプル
this->setLC(LayerColor::create());
this->getLC();
*/
