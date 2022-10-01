#include "GameStage.h"

GameStage::GameStage():
_gameTitle(NULL),_restTime(NULL), _btn1(NULL), _btn2(NULL), _btn3(NULL), _btn4(NULL), _menu(NULL),_touch(NULL),_bike(NULL),
_contactlistener(NULL), _courceMaker(NULL),_courceManager(NULL),_modal(NULL),_modalMenu(NULL),
_yubi(NULL),_setumei(NULL)
{}

GameStage::~GameStage() {
    NJLOG("hoge:GameStage::~GameStage()");
    CC_SAFE_RELEASE_NULL(_gameTitle);
    CC_SAFE_RELEASE_NULL(_restTime);
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
    stopBGM("");
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
//    setBackGroundColor();
    setBackGradientGroundColor();
    setPosition(ctPt + Vec2(250,0));

    this->setDebugMemo(Label::createWithTTF("", "irohamaru.ttf", 16));
    this->mountNode(this->getDebugMemo(), Vec2(this->ctPt.x,120), OBJ_LAYER_LV1);

    setCourceManager(CourceManager::create());
    addChild(getCourceManager()->getCourceMakerA());
    addChild(getCourceManager()->getCourceMakerB());
    addChild(getCourceManager()->getGurd());
    _timeLimit = getCourceManager()->getStagePrm()->getTymeLimit();
    // タイムリミットが設定されている場合
    if(_timeLimit>0){
        setRestTime(Label::createWithTTF("残り時間:" + ST_FLOAT2(_timeLimit), "irohamaru.ttf", 24));
        getColorChanger()->SetColor(COMMENT_COLOR_H, COMMENT_COLOR_S, COMMENT_COLOR_V);
        getRestTime()->setColor(getColorChanger()->getColor3B());
        getRestTime()->setOpacity(0);
        mountNode(getRestTime(), Vec2(ctPt.x,winSize.height-80), OBJ_LAYER_TOP);
    }
        
    // 現在のステージNo
    int selStageNo = getCourceManager()->getStagePrm()->getStageNumber();
    // 最大ステージ数を考慮した次のステージNo
    int maxStage;
    int nextStageNo = selStageNo;

    if(UserDefault::getInstance()->getIntegerForKey(UDF_INT_GAME_MODE,GAME_MODE_STAGE) == GAME_MODE_STAGE){
        maxStage = STAGE_SIZE;
    }else{
        maxStage = COURCE_SIZE;
    }
                
    if(selStageNo < maxStage){
        nextStageNo++;
    }
    
    // modal画面を作成する。
    // もう一度ボタン
    setBtn2(generateMenuItemSprite([this, selStageNo](Ref* ref){
        // 現在のステージNo
        int selStageNo = getCourceManager()->getStagePrm()->getStageNumber();
        stopBGM("");
        callSoundEffect(SOUND_BUTTON);
        full_ad_cnt_ ++;
        if(full_ad_cnt_ >full_ad_cnt){
            full_ad_cnt_ = 0;
            showFullScreenAD();
        }
        transitonScene(GameStage::createScene());
    }, Size(1,1), selStageNo<10 ? " 0" + std::to_string(selStageNo) + " " : " " + std::to_string(selStageNo) + " ", Color3B::WHITE, Color3B::YELLOW, false));
    
    setBtn3(generateMenuItemSprite([this, selStageNo, nextStageNo](Ref* ref){
        if(UserDefault::getInstance()->getIntegerForKey(UDF_INT_CLEAR_STAGE,0) < selStageNo){
            UserDefault::getInstance()->setIntegerForKey(UDF_INT_CLEAR_STAGE, selStageNo);
        }
        UserDefault::getInstance()->setIntegerForKey(UDF_INT_SELECTED_STAGE,nextStageNo);
        callSoundEffect(SOUND_BUTTON);
        full_ad_cnt_ ++;
        if(full_ad_cnt_ >full_ad_cnt){
            full_ad_cnt_ = 0;
            showFullScreenAD();
        }
        transitonScene(GameStage::createScene());
    }, Size(1,1),nextStageNo<10 ? " 0" + std::to_string(nextStageNo) + " " : " " + std::to_string(nextStageNo) + " ", Color3B::WHITE, Color3B::YELLOW, false));
    
    setBtn4(generateMenuItemSprite([this](Ref* ref){
        callSoundEffect(SOUND_BUTTON);
        UserDefault::getInstance()->setIntegerForKey(UDF_INT_GAME_MODE, GAME_MODE_COURCE);
        if(full_ad_cnt_ >full_ad_cnt){
            full_ad_cnt_ = 0;
            showFullScreenAD();
        }
        transitonScene(SelectScene::createScene());
    }, Size(1,1), L_BTN_BACK, Color3B::WHITE, Color3B::YELLOW, false));

    setModal(Modal::create());
    getModal()->setGlobalZOrder(OBJ_LAYER_TOP);
    getModal()->setModal(Size(160,140), "メニュー");
//    getModal()->setModalOpacity(200);
    // modal end
    
    setBtn1(generateMenuItemSprite([this](Ref* ref){
        this->getBike()->removeTouchEvent();
        Director::getInstance()->getEventDispatcher()->removeEventListener(this->getContactListenner());
        this->getBike()->getRwheel()->getPhysicsBody()->setAngularDamping(1);
        this->setModalMenu(Menu::create(getBtn2(),getBtn4(),NULL));
        this->getModalMenu()->alignItemsVerticallyWithPadding(10);
        this->getModalMenu()->setPosition(Vec2(0,-20));
        this->getModal()->addChild(getModalMenu());
        getModal()->getTitle()->setString("もう一度");
        this->getModal()->setScale(0);
        auto big = EaseElasticOut::create(ScaleTo::create(0.8, 1));
        this->getModal()->runAction(big);
        this->mountNode(getModal(), ctPt, OBJ_LAYER_TOP);
        this->getBtn1()->removeFromParent();
    }, Size(1,1), L_BTN_QUIT, Color3B::WHITE, Color3B::YELLOW, false));
    setMenu(Menu::create(getBtn1(),NULL));
    getMenu()->alignItemsHorizontallyWithPadding(20);
    mountNode(getMenu(), Vec2(winSize.width - getBtn1()->getContentSize().height/2 -40,
                              winSize.height - getBtn1()->getContentSize().height/2 -40), OBJ_LAYER_TOP);
    
    // 効果音
    setSoundEffect(SOUND_BUTTON);
    setSoundEffect(SOUND_GAME_READY);
    setSoundEffect(SOUND_GAME_START);
    setSoundEffect(SOUND_GAME_CLEAR);
    setSoundEffect(SOUND_GAME_MISS);
    
    return true;
}

