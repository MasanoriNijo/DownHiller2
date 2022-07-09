#include "SelectScene.h"
#include "scene/TitleScene.h"
#include "scene/GameStage.h"

SelectScene::SelectScene():
_gameTitle(NULL), _btn1(NULL), _btn2(NULL), _menu(NULL), _touch(NULL), _scrollNode(NULL)
{}

SelectScene::~SelectScene() {
    CC_SAFE_RELEASE_NULL(_gameTitle);
    CC_SAFE_RELEASE_NULL(_btn1);
    CC_SAFE_RELEASE_NULL(_btn2);
    CC_SAFE_RELEASE_NULL(_menu);
    CC_SAFE_RELEASE_NULL(_touch);
    CC_SAFE_RELEASE_NULL(_scrollNode);
}

Scene* SelectScene::createScene() {
    auto scene = Scene::create();
    auto layer = SelectScene::create();
    scene->addChild(layer);
    return scene;
}

bool SelectScene::init() {
    if (!GameScene::init()) {
        return false;
    }
    //    setBackGroundColor();
    setBackGradientGroundColor();
    drawDebugLine();
    
    setGameTitle(Label::createWithTTF(L_TITLE_SELECT, "irohamaru.ttf", 16));
    getGameTitle()->setTextColor(Color4B::BLACK);
    getGameTitle()->enableOutline(Color4B::WHITE,1);
    mountNode(getGameTitle(), Vec2(ctPt.x,winSize.height-getGameTitle()->getContentSize().height -5), OBJ_LAYER_TOP);
    
    setBtn1(generateMenuItemSprite([this](Ref* ref){
        transitonScene(TitleScene::createScene());
    }, Size(1,1), L_BTN_BACK, Color3B::WHITE, Color3B::YELLOW, false));
    setMenu(Menu::create(getBtn1(),NULL));
    getMenu()->alignItemsHorizontallyWithPadding(20);
    mountNode(getMenu(), Vec2(winSize.width - getBtn1()->getContentSize().width/2 -10,
                              winSize.height - getBtn1()->getContentSize().height/2 -10), OBJ_LAYER_TOP);
    _arrangeBtns();
    return true;
}

void SelectScene::onEnterTransitionDidFinish() {
    // todo
}

MenuItemSprite* SelectScene::genStageBtn(int i){
    return generateMenuItemSprite([this,i](Ref* ref){
        UserDefault::getInstance()->setIntegerForKey(UDF_INT_SELECTED_STAGE, i);
        transitonScene(GameStage::createScene());

    }, Size(1,1), L_STAGE + std::to_string(i), Color3B::WHITE, Color3B::YELLOW, false);
}

void SelectScene::_arrangeBtns(){
    setMenu(Menu::create(genStageBtn(1),
                         genStageBtn(2),
                         genStageBtn(3),
                         genStageBtn(4),
                         genStageBtn(5),
                         genStageBtn(6),
                         genStageBtn(7),
                         genStageBtn(8),
                         genStageBtn(9),
                         genStageBtn(10),
                         genStageBtn(11),
                         genStageBtn(12),
                         genStageBtn(13),
                         genStageBtn(14),
                         genStageBtn(15),
                         genStageBtn(16),
                         NULL));

    getMenu()->alignItemsVerticallyWithPadding(4);
    getMenu()->setPosition(Vec2(ctPt.x,ctPt.y - 50));
    getMenu()->setAnchorPoint(Vec2(0.5,1));
    setScrollNode(ScrollNode::create());
    getScrollNode()->setMaxScrollPos(10);
    getScrollNode()->setTouchEvent();
    getScrollNode()->addChild(getMenu());
    mountNode(getScrollNode(), Vec2::ZERO, OBJ_LAYER_TOP);
}

void SelectScene::update(float dt) {
    // todo
}

/** パラメータサンプル
 this->setGameTitle(Label::create());
 this->getGameTitle();
 this->setBtn1(MenuItemSprite::create());
 this->getBtn1();
 this->setBtn2(MenuItemSprite::create());
 this->getBtn2();
 this->setMenu(Menu::create());
 this->getMenu();
 this->setTouch(TouchEventHelper::create());
 this->getTouch();
 this->setScrollNode(ScrollNode::create());
 this->getScrollNode();
 */
