#include "Bike.h"
#include "audio/include/AudioEngine.h"

Bike::Bike():
_rider(NULL),_fWheel(NULL), _rWheel(NULL),_sceneChasePt(NULL), _BikeState(BikeState::NOML),_bikeDebug(NULL)
{}

Bike::~Bike() {
    CC_SAFE_RELEASE_NULL(_rider);
    CC_SAFE_RELEASE_NULL(_fWheel);
    CC_SAFE_RELEASE_NULL(_rWheel);
    CC_SAFE_RELEASE_NULL(_sceneChasePt);
    CC_SAFE_RELEASE_NULL(_sceneChasePt);
    CC_SAFE_RELEASE_NULL(_bikeDebug);
}

Bike* Bike::create() {
    auto obj = new Bike;
    if (obj && obj->init()) {
        obj->autorelease();
        return obj;
    } else {
        CC_SAFE_DELETE(obj);
        return nullptr;
    }
}

bool Bike::init() {
    if(!Sprite2::initWithFile("bike2.png")){
        return false;
    }
    bikeAnchorPt.set(0.05, 0.08);
    setAnchorPoint(bikeAnchorPt);
    bikeCenterPt.set(getContentSize().width/2,getContentSize().height/2);
    
    // riderをセットする。
    setRider(Sprite::create("riders.png"));
    frameSize = Size(getRider()->getContentSize().width / 7, getRider()->getContentSize().height / 7);
    
    getRider()->setPosition(Vec2(25,30));
    getRider()->setGlobalZOrder(OBJ_LAYER_LV3);
    addChild(getRider());
    riderImageAction();
    
    // wheelをセットする。
    setFwheel(Sprite::create("wheel3.png"));
    setRwheel(Sprite::createWithTexture(getFwheel()->getTexture()));
    
    // 効果音
    setSoundEffect(SOUND_PLAYER_JUMP);
    
//    _setTouchEvent(); // game進行上で起動させる。

    //debug
    setDebugPt(Sprite::create("dot.png"));
    getDebugPt()->setGlobalZOrder(OBJ_LAYER_TOP+1);
    addChild(getDebugPt());
    setParentSprite(Sprite::create("dot2.png"));
    getParentSprite()->setGlobalZOrder(OBJ_LAYER_TOP);
    addChild(getParentSprite());
    
    // sceneスクロール用
    setSceneChasePt(Sprite::create("dot2.png"));
    getSceneChasePt()->setPosition(sceneOffset);
    getSceneChasePt()->setOpacity(0);
    getSceneChasePt()->setGlobalZOrder(OBJ_LAYER_BUTTOM);

    // debug用
    setSoundEffect(SOUND_PLAYER_JUMP);
//    setBikeDebug(Label::createWithTTF("bikeState", "irohamaru.ttf", 10));
//    getBikeDebug()->setTextColor(Color4B::BLACK);
//    getBikeDebug()->setGlobalZOrder(OBJ_LAYER_TOP);
//    getBikeDebug()->setPosition(Vec2(0,50));
//    addChild(getBikeDebug());
    
    return true;
}

void Bike::setForDisplay(){
    if(getDebugPt()){
        getDebugPt()->removeFromParentAndCleanup(true);
    }
    Vec2 hosei = Vec2(1,2);
    getFwheel()->setPosition(getPosition()+Vec2(wheelBase,0)+hosei);
    addChild(getFwheel());
    getRwheel()->setPosition(getPosition());
    getRwheel()->setPosition(getPosition()+hosei);
    addChild(getRwheel());
    getFwheel()->setGlobalZOrder(OBJ_LAYER_LV2-1);
    getRwheel()->setGlobalZOrder(OBJ_LAYER_LV2-1);
}

