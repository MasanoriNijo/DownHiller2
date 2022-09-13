#include "CourceManager.h"

CourceManager::CourceManager():
_courceMakerA(NULL), _courceMakerB(NULL), _startFlg(NULL), _goalFlg(NULL),_stagePrm(NULL),
_gurd(NULL),_gurdBody(NULL),_colorChanger(NULL)
{}

CourceManager::~CourceManager() {
    CC_SAFE_RELEASE_NULL(_courceMakerA);
    CC_SAFE_RELEASE_NULL(_courceMakerB);
    CC_SAFE_RELEASE_NULL(_startFlg);
    CC_SAFE_RELEASE_NULL(_goalFlg);
    CC_SAFE_RELEASE_NULL(_stagePrm);
    CC_SAFE_RELEASE_NULL(_gurd);
    CC_SAFE_RELEASE_NULL(_gurdBody);
    CC_SAFE_RELEASE_NULL(_colorChanger);
}

bool CourceManager::init() {
    setCourceMakerA(CourceMaker::create());
    setCourceMakerB(CourceMaker::create());
    setStartPt(FIRST_COURCE_BASE_POINT);
    setTergetPt(FIRST_COURCE_BASE_POINT);
    setStartDir(Vec2::ZERO);
    setTargetDir(Vec2::ZERO);
    _setStagePrm();
    
    setGurd(Node::create());
    setGurdBody(PhysicsBody::createEdgeSegment(Vec2(0,0), Vec2(0,50)));
    getGurdBody()->setDynamic(false);
    getGurdBody()->setCollisionBitmask(CT_ALL);
    getGurd()->setPhysicsBody(getGurdBody());
    
    setColorChanger(ColorChanger::create());
    getColorChanger()->SetColor(COURCE_LINE_COLOR_H, COURCE_LINE_COLOR_S, COURCE_LINE_COLOR_V);
    getCourceMakerA()->_lineColor = getColorChanger()->getColor3B();
    getCourceMakerB()->_lineColor = getColorChanger()->getColor3B();
    getColorChanger()->SetColor(COURCE_BASE_COLOR_H, COURCE_BASE_COLOR_S, COURCE_BASE_COLOR_V);
    getCourceMakerA()->_nuriColor = getColorChanger()->getColor4F();
    getCourceMakerB()->_nuriColor = getColorChanger()->getColor4F();
    getColorChanger()->SetColor(COURCE_BASE_COLOR2_H, COURCE_BASE_COLOR2_S, COURCE_BASE_COLOR2_V);
    getCourceMakerA()->_nuriColor2 = getColorChanger()->getColor4F();
    getCourceMakerB()->_nuriColor2 = getColorChanger()->getColor4F();
    
    selStg = UserDefault::getInstance()->getIntegerForKey(UDF_INT_SELECTED_STAGE,1);
    
    setStartFlg(Flg::create(FlgType::START));
    setGoalFlg(Flg::create(FlgType::GOAL));
    
    return true;
}

void CourceManager::onEnterTransitionDidFinish() {
    // todo
}

void CourceManager::update(float dt) {
    // todo
}

void CourceManager::_setStagePrm(){
    setStagePrm(StagePrm::create());
    getStagePrm()->setStageNumber(UserDefault::getInstance()->getIntegerForKey(UDF_INT_SELECTED_STAGE,1));
    if(UserDefault::getInstance()->getIntegerForKey(UDF_INT_GAME_MODE,GAME_MODE_STAGE)==GAME_MODE_STAGE){
        std::string head = "クリア条件\n";
        getStagePrm()->setCommnent("ステージ:" + ST_INT(getStagePrm()->getStageNumber()));
        getStagePrm()->setTymeLimit(30);
        if(getStagePrm()->getStageNumber() == 0){
            getStagePrm()->setCommnent(
                                       "ここからは、\n"
                                       "実際に操作して、\n"
                                       "ゴールを目指そう!\n"
                                       );
        }
        return;
    }else{
        getStagePrm()->setCommnent("練習:" + ST_INT(getStagePrm()->getStageNumber()));
        return;
    }
}

void CourceManager::setStartAndTargetFromCource(CourceMaker* _c){
    setStartPt(_c->getStartPt());
    setStartDir(_c->getStartDir());
    setTergetPt(_c->getTergetPt());
    setTargetDir(_c->getTargetDir());
}

void CourceManager::checkAndMadeCource(Vec2 chPt){
    
    if(UserDefault::getInstance()->getBoolForKey(UDF_BOOL_DEBUG_STAGE, false)){
        checkAndMadeCourceForDebug(chPt);
        return;
    }
    if(chPt.x > (getStartPt().x + 200) || !courceIndex){
        _dirkaku = courceIndex%2 ? getCourceMakerA()->_dirkaku : getCourceMakerB()->_dirkaku;
        switch (selStg) {
            case -1:
                madeCourcePtnForTitle(courceIndex%2 ? getCourceMakerB() : getCourceMakerA(),courceIndex);
                break;
            case 0:
                madeCourcePtn0(courceIndex%2 ? getCourceMakerB() : getCourceMakerA(),courceIndex);
                break;
            case 1:
                madeCourcePtn1(courceIndex%2 ? getCourceMakerB() : getCourceMakerA(),courceIndex);
                break;
            case 2:
                madeCourcePtn2(courceIndex%2 ? getCourceMakerB() : getCourceMakerA(),courceIndex);
                break;
            case 3:
                madeCourcePtn3(courceIndex%2 ? getCourceMakerB() : getCourceMakerA(),courceIndex);
                break;
            case 4:
                madeCourcePtn4(courceIndex%2 ? getCourceMakerB() : getCourceMakerA(),courceIndex);
                break;
            case 5:
                madeCourcePtn5(courceIndex%2 ? getCourceMakerB() : getCourceMakerA(),courceIndex);
                break;
            case 6:
                madeCourcePtn6(courceIndex%2 ? getCourceMakerB() : getCourceMakerA(),courceIndex);
                break;
            case 7:
                madeCourcePtn7(courceIndex%2 ? getCourceMakerB() : getCourceMakerA(),courceIndex);
                break;
            case 8:
                madeCourcePtn8(courceIndex%2 ? getCourceMakerB() : getCourceMakerA(),courceIndex);
                break;
            case 9:
                madeCourcePtn9(courceIndex%2 ? getCourceMakerB() : getCourceMakerA(),courceIndex);
                break;
            case 10:
                madeCourcePtn10(courceIndex%2 ? getCourceMakerB() : getCourceMakerA(),courceIndex);
                break;
            case 11:
                madeCourcePtn11(courceIndex%2 ? getCourceMakerB() : getCourceMakerA(),courceIndex);
                break;
            case 12:
                madeCourcePtn12(courceIndex%2 ? getCourceMakerB() : getCourceMakerA(),courceIndex);
                break;
            case 13:
                madeCourcePtn13(courceIndex%2 ? getCourceMakerB() : getCourceMakerA(),courceIndex);
                break;
            case 14:
                madeCourcePtn14(courceIndex%2 ? getCourceMakerB() : getCourceMakerA(),courceIndex);
                break;
            case 15:
                madeCourcePtn15(courceIndex%2 ? getCourceMakerB() : getCourceMakerA(),courceIndex);
                break;
            case 16:
                madeCourcePtn16(courceIndex%2 ? getCourceMakerB() : getCourceMakerA(),courceIndex);
                break;
            case 17:
                madeCourcePtn17(courceIndex%2 ? getCourceMakerB() : getCourceMakerA(),courceIndex);
                break;
            case 18:
                madeCourcePtn18(courceIndex%2 ? getCourceMakerB() : getCourceMakerA(),courceIndex);
                break;
            case 19:
                madeCourcePtn19(courceIndex%2 ? getCourceMakerB() : getCourceMakerA(),courceIndex);
                break;
            case 20:
                madeCourcePtn20(courceIndex%2 ? getCourceMakerB() : getCourceMakerA(),courceIndex);
                break;
            case 21:
                madeCourcePtn20(courceIndex%2 ? getCourceMakerB() : getCourceMakerA(),courceIndex);
                break;
            default:
                break;
        }
        getGurd()->setPosition(getStartPt());
        setStartAndTargetFromCource(courceIndex%2 ? getCourceMakerB() : getCourceMakerA());
        courceIndex ++;
    }
}

void CourceManager::setForTitle(){
    selStg = -1;
    setStartPt(FIRST_COURCE_BASE_POINT + Vec2(0,40));
    setTergetPt(FIRST_COURCE_BASE_POINT + Vec2(0,40));
}

void CourceManager::setStart(CourceMaker* _c){
    getStartFlg()->setPosition(_c->getTergetPt());
    getStartFlg()->setRotation(_c->getCalc()->nomlKaku(Vec2::ZERO,_c->getTargetDir()));
    if(!_isSetStart){
        _c->addChild(getStartFlg());
        _isSetStart = true;
    }
}

void CourceManager::setGoal(CourceMaker* _c){
    getGoalFlg()->setPosition(_c->getTergetPt());
    getGoalFlg()->setRotation(_c->getCalc()->nomlKaku(Vec2::ZERO,_c->getTargetDir()));
    if(!_isSetGoal){
        _c->addChild(getGoalFlg());
        _isSetGoal = true;
    }
}

void CourceManager::setComment(std::string st,CourceMaker* _c){
    if(!_isDebugComment){
        return;
    }
    Label* _comment = Label::createWithTTF("← " + st, "irohamaru.ttf", 24);
    _comment->setGlobalZOrder(OBJ_LAYER_TOP);
    _comment->setAnchorPoint(Vec2(0,0));
    _comment->setPosition(_c->getTergetPt());
    Vec2 hosei_ = _c->getCalc()->rotByRad(_c->getTargetDir(), M_PI/2);
    _comment->setRotation(_c->getCalc()->nomlKaku(Vec2::ZERO,hosei_));
    _c->addChild(_comment);
}

void CourceManager::madeCourcePtnForTitle(CourceMaker* _c,int ind){
    auto flg = Flg::create();
    int i = 0;
    _c->drawStart(getTergetPt(),getTargetDir());
    ind = ind % 4;
    switch (ind) {
        case 0:
            _c->dS(600,-5);
            setStart(_c);
            _c->dS(200,-5);
            break;
        case 1:
            for(i=0;i<8;i++){
                int kaku_ = i%2 ? random<int>(-70, -30):random<int>(-5, 0);
                int length_ = random<int>(100,200);
                float r_ = random<float>(10,100);
                _c->dC(r_, kaku_);
                _c->dS(length_,kaku_);
            }
            break;
        case 2:
            for(i=0;i<8;i++){
                int kaku_ = i%2 ? random<int>(-70, -30):random<int>(-5, 0);
                int length_ = random<int>(50,200);
                float r_ = random<float>(10,100);
                //                _c->drawBySmoothCurve(r_, kaku_);
                _c->dS(length_,kaku_);
            }
            break;
        case 3:
            _c->dS(Vec2(90,0));
            setGoal(_c);
            _c->dS(Vec2(120,0));
            break;
        default:
            return;
            break;
    }
    _c->madePhysiceBody();
}

