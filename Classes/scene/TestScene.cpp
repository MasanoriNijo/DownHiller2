#include "TestScene.h"

#include "scene/TitleScene.h"
#include "scene/TestPhysicsScene.h"

TestScene::TestScene():
_gameTitle(NULL), _baseLine(NULL), _ball(NULL), _btn1(NULL), _btn2(NULL), _btn3(NULL), _btn4(NULL), _menu(NULL), _touch(NULL), _pt1(NULL), _pt2(NULL), _pt3(NULL), _pt4(NULL), _pt5(NULL), _touchObj(NULL), _lineMaker(NULL),_stLine(NULL),_cvLine(NULL),_courceMaker(NULL),_scrollNode(NULL)
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
    CC_SAFE_RELEASE_NULL(_lineMaker);
    CC_SAFE_RELEASE_NULL(_stLine);
    CC_SAFE_RELEASE_NULL(_cvLine);
    CC_SAFE_RELEASE_NULL(_courceMaker);
    CC_SAFE_RELEASE_NULL(_scrollNode);
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
    
    setBackGroundColor();
    
    setScrollNode(ScrollNode::create());
    getScrollNode()->setTouchEvent();
    mountNode(getScrollNode(), Vec2::ZERO, OBJ_LAYER_TOP);
    
    setGameTitle(Label::createWithTTF("激走！坂チャリ", "irohamaru.ttf", 24));
    getGameTitle()->setTextColor(Color4B::BLACK);
    getGameTitle()->enableOutline(Color4B::WHITE,1);
    getGameTitle()->setGlobalZOrder(OBJ_LAYER_TOP);
    getGameTitle()->setPosition(ctPt);
    getScrollNode()->addChild(getGameTitle());
//    mountNode(getGameTitle(),  ctPt + Vec2(0,120), OBJ_LAYER_TOP);
    
    setBtn1(MenuItemImage::create("howto_btn.png", "howto_btn_p.png",[this](Ref* ref) {
        transitonScene(TitleScene::createScene());
    }));
    setBtn2(MenuItemImage::create("howto_btn.png", "howto_btn_p.png",[this](Ref* ref) {
        transitonScene(TestPhysicsScene::createScene());
    }));
    setBtn3(MenuItemImage::create("howto_btn.png", "howto_btn_p.png",[this](Ref* ref) {
        showGameAnnounce("ゲームスタート！", ctPt);
    }));
    setBtn4(MenuItemImage::create("howto_btn.png", "howto_btn_p.png",[this](Ref* ref) {
        showGameAnnounce("ベストタイム！", ctPt);
    }));
    setMenu(Menu::create(getBtn1(),getBtn2(),getBtn3(),getBtn4(),NULL));
    getMenu()->alignItemsHorizontallyWithPadding(20);
    getMenu()->setPosition(ctPt + Vec2(0,-100));
    getScrollNode()->addChild(getMenu());
//    mountNode(getMenu(), ctPt + Vec2(0,-100), OBJ_LAYER_TOP);
    
    Vec2 achPt_ = Vec2(0.15,0.5);
    setPt1(Sprite2::create("yazi.png"));
    _pt1->setName("pt1");
    _pt1->setDefaultTouchEvent();
    _pt1->setAnchorPoint(achPt_);
    mountScroleNode(getPt1(), ctPt + Vec2(-80,-40) , OBJ_LAYER_TOP);
    
    setPt2(Sprite2::create("yazi2.png"));
    _pt2->setName("pt2");
    _pt2->setDefaultTouchEvent();
    _pt2->setAnchorPoint(achPt_);
    mountScroleNode(getPt2(), ctPt + Vec2(-30,-40) , OBJ_LAYER_TOP);
    
    setPt3(Sprite2::create("dot.png"));
    _pt3->setName("pt3");
    _pt3->setDefaultTouchEvent();
    _pt3->setAnchorPoint(achPt_);
    mountScroleNode(getPt3(), ctPt + Vec2(30,-40) , OBJ_LAYER_TOP);
    
    setPt4(Sprite2::create("dot2.png"));
    _pt4->setName("pt4");
    _pt4->setDefaultTouchEvent();
    _pt4->setAnchorPoint(achPt_);
    mountScroleNode(getPt4(), ctPt + Vec2(80,-40) , OBJ_LAYER_TOP);
    
    setPt5(Sprite2::create("dot3.png"));
    _pt5->setName("pt5");
    _pt5->setDefaultTouchEvent();
    mountScroleNode(getPt5(), ctPt + Vec2(0,80) , OBJ_LAYER_TOP);
    
    setStLine(StraightLine::create());
    _stLine->setGlobalZOrder(OBJ_LAYER_TOP);
    _stLine->setDefaultTouchEvent();
    addChild(_stLine);
    
    setCvLine(CurveLine::create());
    _cvLine->setGlobalZOrder(OBJ_LAYER_TOP);
    _cvLine->setDefaultTouchEvent();
    addChild(_cvLine);
    
    setCourceMaker(CourceMaker::create());
//    _courceMaker->setGlobalZOrder(OBJ_LAYER_TOP);
    addChild(getCourceMaker());
    
    setTouch(TouchEventHelper::create());
    getTouch()->getTouchListenner()->onTouchBegan = [this](Touch* touch,Event* event) {
        auto target = (Sprite*)event->getCurrentTarget();
        setTouchObj(event->getCurrentTarget());
        getDebugMemo()->setString(_touchObj->getName()
                                        + ":" + ST_VEC2(_touchObj->getPosition())+ " "
                                        + ST_FLOAT(_touchObj->getRotation()));
        return true;
    };
    getTouch()->getTouchListenner()->onTouchMoved = [this](Touch* touch,Event* event) {
        getDebugMemo()->setString(_touchObj->getName()
                                        + ":" + ST_VEC2(_touchObj->getPosition())+ " "
                                        + ST_FLOAT(_touchObj->getRotation()));
        return true;
    };
    getTouch()->getTouchListenner()->onTouchEnded = [this](Touch* touch,Event* event) {
        getDebugMemo()->setString(_touchObj->getName()
                                        + ":" + ST_VEC2(_touchObj->getPosition())+ " "
                                        + ST_FLOAT(_touchObj->getRotation()));
        return true;
    };
    //    getTouch()->applyTouchListenner(this);
    
    setLineMaker(LineMaker::create());
    _lineMaker->setPt(Sprite2::create("dot2.png"));
    _lineMaker->setField(this);
    
    return true;
}

void TestScene::onEnterTransitionDidFinish() {
    GameScene::onEnterTransitionDidFinish();
    scheduleUpdate();
    setTouchObj(_pt5);
    // todo
}

void TestScene::update(float dt) {
    if(getDebugMemo()){
        getDebugMemo()->setString(_touchObj->getName() + ":" + ST_NODE(_touchObj));
    }
}
/** パラメータサンプル
 setGameTitle(Label::create());
 getGameTitle();
 setBaseLine(DrawNode::create());
 getBaseLine();
 setBall(DrawNode::create());
 getBall();
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
 setTouch(TouchEventHelper::create());
 getTouch();
 setPt1(Sprite2::create());
 getPt1();
 setPt2(Sprite2::create());
 getPt2();
 setPt3(Sprite2::create());
 getPt3();
 setPt4(Sprite2::create());
 getPt4();
 setPt5(Sprite2::create());
 getPt5();
 */
