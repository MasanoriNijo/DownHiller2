#include "Bike.h"
#include "audio/include/AudioEngine.h"

// 物理判定用 todo 他にまとめて整理する。
static const int NONE = 0x00000000;
static const int PLAYER = 0xFFFFFFFF;
static const int ENEMY = 0xFFFFFFFF;
static const int COURCE = 0xFFFFFFFF;
static const int ITEM = 0xFFFFFFFF;
static const int PLAYERBOUND = 0xFFFFFFFF;
static const int PLAYERBODY = 0xFFFFFFFF;
static const int ALL = 0xFFFFFFFF;

Bike::Bike():
_rider(NULL),_fWheel(NULL), _rWheel(NULL), _BikeState(BikeState::NOML)
{}

Bike::~Bike() {
    CC_SAFE_RELEASE_NULL(_rider);
    CC_SAFE_RELEASE_NULL(_fWheel);
    CC_SAFE_RELEASE_NULL(_rWheel);
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
    this->addChild(_rider);
    this->riderImageAction();
    
    // wheelをセットする。
    this->setFwheel(Sprite::create("wheel3.png"));
    _fWheel->setPosition(Vec2(33,2));
    _addPhysicsToWheel(_fWheel);
    
    this->setRwheel(Sprite::createWithTexture(_fWheel->getTexture()));
    _rWheel->setPosition(Vec2(1,2));
    _addPhysicsToWheel(_rWheel);
    
    this->_setTouchEvent();
    
    //debug
    this->setDebugPt(Sprite::create("dot3.png"));
    this->addChild(this->getDebugPt());
    return true;
}

void Bike::_addPhysicsToWheel(Sprite* _wheel){
    _wheel->setPhysicsBody(PhysicsBody::createCircle(_wheel->getContentSize().width / 2));
    _wheel->getPhysicsBody()->setGravityEnable(true);
    //    _wheel->getPhysicsBody()->setCategoryBitmask(ChrPrm::PLAYER);
    //    _wheel->getPhysicsBody()->setCollisionBitmask(ChrPrm::COURCE);
    //    _wheel->getPhysicsBody()->setContactTestBitmask(ChrPrm::ENEMY | ChrPrm::ITEM);
    _wheel->getPhysicsBody()->setTag(1);
    _wheel->getPhysicsBody()->setDynamic(true);
    //    _wheel->getPhysicsBody()->setAngularDamping(wheelRotDump_);
    //    _wheel->getPhysicsBody()->setLinearDamping(veloDump);
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
    // todo
}

void Bike::touchOn(Vec2 pt){
    touchPt1.set(pt);
    touchPt2.set(pt);
    weightPt.set(Vec2::ZERO);
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
    
    this->getRider()->setTextureRect(
                                     Rect(frameSize.width * (x_+3), frameSize.height * (y_+3), frameSize.width, frameSize.height));
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

void Bike::rWheelJump(float pow){
    if(rWheelTouched){
        Vec2 powPt = this->getCalc()->chgLength(rWheelTouchPt, pow);
        this->_rWheel->getPhysicsBody()->setVelocity(this->_rWheel->getPhysicsBody()->getVelocity() + powPt);
    }
}
/** パラメータサンプル
 this->setRider(Sprite::create());
 this->getRider();
 this->setFwheel(Sprite::create());
 this->getFwheel();
 this->setRwheel(Sprite::create());
 this->getRwheel();
 */


