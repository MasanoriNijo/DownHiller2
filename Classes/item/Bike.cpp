#include "Bike.h"
#include "audio/include/AudioEngine.h"

Bike::Bike():
_rider(NULL),_fWheel(NULL), _rWheel(NULL),_sceneChasePt(NULL), _BikeState(BikeState::NOML)
{}

Bike::~Bike() {
    CC_SAFE_RELEASE_NULL(_rider);
    CC_SAFE_RELEASE_NULL(_fWheel);
    CC_SAFE_RELEASE_NULL(_rWheel);
    CC_SAFE_RELEASE_NULL(_sceneChasePt);
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
    //    bikeAnchorPt.set(0.7690, 0.1708);
    bikeAnchorPt.set(0.10, 0.08);
    this->setAnchorPoint(bikeAnchorPt);
    bikeCenterPt.set(this->getContentSize().width/2,this->getContentSize().height/2);
    
    // riderをセットする。
    this->setRider(Sprite::create("riders.png"));
    frameSize = Size(getRider()->getContentSize().width / 7, getRider()->getContentSize().height / 7);
    
    getRider()->setPosition(Vec2(18,22));
    getRider()->setGlobalZOrder(OBJ_LAYER_TOP);// これを入れないとライダーが下に隠れて見えなくなる。
    this->addChild(getRider());    
    this->riderImageAction();
    
    // wheelをセットする。
    this->setFwheel(Sprite::create("wheel3.png"));
    getFwheel()->setPosition(Vec2(33,2));
    _addPhysicsToWheel(getFwheel());
    getFwheel()->getPhysicsBody()->setTag(TG_F_WHEEL);
    
    this->setRwheel(Sprite::createWithTexture(getFwheel()->getTexture()));
    getRwheel()->setPosition(Vec2(1,2));
    _addPhysicsToWheel(getRwheel());
    getRwheel()->getPhysicsBody()->setTag(TG_R_WHEEL);
    
    this->_setTouchEvent();
    
    //debug
    this->setDebugPt(Sprite::create("dot.png"));
    this->getDebugPt()->setGlobalZOrder(OBJ_LAYER_TOP);
    this->addChild(this->getDebugPt());
    this->setParentSprite(Sprite::create("dot2.png"));
    this->getParentSprite()->setGlobalZOrder(OBJ_LAYER_TOP);
    this->addChild(this->getParentSprite());
    
    // sceneスクロール用
    this->setSceneChasePt(Sprite::create("dot2.png"));
    _sceneChasePt->setPosition(sceneOffset);
    _sceneChasePt->setGlobalZOrder(OBJ_LAYER_TOP);
    //    this->addChild(_sceneChasePt);
    return true;
}

void Bike::_addPhysicsToWheel(Sprite* _wheel){
    
    auto _material = PHYSICSBODY_MATERIAL_DEFAULT;
    _material.restitution = 0.0001f;
    _material.friction =1.0f;
    _material.density = 0.001f;
    
    _wheel->setPhysicsBody(PhysicsBody::createCircle(_wheel->getContentSize().width / 2,_material));
    _wheel->getPhysicsBody()->setGravityEnable(true);
    _wheel->getPhysicsBody()->setCategoryBitmask(CT_WHEEL);
    _wheel->getPhysicsBody()->setCollisionBitmask(CT_COURCE);
    _wheel->getPhysicsBody()->setContactTestBitmask(CT_COURCE);
    //    _wheel->getPhysicsBody()->setTag(1);
    _wheel->getPhysicsBody()->setDynamic(true);
    //    _wheel->getPhysicsBody()->setAngularDamping(wheelRotDump_);
    //    _wheel->getPhysicsBody()->setLinearDamping(veloDump);
    //    _wheel->getPhysicsBody()->setVelocityLimit(maxWheelVelo);
    _wheel->getPhysicsBody()->setRotationEnable(true);
}

void Bike::_positionSyncToWheel(){
    float kaku = getCalc()->nomlKaku(getRwheel()->getPosition(),getFwheel()->getPosition());
    this->setRotation(kaku);
    this->setPosition(getRwheel()->getPosition());
}

void Bike::_setTouchEvent(){
    this->setTouch(TouchEventHelper::create());
    this->getTouch()->getTouchListenner()->onTouchBegan = [this](Touch* touch,Event* event) {
        this->touchOn(touch->getLocation());
        return true;
    };
    this->getTouch()->getTouchListenner()->onTouchMoved = [this](Touch* touch,Event* event) {
        this->swaip(touch->getLocation());
        return true;
    };
    this->getTouch()->getTouchListenner()->onTouchEnded = [this](Touch* touch,Event* event) {
        this->touchOff(Vec2::ZERO);
        return true;
    };
    this->getTouch()->applyTouchListenner(this);
}