void GameStage::onEnterTransitionDidFinish() {
    GameScene::onEnterTransitionDidFinish();
    getCourceManager()->checkAndMadeCource(Vec2::ZERO);
    // Bikeをセット
    setBike(Bike::create());
    mountScroleNode(getBike(), RIDER_START_POINT, OBJ_LAYER_LV3-1);
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
    
    if(getRestTime() && tmFlg && _timeLimit>0){
        tm_ += dt;
        if(_timeLimit>tm_){
            getRestTime()->setString("残り時間:" + ST_FLOAT2(_timeLimit - tm_));
        }else{
            getRestTime()->setString("タイムオーバー！");
        }
    }
    
    if(getBike()){
//        NJLOG(ST_VEC2(ctPt).c_str());
//        NJLOG(ST_VEC2(getPosition()).c_str());
        if(getDebugMemo()){
//            getDebugMemo()->setString("重心位置:" + ST_VEC2(getBike()->weightPt));
            //        getDebugMemo()->setString("chase:" + ST_VEC2(getBike()->getSceneChasePt()->getPosition()) + " " + ST_INT(getBike()->getRotation()));
//                    getDebugMemo()->setString("bike:" + ST_VEC2(getBike()->getPosition()) + " " + ST_INT(getBike()->getRotation()));
            //        getDebugMemo()->setString("swaip:" + ST_VEC2(getBike()->weightPt));
               getDebugMemo()->setString( ST_INT(getBike()->centerObjVelo.length()) + "km/h");
        }
    }
}

