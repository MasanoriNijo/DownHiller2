#include "GameStage.h"

#include "scene/TitleScene.h"
#include "scene/TestScene.h"
#include "scene/TestPhysicsScene.h"
#include "scene/HelloWorldScene.h"

GameStage::GameStage():
_gameTitle(NULL), _btn1(NULL), _btn2(NULL), _btn3(NULL), _btn4(NULL), _menu(NULL),_touch(NULL),_bike(NULL),
_contactlistener(NULL), _courceMaker(NULL),_courceManager(NULL),_modal(NULL),_modalMenu(NULL),
_yubi(NULL),_setumei(NULL)
{}

GameStage::~GameStage() {
    NJLOG("hoge:GameStage::~GameStage()");
    CC_SAFE_RELEASE_NULL(_gameTitle);
    CC_SAFE_RELEASE_NULL(_btn1);
    CC_SAFE_RELEASE_NULL(_btn2);
    CC_SAFE_RELEASE_NULL(_btn3);
    CC_SAFE_RELEASE_NULL(_btn4);
    CC_SAFE_RELEASE_NULL(_menu);
    CC_SAFE_RELEASE_NULL(_touch);
    CC_SAFE_RELEASE_NULL(_bike);
    CC_SAFE_RELEASE_NULL(_contactlistener);
    CC_SAFE_RELEASE_NULL(_courceMaker);
    CC_SAFE_RELEASE_NULL(_courceManager);
    CC_SAFE_RELEASE_NULL(_modal);
    CC_SAFE_RELEASE_NULL(_modalMenu);
    CC_SAFE_RELEASE_NULL(_yubi);
    CC_SAFE_RELEASE_NULL(_setumei);
}

Scene* GameStage::createScene() {
    auto scene = Scene::Scene::createWithPhysics();
    auto world = scene->getPhysicsWorld();
    world->setGravity(GRAVITY_ACCERATION);
    world->setSpeed(PHYSICS_WOELD_SPEED);
#if DEBUG_PHYSICS_MASK
    world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
#endif
    auto layer = GameStage::create();
    scene->addChild(layer);
    return scene;
}

bool GameStage::init() {
    if (!GameScene::init()) {
        return false;
    }
    setSoundEffect("btnon.mp");
    setBackGroundColor();
    setPosition(ctPt + Vec2(250,0));

    this->setDebugMemo(Label::createWithTTF("Deugメモ", "irohamaru.ttf", 8));
    this->mountNode(this->getDebugMemo(), Vec2(this->ctPt.x,30), OBJ_LAYER_LV1);
    
    // modal画面を作成する。
    setBtn2(generateMenuItemSprite([this](Ref* ref){
        transitonScene(GameStage::createScene());
    }, Size(1,1), L_BTN_RETRY, Color3B::WHITE, Color3B::YELLOW, false));
    setBtn3(generateMenuItemSprite([this](Ref* ref){
        transitonScene(GameStage::createScene());
    }, Size(1,1), L_BTN_NEXT, Color3B::WHITE, Color3B::YELLOW, false));
    setBtn4(generateMenuItemSprite([this](Ref* ref){
        transitonScene(TitleScene::createScene());
    }, Size(1,1), L_BTN_BACK, Color3B::WHITE, Color3B::YELLOW, false));
    setModal(Modal::create());
    getModal()->setGlobalZOrder(OBJ_LAYER_TOP);
    getModal()->setModal(Size(60,60), "");
    getModal()->setModalOpacity(0);
    // modal end
    
    setBtn1(generateMenuItemSprite([this](Ref* ref){
        this->getBike()->removeTouchEvent();
        Director::getInstance()->getEventDispatcher()->removeEventListener(this->getContactListenner());
        this->getBike()->getRwheel()->getPhysicsBody()->setAngularDamping(1);
        this->setModalMenu(Menu::create(getBtn2(),getBtn4(),NULL));
        this->getModalMenu()->alignItemsVerticallyWithPadding(5);
        this->getModalMenu()->setPosition(Vec2::ZERO);
        this->getModal()->addChild(getModalMenu());
        this->getModal()->setScale(0);
        auto big = ScaleTo::create(0.3, 1);
        this->getModal()->runAction(big);
        this->mountNode(getModal(), ctPt, OBJ_LAYER_TOP);
        this->getBtn1()->removeFromParent();
    }, Size(1,1), L_BTN_QUIT, Color3B::WHITE, Color3B::YELLOW, false));
    setMenu(Menu::create(getBtn1(),NULL));
    getMenu()->alignItemsHorizontallyWithPadding(20);
    mountNode(getMenu(), Vec2(winSize.width - getBtn1()->getContentSize().width/2 -10,
                              winSize.height - getBtn1()->getContentSize().height/2 -10), OBJ_LAYER_TOP);
    
    setCourceMaker(CourceMaker::create());
    addChild(getCourceMaker());
    
    setCourceManager(CourceManager::create());
    addChild(getCourceManager()->getCourceMakerA());
    addChild(getCourceManager()->getCourceMakerB());
    return true;
}

