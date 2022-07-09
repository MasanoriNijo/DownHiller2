#include "CourceMaker.h"

CourceMaker::CourceMaker():
_calc(NULL),_dot(NULL), _straight(NULL),
_curveA(NULL), _curveB(NULL), _curveC(NULL), _curveD(NULL), _curveE(NULL), _curveF(NULL),
_courceBody(NULL),_mark(NULL),_nuri(NULL)
{}

CourceMaker::~CourceMaker() {
    CC_SAFE_RELEASE_NULL(_calc);
    CC_SAFE_RELEASE_NULL(_dot);
    CC_SAFE_RELEASE_NULL(_straight);
    CC_SAFE_RELEASE_NULL(_mark);
    CC_SAFE_RELEASE_NULL(_curveA);
    CC_SAFE_RELEASE_NULL(_curveB);
    CC_SAFE_RELEASE_NULL(_curveC);
    CC_SAFE_RELEASE_NULL(_curveD);
    CC_SAFE_RELEASE_NULL(_curveE);
    CC_SAFE_RELEASE_NULL(_curveF);
    CC_SAFE_RELEASE_NULL(_courceBody);
    CC_SAFE_RELEASE_NULL(_nuri);
    getMember().clear();
}

bool CourceMaker::init() {
    
    if(!Node::init()){
        return false;
    }
    setCalc(Calclater::create());
    setDot(SpriteBatchNode::create("c_dot.png"));
    getDot()->setGlobalZOrder(OBJ_LAYER_LV1);
    addChild(getDot());
    
    setStraight(SpriteBatchNode::create("c_straight.png"));
    getStraight()->setGlobalZOrder(OBJ_LAYER_LV1);
    _length = getStraight()->getTexture()->getContentSize().width;
    addChild(getStraight());
    
    setCurveA(SpriteBatchNode::create("c_curve_a.png"));
    addChild(getCurveA());
    
    setMark(SpriteBatchNode::create("mark.png"));
    getMark()->setGlobalZOrder(OBJ_LAYER_LV1);
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
    setStartPt(pt_);
    setStartDir(dir_);
    setWorkPt(pt_);
    setWorkDir(dir_);
    setTergetPt(pt_);
    setTargetDir(dir_);
    _polygonPtCnt = 0;
    addStartDot(pt_);//デバック時
//    addDot(pt_);
    addPolygonPts(_wrkPt);
    getMember().clear();
    low_y = 100000;
}
void CourceMaker::drawTo(Vec2 pt_, Vec2 dir_){
    setWorkPt(_trgPt);
    setWorkDir(_trgDir);
    setTergetPt(pt_);
    setTargetDir(dir_);
    calcCurve(_wrkPt, _wrkDir, _trgPt, _trgDir, -1);
}

void CourceMaker::drawByStraight(Vec2 dpt_){
    setWorkPt(_trgPt);
    setWorkDir(dpt_);
    setTergetPt(_trgPt + dpt_);
    setTargetDir(dpt_);
    addStraightLine(_wrkPt, _trgPt);
    addPolygonPts(_trgPt);
    if(markSetflg){
        addMarkStraight(_wrkPt, _trgPt);
    }
}

void CourceMaker::drawByStraight(float length, float kaku){    
    Vec2 dpt_ = getCalc()->rotByKaku(Vec2(length,0), -kaku);
    setWorkPt(_trgPt);
    setWorkDir(dpt_);
    setTergetPt(_trgPt + dpt_);
    setTargetDir(dpt_);
    addStraightLine(_wrkPt, _trgPt);
    addPolygonPts(_trgPt);
    if(markSetflg){
        addMarkStraight(_wrkPt, _trgPt);
    }
    _dirkaku = kaku;
}

void CourceMaker::drawBySmoothCurve(Vec2 dirPt_){
    Vec2 newTrgDir=getCalc()->rotByRad(_trgDir, 2*getCalc()->nomlRad(dirPt_));
    Vec2 dpt_ = getCalc()->rotByRad(dirPt_,_trgDir);
    setWorkPt(_trgPt);
    setWorkDir(_trgDir);
    setTergetPt(_trgPt + dpt_);
    setTargetDir(newTrgDir);
    calcCurve(-1);
}