void CourceManager::madeCourcePtn0(CourceMaker* _c,int ind){
    auto flg = Flg::create();
    int i = 0;
    _c->drawStart(getTergetPt(),getTargetDir());
    switch (ind) {
        case 0:
            _c->dS(500,0);
            _c->dS(100,-1);
            setStart(_c);
            _c->dS(5000,-1);
            break;
        case 1:
            for(i=0;i<3;i++){
                _c->dC(200, -10);
                _c->dS(100, -10);
                _c->dC(80,10);
                _c->dC(30, 0);
                _c->dS(100, 0);
            }
            break;
        case 2:
            for(i=0;i<3;i++){
                _c->dC(100, -30);
                _c->dS(100, -30);
                _c->dC(60, 10);
                _c->dS(400, 0);
            }
            break;
        case 3:
            _c->dS(Vec2(90,0));
            setGoal(_c);
            _c->dS(Vec2(1000,0));
            _c->dS(Vec2(0,100));
            break;
        default:
            return;
            break;
    }
    _c->madePhysiceBody();
}

void CourceManager::madeCourcePtn1(CourceMaker* _c,int ind){
    auto flg = Flg::create();
    int i = 0;
    _c->drawStart(getTergetPt(),getTargetDir());
    switch (ind) {
        case 0:
            _c->dS(615,0);
            setStart(_c);
            _c->dS(30,-3);
            break;
        case 1:
            cPtn00(_c);
            cPtn05(_c);
            break;
        case 2:
            cPtn10(_c);
            cPtn15(_c);
            break;
        case 3:
            _c->dS(100,0);
            setGoal(_c);
            _c->dS(1000,0);
            _c->dS(100,90);
            break;
        default:
            return;
            break;
    }
    _c->madePhysiceBody();
}

void CourceManager::madeCourcePtn2(CourceMaker* _c,int ind){
    int i = 0;
    _c->drawStart(getTergetPt(),getTargetDir());
    switch (ind) {
        case 0:
            _c->dS(615,0);
            setStart(_c);
            _c->dS(30,-3);
            break;
        case 1:
            cPtn01(_c);
            cPtn06(_c);
            break;
        case 2:
            cPtn11(_c);
            cPtn16(_c);
            break;
        case 3:
            _c->dS(100,0);
            setGoal(_c);
            _c->dS(1000,0);
            _c->dS(100,90);
            break;
        default:
            return;
            break;
    }
    _c->madePhysiceBody();
}

void CourceManager::madeCourcePtn3(CourceMaker* _c,int ind){
    int i = 0;
    _c->drawStart(getTergetPt(),getTargetDir());
    switch (ind) {
        case 0:
            _c->dS(615,0);
            setStart(_c);
            _c->dS(30,-3);
            break;
        case 1:
            cPtn02(_c);
            cPtn07(_c);
            break;
        case 2:
            cPtn12(_c);
            cPtn17(_c);
            break;
        case 3:
            _c->dS(100,0);
            setGoal(_c);
            _c->dS(1000,0);
            _c->dS(100,90);
            break;
        default:
            return;
            break;
    }
    _c->madePhysiceBody();
}

void CourceManager::madeCourcePtn4(CourceMaker* _c,int ind){
    int i = 0;
    _c->drawStart(getTergetPt(),getTargetDir());
    switch (ind) {
        case 0:
            _c->dS(615,0);
            setStart(_c);
            _c->dS(30,-3);
            break;
        case 1:
            cPtn03(_c);
            cPtn08(_c);
            break;
        case 2:
            cPtn13(_c);
            cPtn18(_c);
            break;
        case 3:
            _c->dS(100,0);
            setGoal(_c);
            _c->dS(1000,0);
            _c->dS(100,90);
            break;
        default:
            return;
            break;
    }
    _c->madePhysiceBody();
}

void CourceManager::madeCourcePtn5(CourceMaker* _c,int ind){
    int i = 0;
    _c->drawStart(getTergetPt(),getTargetDir());
    switch (ind) {
        case 0:
            _c->dS(615,0);
            setStart(_c);
            _c->dS(30,-3);
            break;
        case 1:
            cPtn04(_c);
            cPtn09(_c);
            break;
        case 2:
            cPtn14(_c);
            cPtn19(_c);
            break;
        case 3:
            _c->dS(100,0);
            setGoal(_c);
            _c->dS(1000,0);
            _c->dS(100,90);
            break;
        default:
            return;
            break;
    }
    _c->madePhysiceBody();
}

void CourceManager::madeCourcePtn6(CourceMaker* _c,int ind){
    int i = 0;
    _c->drawStart(getTergetPt(),getTargetDir());
    switch (ind) {
        case 0:
            _c->dS(615,0);
            setStart(_c);
            _c->dS(30,-3);
            break;
        case 1:
            cPtn05(_c);
            cPtn10(_c);
            break;
        case 2:
            cPtn15(_c);
            cPtn20(_c);
            break;
        case 3:
            _c->dS(100,0);
            setGoal(_c);
            _c->dS(1000,0);
            _c->dS(100,90);
            break;
        default:
            return;
            break;
    }
    _c->madePhysiceBody();
}

void CourceManager::madeCourcePtn7(CourceMaker* _c,int ind){
    int i = 0;
    _c->drawStart(getTergetPt(),getTargetDir());
    switch (ind) {
        case 0:
            _c->dS(615,0);
            setStart(_c);
            _c->dS(30,-3);
            break;
        case 1:
            cPtn16(_c);
            cPtn21(_c);
            break;
        case 2:
            cPtn30(_c);
            cPtn35(_c);
            break;
        case 3:
            _c->dS(100,0);
            setGoal(_c);
            _c->dS(1000,0);
            _c->dS(100,90);
            break;
        default:
            return;
            break;
    }
    _c->madePhysiceBody();
}

void CourceManager::madeCourcePtn8(CourceMaker* _c,int ind){
    int i = 0;
    _c->drawStart(getTergetPt(),getTargetDir());
    switch (ind) {
        case 0:
            _c->dS(615,0);
            setStart(_c);
            _c->dS(30,-3);
            break;
        case 1:
            cPtn17(_c);
            cPtn22(_c);
            break;
        case 2:
            cPtn31(_c);
            cPtn36(_c);
            break;
        case 3:
            _c->dS(100,0);
            setGoal(_c);
            _c->dS(1000,0);
            _c->dS(100,90);
            break;
        default:
            return;
            break;
    }
    _c->madePhysiceBody();
}

void CourceManager::madeCourcePtn9(CourceMaker* _c,int ind){
    int i = 0;
    _c->drawStart(getTergetPt(),getTargetDir());
    switch (ind) {
        case 0:
            _c->dS(615,0);
            setStart(_c);
            _c->dS(30,-3);
            break;
        case 1:
            cPtn18(_c);
            cPtn23(_c);
            break;
        case 2:
            cPtn32(_c);
            cPtn37(_c);
            break;
        case 3:
            _c->dS(100,0);
            setGoal(_c);
            _c->dS(1000,0);
            _c->dS(100,90);
            break;
        default:
            return;
            break;
    }
    _c->madePhysiceBody();
}

void CourceManager::madeCourcePtn10(CourceMaker* _c,int ind){
    int i = 0;
    _c->drawStart(getTergetPt(),getTargetDir());
    switch (ind) {
        case 0:
            _c->dS(615,0);
            setStart(_c);
            _c->dS(30,-3);
            break;
        case 1:
            cPtn19(_c);
            cPtn24(_c);
            break;
        case 2:
            cPtn33(_c);
            cPtn38(_c);
            break;
        case 3:
            _c->dS(100,0);
            setGoal(_c);
            _c->dS(1000,0);
            _c->dS(100,90);
            break;
        default:
            return;
            break;
    }
    _c->madePhysiceBody();
}

void CourceManager::madeCourcePtn11(CourceMaker* _c,int ind){
    int i = 0;
    _c->drawStart(getTergetPt(),getTargetDir());
    switch (ind) {
        case 0:
            _c->dS(615,0);
            setStart(_c);
            _c->dS(30,-3);
            break;
        case 1:
            cPtn20(_c);
            cPtn25(_c);
            break;
        case 2:
            cPtn34(_c);
            cPtn39(_c);
            break;
        case 3:
            _c->dS(100,0);
            setGoal(_c);
            _c->dS(1000,0);
            _c->dS(100,90);
            break;
        default:
            return;
            break;
    }
    _c->madePhysiceBody();
}

void CourceManager::madeCourcePtn12(CourceMaker* _c,int ind){
    int i = 0;
    _c->drawStart(getTergetPt(),getTargetDir());
    switch (ind) {
        case 0:
            _c->dS(615,0);
            setStart(_c);
            _c->dS(30,-3);
            break;
        case 1:
            cPtn00(_c);
            cPtn40(_c);
            break;
        case 2:
            cPtn50(_c);
            cPtn39(_c);
            break;
        case 3:
            _c->dS(100,0);
            setGoal(_c);
            _c->dS(1000,0);
            _c->dS(100,90);
            break;
        default:
            return;
            break;
    }
    _c->madePhysiceBody();
}

void CourceManager::madeCourcePtn13(CourceMaker* _c,int ind){
    int i = 0;
    _c->drawStart(getTergetPt(),getTargetDir());
    switch (ind) {
        case 0:
            _c->dS(615,0);
            setStart(_c);
            _c->dS(30,-3);
            break;
        case 1:
            cPtn48(_c);
            cPtn01(_c);
            break;
        case 2:
            cPtn56(_c);
            cPtn38(_c);
            break;
        case 3:
            _c->dS(100,0);
            setGoal(_c);
            _c->dS(1000,0);
            _c->dS(100,90);
            break;
        default:
            return;
            break;
    }
    _c->madePhysiceBody();
}

void CourceManager::madeCourcePtn14(CourceMaker* _c,int ind){
    int i = 0;
    _c->drawStart(getTergetPt(),getTargetDir());
    switch (ind) {
        case 0:
            _c->dS(615,0);
            setStart(_c);
            _c->dS(30,-3);
            break;
        case 1:
            cPtn49(_c);
            cPtn12(_c);
            break;
        case 2:
            cPtn57(_c);
            cPtn36(_c);
            break;
        case 3:
            _c->dS(100,0);
            setGoal(_c);
            _c->dS(1000,0);
            _c->dS(100,90);
            break;
        default:
            return;
            break;
    }
    _c->madePhysiceBody();
}


void CourceManager::madeCourcePtn15(CourceMaker* _c,int ind){
    int i = 0;
    _c->drawStart(getTergetPt(),getTargetDir());
    switch (ind) {
        case 0:
            _c->dS(615,0);
            setStart(_c);
            _c->dS(30,-3);
            break;
        case 1:
            cPtn47(_c);
            cPtn06(_c);
            break;
        case 2:
            cPtn58(_c);
            cPtn34(_c);
            break;
        case 3:
            _c->dS(100,0);
            setGoal(_c);
            _c->dS(1000,0);
            _c->dS(100,90);
            break;
        default:
            return;
            break;
    }
    _c->madePhysiceBody();
}


void CourceManager::madeCourcePtn16(CourceMaker* _c,int ind){
    int i = 0;
    _c->drawStart(getTergetPt(),getTargetDir());
    switch (ind) {
        case 0:
            _c->dS(615,0);
            setStart(_c);
            _c->dS(30,-3);
            break;
        case 1:
            cPtn08(_c);
            cPtn44(_c);
            break;
        case 2:
            cPtn59(_c);
            cPtn31(_c);
            break;
        case 3:
            _c->dS(100,0);
            setGoal(_c);
            _c->dS(1000,0);
            _c->dS(100,90);
            break;
        default:
            return;
            break;
    }
    _c->madePhysiceBody();
}

