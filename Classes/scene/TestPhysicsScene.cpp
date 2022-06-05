#include "TestPhysicsScene.h"

#include "scene/TitleScene.h"
#include "scene/TestScene.h"
#include "scene/TestPhysicsScene.h"
#include "scene/HelloWorldScene.h"

TestPhysicsScene::TestPhysicsScene():
_gameTitle(NULL), _baseLine(NULL), _ball(NULL), _btn1(NULL), _btn2(NULL), _btn3(NULL), _btn4(NULL), _menu(NULL)
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
    
    //    this->setGameTitle(Label::create());
    //    this->getGameTitle();
    this->setBaseLine(DrawNode::create());
    this->getBaseLine()->setColor(Color3B::WHITE);
    this->getBaseLine()->setLineWidth(11);
    points[0].x = -winSize.width/2+20;
    points[0].y = 20;
    points[1].x = -winSize.width/2+80;
    points[1].y = 50;
    points[2].x = winSize.width/2-20;
    points[2].y = 50;
    points[3].x = winSize.width/2-20;
    points[3].y = -20;
    this->getBaseLine()->drawPoly(points, 4, false, Color4F::GREEN);
    this->getBaseLine()->setPhysicsBody(PhysicsBody::createEdgePolygon(points, 4));
    this->getBaseLine()->getPhysicsBody()->setDynamic(false);
    this->mountNode(this->getBaseLine(), ctPt, OBJ_LAYER_LV1);
    
    int ballRad = 14;
    this->setBall(DrawNode::create());
    this->getBall()->drawDot(Vec2::ZERO, ballRad-4, Color4F::WHITE);
    this->getBall()->setPhysicsBody(PhysicsBody::createCircle(ballRad));
    this->mountNode(this->getBall(),Vec2(120,220), OBJ_LAYER_LV1);
    
    this->setBtn1(MenuItemImage::create("howto_btn.png", "howto_btn_p.png",[this](Ref* ref) {
        this->transitonScene(TestPhysicsScene::createScene());
    }));
    
    this->setBtn2(MenuItemImage::create("howto_btn.png", "howto_btn_p.png",[this](Ref* ref) {
        this->transitonScene(TestScene::createScene());
    }));
    this->setBtn3(MenuItemImage::create("howto_btn.png", "howto_btn_p.png",[this](Ref* ref) {
        points[1].y += 5;
        this->getBaseLine()->removeFromParent();
        this->setBaseLine(DrawNode::create());
        this->getBaseLine()->drawPoly(this->points, 4, false, Color4F::GREEN);
        this->getBaseLine()->setPhysicsBody(PhysicsBody::createEdgePolygon(this->points, 4));
        this->getBaseLine()->getPhysicsBody()->setDynamic(false);
        this->mountNode(this->getBaseLine(), ctPt, OBJ_LAYER_LV1);
    }));
    this->setBtn4(MenuItemImage::create("howto_btn.png", "howto_btn_p.png",[this](Ref* ref) {
        points[1].y -= 5;
        this->getBaseLine()->removeFromParent();
        this->setBaseLine(DrawNode::create());
        this->getBaseLine()->drawPoly(this->points, 4, false, Color4F::GREEN);
        this->getBaseLine()->setPhysicsBody(PhysicsBody::createEdgePolygon(this->points, 4));
        this->getBaseLine()->getPhysicsBody()->setDynamic(false);
        this->mountNode(this->getBaseLine(), ctPt, OBJ_LAYER_LV1);
    }));
    this->setMenu(Menu::create(this->getBtn1(),this->getBtn2(),this->getBtn3(),this->getBtn4(),NULL));
    this->getMenu()->alignItemsHorizontallyWithPadding(20);
    this->mountNode(this->getMenu(), this->ctPt + Vec2(0,-80), OBJ_LAYER_TOP);
    
    return true;
}

void TestPhysicsScene::onEnterTransitionDidFinish() {
    // todo
    this->scheduleUpdate();
}

void TestPhysicsScene::update(float dt) {
    // todo
    this->getDebugMemo()->setString("ボール位置:" + ST_VEC2(this->getBall()->getPosition()));
    
}

/** パラメータサンプル
 this->setGameTitle(Label::create());
 this->getGameTitle();
 this->setBaseLine(DrawNode::create());
 this->getBaseLine();
 this->setBall(DrawNode::create());
 this->getBall();
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
