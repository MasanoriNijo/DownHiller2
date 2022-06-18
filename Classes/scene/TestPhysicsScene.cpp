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
//    this->autorelease();
//    this->setPhysicsBody(PhysicsBody::createEdgeBox(this->winSize));
//    this->getPhysicsBody()->setDynamic(false);
    this->setBackGroundColor();
        
    this->setBtn1(MenuItemImage::create("howto_btn.png", "howto_btn_p.png",[this](Ref* ref) {
        this->transitonScene(TestPhysicsScene::createScene());
    }));
    this->setBtn2(MenuItemImage::create("howto_btn.png", "howto_btn_p.png",[this](Ref* ref) {
        this->transitonScene(TitleScene::createScene());
    }));
    this->setBtn3(MenuItemImage::create("howto_btn.png", "howto_btn_p.png",[this](Ref* ref) {
        courceC();
    }));
    this->setBtn4(MenuItemImage::create("howto_btn.png", "howto_btn_p.png",[this](Ref* ref) {
        _bike->jump(-20);
    }));
    this->setMenu(Menu::create(this->getBtn1(),this->getBtn2(),this->getBtn3(),this->getBtn4(),NULL));
    this->getMenu()->alignItemsHorizontallyWithPadding(20);
    this->mountNode(this->getMenu(), this->ctPt+Vec2(0,-100), OBJ_LAYER_TOP);
    
    
    Vec2 achPt_ = Vec2(0.2,0.5);
    this->setPt1(Sprite2::create("yazi.png"));
    _pt1->setName("pt1");
    _pt1->setDefaultTouchEvent();
    _pt1->setAnchorPoint(achPt_);
    this->mountNode(this->getPt1(), this->ctPt + Vec2(-80,-40) , OBJ_LAYER_TOP);
    
    this->setPt2(Sprite2::create("yazi2.png"));
    _pt2->setName("pt2");
    _pt2->setDefaultTouchEvent();
    _pt2->setAnchorPoint(achPt_);
    this->mountNode(this->getPt2(), this->ctPt + Vec2(-30,-40) , OBJ_LAYER_TOP);

    this->setCourceMaker(CourceMaker::create());
//    _courceMaker->setGlobalZOrder(OBJ_LAYER_TOP);
    this->addChild(getCourceMaker());
    return true;
}

void TestPhysicsScene::onEnterTransitionDidFinish() {
    GameScene::onEnterTransitionDidFinish();
    courceC();
    // Bikeをセットする。
    this->setBike(Bike::create());
    this->mountScroleNode(this->getBike(), Vec2::ZERO, OBJ_LAYER_TOP);
    this->mountScroleNode(this->getBike()->getSceneChasePt(), this->getBike()->getPosition() + this->getBike()->sceneOffset, OBJ_LAYER_TOP);
    this->getBike()->SetJoint();
    this->getScene()->getPhysicsWorld()->addJoint(this->getBike()->getFRJoint());
    
    this->runAction(Follow::create(_bike->getSceneChasePt()));
    
    this->setContactListener();
    this->getBike()->scheduleUpdate();
    
    this->scheduleUpdate();
    
}

void TestPhysicsScene::courceA(){
    
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
    
    Vec2 adPt = Vec2(100,40);
    Vec2 pt_ = getCourceMaker()->getTergetPt();
    Vec2 dir_ = Vec2(10,8);
    for(int i= 0;i<100;i++){
        getCourceMaker()->drawTo(pt_, dir_);
        pt_ += adPt;
        dir_ =Vec2(dir_.x,dir_.y * -1);
    }
    getCourceMaker()->madePhysiceBody();
}

void TestPhysicsScene::courceB(){
    Vec2 stPt = Vec2(100,200);
    Vec2 stDir = Vec2(10,-8);
    getCourceMaker()->calcCurve(stPt, stDir, stPt + Vec2(1600,0), Vec2(stDir.x,-stDir.y), 60);
    getCourceMaker()->madePhysiceBody();
}

void TestPhysicsScene::courceC(){
    Vec2 points[10];
    points[0].x = -51;
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
    
    Vec2 adPt = Vec2(100,40);
    Vec2 pt_ = getCourceMaker()->getTergetPt();
    Vec2 dir_ = Vec2(10,8);
    for(int i= 0;i<100;i++){
        getCourceMaker()->drawTo(pt_, dir_);
        pt_ += adPt;
        dir_ =Vec2(dir_.x,dir_.y * -1);
    }
    getCourceMaker()->madePhysiceBody();
//    getCourceMaker()->drawStart(points[0]+adPt , points[1]-points[0]);
//    getCourceMaker()->drawTo(points[1]+adPt, points[2]-points[1]);
//    getCourceMaker()->drawTo(points[2]+adPt, points[3]-points[2]);
//    getCourceMaker()->drawTo(points[3]+adPt, Vec2(10,-5));
//    getCourceMaker()->madePhysiceBody();
    
}