void CourceManager::madeCourcePtn17(CourceMaker* _c,int ind){
    int i = 0;
    _c->drawStart(getTergetPt(),getTargetDir());
    switch (ind) {
        case 0:
            _c->dS(615,0);
            setStart(_c);
            _c->dS(30,-3);
            break;
        case 1:
            cPtn09(_c);
            cPtn55(_c);
            break;
        case 2:
            cPtn60(_c);
            cPtn29(_c);
            break;
        case 3:
            _c->dS(100,0);
            setGoal(_c);
            _c->dS(1000,0);
            _c->dS(100,90);
            break;
        default:
            return;
            break;
    }
    _c->madePhysiceBody();
}

void CourceManager::madeCourcePtn18(CourceMaker* _c,int ind){
    int i = 0;
    _c->drawStart(getTergetPt(),getTargetDir());
    switch (ind) {
        case 0:
            _c->dS(615,0);
            setStart(_c);
            _c->dS(30,-3);
            break;
        case 1:
            cPtn13(_c);
            cPtn51(_c);
            break;
        case 2:
            cPtn61(_c);
            cPtn29(_c);
            break;
        case 3:
            _c->dS(100,0);
            setGoal(_c);
            _c->dS(1000,0);
            _c->dS(100,90);
            break;
        default:
            return;
            break;
    }
    _c->madePhysiceBody();
}

void CourceManager::madeCourcePtn19(CourceMaker* _c,int ind){
    int i = 0;
    _c->drawStart(getTergetPt(),getTargetDir());
    switch (ind) {
        case 0:
            _c->dS(615,0);
            setStart(_c);
            _c->dS(30,-3);
            break;
        case 1:
            cPtn14(_c);
            cPtn55(_c);
            break;
        case 2:
            cPtn62(_c);
            cPtn26(_c);
            break;
        case 3:
            _c->dS(100,0);
            setGoal(_c);
            _c->dS(1000,0);
            _c->dS(100,90);
            break;
        default:
            return;
            break;
    }
    _c->madePhysiceBody();
}

void CourceManager::madeCourcePtn20(CourceMaker* _c,int ind){
    int i = 0;
    _c->drawStart(getTergetPt(),getTargetDir());
    switch (ind) {
        case 0:
            _c->dS(615,0);
            setStart(_c);
            _c->dS(30,-3);
            break;
        case 1:
            cPtn14(_c);
            cPtn57(_c);
            break;
        case 2:
            cPtn63(_c);
            cPtn29(_c);
            break;
        case 3:
            _c->dS(100,0);
            setGoal(_c);
            _c->dS(1000,0);
            _c->dS(100,90);
            break;
        default:
            return;
            break;
    }
    _c->madePhysiceBody();
}

void CourceManager::checkAndMadeCourceForDebug(Vec2 chPt){
    if(chPt.x > (getStartPt().x + 200) || !courceIndex){
        _dirkaku = courceIndex%2 ? getCourceMakerA()->_dirkaku : getCourceMakerB()->_dirkaku;
        auto _c = courceIndex%2 ? getCourceMakerB() : getCourceMakerA();
        _c->drawStart(getTergetPt(),getTargetDir());
        _c->_dirkaku = _dirkaku;
        switch (courceIndex) {
            case 0:
                _c->dS(615,0);
                setStart(_c);
                _c->dS(30,-3);
                break;
            case 1:
                switch (selStg) {
                    case 0:
                        cPtn00(_c);
                        break;
                    case 1:
                        cPtn01(_c);
                        break;
                    case 2:
                        cPtn02(_c);
                        break;
                    case 3:
                        cPtn03(_c);
                        break;
                    case 4:
                        cPtn04(_c);
                        break;
                    case 5:
                        cPtn05(_c);
                        break;
                    case 6:
                        cPtn06(_c);
                        break;
                    case 7:
                        cPtn07(_c);
                        break;
                    case 8:
                        cPtn08(_c);
                        break;
                    case 9:
                        cPtn09(_c);
                        break;
                    case 10:
                        cPtn10(_c);
                        break;
                    case 11:
                        cPtn11(_c);
                        break;
                    case 12:
                        cPtn12(_c);
                        break;
                    case 13:
                        cPtn13(_c);
                        break;
                    case 14:
                        cPtn14(_c);
                        break;
                    case 15:
                        cPtn15(_c);
                        break;
                    case 16:
                        cPtn16(_c);
                        break;
                    case 17:
                        cPtn17(_c);
                        break;
                    case 18:
                        cPtn18(_c);
                        break;
                    case 19:
                        cPtn19(_c);
                        break;
                    case 20:
                        cPtn20(_c);
                        break;
                    case 21:
                        cPtn21(_c);
                        break;
                    case 22:
                        cPtn22(_c);
                        break;
                    case 23:
                        cPtn23(_c);
                        break;
                    case 24:
                        cPtn24(_c);
                        break;
                    case 25:
                        cPtn25(_c);
                        break;
                    case 26:
                        cPtn26(_c);
                        break;
                    case 27:
                        cPtn27(_c);
                        break;
                    case 28:
                        cPtn28(_c);
                        break;
                    case 29:
                        cPtn29(_c);
                        break;
                    case 30:
                        cPtn30(_c);
                        break;
                    case 31:
                        cPtn31(_c);
                        break;
                    case 32:
                        cPtn32(_c);
                        break;
                    case 33:
                        cPtn33(_c);
                        break;
                    case 34:
                        cPtn34(_c);
                        break;
                    case 35:
                        cPtn35(_c);
                        break;
                    case 36:
                        cPtn36(_c);
                        break;
                    case 37:
                        cPtn37(_c);
                        break;
                    case 38:
                        cPtn38(_c);
                        break;
                    case 39:
                        cPtn39(_c);
                        break;
                    case 40:
                        cPtn40(_c);
                        break;
                    case 41:
                        cPtn41(_c);
                        break;
                    case 42:
                        cPtn42(_c);
                        break;
                    case 43:
                        cPtn43(_c);
                        break;
                    case 44:
                        cPtn44(_c);
                        break;
                    case 45:
                        cPtn45(_c);
                        break;
                    case 46:
                        cPtn46(_c);
                        break;
                    case 47:
                        cPtn47(_c);
                        break;
                    case 48:
                        cPtn48(_c);
                        break;
                    case 49:
                        cPtn49(_c);
                        break;
                    case 50:
                        cPtn50(_c);
                        break;
                    case 51:
                        cPtn51(_c);
                        break;
                    case 52:
                        cPtn52(_c);
                        break;
                    case 53:
                        cPtn53(_c);
                        break;
                    case 54:
                        cPtn54(_c);
                        break;
                    case 55:
                        cPtn55(_c);
                        break;
                    case 56:
                        cPtn56(_c);
                        break;
                    case 57:
                        cPtn57(_c);
                        break;
                    case 58:
                        cPtn58(_c);
                        break;
                    case 59:
                        cPtn59(_c);
                        break;
                    case 60:
                        cPtn60(_c);
                        break;
                    case 61:
                        cPtn61(_c);
                        break;
                    case 62:
                        cPtn62(_c);
                        break;
                    case 63:
                        cPtn63(_c);
                        break;
                    case 64:
                        cPtn64(_c);
                        break;
                    case 65:
                        cPtn65(_c);
                        break;
                    case 66:
                        cPtn66(_c);
                        break;
                    case 67:
                        cPtn67(_c);
                        break;
                    case 68:
                        cPtn68(_c);
                        break;
                    case 69:
                        cPtn69(_c);
                        break;
                    case 70:
                        cPtn70(_c);
                        break;
                    case 71:
                        cPtn71(_c);
                        break;
                    case 72:
                        cPtn72(_c);
                        break;
                    case 73:
                        cPtn73(_c);
                        break;
                    case 74:
                        cPtn74(_c);
                        break;
                    case 75:
                        cPtn75(_c);
                        break;
                    case 76:
                        cPtn76(_c);
                        break;
                    case 77:
                        cPtn77(_c);
                        break;
                    case 78:
                        cPtn78(_c);
                        break;
                    case 79:
                        cPtn79(_c);
                        break;
                    case 80:
                        cPtn80(_c);
                        break;
                    case 81:
                        cPtn81(_c);
                        break;
                    case 82:
                        cPtn82(_c);
                        break;
                    case 83:
                        cPtn83(_c);
                        break;
                    case 84:
                        cPtn84(_c);
                        break;
                    case 85:
                        cPtn85(_c);
                        break;
                    case 86:
                        cPtn86(_c);
                        break;
                    case 87:
                        cPtn87(_c);
                        break;
                    case 88:
                        cPtn88(_c);
                        break;
                    case 89:
                        cPtn89(_c);
                        break;
                    case 90:
                        cPtn90(_c);
                        break;
                    case 91:
                        cPtn91(_c);
                        break;
                    case 92:
                        cPtn92(_c);
                        break;
                    case 93:
                        cPtn93(_c);
                        break;
                    case 94:
                        cPtn94(_c);
                        break;
                    case 95:
                        cPtn95(_c);
                        break;
                    case 96:
                        cPtn96(_c);
                        break;
                    case 97:
                        cPtn97(_c);
                        break;
                    case 98:
                        cPtn98(_c);
                        break;
                    case 99:
                        cPtn99(_c);
                        break;
                    case 100:

                        cPtn100(_c);
                        break;
                    case 101:
                        cPtn101(_c);
                        break;
                    case 102:
                        cPtn102(_c);
                        break;
                    case 103:
                        cPtn103(_c);
                        break;
                    case 104:
                        cPtn104(_c);
                        break;
                    case 105:
                        cPtn105(_c);
                        break;
                    case 106:
                        cPtn106(_c);
                        break;
                    case 107:
                        cPtn107(_c);
                        break;
                    case 108:
                        cPtn108(_c);
                        break;
                    case 109:
                        cPtn109(_c);
                        break;
                    case 110:
                        cPtn110(_c);
                        break;
                    case 111:
                        cPtn111(_c);
                        break;
                    case 112:
                        cPtn112(_c);
                        break;
                    case 113:
                        cPtn113(_c);
                        break;
                    case 114:
                        cPtn114(_c);
                        break;
                    case 115:
                        cPtn115(_c);
                        break;
                    case 116:
                        cPtn116(_c);
                        break;
                    case 117:
                        cPtn117(_c);
                        break;
                    case 118:
                        cPtn118(_c);
                        break;
                    case 119:
                        cPtn119(_c);
                        break;
                    case 120:
                        cPtn120(_c);
                        break;
                    case 121:
                        cPtn121(_c);
                        break;
                    case 122:
                        cPtn122(_c);
                        break;
                    case 123:
                        cPtn123(_c);
                        break;
                }
                break;
            case 2:
                _c->dS(100,0);
                setGoal(_c);
                _c->dS(1000,0);
                _c->dS(100,90);
                break;
            default:
                return;
        }
        _c->madePhysiceBody();
        getGurd()->setPosition(getStartPt());
        setStartAndTargetFromCource(courceIndex%2 ? getCourceMakerB() : getCourceMakerA());
        courceIndex ++;
    }
}