void GameStage::onEnterTransitionDidFinish() {
    GameScene::onEnterTransitionDidFinish();
    getCourceManager()->checkAndMadeCource(Vec2::ZERO);
    
    // Bikeをセット
    setBike(Bike::create());
    mountScroleNode(getBike(), RIDER_START_POINT, OBJ_LAYER_TOP);
    mountScroleNode(getBike()->getSceneChasePt(), getBike()->getFwheel()->getPosition()+getBike()->sceneOffset + Vec2(-200,0), OBJ_LAYER_TOP);
    getBike()->SetPhysicsPrm();
    getScene()->getPhysicsWorld()->addJoint(getBike()->getFRJoint());
    getBike()->scheduleUpdate();
    // ~Bikeをセット
    setContactListener();
    
    // 画面スクロール開始
    runAction(Follow::create(getBike()->getSceneChasePt()));
    scheduleUpdate();
    
    // 開始を遅らせる。
    auto wait_ = DelayTime::create(0.5);
    auto func_ = CallFunc::create([this]{
        setGameState(GameState::READY);
        fstStCnge = true;
    });
    auto seq_ = Sequence::create(wait_,func_, NULL);
    runAction(seq_);
}

void GameStage::update(float dt) {
    if(fstStCnge){
        fstStCnge = false;
        switch (getGameState()) {
            case GameState::READY: {
                onReady();
                break;
            }
            case GameState::PLAY: {
                onPlay();
                break;
            }
            case GameState::CLEAR: {
                onClear();
                break;
            }
            case GameState::MISS: {
                onMiss();
                break;
            }
        }
    }
    getCourceManager()->checkAndMadeCource(getBike()->getPosition());
    if(getBike()){
        NJLOG(ST_VEC2(ctPt).c_str());
        NJLOG(ST_VEC2(getPosition()).c_str());
        if(getDebugMemo()){
        getDebugMemo()->setString("重心位置:" + ST_VEC2(getBike()->weightPt));
//        getDebugMemo()->setString("chase:" + ST_VEC2(getBike()->getSceneChasePt()->getPosition()) + " " + ST_INT(getBike()->getRotation()));
//        getDebugMemo()->setString("bike:" + ST_VEC2(getBike()->getPosition()) + " " + ST_INT(getBike()->getRotation()));
//        getDebugMemo()->setString("swaip:" + ST_VEC2(getBike()->weightPt));
//   getDebugMemo()->setString("bike:" + ST_INT(getBike()->centerObjVelo.length()) + "km/h");
        }
    }
}

void GameStage::onReady(){
    int stg = UserDefault::getInstance()->getIntegerForKey(UDF_INT_SELECTED_STAGE,1);
    if(stg==1){
        demo();
    }else{
        auto setumei_ = CallFunc::create([this,stg]{
            this->setSetumei(getCourceManager()->getStgComment(stg));
        });
        auto wait_ = DelayTime::create(3);
        auto play_ =  CallFunc::create([this]{
            this->getSetumei()->removeFromParentAndCleanup(true);
            this->showGameAnnounce(L_GAME_READY, ctPt + Vec2(0,50),[this]{
                setGameState(GameState::PLAY);
                fstStCnge = true;
            });
        });
        runAction(Sequence::create(setumei_,wait_,play_, NULL));
    }
}

void GameStage::onPlay(){
    showGameAnnounce(L_GAME_START, ctPt + Vec2(0,50),[this]{
        getBike()->setTouchEvent();
    });
}