void CourceMaker::drawBySmoothCurve(float r,float kaku){
    Vec2 trgDir = getCalc()->rotByKaku(Vec2(1,0), -kaku);
    
    float trg_rad = kaku * M_PI/180;
    float wrk_rad = _dirkaku * M_PI/180;
    float dffrad = trg_rad - wrk_rad ;
    _dirkaku = kaku;
    Vec2 wrkPt_ctPt = getCalc()->chgLength(getCalc()->rotByRad(getTargetDir(), dffrad>0 ? -M_PI/2 : M_PI/2) , r);
    Vec2 trgPt_ctPt = getCalc()->rotByRad(wrkPt_ctPt, dffrad);
    Vec2 trgPt = getTergetPt()+trgPt_ctPt-wrkPt_ctPt;
    Vec2 ctPt = getTergetPt() - wrkPt_ctPt;
    setWorkPt(getTergetPt());
    setWorkDir(getTargetDir());
    setTergetPt(trgPt);
    setTargetDir(trgDir);

    // 円弧の部分を描写する。
    float drad = dffrad>0 ? _drawPitch/r : -_drawPitch/r;
    int i = 1;
    while(abs(drad * i) < abs(dffrad)){
        addDot(getCalc()->rotByRad(wrkPt_ctPt, drad * i) + ctPt);
        i++;
    }
    addDot(getTergetPt());
    // カーブ部分へのmarkの追加
    if(markSetflg){
        addMarkCurve(ctPt,getWorkPt(),dffrad);
    }
    
    // ポリゴンの追加
    float dradp = dffrad>0 ? _polygonPitch/r : -_polygonPitch/r;
//    int ip = 1;
    
    addPolygonPts(getWorkPt());
    i = 0;
    while(abs(dradp * i) < abs(dffrad)){
        addPolygonPts(getCalc()->rotByRad(wrkPt_ctPt, dradp * i) + ctPt);
        i++;
    }
    addPolygonPts(getTergetPt());
}

void CourceMaker::drawByCurve(Vec2 dpt_,float kaku){
    setWorkPt(_trgPt);
    setTergetPt(_trgPt + dpt_);
    if(kaku < -89){
        kaku = -89;
    }
    if(kaku > 89){
        kaku = 89;
    }
    setWorkDir(getCalc()->rotByKaku(dpt_, kaku));
    setTargetDir(getCalc()->rotByKaku(dpt_, -kaku));
    calcCurve(-1);
}

void CourceMaker::calcCurve(Vec2 pt1,Vec2 dir1, Vec2 pt2, Vec2 dir2 ,float r_){
    setWorkPt(pt1);
    setWorkDir(dir1);
    setTergetPt(pt2);
    setTargetDir(dir2);
    calcCurve(r_);
}

