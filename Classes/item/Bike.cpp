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
    _frJoint->removeFormWorld();
    _frJoint = nullptr;
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
    frameSize = Size(_rider->getContentSize().width / 7, _rider->getContentSize().height / 7);
    
    _rider->setPosition(Vec2(18,22));
    this->addChild(_rider,OBJ_LAYER_TOP);
    _rider->setGlobalZOrder(OBJ_LAYER_TOP);// これを入れないとライダーが下に隠れて見えなくなる。
    this->riderImageAction();
    
    // wheelをセットする。
    this->setFwheel(Sprite::create("wheel3.png"));
    _fWheel->setPosition(Vec2(33,2));
    _addPhysicsToWheel(_fWheel);
    _fWheel->getPhysicsBody()->setTag(TG_F_WHEEL);
    
    this->setRwheel(Sprite::createWithTexture(_fWheel->getTexture()));
    _rWheel->setPosition(Vec2(1,2));
    _addPhysicsToWheel(_rWheel);
    _rWheel->getPhysicsBody()->setTag(TG_R_WHEEL);
    
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
    float kaku = this->getCalc()->nomlKaku(_rWheel->getPosition(),_fWheel->getPosition());
    this->setRotation(kaku);
    this->setPosition(_rWheel->getPosition());
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
    
    _fWheel->setPosition(this->getPosition()+Vec2(wheelBase,0));
    this->getParent()->addChild(_fWheel,OBJ_LAYER_TOP);
    _rWheel->setPosition(this->getPosition());
    this->getParent()->addChild(_rWheel,OBJ_LAYER_TOP);
    // 前後輪をジョイントを生成する。
    this->setFRJoint(PhysicsJointDistance::construct(_rWheel->getPhysicsBody(),
                                                     _fWheel->getPhysicsBody(),
                                                     _rWheel->getPhysicsBody()->getPosition(),
                                                     _fWheel->getPhysicsBody()->getPosition()));
}