void GameStage::onClear(){
    getBike()->getRwheel()->getPhysicsBody()->setAngularDamping(1);
//    getBike()->getRwheel()->getPhysicsBody()->setLinearDamping(1);
    getBike()->removeTouchEvent();
    showGameAnnounce(L_GAME_CLEAR, ctPt + Vec2(0,50),[this]{
        setModalMenu(Menu::create(getBtn3(),getBtn4(),NULL));
        getModalMenu()->alignItemsVerticallyWithPadding(5);
        getModalMenu()->setPosition(Vec2::ZERO);
        getModal()->addChild(getModalMenu());
        getModal()->setScale(0);
        auto big = ScaleTo::create(0.3, 1);
        getModal()->runAction(big);
        mountNode(getModal(), ctPt, OBJ_LAYER_TOP);
    });
}

void GameStage::onMiss(){
    callSoundEffect("btnon.mp3");
    getBike()->getFRJoint()->removeFormWorld();
    getBike()->unscheduleUpdate();
    getBike()->removeTouchEvent();
    auto gun = Sprite::create("gan.png");
    gun->setPosition(missPt);
    gun->setGlobalZOrder(OBJ_LAYER_TOP);
    addChild(gun);
    showGameAnnounce(L_GAME_MISS, ctPt + Vec2(0,50),[this]{
        setModalMenu(Menu::create(getBtn2(),getBtn4(),NULL));
        getModalMenu()->alignItemsVerticallyWithPadding(5);
        getModalMenu()->setPosition(Vec2::ZERO);
        getModal()->addChild(getModalMenu());
        getModal()->setScale(0);
        auto big = ScaleTo::create(0.3, 1);
        getModal()->runAction(big);
        mountNode(getModal(), ctPt, OBJ_LAYER_TOP);
    });
}

void GameStage::setContactListener() {
    //接触感知
    setContactListenner(EventListenerPhysicsContact::create());
    
    getContactListenner()->onContactBegin = [this](PhysicsContact& contact) {
        //        NJLOG("contact_begin");
        //        NJLOG("fWheel_normal");
        _onContactBegin(contact, contact.getShapeA());
        _onContactBegin(contact, contact.getShapeB());
        return true;
    };
    
    getContactListenner()->onContactPostSolve = [this](PhysicsContact& contact, const PhysicsContactPostSolve& solve) {
        _onContactPostSolve(contact, contact.getShapeA());
        _onContactPostSolve(contact, contact.getShapeB());
        return true;
    };
    
    getContactListenner()->onContactSeparate = [this](PhysicsContact& contact) {
        _onContactSeparate(contact, contact.getShapeA());
        _onContactSeparate(contact, contact.getShapeB());
        return true;
    };
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(getContactListenner(),this);
}

void GameStage::_onContactBegin(PhysicsContact& contact, PhysicsShape* ps){
    switch(ps->getBody()->getTag()){
        case TG_F_WHEEL:{
            getBike()->fWheelTouchPt.set(contact.getContactData()->normal);
            getBike()->fWheelTouched = true;
            //                NJLOG("fWheel_normal");
            //                NJLOG(ST_VEC2(contact.getContactData()->normal).c_str());
            break;
        }
        case TG_R_WHEEL:{
            getBike()->rWheelTouchPt.set(contact.getContactData()->normal);
            getBike()->rWheelTouched = true;
            //                NJLOG("rWheel_normal");
            //                NJLOG(ST_VEC2(contact.getContactData()->normal).c_str());
            break;
        }
        case TG_RIDER: {
            setGameState(GameState::MISS);
            missPt.set(contact.getContactData()->points[0]);
            fstStCnge = true;
            break;
        }
        case TG_START: {
            break;
        }
        case TG_GOAL: {
            setGameState(GameState::CLEAR);
            fstStCnge = true;
            break;
        }
        default:{
            break;
        }
    }
}

