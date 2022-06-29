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
    mountNode(getMenu(), Vec2(winSize.width - getBtn1()->getContentSize().width/2 -10,
                              winSize.height - getBtn1()->getContentSize().height/2 -10), OBJ_LAYER_TOP);
    
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
    
    // Bikeをセット
    setBike(Bike::create());
    mountScroleNode(getBike(), Vec2::ZERO, OBJ_LAYER_TOP);
    mountScroleNode(getBike()->getSceneChasePt(), getBike()->getPosition() + getBike()->sceneOffset, OBJ_LAYER_TOP);
    getBike()->SetJoint();
    getScene()->getPhysicsWorld()->addJoint(getBike()->getFRJoint());
    runAction(Follow::create(getBike()->getSceneChasePt()));
    getBike()->scheduleUpdate();
    // ~Bikeをセット
    
    getCourceManager()->checkAndMadeCource(getBike()->getPosition());
    
    setContactListener();
    
    setGameState(GameState::READY);
    fstStCnge = true;
    scheduleUpdate();
}

void GameStage::courceA(){
    auto flg = Flg::create();
    getCourceMaker()->drawStart(Vec2(-50,100),Vec2::ZERO);
    getCourceMaker()->drawByStraight(Vec2(0,-100));
    getCourceMaker()->drawByStraight(Vec2(200,-30));
    flg->setGlobalZOrder(OBJ_LAYER_TOP);
    flg->setPosition(getCourceMaker()->getTergetPt());
    flg->setRotation(getCalc()->nomlRad(getCourceMaker()->getTargetDir()));
    addChild(flg);
    getCourceMaker()->drawBySmoothCurve(Vec2(50,-40));
    getCourceMaker()->drawBySmoothCurve(Vec2(50,40));
    getCourceMaker()->drawByStraight(200,0);
    getCourceMaker()->drawByStraight(Vec2(0,100));
    getCourceMaker()->madePhysiceBody();
}

void GameStage::courceB(){
    getCourceMaker()->drawStart(Vec2(-50,100),Vec2::ZERO);
    getCourceMaker()->drawByStraight(Vec2(0,-100));
    getCourceMaker()->drawByStraight(Vec2(200,0));
    for(int i = 0;i<2;i++){
        getCourceMaker()->drawBySmoothCurve(Vec2(50,20));
        getCourceMaker()->drawBySmoothCurve(Vec2(80,-50));
        getCourceMaker()->drawBySmoothCurve(Vec2(100,50));
        getCourceMaker()->drawBySmoothCurve(Vec2(100,-80));
        getCourceMaker()->drawBySmoothCurve(Vec2(130,100));
        getCourceMaker()->drawByStraight(Vec2(300,0));
        getCourceMaker()->drawByStraight(Vec2(0,-50));
        getCourceMaker()->drawByStraight(Vec2(90,0));
        getCourceMaker()->drawByCurve(Vec2(240,-30), -50);
        getCourceMaker()->drawByStraight(Vec2(0,-50));
        getCourceMaker()->drawByStraight(Vec2(90,0));
    }
    getCourceMaker()->drawByStraight(Vec2(90,0));
    auto flg = Flg::create();
    flg->setGlobalZOrder(OBJ_LAYER_TOP);
    flg->setPosition(getCourceMaker()->getTergetPt());
    flg->setRotation(getCalc()->nomlKaku(Vec2::ZERO, getCourceMaker()->getTargetDir()));
    addChild(flg);
    getCourceMaker()->drawByStraight(Vec2(90,0));
    getCourceMaker()->drawByStraight(Vec2(0,100));
    getCourceMaker()->madePhysiceBody();
}

void GameStage::courceC(){
    Vec2 points[10];
    points[0].x = -50;
    points[0].y = 100;
    points[1].x = -50;
    points[1].y = -20;
    points[2].x = 300;
    points[2].y = -20;
    points[3].x = 600;
    points[3].y = -70;
    
    getCourceMaker()->drawStart(points[0], points[1]-points[0]);
    getCourceMaker()->drawTo(points[1], points[2]-points[1]);
    getCourceMaker()->drawTo(points[2], points[3]-points[2]);
    getCourceMaker()->drawTo(points[3], Vec2(10,-5));
    
    Vec2 adPt = Vec2(150,-40);
    Vec2 pt_ = getCourceMaker()->getTergetPt();
    Vec2 dir_ = Vec2(10,8);
    for(int i= 0;i<100;i++){
        getCourceMaker()->drawTo(pt_, dir_);
        pt_ += adPt;
        dir_ =Vec2(dir_.x,dir_.y * -1);
    }
    getCourceMaker()->madePhysiceBody();
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
        //        getDebugMemo()->setString("bike:" + ST_VEC2(getBike()->getPosition()) + " " + ST_INT(getBike()->getRotation()));
        //        getDebugMemo()->setString("swaip:" + ST_VEC2(getBike()->weightPt));
        getDebugMemo()->setString("bike:" + ST_INT(getBike()->centerObjVelo.length()) + "km/h");
    }
}

void GameStage::onReady(){
    showGameAnnounce(L_GAME_READY, ctPt,[this]{
        setGameState(GameState::PLAY);
        fstStCnge = true;
    });
}

void GameStage::onPlay(){
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
