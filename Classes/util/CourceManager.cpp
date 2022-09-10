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
            _c->dC(30,-10);
            for(int i=0;i<2;i++){
                cPtn00(_c);
                _c->dC(30,-90);
                _c->dS(30,-10);
            }
            break;
        case 2:
            for(int i=0;i<2;i++){
                cPtn01(_c);
            }
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
            _c->dC(30,-10);
            for(int i=0;i<2;i++){
                cPtn02(_c);
                _c->dC(30,-90);
                _c->dS(30,-10);
            }
            break;
        case 2:
            for(int i=0;i<2;i++){
                cPtn03(_c);
            }
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
            _c->dC(30,-10);
            for(int i=0;i<2;i++){
                cPtn05(_c);
                cPtn07(_c);
                cPtn10(_c);
            }
            break;
        case 2:
            for(int i=0;i<2;i++){
                cPtn12(_c);
                cPtn07(_c);
                cPtn11(_c);
            }
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
            _c->dC(30,-10);
            for(int i=0;i<2;i++){
                cPtn09(_c);
                cPtn13(_c);
                cPtn14(_c);
            }
            break;
        case 2:
            for(int i=0;i<2;i++){
                cPtn15(_c);
                cPtn07(_c);
                cPtn20(_c);
            }
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
            _c->dC(30,-10);
            for(int i=0;i<2;i++){
                cPtn09(_c);
                cPtn12(_c);
                cPtn15(_c);
            }
            break;
        case 2:
            for(int i=0;i<2;i++){
                cPtn15(_c);
                cPtn02(_c);
                cPtn22(_c);
            }
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
            _c->dC(30,-10);
            for(int i=0;i<2;i++){
                cPtn14(_c);
                cPtn21(_c);
                cPtn14(_c);
            }
            break;
        case 2:
            for(int i=0;i<2;i++){
                cPtn30(_c);
                cPtn17(_c);
                cPtn24(_c);
            }
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
            _c->dC(30,-10);
            for(int i=0;i<2;i++){
                cPtn09(_c);
                cPtn25(_c);
                cPtn34(_c);
            }
            break;
        case 2:
            for(int i=0;i<2;i++){
                cPtn35(_c);
                cPtn04(_c);
                cPtn23(_c);
            }
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
            _c->dC(30,-10);
            for(int i=0;i<2;i++){
                cPtn03(_c);
                cPtn16(_c);
                cPtn44(_c);
            }
            break;
        case 2:
            for(int i=0;i<2;i++){
                cPtn35(_c);
                cPtn37(_c);
                cPtn20(_c);
            }
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
            _c->dC(30,-10);
            for(int i=0;i<2;i++){
                cPtn04(_c);
                cPtn19(_c);
                cPtn24(_c);
            }
            break;
        case 2:
            for(int i=0;i<2;i++){
                cPtn25(_c);
                cPtn16(_c);
                cPtn40(_c);
            }
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
            _c->dC(30,-10);
            for(int i=0;i<2;i++){
                cPtn08(_c);
                cPtn34(_c);
                cPtn36(_c);
            }
            break;
        case 2:
            for(int i=0;i<2;i++){
                cPtn32(_c);
                cPtn33(_c);
                cPtn20(_c);
            }
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
            _c->dC(30,-10);
            for(int i=0;i<2;i++){
                cPtn05(_c);
                cPtn11(_c);
                cPtn42(_c);
            }
            break;
        case 2:
            for(int i=0;i<2;i++){
                cPtn45(_c);
                cPtn37(_c);
                cPtn29(_c);
            }
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
            _c->dC(30,-10);
            for(int i=0;i<2;i++){
                cPtn19(_c);
                cPtn43(_c);
                cPtn44(_c);
            }
            break;
        case 2:
            for(int i=0;i<2;i++){
                cPtn50(_c);
                cPtn49(_c);
                cPtn20(_c);
            }
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
            _c->dC(30,-10);
            for(int i=0;i<2;i++){
                cPtn19(_c);
                cPtn13(_c);
                cPtn48(_c);
            }
            break;
        case 2:
            for(int i=0;i<2;i++){
                cPtn45(_c);
                cPtn47(_c);
                cPtn32(_c);
            }
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
            _c->dC(30,-10);
            for(int i=0;i<2;i++){
                cPtn29(_c);
                cPtn13(_c);
                cPtn54(_c);
            }
            break;
        case 2:
            for(int i=0;i<2;i++){
                cPtn45(_c);
                cPtn47(_c);
                cPtn23(_c);
            }
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
            _c->dC(30,-10);
            for(int i=0;i<2;i++){
                cPtn39(_c);
                cPtn43(_c);
                cPtn56(_c);
            }
            break;
        case 2:
            for(int i=0;i<2;i++){
                cPtn49(_c);
                cPtn44(_c);
                cPtn43(_c);
            }
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
            _c->dC(30,-10);
            for(int i=0;i<2;i++){
                cPtn59(_c);
                cPtn53(_c);
                cPtn56(_c);
            }
            break;
        case 2:
            for(int i=0;i<2;i++){
                cPtn39(_c);
                cPtn48(_c);
                cPtn45(_c);
            }
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
            _c->dC(30,-10);
            for(int i=0;i<2;i++){
                cPtn49(_c);
                cPtn43(_c);
                cPtn54(_c);
            }
            break;
        case 2:
            for(int i=0;i<2;i++){
                cPtn59(_c);
                cPtn17(_c);
                cPtn60(_c);
            }
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
            _c->dC(30,-10);
            for(int i=0;i<2;i++){
                cPtn51(_c);
                cPtn41(_c);
                cPtn52(_c);
            }
            break;
        case 2:
            for(int i=0;i<2;i++){
                cPtn53(_c);
                cPtn55(_c);
                cPtn61(_c);
            }
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
            _c->dC(30,-10);
            for(int i=0;i<2;i++){
                cPtn62(_c);
                cPtn57(_c);
                cPtn61(_c);
            }
            break;
        case 2:
            for(int i=0;i<2;i++){
                cPtn60(_c);
                cPtn27(_c);
                cPtn22(_c);
            }
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
            _c->dC(30,-10);
            for(int i=0;i<2;i++){
                cPtn63(_c);
                cPtn62(_c);
                cPtn34(_c);
            }
            break;
        case 2:
            for(int i=0;i<2;i++){
                cPtn35(_c);
                cPtn56(_c);
                cPtn61(_c);
            }
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
                        setComment("c71",_c);
                        cPtn71(_c);
                        break;
                    case 72:
                        setComment("c72",_c);
                        cPtn72(_c);
                        break;
                    case 73:
                        setComment("c73",_c);
                        cPtn73(_c);
                        break;
                    case 74:
                        setComment("c74",_c);
                        cPtn74(_c);
                        break;
                    case 75:
                        setComment("c75",_c);
                        cPtn75(_c);
                        break;
                    case 76:
                        setComment("c76",_c);
                        cPtn76(_c);
                        break;
                    case 77:
                        setComment("c77",_c);
                        cPtn77(_c);
                        break;
                    case 78:
                        setComment("c78",_c);
                        cPtn78(_c);
                        break;
                    case 79:
                        setComment("c79",_c);
                        cPtn79(_c);
                        break;
                    case 80:
                        setComment("c80",_c);
                        cPtn80(_c);
                        break;
                    case 81:
                        setComment("c81",_c);
                        cPtn81(_c);
                        break;
                    case 82:
                        setComment("c82",_c);
                        cPtn82(_c);
                        break;
                    case 83:
                        setComment("c83",_c);
                        cPtn83(_c);
                        break;
                    case 84:
                        setComment("c84",_c);
                        cPtn84(_c);
                        break;
                    case 85:
                        setComment("c85",_c);
                        cPtn85(_c);
                        break;
                    case 86:
                        setComment("c86",_c);
                        cPtn86(_c);
                        break;
                    case 87:
                        setComment("c87",_c);
                        cPtn87(_c);
                        break;
                    case 88:
                        setComment("c88",_c);
                        cPtn88(_c);
                        break;
                    case 89:
                        setComment("c89",_c);
                        cPtn89(_c);
                        break;
                    case 90:
                        setComment("c90",_c);
                        cPtn90(_c);
                        break;
                    case 91:
                        setComment("c91",_c);
                        cPtn91(_c);
                        break;
                    case 92:
                        setComment("c92",_c);
                        cPtn92(_c);
                        break;
                    case 93:
                        setComment("c93",_c);
                        cPtn93(_c);
                        break;
                    case 94:
                        setComment("c94",_c);
                        cPtn94(_c);
                        break;
                    case 95:
                        setComment("c95",_c);
                        cPtn95(_c);
                        break;
                    case 96:
                        setComment("c96",_c);
                        cPtn96(_c);
                        break;
                    case 97:
                        setComment("c97",_c);
                        cPtn97(_c);
                        break;
                    case 98:
                        setComment("c98",_c);
                        cPtn98(_c);
                        break;
                    case 99:
                        setComment("c99",_c);
                        cPtn99(_c);
                        break;
                    case 100:
                        setComment("c100",_c);
                        cPtn100(_c);
                        break;
                    case 101:
                        setComment("c101",_c);
                        cPtn101(_c);
                        break;
                    case 102:
                        setComment("c102",_c);
                        cPtn102(_c);
                        break;
                    case 103:
                        setComment("c103",_c);
                        cPtn103(_c);
                        break;
                    case 104:
                        setComment("c104",_c);
                        cPtn104(_c);
                        break;
                    case 105:
                        setComment("c105",_c);
                        cPtn105(_c);
                        break;
                    case 106:
                        setComment("c106",_c);
                        cPtn106(_c);
                        break;
                    case 107:
                        setComment("c107",_c);
                        cPtn107(_c);
                        break;
                    case 108:
                        setComment("c108",_c);
                        cPtn108(_c);
                        break;
                    case 109:
                        setComment("c109",_c);
                        cPtn109(_c);
                        break;
                    case 110:
                        setComment("c110",_c);
                        cPtn110(_c);
                        break;
                    case 111:
                        setComment("c111",_c);
                        cPtn111(_c);
                        break;
                    case 112:
                        setComment("c112",_c);
                        cPtn112(_c);
                        break;
                    case 113:
                        setComment("c113",_c);
                        cPtn113(_c);
                        break;
                    case 114:
                        setComment("c114",_c);
                        cPtn114(_c);
                        break;
                    case 115:
                        setComment("c115",_c);
                        cPtn115(_c);
                        break;
                    case 116:
                        setComment("c116",_c);
                        cPtn116(_c);
                        break;
                    case 117:
                        setComment("c117",_c);
                        cPtn117(_c);
                        break;
                    case 118:
                        setComment("c118",_c);
                        cPtn118(_c);
                        break;
                    case 119:
                        setComment("c119",_c);
                        cPtn119(_c);
                        break;
                    case 120:
                        setComment("c120",_c);
                        cPtn120(_c);
                        break;
                    case 121:
                        setComment("c121",_c);
                        cPtn121(_c);
                        break;
                    case 122:
                        setComment("c122",_c);
                        cPtn122(_c);
                        break;
                    case 123:
                        setComment("c123",_c);
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
    for(int i=0;i<4;i++){
        _c->dC(180,-10+kaku);
        _c->dC(180,5 + kaku);
    }
    _c->dC(180,kaku);
}

