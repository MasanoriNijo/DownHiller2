#include "TitleScene.h"
#include "scene/TestScene.h"
#include "scene/TestPhysicsScene.h"
#include "scene/GameStage.h"
#include "scene/SelectScene.h"

TitleScene::TitleScene():
_gameTitle(NULL), _startBtn(NULL), _howtoBtn(NULL), _resultBtn(NULL),
_menu(NULL),_courceManager(NULL),_bike(NULL),_contactlistener(NULL)
{}

TitleScene::~TitleScene() {
    CC_SAFE_RELEASE_NULL(_gameTitle);
    CC_SAFE_RELEASE_NULL(_startBtn);
    CC_SAFE_RELEASE_NULL(_howtoBtn);
    CC_SAFE_RELEASE_NULL(_resultBtn);
    CC_SAFE_RELEASE_NULL(_menu);
    CC_SAFE_RELEASE_NULL(_courceManager);
    CC_SAFE_RELEASE_NULL(_bike);
    CC_SAFE_RELEASE_NULL(_contactlistener);
    stopBGM("");
}

Scene* TitleScene::createScene() {
    auto scene = Scene::Scene::createWithPhysics();
    auto world = scene->getPhysicsWorld();
    world->setGravity(GRAVITY_ACCERATION);
    world->setSpeed(PHYSICS_WOELD_SPEED);
#if DEBUG_PHYSICS_MASK
    world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
#endif
    auto layer = TitleScene::create();
    scene->addChild(layer);
    return scene;
}

bool TitleScene::init() {
    if (!GameScene::init()) {
        return false;
    }
//    drawDebugLine();
//    setBackGroundColor();
    setBackGradientGroundColor();
    setGameTitle(Label::createWithTTF(L_TITLE, "irohamaru.ttf", 30));
    getColorChanger()->SetColor(TITLE_COLOR_H, TITLE_COLOR_S, TITLE_COLOR_V);
    getGameTitle()->setTextColor(getColorChanger()->getColor4B());
    getColorChanger()->SetColor(TITLE_FUTI_COLOR_H, TITLE_FUTI_COLOR_S, TITLE_FUTI_COLOR_V);
    getGameTitle()->enableOutline(getColorChanger()->getColor4B(),1);
    mountNode(getGameTitle(), Vec2(winSize.width/2,winSize.height -80), OBJ_LAYER_TOP);
    
    setStartBtn(generateMenuItemSprite([this](Ref* ref){
        callSoundEffect("button05.mp3");
        transitonScene(SelectScene::createScene());
    }, Size(1,1), L_BTN_START, Color3B::WHITE, Color3B::YELLOW, true));
    
    setHowToBtn(generateMenuItemSprite([this](Ref* ref){
        callSoundEffect("button05.mp3");
        UserDefault::getInstance()->setIntegerForKey(UDF_INT_SELECTED_STAGE, 0);
        transitonScene(GameStage::createScene());
    }, Size(1,1), L_BTN_HOWTO, Color3B::WHITE, Color3B::YELLOW, false));
    
    setMenu(Menu::create(getStartBtn(), getHowToBtn(), NULL));
    getMenu()->alignItemsVerticallyWithPadding(10);
    mountNode(getMenu(),Vec2(winSize.width/2,60), OBJ_LAYER_LV3);
    
    setCourceManager(CourceManager::create());
    getCourceManager()->setForTitle();
    addChild(getCourceManager()->getCourceMakerA());
    addChild(getCourceManager()->getCourceMakerB());
    addChild(getCourceManager()->getGurd());
    setBGM("BGM124-110921-tamashiinopistol-wav-nointro.mp3");
       
    return true;
}