void Bike::onEnterTransitionDidFinish() {
    // todo
}

void Bike::SetJoint(){
    
    getFwheel()->setPosition(this->getPosition()+Vec2(wheelBase,0));
    this->getParent()->addChild(getFwheel(),OBJ_LAYER_TOP);
    getRwheel()->setPosition(this->getPosition());
    this->getParent()->addChild(getRwheel(),OBJ_LAYER_TOP);
    // 前後輪をジョイントを生成する。
    this->setFRJoint(PhysicsJointDistance::construct(getRwheel()->getPhysicsBody(),
                                                     getFwheel()->getPhysicsBody(),
                                                     getRwheel()->getPhysicsBody()->getPosition(),
                                                     getFwheel()->getPhysicsBody()->getPosition()));
}

void Bike::update(float dt) {
    this->riderImageAction();
    this->_positionSyncToWheel();
    this->_bikeBehaviorControl();
    this->_judeAction(dt);
    
    // 画面のスクロールポイントを設定する。
    //    _this->getPosition() + sceneOffset;
    // todo
}

void Bike::touchOn(Vec2 pt){
    touchPt1.set(pt);
    touchPt2.set(pt);
    weightPt.set(Vec2::ZERO);
    chasePt.set(weightPt);
}

void Bike::swaip(Vec2 pt){
    touchPt2.set(pt);
    Vec2 dV = touchPt2 - touchPt1;
//    dV = getCalc()->rotByKaku(dV, -getRotation());
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
    if(this->getDebugPt()){
        this->getDebugPt()->setPosition(weightPt+bikeCenterPt);
    }
    
    this->getRider()->setTextureRect(Rect(frameSize.width * (x_+3), frameSize.height * (y_+3),
                                          frameSize.width, frameSize.height));
    // 画面スクロールポイントを指定
    if(_sceneChasePt){
        _sceneChasePt->setPosition(this->getPosition()+sceneOffset);
    }
    
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
        if(noml_.x > riderActionSpan){
            this->werry(-noml_.x);
            chasePt.set(weightPt);
            getParentSprite()->setPosition(chasePt + bikeCenterPt);
            return;
        }else if(noml_.x < -riderActionSpan){
            this->werry(-noml_.x);
            chasePt.set(weightPt);
            getParentSprite()->setPosition(chasePt + bikeCenterPt);
            return;
        }
    }
    
    // ジャンプ
    if(weightPt.y > riderActionSpan * 4 -1){
        if(noml_.y > riderActionSpan*2){
            this->jump(noml_.y);
            chasePt.set(weightPt);
            getParentSprite()->setPosition(chasePt + bikeCenterPt);
            return;
        }
    }

    // dush
    if( chasePt.y < -riderActionSpan * 2){
        if(rWheelTouched && fWheelTouched){
            if(noml_.x > riderActionSpan * 2){
                this->dush(noml_.x);
                chasePt.set(weightPt);
                getParentSprite()->setPosition(chasePt + bikeCenterPt);
                return;
            }
        }
    }
    // 後輪ブレーキ
    if(chasePt.x < -4 * riderActionSpan + 0.5 && chasePt.y < -4 * riderActionSpan + 0.5){
        stop();
        chasePt.set(weightPt);
        getParentSprite()->setPosition(chasePt + bikeCenterPt);
        return;
    }
    
    getCalc()->chasePt(weightPt , chasePt, chaseVelo, dt);
    getParentSprite()->setPosition(chasePt + bikeCenterPt);
}

bool Bike::jump(float lvl){
    Vec2 powPt;
    Vec2 veloPt;
    Vec2 nomlVeloPt;
    if(rWheelTouched){
        rWheelTouched = false;
        veloPt = getRwheel()->getPhysicsBody()->getVelocity();
        nomlVeloPt = getCalc()->cordinaneX(rWheelTouchPt, veloPt);
        if(fWheelTouched){
            nomlVeloPt.x = maxFRJumpSpeed;
            fWheelTouched = false;
            NJLOG("前後輪ジャンプ");
            NJLOG(ST_VEC2(powPt).c_str());
        }else{
            nomlVeloPt.x = maxRJumpSpeed;
            NJLOG("後輪ジャンプ");
            NJLOG(ST_VEC2(powPt).c_str());
        }
        powPt = getCalc()->rotByRad(nomlVeloPt, getCalc()->chgRad(-rWheelTouchPt));
        getRwheel()->getPhysicsBody()->setVelocity(getRwheel()->getPhysicsBody()->getVelocity() + powPt);
        getFwheel()->getPhysicsBody()->setVelocity(getRwheel()->getPhysicsBody()->getVelocity());
        return true;
    }else{
        if(fWheelTouched){
            veloPt = getFwheel()->getPhysicsBody()->getVelocity();
            nomlVeloPt = getCalc()->cordinaneX(fWheelTouchPt, veloPt);
            nomlVeloPt.x = maxFJumpSpeed;
            powPt = getCalc()->rotByRad(nomlVeloPt, getCalc()->chgRad(-fWheelTouchPt));
            NJLOG("前輪ジャンプ");
            NJLOG(ST_VEC2(powPt).c_str());
            fWheelTouched = false;
            getFwheel()->getPhysicsBody()->setVelocity(getFwheel()->getPhysicsBody()->getVelocity() + powPt);
            getRwheel()->getPhysicsBody()->setVelocity(getFwheel()->getPhysicsBody()->getVelocity());
            return true;
        }else{
            return false;
        }
    }
    return true;
}