// 滑らかな波波
void CourceManager::cPtn01(CourceMaker* _c){
    setComment("c01",_c);
    auto kaku = -5;
    for(int i=0;i<4;i++){
        _c->dC(80,-25+kaku);
        _c->dC(80,20 + kaku);
    }
    _c->dC(80,kaku);
}

// 滑らかな波波
void CourceManager::cPtn02(CourceMaker* _c){
    setComment("c02",_c);
    auto kaku = -1;
    for(int i=0;i<4;i++){
        _c->dC(80,-40+kaku);
        _c->dC(80,20+kaku);
    }
    _c->dC(80,kaku);
}

// 滑らかな波波
void CourceManager::cPtn03(CourceMaker* _c){
    setComment("c03",_c);
    auto kaku = -7;
    for(int i=0;i<4;i++){
        _c->dC(80,-50+kaku);
        _c->dC(80,45+kaku);
    }
    _c->dC(80,kaku);
}

// 滑らかな波波
void CourceManager::cPtn04(CourceMaker* _c){
    setComment("c04",_c);
    auto kaku = -5;
    _c->dC(80,-25+kaku);
    _c->dC(80,kaku);
    _c->dC(80,-50+kaku);
    _c->dC(80,kaku);
    _c->dC(80,-25+kaku);
    _c->dC(80,kaku);
    _c->dC(80,-70+kaku);
    _c->dC(80,kaku);
}