void TitleScene::onEnterTransitionDidFinish() {
    GameScene::onEnterTransitionDidFinish();
    //    getAD()->AdShow(false, true, false, false, false, false);
    
    // コースをセット
    UserDefault::getInstance()->setBoolForKey(UDF_BOOL_DEBUG_STAGE, false);
    getCourceManager()->checkAndMadeCource(Vec2::ZERO);
    
    // bikeをセット
    setBike(Bike::create());
    mountScroleNode(getBike(), Vec2::ZERO, OBJ_LAYER_LV3-1);
    getBike()->sceneOffset = Vec2(-10,35);
    mountScroleNode(getBike()->getSceneChasePt(), getBike()->getFwheel()->getPosition()+getBike()->sceneOffset, OBJ_LAYER_BUTTOM);
    getBike()->SetPhysicsPrm();
    getScene()->getPhysicsWorld()->addJoint(getBike()->getFRJoint());
    getBike()->scheduleUpdate();

    // 接触感知
    setContactListener();
    
    // 画面スクロール開始
    runAction(Follow::create(getBike()->getSceneChasePt()));
    scheduleUpdate();
    demo();
    
    startBGM("BGM124-110921-tamashiinopistol-wav-nointro.mp3");
}

void TitleScene::update(float dt) {
    if(fstStCnge){
        fstStCnge = false;
        switch (getGameState()) {
            case GameState::READY: {
                break;
            }
            case GameState::PLAY: {
                break;
            }
            case GameState::CLEAR: {
                stopBGM("");
                getBike()->getRwheel()->getPhysicsBody()->setAngularDamping(1);
                getBike()->removeTouchEvent();
                getBike()->stopAllActions();
                Director::getInstance()->getEventDispatcher()->removeEventListener(getContactListenner());
                auto wait_ = DelayTime::create(3.0);
                auto endfunc_ = CallFunc::create([this]{
                    transitonScene(TitleScene::createScene());
                });
                runAction(Sequence::create(wait_,endfunc_, NULL));
                break;
            }
            case GameState::MISS: {
                stopBGM("");
                getBike()->getFRJoint()->removeFormWorld();
                getBike()->getFwheel()->getPhysicsBody()->setVelocity(Vec2::ZERO);
                getBike()->getRwheel()->getPhysicsBody()->setVelocity(Vec2::ZERO);
                getBike()->unscheduleUpdate();
                Director::getInstance()->getEventDispatcher()->removeEventListener(getContactListenner());
                getBike()->removeTouchEvent();
                Director::getInstance()->getEventDispatcher()->removeEventListener(getContactListenner());
                auto gun = Sprite::create("gan.png");
                gun->setRotation(getCalc()->chgKaku(missNomalPt)-getBike()->getRotation());
                gun->setPosition(Vec2(getBike()->getRider()->getContentSize().width/2,
                                      getBike()->getRider()->getContentSize().height/2));
                gun->setGlobalZOrder(OBJ_LAYER_TOP);
                auto fade = FadeOut::create(0.5);
                gun->runAction(fade);
                getBike()->getRider()->addChild(gun);
                auto wait2_ = DelayTime::create(3.0);
                auto endfunc2_ = CallFunc::create([this]{
                    transitonScene(TitleScene::createScene());
                });
                runAction(Sequence::create(wait2_,endfunc2_, NULL));
                break;
            }
        }
    }
    getCourceManager()->checkAndMadeCource(getBike()->getPosition());
}

void TitleScene::demo(){
    
    getBike()->autoFlg = true;
    getBike()->weightPt= Vec2::ZERO;
    getBike()->getDebugPt()->setPosition(Vec2::ZERO);
    getBike()->removeTouchEvent();
    
    // werry
    auto move10_ = MoveTo::create(1.5, Vec2(6,0));
    auto move11_ = MoveTo::create(0.15, Vec2(-6,0));
    auto werryF4_ = Repeat::create(Sequence::create(move10_,move11_, NULL), 1);
        
    // FRJump
    auto delay14_ = DelayTime::create(0.5);
    auto move14_ = MoveTo::create(0.8, Vec2(0,-6));
    auto move15_ = MoveTo::create(0.05, Vec2(0,6));
    auto frJump4_ = Repeat::create(Sequence::create(delay14_,move14_,move15_, NULL), 1);
    
    // RJump
    auto move16_ = MoveTo::create(0.8, Vec2(6,6));
    auto move17_ = MoveTo::create(0.1, Vec2(-6,-6));
    auto move18_ = DelayTime::create(0.4);
    auto move19_ = MoveTo::create(0.05, Vec2(-6,6.0));
    auto delay20_ = DelayTime::create(0.5);
    auto rJump4_ = Repeat::create(Sequence::create(move16_,move17_,move18_,move19_,delay20_, NULL), 1);
    
    // dush
    auto move21_ = MoveTo::create(0.8, Vec2(-5,-6));
    auto move22_ = MoveTo::create(0.1, Vec2(6,-6));
    auto dush4_ = Repeat::create(Sequence::create(move21_,move22_, NULL), 1);
    
    // break
    auto move23_ = MoveTo::create(0.8, Vec2(-6,-6));
    auto delay24_ = DelayTime::create(3);
    auto move25_ = MoveTo::create(0.8, Vec2(0,0));
    auto break_ = Sequence::create(move23_,delay24_,move25_, NULL);
    

     auto seq_ = Sequence::create(
                                  // werry
                                  werryF4_,
                                  // frJump
                                  frJump4_,
                                  // rJump
                                  rJump4_,
                                  // dush
                                  dush4_,
                                  // stop
                                  break_,
                                  NULL);
    
    getBike()->getDebugPt()->runAction(RepeatForever::create(seq_));

}