// 滑らかな波波
void CourceManager::cPtn00(CourceMaker* _c){
    setComment("c00",_c);
    auto kaku = -1;
    _c->dC(59, -60 + kaku);
    _c->dC(133, -23 + kaku);
    _c->dC(130, -55 + kaku);
    _c->dC(113, -9 + kaku);
    _c->dC(116, -51 + kaku);
    _c->dC(71, 2 + kaku);
    _c->dC(115, -46 + kaku);
    _c->dC(129, -7 + kaku);
    _c->dC(144, -45 + kaku);
    _c->dC(97, -12 + kaku);
    _c->dC(70, -59 + kaku);
    _c->dC(85, -10 + kaku);
    _c->dC(104, -59 + kaku);
    _c->dC(51, -1 + kaku);
    _c->dC(72, -43 + kaku);
    _c->dC(114, 5 + kaku);
    _c->dC(126, -25 + kaku);
    _c->dC(191, 5 + kaku);
    _c->dC(99, -41 + kaku);
    _c->dC(175, -11 + kaku);

}

// 滑らかな波波
void CourceManager::cPtn01(CourceMaker* _c){
    setComment("c01",_c);
    auto kaku = 0;
    _c->dC(84, -55 + kaku);
    _c->dC(98, -19 + kaku);
    _c->dC(91, -54 + kaku);
    _c->dC(77, -15 + kaku);
    _c->dC(155, -49 + kaku);
    _c->dC(108, -5 + kaku);
    _c->dC(77, -54 + kaku);
    _c->dC(62, 5 + kaku);
    _c->dC(148, -32 + kaku);
    _c->dC(108, 3 + kaku);
    _c->dC(105, -45 + kaku);
    _c->dC(69, 5 + kaku);
    _c->dC(164, -27 + kaku);
    _c->dC(125, 4 + kaku);
    _c->dC(109, -28 + kaku);
    _c->dC(138, 3 + kaku);
    _c->dC(60, -57 + kaku);
    _c->dC(64, -8 + kaku);
    _c->dC(68, -56 + kaku);
    _c->dC(135, -21 + kaku);

}

// 滑らかな波波
void CourceManager::cPtn02(CourceMaker* _c){
    setComment("c02",_c);
    auto kaku = -1;
    _c->dC(114, -40 + kaku);
    _c->dC(139, 1 + kaku);
    _c->dC(82, -38 + kaku);
    _c->dC(97, -4 + kaku);
    _c->dC(98, -42 + kaku);
    _c->dC(117, -2 + kaku);
    _c->dC(85, -58 + kaku);
    _c->dC(83, -6 + kaku);
    _c->dC(67, -49 + kaku);
    _c->dC(67, 2 + kaku);
    _c->dC(90, -58 + kaku);
    _c->dC(71, -7 + kaku);
    _c->dC(107, -48 + kaku);
    _c->dC(150, -16 + kaku);
    _c->dC(111, -53 + kaku);
    _c->dC(95, 2 + kaku);
    _c->dC(184, -29 + kaku);
    _c->dC(158, 1 + kaku);
    _c->dC(70, -51 + kaku);
    _c->dC(86, -16 + kaku);

}

// 滑らかな波波
void CourceManager::cPtn03(CourceMaker* _c){
    setComment("c03",_c);
    auto kaku = -10;
    _c->dC(111, -36 + kaku);
    _c->dC(113, 1 + kaku);
    _c->dC(111, -33 + kaku);
    _c->dC(71, 18 + kaku);
    _c->dC(108, -34 + kaku);
    _c->dC(80, 14 + kaku);
    _c->dC(97, -35 + kaku);
    _c->dC(80, 23 + kaku);
    _c->dC(119, -15 + kaku);
    _c->dC(89, 23 + kaku);
    _c->dC(67, -40 + kaku);
    _c->dC(75, 17 + kaku);
    _c->dC(146, -15 + kaku);
    _c->dC(73, 27 + kaku);
    _c->dC(183, -4 + kaku);
    _c->dC(97, 30 + kaku);
    _c->dC(141, -9 + kaku);
    _c->dC(141, 23 + kaku);
    _c->dC(130, -16 + kaku);
    _c->dC(117, 23 + kaku);
}

// 滑らかな波波
void CourceManager::cPtn04(CourceMaker* _c){
    setComment("c04",_c);
    auto kaku = -10;
    _c->dC(83, -39 + kaku);
    _c->dC(87, 7 + kaku);
    _c->dC(110, -24 + kaku);
    _c->dC(86, 29 + kaku);
    _c->dC(123, -10 + kaku);
    _c->dC(111, 27 + kaku);
    _c->dC(117, -10 + kaku);
    _c->dC(159, 22 + kaku);
    _c->dC(74, -28 + kaku);
    _c->dC(83, 28 + kaku);
    _c->dC(92, -34 + kaku);
    _c->dC(85, 29 + kaku);
    _c->dC(103, -11 + kaku);
    _c->dC(126, 19 + kaku);
    _c->dC(107, -34 + kaku);
    _c->dC(94, 16 + kaku);
    _c->dC(117, -22 + kaku);
    _c->dC(112, 11 + kaku);
    _c->dC(70, -38 + kaku);
    _c->dC(87, 10 + kaku);

}

// 滑らかな波波
void CourceManager::cPtn05(CourceMaker* _c){
    setComment("c05",_c);
    auto kaku = 0;
    _c->dC(152, -41 + kaku);
    _c->dC(418, -21 + kaku);
    _c->dC(169, -68 + kaku);
    _c->dC(214, -36 + kaku);
    _c->dC(260, -64 + kaku);
    _c->dC(271, -41 + kaku);
    _c->dC(289, -65 + kaku);
    _c->dC(86, 4 + kaku);
    _c->dC(111, -54 + kaku);
    _c->dC(104, 8 + kaku);
    _c->dC(190, -26 + kaku);
    _c->dC(241, 7 + kaku);
    _c->dC(139, -39 + kaku);
    _c->dC(174, 9 + kaku);
    _c->dC(72, -73 + kaku);
    _c->dC(124, -26 + kaku);
    _c->dC(183, -70 + kaku);
    _c->dC(135, -21 + kaku);
    _c->dC(212, -52 + kaku);
    _c->dC(138, 6 + kaku);

}

// 滑らかな波波
void CourceManager::cPtn06(CourceMaker* _c){
    setComment("c06",_c);
    auto kaku = 0;
    _c->dC(87, -70 + kaku);
    _c->dC(152, -19 + kaku);
    _c->dC(199, -55 + kaku);
    _c->dC(145, 1 + kaku);
    _c->dC(162, -42 + kaku);
    _c->dC(123, 5 + kaku);
    _c->dC(300, -19 + kaku);
    _c->dC(303, 9 + kaku);
    _c->dC(87, -68 + kaku);
    _c->dC(114, 3 + kaku);
    _c->dC(103, -66 + kaku);
    _c->dC(111, -11 + kaku);
    _c->dC(290, -40 + kaku);
    _c->dC(218, -3 + kaku);
    _c->dC(118, -65 + kaku);
    _c->dC(278, -37 + kaku);
    _c->dC(289, -59 + kaku);
    _c->dC(106, 10 + kaku);
    _c->dC(102, -70 + kaku);
    _c->dC(124, -8 + kaku);
}

// 滑らかな波波
void CourceManager::cPtn07(CourceMaker* _c){
    setComment("c07",_c);
    auto kaku = 0;
    _c->dC(171, -33 + kaku);
    _c->dC(107, 8 + kaku);
    _c->dC(63, -77 + kaku);
    _c->dC(72, -2 + kaku);
    _c->dC(92, -38 + kaku);
    _c->dC(129, 5 + kaku);
    _c->dC(49, -78 + kaku);
    _c->dC(64, -10 + kaku);
    _c->dC(62, -75 + kaku);
    _c->dC(78, -13 + kaku);
    _c->dC(74, -61 + kaku);
    _c->dC(83, -20 + kaku);
    _c->dC(132, -59 + kaku);
    _c->dC(59, 10 + kaku);
    _c->dC(66, -60 + kaku);
    _c->dC(96, -20 + kaku);
    _c->dC(160, -51 + kaku);
    _c->dC(140, -14 + kaku);
    _c->dC(170, -47 + kaku);
    _c->dC(80, 2 + kaku);

}

// comment
void CourceManager::cPtn08(CourceMaker* _c){
    setComment("c08",_c);
    auto kaku = 0;
    _c->dC(91, -32 + kaku);
    _c->dC(100, 9 + kaku);
    _c->dC(60, -72 + kaku);
    _c->dC(63, -2 + kaku);
    _c->dC(77, -47 + kaku);
    _c->dC(98, 6 + kaku);
    _c->dC(187, -24 + kaku);
    _c->dC(114, 10 + kaku);
    _c->dC(124, -20 + kaku);
    _c->dC(150, 10 + kaku);
    _c->dC(102, -36 + kaku);
    _c->dC(102, -3 + kaku);
    _c->dC(133, -42 + kaku);
    _c->dC(110, 10 + kaku);
    _c->dC(70, -68 + kaku);
    _c->dC(68, 2 + kaku);
    _c->dC(77, -53 + kaku);
    _c->dC(75, 7 + kaku);
    _c->dC(62, -63 + kaku);
    _c->dC(108, -18 + kaku);

}

// 滑らかな波波
void CourceManager::cPtn09(CourceMaker* _c){
    setComment("c09",_c);
    auto kaku = 0;
    _c->dC(308, -34 + kaku);
    _c->dC(234, 12 + kaku);
    _c->dC(264, -30 + kaku);
    _c->dC(340, 2 + kaku);
    _c->dC(195, -47 + kaku);
    _c->dC(199, -3 + kaku);
    _c->dC(159, -59 + kaku);
    _c->dC(164, 6 + kaku);
    _c->dC(156, -54 + kaku);
    _c->dC(210, 0 + kaku);
    _c->dC(181, -48 + kaku);
    _c->dC(245, -13 + kaku);
    _c->dC(246, -54 + kaku);
    _c->dC(331, -23 + kaku);
    _c->dC(281, -57 + kaku);
    _c->dC(355, -26 + kaku);
    _c->dC(311, -60 + kaku);
    _c->dC(244, -19 + kaku);
    _c->dC(376, -49 + kaku);
    _c->dC(171, 7 + kaku);

}

// カクカク
void CourceManager::cPtn10(CourceMaker* _c){
    setComment("c10",_c);
    auto kaku = 0;
    _c->dS(67, -59 + kaku);
    _c->dS(74, -4 + kaku);
    _c->dS(93, -39 + kaku);
    _c->dS(73, 5 + kaku);
    _c->dS(74, -60 + kaku);
    _c->dS(71, -15 + kaku);
    _c->dS(62, -56 + kaku);
    _c->dS(72, -15 + kaku);
    _c->dS(87, -60 + kaku);
    _c->dS(55, -29 + kaku);
    _c->dS(79, -60 + kaku);
    _c->dS(98, -19 + kaku);
    _c->dS(62, -58 + kaku);
    _c->dS(52, -7 + kaku);
    _c->dS(91, -51 + kaku);
    _c->dS(85, -15 + kaku);
    _c->dS(73, -46 + kaku);
    _c->dS(62, 1 + kaku);
    _c->dS(89, -45 + kaku);
    _c->dS(77, -5 + kaku);

}