// 滑らかな波波
void CourceManager::cPtn05(CourceMaker* _c){
    setComment("c05",_c);
    auto kaku = -4;
    _c->dC(120,-25+kaku);
    _c->dC(80,5+kaku);
    _c->dC(130,-60+kaku);
    _c->dC(100,kaku);
    _c->dC(180,-45+kaku);
    _c->dC(80,kaku);
    _c->dC(300,-60+kaku);
    _c->dC(120,kaku);
}

// 滑らかな波波
void CourceManager::cPtn06(CourceMaker* _c){
    setComment("c06",_c);
    auto kaku = -3;
    _c->dC(50,-70+kaku);
    _c->dC(50,5+kaku);
    _c->dC(50,-70+kaku);
    _c->dC(50,5+kaku);
    _c->dC(50,-70+kaku);
    _c->dC(50,kaku);
}

// 滑らかな波波
void CourceManager::cPtn07(CourceMaker* _c){
    setComment("c07",_c);
    auto kaku = -5;
    _c->dC(300,-70+kaku);
    _c->dC(80,5+kaku);
    _c->dC(50,-70+kaku);
    _c->dC(100,kaku);
}

// comment
void CourceManager::cPtn08(CourceMaker* _c){
    setComment("c08",_c);
    auto kaku = -5;
    _c->dC(90,-45+kaku);
    _c->dC(150,5+kaku);
    _c->dC(130,-70+kaku);
    _c->dC(50,5+kaku);
    _c->dC(50,-30+kaku);
    _c->dC(50,kaku);
}

