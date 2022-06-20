#include "CurveLine.h"

CurveLine::CurveLine():
_straightA(NULL), _straightB(NULL), _dot(NULL), _curveA(NULL), _curveB(NULL), _curveC(NULL), _curveD(NULL), _curveE(NULL), _curveF(NULL)
{}

CurveLine::~CurveLine() {
    CC_SAFE_RELEASE_NULL(_straightA);
    CC_SAFE_RELEASE_NULL(_straightB);
    CC_SAFE_RELEASE_NULL(_dot);
    CC_SAFE_RELEASE_NULL(_curveA);
    CC_SAFE_RELEASE_NULL(_curveB);
    CC_SAFE_RELEASE_NULL(_curveC);
    CC_SAFE_RELEASE_NULL(_curveD);
    CC_SAFE_RELEASE_NULL(_curveE);
    CC_SAFE_RELEASE_NULL(_curveF);
}

CurveLine* CurveLine::create() {
    auto obj = new CurveLine;
    if (obj && obj->init()) {
        obj->autorelease();
        return obj;
    } else {
        CC_SAFE_DELETE(obj);
        return nullptr;
    }
}

bool CurveLine::init() {
    if(!Sprite2::initWithFile("c_dot.png")){
        return false;
    }
    this->setStraightA(StraightLine::create());
    this->setStraightB(StraightLine::create());
    _length = _straightA->getContentSize().width;
    
    this->setDot(SpriteBatchNode::create("c_dot.png"));

    this->setCurveA(Sprite::create("c_curve_a.png"));

  return true;
}

void CurveLine::onEnterTransitionDidFinish() {
    // todo
}

void CurveLine::update(float dt) {
    // todo
}