// カクカク
void CourceManager::cPtn11(CourceMaker* _c){
    setComment("c11",_c);
    auto kaku = 0;
    _c->dS(67, -46 + kaku);
    _c->dS(54, -7 + kaku);
    _c->dS(90, -40 + kaku);
    _c->dS(100, -1 + kaku);
    _c->dS(100, -36 + kaku);
    _c->dS(72, 3 + kaku);
    _c->dS(61, -53 + kaku);
    _c->dS(78, -21 + kaku);
    _c->dS(82, -59 + kaku);
    _c->dS(62, -6 + kaku);
    _c->dS(80, -54 + kaku);
    _c->dS(86, -7 + kaku);
    _c->dS(99, -38 + kaku);
    _c->dS(64, -8 + kaku);
    _c->dS(88, -54 + kaku);
    _c->dS(98, -17 + kaku);
    _c->dS(94, -51 + kaku);
    _c->dS(75, 2 + kaku);
    _c->dS(78, -36 + kaku);
    _c->dS(53, -3 + kaku);

}

// カクカク
void CourceManager::cPtn12(CourceMaker* _c){
    setComment("c12",_c);
    auto kaku = 0;
    _c->dS(169, -30 + kaku);
    _c->dS(166, 5 + kaku);
    _c->dS(168, -31 + kaku);
    _c->dS(189, 10 + kaku);
    _c->dS(156, -22 + kaku);
    _c->dS(165, 15 + kaku);
    _c->dS(184, -46 + kaku);
    _c->dS(150, 8 + kaku);
    _c->dS(194, -56 + kaku);
    _c->dS(182, 1 + kaku);
    _c->dS(198, -48 + kaku);
    _c->dS(151, 2 + kaku);
    _c->dS(166, -56 + kaku);
    _c->dS(197, -5 + kaku);
    _c->dS(158, -42 + kaku);
    _c->dS(200, 2 + kaku);
    _c->dS(154, -42 + kaku);
    _c->dS(199, -9 + kaku);
    _c->dS(176, -59 + kaku);
    _c->dS(190, -12 + kaku);

}

// カクカク
void CourceManager::cPtn13(CourceMaker* _c){
    setComment("c13",_c);
    auto kaku = 0;
    _c->dS(184, -49 + kaku);
    _c->dS(188, -9 + kaku);
    _c->dS(196, -45 + kaku);
    _c->dS(179, 5 + kaku);
    _c->dS(163, -56 + kaku);
    _c->dS(197, 14 + kaku);
    _c->dS(150, -59 + kaku);
    _c->dS(180, 4 + kaku);
    _c->dS(163, -28 + kaku);
    _c->dS(194, 7 + kaku);
    _c->dS(155, -59 + kaku);
    _c->dS(152, -20 + kaku);
    _c->dS(190, -51 + kaku);
    _c->dS(196, 4 + kaku);
    _c->dS(159, -35 + kaku);
    _c->dS(200, -1 + kaku);
    _c->dS(180, -39 + kaku);
    _c->dS(198, -3 + kaku);
    _c->dS(175, -49 + kaku);
    _c->dS(167, -17 + kaku);

}

// カクカクと波波
void CourceManager::cPtn14(CourceMaker* _c){
    setComment("c14",_c);
    auto kaku = 0;
    _c->dS(82, -33 + kaku);
    _c->dC(71, 10 + kaku);
    _c->dC(52, -53 + kaku);
    _c->dC(74, -1 + kaku);
    _c->dC(93, -60 + kaku);
    _c->dC(85, -26 + kaku);
    _c->dS(88, -60 + kaku);
    _c->dS(77, -11 + kaku);
    _c->dC(130, -51 + kaku);
    _c->dC(83, -10 + kaku);
    _c->dC(141, -46 + kaku);
    _c->dS(100, 4 + kaku);
    _c->dS(92, -60 + kaku);
    _c->dC(114, -17 + kaku);
    _c->dC(149, -52 + kaku);
    _c->dC(130, -11 + kaku);
    _c->dS(88, -47 + kaku);
    _c->dS(57, 12 + kaku);
    _c->dS(87, -31 + kaku);
    _c->dS(52, -1 + kaku);

}

// カクカクと波波
void CourceManager::cPtn15(CourceMaker* _c){
    setComment("c15",_c);
    auto kaku = 0;
    _c->dC(97, -47 + kaku);
    _c->dC(88, 6 + kaku);
    _c->dC(61, -47 + kaku);
    _c->dS(77, 7 + kaku);
    _c->dS(95, -30 + kaku);
    _c->dS(92, 2 + kaku);
    _c->dS(71, -59 + kaku);
    _c->dC(89, -13 + kaku);
    _c->dS(58, -50 + kaku);
    _c->dS(63, -19 + kaku);
    _c->dS(94, -59 + kaku);
    _c->dS(55, -20 + kaku);
    _c->dS(100, -54 + kaku);
    _c->dC(156, -20 + kaku);
    _c->dC(141, -56 + kaku);
    _c->dC(103, -9 + kaku);
    _c->dC(76, -59 + kaku);
    _c->dS(71, -17 + kaku);
    _c->dC(132, -55 + kaku);
    _c->dC(47, 12 + kaku);

}

// カクカクと波波
void CourceManager::cPtn16(CourceMaker* _c){
    setComment("c16",_c);
    auto kaku = 0;
    _c->dS(69, -58 + kaku);
    _c->dS(66, -25 + kaku);
    _c->dC(120, -57 + kaku);
    _c->dS(97, 5 + kaku);
    _c->dS(72, -58 + kaku);
    _c->dS(81, 4 + kaku);
    _c->dS(92, -56 + kaku);
    _c->dC(90, -14 + kaku);
    _c->dS(62, -50 + kaku);
    _c->dC(75, -3 + kaku);
    _c->dS(77, -54 + kaku);
    _c->dS(89, 5 + kaku);
    _c->dS(76, -59 + kaku);
    _c->dC(49, 4 + kaku);
    _c->dS(66, -27 + kaku);
    _c->dC(112, 6 + kaku);
    _c->dC(109, -29 + kaku);
    _c->dC(134, 9 + kaku);
    _c->dS(51, -38 + kaku);
    _c->dC(121, -5 + kaku);

}

// カクカクと波波
void CourceManager::cPtn17(CourceMaker* _c){
    setComment("c17",_c);
    auto kaku = 0;
    _c->dC(77, -53 + kaku);
    _c->dS(57, -14 + kaku);
    _c->dS(69, -52 + kaku);
    _c->dC(63, 0 + kaku);
    _c->dS(53, -39 + kaku);
    _c->dS(94, -3 + kaku);
    _c->dS(87, -55 + kaku);
    _c->dS(66, -11 + kaku);
    _c->dC(78, -49 + kaku);
    _c->dC(112, 2 + kaku);
    _c->dS(98, -57 + kaku);
    _c->dS(52, -22 + kaku);
    _c->dS(97, -52 + kaku);
    _c->dC(77, 7 + kaku);
    _c->dC(90, -51 + kaku);
    _c->dC(95, -5 + kaku);
    _c->dC(157, -36 + kaku);
    _c->dS(64, 1 + kaku);
    _c->dC(133, -35 + kaku);
    _c->dC(109, 12 + kaku);

}

// カクカクと波波
void CourceManager::cPtn18(CourceMaker* _c){
    setComment("c18",_c);
    auto kaku = 0;
    _c->dS(100, -35 + kaku);
    _c->dS(54, 3 + kaku);
    _c->dS(100, -29 + kaku);
    _c->dC(140, 8 + kaku);
    _c->dC(114, -27 + kaku);
    _c->dC(89, 7 + kaku);
    _c->dC(69, -45 + kaku);
    _c->dC(108, 7 + kaku);
    _c->dS(75, -28 + kaku);
    _c->dS(91, 11 + kaku);
    _c->dS(65, -23 + kaku);
    _c->dC(138, 8 + kaku);
    _c->dC(114, -41 + kaku);
    _c->dC(83, 14 + kaku);
    _c->dS(77, -37 + kaku);
    _c->dC(148, -1 + kaku);
    _c->dC(95, -43 + kaku);
    _c->dS(54, -4 + kaku);
    _c->dC(71, -56 + kaku);
    _c->dC(63, 8 + kaku);

}

// カクカクと波波
void CourceManager::cPtn19(CourceMaker* _c){
    setComment("c19",_c);
    auto kaku = 06;
    _c->dC(134, -41 + kaku);
    _c->dS(50, 2 + kaku);
    _c->dS(71, -46 + kaku);
    _c->dS(76, -12 + kaku);
    _c->dC(185, -42 + kaku);
    _c->dC(177, -11 + kaku);
    _c->dC(156, -47 + kaku);
    _c->dC(81, 3 + kaku);
    _c->dC(140, -30 + kaku);
    _c->dC(157, 6 + kaku);
    _c->dS(82, -45 + kaku);
    _c->dS(54, 9 + kaku);
    _c->dS(90, -21 + kaku);
    _c->dS(52, 13 + kaku);
    _c->dC(171, -17 + kaku);
    _c->dC(139, 13 + kaku);
    _c->dS(85, -19 + kaku);
    _c->dS(74, 14 + kaku);
    _c->dC(104, -25 + kaku);
    _c->dC(108, 11 + kaku);

}

// 波波と凸
void CourceManager::cPtn20(CourceMaker* _c){
    setComment("c20",_c);
    auto kaku = 0;
    int bufKaku = 0;
    _c->dC(151, -31 + kaku);
    _c->dC(90, 14 + kaku);
    _c->dC(100, -41 + kaku);
    
    bufKaku = -41 + kaku;
    _c->dS(100,bufKaku);
    _c->dS(0,90 + bufKaku);
    _c->dC(10,-90 + bufKaku);
    _c->dS(0, bufKaku);
    
    _c->dC(170, -10 + kaku);
    _c->dC(60, -60 + kaku);
    _c->dC(72, 2 + kaku);
    _c->dC(104, -49 + kaku);
    
    bufKaku = -49 + kaku;
    _c->dS(100,bufKaku);
    _c->dS(0,90 + bufKaku);
    _c->dC(10,-90 + bufKaku);
    _c->dS(0, bufKaku);
    
    _c->dC(71, 1 + kaku);
    _c->dC(133, -35 + kaku);
    _c->dC(84, 14 + kaku);
    _c->dC(70, -53 + kaku);
    
    bufKaku = -53 + kaku;
    _c->dS(100,bufKaku);
    _c->dS(0,90 + bufKaku);
    _c->dC(10,-90 + bufKaku);
    _c->dS(0, bufKaku);
    
    _c->dC(94, -8 + kaku);
    _c->dC(126, -41 + kaku);
    _c->dC(115, 7 + kaku);
    _c->dC(144, -32 + kaku);
    _c->dC(127, 13 + kaku);

}