bool Bike::lift(float lvl){
    Vec2 powPt;
    Vec2 veloPt;
    Vec2 nomlVeloPt;
    if(rWheelTouched){
        rWheelTouched = false;
        veloPt = getRwheel()->getPhysicsBody()->getVelocity();
        nomlVeloPt = getCalc()->cordinaneX(rWheelTouchPt, veloPt);
        if(fWheelTouched){
            nomlVeloPt.x = maxFRJumpSpeed;
            fWheelTouched = false;
            NJLOG("前後輪ジャンプ");
            NJLOG(ST_VEC2(powPt).c_str());
        }else{
            nomlVeloPt.x = maxRJumpSpeed;
            NJLOG("後輪ジャンプ");
            NJLOG(ST_VEC2(powPt).c_str());
        }
        powPt = getCalc()->rotByRad(nomlVeloPt, getCalc()->chgRad(-rWheelTouchPt));
        getRwheel()->getPhysicsBody()->setVelocity(getRwheel()->getPhysicsBody()->getVelocity() + powPt);
        getFwheel()->getPhysicsBody()->setVelocity(getRwheel()->getPhysicsBody()->getVelocity());
        return true;
    }else{
        if(fWheelTouched){
            veloPt = getFwheel()->getPhysicsBody()->getVelocity();
            nomlVeloPt = getCalc()->cordinaneX(fWheelTouchPt, veloPt);
            nomlVeloPt.x = maxFJumpSpeed;
            powPt = getCalc()->rotByRad(nomlVeloPt, getCalc()->chgRad(-fWheelTouchPt));
            NJLOG("前輪ジャンプ");
            NJLOG(ST_VEC2(powPt).c_str());
            fWheelTouched = false;
            getFwheel()->getPhysicsBody()->setVelocity(getFwheel()->getPhysicsBody()->getVelocity() + powPt);
            getRwheel()->getPhysicsBody()->setVelocity(getFwheel()->getPhysicsBody()->getVelocity());
            return true;
        }else{
            return false;
        }
    }
    return true;
}

void Bike::werry(float lvl){
    Vec2 rfpt_ = getFwheel()->getPosition()-_rWheel->getPosition();
    Vec2 dirPt_ = getCalc()->rotByRad(rfpt_, -M_PI/2);
    Vec2 powPt = getCalc()->chgLength(dirPt_, weeryPow * -lvl) + centerObjRotVelo;
    if(powPt.length()>maxRotSpeed){
        powPt = getCalc()->chgLength(powPt, maxRotSpeed);
    }
    if(!fWheelTouched && !rWheelTouched){
        powPt *= 0.5; // 空中回転の場合は、回転しすぎるので、半減させる。
    }
    getFwheel()->getPhysicsBody()->setVelocity(centerObjVelo + powPt);
    getRwheel()->getPhysicsBody()->setVelocity(centerObjVelo - powPt);
    
}

void Bike::dush(float lvl){
    Vec2 powPt;
    if(rWheelTouched && rWheelTouched){
        Vec2 powPt = this->getCalc()->chgLength(getFwheel()->getPosition()-getRwheel()->getPosition(), dushPow * lvl);
        getRwheel()->getPhysicsBody()->setVelocity(getRwheel()->getPhysicsBody()->getVelocity() + powPt);
        getFwheel()->getPhysicsBody()->setVelocity(getFwheel()->getPhysicsBody()->getVelocity() + powPt);
        return;
    }
}

void Bike::stop(){
    getRwheel()->getPhysicsBody()->setAngularVelocity(getRwheel()->getPhysicsBody()->getAngularVelocity() * 0.8);
}

/** パラメータサンプル
 this->setRider(Sprite::create());
 this->getRider();
 this->setFwheel(Sprite::create());
 this->getFwheel();
 this->setRwheel(Sprite::create());
 this->getRwheel();
 */


