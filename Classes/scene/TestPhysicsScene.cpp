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
    points[1].x = -winSize.width/2+80;
    points[1].y = -50;
    points[2].x = winSize.width/2-20;
    points[2].y = -50;
    points[3].x = winSize.width/2-20;
    points[3].y = -20;
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
    this->getBaseLine()->setPhysicsBody(PhysicsBody::createEdgePolygon(points, 14));
    this->getBaseLine()->getPhysicsBody()->setDynamic(false);
    this->mountNode(this->getBaseLine(), ctPt, OBJ_LAYER_LV1);
    
    this->setBtn1(MenuItemImage::create("howto_btn.png", "howto_btn_p.png",[this](Ref* ref) {
        this->transitonScene(TestPhysicsScene::createScene());
    }));
    this->setBtn2(MenuItemImage::create("howto_btn.png", "howto_btn_p.png",[this](Ref* ref) {
        this->transitonScene(TestScene::createScene());
    }));
    this->setBtn3(MenuItemImage::create("howto_btn.png", "howto_btn_p.png",[this](Ref* ref) {
        NJLOG("Fwheel");
        NJLOG(ST_NODE(_bike->getFwheel()).c_str());
        NJLOG("Rwheel");
        NJLOG(ST_NODE(_bike->getRwheel()).c_str());
        NJLOG("kaku");
        float kaku = this->getCalc()->nomlKaku(_bike->getRwheel()->getPosition(),_bike->getFwheel()->getPosition());
        NJLOG(ST_FLOAT(kaku).c_str());
        _bike->fWheelUp(15);
        _bike->fWheelJump(15);
    }));
    this->setBtn4(MenuItemImage::create("howto_btn.png", "howto_btn_p.png",[this](Ref* ref) {
        _bike->fWheeldown(15);
        
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
                _bike->fWheelTouchPt.set(contact.getContactData()->normal);
        _bike->fWheelTouched = true;
        _bike->rWheelTouchPt.set(contact.getContactData()->points[1]);
        _bike->rWheelTouched = true;
        return true;
    };
    
    _contactlistener->onContactPostSolve = [this](PhysicsContact& contact, const PhysicsContactPostSolve& solve) {
        _bike->fWheelTouchPt.set(contact.getContactData()->normal);
        _bike->fWheelTouched = true;
        
        _bike->rWheelTouchPt.set(contact.getContactData()->points[1]);
        _bike->rWheelTouched = true;
    };
    
    _contactlistener->onContactSeparate = [this](PhysicsContact& contact) {
        _bike->fWheelTouched = false;
        _bike->rWheelTouched = false;
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