void Bike::update(float dt) {
    this->riderImageAction();
    this->_positionSyncToWheel();
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
    if(dV.x > 4 * riderActionSpan){
        touchPt1.x = touchPt2.x - 4 * riderActionSpan;
    }
    if(dV.x < - 4 * riderActionSpan){
        touchPt1.x = touchPt2.x + 4 * riderActionSpan;
    }
    if(dV.y > 4 * riderActionSpan){
        touchPt1.y = touchPt2.y - 4 * riderActionSpan;
    }
    if(dV.y < - 4 * riderActionSpan){
        touchPt1.y = touchPt2.y + 4 * riderActionSpan;
    }
    weightPt.set(touchPt2-touchPt1);
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

void Bike::_judeAction(float dt){
    
    // 左下で下方の動きがある場合は、初期化して処理を抜ける。
//    if(weightPt.x < -riderActionSpan && weightPt.y < -riderActionSpan){
//        if((weightPt - chasePt).y<0){
//            chasePt.set(weightPt);
//            return;
//        }
//    }
    
    // 領域とchasePtとの差分ベクトルにより処理や、その強度を変化させる。
    int lvlX_;
    int lvlY_;
    if(chasePt.x < -riderActionSpan * 2){
        lvlX_ = -2;
    }else if(chasePt.x >= -riderActionSpan * 2 && chasePt.x < 0){
        lvlX_ = -1;
    }else if(chasePt.x < riderActionSpan * 2 && chasePt.x >= 0){
        lvlX_ = 1;
    }else{
        lvlX_ = 2;
    }
    if(chasePt.y < -riderActionSpan * 2){
        lvlY_ = -2;
    }else if(chasePt.y >= -riderActionSpan * 2 && chasePt.y < 0){
        lvlY_ = -1;
    }else if(chasePt.y < riderActionSpan * 2 && chasePt.y >= 0){
        lvlY_ = 1;
    }else{
        lvlY_ = 2;
    }
    
    Vec2 noml_ = this->getCalc()->cordinaneX(Vec2(1,0), weightPt-chasePt);
    int lvl = 0;
    // 前後のウイリー
    if( chasePt.y >= -riderActionSpan){
        lvl = -abs(lvlY_);
        if(noml_.x > 5){
            this->werry(lvl * noml_.x);
            chasePt.set(weightPt);
            return;
        }else if(noml_.x < -5){
            this->werry(lvl * noml_.x);
            chasePt.set(weightPt);
            return;
        }
    }
    
    // 前方のウイリー
    if( chasePt.x >= riderActionSpan * 2){
        lvl = abs(lvlX_);
        if(noml_.y > 5){
            if(fWheelTouched && !rWheelTouched){
                this->jump(lvl * noml_.y);
                chasePt.set(weightPt);
            }else{
                this->werry(lvl * noml_.y);
                chasePt.set(weightPt);
            }
            return;
        }else if(noml_.y < -5){
            this->werry(lvl * noml_.y);
            chasePt.set(weightPt);
            return;
        }
    }
    
    // 後方のウイリーと後輪ジャンプ
    if( chasePt.x <= -riderActionSpan * 2){
        lvl = -abs(lvlX_);
        if(noml_.y > 5){
            if(rWheelTouched && !fWheelTouched){
                this->jump(lvl * noml_.y);
                chasePt.set(weightPt);
            }else{
                this->werry(lvl * noml_.y);
                chasePt.set(weightPt);
            }
            return;
        }else if(noml_.y < -5){
            this->werry(lvl * noml_.y);
            chasePt.set(weightPt);
            return;
        }
    }
    
    
    
    this->getCalc()->chasePt(weightPt , chasePt, chaseVelo, dt);
    this->getParentSprite()->setPosition(chasePt + bikeCenterPt);
    
    return;
    // ジャンプ or 前進
    if(chasePt.x < riderActionSpan*2 && chasePt.y < 0 ){
        if(noml_.y > 5){
            if(this->jump(lvlY_)){
                chasePt.set(weightPt);
            }
            return;
        }
        
    }
    
    if( chasePt.y < -riderActionSpan){
        if(noml_.x > 5){
            this->dush(-lvlY_);
            chasePt.set(weightPt);
            return;
        }
    }

    // 前方のウイリー
    if( chasePt.x >= riderActionSpan * 2){
        if(noml_.y > 5){
            this->werry(1);
            chasePt.set(weightPt);
            return;
        }else if(noml_.y < -5){
            this->werry(-1);
            chasePt.set(weightPt);
            return;
        }
    }
        
    // 後輪ブレーキ
    if(chasePt.x < -4 * riderActionSpan + 2 && chasePt.y < -4 * riderActionSpan + 2){
        stop();
        chasePt.set(weightPt);
        return;
    }
    
}


// bikeへの加重
void Bike::fWheelUp(float pow){
    Vec2 rfpt_ = _fWheel->getPosition()-_rWheel->getPosition();
    Vec2 dirPt_ = this->getCalc()->rotByRad(rfpt_, M_PI/2);
    Vec2 powPt = this->getCalc()->chgLength(dirPt_, pow);
    this->_fWheel->getPhysicsBody()->setVelocity(this->_fWheel->getPhysicsBody()->getVelocity() + powPt);
}

void Bike::fWheeldown(float pow){
    Vec2 rfpt_ = _fWheel->getPosition()-_rWheel->getPosition();
    Vec2 dirPt_ = this->getCalc()->rotByRad(rfpt_, -M_PI/2);
    Vec2 powPt = this->getCalc()->chgLength(dirPt_, pow);
    this->_fWheel->getPhysicsBody()->setVelocity(this->_fWheel->getPhysicsBody()->getVelocity() + powPt);
}

void Bike::rWheelUp(float pow){
    Vec2 rfpt_ = _fWheel->getPosition()-_rWheel->getPosition();
    Vec2 dirPt_ = this->getCalc()->rotByRad(rfpt_, M_PI/2);
    Vec2 powPt = this->getCalc()->chgLength(dirPt_, pow);
    this->_rWheel->getPhysicsBody()->setVelocity(this->_rWheel->getPhysicsBody()->getVelocity() + powPt);
}

void Bike::rWheeldown(float pow){
    Vec2 rfpt_ = _rWheel->getPosition()-_rWheel->getPosition();
    Vec2 dirPt_ = this->getCalc()->rotByRad(rfpt_, -M_PI/2);
    Vec2 powPt = this->getCalc()->chgLength(dirPt_, pow);
    this->_rWheel->getPhysicsBody()->setVelocity(this->_rWheel->getPhysicsBody()->getVelocity() + powPt);
}

void Bike::fWheelJump(float pow){
    if(fWheelTouched){
        Vec2 powPt = this->getCalc()->chgLength(fWheelTouchPt, pow);
        this->_fWheel->getPhysicsBody()->setVelocity(this->_fWheel->getPhysicsBody()->getVelocity() + powPt);
        this->_rWheel->getPhysicsBody()->setVelocity(this->_fWheel->getPhysicsBody()->getVelocity());
    }
}

void Bike::rWheelJump(float pow){
    if(rWheelTouched){
        Vec2 powPt = this->getCalc()->chgLength(rWheelTouchPt, -pow);
        this->_rWheel->getPhysicsBody()->setVelocity(this->_rWheel->getPhysicsBody()->getVelocity() + powPt);
        this->_fWheel->getPhysicsBody()->setVelocity(this->_rWheel->getPhysicsBody()->getVelocity());
    }
}

void Bike::rWheelRot(float pow){
    if(rWheelTouched){
        Vec2 powPt = this->getCalc()->chgLength(_fWheel->getPosition()-_rWheel->getPosition(), pow);
        this->_rWheel->getPhysicsBody()->setVelocity(this->_rWheel->getPhysicsBody()->getVelocity() + powPt);
        this->_fWheel->getPhysicsBody()->setVelocity(this->_fWheel->getPhysicsBody()->getVelocity() + powPt);
    }
    //    float velo = this->_rWheel->getPhysicsBody()->getAngularVelocity();
    //    NJLOG(ST_FLOAT(velo).c_str());
    //    velo += pow;
    //    this->_rWheel->getPhysicsBody()->setAngularVelocity(velo);
}

bool Bike::jump(float lvl){
    Vec2 powPt;
    if(rWheelTouched){
        if(fWheelTouched){
            powPt = this->getCalc()->chgLength(rWheelTouchPt, -frJumpPow + lvl);
        }else{
            powPt = this->getCalc()->chgLength(rWheelTouchPt, -rJumpPow + lvl);
        }
        this->_rWheel->getPhysicsBody()->setVelocity(this->_rWheel->getPhysicsBody()->getVelocity() + powPt);
        this->_fWheel->getPhysicsBody()->setVelocity(this->_rWheel->getPhysicsBody()->getVelocity());
    }else{
        if(fWheelTouched){
            powPt = this->getCalc()->chgLength(fWheelTouchPt, fJumpPow + lvl);
            this->_fWheel->getPhysicsBody()->setVelocity(this->_fWheel->getPhysicsBody()->getVelocity() - powPt);
            this->_rWheel->getPhysicsBody()->setVelocity(this->_fWheel->getPhysicsBody()->getVelocity());
        }else{
            return false;
        }
    }
    return true;
}

void Bike::werry(float lvl){
    Vec2 rfpt_ = _fWheel->getPosition()-_rWheel->getPosition();
    Vec2 dirPt_ = this->getCalc()->rotByRad(rfpt_, M_PI/2);
    Vec2 powPt = this->getCalc()->chgLength(dirPt_, weeryPow * lvl);
    this->_fWheel->getPhysicsBody()->setVelocity(this->_fWheel->getPhysicsBody()->getVelocity() + powPt);
    this->_rWheel->getPhysicsBody()->setVelocity(this->_rWheel->getPhysicsBody()->getVelocity() - powPt);
}

void Bike::fWerry(float lvl){
    Vec2 rfpt_ = _fWheel->getPosition()-_rWheel->getPosition();
    Vec2 dirPt_ = this->getCalc()->rotByRad(rfpt_, M_PI/2);
    Vec2 powPt = this->getCalc()->chgLength(dirPt_, weeryPow * lvl);
    this->_fWheel->getPhysicsBody()->setVelocity(this->_fWheel->getPhysicsBody()->getVelocity() + powPt);
}

void Bike::rWerry(float lvl){
    Vec2 rfpt_ = _fWheel->getPosition()-_rWheel->getPosition();
    Vec2 dirPt_ = this->getCalc()->rotByRad(rfpt_, -M_PI/2);
    Vec2 powPt = this->getCalc()->chgLength(dirPt_, weeryPow * lvl);
    this->_rWheel->getPhysicsBody()->setVelocity(this->_rWheel->getPhysicsBody()->getVelocity() + powPt);
}

void Bike::dush(float lvl){
    Vec2 powPt;
    if(rWheelTouched && rWheelTouched){
        Vec2 powPt = this->getCalc()->chgLength(_fWheel->getPosition()-_rWheel->getPosition(), dushPow * lvl);
        this->_rWheel->getPhysicsBody()->setVelocity(this->_rWheel->getPhysicsBody()->getVelocity() + powPt);
        this->_fWheel->getPhysicsBody()->setVelocity(this->_fWheel->getPhysicsBody()->getVelocity() + powPt);
        return;
    }
}

void Bike::stop(){
    _rWheel->getPhysicsBody()->setAngularVelocity(_rWheel->getPhysicsBody()->getAngularVelocity() * 0.8);
}

/** パラメータサンプル
 this->setRider(Sprite::create());
 this->getRider();
 this->setFwheel(Sprite::create());
 this->getFwheel();
 this->setRwheel(Sprite::create());
 this->getRwheel();
 */