void CourceMaker::calcCurve(float r_){
    // workとtargetの交点
    Vec2 ptA = getCalc()->getCrossPointLineA2B(_wrkPt,_wrkPt + _wrkDir, _trgPt, _trgPt + _trgDir);
    
    // 折れ曲がるだけの場合
    if((ptA-_trgPt).length() < 1 || ptA.equals(Vec2::ZERO)){
        addStraightLine(_wrkPt, _trgPt);
        addPolygonPts(_trgPt);
        if(markSetflg){
            addMarkStraight(_wrkPt, _trgPt);
        }
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
    bool rotLeft = getCalc()->chkLeft(_wrkPt, _trgPt-_wrkPt, ctPt);
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
    if(_polygonPts[_polygonPtCnt-1].y<low_y){
        low_y = _polygonPts[_polygonPtCnt-1].y;
    }
}

void CourceMaker::addStraightLine(Vec2 pt1_, Vec2 pt2_){
    Sprite* stline = Sprite::createWithTexture(getStraight()->getTexture());
    stline->setAnchorPoint(Vec2(0,0.5));
    stline->setScaleX((pt2_-pt1_).length()/_length);
    stline->setPosition(pt1_);
    stline->setRotation(getCalc()->chgKaku((pt2_-pt1_)));
    stline->setGlobalZOrder(OBJ_LAYER_LV1);
//    stline->setOpacity(95);
    getStraight()->addChild(stline);
    getMember().pushBack(stline);
    addDot(pt2_);
}

void CourceMaker::addDot(Vec2 pt_){
    Sprite* dot = Sprite::createWithTexture(getDot()->getTexture());
    dot->setGlobalZOrder(OBJ_LAYER_LV1);
    dot->setPosition(pt_);
    //    dot->setOpacity(0.2f);
    getDot()->addChild(dot);
    getMember().pushBack(dot);
}

void CourceMaker::addStartDot(Vec2 pt_){
    Sprite* dot = Sprite::createWithTexture(getDot()->getTexture());
    dot->setGlobalZOrder(OBJ_LAYER_LV1);
    dot->setScale(2, 2);
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
        mark->setGlobalZOrder(OBJ_LAYER_LV1 + 1);
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
        optRad *= -1;
        while(rad<drawRad){
            Sprite* mark = Sprite::createWithTexture(getMark()->getTexture());
            mark->setAnchorPoint(Vec2(0.5,0.5));
            mark->setPosition(getCalc()->rotByRad(fstPt-curveCenterPt, drawRad)+ curveCenterPt);
            mark->setRotation(getCalc()->chgKaku(getCalc()->rotByRad(fstPt-curveCenterPt, drawRad + optRad)));
            mark->setGlobalZOrder(OBJ_LAYER_LV1);
            getMark()->addChild(mark);
            getMember().pushBack(mark);
            drawRad += pitchRad;
        }
    }else{
        while(rad>drawRad){
            Sprite* mark = Sprite::createWithTexture(getMark()->getTexture());
            mark->setAnchorPoint(Vec2(0.5,0.5));
            mark->setPosition(getCalc()->rotByRad(fstPt-curveCenterPt, drawRad)+ curveCenterPt);
            mark->setRotation(getCalc()->chgKaku(getCalc()->rotByRad(fstPt-curveCenterPt, drawRad + optRad)));
            mark->setGlobalZOrder(OBJ_LAYER_LV1);
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
    
    setCourceBody(PhysicsBody::createEdgeChain(_polygonPts, _polygonPtCnt,_material));
    getCourceBody()->setDynamic(false);
    getCourceBody()->setCategoryBitmask(CT_COURCE);
    getCourceBody()->setCollisionBitmask(CT_WHEEL | CT_RIDER);
    getCourceBody()->setContactTestBitmask(CT_WHEEL | CT_RIDER);
    getCourceBody()->setTag(TG_COURCE);
    setPhysicsBody(getCourceBody());
        
    // ぬり
    if(getNuri()){
        getNuri()->removeFromParentAndCleanup(true);
    }
    setNuri(DrawNode::create());
    getNuri()->setGlobalZOrder(OBJ_LAYER_LV1-1);
    addChild(getNuri());
    low_y -= 400;
    float min_x =_polygonPts[0].x;
    for(int i=0; i<_polygonPtCnt-1;i++){
        if(_polygonPts[i].x > _polygonPts[i+1].x || _polygonPts[i+1].x < min_x){
            continue;
        }
        _nuriPts[0].x = _polygonPts[i].x;
        _nuriPts[0].y = _polygonPts[i].y;
        _nuriPts[1].x = _polygonPts[i+1].x;
        _nuriPts[1].y = _polygonPts[i+1].y;
        _nuriPts[2].x = _polygonPts[i+1].x;
        _nuriPts[2].y = low_y;
        _nuriPts[3].x = _polygonPts[i].x;
        _nuriPts[3].y = low_y;
        getNuri()->drawSolidPoly(_nuriPts, 4,  Color4F::RED);
        if(min_x < _polygonPts[i+1].x){
            min_x = _polygonPts[i+1].x;
        }
    }
}

void CourceMaker::madePhysiceBody(Node* field){
    auto _material = PHYSICSBODY_MATERIAL_DEFAULT;
    _material.restitution = 0.0001f;
    _material.friction =1.0f;
    _material.density = 0.001f;
    
    setCourceBody(PhysicsBody::createEdgeChain(_polygonPts, _polygonPtCnt,_material));
    getCourceBody()->setDynamic(false);
    getCourceBody()->setCategoryBitmask(CT_COURCE);
    getCourceBody()->setCollisionBitmask(CT_WHEEL | CT_RIDER);
    getCourceBody()->setContactTestBitmask(CT_WHEEL | CT_RIDER);
    getCourceBody()->setTag(TG_COURCE);
    field->setPhysicsBody(getCourceBody());
}

void CourceMaker::addCurveA(Vec2 pt_, Vec2 dir_){
    
}

/** パラメータサンプル
 setDot(SpriteBatchNode*::create());
 getDot();
 setStraight(SpriteBachNode::create());
 getStraight();
 setCurveA(SpriteBachNode::create());
 getCurveA();
 setCurveB(SpriteBachNode::create());
 getCurveB();
 setCurveC(SpriteBachNode::create());
 getCurveC();
 setCurveD(SpriteBachNode::create());
 getCurveD();
 setCurveE(SpriteBachNode::create());
 getCurveE();
 setCurveF(SpriteBachNode::create());
 getCurveF();
 */
