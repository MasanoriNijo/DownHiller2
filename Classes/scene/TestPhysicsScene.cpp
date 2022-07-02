#include "TestPhysicsScene.h"

#include "scene/TitleScene.h"
#include "scene/TestScene.h"
#include "scene/TestPhysicsScene.h"
#include "scene/HelloWorldScene.h"

TestPhysicsScene::TestPhysicsScene():
_gameTitle(NULL), _btn1(NULL), _btn2(NULL), _btn3(NULL), _btn4(NULL), _menu(NULL),_touch(NULL),_bike(NULL),_contactlistener(NULL), _pt1(NULL), _pt2(NULL), _courceMaker(NULL)
{}

TestPhysicsScene::~TestPhysicsScene() {
    NJLOG("hoge:TestPhysicsScene::~TestPhysicsScene()");
    CC_SAFE_RELEASE_NULL(_gameTitle);
    CC_SAFE_RELEASE_NULL(_btn1);
    CC_SAFE_RELEASE_NULL(_btn2);
    CC_SAFE_RELEASE_NULL(_btn3);
    CC_SAFE_RELEASE_NULL(_btn4);
    CC_SAFE_RELEASE_NULL(_menu);
    CC_SAFE_RELEASE_NULL(_touch);
    CC_SAFE_RELEASE_NULL(_bike);
    CC_SAFE_RELEASE_NULL(_contactlistener);
    CC_SAFE_RELEASE_NULL(_pt1);
    CC_SAFE_RELEASE_NULL(_pt2);
    CC_SAFE_RELEASE_NULL(_courceMaker);
}

Scene* TestPhysicsScene::createScene() {
    auto scene = Scene::Scene::createWithPhysics();
    auto world = scene->getPhysicsWorld();
    world->setGravity(GRAVITY_ACCERATION);
    world->setSpeed(PHYSICS_WOELD_SPEED);
#if DEBUG_PHYSICS_MASK
    world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
#endif
    auto layer = TestPhysicsScene::create();
    scene->addChild(layer);
    return scene;
}

bool TestPhysicsScene::init() {
    if (!GameScene::init()) {
        return false;
    }
    //    this->setPhysicsBody(PhysicsBody::createEdgeBox(this->winSize));
    //    this->getPhysicsBody()->setDynamic(false);
    setBackGroundColor();
    
    setBtn1(MenuItemImage::create("howto_btn.png", "howto_btn_p.png",[this](Ref* ref) {
        if(getBike()){
            getScene()->getPhysicsWorld()->removeJoint(getBike()->getFRJoint());
        }
        transitonScene(TitleScene::createScene());
    }));
    setBtn2(MenuItemImage::create("howto_btn.png", "howto_btn_p.png",[this](Ref* ref) {
        getBike()->autoFlg = true;
        auto delay_ = DelayTime::create(1);
        auto move1_ = MoveTo::create(0.5, Vec2(-6,-6));
        auto move2_ = MoveTo::create(0.1, Vec2(6,-6));
        auto move3_ = MoveTo::create(0.1, Vec2(6,-6));
        auto move4_ = MoveTo::create(0.5, Vec2(0,0));
        auto seq_ = Sequence::create(move1_,delay_,move2_,move4_, NULL);
        getBike()->getDebugPt()->runAction(seq_);
    }));
    setBtn3(MenuItemImage::create("howto_btn.png", "howto_btn_p.png",[this](Ref* ref) {
        getBike()->autoFlg = true;
        auto move1_ = MoveTo::create(0.5, Vec2(0,-6));
        auto move2_ = MoveTo::create(0.1, Vec2(0,6));
        auto delay_ = DelayTime::create(0.1);
        auto move3_ = MoveTo::create(0.01, Vec2(-6,6.2));
        auto move4_ = MoveTo::create(0.5, Vec2(0,0));
        auto seq_ = Sequence::create(move1_,move2_,delay_,move3_,move4_, NULL);
        getBike()->getDebugPt()->runAction(seq_);
    }));
    setBtn4(MenuItemImage::create("howto_btn.png", "howto_btn_p.png",[this](Ref* ref) {
        getBike()->autoFlg = true;
        auto move1_ = MoveTo::create(0.5, Vec2(6,6));
        auto move2_ = MoveTo::create(0.1, Vec2(-6,-6));
        auto delay_ = DelayTime::create(0.4);
        auto move3_ = MoveTo::create(0.05, Vec2(-6,6.0));
        auto delay2_ = DelayTime::create(0.2);
        auto move4_ = MoveTo::create(0.5, Vec2(0,0));
        auto seq_ = Sequence::create(move1_,move2_,delay_,move3_,delay2_,move4_, NULL);
        getBike()->getDebugPt()->runAction(seq_);
    }));
    setMenu(Menu::create(getBtn1(),getBtn2(),getBtn3(),getBtn4(),NULL));
    getMenu()->alignItemsHorizontallyWithPadding(20);
    mountNode(getMenu(), ctPt+Vec2(0,-100), OBJ_LAYER_TOP);
    
    
    Vec2 achPt_ = Vec2(0.2,0.5);
    setPt1(Sprite2::create("yazi.png"));
    _pt1->setName("pt1");
    _pt1->setDefaultTouchEvent();
    _pt1->setAnchorPoint(achPt_);
    mountNode(getPt1(), ctPt + Vec2(-80,-40) , OBJ_LAYER_TOP);
    
    setPt2(Sprite2::create("yazi2.png"));
    _pt2->setName("pt2");
    _pt2->setDefaultTouchEvent();
    _pt2->setAnchorPoint(achPt_);
    mountNode(getPt2(), ctPt + Vec2(-30,-40) , OBJ_LAYER_TOP);
    
    setCourceMaker(CourceMaker::create());
    //    _courceMaker->setGlobalZOrder(OBJ_LAYER_TOP);
    addChild(getCourceMaker());
    return true;
}

