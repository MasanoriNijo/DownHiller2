#include "GameScene.h"

GameScene::GameScene():
_backColor(NULL), _colorChanger(NULL), _calc(NULL),_gameAnounce(NULL),
_debugLine(NULL), _debugMemo(NULL), _noMoveLayer(NULL)
{}

GameScene::~GameScene() {
    NJLOG("hoge:GameScene::~GameScene()");
    CC_SAFE_RELEASE_NULL(_backColor);
//    CC_SAFE_RELEASE_NULL(_ad);
    CC_SAFE_RELEASE_NULL(_colorChanger);
    CC_SAFE_RELEASE_NULL(_calc);
    CC_SAFE_RELEASE_NULL(_debugLine);
    CC_SAFE_RELEASE_NULL(_debugMemo);
    CC_SAFE_RELEASE_NULL(_noMoveLayer);
    CC_SAFE_RELEASE_NULL(_gameAnounce);
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
//    this->setAD(ImovileAd::create());
//    this->getAD()->txtFlg = true;
//    this->getAD()->instFlg = true;
    
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
    //    auto moveBy_ = MoveBy::create(0.5, Vec2(-ctPt.x,0));
    //    auto transition_ = CallFuncN::create([scene](Node* node_) {
    //        auto transition=TransitionSlideInL::create(2.0,scene);
    //        auto transition=TransitionCrossFade::create(0.5,scene);
    //        auto transition=TransitionShrinkGrow::create(0.5,scene);
    auto transition=TransitionFade::create(0.5,scene);
    Director::getInstance()->replaceScene(transition);
    
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
//    this->setDebugMemo(Label::createWithTTF("Deugメモ", "irohamaru.ttf", 14));
//    this->mountNode(this->getDebugMemo(), Vec2(this->ctPt.x,30), OBJ_LAYER_LV1);
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

void GameScene::showGameAnnounce(std::string st,Vec2 pt){
    
    auto fadeIn = FadeIn::create(0.5f);
    auto scaleIn = EaseElasticOut::create(ScaleTo::create(0.5, 1));
    auto para = Spawn::create(fadeIn,scaleIn, NULL);
    auto stayTime = DelayTime::create(1.0f);
    auto fadeOut = FadeOut::create(0.2f);
    auto endFnc = CallFunc::create([this](){
        if(this->getGameAnounce()->getParent()){
            this->getGameAnounce()->removeFromParentAndCleanup(true);
        }
    });
    auto seq = Sequence::create(para,stayTime,fadeOut,endFnc, NULL);
    setGameAnounce(Label::createWithTTF(st, "irohamaru.ttf", 24));
    getGameAnounce()->setTextColor(Color4B::BLACK);
    getGameAnounce()->enableOutline(Color4B::WHITE,1);
    getGameAnounce()->setOpacity(0);
    getGameAnounce()->setScale(0);
    getGameAnounce()->runAction(seq);
    mountNode(getGameAnounce(), pt, OBJ_LAYER_TOP);
}


void GameScene::showGameAnnounce(std::string st,Vec2 pt, const std::function<void()> &endFunc){
    auto fadeIn = FadeIn::create(0.5f);
    auto scaleIn = EaseElasticOut::create(ScaleTo::create(0.5, 1));
    auto para = Spawn::create(fadeIn,scaleIn, NULL);
    auto stayTime = DelayTime::create(1.0f);
    auto fadeOut = FadeOut::create(0.2f);
    auto endFnc = CallFunc::create([this](){
        if(this->getGameAnounce()->getParent()){
            this->getGameAnounce()->removeFromParentAndCleanup(true);
        }
    });
    auto endFnc2 = CallFunc::create(endFunc);
    auto seq = Sequence::create(para,stayTime,fadeOut,endFnc,endFnc2, NULL);
    setGameAnounce(Label::createWithTTF(st, "irohamaru.ttf", 24));
    getGameAnounce()->setTextColor(Color4B::BLACK);
    getGameAnounce()->enableOutline(Color4B::WHITE,1);
    getGameAnounce()->setOpacity(0);
    getGameAnounce()->setScale(0);
    getGameAnounce()->runAction(seq);
    mountNode(getGameAnounce(), pt, OBJ_LAYER_TOP);
}


MenuItemSprite* GameScene::generateMenuItemSprite(const ccMenuCallback& callback,Size size,std::string st,
                                                  Color3B color_, Color3B color2_, bool isBlink){
    Button* btn_ = Button::create();
    btn_->setButton(Size(1,1), st);
    btn_->setColor(color_);
    if(isBlink){
        auto fadeOut = FadeOut::create(0.5);
        auto act = RepeatForever::create(Sequence::create(fadeOut,fadeOut->reverse(), NULL));
        btn_->runAction(act);
    }
    Button* btn2_ = Button::create();
    btn2_->setButton(Size(1,1), st);
    btn2_->setButtonColor(color2_);
    return  MenuItemSprite::create(btn_, btn2_,callback);
}

void GameScene::setBGM(const char* filePath){
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(filePath);
}

void GameScene::startBGM(const char* filePath){
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(filePath, true);
}

void GameScene::stopBGM(const char* filePath){
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}

void GameScene::setSoundEffect(const char* filePath){
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(filePath);
}

void GameScene::callSoundEffect(const char* filePath){
    // play a sound effect, just once.
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    audio->playEffect(filePath, false, 1.0f, 1.0f, 1.0f);
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