void Bike::_addPhysicsToWheel(Sprite* _wheel){
    
    auto _material = PHYSICSBODY_MATERIAL_DEFAULT;
    _material.restitution = 0.0f;
    _material.friction =1.0f;
    _material.density = 0.001f;
    
    _wheel->setPhysicsBody(PhysicsBody::createCircle(_wheel->getContentSize().width / 2 + 1,_material));
    _wheel->getPhysicsBody()->setGravityEnable(true);
    _wheel->getPhysicsBody()->setCategoryBitmask(CT_WHEEL);
    _wheel->getPhysicsBody()->setCollisionBitmask(CT_COURCE);
    _wheel->getPhysicsBody()->setContactTestBitmask(CT_COURCE | CT_GOAL);
    //    _wheel->getPhysicsBody()->setTag(1);
    _wheel->getPhysicsBody()->setDynamic(true);
    //    _wheel->getPhysicsBody()->setAngularDamping(wheelRotDump_);
    //    _wheel->getPhysicsBody()->setLinearDamping(veloDump);
    _wheel->getPhysicsBody()->setVelocityLimit(maxWheelVelo);
    _wheel->getPhysicsBody()->setRotationEnable(true);
}

void Bike::_positionSyncToWheel(float dt){
    float kaku = getCalc()->nomlKaku(getRwheel()->getPosition(),getFwheel()->getPosition());
    setRotation(kaku);
     setPosition(getRwheel()->getPosition()+getRwheel()->getPhysicsBody()->getVelocity()*dt*PHYSICS_WOELD_SPEED);
//    setPosition(getRwheel()->getPosition()+getRwheel()->getPhysicsBody()->getVelocity()*dt);
    
    // 画面スクロールポイントを指定
    if(_sceneChasePt){
        if(sceneChaseAjustFlg){
            _sceneChasePt->setPosition(getFwheel()->getPosition()+sceneOffset);
        }else{
            Vec2 pos = _sceneChasePt->getPosition();
            if(pos.equals(Vec2::ZERO)){
                sceneChaseAjustFlg = true;
            }
            getCalc()->chasePt(getFwheel()->getPosition()+sceneOffset, pos, sceneChaseAjustSpeed, dt);
            _sceneChasePt->setPosition(pos);
        }
    }
}

void Bike::setTouchEvent(){
    setTouch(TouchEventHelper::create());
    getTouch()->getTouchListenner()->onTouchBegan = [this](Touch* touch,Event* event) {
        touchOn(touch->getLocation());
        return true;
    };
    getTouch()->getTouchListenner()->onTouchMoved = [this](Touch* touch,Event* event) {
        swaip(touch->getLocation());
        return true;
    };
    getTouch()->getTouchListenner()->onTouchEnded = [this](Touch* touch,Event* event) {
        touchOff(Vec2::ZERO);
        return true;
    };
    getTouch()->applyTouchListenner(this);
}

void Bike::removeTouchEvent(){
    if(getTouch()){
        getTouch()->removeTouchListenner();
    }
    
}

void Bike::onEnterTransitionDidFinish() {
    // todo
}

void Bike::SetPhysicsPrm(){
    
    getFwheel()->setPosition(getPosition()+Vec2(wheelBase,0));
    getParent()->addChild(getFwheel(),OBJ_LAYER_LV2);
    _addPhysicsToWheel(getFwheel());
    getFwheel()->getPhysicsBody()->setTag(TG_F_WHEEL);
    
    getRwheel()->setPosition(getPosition());
    getParent()->addChild(getRwheel(),OBJ_LAYER_LV2);
    _addPhysicsToWheel(getRwheel());
    getRwheel()->getPhysicsBody()->setTag(TG_R_WHEEL);
    
    // 前後輪をジョイントを生成する。
    setFRJoint(PhysicsJointDistance::construct(getRwheel()->getPhysicsBody(),
                                                     getFwheel()->getPhysicsBody(),
                                                     getRwheel()->getPhysicsBody()->getPosition(),
                                                     getFwheel()->getPhysicsBody()->getPosition()));
    getFwheel()->setGlobalZOrder(OBJ_LAYER_LV2);
    getRwheel()->setGlobalZOrder(OBJ_LAYER_LV2);
    
    // body追加
    auto _material = PHYSICSBODY_MATERIAL_DEFAULT;
    _material.restitution = 0;
    _material.friction = 0;
    _material.density = 0;
    getRider()->setPhysicsBody(PhysicsBody::createCircle(5,_material));
    getRider()->getPhysicsBody()->setGravityEnable(false);
    getRider()->getPhysicsBody()->setCategoryBitmask(CT_RIDER);
    getRider()->getPhysicsBody()->setCollisionBitmask(CT_COURCE);
    getRider()->getPhysicsBody()->setContactTestBitmask(CT_COURCE);
    getRider()->getPhysicsBody()->setDynamic(true);
    getRider()->getPhysicsBody()->setRotationEnable(false);
    getRider()->getPhysicsBody()->setTag(TG_RIDER);
}