void TestPhysicsScene::update(float dt) {
    // todo
//    if(this->getBike()){
//        //        this->getDebugMemo()->setString("重心位置:" + ST_VEC2(this->getBike()->weightPt));
//        //        this->getDebugMemo()->setString("bike:" + ST_VEC2(this->getBike()->getPosition()) + " " + ST_INT(this->getBike()->getRotation()));
//        this->getDebugMemo()->setString("swaip:" + ST_VEC2(_bike->weightPt));
//    }
}

void TestPhysicsScene::setContactListener() {
    //接触感知
    this->setContactListenner(EventListenerPhysicsContact::create());
    
    _contactlistener->onContactBegin = [this](PhysicsContact& contact) {
//        NJLOG("contact_begin");
//        NJLOG("fWheel_normal");
        switch(contact.getShapeA()->getBody()->getTag()){
            case TG_F_WHEEL:{
                _bike->fWheelTouchPt.set(contact.getContactData()->normal);
                _bike->fWheelTouched = true;
//                NJLOG("fWheel_normal");
//                NJLOG(ST_VEC2(contact.getContactData()->normal).c_str());
                break;
            }
            case TG_R_WHEEL:{
                _bike->rWheelTouchPt.set(contact.getContactData()->normal);
                _bike->rWheelTouched = true;
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
        }
        switch(contact.getShapeB()->getBody()->getTag()){
            case TG_F_WHEEL:{
                _bike->fWheelTouchPt.set(contact.getContactData()->normal);
                _bike->fWheelTouched = true;
//                NJLOG("fWheel_normal");
//                NJLOG(ST_VEC2(contact.getContactData()->normal).c_str());
                break;
            }
            case TG_R_WHEEL:{
                _bike->rWheelTouchPt.set(contact.getContactData()->normal);
                _bike->rWheelTouched = true;
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
        }
        return true;
    };
    
    _contactlistener->onContactPostSolve = [this](PhysicsContact& contact, const PhysicsContactPostSolve& solve) {
        switch(contact.getShapeA()->getBody()->getTag()){
            case TG_F_WHEEL:{
                _bike->fWheelTouchPt.set(contact.getContactData()->normal);
                _bike->fWheelTouched = true;
//                NJLOG("fWheel_normal");
//                NJLOG(ST_VEC2(contact.getContactData()->normal).c_str());
                break;
            }
            case TG_R_WHEEL:{
                _bike->rWheelTouchPt.set(contact.getContactData()->normal);
                _bike->rWheelTouched = true;
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
        }
        switch(contact.getShapeB()->getBody()->getTag()){
            case TG_F_WHEEL:{
                _bike->fWheelTouchPt.set(contact.getContactData()->normal);
                _bike->fWheelTouched = true;
                NJLOG("fWheel_normal");
                NJLOG(ST_VEC2(contact.getContactData()->normal).c_str());
                break;
            }
            case TG_R_WHEEL:{
                _bike->rWheelTouchPt.set(contact.getContactData()->normal);
                _bike->rWheelTouched = true;
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
        }
        return true;
    };
    
    _contactlistener->onContactSeparate = [this](PhysicsContact& contact) {
        switch(contact.getShapeA()->getBody()->getTag()){
            case TG_F_WHEEL:{
                _bike->fWheelTouchPt.set(contact.getContactData()->normal);
                _bike->fWheelTouched = false;
                NJLOG("fWheel_touch_OFF");
                NJLOG(ST_VEC2(contact.getContactData()->normal).c_str());
                break;
            }
            case TG_R_WHEEL:{
                _bike->rWheelTouchPt.set(contact.getContactData()->normal);
                _bike->rWheelTouched = false;
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
        }
        switch(contact.getShapeB()->getBody()->getTag()){
            case TG_F_WHEEL:{
                _bike->fWheelTouchPt.set(contact.getContactData()->normal);
                _bike->fWheelTouched = false;
                NJLOG("fWheel_touch_OFF");
                NJLOG(ST_VEC2(contact.getContactData()->normal).c_str());
                break;
            }
            case TG_R_WHEEL:{
                _bike->rWheelTouchPt.set(contact.getContactData()->normal);
                _bike->rWheelTouched = false;
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
        }
        return true;
    };
    
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_contactlistener,this);
    
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