// 波波と凸
void CourceManager::cPtn21(CourceMaker* _c){
    setComment("c21",_c);
    auto kaku = 0;
    int bufKaku = 0;
    _c->dC(227, -40 + kaku);
    _c->dC(268, -2 + kaku);
    
    bufKaku = -2 + kaku;
    _c->dS(100,bufKaku);
    _c->dS(0,90 + bufKaku);
    _c->dC(10,-90 + bufKaku);
    _c->dS(0, bufKaku);
    
    _c->dC(372, -32 + kaku);
    _c->dC(249, 14 + kaku);
    _c->dC(264, -27 + kaku);
    _c->dC(264, 14 + kaku);
    _c->dC(363, -16 + kaku);
    _c->dC(343, 14 + kaku);
    _c->dC(303, -17 + kaku);
    
    bufKaku = -17 + kaku;
    _c->dS(100,bufKaku);
    _c->dS(0,90 + bufKaku);
    _c->dC(10,-90 + bufKaku);
    _c->dS(0, bufKaku);
    
    _c->dC(274, 15 + kaku);
    _c->dC(264, -19 + kaku);
    _c->dC(334, 13 + kaku);
    _c->dC(178, -38 + kaku);
    
    bufKaku = -38 + kaku;
    _c->dS(100,bufKaku);
    _c->dS(0,90 + bufKaku);
    _c->dC(10,-90 + bufKaku);
    _c->dS(0, bufKaku);
    
    _c->dC(215, 8 + kaku);
    _c->dC(326, -25 + kaku);
    _c->dC(264, 12 + kaku);

}

// 波波と凸
void CourceManager::cPtn22(CourceMaker* _c){
    setComment("c22",_c);
    auto kaku = 0;
    int bufKaku = 0;
    _c->dC(256, -36 + kaku);
    _c->dC(244, 5 + kaku);
    _c->dC(265, -31 + kaku);
    
    bufKaku = -31 + kaku;
    _c->dS(100,bufKaku);
    _c->dS(0,90 + bufKaku);
    _c->dC(30,-90 + bufKaku);
    _c->dS(0, bufKaku);
    
    _c->dC(211, 15 + kaku);
    _c->dC(219, -26 + kaku);
    
    bufKaku = -26 + kaku;
    _c->dS(100,bufKaku);
    _c->dS(0,90 + bufKaku);
    _c->dC(30,-90 + bufKaku);
    _c->dS(0, bufKaku);
    
    _c->dC(359, 4 + kaku);
    _c->dC(338, -26 + kaku);
    _c->dC(292, 12 + kaku);
    _c->dC(178, -37 + kaku);
    
    bufKaku = -37 + kaku;
    _c->dS(100,bufKaku);
    _c->dS(0,90 + bufKaku);
    _c->dC(30,-90 + bufKaku);
    _c->dS(0, bufKaku);
    
    _c->dC(219, 4 + kaku);
    _c->dC(261, -30 + kaku);
    _c->dC(342, 3 + kaku);
    _c->dC(245, -32 + kaku);
    _c->dC(264, 9 + kaku);


}

// 波波と凸
void CourceManager::cPtn23(CourceMaker* _c){
    setComment("c23",_c);
    auto kaku = 0;
    int bufKaku = 0;
    _c->dC(289, -35 + kaku);
    
    bufKaku = -35 + kaku;
    _c->dS(100,bufKaku);
    _c->dS(0,90 + bufKaku);
    _c->dC(30,-90 + bufKaku);
    _c->dS(0, bufKaku);
    
    _c->dC(205, 10 + kaku);
    _c->dC(236, -28 + kaku);
    _c->dC(266, 15 + kaku);
    _c->dC(271, -20 + kaku);
    _c->dC(328, 10 + kaku);
    _c->dC(241, -28 + kaku);
    
    bufKaku = -28 + kaku;
    _c->dS(100,bufKaku);
    _c->dS(0,90 + bufKaku);
    _c->dC(30,-90 + bufKaku);
    _c->dS(0, bufKaku);
    
    _c->dC(237, 12 + kaku);
    _c->dC(376, -18 + kaku);
    _c->dC(297, 15 + kaku);
    _c->dC(170, -39 + kaku);
    
    bufKaku = -39 + kaku;
    _c->dS(100,bufKaku);
    _c->dS(0,90 + bufKaku);
    _c->dC(30,-90 + bufKaku);
    _c->dS(0, bufKaku);
    
    _c->dC(188, 15 + kaku);
    _c->dC(236, -24 + kaku);
    _c->dC(273, 10 + kaku);

}

//  波波と凸特大
void CourceManager::cPtn24(CourceMaker* _c){
    setComment("c24",_c);
    auto kaku = -2;
    int bufKaku = 0;
    _c->dC(521, -33 + kaku);
    
    bufKaku = -28 + kaku;
    _c->dC(30,80 + bufKaku);
    _c->dC(50,-80 + bufKaku);
    _c->dC(30, bufKaku);
    
    _c->dC(412, 3 + kaku);
    _c->dC(543, -28 + kaku);
    
    bufKaku = -28 + kaku;
    _c->dC(30,80 + bufKaku);
    _c->dC(50,-80 + bufKaku);
    _c->dC(30, bufKaku);
    
    _c->dC(375, 15 + kaku);
    _c->dC(534, -16 + kaku);
    
    bufKaku = -28 + kaku;
    _c->dC(30,80 + bufKaku);
    _c->dC(50,-80 + bufKaku);
    _c->dC(30, bufKaku);
    
    _c->dC(508, 15 + kaku);
    
}

//  波波と凸特大
void CourceManager::cPtn25(CourceMaker* _c){
    setComment("c25",_c);
    auto kaku = -2;
    int bufKaku = 0;
    
    _c->dC(540, -30 + kaku);
    
    bufKaku = -30 + kaku;
    _c->dC(30,80 + bufKaku);
    _c->dC(50,-80 + bufKaku);
    _c->dC(30, bufKaku);
    
    _c->dC(358, 14 + kaku);
    _c->dC(504, -20 + kaku);
    
    bufKaku = -20 + kaku;
    _c->dC(30,80 + bufKaku);
    _c->dC(50,-80 + bufKaku);
    _c->dC(30, bufKaku);
    
    _c->dC(467, 11 + kaku);
    _c->dC(419, -26 + kaku);
    
    bufKaku = -26 + kaku;
    _c->dC(30,80 + bufKaku);
    _c->dC(50,-80 + bufKaku);
    _c->dC(30, bufKaku);
    
    _c->dC(429, 9 + kaku);
}

//  波波と凸特大凹
void CourceManager::cPtn26(CourceMaker* _c){
    setComment("c26",_c);
    auto kaku = -2;
    int bufKaku = 0;
    _c->dC(380, -38 + kaku);
    
    bufKaku = -38 + kaku;
    _c->dC(50,-70 + bufKaku);
    _c->dC(50,70 + bufKaku);
    _c->dC(50, bufKaku);
    
    _c->dC(365, 9 + kaku);
    _c->dC(535, -23 + kaku);
    _c->dC(466, 13 + kaku);
    _c->dC(311, -37 + kaku);
    
    bufKaku = -38 + kaku;
    _c->dC(50,-70 + bufKaku);
    _c->dC(50,70 + bufKaku);
    _c->dC(50, bufKaku);
    
    _c->dC(315, 14 + kaku);
    
    bufKaku = -38 + kaku;
    _c->dC(50,-70 + bufKaku);
    _c->dC(50,70 + bufKaku);
    _c->dC(50, bufKaku);
    
    _c->dC(544, -16 + kaku);
    _c->dC(538, 15 + kaku);
}

// 特大凹+カクカク
void CourceManager::cPtn27(CourceMaker* _c){
    setComment("c27",_c);
    auto kaku = -2;
    int bufKaku = 0;
    _c->dS(292, -36 + kaku);
    
    bufKaku = -36 + kaku;
    _c->dC(50,-70 + bufKaku);
    _c->dC(50,70 + bufKaku);
    _c->dC(50, bufKaku);
    
    _c->dS(286, 8 + kaku);
    
    bufKaku = 8 + kaku;
    _c->dC(50,-70 + bufKaku);
    _c->dC(50,70 + bufKaku);
    _c->dC(50, bufKaku);
    
    _c->dS(266, -40 + kaku);
    _c->dS(276, 1 + kaku);
    _c->dS(253, -37 + kaku);
    
    bufKaku = -37 + kaku;
    _c->dC(50,-70 + bufKaku);
    _c->dC(50,70 + bufKaku);
    _c->dC(50, bufKaku);
    
    _c->dS(251, 1 + kaku);
}

// 特大凸凹カクカク
void CourceManager::cPtn28(CourceMaker* _c){
    setComment("c28",_c);
    auto kaku = -2;
    int bufKaku = 0;
    _c->dS(300, -38 + kaku);
    
    bufKaku = -38 + kaku;
    _c->dC(50,-70 + bufKaku);
    _c->dC(50,70 + bufKaku);
    _c->dC(50, bufKaku);
    
    _c->dS(268, -6 + kaku);
    _c->dS(276, -39 + kaku);
    
    bufKaku = -30 + kaku;
    _c->dC(30,80 + bufKaku);
    _c->dC(50,-80 + bufKaku);
    _c->dC(30, bufKaku);
    
    _c->dS(271, 3 + kaku);
    _c->dS(269, -39 + kaku);
    
    bufKaku = -30 + kaku;
    _c->dC(30,80 + bufKaku);
    _c->dC(50,-80 + bufKaku);
    _c->dC(30, bufKaku);
    
    _c->dS(279, 13 + kaku);
    _c->dS(261, -34 + kaku);
   
}

// 特大凸凹波波
void CourceManager::cPtn29(CourceMaker* _c){
    setComment("c29",_c);
    auto kaku = -2;
    int bufKaku = 0;
    _c->dC(389, -38 + kaku);
    
    bufKaku = -30 + kaku;
    _c->dC(30,80 + bufKaku);
    _c->dC(50,-80 + bufKaku);
    _c->dC(30, bufKaku);
    
    _c->dC(323, 7 + kaku);
    _c->dC(532, -24 + kaku);
    
    _c->dC(50,-70 + bufKaku);
    _c->dC(50,70 + bufKaku);
    _c->dC(50, bufKaku);
    
    _c->dC(438, 11 + kaku);
    _c->dC(410, -27 + kaku);
    
    _c->dC(50,-70 + bufKaku);
    _c->dC(50,70 + bufKaku);
    _c->dC(50, bufKaku);
    
    _c->dC(484, 4 + kaku);
    _c->dC(471, -27 + kaku);
    _c->dC(440, 12 + kaku);
    
}

