#include "LineMaker.h"
#include "cmath"

LineMaker::LineMaker():
_pt(NULL), _calc(NULL),_field(NULL)
{}

LineMaker::~LineMaker() {
    CC_SAFE_RELEASE_NULL(_pt);
    CC_SAFE_RELEASE_NULL(_calc);
    CC_SAFE_RELEASE_NULL(_field);
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
    this->setCalc(Calclater::create());
    return true;
}

void LineMaker::onEnterTransitionDidFinish() {
    // todo
}

void LineMaker::update(float dt) {
    // todo
}

void LineMaker::addLinePts(Vec2 pt_) {
    if (this->_dotSprites.size() <= _dotSpriteCnt) {
        auto sp_ = Sprite::createWithTexture(this->getPt()->getTexture());
        this->_dotSprites.pushBack(sp_);
        sp_->setPosition(pt_);
        _field->addChild(sp_);
    } else {
        this->_dotSprites.at(_dotSpriteCnt)->setPosition(pt_);
    }
    _dotSpriteCnt++;
    _wrkPt.set(pt_);
    
    _linePts[_linePtCnt].set(pt_);
    _linePtCnt++;
}

void LineMaker::calcA(){
    _dotSpriteCnt=0;
    _linePtCnt=0;
    
    ptA = _calc->getCrossPointLineA2B(_wrkPt,_wrkPt + _wrkDir, _trgPt, _trgPt + _trgDir);
    NJLOG(ST_VEC2(ptA).c_str());
    Vec2 ptA_dir = _calc->nomalizeVec2(_wrkPt-ptA) + _calc->nomalizeVec2(_trgPt-ptA);
    NJLOG("ptA_dir");
    NJLOG(ST_VEC2(ptA_dir).c_str());
    ptA_wrk = _calc->getCrossPointLineA2B(ptA,
                                          ptA + ptA_dir,
                                          _wrkPt,
                                          _wrkPt + _calc->rotByRad(_wrkDir, M_PI/2));
    ptA_trg = _calc->getCrossPointLineA2B(ptA,
                                          ptA + ptA_dir,
                                          _trgPt,
                                          _trgPt + _calc->rotByRad(_trgDir, M_PI/2));
    
    Vec2 ctPt;
    if((ptA_wrk - ptA).length() < (ptA_trg - ptA).length()){
        ctPt = ptA_wrk;
    }else{
        ctPt = ptA_trg;
    }
    
    Vec2 stPt_ctPt;
    if((ptA_wrk - ptA).length() < (ptA_trg - ptA).length()){
        stPt_ctPt = _wrkPt - ctPt;
    }else{
        stPt_ctPt = _calc->getMirrorPointLineA(ptA,ptA + ptA_dir,_trgPt)-ctPt;
    }
    
    Vec2 edPt_ctPt;
    if((ptA_wrk - ptA).length() < (ptA_trg - ptA).length()){
        edPt_ctPt = _calc->getMirrorPointLineA(ptA,ptA + ptA_dir,_wrkPt)-ctPt;
    }else{
        edPt_ctPt = _trgPt - ctPt;
    }
    
    bool rotLeft = _calc->chkLeft(_wrkPt, _wrkDir,ctPt);
    float drad = rotLeft ? 0.1 : -0.1;
    int i = 0;
    while(i<1000 && abs(_calc->diffRadA2B(edPt_ctPt,stPt_ctPt))>=abs(drad)){
        stPt_ctPt = _calc->rotByRad(stPt_ctPt, drad);
        addLinePts(stPt_ctPt + ctPt);
        i++;
    }
}

//void LineMaker::madeCurve(int w, int h, float endRad){
//    //幅ｗ、高さhのコブ、穴を作る。drad曲率
//    float rad2 = 0;
//    trgPt1.set(_wrkPt);
//    while (rad2 < endRad) {
//        trgPt2.set(this->SinLength(h / 2, w, rad2, 5, endRad));
////        trgPt2.rotate(Vec2::ZERO, madePt.getAngle());
//        this->addLinePts(trgPt1 + trgPt2);
//    }
//}

//Vec2 LineMaker::moveSin(float r, float w, float rad1, int dl, float endrad) {
//    //１周期幅：w、半径ｒのSinで、現在rad1の位置から、dlだけ遠い位置の点を算出する。
//    Vec2 nowPt;
//    Vec2 nextPt;
//    float drad = 0;
//    nowPt.set(w * (rad1 / (2 * M_PI)), r * (-cos(rad1) + 1));
//    nextPt.set(w * ((rad1 + drad) / (2 * M_PI)), r * (-cos(rad1 + drad) + 1));
//
//    while ((nextPt - nowPt).length() < dl && (rad1 + drad) < endrad) {
//        drad += 0.01f;
//        nextPt.set(w * ((rad1 + drad) / (2 * M_PI)), r * (-cos(rad1 + drad) + 1));
//    }
//
//    rad2 = rad1 + drad;
//    if (rad2 >= endrad) {
//        nextPt.set(w * ((endrad) / (2 * M_PI)), r * (-cos(endrad) + 1));
//        rad2 = endrad;
//    }
//    return nextPt;
//}
/** パラメータサンプル
 this->setPt(Sprite2::create());
 this->getPt();
 this->setCalc(CalcLater::create());
 this->getCalc();
 */
