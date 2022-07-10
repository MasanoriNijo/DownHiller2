#include "TitleScene.h"
#include "scene/TestScene.h"
#include "scene/TestPhysicsScene.h"
#include "scene/GameStage.h"
#include "scene/SelectScene.h"

TitleScene::TitleScene():
_gameTitle(NULL), _startBtn(NULL), _howtoBtn(NULL), _resultBtn(NULL),
_menu(NULL),_courceManager(NULL),_bike(NULL)
{}

TitleScene::~TitleScene() {
    CC_SAFE_RELEASE_NULL(_gameTitle);
    CC_SAFE_RELEASE_NULL(_startBtn);
    CC_SAFE_RELEASE_NULL(_howtoBtn);
    CC_SAFE_RELEASE_NULL(_resultBtn);
    CC_SAFE_RELEASE_NULL(_menu);
    CC_SAFE_RELEASE_NULL(_courceManager);
    CC_SAFE_RELEASE_NULL(_bike);
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
//    drawDebugLine();
    setBackGroundColor();
//    setBackGradientGroundColor();
    setGameTitle(Label::createWithTTF(L_TITLE, "irohamaru.ttf", 30));
    getColorChanger()->SetColor(TITLE_COLOR_H, TITLE_COLOR_S, TITLE_COLOR_V);
    getGameTitle()->setTextColor(getColorChanger()->getColor4B());
    getColorChanger()->SetColor(TITLE_FUTI_COLOR_H, TITLE_FUTI_COLOR_S, TITLE_FUTI_COLOR_V);
    getGameTitle()->enableOutline(getColorChanger()->getColor4B(),1);
    mountNode(getGameTitle(), Vec2(winSize.width/2,winSize.height -80), OBJ_LAYER_TOP);
    
    setStartBtn(generateMenuItemSprite([this](Ref* ref){
        transitonScene(SelectScene::createScene());
    }, Size(1,1), L_BTN_START, Color3B::WHITE, Color3B::YELLOW, true));
    
    setHowToBtn(generateMenuItemSprite([this](Ref* ref){
        transitonScene(TestPhysicsScene::createScene());
    }, Size(1,1), L_BTN_HOWTO, Color3B::WHITE, Color3B::YELLOW, false));
    
    setResultBtn(generateMenuItemSprite([this](Ref* ref){
        transitonScene(TestScene::createScene());
    }, Size(1,1), "デバック", Color3B::WHITE, Color3B::YELLOW, false));
    
    setMenu(Menu::create(getStartBtn(), NULL));
    getMenu()->alignItemsVerticallyWithPadding(10);
    mountNode(getMenu(),Vec2(winSize.width/2,60), OBJ_LAYER_TOP);
    
    setCourceManager(CourceManager::create());
    getCourceManager()->getCourceMakerA()->drawStart(Vec2(-10,ctPt.y-20), Vec2(winSize.width + 10,ctPt.y - 50));
    getCourceManager()->getCourceMakerA()->drawByStraight(Vec2(winSize.width + 20,-60));
    getCourceManager()->getCourceMakerA()->madeCourceBase();
    mountNode(getCourceManager()->getCourceMakerA(),Vec2::ZERO,OBJ_LAYER_LV1);
    
    setBike(Bike::create());
    getBike()->setForDisplay();
    mountNode(getBike(),ctPt+Vec2(-12,-20),OBJ_LAYER_LV2);
    getBike()->weightPt = Vec2(-4,0);
    getBike()->riderImageAction();
    getBike()->setRotation(-30);
   
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