// 細かい段差
void CourceManager::cPtn30(CourceMaker* _c){
    setComment("c30",_c);
    auto kaku = -5;
    _c->dS(44, -67 + kaku);
    _c->dS(39, 0 + kaku);
    _c->dS(32, 45 + kaku);
    _c->dS(30, 0 + kaku);
    _c->dS(50, -51 + kaku);
    _c->dS(47, 0 + kaku);
    _c->dS(31, 69 + kaku);
    _c->dS(30, 0 + kaku);
    _c->dS(41, -72 + kaku);
    _c->dS(48, 0 + kaku);
    _c->dS(32, 8 + kaku);
    _c->dS(35, 0 + kaku);
    _c->dS(41, -90 + kaku);
    _c->dS(34, 0 + kaku);
    _c->dS(46, 48 + kaku);
    _c->dS(32, 0 + kaku);
    _c->dS(34, -28 + kaku);
    _c->dS(39, 0 + kaku);
    _c->dS(50, 61 + kaku);
    _c->dS(37, 0 + kaku);
    _c->dS(43, -60 + kaku);
    _c->dS(37, 0 + kaku);
    _c->dS(32, 1 + kaku);
    _c->dS(47, 0 + kaku);
    _c->dS(30, -64 + kaku);
    _c->dS(39, 0 + kaku);
    _c->dS(32, 8 + kaku);
    _c->dS(31, 0 + kaku);
    _c->dS(44, -83 + kaku);
    _c->dS(43, 0 + kaku);
    _c->dS(42, 68 + kaku);
    _c->dS(43, 0 + kaku);
    _c->dS(45, -81 + kaku);
    _c->dS(35, 0 + kaku);
    _c->dS(46, 34 + kaku);
    _c->dS(34, 0 + kaku);
    _c->dS(41, -37 + kaku);
    _c->dS(36, 0 + kaku);
    _c->dS(34, 45 + kaku);
    _c->dS(37, 0 + kaku);

}

// 細かい段差
void CourceManager::cPtn31(CourceMaker* _c){
    setComment("c31",_c);
    auto kaku = -10;
    _c->dC(58, -85 + kaku);
    _c->dS(147, 12 + kaku);
    _c->dS(94, 0 + kaku);
    _c->dC(79, -48 + kaku);
    _c->dC(61, 52 + kaku);
    _c->dC(76, -31 + kaku);
    _c->dC(110, 30 + kaku);
    _c->dC(60, -88 + kaku);
    _c->dS(135, 24 + kaku);
    _c->dS(124, 0 + kaku);
    _c->dC(91, -61 + kaku);
    _c->dC(72, 50 + kaku);
    _c->dS(95, -70 + kaku);
    _c->dS(108, 0 + kaku);
    _c->dS(150, 26 + kaku);
    _c->dS(144, 0 + kaku);
    _c->dC(94, -36 + kaku);
    _c->dC(102, 31 + kaku);
    _c->dC(66, -51 + kaku);
    _c->dS(137, 44 + kaku);
    _c->dS(92, 0 + kaku);
    _c->dC(96, -20 + kaku);
    _c->dS(144, 45 + kaku);
    _c->dS(127, 0 + kaku);
    _c->dS(145, -19 + kaku);
    _c->dS(146, 0 + kaku);
    _c->dS(130, 54 + kaku);
    _c->dS(110, 0 + kaku);

}

// 細かい段差
void CourceManager::cPtn32(CourceMaker* _c){
    setComment("c32",_c);
    auto kaku = -5;
    _c->dS(58, -69 + kaku);
    _c->dS(65, 0 + kaku);
    _c->dS(64, 21 + kaku);
    _c->dS(79, 0 + kaku);
    _c->dS(64, -61 + kaku);
    _c->dS(59, 0 + kaku);
    _c->dS(60, 8 + kaku);
    _c->dS(53, 0 + kaku);
    _c->dS(53, -80 + kaku);
    _c->dS(69, 0 + kaku);
    _c->dS(65, 51 + kaku);
    _c->dS(63, 0 + kaku);
    _c->dS(75, -52 + kaku);
    _c->dS(55, 0 + kaku);
    _c->dS(55, 43 + kaku);
    _c->dS(74, 0 + kaku);
    _c->dS(71, -63 + kaku);
    _c->dS(63, 0 + kaku);
    _c->dS(70, 48 + kaku);
    _c->dS(63, 0 + kaku);
    _c->dS(71, -65 + kaku);
    _c->dS(61, 0 + kaku);
    _c->dS(53, 52 + kaku);
    _c->dS(50, 0 + kaku);
    _c->dS(70, -13 + kaku);
    _c->dS(57, 0 + kaku);
    _c->dS(78, 55 + kaku);
    _c->dS(53, 0 + kaku);
    _c->dS(67, -55 + kaku);
    _c->dS(79, 0 + kaku);
    _c->dS(65, 28 + kaku);
    _c->dS(51, 0 + kaku);
    _c->dS(75, -74 + kaku);
    _c->dS(61, 0 + kaku);
    _c->dS(63, -8 + kaku);
    _c->dS(77, 0 + kaku);
    _c->dS(53, -77 + kaku);
    _c->dS(80, 0 + kaku);
    _c->dS(50, -5 + kaku);
    _c->dS(69, 0 + kaku);


}

// なだらかな段差
void CourceManager::cPtn33(CourceMaker* _c){
    setComment("c33",_c);
    auto kaku = 0;
    _c->dS(80, -70 + kaku);
    _c->dC(145, 0 + kaku);
    _c->dS(51, 0 + kaku);
    _c->dC(28, 44 + kaku);
    _c->dS(56, 44 + kaku);
    _c->dS(68, 0 + kaku);
    _c->dS(56, -61 + kaku);
    _c->dC(110, 0 + kaku);
    _c->dS(53, 0 + kaku);
    _c->dC(25, 59 + kaku);
    _c->dS(53, 59 + kaku);
    _c->dS(78, 0 + kaku);
    _c->dS(58, -54 + kaku);
    _c->dC(109, 0 + kaku);
    _c->dS(69, 0 + kaku);
    _c->dC(34, 55 + kaku);
    _c->dS(65, 55 + kaku);
    _c->dS(74, 0 + kaku);
    _c->dS(79, -69 + kaku);
    _c->dC(116, 0 + kaku);
    _c->dS(73, 0 + kaku);
    _c->dC(32, 45 + kaku);
    _c->dS(65, 45 + kaku);
    _c->dS(79, 0 + kaku);
    _c->dS(77, -64 + kaku);
    _c->dC(120, 0 + kaku);
    _c->dS(80, 0 + kaku);
    _c->dC(29, 47 + kaku);
    _c->dS(57, 47 + kaku);
    _c->dS(57, 0 + kaku);

}

// なだらかな段差
void CourceManager::cPtn34(CourceMaker* _c){
    setComment("c34",_c);
    auto kaku = 0;
    _c->dS(73, -70 + kaku);
    _c->dC(139, 0 + kaku);
    _c->dS(79, 0 + kaku);
    _c->dC(37, 50 + kaku);
    _c->dS(79, 50 + kaku);
    _c->dS(72, 0 + kaku);
    _c->dS(71, -57 + kaku);
    _c->dC(118, 0 + kaku);
    _c->dS(50, 0 + kaku);
    _c->dC(42, 43 + kaku);
    _c->dS(74, 43 + kaku);
    _c->dS(72, 0 + kaku);
    _c->dS(73, -69 + kaku);
    _c->dC(117, 0 + kaku);
    _c->dS(56, 0 + kaku);
    _c->dC(32, 43 + kaku);
    _c->dS(63, 43 + kaku);
    _c->dS(71, 0 + kaku);
    _c->dS(65, -64 + kaku);
    _c->dC(114, 0 + kaku);
    _c->dS(54, 0 + kaku);
    _c->dC(28, 45 + kaku);
    _c->dS(55, 45 + kaku);
    _c->dS(56, 0 + kaku);
    _c->dS(66, -59 + kaku);
    _c->dC(116, 0 + kaku);
    _c->dS(61, 0 + kaku);
    _c->dC(29, 53 + kaku);
    _c->dS(58, 53 + kaku);
    _c->dS(66, 0 + kaku);

}

// なだらかな段差
void CourceManager::cPtn35(CourceMaker* _c){
    setComment("c35",_c);
    auto kaku = 0;
    _c->dS(53, -70 + kaku);
    _c->dC(123, 0 + kaku);
    _c->dS(60, 0 + kaku);
    _c->dC(31, 43 + kaku);
    _c->dS(62, 43 + kaku);
    _c->dS(72, 0 + kaku);
    _c->dS(57, -65 + kaku);
    _c->dC(110, 0 + kaku);
    _c->dS(80, 0 + kaku);
    _c->dC(36, 59 + kaku);
    _c->dS(79, 59 + kaku);
    _c->dS(58, 0 + kaku);
    _c->dS(67, -57 + kaku);
    _c->dC(113, 0 + kaku);
    _c->dS(57, 0 + kaku);
    _c->dC(32, 60 + kaku);
    _c->dS(66, 60 + kaku);
    _c->dS(78, 0 + kaku);
    _c->dS(75, -62 + kaku);
    _c->dC(115, 0 + kaku);
    _c->dS(58, 0 + kaku);
    _c->dC(37, 60 + kaku);
    _c->dS(79, 60 + kaku);
    _c->dS(70, 0 + kaku);
    _c->dS(69, -69 + kaku);
    _c->dC(110, 0 + kaku);
    _c->dS(50, 0 + kaku);
    _c->dC(36, 51 + kaku);
    _c->dS(76, 51 + kaku);
    _c->dS(55, 0 + kaku);

}

// 激しい波波
void CourceManager::cPtn36(CourceMaker* _c){
    setComment("c36",_c);
    auto kaku = 0;
    _c->dC(84, -73 + kaku);
    _c->dC(70, -11 + kaku);
    _c->dC(89, -74 + kaku);
    _c->dC(77, 13 + kaku);
    _c->dC(103, -49 + kaku);
    _c->dC(73, 36 + kaku);
    _c->dC(114, -24 + kaku);
    _c->dC(100, 38 + kaku);
    _c->dC(97, -26 + kaku);
    _c->dC(65, 30 + kaku);
    _c->dC(62, -71 + kaku);
    _c->dC(80, -12 + kaku);
    _c->dC(128, -54 + kaku);
    _c->dC(117, -1 + kaku);
    _c->dC(68, -74 + kaku);
    _c->dC(132, -29 + kaku);
    _c->dC(91, -73 + kaku);
    _c->dC(85, 7 + kaku);
    _c->dC(61, -70 + kaku);
    _c->dC(44, 12 + kaku);

}

// 激しい波波
void CourceManager::cPtn37(CourceMaker* _c){
    setComment("c37",_c);
    auto kaku = 0;
    _c->dC(85, -77 + kaku);
    _c->dC(84, -10 + kaku);
    _c->dC(74, -58 + kaku);
    _c->dC(61, 18 + kaku);
    _c->dC(107, -43 + kaku);
    _c->dC(96, 15 + kaku);
    _c->dC(59, -46 + kaku);
    _c->dC(72, 11 + kaku);
    _c->dC(104, -33 + kaku);
    _c->dC(95, 18 + kaku);
    _c->dC(69, -79 + kaku);
    _c->dC(56, 40 + kaku);
    _c->dC(26, -88 + kaku);
    _c->dC(41, 15 + kaku);
    _c->dC(44, -73 + kaku);
    _c->dC(69, -7 + kaku);
    _c->dC(113, -63 + kaku);
    _c->dC(107, -18 + kaku);
    _c->dC(118, -59 + kaku);
    _c->dC(71, 14 + kaku);

}

// モアイ
void CourceManager::cPtn38(CourceMaker* _c){
    setComment("c38",_c);
    auto kaku = -15;
    _c->dS(100,0+kaku);
    _c->dS(10,80+kaku);
    _c->dC(30,23+kaku);
    _c->dS(60,23+kaku);
    _c->dC(5,-50+kaku);
    _c->dS(40,-50+kaku);
    _c->dS(80,30+kaku);
    _c->dC(200,55+kaku);
    _c->dC(10,-70+kaku);
    _c->dS(80,-70+kaku);
    _c->dS(30,10+kaku);
    _c->dS(0,-80+kaku);
    _c->dC(60,80+kaku);
    _c->dC(5,-10+kaku);
    _c->dS(30,-10+kaku);
    _c->dC(10,-90+kaku);
    _c->dS(70,-90+kaku);
    _c->dS(50,0+kaku);
}

