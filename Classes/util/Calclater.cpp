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
    float x = pt1.getAngle(pt2);
    return chgKaku(pt1.getAngle(pt2));
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
    return nomlRad(pt1.getAngle(pt2));
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


/** パラメータサンプル
 */