// 滑らかな波波
void CourceManager::cPtn09(CourceMaker* _c){
    setComment("c09",_c);
    auto kaku = -5;
    _c->dC(90,-45+kaku);
    _c->dC(150,5+kaku);
    _c->dC(130,-45+kaku);
    _c->dC(50,5+kaku);
    _c->dC(90,-90+kaku);
    _c->dC(50,kaku);
}

// カクカク
void CourceManager::cPtn10(CourceMaker* _c){
    setComment("c10",_c);
    auto kaku = -7;
    for(int i=0;i<4;i++){
        _c->dS(180,-10+kaku);
        _c->dS(180,5 + kaku);
    }
    _c->dS(180,kaku);
}

// カクカク
void CourceManager::cPtn11(CourceMaker* _c){
    setComment("c12",_c);
    auto kaku = -5;
    for(int i=0;i<4;i++){
        _c->dS(80,-25+kaku);
        _c->dS(80,20 + kaku);
    }
    _c->dS(80,kaku);
}

// カクカク
void CourceManager::cPtn12(CourceMaker* _c){
    auto kaku = -6;
    for(int i=0;i<4;i++){
        _c->dS(80,-40+kaku);
        _c->dS(80,20+kaku);
    }
    _c->dS(80,kaku);
}

// カクカク
void CourceManager::cPtn13(CourceMaker* _c){
    setComment("c13",_c);
    auto kaku = -7;
    for(int i=0;i<4;i++){
        _c->dS(80,-50+kaku);
        _c->dS(80,45+kaku);
    }
    _c->dS(80,kaku);
}

// カクカク
void CourceManager::cPtn14(CourceMaker* _c){
    setComment("c14",_c);
    auto kaku = 0;
    _c->dS(80,-25+kaku);
    _c->dS(80,kaku);
    _c->dS(80,-50+kaku);
    _c->dS(80,kaku);
    _c->dS(80,-25+kaku);
    _c->dS(80,kaku);
    _c->dS(80,-70+kaku);
    _c->dS(80,kaku);
}

