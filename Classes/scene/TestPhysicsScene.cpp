#include "TestPhysicsScene.h"

#include "scene/TitleScene.h"
#include "scene/TestScene.h"
#include "scene/TestPhysicsScene.h"
#include "scene/HelloWorldScene.h"

TestPhysicsScene::TestPhysicsScene():
_gameTitle(NULL), _baseLine(NULL), _ball(NULL), _btn1(NULL), _btn2(NULL), _btn3(NULL), _btn4(NULL), _menu(NULL),_touch(NULL),_bike(NULL)
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
    points[0].x = -winSize.width/2+20;
    points[0].y = 20;
    points[1].x = -winSize.width/2+80;
    points[1].y = -50;
    points[2].x = winSize.width/2-20;
    points[2].y = -50;
    points[3].x = winSize.width/2-20;
    points[3].y = -20;
    this->getBaseLine()->drawPoly(points, 4, false, Color4F::GREEN);
    this->getBaseLine()->setPhysicsBody(PhysicsBody::createEdgePolygon(points, 4));
    this->getBaseLine()->getPhysicsBody()->setDynamic(false);
    this->mountNode(this->getBaseLine(), ctPt, OBJ_LAYER_LV1);
        
    this->setBtn1(MenuItemImage::create("howto_btn.png", "howto_btn_p.png",[this](Ref* ref) {
        this->transitonScene(TestPhysicsScene::createScene());
    }));
    this->setBtn2(MenuItemImage::create("howto_btn.png", "howto_btn_p.png",[this](Ref* ref) {
        this->transitonScene(TestScene::createScene());
    }));
    this->setBtn3(MenuItemImage::create("howto_btn.png", "howto_btn_p.png",[this](Ref* ref) {
        this->getBike()->setRotation(30);
    }));
    this->setBtn4(MenuItemImage::create("howto_btn.png", "howto_btn_p.png",[this](Ref* ref) {
        this->getBike()->setRotation(-30);

    }));
    this->setMenu(Menu::create(this->getBtn1(),this->getBtn2(),this->getBtn3(),this->getBtn4(),NULL));
    this->getMenu()->alignItemsHorizontallyWithPadding(20);
    this->mountNode(this->getMenu(), this->ctPt+Vec2(0,-100), OBJ_LAYER_TOP);
    
    return true;
}

void TestPhysicsScene::onEnterTransitionDidFinish() {
    // Bikeをセットする。
    this->setBike(Bike::create());
    this->getBike()->setBikeState(Bike::BikeState::NOML);
    this->mountNode(this->getBike(), this->ctPt+Vec2(0,30), OBJ_LAYER_TOP);
    this->mountNode(this->getBike()->getFwheel(), this->getBike()->getPosition() + Vec2(this->getBike()->wheelBase,0), OBJ_LAYER_TOP);
    this->mountNode(this->getBike()->getRwheel(), this->getBike()->getPosition(), OBJ_LAYER_TOP);
    this->getBike()->SetJoint();
    this->getScene()->getPhysicsWorld()->addJoint(this->getBike()->getFRJoint());
    this->getBike()->scheduleUpdate();
    
    this->setTouch(TouchEventHelper::create());
    this->getTouch()->getTouchListenner()->onTouchBegan = [this](Touch* touch,Event* event) {
        this->points[0].set(touch->getLocation()-this->getBaseLine()->getPosition());
        this->getDebugMemo()->setString("onTouchBegan:" + ST_VEC2(this->points[0]));
        pt1.set(touch->getLocation());
        pt2.set(touch->getLocation());
        this->_bike->touchOn(pt1);
        return true;
    };
    this->getTouch()->getTouchListenner()->onTouchMoved = [this](Touch* touch,Event* event) {
        this->points[0].set(touch->getLocation()-this->getBaseLine()->getPosition());
        this->getDebugMemo()->setString("onTouchTouchMoved:" + ST_VEC2(this->points[0]));
        this->getBaseLine()->removeFromParent();
        this->setBaseLine(DrawNode::create());
        this->getBaseLine()->drawPoly(this->points, 4, false, Color4F::GREEN);
        this->getBaseLine()->setPhysicsBody(PhysicsBody::createEdgePolygon(this->points, 4));
        this->getBaseLine()->getPhysicsBody()->setDynamic(false);
        this->mountNode(this->getBaseLine(), ctPt, OBJ_LAYER_LV1);
        pt2.set(touch->getLocation());
        this->_bike->swaip(pt2);
        return true;
    };
    this->getTouch()->getTouchListenner()->onTouchEnded = [this](Touch* touch,Event* event) {
        this->points[0].set(touch->getLocation());
        this->getDebugMemo()->setString("onTouchEnded:" + ST_VEC2(this->points[0]));
        pt1.set(Vec2::ZERO);
        pt2.set(Vec2::ZERO);
        this->_bike->touchOff(Vec2::ZERO);
        return true;
    };
    
    this->getTouch()->applyTouchListenner(this->getBike());
    
    this->scheduleUpdate();
}

void TestPhysicsScene::update(float dt) {
    // todo
    if(this->getBike()){
//        this->getDebugMemo()->setString("重心位置:" + ST_VEC2(this->getBike()->weightPt));
//        this->getDebugMemo()->setString("bike:" + ST_VEC2(this->getBike()->getPosition()) + " " + ST_INT(this->getBike()->getRotation()));
        this->getDebugMemo()->setString("bike:" + ST_VEC2(this->getCalc()->getParentNodePosition(_bike->getRwheel())));
    }
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