void Bike::update(float dt) {
    if (autoFlg){
        weightPt = getDebugPt()->getPosition();
    }
    riderImageAction();
    _bikeBehaviorControl();
    _judeAction(dt);
    _positionSyncToWheel(dt);
}

void Bike::touchOn(Vec2 pt){
    touchPt1.set(pt);
    touchPt2.set(pt);
    weightPt.set(Vec2::ZERO);
    chasePt.set(weightPt);
    if(getBikeDebug()){
        getBikeDebug()->setString("bikeState");
    }
}

void Bike::swaip(Vec2 pt){
    touchPt2.set(pt);
//    Vec2 dir_ = getFwheel()->getPosition() - getRwheel()->getPosition();
    Vec2 dV = touchPt2 - touchPt1;
//    dV = getCalc()->cordinaneX(dir_, dV);
    weightPt+=dV;
    if(weightPt.x > 4 * riderActionSpan){
        weightPt.x =  4 * riderActionSpan;
    }
    if(weightPt.x < - 4 * riderActionSpan){
        weightPt.x = - 4 * riderActionSpan;
    }
    if(weightPt.y > 4 * riderActionSpan){
        weightPt.y =  4 * riderActionSpan;
    }
    if(weightPt.y < - 4 * riderActionSpan){
        weightPt.y = - 4 * riderActionSpan;
    }
    touchPt1.set(pt);
}

void Bike::touchOff(Vec2 pt){
    touchPt1.set(pt);
    touchPt2.set(pt);
    weightPt.set(Vec2::ZERO);
    chasePt.set(weightPt);
    if(getBikeDebug()){
        getBikeDebug()->setString("bikeState");
    }
}

void Bike::riderImageAction(){
    int x_ = weightPt.x/riderActionSpan;
    int y_ = -weightPt.y/riderActionSpan;
    if (x_ > 3){
        x_=3;
    }
    if (x_ < -3){
        x_=-3;
    }
    if (y_ > 3){
        y_=3;
    }
    if (y_ < -3){
        y_=-3;
    }
    if(getDebugPt() && !autoFlg){
        getDebugPt()->setPosition(weightPt+bikeCenterPt);
    }
    getRider()->setTextureRect(Rect(frameSize.width * (x_+3), frameSize.height * (y_+3),
                                          frameSize.width, frameSize.height));
}

void Bike::_bikeBehaviorControl(){
    centerObjVelo = (getFwheel()->getPhysicsBody()->getVelocity() + getRwheel()->getPhysicsBody()->getVelocity())/2;
    float maxCenterObjVelo = 200;
    centerObjRotVelo = getFwheel()->getPhysicsBody()->getVelocity() - centerObjVelo;
}

