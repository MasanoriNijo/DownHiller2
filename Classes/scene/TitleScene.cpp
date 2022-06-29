#include "TitleScene.h"
#include "scene/TestScene.h"
#include "scene/TestPhysicsScene.h"
#include "scene/GameStage.h"

TitleScene::TitleScene():
_gameTitle(NULL), _startBtn(NULL), _howtoBtn(NULL), _resultBtn(NULL), _menu(NULL)
{}

TitleScene::~TitleScene() {
    CC_SAFE_RELEASE_NULL(_gameTitle);
    CC_SAFE_RELEASE_NULL(_startBtn);
    CC_SAFE_RELEASE_NULL(_howtoBtn);
    CC_SAFE_RELEASE_NULL(_resultBtn);
    CC_SAFE_RELEASE_NULL(_menu);
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
    setBackGroundColor();
    setGameTitle(Label::createWithTTF(L_TITLE, "irohamaru.ttf", 24));
    getGameTitle()->setTextColor(Color4B::BLACK);
    getGameTitle()->enableOutline(Color4B::WHITE,1);
    mountNode(getGameTitle(), Vec2(winSize.width/2,winSize.height -80), OBJ_LAYER_TOP);
    
    setStartBtn(generateMenuItemSprite([this](Ref* ref){
        transitonScene(GameStage::createScene());
    }, Size(1,1), L_BTN_START, Color3B::WHITE, Color3B::YELLOW, false));
    
    setHowToBtn(generateMenuItemSprite([this](Ref* ref){
        transitonScene(TestPhysicsScene::createScene());
    }, Size(1,1), L_BTN_HOWTO, Color3B::WHITE, Color3B::YELLOW, false));
    setResultBtn(generateMenuItemSprite([this](Ref* ref){
        transitonScene(TestScene::createScene());
    }, Size(1,1), "デバック", Color3B::WHITE, Color3B::YELLOW, false));
    setMenu(Menu::create(getStartBtn(),getHowToBtn(),getResultBtn(), NULL));
    getMenu()->alignItemsVerticallyWithPadding(10);
    mountNode(getMenu(),Vec2(winSize.width/2,80), OBJ_LAYER_TOP);
    
    return true;
}

void TitleScene::onEnterTransitionDidFinish() {
    GameScene::onEnterTransitionDidFinish();
    //    getAD()->AdShow(false, true, false, false, false, false);
    // todo
}

void TitleScene::update(float dt) {
    // todo
}

/** パラメータサンプル
 setGameTitle(Sprite::create());
 getGameTitle();
 setStartBtn(MenuItemImage::create());
 getStartBtn();
 setHowToBtn(MenuItemImage::create());
 getHowToBtn();
 setResultBtn(MenuItemImage::create());
 getResultBtn();
 setSMenu(Menu::create());
 getSMenu();
 */
