#include "Calclater.h"

Calclater::Calclater(){}

Calclater::~Calclater(){
}

//Calclater* Calclater::create() {
//    auto obj = new Calclater;
//    if (obj && obj->init()) {
//        obj->autorelease();
//    } else {
//        CC_SAFE_DELETE(obj);
//        return nullptr;
//    }
//}

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

float Calclater::chgKaku(Vec2 pt) {
    return nomlKaku(Vec2::ZERO,pt);
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

float Calclater::chgRad(Vec2 pt) {
    return nomlRad(Vec2::ZERO,pt);
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

Vec2 Calclater::nomalizeVec2(Vec2 pt){
    return chgLength(pt, 1);
}

Vec2 Calclater::getNodeDict(Node* nd){
    Vec2 nml = Vec2(1,0);
    return rotByKaku(nml, nd->getRotation());
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

Vec2 Calclater::getCrossPointLineA2B(Vec2 a1, Vec2 a2,Vec2 b1, Vec2 b2){
    
    Vec2 basePt = a2 - a1;
    NJLOG(ST_VEC2(a2).c_str());
    float basePt_rad = chgRad(basePt);
    NJLOG(ST_FLOAT(basePt_rad).c_str());
    Vec2 a2_ = rotByRad(a2-a1, -basePt_rad);
    Vec2 b1_ = rotByRad(b1-a1, -basePt_rad);
    Vec2 b2_ = rotByRad(b2-a1, -basePt_rad);
    
    float x_;
    if(b1_.y == b2_.y) {
        return Vec2::ZERO;
    }else{
        x_ = (b1_.x * b2_.y - b2_.x * b1_.y)/(b2_.y - b1_.y);
    }
    
    return a1 + rotByRad(Vec2(x_,0), basePt_rad);
}

// A→Bまで回転するための角度、leftFlg 反時計、左回り、座標系正回り
float Calclater::diffRadA2B(Vec2 A, Vec2 B, bool leftFlg){
    
    float radA = nomlRad(Vec2::ZERO, A);
    float radB = nomlRad(Vec2::ZERO, B);
    if (leftFlg){
        if (radA < radB){
            return radB - radA;
        }else{
            return 2 * M_PI - radB + radA;
        }
    }else{
        if (radA < radB){
            return 2 * M_PI - radB + radA;
        }else{
            return radB - radA;
        }
    }
}

// 指定の線分に対して対照のポイントを変える。
Vec2 Calclater::getMirrorPointLineA(Vec2 a1, Vec2 a2,Vec2 pt){
    Vec2 basePt = a2 - a1;
    NJLOG(ST_VEC2(a2).c_str());
    float basePt_rad = chgRad(basePt);
    NJLOG(ST_FLOAT(basePt_rad).c_str());
    Vec2 pt_ = rotByRad(pt-a1, -basePt_rad);
    pt_.y *= -1;
    return a1 + rotByRad(pt_, basePt_rad);
}

bool Calclater::chkLeft(Vec2 pt, Vec2 dst,Vec2 chkPt){
    Vec2 basePt = pt + dst - pt;
    float basePt_rad = chgRad(basePt);

    Vec2 pt_ = rotByRad(chkPt-pt, -basePt_rad);
    
    return pt_.y>0;
}

/** パラメータサンプル
 */
