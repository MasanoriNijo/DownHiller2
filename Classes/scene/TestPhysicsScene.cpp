#include "TestPhysicsScene.h"

#include "scene/TitleScene.h"
#include "scene/TestScene.h"
#include "scene/TestPhysicsScene.h"
#include "scene/HelloWorldScene.h"

TestPhysicsScene::TestPhysicsScene():
_gameTitle(NULL), _baseLine(NULL), _ball(NULL), _btn1(NULL), _btn2(NULL), _btn3(NULL), _btn4(NULL), _menu(NULL),_touch(NULL),_bike(NULL),_contactlistener(NULL)
{}

TestPhysicsScene::~TestPhysicsScene() {
    NJLOG("hoge:TestPhysicsScene::~TestPhysicsScene()");
    CC_SAFE_RELEASE_NULL(_gameTitle);
    CC_SAFE_RELEASE_NULL(_baseLine);
    CC_SAFE_RELEASE_NULL(_ball);
    CC_SAFE_RELEASE_NULL(_btn1);
    CC_SAFE_RELEASE_NULL(_btn2);
    CC_SAFE_RELEASE_NULL(_btn3);
    CC_SAFE_RELEASE_NULL(_btn4);
    CC_SAFE_RELEASE_NULL(_menu);
    CC_SAFE_RELEASE_NULL(_touch);
    CC_SAFE_RELEASE_NULL(_bike);
    CC_SAFE_RELEASE_NULL(_contactlistener);
    GameScene::~GameScene();
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
    
    this->setPhysicsBody(PhysicsBody::createEdgeBox(this->winSize));
    this->getPhysicsBody()->setDynamic(false);
    this->setBackGroundColor();
    
    this->setBaseLine(DrawNode::create());
    this->getBaseLine()->setColor(Color3B::WHITE);
    this->getBaseLine()->setLineWidth(11);
    points[0].x = -winSize.width/2;
    points[0].y = 20;
    points[1].x = -winSize.width/2+100;
    points[1].y = 30;
    points[2].x = 0;
    points[2].y = -50;
    points[3].x = 30;
    points[3].y = -10;
    points[4].x = winSize.width/2-20;
    points[4].y = -20;
    points[5].x = winSize.width/2-20;
    points[5].y = -20;
    points[6].x = winSize.width/2-20;
    points[6].y = -20;
    points[7].x = winSize.width/2-20;
    points[7].y = -20;
    points[8].x = winSize.width/2-20;
    points[8].y = -20;
    points[9].x = winSize.width/2-20;
    points[9].y = -20;
    points[10].x = winSize.width/2-20;
    points[10].y = -20;
    points[11].x = winSize.width/2-20;
    points[11].y = -20;
    points[12].x = winSize.width/2;
    points[12].y = -30;
    points[13].x = 0;
    points[13].y = -winSize.height/2;
    this->getBaseLine()->drawPoly(points, 4, false, Color4F::GREEN);
    auto _material = PHYSICSBODY_MATERIAL_DEFAULT;
    _material.restitution = 0.0001f;
    _material.friction =1.0f;
    _material.density = 0.001f;
    this->getBaseLine()->setPhysicsBody(PhysicsBody::createEdgePolygon(points, 14,_material));
    this->getBaseLine()->getPhysicsBody()->setDynamic(false);
    this->getBaseLine()->getPhysicsBody()->setCategoryBitmask(CT_COURCE);
    this->getBaseLine()->getPhysicsBody()->setCollisionBitmask(CT_WHEEL);
    this->getBaseLine()->getPhysicsBody()->setContactTestBitmask(CT_WHEEL);
    this->getBaseLine()->getPhysicsBody()->setTag(TG_COURCE);
    this->mountNode(this->getBaseLine(), ctPt, OBJ_LAYER_LV1);
    
    this->setBtn1(MenuItemImage::create("howto_btn.png", "howto_btn_p.png",[this](Ref* ref) {
        this->transitonScene(TestPhysicsScene::createScene());
    }));
    this->setBtn2(MenuItemImage::create("howto_btn.png", "howto_btn_p.png",[this](Ref* ref) {
        this->transitonScene(TestScene::createScene());
    }));
    this->setBtn3(MenuItemImage::create("howto_btn.png", "howto_btn_p.png",[this](Ref* ref) {
        float kaku = this->getCalc()->nomlKaku(_bike->getRwheel()->getPosition(),_bike->getFwheel()->getPosition());
        _bike->fWheelUp(15);
        _bike->rWheelJump(-15);
    }));
    this->setBtn4(MenuItemImage::create("howto_btn.png", "howto_btn_p.png",[this](Ref* ref) {
        _bike->rWheelRot(-5);
        
    }));
    this->setMenu(Menu::create(this->getBtn1(),this->getBtn2(),this->getBtn3(),this->getBtn4(),NULL));
    this->getMenu()->alignItemsHorizontallyWithPadding(20);
    this->mountNode(this->getMenu(), this->ctPt+Vec2(0,-100), OBJ_LAYER_TOP);
    
    return true;
}

void TestPhysicsScene::onEnterTransitionDidFinish() {
    // Bikeをセットする。
    this->setBike(Bike::create());
    this->mountNode(this->getBike(), this->ctPt+Vec2(-100,30), OBJ_LAYER_TOP);
    this->getBike()->SetJoint();
    this->getScene()->getPhysicsWorld()->addJoint(this->getBike()->getFRJoint());
    
    this->setContactListener();
    this->getBike()->scheduleUpdate();
    
    this->scheduleUpdate();
}

void TestPhysicsScene::update(float dt) {
    // todo
    if(this->getBike()){
        //        this->getDebugMemo()->setString("重心位置:" + ST_VEC2(this->getBike()->weightPt));
        //        this->getDebugMemo()->setString("bike:" + ST_VEC2(this->getBike()->getPosition()) + " " + ST_INT(this->getBike()->getRotation()));
        this->getDebugMemo()->setString("bike:" + ST_NODE(_bike));
    }
}

void TestPhysicsScene::setContactListener() {
    //接触感知
    this->setContactListenner(EventListenerPhysicsContact::create());
    
    _contactlistener->onContactBegin = [this](PhysicsContact& contact) {
        NJLOG("contact_begin");
        NJLOG("fWheel_normal");
        switch(contact.getShapeA()->getBody()->getTag()){
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
    
    _contactlistener->onContactPostSolve = [this](PhysicsContact& contact, const PhysicsContactPostSolve& solve) {
        switch(contact.getShapeA()->getBody()->getTag()){
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