// カクカク
void CourceManager::cPtn15(CourceMaker* _c){
    setComment("c15",_c);
    auto kaku = -10;
    _c->dS(120,-25+kaku);
    _c->dS(80,5+kaku);
    _c->dS(130,-60+kaku);
    _c->dS(100,kaku);
    _c->dS(180,-45+kaku);
    _c->dS(80,kaku);
    _c->dS(300,-60+kaku);
    _c->dS(120,kaku);
}

// comment
void CourceManager::cPtn16(CourceMaker* _c){
    setComment("c16",_c);
    auto kaku = -6;
    _c->dS(50,-70+kaku);
    _c->dS(50,5+kaku);
    _c->dS(50,-70+kaku);
    _c->dS(50,5+kaku);
    _c->dS(50,-70+kaku);
    _c->dS(50,kaku);
}

// カクカク
void CourceManager::cPtn17(CourceMaker* _c){
    setComment("c17",_c);
    auto kaku = -4;
    _c->dS(150,-70+kaku);
    _c->dS(120,5+kaku);
    _c->dS(50,-70+kaku);
    _c->dS(100,kaku);
}

// カクカク
void CourceManager::cPtn18(CourceMaker* _c){
    setComment("c18",_c);
    auto kaku = -5;
    _c->dS(90,-45+kaku);
    _c->dS(150,5+kaku);
    _c->dS(130,-70+kaku);
    _c->dS(50,5+kaku);
    _c->dS(50,-30+kaku);
    _c->dS(50,5+kaku);
}

// カクカク
void CourceManager::cPtn19(CourceMaker* _c){
    setComment("c19",_c);
    auto kaku = -6;
    _c->dS(90,-45+kaku);
    _c->dS(150,5+kaku);
    _c->dS(130,-45+kaku);
    _c->dS(50,5+kaku);
    _c->dS(90,-90+kaku);
    _c->dS(50,kaku);
}

// 凸
void CourceManager::cPtn20(CourceMaker* _c){
    setComment("c20",_c);
    auto kaku = 0;
    for(int i=0;i<3;i++){
        _c->dS(100,kaku);
        _c->dS(0,90+kaku);
        _c->dC(10,-90 + kaku);
    }
    _c->dS(30,kaku);
}

// 凸
void CourceManager::cPtn21(CourceMaker* _c){
    setComment("c21",_c);
    auto kaku = -6;
    for(int i=0;i<3;i++){
        _c->dS(100,kaku);
        _c->dS(0,90+kaku);
        _c->dC(20,-90 + kaku);
    }
    _c->dS(30,kaku);
}

// 凸
void CourceManager::cPtn22(CourceMaker* _c){
    setComment("c22",_c);
    auto kaku = -15;
    for(int i=0;i<1;i++){
        _c->dS(150,kaku);
        _c->dS(0,90+kaku);
        _c->dC(30,-90 + kaku);
    }
    _c->dS(80,kaku);
}

// 凸
void CourceManager::cPtn23(CourceMaker* _c){
    setComment("c23",_c);
    auto kaku = -15;
    for(int i=0;i<1;i++){
        _c->dS(200,kaku);
        _c->dS(0,90+kaku);
        _c->dC(10,-90 + kaku);
        _c->dS(80,kaku);
    }
}

// 凸
void CourceManager::cPtn24(CourceMaker* _c){
    setComment("c24",_c);
    auto kaku = -2;
    for(int i=0;i<1;i++){
        _c->dS(200,kaku);
        _c->dC(30,80 + kaku);
        _c->dC(50,-80 + kaku);
        _c->dC(30, kaku);
        _c->dS(50,kaku);
    }
}

// 凹
void CourceManager::cPtn25(CourceMaker* _c){
    setComment("c25",_c);
    auto kaku = -10;
    for(int i=0;i<3;i++){
        _c->dS(50,kaku);
        _c->dS(0,-90+kaku);
        _c->dC(10,90 + kaku);
        _c->dS(20,kaku);
    }
}

// 凹
void CourceManager::cPtn26(CourceMaker* _c){
    setComment("c26",_c);
    auto kaku = -7;
    for(int i=0;i<3;i++){
        _c->dS(50,kaku);
        _c->dS(0,-90+kaku);
        _c->dC(20,90 + kaku);
        _c->dS(40,kaku);
    }
}

