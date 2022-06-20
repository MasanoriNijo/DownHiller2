#include "StraightLine.h"

StraightLine::StraightLine():
_fDot(NULL), _rDot(NULL)
{}

StraightLine::~StraightLine() {
    CC_SAFE_RELEASE_NULL(_fDot);
    CC_SAFE_RELEASE_NULL(_rDot);
}

StraightLine* StraightLine::create() {
    auto obj = new StraightLine;
    if (obj && obj->init()) {
        obj->autorelease();
        return obj;
    } else {
        CC_SAFE_DELETE(obj);
        return nullptr;
    }
}

bool StraightLine::init() {
    if(!Sprite2::initWithFile("c_straight.png")){
        return false;
    }
    this->setGlobalZOrder(OBJ_LAYER_TOP);
    _length = this->getContentSize().width;
    this->setAnchorPoint(Vec2(0,0.5));
    this->setFDot(Sprite::create("c_dot.png"));
    _fDot->setGlobalZOrder(OBJ_LAYER_TOP);
    this->setRDot(Sprite::create("c_dot.png"));
    _rDot->setGlobalZOrder(OBJ_LAYER_TOP);
  return true;
}

void StraightLine::onEnterTransitionDidFinish() {
  // todo
}

void StraightLine::update(float dt) {
  // todo
}

void StraightLine::drawLine(Vec2 pt1, Vec2 pt2){
    
    if(!_fDot->getParent()){
        this->getParent()->addChild(_fDot);
    }
    if(!_rDot->getParent()){
        this->getParent()->addChild(_rDot);
    }
    _fDot->setPosition(pt1);
    _rDot->setPosition(pt2);
    
    Vec2 destPt_ = pt2-pt1;
    _wrkPt.set(pt1);
    _wrkDir.set(destPt_);
    _trgPt.set(pt2);
    _trgDir.set(destPt_);
    
    this->setScaleX(destPt_.length()/_length);
    this->setRotation(this->getCalc()->chgKaku(destPt_));
    this->setPosition(pt1);
}

/** パラメータサンプル
this->setFDot(Sprite::create());
this->getFDot();
this->setRDot(Sprite::create());
this->getRDot();
*/