void CurveLine::drawCurve(Vec2 pt1,Vec2 dir1, Vec2 pt2, Vec2 dir2 ,float r_){
    
    if(!_straightA->getParent()){
        this->getParent()->addChild(_straightA);
    }
    if(!_straightB->getParent()){
        this->getParent()->addChild(_straightB);
    }
    
    this->setWorkPt(pt1);
    this->setWorkDir(dir1);
    this->setTergetPt(pt2);
    this->setTargetDir(dir2);
    // workとtargetの交点
    Vec2 ptA = this->getCalc()->getCrossPointLineA2B(_wrkPt,_wrkPt + _wrkDir, _trgPt, _trgPt + _trgDir);
    NJLOG(ST_VEC2(ptA).c_str());
    Vec2 ptA_dir = this->getCalc()->nomalizeVec2(_wrkPt-ptA) + this->getCalc()->nomalizeVec2(_trgPt-ptA);
    NJLOG("ptA_dir");
    NJLOG(ST_VEC2(ptA_dir).c_str());
        
    // workポイントの中心点
    Vec2 ptA_wrk = this->getCalc()->getCrossPointLineA2B(ptA,
                                          ptA + ptA_dir,
                                          _wrkPt,
                                          _wrkPt + this->getCalc()->rotByRad(_wrkDir, M_PI/2));
    
    // targetポイントの中心点
    Vec2 ptA_trg = this->getCalc()->getCrossPointLineA2B(ptA,
                                          ptA + ptA_dir,
                                          _trgPt,
                                          _trgPt + this->getCalc()->rotByRad(_trgDir, M_PI/2));
    
    // r_の位置の中心点とwrkとtrgそれぞれの接点
    float dl_ = (_wrkPt - ptA_wrk).length();
    float dl2_ = (_trgPt - ptA_trg).length();
    Vec2 ptA2ptr_ = (ptA_wrk - ptA) * r_/dl_;
    Vec2 ptr_ = ((ptA_wrk-ptA) * r_/dl_) + ptA;
    Vec2 ptr_wrk = ((_wrkPt - ptA) * r_/dl_) + ptA;
    Vec2 ptr_trg = ((_trgPt - ptA) * r_/dl2_) + ptA;
    
    // 円弧の中心絶対位置
    Vec2 ctPt;
    if(r_<0 || r_/dl_ > 1 || r_/dl2_ > 1){
        if((ptA_wrk - ptA).length() < (ptA_trg - ptA).length()){
            ctPt = ptA_wrk;
        }else{
            ctPt = ptA_trg;
        }
    }else{
        ctPt = ptr_;
    }
    
    Vec2 stPt_ctPt;
    Vec2 edPt_ctPt;
    if(r_< 0 || r_/dl_ > 1 || r_/dl2_ > 1){
        if((ptA_wrk - ptA).length() < (ptA_trg - ptA).length()){
            stPt_ctPt = _wrkPt - ctPt;
            edPt_ctPt = this->getCalc()->getMirrorPointLineA(ptA,ptA + ptA_dir,_wrkPt)-ctPt;
        }else{
            stPt_ctPt = this->getCalc()->getMirrorPointLineA(ptA,ptA + ptA_dir,_trgPt)-ctPt;
            edPt_ctPt = _trgPt - ctPt;
        }
    }else{
        stPt_ctPt = ptr_wrk - ctPt;
        edPt_ctPt = ptr_trg - ctPt;
    }
    
    // カーブまでの直線部を描写する。
    if(r_<0 || r_/dl_ > 1 || r_/dl2_ > 1){
        // r_が無効の場合。最大曲率が適用される。
        _straightA->drawLine(_wrkPt, stPt_ctPt + ctPt);
        _straightB->drawLine(edPt_ctPt + ctPt, _trgPt);
        
    }else{
        _straightA->drawLine(_wrkPt, ptr_wrk);
        _straightB->drawLine(ptr_trg ,_trgPt);
    }
    
    // 円弧の部分を描写する。
    bool rotLeft = this->getCalc()->chkLeft(_wrkPt, _wrkDir,ctPt);
    float r;
    if(r_<0 || r_/dl_ > 1 || r_/dl2_ > 1){
        r = stPt_ctPt.length();
    }else{
        r = r_;
    }
    float drad = rotLeft ? _drawPitch/r : -_drawPitch/r;
    float diffRad = this->getCalc()->diffRadA2B(stPt_ctPt,edPt_ctPt,rotLeft);
    int i = 1;
    
    while(abs(drad * i) < abs(diffRad)){
        auto dot = Sprite::createWithTexture(_dot->getTexture());
        dot->setGlobalZOrder(OBJ_LAYER_TOP);
        dot->setPosition(this->getCalc()->rotByRad(stPt_ctPt, drad * i) + ctPt);
        this->getParent()->addChild(dot);
        i++;
    }
    
    float dradp = rotLeft ? _polygonPitch/r : -_polygonPitch/r;
    float diffRadp = this->getCalc()->diffRadA2B(stPt_ctPt,edPt_ctPt,rotLeft);
    int ip = 1;
    
    addPolygonPts(_wrkPt);
    i = 0;
    while(abs(dradp * i) < abs(diffRadp)){
        addPolygonPts(this->getCalc()->rotByRad(stPt_ctPt, dradp * i) + ctPt);
        i++;
    }
    addPolygonPts(edPt_ctPt + ctPt);
    addPolygonPts(_trgPt);
}

void CurveLine::addPolygonPts(Vec2 pt_) {
    _polygonPts[_polygonPtCnt].set(pt_);
    _polygonPtCnt++;
}
/** パラメータサンプル
this->setStraightA(Sprite::create());
this->getStraightA();
this->setStraightB(Sprite::create());
this->getStraightB();
this->setDot(SpriteBatchNode*::create());
this->getDot();
this->setCurveA(Sprite::create());
this->getCurveA();
this->setCurveB(Sprite::create());
this->getCurveB();
this->setCurveC(Sprite::create());
this->getCurveC();
this->setCurveD(Sprite::create());
this->getCurveD();
this->setCurveE(Sprite::create());
this->getCurveE();
this->setCurveF(Sprite::create());
this->getCurveF();
*/