void Bike::_judeAction(float dt){
    
    Vec2 noml_ = getCalc()->cordinaneX(Vec2(1,0), weightPt-chasePt);
    
    // 前後のウイリー
    if( chasePt.y >= -riderActionSpan){
        if(noml_.x > riderActionSpan/2){
            werry(-noml_.x);
            chasePt.set(weightPt);
            if(getParentSprite()){
                getParentSprite()->setPosition(chasePt + bikeCenterPt);
            }
            return;
        }else if(noml_.x < -riderActionSpan/2){
            werry(-noml_.x);
            chasePt.set(weightPt);
            if(getParentSprite()){
                getParentSprite()->setPosition(chasePt + bikeCenterPt);
            }
            return;
        }
    }
    
    // 後のウイリー
    if( chasePt.x < -riderActionSpan*2){
        if(noml_.y > riderActionSpan/2 && !rWheelTouched){
            werry(-noml_.y);
            chasePt.set(weightPt);
            if(getParentSprite()){
                getParentSprite()->setPosition(chasePt + bikeCenterPt);
            }
            return;
        }else if(noml_.y < -riderActionSpan/2){
            werry(-noml_.y);
            chasePt.set(weightPt);
            if(getParentSprite()){
                getParentSprite()->setPosition(chasePt + bikeCenterPt);
            }
            return;
        }
    }
    
    // 前のウイリー
    if( chasePt.x > riderActionSpan*2){
        if(noml_.y > riderActionSpan/2 && !fWheelTouched){
            werry(noml_.y);
            chasePt.set(weightPt);
            if(getParentSprite()){
                getParentSprite()->setPosition(chasePt + bikeCenterPt);
            }
            return;
        }else if(noml_.y < -riderActionSpan/2){
            werry(noml_.y);
            chasePt.set(weightPt);
            if(getParentSprite()){
                getParentSprite()->setPosition(chasePt + bikeCenterPt);
            }
            return;
        }
    }

    // ジャンプ
    if(weightPt.y == riderActionSpan * 4){
        if(noml_.y > riderActionSpan * 4){
            jump(noml_.y);
            chasePt.set(weightPt);
            if(getParentSprite()){
                getParentSprite()->setPosition(chasePt + bikeCenterPt);
            }
            return;
        }
    }
    
    // dush
    if( chasePt.y < -riderActionSpan * 2){
        if(rWheelTouched && fWheelTouched){
            if(noml_.x > riderActionSpan * 2){
                dush(noml_.x);
                chasePt.set(weightPt);
                if(getParentSprite()){
                    getParentSprite()->setPosition(chasePt + bikeCenterPt);
                }
                return;
            }
        }
    }
    // 後輪ブレーキ
    if(chasePt.x == -4 * riderActionSpan && chasePt.y == -4 * riderActionSpan){
        if(rWheelTouched && fWheelTouched){
            stop();
            chasePt.set(weightPt);
            if(getParentSprite()){
                getParentSprite()->setPosition(chasePt + bikeCenterPt);
            }
            return;
        }
    }
    
    
    Vec2 weightDict = weightPt-weightPt_before;
    weightPt_before.set(weightPt);
    
    if(weightDict != Vec2::ZERO){
        float drad = getCalc()->diffRadA2B(weightDict_before, weightDict);
        weightDict_before.set(weightDict);
        if(abs(drad)>M_PI/2){
            chasePt.set(weightPt);
            return;
        }
    }
    
    getCalc()->chasePt(weightPt , chasePt, chaseVelo, dt);
    if(getParentSprite()){
        getParentSprite()->setPosition(chasePt + bikeCenterPt);
    }
}

