#include "GameScene.h"

GameScene::GameScene():
_backColor(NULL), _ad(NULL), _colorChanger(NULL), _calc(NULL), _debugLine(NULL), _debugMemo(NULL), _noMoveLayer(NULL)
{}

GameScene::~GameScene() {
    NJLOG("hoge:GameScene::~GameScene()");
    CC_SAFE_RELEASE_NULL(_backColor);
    CC_SAFE_RELEASE_NULL(_ad);
    CC_SAFE_RELEASE_NULL(_colorChanger);
    CC_SAFE_RELEASE_NULL(_calc);
    CC_SAFE_RELEASE_NULL(_debugLine);
    CC_SAFE_RELEASE_NULL(_debugMemo);
    CC_SAFE_RELEASE_NULL(_noMoveLayer);
}

Scene* GameScene::createScene() {
    auto scene = Scene::create();
    auto layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}

Scene* GameScene::createPhysicsScene() {
    auto scene = Scene::Scene::createWithPhysics();
    auto world = scene->getPhysicsWorld();
    world->setGravity(GRAVITY_ACCERATION);
    world->setSpeed(PHYSICS_WOELD_SPEED);
#if DEBUG_PHYSICS_MASK
    world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
#endif
    auto layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}

bool GameScene::init() {
    
    if (!Layer::init()) {
        return false;
    }
    
    //画面のサイズをセットする
    auto director = Director::getInstance();
    this->winSize = director->getWinSize();
    this->ctPt.set(winSize.width / 2, winSize.height / 2);
    
    //imovileAdをセットする。
    this->setAD(ImovileAd::create());
    this->getAD()->txtFlg = true;
    this->getAD()->instFlg = true;
    
    // Calclaterをセット
    this->setCalc(Calclater::create());
    
    // 固定画面をセット
    this->setNoMoveLayer(ParallaxNode::create());
    this->addChild(_noMoveLayer,OBJ_LAYER_TOP);
    
    
#if ENABLE_DEBUG_LINE
    this->drawDebugLine();
#endif
    
    return true;
}

void GameScene::setBackGroundColor(){
    this->setBackGroundColor(DEFAULT_COLOR_H,DEFAULT_COLOR_S,DEFAULT_COLOR_V);
}

void GameScene::setBackGroundColor(float h, float s, float v){
    this->setColorChanger(ColorChanger::create());
    this->getColorChanger()->SetColor(h, s, v);
    this->setBackColor(LayerColor::create(this->getColorChanger()->getColor4B()));
    if(_noMoveLayer){
        _noMoveLayer->addChild(this->_backColor,(int)OBJ_LAYER_BUTTOM,Vec2::ZERO,this->_backColor->getPosition());
    }else{
        this->addChild(this->_backColor,OBJ_LAYER_BUTTOM);
    }
}

void GameScene::onEnterTransitionDidFinish() {
    Layer::onEnterTransitionDidFinish();
    // todo
}

void GameScene::onExit(){
    Layer::onExit();
}


void GameScene::update(float dt) {
    switch (this->getGameState()) {
        case GameState::READY: {
            // todo
            break;
        }
        case GameState::PLAY: {
            // todo
            break;
        }
        case GameState::CLEAR: {
            // todo
            break;
        }
        case GameState::MISS: {
            // todo
            break;
        }
    }
}

void GameScene::transitonScene(Scene* scene){
    NJLOG("GameScene:Count3");
    NJLOG(ST_INT(this->getReferenceCount()).c_str());
//    this->release();
    NJLOG(ST_INT(this->getReferenceCount()).c_str());
    auto transition_ = CallFuncN::create([scene](Node* node_) {
        auto transition=TransitionCrossFade::create(0.5,scene);
        Director::getInstance()->replaceScene(transition);
    });
    this->runAction(transition_);
    //    this->getColorChanger()->transitonScene(this, scene);
}

void GameScene::mountNode(Node* sp, Vec2 pt, float lvl){
    sp->setPosition(pt);
    sp->setGlobalZOrder(lvl);
    if(_noMoveLayer){
        _noMoveLayer->addChild(sp,(int)lvl, Vec2::ZERO,sp->getPosition());
    }else{
        this->addChild(sp);
    }
}

void GameScene::mountScroleNode(Node* sp, Vec2 pt, float lvl){
    sp->setPosition(pt);
    sp->setGlobalZOrder(lvl);
    this->addChild(sp);
}

void GameScene::drawDebugLine(){
    this->setDebugLine(DrawNode::create());
    this->getDebugLine()->setLineWidth(4);
    this->getDebugLine()->drawDot(this->ctPt, 1, Color4F::GREEN);
    
    int meshSize = 10;
    
    int horCnt = this->winSize.width / meshSize;
    int verCnt = this->winSize.height / meshSize;
    
    for (int i = -verCnt-2; i < verCnt + 2; i++) {
        this->getDebugLine()->drawLine(Vec2(0,this->ctPt.y + i * meshSize),
                                       Vec2(this->winSize.width,this->ctPt.y + i * meshSize),
                                       Color4F::GRAY);
    }
    for (int i = -horCnt-2; i < horCnt + 2; i++) {
        this->getDebugLine()->drawLine(Vec2(this->ctPt.x + i * meshSize,0),
                                       Vec2(this->ctPt.x + i * meshSize,this->winSize.height),
                                       Color4F::GRAY);
    }
    this->mountNode(this->getDebugLine(), Vec2::ZERO, OBJ_LAYER_LV1);
    this->setDebugMemo(Label::createWithTTF("Deugメモ", "irohamaru.ttf", 14));
    this->mountNode(this->getDebugMemo(), Vec2(this->ctPt.x,30), OBJ_LAYER_LV1);
    
}

float GameScene::getScreenWidth() {
    return Director::getInstance()->getOpenGLView()->getFrameSize().width;
}

float GameScene::getScreenHeight() {
    return Director::getInstance()->getOpenGLView()->getFrameSize().height;
}

float GameScene::getDesignWidth() {
    return Director::getInstance()->getOpenGLView()->getDesignResolutionSize().width;
}

float GameScene::getDesignHeight() {
    return Director::getInstance()->getOpenGLView()->getDesignResolutionSize().height;
}

/** パラメータサンプル
 this->setBackColor(LayerColor::create());
 this->getBackColor();
 this->setAD(ImovileAd::create());
 this->getAD();
 this->setColorChanger(ColorChanger::create());
 this->getColorChanger();
 this->setCalc(Calclater::create());
 this->getCalc();
 this->setDebugLine(DrawNode::create());
 this->getDebugLine();
 this->setDebugMemo(Label::create());
 this->getDebugMemo();
 */
