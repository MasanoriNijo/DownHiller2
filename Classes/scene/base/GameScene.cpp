#include "GameScene.h"

GameScene::GameScene():
_backColor(NULL), _ad(NULL), _colorChanger(NULL), _calc(NULL),_gameAnounce(NULL),
_debugLine(NULL), _debugMemo(NULL), _noMoveLayer(NULL),_backGradientColor(NULL)
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
    CC_SAFE_RELEASE_NULL(_gameAnounce);
    CC_SAFE_RELEASE_NULL(_backGradientColor);
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
    winSize = director->getWinSize();
    ctPt.set(winSize.width / 2, winSize.height / 2);
    
    //imovileAdをセットする。
    setAD(ImovileAd::create());
    getAD()->txtFlg = true;
    getAD()->instFlg = true;
    
    // Calclaterをセット
    setCalc(Calclater::create());
    
    // 固定画面をセット
    setNoMoveLayer(ParallaxNode::create());
    addChild(_noMoveLayer,OBJ_LAYER_TOP);
    
#if ENABLE_DEBUG_LINE
    drawDebugLine();
#endif
    
    return true;
}

void GameScene::setBackGroundColor(){
    setBackGroundColor(DEFAULT_COLOR_H,DEFAULT_COLOR_S,DEFAULT_COLOR_V);
}

void GameScene::setBackGradientGroundColor(){
    setBackGradientGroundColor(DEFAULT_COLOR_H,DEFAULT_COLOR_S,DEFAULT_COLOR_V,
                               DEFAULT_GRADIATE_COLOR_H,DEFAULT_GRADIATE_COLOR_S,DEFAULT_GRADIATE_COLOR_V);
}

void GameScene::setBackGroundColor(float h, float s, float v){
    setColorChanger(ColorChanger::create());
    getColorChanger()->SetColor(h, s, v);
    setBackColor(LayerColor::create(getColorChanger()->getColor4B()));
    if(_noMoveLayer){
        _noMoveLayer->addChild(_backColor,(int)OBJ_LAYER_BUTTOM,Vec2::ZERO,_backColor->getPosition());
    }else{
        addChild(_backColor,OBJ_LAYER_BUTTOM);
    }
}

void GameScene::setBackGradientGroundColor(float h, float s, float v, float h2, float s2, float v2){
    setColorChanger(ColorChanger::create());
    getColorChanger()->SetColor(h, s, v);
    Color4B fstColor = getColorChanger()->getColor4B();
    getColorChanger()->SetColor(h2, s2, v2);
    Color4B endColor = getColorChanger()->getColor4B();
    
    setBackGradientColor(LayerGradient::create(fstColor,endColor));
    if(_noMoveLayer){
        _noMoveLayer->addChild(getBackGradientColor(),(int)OBJ_LAYER_BUTTOM,Vec2::ZERO,getBackGradientColor()->getPosition());
    }else{
        addChild(getBackGradientColor(),OBJ_LAYER_BUTTOM);
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
    switch (getGameState()) {
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
    if(tmFlg){
        tm_ += dt;
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
        addChild(sp);
    }
}

void GameScene::mountScroleNode(Node* sp, Vec2 pt, float lvl){
    sp->setPosition(pt);
    sp->setGlobalZOrder(lvl);
    addChild(sp);
}

void GameScene::drawDebugLine(){
    setDebugLine(DrawNode::create());
    getDebugLine()->setLineWidth(4);
    getDebugLine()->drawDot(ctPt, 1, Color4F::GREEN);
    
    int meshSize = 10;
    
    int horCnt = winSize.width / meshSize;
    int verCnt = winSize.height / meshSize;
    
    for (int i = -verCnt-2; i < verCnt + 2; i++) {
        getDebugLine()->drawLine(Vec2(0,ctPt.y + i * meshSize),
                                       Vec2(winSize.width,ctPt.y + i * meshSize),
                                       Color4F::GRAY);
    }
    for (int i = -horCnt-2; i < horCnt + 2; i++) {
        getDebugLine()->drawLine(Vec2(ctPt.x + i * meshSize,0),
                                       Vec2(ctPt.x + i * meshSize,winSize.height),
                                       Color4F::GRAY);
    }
    mountNode(getDebugLine(), Vec2::ZERO, OBJ_LAYER_LV1);
//    setDebugMemo(Label::createWithTTF("Deugメモ", "irohamaru.ttf", 14));
//    mountNode(getDebugMemo(), Vec2(ctPt.x,30), OBJ_LAYER_LV1);
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
        if(getGameAnounce()->getParent()){
            getGameAnounce()->removeFromParentAndCleanup(true);
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
        if(getGameAnounce()->getParent()){
            getGameAnounce()->removeFromParentAndCleanup(true);
        }
    });
    auto endFnc2 = CallFunc::create(endFunc);
    auto seq = Sequence::create(para,stayTime,fadeOut,endFnc,endFnc2, NULL);
    setGameAnounce(Label::createWithTTF(st, "irohamaru.ttf", 24));
    getColorChanger()->SetColor(TITLE_COLOR_H, TITLE_COLOR_S, TITLE_COLOR_V);
    getGameAnounce()->setTextColor(getColorChanger()->getColor4B());
    getColorChanger()->SetColor(TITLE_FUTI_COLOR_H, TITLE_FUTI_COLOR_S, TITLE_FUTI_COLOR_V);
    getGameAnounce()->enableOutline(getColorChanger()->getColor4B(),1);
    getGameAnounce()->setOpacity(0);
    getGameAnounce()->setScale(0);
    getGameAnounce()->runAction(seq);
    mountNode(getGameAnounce(), pt, OBJ_LAYER_TOP);
}


MenuItemSprite* GameScene::generateMenuItemSprite(const ccMenuCallback& callback,Size size,std::string st,
                                                  Color3B color_, Color3B color2_, bool isBlink){
    Button* btn_ = Button::create();
    btn_->setButton(size, st);
    btn_->setColor(color_);
    if(isBlink){
        auto fadeOut = FadeOut::create(1.0);
        auto act = RepeatForever::create(Sequence::create(fadeOut,fadeOut->reverse(), NULL));
        btn_->runAction(act);
    }
    Button* btn2_ = Button::create();
    btn2_->setButton(size, st);
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

void GameScene::startTime(){
    tm_ = 0;
    tmFlg = true;
}

void GameScene::stopTime(){
    tmFlg = false;
}

std::string GameScene::getTime(){
    return ST_FLOAT(tm_);
}
/** パラメータサンプル
 setBackColor(LayerColor::create());
 getBackColor();
 setAD(ImovileAd::create());
 getAD();
 setColorChanger(ColorChanger::create());
 getColorChanger();
 setCalc(Calclater::create());
 getCalc();
 setDebugLine(DrawNode::create());
 getDebugLine();
 setDebugMemo(Label::create());
 getDebugMemo();
 */
