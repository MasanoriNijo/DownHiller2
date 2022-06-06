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
_fWheel(NULL), _rWheel(NULL), _BikeState(BikeState::NOML)
{}

Bike::~Bike() {
    CC_SAFE_RELEASE_NULL(_fWheel);
    CC_SAFE_RELEASE_NULL(_rWheel);
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
    if(!Sprite2::initWithFile("riders.png")){
        return false;
    }
    this->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    frameSize = Size(this->getContentSize().width / 7, this->getContentSize().height / 7);
    riderCenterPt.set(frameSize.width/2,frameSize.height/2);
    this->riderImageAction();
    this->scheduleUpdate();
    
    //debug
    this->setDebugPt(Sprite::create("dot3.png"));
    this->addChild(this->getDebugPt());
    return true;
}

void Bike::onEnterTransitionDidFinish() {
    // todo
    this->scheduleUpdate();
}

void Bike::update(float dt) {
    this->riderImageAction();
    // todo
}

void Bike::touchOn(Vec2 pt){
    touchPt1.set(pt);
    touchPt2.set(pt);
}

void Bike::swaip(Vec2 pt){
    touchPt2.set(pt);
    weightPt.set(touchPt2-touchPt1);
}

void Bike::touchOff(Vec2 pt){
    touchPt1.set(pt);
    touchPt2.set(pt);
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
        this->getDebugPt()->setPosition(weightPt+riderCenterPt);
    }
    
    this->setTextureRect(
                Rect(frameSize.width * (x_+3), frameSize.height * (y_+3), frameSize.width, frameSize.height));
}
/** パラメータサンプル
 this->setFwheel(Sprite::create());
 this->getFwheel();
 this->setRwheel(Sprite::create());
 this->getRwheel();
 */