void GameStage::onReady(){
    if(UserDefault::getInstance()->getIntegerForKey(UDF_INT_GAME_MODE,GAME_MODE_STAGE)==GAME_MODE_DEMO){
        demo();
    }else{
        showGameAnnounce("コース：" + ST_INT(getCourceManager()->getStagePrm()->getStageNumber()), ctPt + Vec2(0,200),[this]{
        auto play_ =  CallFunc::create([this]{
            this->setSetumei(getCourceManager()->getStagePrm()->getCommnent());
            auto delay_ = DelayTime::create(3);
            auto delSetumei_ = CallFunc::create([this]{
                this->getSetumei()->removeFromParentAndCleanup(true);
                this->callSoundEffect(SOUND_GAME_READY);
                this->showGameAnnounce(L_GAME_READY, ctPt + Vec2(0,200),[this]{
                    setGameState(GameState::PLAY);
                    fstStCnge = true;
                    getBike()->setTouchEvent();
                    if(getRestTime()){
                        getRestTime()->setOpacity(255);
                    }
                    startTime();
                });
            });
            runAction(Sequence::create(delay_,delSetumei_, NULL));
        });
        runAction(play_);
        });
    }
}

void GameStage::onPlay(){
    this->callSoundEffect(SOUND_GAME_START);
    showGameAnnounce(L_GAME_START, ctPt + Vec2(0,200),[this]{
        this->startBGM(SOUND_GAME_BGM,0.5f);
    });
}

void GameStage::onClear(){
    stopBGM("");
    getMenu()->removeFromParentAndCleanup(true);
//    getBike()->getRwheel()->getPhysicsBody()->setAngularDamping(1);
//    getBike()->getRwheel()->getPhysicsBody()->setLinearDamping(0.5);
    getBike()->removeTouchEvent();
    Director::getInstance()->getEventDispatcher()->removeEventListener(getContactListenner());
    stopTime();
    stopAllActions();
    // タイムオーバーチェック
    if(_timeLimit &&
       _timeLimit < tm_){
        this->callSoundEffect(SOUND_GAME_MISS);
        showGameAnnounce(L_GAME_MISS, ctPt + Vec2(0,200),[this]{
            setModalMenu(Menu::create(getBtn2(),getBtn4(),NULL));
            this->getModalMenu()->alignItemsVerticallyWithPadding(10);
            this->getModalMenu()->setPosition(Vec2(0,-20));
            getModal()->getTitle()->setString("もう一度");
            getModal()->addChild(getModalMenu());
            getModal()->setScale(0);
            auto big = EaseElasticOut::create(ScaleTo::create(0.8, 1));
            getModal()->runAction(big);
            mountNode(getModal(), ctPt, OBJ_LAYER_TOP);
        });
    }else{
        this->callSoundEffect(SOUND_GAME_CLEAR);
        showGameAnnounce(L_GAME_CLEAR, ctPt + Vec2(0,200),[this]{
            setModalMenu(Menu::create(getBtn3(),getBtn4(),NULL));
            this->getModalMenu()->alignItemsVerticallyWithPadding(10);
            this->getModalMenu()->setPosition(Vec2(0,-20));
            getModal()->getTitle()->setString("次のコース");
            getModal()->addChild(getModalMenu());
            getModal()->setScale(0);
            auto big = EaseElasticOut::create(ScaleTo::create(0.8, 1));
            getModal()->runAction(big);
            mountNode(getModal(), ctPt, OBJ_LAYER_TOP);
        });
    }
}

