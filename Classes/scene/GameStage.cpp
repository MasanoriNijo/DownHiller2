#include "GameStage.h"

#include "scene/TitleScene.h"
#include "scene/TestScene.h"
#include "scene/TestPhysicsScene.h"
#include "scene/HelloWorldScene.h"

GameStage::GameStage():
_gameTitle(NULL), _btn1(NULL), _btn2(NULL), _btn3(NULL), _btn4(NULL), _menu(NULL),_touch(NULL),_bike(NULL),_contactlistener(NULL), _courceMaker(NULL), _courceManager(NULL)
{}

GameStage::~GameStage() {
    NJLOG("hoge:GameStage::~GameStage()");
    CC_SAFE_RELEASE_NULL(_gameTitle);
    CC_SAFE_RELEASE_NULL(_btn1);
    CC_SAFE_RELEASE_NULL(_btn2);
    CC_SAFE_RELEASE_NULL(_btn3);
    CC_SAFE_RELEASE_NULL(_btn4);
    CC_SAFE_RELEASE_NULL(_menu);
    CC_SAFE_RELEASE_NULL(_touch);
    CC_SAFE_RELEASE_NULL(_bike);
    CC_SAFE_RELEASE_NULL(_contactlistener);
    CC_SAFE_RELEASE_NULL(_courceMaker);
    CC_SAFE_RELEASE_NULL(_courceManager);
}

Scene* GameStage::createScene() {
    auto scene = Scene::Scene::createWithPhysics();
    auto world = scene->getPhysicsWorld();
    world->setGravity(GRAVITY_ACCERATION);
    world->setSpeed(PHYSICS_WOELD_SPEED);
#if DEBUG_PHYSICS_MASK
    world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
#endif
    auto layer = GameStage::create();
    scene->addChild(layer);
    return scene;
}

bool GameStage::init() {
    if (!GameScene::init()) {
        return false;
    }
    setSoundEffect("btnon.mp");
    setBackGroundColor();
    setPosition(ctPt);
//    setBtn1(generateMenuItemSprite([this](Ref* ref){
//        transitonScene(TitleScene::createScene());
//    }, Size(1,1), L_BTN_BACK, Color3B::WHITE, Color3B::YELLOW, false));
    setBtn1(generateMenuItemSprite([this](Ref* ref){
        transitonScene(TitleScene::createScene());
    }, Size(1,1), L_BTN_BACK, Color3B::WHITE, Color3B::YELLOW, false));
//    setBtn2(MenuItemImage::create("howto_btn.png", "howto_btn_p.png",[this](Ref* ref) {
//        getBike()->weightPt = Vec2(-6,6);
//        getBike()->weightPt = Vec2(6,6);
//    }));
//    setBtn3(MenuItemImage::create("howto_btn.png", "howto_btn_p.png",[this](Ref* ref) {
//        getBike()->weightPt = Vec2(6,6);
//        getBike()->weightPt = Vec2(-6,6);
//    }));
//    setBtn4(MenuItemImage::create("howto_btn.png", "howto_btn_p.png",[this](Ref* ref) {
//        getBike()->weightPt = Vec2(0,6);
//        getBike()->chasePt = Vec2(0,-6);
//    }));
    setMenu(Menu::create(getBtn1(),NULL));
    getMenu()->alignItemsHorizontallyWithPadding(20);
//    mountNode(getMenu(), Vec2(winSize.width - getBtn1()->getContentSize().width/2 -10,
//                              winSize.height - getBtn1()->getContentSize().height/2 -10), OBJ_LAYER_TOP);
    mountNode(getMenu(), ctPt, OBJ_LAYER_TOP);
    setCourceMaker(CourceMaker::create());
    addChild(getCourceMaker());
    
    setCourceManager(CourceManager::create());
    addChild(getCourceManager()->getCourceMakerA());
    addChild(getCourceManager()->getCourceMakerB());
    return true;
}

void GameStage::onEnterTransitionDidFinish() {
    GameScene::onEnterTransitionDidFinish();
//    courceB();
    
//    // Bikeをセット
//    setBike(Bike::create());
//    mountScroleNode(getBike(), RIDER_START_POINT, OBJ_LAYER_TOP);
//    mountScroleNode(getBike()->getSceneChasePt(), getBike()->getPosition() + getBike()->sceneOffset, OBJ_LAYER_TOP);
//    getBike()->SetJoint();
//    getScene()->getPhysicsWorld()->addJoint(getBike()->getFRJoint());
//    getBike()->scheduleUpdate();
//    // ~Bikeをセット
//    // 画面スクロール開始
//    runAction(Follow::create(getBike()->getSceneChasePt()));
//    getCourceManager()->checkAndMadeCource(Vec2::ZERO);
//
//    setContactListener();
    
    setGameState(GameState::READY);
    fstStCnge = true;
    scheduleUpdate();
}

void GameStage::update(float dt) {
    if(fstStCnge){
        fstStCnge = false;
        switch (getGameState()) {
            case GameState::READY: {
                onReady();
                break;
            }
            case GameState::PLAY: {
                onPlay();
                break;
            }
            case GameState::CLEAR: {
                onClear();
                break;
            }
            case GameState::MISS: {
                onMiss();
                break;
            }
        }
    }
    getCourceManager()->checkAndMadeCource(getBike()->getPosition());
    if(getBike()){
//        getDebugMemo()->setString("重心位置:" + ST_VEC2(getBike()->weightPt));
        getDebugMemo()->setString("bike:" + ST_VEC2(getBike()->getPosition()) + " " + ST_INT(getBike()->getRotation()));
//        getDebugMemo()->setString("swaip:" + ST_VEC2(getBike()->weightPt));
//   getDebugMemo()->setString("bike:" + ST_INT(getBike()->centerObjVelo.length()) + "km/h");
    }
}

