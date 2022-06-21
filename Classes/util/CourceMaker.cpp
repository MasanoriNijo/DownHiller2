#include "CourceMaker.h"

CourceMaker::CourceMaker():
_calc(NULL),_dot(NULL), _straight(NULL),
_curveA(NULL), _curveB(NULL), _curveC(NULL), _curveD(NULL), _curveE(NULL), _curveF(NULL),
_courceBody(NULL)
{}

CourceMaker::~CourceMaker() {
    CC_SAFE_RELEASE_NULL(_calc);
    CC_SAFE_RELEASE_NULL(_dot);
    CC_SAFE_RELEASE_NULL(_straight);
    CC_SAFE_RELEASE_NULL(_curveA);
    CC_SAFE_RELEASE_NULL(_curveB);
    CC_SAFE_RELEASE_NULL(_curveC);
    CC_SAFE_RELEASE_NULL(_curveD);
    CC_SAFE_RELEASE_NULL(_curveE);
    CC_SAFE_RELEASE_NULL(_curveF);
    CC_SAFE_RELEASE_NULL(_courceBody);
    getMember().clear();
    //    _clearMember();
}

//void CourceMaker::release(){
//    CC_SAFE_RELEASE_NULL(_calc);
//    CC_SAFE_RELEASE_NULL(_dot);
//    CC_SAFE_RELEASE_NULL(_straight);
//    CC_SAFE_RELEASE_NULL(_curveA);
//    CC_SAFE_RELEASE_NULL(_curveB);
//    CC_SAFE_RELEASE_NULL(_curveC);
//    CC_SAFE_RELEASE_NULL(_curveD);
//    CC_SAFE_RELEASE_NULL(_curveE);
//    CC_SAFE_RELEASE_NULL(_curveF);
//    CC_SAFE_RELEASE_NULL(_courceBody);
//    _clearMember();
//}

void CourceMaker::_clearMember(){
    //    _member.clear();
    //    while(_member.size()>0) {
    //        _member.popBack();
    //    }
    //    _polygonPts.clear();
    //    while(_polygonPts.size()>0) {
    //        _polygonPts.popBack();
    //    }
}

bool CourceMaker::init() {
    
    if(!Node::init()){
        return false;
    }
    setCalc(Calclater::create());
    setDot(SpriteBatchNode::create("c_dot.png"));
    getDot()->setGlobalZOrder(OBJ_LAYER_TOP);
    addChild(getDot());
    
    setStraight(SpriteBatchNode::create("c_straight.png"));
    getStraight()->setGlobalZOrder(OBJ_LAYER_TOP);
    _length = getStraight()->getTexture()->getContentSize().width;
    addChild(getStraight());
    
    setCurveA(SpriteBatchNode::create("c_curve_a.png"));
    addChild(getCurveA());
    
    setMark(SpriteBatchNode::create("mark.png"));
    getMark()->setGlobalZOrder(OBJ_LAYER_TOP);
    addChild(getMark());
    
    return true;
}

void CourceMaker::onEnterTransitionDidFinish() {
    // todo
}

void CourceMaker::update(float dt) {
    // todo
}

void CourceMaker::drawStart(Vec2 pt_, Vec2 dir_){
    this->setWorkPt(pt_);
    this->setWorkDir(dir_);
    this->setTergetPt(pt_);
    this->setTargetDir(dir_);
    _polygonPtCnt = 0;
    addDot(pt_);
    addPolygonPts(_wrkPt);
}
void CourceMaker::drawTo(Vec2 pt_, Vec2 dir_){
    this->setWorkPt(_trgPt);
    this->setWorkDir(_trgDir);
    this->setTergetPt(pt_);
    this->setTargetDir(dir_);
    calcCurve(_wrkPt, _wrkDir, _trgPt, _trgDir, -1);
}