void TestPhysicsScene::onEnterTransitionDidFinish() {
    GameScene::onEnterTransitionDidFinish();
    courceB();
    // Bikeをセットする。
    setBike(Bike::create());
    mountScroleNode(getBike(), Vec2::ZERO, OBJ_LAYER_TOP);
    mountScroleNode(getBike()->getSceneChasePt(), getBike()->getPosition() + getBike()->sceneOffset, OBJ_LAYER_TOP);
    getBike()->SetPhysicsPrm();
    getScene()->getPhysicsWorld()->addJoint(getBike()->getFRJoint());
    
    runAction(Follow::create(getBike()->getSceneChasePt()));
    
    setContactListener();
    getBike()->scheduleUpdate();
    
    scheduleUpdate();
    showGameAnnounce("READY!", ctPt);
}

void TestPhysicsScene::courceA(){
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

void TestPhysicsScene::courceB(){
    getCourceMaker()->drawStart(Vec2(-50,100),Vec2::ZERO);
    getCourceMaker()->drawByStraight(Vec2(0,-100));
    getCourceMaker()->drawByStraight(Vec2(200,0));
    for(int i = 0;i<5;i++){
        getCourceMaker()->drawBySmoothCurve(Vec2(50,20));
        getCourceMaker()->drawBySmoothCurve(Vec2(80,-50));
        getCourceMaker()->drawBySmoothCurve(Vec2(100,50));
        auto flg = Flg::create();
        flg->setGlobalZOrder(OBJ_LAYER_TOP);
        flg->setPosition(getCourceMaker()->getTergetPt());
        flg->setRotation(getCalc()->nomlKaku(Vec2::ZERO, getCourceMaker()->getTargetDir()));
        addChild(flg);
        getCourceMaker()->drawBySmoothCurve(Vec2(100,-80));
        getCourceMaker()->drawBySmoothCurve(Vec2(130,100));
        getCourceMaker()->drawByStraight(Vec2(300,0));
        getCourceMaker()->drawByStraight(Vec2(0,-50));
        getCourceMaker()->drawByStraight(Vec2(90,0));
        getCourceMaker()->drawByCurve(Vec2(240,-30), -50);
        getCourceMaker()->drawByStraight(Vec2(0,-50));
        getCourceMaker()->drawByStraight(Vec2(90,0));
    }
    getCourceMaker()->drawByStraight(Vec2(0,100));
    getCourceMaker()->madePhysiceBody();
}

void TestPhysicsScene::courceC(){
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

void TestPhysicsScene::update(float dt) {
    // todo
    if(fstStCnge && getGameState() == GameState::CLEAR){
        showGameAnnounce("GOAL!", ctPt);
        fstStCnge = false;
    }
    if(getBike()){
        if(getDebugMemo()){
            //        getDebugMemo()->setString("重心位置:" + ST_VEC2(getBike()->weightPt));
            //        getDebugMemo()->setString("bike:" + ST_VEC2(getBike()->getPosition()) + " " + ST_INT(getBike()->getRotation()));
            //        getDebugMemo()->setString("swaip:" + ST_VEC2(getBike()->weightPt));
            getDebugMemo()->setString("bike:" + ST_INT(getBike()->centerObjVelo.length()) + "km/h");
        }
    }
}

void TestPhysicsScene::setContactListener() {
    //接触感知
    setContactListenner(EventListenerPhysicsContact::create());
    
    getContactListenner()->onContactBegin = [this](PhysicsContact& contact) {
        //        NJLOG("contact_begin");
        //        NJLOG("fWheel_normal");
        switch(contact.getShapeA()->getBody()->getTag()){
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
                setGameState(GameState::CLEAR);
                fstStCnge = true;
                break;
            }
            default:{
                break;
            }
        }
        switch(contact.getShapeB()->getBody()->getTag()){
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
                setGameState(GameState::CLEAR);
                fstStCnge = true;
                break;
            }
            default:{
                break;
            }
        }
        return true;
    };
    
    getContactListenner()->onContactPostSolve = [this](PhysicsContact& contact, const PhysicsContactPostSolve& solve) {
        switch(contact.getShapeA()->getBody()->getTag()){
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
        switch(contact.getShapeB()->getBody()->getTag()){
            case TG_F_WHEEL:{
                getBike()->fWheelTouchPt.set(contact.getContactData()->normal);
                getBike()->fWheelTouched = true;
                NJLOG("fWheel_normal");
                NJLOG(ST_VEC2(contact.getContactData()->normal).c_str());
                break;
            }
            case TG_R_WHEEL:{
                getBike()->rWheelTouchPt.set(contact.getContactData()->normal);
                getBike()->rWheelTouched = true;
                NJLOG("rWheel_normal");
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
        return true;
    };
    
    getContactListenner()->onContactSeparate = [this](PhysicsContact& contact) {
        switch(contact.getShapeA()->getBody()->getTag()){
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
        switch(contact.getShapeB()->getBody()->getTag()){
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
        return true;
    };
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(getContactListenner(),this);
    
}

/** パラメータサンプル
 this->setGameTitle(Label::create());
 this->getGameTitle();
 this->setBaseLine(DrawNode::create());
 this->getBaseLine();
 this->setbike(DrawNode::create());
 this->getbike();
 this->setBtn1(MenuItemImage::create());
 this->getBtn1();
 this->setBtn2(MenuItemImage::create());
 this->getBtn2();
 this->setBtn3(MenuItemImage::create());
 this->getBtn3();
 this->setBtn4(MenuItemImage::create());
 this->getBtn4();
 this->setMenu(Menu::create());
 this->getMenu();
 */
