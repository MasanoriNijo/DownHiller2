#include "TestScene.h"

#include "scene/TitleScene.h"
#include "scene/TestPhysicsScene.h"

TestScene::TestScene():
_gameTitle(NULL), _baseLine(NULL), _ball(NULL), _btn1(NULL), _btn2(NULL), _btn3(NULL), _btn4(NULL), _menu(NULL), _touch(NULL), _pt1(NULL), _pt2(NULL), _pt3(NULL), _pt4(NULL), _pt5(NULL), _touchObj(NULL)
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
    CC_SAFE_RELEASE_NULL(_touch);
    CC_SAFE_RELEASE_NULL(_pt1);
    CC_SAFE_RELEASE_NULL(_pt2);
    CC_SAFE_RELEASE_NULL(_pt3);
    CC_SAFE_RELEASE_NULL(_pt4);
    CC_SAFE_RELEASE_NULL(_pt5);
    CC_SAFE_RELEASE_NULL(_touchObj);
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
    this->mountNode(this->getGameTitle(),  this->ctPt + Vec2(0,100), OBJ_LAYER_TOP);
    
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
        _pt2->setPosition(this->getCalc()->cordinaneX(_pt1->getPosition()-ctPt, _pt2->getPosition()-ctPt)+ctPt);
        _pt1->setPosition(Vec2((_pt1->getPosition()-ctPt).length(),0)+ctPt);
    }));
    this->setMenu(Menu::create(this->getBtn1(),this->getBtn2(),this->getBtn3(),this->getBtn4(),NULL));
    this->getMenu()->alignItemsHorizontallyWithPadding(20);
    this->mountNode(this->getMenu(), this->ctPt + Vec2(0,-100), OBJ_LAYER_TOP);
    
    this->setPt1(Sprite2::create("yazi.png"));
    _pt1->setName("pt1");
    _pt1->setDefaultTouchEvent();
    this->mountNode(this->getPt1(), this->ctPt + Vec2(-80,-40) , OBJ_LAYER_TOP);
    
    this->setPt2(Sprite2::create("yazi.png"));
    _pt2->setName("pt2");
    _pt2->setDefaultTouchEvent();
    this->mountNode(this->getPt2(), this->ctPt + Vec2(-30,-40) , OBJ_LAYER_TOP);
    
    this->setPt3(Sprite2::create("yazi.png"));
    _pt3->setName("pt3");
    _pt3->setDefaultTouchEvent();
    this->mountNode(this->getPt3(), this->ctPt + Vec2(30,-40) , OBJ_LAYER_TOP);
    
    this->setPt4(Sprite2::create("yazi.png"));
    _pt4->setName("pt4");
    _pt4->setDefaultTouchEvent();
    this->mountNode(this->getPt4(), this->ctPt + Vec2(80,-40) , OBJ_LAYER_TOP);
    
    this->setPt5(Sprite2::create("HelloWorld.png"));
    _pt5->setName("pt5");
    _pt5->setDefaultTouchEvent();
    this->mountNode(this->getPt5(), this->ctPt + Vec2(0,80) , OBJ_LAYER_TOP);
    
    this->setTouch(TouchEventHelper::create());
    this->getTouch()->getTouchListenner()->onTouchBegan = [this](Touch* touch,Event* event) {
        auto target = (Sprite*)event->getCurrentTarget();
        this->setTouchObj(event->getCurrentTarget());
        this->getDebugMemo()->setString(_touchObj->getName()
                                        + ":" + ST_VEC2(_touchObj->getPosition())+ " "
                                        + ST_FLOAT(_touchObj->getRotation()));
        return true;
    };
    this->getTouch()->getTouchListenner()->onTouchMoved = [this](Touch* touch,Event* event) {
        this->getDebugMemo()->setString(_touchObj->getName()
                                        + ":" + ST_VEC2(_touchObj->getPosition())+ " "
                                        + ST_FLOAT(_touchObj->getRotation()));
        return true;
    };
    this->getTouch()->getTouchListenner()->onTouchEnded = [this](Touch* touch,Event* event) {
        this->getDebugMemo()->setString(_touchObj->getName()
                                        + ":" + ST_VEC2(_touchObj->getPosition())+ " "
                                        + ST_FLOAT(_touchObj->getRotation()));
        return true;
    };
    
    //    this->getTouch()->applyTouchListenner(this);
    
    
    return true;
}

void TestScene::onEnterTransitionDidFinish() {
    
    this->scheduleUpdate();
    this->setTouchObj(_pt5);
    // todo
}

void TestScene::update(float dt) {
    // todo
    this->getDebugMemo()->setString(_touchObj->getName() + ":" + ST_NODE(_touchObj));
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
 this->setTouch(TouchEventHelper::create());
 this->getTouch();
 this->setPt1(Sprite2::create());
 this->getPt1();
 this->setPt2(Sprite2::create());
 this->getPt2();
 this->setPt3(Sprite2::create());
 this->getPt3();
 this->setPt4(Sprite2::create());
 this->getPt4();
 this->setPt5(Sprite2::create());
 this->getPt5();
 */
