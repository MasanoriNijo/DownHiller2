#include "TestScene.h"

#include "scene/TitleScene.h"
#include "scene/TestScene.h"
#include "scene/TestPhysicsScene.h"

TestScene::TestScene():
_gameTitle(NULL), _baseLine(NULL), _ball(NULL), _btn1(NULL), _btn2(NULL), _btn3(NULL), _btn4(NULL), _menu(NULL)
{}

TestScene::~TestScene() {
    CC_SAFE_RELEASE_NULL(_gameTitle);
    CC_SAFE_RELEASE_NULL(_baseLine);
    CC_SAFE_RELEASE_NULL(_ball);
    CC_SAFE_RELEASE_NULL(_btn1);
    CC_SAFE_RELEASE_NULL(_btn2);
    CC_SAFE_RELEASE_NULL(_btn3);
    CC_SAFE_RELEASE_NULL(_btn4);
    CC_SAFE_RELEASE_NULL(_menu);
}

Scene* TestScene::createScene() {
    auto scene = Scene::create();
    auto layer = TestScene::create();
    scene->addChild(layer);
    return scene;
}

bool TestScene::init() {
    if (!GameScene::init()) {
        return false;
    }
    
    this->setGameTitle(Label::createWithTTF("鬼舞辻無惨", "irohamaru.ttf", 24));
    this->mountNode(this->getGameTitle(), ctPt, OBJ_LAYER_TOP);
    //    this->setBaseLine(DrawNode::create());
    //    this->getBaseLine()->setColor(Color3B::WHITE);
    //    this->getBaseLine()->setLineWidth(11);
    //    Vec2 xx[] = {Vec2(-winSize.width/2,20),Vec2(winSize.width/2,-20)};
    //    //    this->getBaseLine()->drawLine(Vec2(-winSize.width/2,20),Vec2(winSize.width/2,-20),Color4F::GREEN);
    //    this->getBaseLine()->drawPoly(xx, 2, false, Color4F::GREEN);
    //
    ////    this->getBaseLine()->setPhysicsBody(PhysicsBody::createPolygon(xx, 2));
    ////    this->getBaseLine()->getPhysicsBody()->setDynamic(false);
    //    this->mountNode(this->getBaseLine(), ctPt, OBJ_LAYER_LV1);
    //
    //    int ballRad = 14;
    //    this->setBall(DrawNode::create());
    //    this->getBall()->drawDot(Vec2::ZERO, ballRad-4, Color4F::WHITE);
    ////    this->getBall()->setPhysicsBody(PhysicsBody::createCircle(ballRad));
    //    this->mountNode(this->getBall(),Vec2(240,220), OBJ_LAYER_LV1);
    
    this->getDebugMemo()->setString("画面中央は" + ST_VEC2(this->ctPt));
    this->setBtn1(MenuItemImage::create("howto_btn.png", "howto_btn_p.png",[this](Ref* ref) {
        this->transitonScene(TitleScene::createScene());
    }));
    
    this->setBtn2(MenuItemImage::create("howto_btn.png", "howto_btn_p.png",[this](Ref* ref) {
        this->transitonScene(TestPhysicsScene::createScene());
    }));
    this->setBtn3(MenuItemImage::create("howto_btn.png", "howto_btn_p.png",[this](Ref* ref) {
        this->transitonScene(TestScene::createScene());
    }));
    this->setBtn4(MenuItemImage::create("howto_btn.png", "howto_btn_p.png",[this](Ref* ref) {
        this->transitonScene(TestScene::createScene());
    }));
    this->setMenu(Menu::create(this->getBtn1(),this->getBtn2(),this->getBtn3(),this->getBtn4(),NULL));
    this->getMenu()->alignItemsHorizontallyWithPadding(20);
    this->mountNode(this->getMenu(), this->ctPt + Vec2(0,-80), OBJ_LAYER_TOP);
    
    return true;
}

void TestScene::onEnterTransitionDidFinish() {
    // todo
}

void TestScene::update(float dt) {
    // todo
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
