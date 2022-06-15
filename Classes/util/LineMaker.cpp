#include "LineMaker.h"
#include "cmath"

LineMaker::LineMaker():
_pt(NULL), _calc(NULL),_field(NULL), _wrkPt(Vec2::ZERO), _wrkDir(Vec2::ZERO), _trgPt(Vec2::ZERO), _trgDir(Vec2::ZERO)
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
        sp_->setGlobalZOrder(OBJ_LAYER_LV1);
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

void LineMaker::madeCircleLine(){
//    _dotSpriteCnt=0;
//    _linePtCnt=0;
    
    // workとtargetの交点
    ptA = _calc->getCrossPointLineA2B(_wrkPt,_wrkPt + _wrkDir, _trgPt, _trgPt + _trgDir);
    NJLOG(ST_VEC2(ptA).c_str());
    Vec2 ptA_dir = _calc->nomalizeVec2(_wrkPt-ptA) + _calc->nomalizeVec2(_trgPt-ptA);
    NJLOG("ptA_dir");
    NJLOG(ST_VEC2(ptA_dir).c_str());
    
    // workポイントの中心点
    ptA_wrk = _calc->getCrossPointLineA2B(ptA,
                                          ptA + ptA_dir,
                                          _wrkPt,
                                          _wrkPt + _calc->rotByRad(_wrkDir, M_PI/2));
    
    // targetポイントの中心点
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
        addLinePts(stPt_ctPt + ctPt);
    }
    
    Vec2 edPt_ctPt;
    if((ptA_wrk - ptA).length() < (ptA_trg - ptA).length()){
        edPt_ctPt = _calc->getMirrorPointLineA(ptA,ptA + ptA_dir,_wrkPt)-ctPt;
    }else{
        edPt_ctPt = _trgPt - ctPt;
    }
    
    bool rotLeft = _calc->chkLeft(_wrkPt, _wrkDir,ctPt);
    float r = stPt_ctPt.length();
    float drad = rotLeft ? porigonPich/r : -porigonPich/r;
    float diffRad = _calc->diffRadA2B(stPt_ctPt,edPt_ctPt,rotLeft);
    int i = 1;
    while(abs(drad * i) < abs(diffRad)){
        addLinePts(_calc->rotByRad(stPt_ctPt, drad * i) + ctPt);
        i++;
    }
    addLinePts(_trgPt);
}


/** パラメータサンプル
 this->setPt(Sprite2::create());
 this->getPt();
 this->setCalc(CalcLater::create());
 this->getCalc();
 */
