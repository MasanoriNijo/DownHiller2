#include "TitleScene.h"

TitleScene::TitleScene():_productTitler(NULL){}

TitleScene::~TitleScene() {
    CC_SAFE_RELEASE_NULL(_productTitler);
}

Scene* TitleScene::createScene() {
  auto scene = Scene::create();
  auto layer = TitleScene::create();
    scene->addChild(layer);
  return scene;
}

bool TitleScene::init() {
    if (!GameScene::init()) {
        return false;
    }
    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(TitleScene::menuCloseCallback, this));
        closeItem->setPosition(this->ctPt);
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);
    this->ctPt.add(Vec2(50,50));
    this->setSprite(Label::createWithTTF("鬼舞辻無惨", "irohamaru.ttf", 24),this->ctPt, OBJ_LAYER_LV3);
    
  return true;
}

void TitleScene::onEnterTransitionDidFinish() {
    this->scheduleUpdate();
}

void TitleScene::update(float dt) {
  // todo
}

void TitleScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
/** パラメータサンプル
this->setProductTitle(Sprite::create());
this->getProductTitle();
*/
