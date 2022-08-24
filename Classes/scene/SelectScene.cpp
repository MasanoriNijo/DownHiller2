#include "SelectScene.h"
#include "scene/TitleScene.h"
#include "scene/GameStage.h"

SelectScene::SelectScene():
_gameTitle(NULL), _btn1(NULL), _btn2(NULL),
_menu(NULL),_menu2(NULL),_menu3(NULL),_menu4(NULL),
_touch(NULL), _scrollNode(NULL),_courceManager(NULL),_bike(NULL)
{}

SelectScene::~SelectScene() {
    CC_SAFE_RELEASE_NULL(_gameTitle);
    CC_SAFE_RELEASE_NULL(_btn1);
    CC_SAFE_RELEASE_NULL(_btn2);
    CC_SAFE_RELEASE_NULL(_menu);
    CC_SAFE_RELEASE_NULL(_touch);
    CC_SAFE_RELEASE_NULL(_scrollNode);
    CC_SAFE_RELEASE_NULL(_courceManager);
    CC_SAFE_RELEASE_NULL(_bike);
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
    setBackGroundColor();
    setBackGradientGroundColor();
    drawDebugLine();
    
    setGameTitle(Label::createWithTTF(L_TITLE_SELECT, "irohamaru.ttf", 16));
    getColorChanger()->SetColor(TITLE_COLOR_H, TITLE_COLOR_S, TITLE_COLOR_V);
    getGameTitle()->setTextColor(getColorChanger()->getColor4B());
    getColorChanger()->SetColor(TITLE_FUTI_COLOR_H, TITLE_FUTI_COLOR_S, TITLE_FUTI_COLOR_V);
    getGameTitle()->enableOutline(getColorChanger()->getColor4B(),1);
    mountNode(getGameTitle(), Vec2(ctPt.x,winSize.height-getGameTitle()->getContentSize().height -20), OBJ_LAYER_TOP);
    
    setBtn1(generateMenuItemSprite([this](Ref* ref){
        transitonScene(TitleScene::createScene());
    }, Size(1,1), L_BTN_BACK, Color3B::WHITE, Color3B::YELLOW, false));
    setMenu(Menu::create(getBtn1(),NULL));
    getMenu()->alignItemsHorizontallyWithPadding(20);
    mountNode(getMenu(), Vec2(winSize.width - getBtn1()->getContentSize().width/2 -10,
                              winSize.height - getBtn1()->getContentSize().height/2 -10), OBJ_LAYER_TOP);
    _arrangeBtns();
    _arrangeBtnsForDebug();
    
    setCourceManager(CourceManager::create());
    getCourceManager()->getCourceMakerA()->drawStart(Vec2(-10,50), Vec2(winSize.width + 10,ctPt.y - 50));
    getCourceManager()->getCourceMakerA()->dS(Vec2(winSize.width + 20,0));
    getCourceManager()->getCourceMakerA()->madeCourceBase();
    mountNode(getCourceManager()->getCourceMakerA(),Vec2::ZERO,OBJ_LAYER_LV1);
    
    setBike(Bike::create());
    getBike()->setForDisplay();
    mountNode(getBike(),Vec2(20,63),OBJ_LAYER_LV2);
    getBike()->weightPt = Vec2(0,-4);
    getBike()->riderImageAction();
    
    return true;
}

void SelectScene::onEnterTransitionDidFinish() {
    // todo
}

MenuItemSprite* SelectScene::genStageBtn(int i){
    
    auto udf = UserDefault::getInstance();
    UserDefault::getInstance()->setBoolForKey(UDF_BOOL_DEBUG_STAGE, false);
    if(i>udf->getIntegerForKey(UDF_INT_CLEAR_STAGE,0)+1){
        MenuItemSprite* obj = generateMenuItemSprite([this,i](Ref* ref){
            // 本当は何もしない。
            UserDefault::getInstance()->setIntegerForKey(UDF_INT_SELECTED_STAGE, i);
            transitonScene(GameStage::createScene());
        }, Size(28,28),"??", Color3B::WHITE, Color3B::YELLOW, false);
        obj->setOpacity(30);
        obj->getNormalImage()->setOpacity(120);
        obj->getSelectedImage()->setOpacity(120);
        for(int i=1; i<obj->getChildren().size(); ++i) {
            obj->getChildren().at(i)->setOpacity(30);
        }
        return obj;
    }else if(i==udf->getIntegerForKey(UDF_INT_CLEAR_STAGE,0)+1){
        return generateMenuItemSprite([this,i](Ref* ref){
            UserDefault::getInstance()->setIntegerForKey(UDF_INT_SELECTED_STAGE, i);
            transitonScene(GameStage::createScene());
        }, Size(28,28), i<10 ? "0" + std::to_string(i) : std::to_string(i), Color3B::WHITE, Color3B::YELLOW, true);
    }else{
        return generateMenuItemSprite([this,i](Ref* ref){
            UserDefault::getInstance()->setIntegerForKey(UDF_INT_SELECTED_STAGE, i);
            transitonScene(GameStage::createScene());
        }, Size(28,28), i<10 ? "0" + std::to_string(i) : std::to_string(i), Color3B::WHITE, Color3B::YELLOW, false);
    }
}