// 凹
void CourceManager::cPtn27(CourceMaker* _c){
    setComment("c27",_c);
    auto kaku = -7;
    for(int i=0;i<2;i++){
        _c->dS(100,kaku);
        _c->dS(0,-90+kaku);
        _c->dC(30,90 + kaku);
        _c->dS(80,kaku);
    }
}

// 凹
void CourceManager::cPtn28(CourceMaker* _c){
    setComment("c28",_c);
    auto kaku = -7;
    for(int i=0;i<1;i++){
        _c->dS(200,kaku);
        _c->dC(50,-70 + kaku);
        _c->dC(50,70 + kaku);
        _c->dC(50, kaku);
        _c->dS(50,kaku);
    }
}

// 凹
void CourceManager::cPtn29(CourceMaker* _c){
    setComment("c29",_c);
    auto kaku = -15;
    for(int i=0;i<1;i++){
        _c->dS(200,kaku);
        _c->dC(30,-80 + kaku);
        _c->dC(50,80 + kaku);
        _c->dC(30, kaku);
        _c->dS(50,kaku);
    }
}

// 段差下り
void CourceManager::cPtn30(CourceMaker* _c){
    setComment("c30",_c);
    auto kaku = _c->_dirkaku;
    _c->dC(30,0);
    _c->dS(80,0);
    for(int i=0;i<20;i++){
        _c->dS(20,-90);
        _c->dS(40,0);
    }
    _c->dS(80,0);
}

// 段差下り
void CourceManager::cPtn31(CourceMaker* _c){
    setComment("c31",_c);
    auto kaku = _c->_dirkaku;
    _c->dC(30,0);
    _c->dS(80,0);
    for(int i=0;i<20;i++){
        _c->dS(40,-90);
        _c->dS(80,0);
    }
    _c->dS(80,0);
}

// 段差下り
void CourceManager::cPtn32(CourceMaker* _c){
    setComment("c32",_c);
    auto kaku = _c->_dirkaku;
    _c->dC(30,0);
    _c->dS(80,0);
    for(int i=0;i<3;i++){
        _c->dS(60,-90);
        _c->dS(100,0);
    }
    _c->dS(80,0);
}

// 段差下り
void CourceManager::cPtn33(CourceMaker* _c){
    setComment("c33",_c);
    auto kaku = _c->_dirkaku;
    _c->dC(30,0);
    _c->dS(80,0);
    for(int i=0;i<2;i++){
        _c->dS(80,-90);
        _c->dS(70,0);
    }
    _c->dS(80,0);
}

// 段差下り
void CourceManager::cPtn34(CourceMaker* _c){
    setComment("c34",_c);
    auto kaku = _c->_dirkaku;
    _c->dS(100,0);
    for(int i=0;i<1;i++){
        _c->dS(100,-90);
        _c->dS(100,0);
        _c->dS(50,90);
    }
    _c->dS(80,0);
}

// 段差上り
void CourceManager::cPtn35(CourceMaker* _c){
    setComment("c35",_c);
    auto kaku = _c->_dirkaku;
    _c->dS(50,0);
    for(int i=0;i<4;i++){
        _c->dS(8,90);
        _c->dS(100,0);
    }
    _c->dS(80,0);
}

// 段差上り
void CourceManager::cPtn36(CourceMaker* _c){
    setComment("c36",_c);
    auto kaku = _c->_dirkaku;
    _c->dS(100,0);
    for(int i=0;i<2;i++){
        _c->dS(20,90);
        _c->dS(150,0);
    }
    _c->dS(80,0);
}

// 段差上り
void CourceManager::cPtn37(CourceMaker* _c){
    setComment("c37",_c);
    auto kaku = _c->_dirkaku;
    _c->dS(50,0);
    for(int i=0;i<1;i++){
        _c->dS(30,90);
        _c->dS(150,0);
    }
    _c->dS(80,0);
}

// 段差上り
void CourceManager::cPtn38(CourceMaker* _c){
    setComment("c38",_c);
    auto kaku = _c->_dirkaku;
    _c->dS(70,-10);
    for(int i=0;i<4;i++){
        _c->dS(20,80);
        _c->dS(70,-10);
    }
    _c->dS(80,0);
}