void GameStage::onMiss(){
    getMenu()->removeFromParentAndCleanup(true);
    stopBGM("");
    callSoundEffect(SOUND_PLAYER_MISS);
    getBike()->getFRJoint()->removeFormWorld();
    getBike()->getFwheel()->getPhysicsBody()->setVelocity(Vec2::ZERO);
    getBike()->getRwheel()->getPhysicsBody()->setVelocity(Vec2::ZERO);
    getBike()->unscheduleUpdate();
    getBike()->removeTouchEvent();
    Director::getInstance()->getEventDispatcher()->removeEventListener(getContactListenner());
    auto gun = Sprite::create("gan.png");
    gun->setRotation(getCalc()->chgKaku(missNomalPt)-getBike()->getRotation());
    gun->setPosition(Vec2(getBike()->getRider()->getContentSize().width/2,
                          getBike()->getRider()->getContentSize().height/2));
    gun->setGlobalZOrder(OBJ_LAYER_TOP);
    auto moveto = MoveBy::create(0.5, missNomalPt*20);
    auto fade = FadeOut::create(0.5);
    gun->runAction(fade);
    
    getBike()->getRider()->addChild(gun);
    showGameAnnounce(L_GAME_MISS, ctPt + Vec2(0,200),[this]{
        this->callSoundEffect(SOUND_GAME_MISS);
        setModalMenu(Menu::create(getBtn2(),getBtn4(),NULL));
        this->getModalMenu()->alignItemsVerticallyWithPadding(10);
        this->getModalMenu()->setPosition(Vec2(0,-20));
        getModal()->getTitle()->setString("もう一度");
        getModal()->addChild(getModalMenu());
        getModal()->setScale(0);
        auto big = EaseElasticOut::create(ScaleTo::create(0.8, 1));
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
            missNomalPt.set(contact.getContactData()->normal);
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
    setSetumei(Label::createWithTTF("", "irohamaru.ttf", 23));
    getSetumei()->setAnchorPoint(Vec2(0,1));
    getSetumei()->setGlobalZOrder(OBJ_LAYER_TOP);
    getColorChanger()->SetColor(COMMENT_COLOR_H, COMMENT_COLOR_S, COMMENT_COLOR_V);
    getSetumei()->setColor(getColorChanger()->getColor3B());
    getBike()->getSceneChasePt()->addChild(getSetumei());
    
    getSetumei()->setString(st);
    getSetumei()->setPosition(Vec2(-150,260) + Vec2(500,0));
    auto moveTo = MoveBy::create(0.5, Vec2(-500,0));
    getSetumei()->runAction(moveTo);
}

void GameStage::demo(){

    setYubi(Sprite::create("yubi.png"));
    getYubi()->setScale(1.5);
    getYubi()->setGlobalZOrder(OBJ_LAYER_TOP);
    getYubi()->setAnchorPoint(Vec2(0.5,2));
    getBike()->getSceneChasePt()->addChild(getYubi());
    
    getBike()->autoFlg = true;
    getBike()->weightPt= Vec2::ZERO;
    getBike()->setForDemo();
    getBike()->getDebugPt()->setPosition(Vec2::ZERO);
    getBike()->removeTouchEvent();
    
    // demofirst
    auto sosaSetumei_ = CallFunc::create([this]{
        this->setSetumei(DEMO_SOSA);
    });
    float moveSpn = 12;
    auto delay_ = DelayTime::create(1);
    auto move1_ = MoveTo::create(0.8, Vec2(0,moveSpn));
    auto move2_ = MoveTo::create(0.8, Vec2(0,-moveSpn));
    auto move3_ = MoveTo::create(0.8, Vec2(-moveSpn,0));
    auto move4_ = MoveTo::create(0.8, Vec2(moveSpn,0));
    auto move5_ = MoveTo::create(0.8, Vec2(moveSpn,moveSpn));
    auto move6_ = MoveTo::create(0.8, Vec2(-moveSpn,moveSpn));
    auto move7_ = MoveTo::create(0.8, Vec2(-moveSpn,-moveSpn));
    auto move8_ = MoveTo::create(0.8, Vec2(moveSpn,-moveSpn));
    auto move9_ = MoveTo::create(0.8, Vec2(0,0));
    auto allSetumei_ = Sequence::create(sosaSetumei_,delay_,move1_,move2_,move3_,move4_,move5_,move6_,move7_,move8_,move9_, NULL);
    
    // werry
    auto werrySetumei_ = CallFunc::create([this]{
        this->setSetumei(DEMO_WERRY);
    });
    auto move10_ = MoveTo::create(2, Vec2(moveSpn,0));
    auto move11_ = MoveTo::create(0.3, Vec2(-moveSpn,0));
    auto werryF4_ = Repeat::create(Sequence::create(move10_,move11_, NULL), 2);
        
    auto move12_ = MoveTo::create(2, Vec2(-moveSpn,0));
    auto move13_ = MoveTo::create(0.3, Vec2(moveSpn,0));
    auto werryR4_ = Repeat::create(Sequence::create(move12_,move13_, NULL), 2);
    
    // FRJump
    auto frJumpSetumei_ = CallFunc::create([this]{
        this->setSetumei(DEMO_FR_JUMP);
    });
    auto jumpSet_ = CallFunc::create([this]{
        this->getBike()->isReadyJump = true;
    });
    auto delay14_ = DelayTime::create(1);
    auto move14_ = MoveTo::create(0.8, Vec2(0,-moveSpn));
    auto move15_ = MoveTo::create(0.05, Vec2(0,moveSpn));
    auto frJump4_ = Repeat::create(Sequence::create(jumpSet_,delay14_,move14_,move15_, NULL), 2);
    
    // RJump
    auto rJumpSetumei_ = CallFunc::create([this]{
        this->setSetumei(DEMO_R_JUMP);
    });
    auto move16_ = MoveTo::create(1, Vec2(moveSpn,moveSpn));
    auto move17_ = MoveTo::create(0.3, Vec2(-moveSpn,-moveSpn));
    auto move18_ = DelayTime::create(0.4);
    auto move19_ = MoveTo::create(0.05, Vec2(-moveSpn,moveSpn));
    auto delay20_ = DelayTime::create(1);
    auto rJump4_ = Repeat::create(Sequence::create(move16_,move17_,move18_,jumpSet_,move19_,delay20_, NULL), 2);
    
    // dush
    auto dushSetumei_ = CallFunc::create([this]{
        this->setSetumei(DEMO_DUSH);
    });
    auto move21_ = MoveTo::create(1, Vec2(-moveSpn-1,-moveSpn));
    auto move22_ = MoveTo::create(0.2, Vec2(moveSpn,-moveSpn));
    auto dush4_ = Repeat::create(Sequence::create(move21_,move22_, NULL), 2);
    
    // break
    auto breakSetumei_ = CallFunc::create([this]{
        this->setSetumei(DEMO_BREAK);
    });
    auto move23_ = MoveTo::create(0.8, Vec2(-moveSpn,-moveSpn));
    auto delay24_ = DelayTime::create(3);
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
        UserDefault::getInstance()->setIntegerForKey(UDF_INT_GAME_MODE, GAME_MODE_COURCE);
    });
    
    auto setumei_ = CallFunc::create([this]{
        this->setSetumei(getCourceManager()->getStagePrm()->getCommnent());
    });
    
    auto wait_ = DelayTime::create(3);
    auto play_ =  CallFunc::create([this]{
        this->getSetumei()->removeFromParentAndCleanup(true);
        this->showGameAnnounce(L_GAME_READY, ctPt + Vec2(0,200),[this]{
            getBike()->setTouchEvent();
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