void SelectScene::_arrangeBtns(){
    
    int topOffset = -80;
    int verticalPitch = -32;
    setMenu(Menu::create(genStageBtn(1),
                         genStageBtn(2),
                         genStageBtn(3),
                         genStageBtn(4),
                         genStageBtn(5),
                         NULL));
    getMenu()->alignItemsHorizontallyWithPadding(18);
    mountNode(getMenu(), Vec2(ctPt.x,winSize.height+topOffset+verticalPitch * 0) , OBJ_LAYER_TOP);
    
    setMenu2(Menu::create(genStageBtn(6),
                          genStageBtn(7),
                          genStageBtn(8),
                          genStageBtn(9),
                          genStageBtn(10),
                          NULL));
    getMenu2()->alignItemsHorizontallyWithPadding(18);
    mountNode(getMenu2(), Vec2(ctPt.x,winSize.height+topOffset+verticalPitch * 1), OBJ_LAYER_TOP);
    
    setMenu3(Menu::create(genStageBtn(11),
                          genStageBtn(12),
                          genStageBtn(13),
                          genStageBtn(14),
                          genStageBtn(15),
                          NULL));
    getMenu3()->alignItemsHorizontallyWithPadding(18);
    mountNode(getMenu3(), Vec2(ctPt.x,winSize.height+topOffset+verticalPitch * 2), OBJ_LAYER_TOP);
    
    setMenu4(Menu::create(genStageBtn(16),
                          genStageBtn(17),
                          genStageBtn(18),
                          genStageBtn(19),
                          genStageBtn(20),
                          NULL));
    getMenu4()->alignItemsHorizontallyWithPadding(18);
    mountNode(getMenu4(), Vec2(ctPt.x,winSize.height+topOffset+verticalPitch * 3), OBJ_LAYER_TOP);
}

void SelectScene::_arrangeBtnsForDebug(){
    setScrollNode(ScrollNode::create());
    getScrollNode()->setMinScrollPos(-2000);
    getScrollNode()->setMaxScrollPos(2000);
    Vector<MenuItem*> menuItems;
    for(int i=0;i<100;i++){
        std::string stageName;
        if(i<9){
            stageName = "stage:0"+ST_INT(i);
        }else{
            stageName = "stage:"+ST_INT(i);
        }
        Label* label_ = Label::createWithTTF(stageName , "irohamaru.ttf", 8);
        label_->setColor(Color3B::BLACK);
        label_->setGlobalZOrder(OBJ_LAYER_TOP);
        MenuItemLabel* obj_ = MenuItemLabel::create(label_, [this,i](Ref* ref){
            UserDefault::getInstance()->setBoolForKey(UDF_BOOL_DEBUG_STAGE, true);
            UserDefault::getInstance()->setIntegerForKey(UDF_INT_SELECTED_STAGE, i);
            transitonScene(GameStage::createScene());
        });
        obj_->setGlobalZOrder(OBJ_LAYER_TOP);
        menuItems.pushBack(obj_);
    }
    auto menu_ = Menu::createWithArray(menuItems);
    menu_->alignItemsVerticallyWithPadding(0);
    menu_->setAnchorPoint(Vec2(0,1));
    menu_->setPosition(Vec2(ctPt.x,300));
    getScrollNode()->addChild(menu_);
    mountNode(getScrollNode(), Vec2::ZERO, OBJ_LAYER_TOP);
    getScrollNode()->setTouchEvent();
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