// 段差上り
void CourceManager::cPtn39(CourceMaker* _c){
    setComment("c39",_c);
    auto kaku = _c->_dirkaku;
    _c->dS(100,0);
    _c->dC(30,60);
    _c->dS(30,-90);
    _c->dS(30,0);
    _c->dS(50,90);
    _c->dS(150,0);
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

// 段差＋ジャンプ穴
void CourceManager::cPtn45(CourceMaker* _c){
    setComment("c45",_c);
    _c->dS(200, -20);
    _c->dS(20, 70);
    _c->dS(100, -20);
    _c->dC(50, 50);
    _c->dS(100,-90);
    _c->dS(50, 0);
    _c->dS(130,90);
    _c->dS(50, 0);
}

// 穴ジャンプ
void CourceManager::cPtn46(CourceMaker* _c){
    setComment("c46",_c);
    auto kaku = _c->_dirkaku;
    _c->dS(100, 0);
    _c->dS(100, -90);
    _c->dS(70, 0);
    _c->dS(100, 90);
    _c->dS(100, 0);
}

// 穴ジャンプ
void CourceManager::cPtn47(CourceMaker* _c){
    setComment("c47",_c);
    auto kaku = _c->_dirkaku;
    _c->dC(200, -50);
    _c->dS(100, -90);
    _c->dS(60, 0);
    _c->dS(120, 90);
    _c->dS(50, 0);
}

// 2段ジャンプ
void CourceManager::cPtn48(CourceMaker* _c){
    setComment("c48",_c);
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

// 凸小凹大
void CourceManager::cPtn51(CourceMaker* _c){
    setComment("c51",_c);
    auto kaku = _c->_dirkaku;
    _c->dC(30,0);
    _c->dS(100,0);
    _c->dS(0,90);
    _c->dC(20,-90);
    _c->dC(60,80);
    _c->dS(50,0);
}

// 凸小凹大
void CourceManager::cPtn52(CourceMaker* _c){
    setComment("c52",_c);
    auto kaku = _c->_dirkaku;
    _c->dC(30,kaku);
    _c->dS(100,kaku);
    _c->dS(0,90+kaku);
    _c->dC(20,-90+kaku);
    _c->dC(60,80+kaku);
    _c->dS(50,kaku);
}

// モアイ
void CourceManager::cPtn53(CourceMaker* _c){
    setComment("c53",_c);
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

// 車
void CourceManager::cPtn54(CourceMaker* _c){
    setComment("c54",_c);
    auto kaku = _c->_dirkaku;
    kaku = -15;
    _c->dS(100,kaku);
    _c->dS(0,80+kaku);
    _c->dS(20,80+kaku);
    _c->dC(40,5+kaku);
    _c->dS(20,5+kaku);
    _c->dS(20,70+kaku);
    _c->dC(100,0+kaku);
    _c->dS(50,0+kaku);
    _c->dC(200,-80+kaku);
    _c->dS(50,0+kaku);
}

// 3段段差穴下り
void CourceManager::cPtn55(CourceMaker* _c){
    setComment("c55",_c);
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
void CourceManager::cPtn56(CourceMaker* _c){
    setComment("c56",_c);
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

// なだらかな坂と石ころ
void CourceManager::cPtn57(CourceMaker* _c){
    setComment("c57",_c);
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

// なだらかな坂と石柱
void CourceManager::cPtn58(CourceMaker* _c){
    setComment("c58",_c);
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

// 連続した石ころ
void CourceManager::cPtn59(CourceMaker* _c){
    setComment("c59",_c);
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
    _c->dS(0,90);
    _c->dC(10,-90);
    _c->dS(0,20);
    _c->dC(80,0);
    _c->dS(50,0);
}

// 連続した石柱
void CourceManager::cPtn60(CourceMaker* _c){
    setComment("c60",_c);
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

// 波波プッシュ10連
void CourceManager::cPtn61(CourceMaker* _c){
    setComment("c61",_c);
    auto kaku = _c->_dirkaku;
    _c->dC(30,0);
    for(int i=0;i<10;i++){
        _c->dC(30,-45);
        _c->dC(30,45);
    }
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
