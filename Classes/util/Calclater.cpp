#include "Calclater.h"

Calclater::Calclater(){}

Calclater::~Calclater(){
}

Calclater* Calclater::create() {
    auto obj = new Calclater;
    if (obj && obj->init()) {
        obj->autorelease();
    } else {
        CC_SAFE_DELETE(obj);
        return nullptr;
    }
}

bool Calclater::init() {
    // todo
    return true;
}

void Calclater::onEnterTransitionDidFinish() {
    // todo
}

void Calclater::update(float dt) {
    // todo
}

float Calclater::chgKaku(float rad) {
    float x_ = -CC_RADIANS_TO_DEGREES(rad);
    return nomlKaku(x_);
}

float Calclater::nomlKaku(Vec2 pt1, Vec2 pt2){
    Vec2 dpt = pt2 - pt1;
    float angle = atan2f(dpt.y, dpt.x);
    if (std::abs(angle) < FLT_EPSILON) return 0.f;
    return chgKaku(angle);
}

float Calclater::chgRad(float kaku) {
    float x_ = -CC_DEGREES_TO_RADIANS(kaku);
    return nomlRad(x_);
}

float Calclater::nomlKaku(float kaku) {
    float x_ = kaku;
    while (x_ >= 360) {
        x_ -= 360;
    }
    while (x_ < 0) {
        x_ += 360;
    }
    return x_;
}

float Calclater::nomlRad(float rad) {
    float x_ = rad;
    while (x_ >= 2 * M_PI) {
        x_ -= 2 * M_PI;
    }
    while (x_ < 0) {
        x_ += 2 * M_PI;
    }
    return x_;
}

float Calclater::nomlRad(Vec2 pt1, Vec2 pt2){
    Vec2 dpt = pt2 - pt1;
    float angle = atan2f(dpt.y, dpt.x);
    if (std::abs(angle) < FLT_EPSILON) return 0.f;
    return angle;
}

bool Calclater::betweenKaku(float x, float min_, float max_) {
    min_ = nomlKaku(min_);
    max_ = nomlKaku(max_);
    x = nomlKaku(x);
    if (min_ < max_) {
        if ((min_ < x) && (max_ > x)) {
            return true;
        } else {
            return false;
        }
    } else {
        if ((max_ > x && x >= 0) || (min_ < x && x <= 360)) {
            return true;
        } else {
            return false;
        }
    }
}

bool Calclater::betweenRad(float x, float min_, float max_) {
    min_ = nomlRad(min_);
    max_ = nomlRad(max_);
    x = nomlRad(x);
    if (min_ < max_) {
        if ((min_ < x) && (max_ > x)) {
            return true;
        } else {
            return false;
        }
    } else {
        if ((max_ > x && x >= 0) || (min_ < x && x <= 2 * M_PI)) {
            return true;
        } else {
            return false;
        }
    }
}

float Calclater::getDot(Vec2 A, Vec2 B) {
    return (A.x*B.x+A.y*B.y);
}

// 親が所属する座標系でのポジションを算出
Vec2 Calclater::getParentNodePosition(Node* nd){
    if(!nd->getParent()){
        return nd->getPosition();
    }
    Vec2 parentPt = nd->getParent()->getPosition();
    Vec2 parentAnchorPt = Vec2(nd->getParent()->getContentSize().width * nd->getParent()->getAnchorPoint().x,
                               nd->getParent()->getContentSize().height * nd->getParent()->getAnchorPoint().y);
    Vec2 localPt = nd->getPosition() - parentAnchorPt;
    
    float parentAngle = nd->getParent()->getRotation();
    localPt = localPt.rotateByAngle(Vec2::ZERO, parentAngle);
    return parentPt + localPt;
}

// 指定したラジアン分回転する。反時計回り
Vec2 Calclater::rotByRad(Vec2 pt,float rad){
    return Vec2(cos(rad)*pt.x-sin(rad)*pt.y, sin(rad)*pt.x+cos(rad)*pt.y);
}

// 指定した角度分回転する。時計回り
Vec2 Calclater::rotByKaku(Vec2 pt,float kaku){
    float rad = chgRad(kaku);
    return rotByRad(pt, rad);
}

Vec2 Calclater::chgLength(Vec2 pt,float length){
    float l = pt.getLength();
    if(l==0){
        return pt;
    }
    return pt * (length / l);
}

Vec2 Calclater::chasePt(Vec2 destPt,Vec2& chasePt,float velo,float dt){
    
    Vec2 dst_ = destPt - chasePt;
    Vec2 ch_ = chgLength(dst_, velo*dt);
    if(dst_.length()>ch_.length()){
        chasePt += ch_;
        return destPt - chasePt;
    }else{
        chasePt.set(destPt);
        return Vec2::ZERO;
    }
}

Vec2 Calclater::chasePt(Vec2 destPt,Vec2& chasePt,float length){
    
    Vec2 dst_ = destPt - chasePt;
    Vec2 ch_ = chgLength(dst_, length);
    if(dst_.length()>ch_.length()){
        chasePt += ch_;
        return destPt - chasePt;
    }else{
        chasePt.set(destPt);
        return Vec2::ZERO;
    }
}

Vec2 Calclater::cordinaneX(Vec2 ptX, Vec2 pt){
    float rad = nomlRad(Vec2::ZERO, ptX);
    return rotByRad(pt, -rad);
}

/** パラメータサンプル
 */
