#include "LineMaker.h"
#include "cmath"

LineMaker::LineMaker():
_pt(NULL), _calc(NULL)
{}

LineMaker::~LineMaker() {
    CC_SAFE_RELEASE_NULL(_pt);
    CC_SAFE_RELEASE_NULL(_calc);
}

LineMaker* LineMaker::create() {
    auto obj = new LineMaker;
    if (obj && obj->init()) {
        obj->autorelease();
        return obj;
    } else {
        CC_SAFE_DELETE(obj);
        return nullptr;
    }
}

bool LineMaker::init() {
    // todo
    this->setPt(Sprite2::create("dot2.png"));
    this->setCalc(CalcLater::create());
    return true;
}

void LineMaker::onEnterTransitionDidFinish() {
    // todo
}

void LineMaker::update(float dt) {
    // todo
}

void LineMaker::addLinePts(Vec2 pt_) {
    Vector<Sprite*> _dotSprites;
    int _dotSpriteCnt = 0;
    if (this->_dotSprites.size() <= _dotSpriteCnt) {
        auto sp_ = Sprite::createWithTexture(this->getPt()->get);
        this->_dotSprites.pushBack(sp_);
        sp_->setPosition(pt_);
        this->addChild(sp_);
    } else {
        this->_dotSprites.at(_dotSpriteCnt)->setPosition(pt_);
    }
    _dotSpriteCnt++;
    _wrkPt.set(pt_);
    
    _linePts[_linePtCnt].set(pt_);
    _linePtCnt++;
}

void LineMaker::madeCurve(int w, int h, float endRad){
    //幅ｗ、高さhのコブ、穴を作る。drad曲率
    float rad2 = 0;
    trgPt1.set(_wrkPt);
    while (rad2 < endRad) {
        trgPt2.set(this->SinLength(h / 2, w, rad2, 5, endRad));
//        trgPt2.rotate(Vec2::ZERO, madePt.getAngle());
        this->addLinePts(trgPt1 + trgPt2);
    }
}

Vec2 LineMaker::moveSin(float r, float w, float rad1, int dl, float endrad) {
    //１周期幅：w、半径ｒのSinで、現在rad1の位置から、dlだけ遠い位置の点を算出する。
    Vec2 nowPt;
    Vec2 nextPt;
    float drad = 0;
    nowPt.set(w * (rad1 / (2 * M_PI)), r * (-cos(rad1) + 1));
    nextPt.set(w * ((rad1 + drad) / (2 * M_PI)), r * (-cos(rad1 + drad) + 1));
    
    while ((nextPt - nowPt).length() < dl && (rad1 + drad) < endrad) {
        drad += 0.01f;
        nextPt.set(w * ((rad1 + drad) / (2 * M_PI)), r * (-cos(rad1 + drad) + 1));
    }
    
    rad2 = rad1 + drad;
    if (rad2 >= endrad) {
        nextPt.set(w * ((endrad) / (2 * M_PI)), r * (-cos(endrad) + 1));
        rad2 = endrad;
    }
    return nextPt;
}
/** パラメータサンプル
 this->setPt(Sprite2::create());
 this->getPt();
 this->setCalc(CalcLater::create());
 this->getCalc();
 */