void TitleScene::setContactListener() {
    //接触感知
    setContactListenner(EventListenerPhysicsContact::create());
    
    getContactListenner()->onContactBegin = [this](PhysicsContact& contact) {
        _onContactBegin(contact, contact.getShapeA());
        _onContactBegin(contact, contact.getShapeB());
        return true;
    };
    
    getContactListenner()->onContactPostSolve = [this](PhysicsContact& contact, const PhysicsContactPostSolve& solve) {
        _onContactPostSolve(contact, contact.getShapeA());
        _onContactPostSolve(contact, contact.getShapeB());
        return true;
    };
    
    getContactListenner()->onContactSeparate = [this](PhysicsContact& contact) {
        _onContactSeparate(contact, contact.getShapeA());
        _onContactSeparate(contact, contact.getShapeB());
        return true;
    };
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(getContactListenner(),this);
}

void TitleScene::_onContactBegin(PhysicsContact& contact, PhysicsShape* ps){
    switch(ps->getBody()->getTag()){
        case TG_F_WHEEL:{
            getBike()->fWheelTouchPt.set(contact.getContactData()->normal);
            getBike()->fWheelTouched = true;
            break;
        }
        case TG_R_WHEEL:{
            getBike()->rWheelTouchPt.set(contact.getContactData()->normal);
            getBike()->rWheelTouched = true;
            break;
        }
        case TG_RIDER: {
            missNomalPt.set(contact.getContactData()->normal);
            setGameState(GameState::MISS);
            fstStCnge = true;
            break;
        }
        case TG_START: {
            break;
        }
        case TG_GOAL: {
            setGameState(GameState::CLEAR);
            fstStCnge = true;
            break;
        }
        default:{
            break;
        }
    }
}

void TitleScene::_onContactPostSolve(PhysicsContact& contact, PhysicsShape* ps){
    switch(ps->getBody()->getTag()){
        case TG_F_WHEEL:{
            getBike()->fWheelTouchPt.set(contact.getContactData()->normal);
            getBike()->fWheelTouched = true;
            break;
        }
        case TG_R_WHEEL:{
            getBike()->rWheelTouchPt.set(contact.getContactData()->normal);
            getBike()->rWheelTouched = true;
            break;
        }
        case TG_START: {
            break;
        }
        case TG_GOAL: {
            break;
        }
        default:{
            break;
        }
    }
}

void TitleScene::_onContactSeparate(PhysicsContact& contact, PhysicsShape* ps){
    switch(ps->getBody()->getTag()){
        case TG_F_WHEEL:{
            getBike()->fWheelTouchPt.set(contact.getContactData()->normal);
            getBike()->fWheelTouched = false;
            NJLOG("fWheel_touch_OFF");
            NJLOG(ST_VEC2(contact.getContactData()->normal).c_str());
            break;
        }
        case TG_R_WHEEL:{
            getBike()->rWheelTouchPt.set(contact.getContactData()->normal);
            getBike()->rWheelTouched = false;
            NJLOG("rWheel_touch_OFF");
            NJLOG(ST_VEC2(contact.getContactData()->normal).c_str());
            break;
        }
        case TG_START: {
            break;
        }
        case TG_GOAL: {
            break;
        }
        default:{
            break;
        }
    }
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