void CourceMaker::calcCurve(Vec2 pt1,Vec2 dir1, Vec2 pt2, Vec2 dir2 ,float r_){
    
    this->setWorkPt(pt1);
    this->setWorkDir(dir1);
    this->setTergetPt(pt2);
    this->setTargetDir(dir2);
    // workとtargetの交点
    Vec2 ptA = getCalc()->getCrossPointLineA2B(_wrkPt,_wrkPt + _wrkDir, _trgPt, _trgPt + _trgDir);
    
    // 折れ曲がるだけの場合
    if(ptA.equals(_trgPt)){
        addStraightLine(_wrkPt, _trgPt);
        addPolygonPts(_trgPt);
        return;
    }
    
    NJLOG(ST_VEC2(ptA).c_str());
    Vec2 ptA_dir = getCalc()->nomalizeVec2(_wrkPt-ptA) + getCalc()->nomalizeVec2(_trgPt-ptA);
    NJLOG("ptA_dir");
    NJLOG(ST_VEC2(ptA_dir).c_str());
    
    // workポイントの中心点
    Vec2 ptA_wrk = getCalc()->getCrossPointLineA2B(ptA,
                                                   ptA + ptA_dir,
                                                   _wrkPt,
                                                   _wrkPt + getCalc()->rotByRad(_wrkDir, M_PI/2));
    
    // targetポイントの中心点
    Vec2 ptA_trg = getCalc()->getCrossPointLineA2B(ptA,
                                                   ptA + ptA_dir,
                                                   _trgPt,
                                                   _trgPt + getCalc()->rotByRad(_trgDir, M_PI/2));
    
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
    bool reverseFlg = false;
    if(r_< 0 || r_/dl_ > 1 || r_/dl2_ > 1){
        if((ptA_wrk - ptA).length() < (ptA_trg - ptA).length()){
            stPt_ctPt = _wrkPt - ctPt;
            edPt_ctPt = getCalc()->getMirrorPointLineA(ptA,ptA + ptA_dir,_wrkPt)-ctPt;
        }else{
            stPt_ctPt = getCalc()->getMirrorPointLineA(ptA,ptA + ptA_dir,_trgPt)-ctPt;
            edPt_ctPt = _trgPt - ctPt;
        }
    }else{
        stPt_ctPt = ptr_wrk - ctPt;
        edPt_ctPt = ptr_trg - ctPt;
    }
    
    // カーブまでの直線部を描写する。
    // mark用に変数を保持
    Vec2 mrkStEdPt;
    Vec2 mrkEdStPt;
    if(r_<0 || r_/dl_ > 1 || r_/dl2_ > 1){
        // r_が無効の場合。最大曲率が適用される。
        addStraightLine(_wrkPt, stPt_ctPt + ctPt);
        addStraightLine(edPt_ctPt + ctPt, _trgPt);
        mrkStEdPt = stPt_ctPt + ctPt;
        mrkEdStPt = edPt_ctPt + ctPt;
        
    }else{
        addStraightLine(_wrkPt, ptr_wrk);
        addStraightLine(ptr_trg ,_trgPt);
        mrkStEdPt = ptr_wrk;
        mrkEdStPt = ptr_trg;
    }
    
    // 円弧の部分を描写する。
    bool rotLeft = getCalc()->chkLeft(_wrkPt, _wrkDir,ctPt);
    float r;
    if(r_<0 || r_/dl_ > 1 || r_/dl2_ > 1){
        r = stPt_ctPt.length();
    }else{
        r = r_;
    }
    float drad = rotLeft ? _drawPitch/r : -_drawPitch/r;
    float diffRad = getCalc()->diffRadA2B(stPt_ctPt,edPt_ctPt,rotLeft);
    int i = 1;
    
    while(abs(drad * i) < abs(diffRad)){
        addDot(getCalc()->rotByRad(stPt_ctPt, drad * i) + ctPt);
        i++;
    }
    if(r_<0 || r_/dl_ > 1 || r_/dl2_ > 1){
        addDot(edPt_ctPt + ctPt);
    }else{
        addDot(ptr_trg);
    }
    
    // カーブ部分へのmarkの追加
    if(markSetflg){
        addMarkStraight(_wrkPt, mrkStEdPt);
        addMarkCurve(ctPt,stPt_ctPt + ctPt,diffRad);
        addMarkStraight(mrkEdStPt, _trgPt);
    }
    
    // ポリゴンの追加
    float dradp = rotLeft ? _polygonPitch/r : -_polygonPitch/r;
    float diffRadp = getCalc()->diffRadA2B(stPt_ctPt,edPt_ctPt,rotLeft);
    int ip = 1;
    
    addPolygonPts(_wrkPt);
    i = 0;
    while(abs(dradp * i) < abs(diffRadp)){
        addPolygonPts(getCalc()->rotByRad(stPt_ctPt, dradp * i) + ctPt);
        i++;
    }
    if(r_<0 || r_/dl_ > 1 || r_/dl2_ > 1){
        addPolygonPts(edPt_ctPt + ctPt);
    }else{
        addPolygonPts(ptr_trg);
    }
    addPolygonPts(_trgPt);
}

void CourceMaker::addPolygonPts(Vec2 pt_) {
    // 前回と同じポリゴンの場合は、キャンセル。
    if(_polygonPtCnt && (_polygonPts[_polygonPtCnt-1]-pt_).length()<1){
        return;
    }
    _polygonPts[_polygonPtCnt].set(pt_);
    _polygonPtCnt++;
}

void CourceMaker::addStraightLine(Vec2 pt1_, Vec2 pt2_){
    Sprite* stline = Sprite::createWithTexture(getStraight()->getTexture());
    stline->setAnchorPoint(Vec2(0,0.5));
    stline->setScaleX((pt2_-pt1_).length()/_length);
    stline->setPosition(pt1_);
    stline->setRotation(getCalc()->chgKaku((pt2_-pt1_)));
    stline->setGlobalZOrder(OBJ_LAYER_TOP);
//    stline->setOpacity(95);
    getStraight()->addChild(stline);
    getMember().pushBack(stline);
    addDot(pt2_);
}

void CourceMaker::addDot(Vec2 pt_){
    Sprite* dot = Sprite::createWithTexture(getDot()->getTexture());
    dot->setGlobalZOrder(OBJ_LAYER_TOP);
    dot->setPosition(pt_);
    //    dot->setOpacity(0.2f);
    getDot()->addChild(dot);
    getMember().pushBack(dot);
}