bool Bike::jump(float lvl){
    Vec2 powPt;
    Vec2 veloPt = Vec2::ZERO;
    Vec2 fWheelTouchPt_ = fWheelTouchPt.y < 0 ? -fWheelTouchPt : fWheelTouchPt;
    Vec2 rWheelTouchPt_ = rWheelTouchPt.y < 0 ? -rWheelTouchPt : rWheelTouchPt;
    if(rWheelTouched){
        rWheelTouched = false;
        if(fWheelTouched){
            powPt = getCalc()->chgLength((rWheelTouchPt_ + fWheelTouchPt_), maxFRJumpSpeed);
            if(getBikeDebug()){
                getBikeDebug()->setString("jump_FR");
            }
            fWheelTouched = false;
            NJLOG("前後輪ジャンプ");
            NJLOG(ST_VEC2(powPt).c_str());
        }else{
            
            powPt = getCalc()->chgLength(rWheelTouchPt_, maxRJumpSpeed);
            if(getBikeDebug()){
                getBikeDebug()->setString("jump_R");
            }
            NJLOG("後輪ジャンプ");
            NJLOG(ST_VEC2(powPt).c_str());
        }
    }else{
        if(fWheelTouched){
            powPt = getCalc()->chgLength(fWheelTouchPt_, maxFJumpSpeed);
            NJLOG("前輪ジャンプ");
            NJLOG(ST_VEC2(powPt).c_str());
            fWheelTouched = false;
            if(getBikeDebug()){
                getBikeDebug()->setString("jump_F");
            }
        }else{
            return false;
        }
    }
    callSoundEffect(SOUND_PLAYER_JUMP);
    Vec2 dirX = getCalc()->rotByRad(powPt, -M_PI/2);
    float speedX = getCalc()->cordinaneX(dirX, getRwheel()->getPhysicsBody()->getVelocity()).x;
    Vec2 veloX = getCalc()->chgLength(dirX, speedX);
    
    getRwheel()->getPhysicsBody()->setVelocity(veloX + powPt);
    getFwheel()->getPhysicsBody()->setVelocity(veloX + powPt);
    return true;
}

bool Bike::lift(float lvl){
}

void Bike::werry(float lvl){
    Vec2 rfpt_ = getFwheel()->getPosition()-_rWheel->getPosition();
    Vec2 dirPt_ = getCalc()->rotByRad(rfpt_, -M_PI/2);
    Vec2 powPt = getCalc()->chgLength(dirPt_, weeryPow * -lvl) + centerObjRotVelo;
    if(powPt.length()>maxRotSpeed){
        powPt = getCalc()->chgLength(powPt, maxRotSpeed);
        if(getBikeDebug()){
            getBikeDebug()->setString("werry_max");
        }
    }else{
        if(getBikeDebug()){
            getBikeDebug()->setString("werry");
        }
    }
    if(!fWheelTouched && !rWheelTouched){
        powPt *= 0.8; // 空中回転の場合は、回転しすぎるので、半減させる。
    }
    getFwheel()->getPhysicsBody()->setVelocity(centerObjVelo + powPt);
    getRwheel()->getPhysicsBody()->setVelocity(centerObjVelo - powPt);
    
}

void Bike::dush(float lvl){
        Vec2 powPt = getCalc()->chgLength(getFwheel()->getPosition()-getRwheel()->getPosition(), dushPow * lvl);
        if(centerObjVelo.length() > maxDushSpeed){
            if(getBikeDebug()){
                getBikeDebug()->setString("dush_no");
            }
            return;
        }else{
            if((centerObjVelo + powPt).length() >  maxDushSpeed){
                powPt = getCalc()->chgLength(powPt, maxDushSpeed);
            }else{
                powPt = getCalc()->chgLength(powPt, (centerObjVelo + powPt).length());
            }
            
            getRwheel()->getPhysicsBody()->setVelocity(powPt);
            getFwheel()->getPhysicsBody()->setVelocity(powPt);
            if(getBikeDebug()){
                getBikeDebug()->setString("dush");
            }
        }
}

void Bike::stop(){
    if(getBikeDebug()){
        getBikeDebug()->setString("stop");
    }
    getRwheel()->getPhysicsBody()->setAngularVelocity(getRwheel()->getPhysicsBody()->getAngularVelocity() * 0.8);
}

void Bike::autoSosa(float dt,Vec2 pt){
    auto moveTo = MoveTo::create(dt, pt);
    getDebugPt()->runAction(moveTo);
}

/** パラメータサンプル
 setRider(Sprite::create());
 getRider();
 setFwheel(Sprite::create());
 getFwheel();
 setRwheel(Sprite::create());
 getRwheel();
 */