void GameStage::_onContactPostSolve(PhysicsContact& contact, PhysicsShape* ps){
    switch(ps->getBody()->getTag()){
        case TG_F_WHEEL:{
            getBike()->fWheelTouchPt.set(contact.getContactData()->normal);
            getBike()->fWheelTouched = true;
            //                NJLOG("fWheel_normal");
            //                NJLOG(ST_VEC2(contact.getContactData()->normal).c_str());
            break;
        }
        case TG_R_WHEEL:{
            getBike()->rWheelTouchPt.set(contact.getContactData()->normal);
            getBike()->rWheelTouched = true;
            //                NJLOG("rWheel_normal");
            //                NJLOG(ST_VEC2(contact.getContactData()->normal).c_str());
            break;
        }
        case TG_START: {
            break;
        }
        case TG_GOAL: {
            break;
        }
        default:{
            break;
        }
    }
}

void GameStage::_onContactSeparate(PhysicsContact& contact, PhysicsShape* ps){
    switch(ps->getBody()->getTag()){
        case TG_F_WHEEL:{
            getBike()->fWheelTouchPt.set(contact.getContactData()->normal);
            getBike()->fWheelTouched = false;
            NJLOG("fWheel_touch_OFF");
            NJLOG(ST_VEC2(contact.getContactData()->normal).c_str());
            break;
        }
        case TG_R_WHEEL:{
            getBike()->rWheelTouchPt.set(contact.getContactData()->normal);
            getBike()->rWheelTouched = false;
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
        default:{
            break;
        }
    }
}

void GameStage::setSetumei(std::string st){
    if(getSetumei()){
        getSetumei()->removeFromParentAndCleanup(true);
    }
    setSetumei(Label::createWithTTF("", "irohamaru.ttf", 12));
    getSetumei()->setAnchorPoint(Vec2(0,1));
    getSetumei()->setGlobalZOrder(OBJ_LAYER_TOP);
    getBike()->getSceneChasePt()->addChild(getSetumei());
    
    getSetumei()->setString(st);
    getSetumei()->setPosition(Vec2(-30,130) + Vec2(500,0));
    auto moveTo = MoveBy::create(0.5, Vec2(-500,0));
    getSetumei()->runAction(moveTo);
}

void GameStage::demo(){

    setYubi(Sprite::create("yubi.png"));
    getYubi()->setGlobalZOrder(OBJ_LAYER_TOP);
    getBike()->getSceneChasePt()->addChild(getYubi());
    
    getBike()->autoFlg = true;
    getBike()->weightPt= Vec2::ZERO;
    getBike()->getDebugPt()->setPosition(Vec2::ZERO);
    getBike()->removeTouchEvent();
    
    // demofirst
    auto sosaSetumei_ = CallFunc::create([this]{
        std::string st = "<<操作方法>>\n"
        "画面をタップして、\n"
        "上下左右にスワイプすると\n"
        "ライダーも上下左右に\n"
        "重心移動します。\n";
        this->setSetumei(st);
    });
    
    auto delay_ = DelayTime::create(1);
    auto move1_ = MoveTo::create(0.5, Vec2(0,6));
    auto move2_ = MoveTo::create(0.5, Vec2(0,-6));
    auto move3_ = MoveTo::create(0.5, Vec2(-6,0));
    auto move4_ = MoveTo::create(0.5, Vec2(6,0));
    auto move5_ = MoveTo::create(0.5, Vec2(6,6));
    auto move6_ = MoveTo::create(0.5, Vec2(-6,6));
    auto move7_ = MoveTo::create(0.5, Vec2(-6,-6));
    auto move8_ = MoveTo::create(0.5, Vec2(6,-6));
    auto move9_ = MoveTo::create(0.5, Vec2(0,0));
    auto allSetumei_ = Sequence::create(sosaSetumei_,delay_,move1_,move2_,move3_,move4_,move5_,move6_,move7_,move8_,move9_, NULL);
    
    // werry
    auto werrySetumei_ = CallFunc::create([this]{
        std::string st = "<<ウイリー>>\n"
        "左右に素早くスワイプすると\n"
        "ライダーが左右に\n"
        "ウイリーします。\n";
        this->setSetumei(st);
    });
    auto move10_ = MoveTo::create(0.8, Vec2(6,0));
    auto move11_ = MoveTo::create(0.2, Vec2(-6,0));
    auto werryF4_ = Repeat::create(Sequence::create(move10_,move11_, NULL), 4);
        
    auto move12_ = MoveTo::create(0.8, Vec2(-6,0));
    auto move13_ = MoveTo::create(0.2, Vec2(6,0));
    auto werryR4_ = Repeat::create(Sequence::create(move12_,move13_, NULL), 4);
    
    // FRJump
    auto frJumpSetumei_ = CallFunc::create([this]{
        std::string st = "<<両輪ジャンプ>>\n"
        "両輪が地面接地時に\n"
        "下から上に素早くスワイプすると\n"
        "両輪ジャンプします。\n";
        this->setSetumei(st);
    });
    auto delay14_ = DelayTime::create(0.5);
    auto move14_ = MoveTo::create(0.8, Vec2(0,-6));
    auto move15_ = MoveTo::create(0.05, Vec2(0,6));
    auto frJump4_ = Repeat::create(Sequence::create(delay14_,move14_,move15_, NULL), 4);
    
    // RJump
    auto rJumpSetumei_ = CallFunc::create([this]{
        std::string st = "<<後輪ジャンプ>>\n"
        "前輪ウイリー時に\n"
        "下から上に素早くスワイプすると\n"
        "両輪ジャンプより\n"
        "より高くジャンプします。\n";
        this->setSetumei(st);
    });
    auto move16_ = MoveTo::create(0.8, Vec2(6,6));
    auto move17_ = MoveTo::create(0.1, Vec2(-6,-6));
    auto move18_ = DelayTime::create(0.4);
    auto move19_ = MoveTo::create(0.05, Vec2(-6,6.0));
    auto delay20_ = DelayTime::create(0.5);
    auto rJump4_ = Repeat::create(Sequence::create(move16_,move17_,move18_,move19_,delay20_, NULL), 4);
    
    // dush
    auto dushSetumei_ = CallFunc::create([this]{
        std::string st = "<<加速>>\n"
        "しゃがんだ状態で\n"
        "右に素早くスワイプすると\n"
        "加速します。\n";
        this->setSetumei(st);
    });
    auto move21_ = MoveTo::create(0.8, Vec2(-5,-6));
    auto move22_ = MoveTo::create(0.1, Vec2(6,-6));
    auto dush4_ = Repeat::create(Sequence::create(move21_,move22_, NULL), 4);
    
    // break
    auto breakSetumei_ = CallFunc::create([this]{
        std::string st = "<<減速>>\n"
        "左下に重心を\n"
        "置き続けると\n"
        "ブレーキが働きます。\n";
        this->setSetumei(st);
    });
    auto move23_ = MoveTo::create(0.8, Vec2(-6,-6));
    auto delay24_ = DelayTime::create(5);
    auto move25_ = MoveTo::create(0.8, Vec2(0,0));
    auto break_ = Sequence::create(move23_,delay24_,move25_, NULL);

     auto seq_ = Sequence::create(allSetumei_,
                                  // werry
                                  werrySetumei_,werryF4_,werryR4_,
                                  // frJump
                                  frJumpSetumei_,frJump4_,
                                  // rJump
                                  rJumpSetumei_,rJump4_,
                                  // dush
                                  dushSetumei_,dush4_,
                                  // stop
                                  breakSetumei_,break_,
                                  delay_,NULL);
    
    auto endfunc_ = CallFunc::create([this]{
        this->getBike()->autoFlg = false;
        this->getYubi()->setOpacity(0);
        this->getSetumei()->setString("");
    });
    
    auto setumei_ = CallFunc::create([this]{
        this->setSetumei(getCourceManager()->getStgComment(1));
    });
    
    auto wait_ = DelayTime::create(3);
    auto play_ =  CallFunc::create([this]{
        this->getSetumei()->removeFromParentAndCleanup(true);
        this->showGameAnnounce(L_GAME_READY, ctPt + Vec2(0,50),[this]{
            setGameState(GameState::PLAY);
            fstStCnge = true;
        });
    });

    auto strt_ = Sequence::create(endfunc_,setumei_,wait_,play_,NULL);
    getBike()->getDebugPt()->runAction(Sequence::create(seq_,strt_,NULL));
    getYubi()->runAction(seq_->clone());
}


/** パラメータサンプル
 setGameTitle(Label::create());
 getGameTitle();
 setBaseLine(DrawNode::create());
 getBaseLine();
 setbike(DrawNode::create());
 getbike();
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
 */