void CourceMaker::addMarkStraight(Vec2 pt1_, Vec2 pt2_){
    Vec2 dirPt = pt2_- pt1_;
    if(dirPt.equals(Vec2::ZERO)){
        return;
    }
    Vec2 drawPt = pt1_ + getCalc()->chgLength(dirPt, _remindMarkPitch);
    while(getCalc()->cordinaneX(dirPt, drawPt - pt1_).x < dirPt.length()){
        Sprite* mark = Sprite::createWithTexture(getMark()->getTexture());
        mark->setAnchorPoint(Vec2(0.5,0.5));
        mark->setPosition(drawPt);
        mark->setRotation(getCalc()->chgKaku(dirPt));
        mark->setGlobalZOrder(OBJ_LAYER_TOP + 1);
        getMark()->addChild(mark);
        getMember().pushBack(mark);
        drawPt = drawPt + getCalc()->chgLength(dirPt, _markPitch);
    }
    _remindMarkPitch = getCalc()->cordinaneX(dirPt, drawPt - pt1_).x - dirPt.length();
}

void CourceMaker::addMarkCurve(Vec2 curveCenterPt,Vec2 fstPt,float rad){
    float r = (fstPt-curveCenterPt).length();
    if(r<1){
        return;
    }
    float pitchRad = _markPitch/r;
    float drawRad = _remindMarkPitch/r;
    float optRad = M_PI/2;
    if(rad<0){
        drawRad *=-1;
        pitchRad *=-1;
        while(rad<drawRad){
            Sprite* mark = Sprite::createWithTexture(getMark()->getTexture());
            mark->setAnchorPoint(Vec2(0.5,0.5));
            mark->setScaleX(3);
            mark->setPosition(getCalc()->rotByRad(fstPt-curveCenterPt, drawRad)+ curveCenterPt);
            mark->setRotation(getCalc()->chgKaku(getCalc()->rotByRad(fstPt-curveCenterPt, drawRad + optRad)));
            mark->setGlobalZOrder(OBJ_LAYER_TOP);
            getMark()->addChild(mark);
            getMember().pushBack(mark);
            drawRad += pitchRad;
        }
    }else{
        while(rad>drawRad){
            Sprite* mark = Sprite::createWithTexture(getMark()->getTexture());
            mark->setAnchorPoint(Vec2(0.5,0.5));
            mark->setScaleX(3);
            mark->setPosition(getCalc()->rotByRad(fstPt-curveCenterPt, drawRad)+ curveCenterPt);
            mark->setRotation(getCalc()->chgKaku(getCalc()->rotByRad(fstPt-curveCenterPt, drawRad + optRad)));
            mark->setGlobalZOrder(OBJ_LAYER_TOP);
            getMark()->addChild(mark);
            getMember().pushBack(mark);
            drawRad += pitchRad;
        }
    }
    _remindMarkPitch = abs(rad-drawRad) * r;
}

void CourceMaker::madePhysiceBody(){
    auto _material = PHYSICSBODY_MATERIAL_DEFAULT;
    _material.restitution = 0.0001f;
    _material.friction =1.0f;
    _material.density = 0.001f;
    
    this->setCourceBody(PhysicsBody::createEdgeChain(_polygonPts, _polygonPtCnt,_material));
    getCourceBody()->setDynamic(false);
    getCourceBody()->setCategoryBitmask(CT_COURCE);
    getCourceBody()->setCollisionBitmask(CT_WHEEL);
    getCourceBody()->setContactTestBitmask(CT_WHEEL);
    getCourceBody()->setTag(TG_COURCE);
    this->setPhysicsBody(getCourceBody());
}

void CourceMaker::madePhysiceBody(Node* field){
    auto _material = PHYSICSBODY_MATERIAL_DEFAULT;
    _material.restitution = 0.0001f;
    _material.friction =1.0f;
    _material.density = 0.001f;
    
    this->setCourceBody(PhysicsBody::createEdgeChain(_polygonPts, _polygonPtCnt,_material));
    getCourceBody()->setDynamic(false);
    getCourceBody()->setCategoryBitmask(CT_COURCE);
    getCourceBody()->setCollisionBitmask(CT_WHEEL);
    getCourceBody()->setContactTestBitmask(CT_WHEEL);
    getCourceBody()->setTag(TG_COURCE);
    field->setPhysicsBody(getCourceBody());
}

void CourceMaker::addCurveA(Vec2 pt_, Vec2 dir_){
    
}

/** パラメータサンプル
 this->setDot(SpriteBatchNode*::create());
 this->getDot();
 this->setStraight(SpriteBachNode::create());
 this->getStraight();
 this->setCurveA(SpriteBachNode::create());
 this->getCurveA();
 this->setCurveB(SpriteBachNode::create());
 this->getCurveB();
 this->setCurveC(SpriteBachNode::create());
 this->getCurveC();
 this->setCurveD(SpriteBachNode::create());
 this->getCurveD();
 this->setCurveE(SpriteBachNode::create());
 this->getCurveE();
 this->setCurveF(SpriteBachNode::create());
 this->getCurveF();
 */