void GameStage::onReady(){
    // Bikeをセット
    setBike(Bike::create());
    mountScroleNode(getBike(), RIDER_START_POINT, OBJ_LAYER_TOP);
    mountScroleNode(getBike()->getSceneChasePt(), getBike()->getPosition() + getBike()->sceneOffset, OBJ_LAYER_TOP);
    getBike()->SetJoint();
    getScene()->getPhysicsWorld()->addJoint(getBike()->getFRJoint());
    getBike()->scheduleUpdate();
    // ~Bikeをセット
    // 画面スクロール開始
    runAction(Follow::create(getBike()->getSceneChasePt()));
    getCourceManager()->checkAndMadeCource(Vec2::ZERO);
    
    setContactListener();
//    getBike()->setPosition(RIDER_START_POINT);
//    auto wait = DelayTime::create(4);
//    auto moveto = MoveBy::create(5, Vec2(89,0));
    //    auto endFnc = CallFunc::create([this](){
    this->showGameAnnounce(L_GAME_READY, ctPt,[this]{
        setGameState(GameState::PLAY);
        fstStCnge = true;
    });
//    });
//    auto seq = Sequence::create(wait,moveto,endFnc, NULL);
//    getBike()->runAction(seq);
}

void GameStage::onPlay(){
    // 画面スクロール開始
    runAction(Follow::create(getBike()->getSceneChasePt()));
    showGameAnnounce(L_GAME_START, ctPt,[this]{
        getBike()->setTouchEvent();
    });
}

void GameStage::onClear(){
    getBike()->getRwheel()->getPhysicsBody()->setAngularDamping(1);
//    getBike()->getRwheel()->getPhysicsBody()->setLinearDamping(1);
    getBike()->removeTouchEvent();
    showGameAnnounce(L_GAME_CLEAR, ctPt,[this]{
    });
}

void GameStage::onMiss(){
    callSoundEffect("btnon.mp3");
    showGameAnnounce(L_GAME_MISS, ctPt);
    getBike()->getFRJoint()->removeFormWorld();
//    getBike()->getRwheel()->getPhysicsBody()->setAngularDamping(1);
//    getBike()->getRwheel()->getPhysicsBody()->setLinearDamping(1);
    getBike()->unscheduleUpdate();
    getBike()->removeTouchEvent();
    auto gun = Sprite::create("gan.png");
    gun->setPosition(missPt);
    gun->setGlobalZOrder(OBJ_LAYER_TOP);
    addChild(gun);
//    mountScroleNode(gun, missPt, OBJ_LAYER_TOP);
}

void GameStage::setContactListener() {
    //接触感知
    setContactListenner(EventListenerPhysicsContact::create());
    
    getContactListenner()->onContactBegin = [this](PhysicsContact& contact) {
        //        NJLOG("contact_begin");
        //        NJLOG("fWheel_normal");
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

void GameStage::_onContactBegin(PhysicsContact& contact, PhysicsShape* ps){
    switch(ps->getBody()->getTag()){
        case TG_F_WHEEL:{
            getBike()->fWheelTouchPt.set(contact.getContactData()->normal);
            getBike()->fWheelTouched = true;
            //                NJLOG("fWheel_normal");
            //                NJLOG(ST_VEC2(contact.getContactData()->normal).c_str());
            break;
        }
        case TG_R_WHEEL:{
            getBike()->rWheelTouchPt.set(contact.getContactData()->normal);
            getBike()->rWheelTouched = true;
            //                NJLOG("rWheel_normal");
            //                NJLOG(ST_VEC2(contact.getContactData()->normal).c_str());
            break;
        }
        case TG_RIDER: {
            setGameState(GameState::MISS);
            missPt.set(contact.getContactData()->points[0]);
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

void GameStage::_onContactPostSolve(PhysicsContact& contact, PhysicsShape* ps){
    switch(ps->getBody()->getTag()){
        case TG_F_WHEEL:{
            getBike()->fWheelTouchPt.set(contact.getContactData()->normal);
            getBike()->fWheelTouched = true;
            //                NJLOG("fWheel_normal");
            //                NJLOG(ST_VEC2(contact.getContactData()->normal).c_str());
            break;
        }
        case TG_R_WHEEL:{
            getBike()->rWheelTouchPt.set(contact.getContactData()->normal);
            getBike()->rWheelTouched = true;
            //                NJLOG("rWheel_normal");
            //                NJLOG(ST_VEC2(contact.getContactData()->normal).c_str());
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

void GameStage::_onContactSeparate(PhysicsContact& contact, PhysicsShape* ps){
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
 setGameTitle(Label::create());
 getGameTitle();
 setBaseLine(DrawNode::create());
 getBaseLine();
 setbike(DrawNode::create());
 getbike();
 setBtn1(MenuItemImage::create());
 getBtn1();
 setBtn2(MenuItemImage::create());
 getBtn2();
 setBtn3(MenuItemImage::create());
 getBtn3();
 setBtn4(MenuItemImage::create());
 getBtn4();
 setMenu(Menu::create());
 getMenu();
 */