// 連続した石柱
void CourceManager::cPtn39(CourceMaker* _c){
    setComment("c39",_c);
    auto kaku = _c->_dirkaku;
    _c->dC(30,-5);
    _c->dS(150,-20);
    for(int i=0;i<3;i++){
        _c->dS(40,70);
        _c->dC(10,-110);
        _c->dS(40,-90);
        _c->dS(150,-20);
    }
    _c->dS(50,0);
}
// 富士山
void CourceManager::cPtn40(CourceMaker* _c){
    setComment("c40",_c);
    auto kaku = _c->_dirkaku;
    _c->dC(100,-20);
    _c->dS(100,-20);
    _c->dC(50,70);
    _c->dS(0,-60);
    _c->dC(30,60);
    _c->dS(0,-70);
    _c->dC(50,0);
    _c->dS(30,0);
}

// 富士山
void CourceManager::cPtn41(CourceMaker* _c){
    setComment("c41",_c);
    auto kaku = _c->_dirkaku;
    _c->dC(100,-20);
    _c->dS(150,-20);
    _c->dC(100,70);
    _c->dS(0,-60);
    _c->dC(50,60);
    _c->dS(0,-70);
    _c->dC(100,0);
    _c->dS(30,0);
}

// 富士山
void CourceManager::cPtn42(CourceMaker* _c){
    setComment("c42",_c);
    auto kaku = _c->_dirkaku;
    _c->dS(10,kaku);
    _c->dC(100,75);
    _c->dS(100,0);
    _c->dC(100,0);
    _c->dS(100,0);
}

// 富士山
void CourceManager::cPtn43(CourceMaker* _c){
    setComment("c43",_c);
    auto kaku = _c->_dirkaku;
    _c->dS(100,kaku);
    _c->dC(40,85);
    _c->dS(50,0);
    _c->dC(40,0);
    _c->dS(100,0);
}

// 角富士山
void CourceManager::cPtn44(CourceMaker* _c){
    setComment("c44",_c);
    auto kaku = _c->_dirkaku;
    _c->dS(120,kaku);
    _c->dS(80,kaku + 45);
    _c->dS(80,-90);
    _c->dS(50,0);
    _c->dS(80,90);
    _c->dS(80,kaku);
}

// なだらかな坂と石ころ
void CourceManager::cPtn45(CourceMaker* _c){
    setComment("c45",_c);
    auto kaku = _c->_dirkaku;
    _c->dC(30,-5);
    _c->dS(100,-5);
    _c->dC(300,-20);
    _c->dS(0,70);
    _c->dC(10,-110);
    _c->dS(0,-20);
    _c->dC(300,-45);
    _c->dC(40,20);
    _c->dS(50,20);
    _c->dC(80,0);
    _c->dS(50,0);
}

// 凸小凹大
void CourceManager::cPtn46(CourceMaker* _c){
    setComment("c46",_c);
    auto kaku = _c->_dirkaku;
    _c->dC(30,0);
    _c->dS(100,0);
    _c->dS(0,90);
    _c->dC(20,-90);
    _c->dC(60,80);
    _c->dS(50,0);
}

// 凸小凹大
void CourceManager::cPtn47(CourceMaker* _c){
    setComment("c47",_c);
    auto kaku = _c->_dirkaku;
    _c->dC(30,kaku);
    _c->dS(100,kaku);
    _c->dS(0,90+kaku);
    _c->dC(20,-90+kaku);
    _c->dC(60,80+kaku);
    _c->dS(50,kaku);
}

// なだらかな坂と石柱
void CourceManager::cPtn48(CourceMaker* _c){
    setComment("c48",_c);
    auto kaku = _c->_dirkaku;
    _c->dC(30,-5);
    _c->dS(100,-5);
    _c->dC(300,-20);
    _c->dS(40,70);
    _c->dC(10,-110);
    _c->dS(40,-90);
    _c->dS(0,-20);
    _c->dC(300,-45);
    _c->dC(40,20);
    _c->dS(50,20);
    _c->dC(80,0);
    _c->dS(50,0);
}

// 凸小凹大
void CourceManager::cPtn49(CourceMaker* _c){
    setComment("c49",_c);
    auto kaku = _c->_dirkaku;
    _c->dC(30,0);
    _c->dS(100,0);
    _c->dS(0,90);
    _c->dC(30,-60);
    _c->dC(60,90);
    _c->dS(50,0);
}

// 凸小凹大
void CourceManager::cPtn50(CourceMaker* _c){
    setComment("c50",_c);
    auto kaku = _c->_dirkaku;
    _c->dC(30,kaku);
    _c->dS(100,kaku);
    _c->dS(0,90+kaku);
    _c->dC(30,-60+kaku);
    _c->dC(60,90+kaku);
    _c->dS(50,kaku);
}

// 3連穴ジャンプ
void CourceManager::cPtn51(CourceMaker* _c){
    setComment("c51",_c);
    auto kaku = _c->_dirkaku;
    _c->dS(100, 0);
    for(int i=0;i<3;i++){
        _c->dS(100, -90);
        _c->dS(70, 0);
        _c->dS(100, 90);
        _c->dS(100, 0);
    }
}

// 波波プッシュ10連
void CourceManager::cPtn52(CourceMaker* _c){
    setComment("c52",_c);
    auto kaku = _c->_dirkaku;
    
    _c->dC(100,-45);
    for(int i=0;i<10;i++){
        _c->dC(30,-45);
        _c->dC(80,45);
    }
    _c->dS(100,0);
}

// 段差上り
void CourceManager::cPtn53(CourceMaker* _c){
    setComment("c53",_c);
    auto kaku = _c->_dirkaku;
    _c->dS(180,0);
    for(int i=0;i<3;i++){
        _c->dS(30,90);
        _c->dS(180,0);
    }
    _c->dS(80,0);
}

// 段差上り
void CourceManager::cPtn54(CourceMaker* _c){
    setComment("c54",_c);
    auto kaku = _c->_dirkaku;
    _c->dS(70,-10);
    for(int i=0;i<8;i++){
        _c->dS(20,80);
        _c->dS(120,-10);
    }
    _c->dS(80,0);
}

// 段差上り
void CourceManager::cPtn55(CourceMaker* _c){
    setComment("c55",_c);
    auto kaku = _c->_dirkaku;
    for(int i=0;i<3;i++){
    _c->dS(100,0);
    _c->dC(30,60);
    _c->dS(30,-90);
    _c->dS(60,0);
    _c->dS(50,90);
    }
    _c->dS(150,0);
}

// 穴ジャンプA
void CourceManager::cPtn56(CourceMaker* _c){
    setComment("c56",_c);
    auto kaku = _c->_dirkaku;
    _c->dC(200, -50);
    _c->dC(200, 0);
    _c->dS(100, -90);
    _c->dS(60, 0);
    _c->dS(120, 90);
    _c->dS(50, 0);
}

// 段差＋ジャンプ穴
void CourceManager::cPtn57(CourceMaker* _c){
    setComment("c57",_c);
    _c->dS(200, -20);
    _c->dS(20, 70);
    _c->dS(200, -20);
    _c->dC(50, 50);
    _c->dS(100,-90);
    _c->dS(50, 0);
    _c->dS(130,90);
    _c->dS(50, 0);
}

// 2段ジャンプ
void CourceManager::cPtn58(CourceMaker* _c){
    setComment("c58",_c);
    auto kaku = _c->_dirkaku;
    _c->dC(30,-5);
    _c->dS(100,-5);
    for(int i = 0;i<2;i++){
        _c->dS(50,-90);
        _c->dS(80,0);
        _c->dS(50,90);
        _c->dS(50,0);
    }
    _c->dS(50,0);
}

// モアイ
void CourceManager::cPtn59(CourceMaker* _c){
    setComment("c59",_c);
    auto kaku = _c->_dirkaku;
    _c->dS(100,0);
    _c->dS(10,80);
    _c->dC(30,23);
    _c->dS(60,23);
    _c->dC(5,-50);
    _c->dS(40,-50);
    _c->dS(80,30);
    _c->dC(200,55);
    _c->dC(10,-70);
    _c->dS(80,-70);
    _c->dS(30,10);
    _c->dS(0,-80);
    _c->dC(60,80);
    _c->dC(5,-10);
    _c->dS(30,-10);
    _c->dC(10,-90);
    _c->dS(70,-90);
    _c->dS(50,0);
}

// 3段段差穴下り
void CourceManager::cPtn60(CourceMaker* _c){
    setComment("c60",_c);
    auto kaku = _c->_dirkaku;
    _c->dS(100,kaku);
    for(int i=0;i<3;i++){
        _c->dS(100,-90);
        _c->dS(80,0);
        _c->dS(100,90);
        _c->dS(70,kaku);
    }
    _c->dS(30,kaku);
}

// スーパー幅跳び
void CourceManager::cPtn61(CourceMaker* _c){
    setComment("c61",_c);
    auto kaku = _c->_dirkaku;
    _c->dS(150,-20);
    _c->dC(40,0);
    _c->dS(150,0);
    _c->dS(0,90);
    _c->dC(10,-90);
    _c->dS(100,-90);
    _c->dS(100,0);
    _c->dS(100,90);
    _c->dS(50,0);
}

// ジャンプ台+石柱ごえ
void CourceManager::cPtn62(CourceMaker* _c){
    setComment("c62",_c);
    auto kaku = _c->_dirkaku;
    _c->dC(80,-45);
    _c->dS(500,-45);
    _c->dC(50,45);
    _c->dS(150,0);
    _c->dS(100,90);
    _c->dC(10,-90);
    _c->dS(100,-90);
    _c->dS(200,0);
}

// ジャンプ台＋段差
void CourceManager::cPtn63(CourceMaker* _c){
    setComment("c63",_c);
    auto kaku = _c->_dirkaku;
    _c->dC(80,-45);
    _c->dS(300,-45);
    _c->dC(20,0);
    _c->dC(20,-45);
    _c->dS(180,-45);
    _c->dC(50,45);
    _c->dS(100,-90);
    _c->dS(200,0);
    _c->dS(100,90);
    _c->dS(100,0);
}

// comment
void CourceManager::cPtn64(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn65(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn66(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn67(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn68(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn69(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn70(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn71(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn72(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn73(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn74(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn75(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn76(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn77(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn78(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn79(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn80(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn81(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn82(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn83(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn84(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn85(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn86(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn87(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn88(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn89(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn90(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn91(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn92(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn93(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn94(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn95(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn96(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn97(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn98(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn99(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn100(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn101(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn102(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn103(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn104(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn105(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn106(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn107(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn108(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn109(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn110(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn111(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn112(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn113(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn114(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn115(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn116(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn117(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn118(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn119(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn120(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn121(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn122(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn123(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}
/** パラメータサンプル
 setCourceMakerA(CourceMaker::create());
 getCourceMakerA();
 setCourceMakerB(CourceMaker::create());
 getCourceMakerB();
 */
