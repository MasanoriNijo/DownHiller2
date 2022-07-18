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
    std::string head = "クリア条件\n";
    switch (getStagePrm()->getStageNumber()) {
        case 1:
            getStagePrm()->setCommnent(
                                       "ここからは、\n"
                                       "実際に操作して、\n"
                                       "ゴールを目指そう!\n"
                                       );
            break;
        case 2:
            getStagePrm()->setCommnent(head+
                                       "実際に操作してみて、\n"
                                       "ゴールを目指そう！"
                                       );
            getStagePrm()->setTymeLimit(10);
            break;
        case 3:
            getStagePrm()->setCommnent(head+
                                       "コブを乗り越えて、\n"
                                       "10秒以内に、\n"
                                       "ゴールすること。"
                                       );
            getStagePrm()->setTymeLimit(10);
            break;
        case 4:
            getStagePrm()->setCommnent(head+
                                       "巨大な穴\n"
                                       "を攻略し\n"
                                       "ゴールを目指そう！"
                                       );
            break;
        case 5:
            getStagePrm()->setCommnent(head+
                                       "スーパージャンプ\n"
                                       "をキメよう！\n"
                                       );
            getStagePrm()->setTymeLimit(10);
            break;
        case 6:
            getStagePrm()->setCommnent(head+
                                       "曲線ランダム、\n"
                                       "10秒以内に、\n"
                                       "ゴールすること。"
                                       );
            getStagePrm()->setTymeLimit(10);
            break;
        case 7:
            getStagePrm()->setCommnent(head+
                                       "直線ランダム、\n"
                                       "10秒以内に、\n"
                                       "ゴールすること。"
                                       );
            getStagePrm()->setTymeLimit(10);
            break;
        case 8:
            getStagePrm()->setCommnent(head+
                                       "穴ぼことなみなみ、\n"
                                       "10秒以内に、\n"
                                       "ゴールすること。"
                                       );
            getStagePrm()->setTymeLimit(10);
            break;
        case 9:
            getStagePrm()->setCommnent(head+
                                       "ピラミッド、\n"
                                       "10秒以内に、\n"
                                       "ゴールすること。"
                                       );
            getStagePrm()->setTymeLimit(10);
            break;
        case 10:
            getStagePrm()->setCommnent(head+
                                       "巨大ループ、\n"
                                       "10秒以内に、\n"
                                       "ゴールすること。"
                                       );
            getStagePrm()->setTymeLimit(10);
            break;
        case 11:
            getStagePrm()->setCommnent(head+
                                       "壁と落とし穴、\n"
                                       "10秒以内に、\n"
                                       "ゴールすること。"
                                       );
            getStagePrm()->setTymeLimit(10);
            break;
        case 12:
            getStagePrm()->setCommnent(head+
                                       "富士山、\n"
                                       "小さい石ころ、\n"
                                       "ゴールすること。"
                                       );
            getStagePrm()->setTymeLimit(10);
            break;
        case 13:
            getStagePrm()->setCommnent(head+
                                       "巨大ループ、\n"
                                       "10秒以内に、\n"
                                       "ゴールすること。"
                                       );
            getStagePrm()->setTymeLimit(10);
            break;
        case 14:
            getStagePrm()->setCommnent(head+
                                       "巨大ループ、\n"
                                       "10秒以内に、\n"
                                       "ゴールすること。"
                                       );
            getStagePrm()->setTymeLimit(10);
            break;
        case 15:
            getStagePrm()->setCommnent(head+
                                       "巨大ループ、\n"
                                       "10秒以内に、\n"
                                       "ゴールすること。"
                                       );
            getStagePrm()->setTymeLimit(10);
            break;
        case 16:
            getStagePrm()->setCommnent(head+
                                       "巨大ループ、\n"
                                       "10秒以内に、\n"
                                       "ゴールすること。"
                                       );
            getStagePrm()->setTymeLimit(10);
            break;
        case 17:
            getStagePrm()->setCommnent(head+
                                       "巨大ループ、\n"
                                       "10秒以内に、\n"
                                       "ゴールすること。"
                                       );
            getStagePrm()->setTymeLimit(10);
            break;
        case 18:
            getStagePrm()->setCommnent(head+
                                       "巨大ループ、\n"
                                       "10秒以内に、\n"
                                       "ゴールすること。"
                                       );
            getStagePrm()->setTymeLimit(10);
            break;
        case 19:
            getStagePrm()->setCommnent(head+
                                       "巨大ループ、\n"
                                       "10秒以内に、\n"
                                       "ゴールすること。"
                                       );
            getStagePrm()->setTymeLimit(10);
            break;
        case 20:
            getStagePrm()->setCommnent(head+
                                       "巨大ループ、\n"
                                       "10秒以内に、\n"
                                       "ゴールすること。"
                                       );
            getStagePrm()->setTymeLimit(10);
            break;
        default:
            break;
    }
}

void CourceManager::setStartAndTargetFromCource(CourceMaker* _c){
    setStartPt(_c->getStartPt());
    setStartDir(_c->getStartDir());
    setTergetPt(_c->getTergetPt());
    setTargetDir(_c->getTargetDir());
}

void CourceManager::checkAndMadeCource(Vec2 chPt){
    if(chPt.x > (getStartPt().x + 80) || !courceIndex){
        _dirkaku = courceIndex%2 ? getCourceMakerA()->_dirkaku : getCourceMakerB()->_dirkaku;
        switch (selStg) {
            case 0:
                madeCourcePtnForTitle(courceIndex%2 ? getCourceMakerB() : getCourceMakerA(),courceIndex);
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
    selStg = 0;
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
    Label* _comment = Label::createWithTTF("← " + st, "irohamaru.ttf", 8);
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

void CourceManager::madeCourcePtn1(CourceMaker* _c,int ind){
    auto flg = Flg::create();
    int i = 0;
    _c->drawStart(getTergetPt(),getTargetDir());
    switch (ind) {
        case 0:
            _c->dS(500,0);
            _c->dS(100,-1);
            setStart(_c);
            _c->dS(2800,-1);
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

void CourceManager::madeCourcePtn2(CourceMaker* _c,int ind){
    auto flg = Flg::create();
    int i = 0;
    _c->drawStart(getTergetPt(),getTargetDir());
    switch (ind) {
        case 0:
            _c->dS(600,0);
            setStart(_c);
            _c->dS(10,-90);
            _c->dC(200, -30);
            _c->dS(200, -30);
            break;
        case 1:
            for(i=0;i<4;i++){
                _c->dC(120,30);
                _c->dS(50, 30);
                _c->dC(100,-30);
                _c->dS(150, -30);
            }
            break;
        case 2:
            for(i=0;i<4;i++){
                _c->dS(Vec2(100,-5));
                _c->dC(50,45);
            }
            break;
        case 3:
            _c->dS(Vec2(90,0));
             flg->setGlobalZOrder(OBJ_LAYER_LV1-1);
             flg->setPosition(_c->getTergetPt());
             flg->setRotation(_c->getCalc()->nomlKaku(Vec2::ZERO,_c->getTargetDir()));
             _c->addChild(flg);
            _c->dS(Vec2(500,0));
            _c->dS(Vec2(0,100));
            break;
        default:
            return;
            break;
    }
    _c->madePhysiceBody();
}

void CourceManager::madeCourcePtn3(CourceMaker* _c,int ind){
    auto flg = Flg::create();
    int i = 0;
    _c->drawStart(getTergetPt(),getTargetDir());
    switch (ind) {
        case 0:
            _c->dS(600,0);
            setStart(_c);
            _c->dC(300,-10);
            break;
        case 1:
            for(i=0;i<4;i++){
                _c->dC(Vec2(30,0), -100);
                _c->dS(100,-10);
            }
            break;
        case 2:
            for(i=0;i<6;i++){
                _c->dC(100,-50);
                _c->dC(60,30);
            }
            break;
        case 3:
            _c->dS(Vec2(90,0));
             flg->setGlobalZOrder(OBJ_LAYER_LV1-1);
             flg->setPosition(_c->getTergetPt());
             flg->setRotation(_c->getCalc()->nomlKaku(Vec2::ZERO,_c->getTargetDir()));
             _c->addChild(flg);
            _c->dS(Vec2(500,0));
            _c->dS(Vec2(0,100));
            break;
        default:
            return;
            break;
    }
    _c->madePhysiceBody();
}

void CourceManager::madeCourcePtn4(CourceMaker* _c,int ind){
    auto flg = Flg::create();
    int i = 0;
    _c->drawStart(getTergetPt(),getTargetDir());
    switch (ind) {
        case 0:
            _c->dS(600,0);
            setStart(_c);
            _c->dS(300,-5);
            break;
        case 1:
            for(i=0;i<4;i++){
                _c->dC(50, -70);
                _c->dS(100, -70);
                _c->dC(50, 70);
                _c->dS(80, 70);
                _c->dC(50, 0);
                _c->dS(100, -5);
                
            }
            break;
        case 2:
            for(i=0;i<4;i++){
                _c->dS(Vec2(0,-50));
                _c->dS(Vec2(60,0));
            }
            break;
        case 3:
            _c->dS(Vec2(90,0));
             flg->setGlobalZOrder(OBJ_LAYER_LV1-1);
             flg->setPosition(_c->getTergetPt());
             flg->setRotation(_c->getCalc()->nomlKaku(Vec2::ZERO,_c->getTargetDir()));
             _c->addChild(flg);
            _c->dS(Vec2(500,0));
            _c->dS(Vec2(0,100));
            break;
        default:
            return;
            break;
    }
    _c->madePhysiceBody();
}

void CourceManager::madeCourcePtn5(CourceMaker* _c,int ind){
    auto flg = Flg::create();
    int i = 0;
    _c->drawStart(getTergetPt(),getTargetDir());
    switch (ind) {
        case 0:
            _c->dS(600,0);
            setStart(_c);
            _c->dS(Vec2(0,-100));
            _c->dS(Vec2(300,-3));
            break;
        case 1:
                _c->dC(50, -70);
                _c->dS(600, -70);
                _c->dC(80, 70);
                _c->dS(50, 70);
                _c->dC(20, 0);
                _c->dS(100, 0);
            break;
        case 2:
                _c->dS(Vec2(0,150));
                _c->dS(Vec2(380,0));
            break;
        case 3:
            _c->dS(Vec2(90,0));
             flg->setGlobalZOrder(OBJ_LAYER_LV1-1);
             flg->setPosition(_c->getTergetPt());
             flg->setRotation(_c->getCalc()->nomlKaku(Vec2::ZERO,_c->getTargetDir()));
             _c->addChild(flg);
            _c->dS(Vec2(200,0));
            _c->dS(Vec2(0,100));
            break;
        default:
            return;
            break;
    }
    _c->madePhysiceBody();
}

void CourceManager::madeCourcePtn6(CourceMaker* _c,int ind){
    auto flg = Flg::create();
    int i = 0;
    _c->drawStart(getTergetPt(),getTargetDir());
    switch (ind) {
        case 0:
            _c->dS(600,0);
            setStart(_c);
            _c->dC(500, -10);
            _c->dS(200,-10);
            break;
        case 1:
            for(i=0;i<6;i++){
                int kaku_ = i%2 ? random<int>(-75, -30):random<int>(0, 30);
                int length_ = random<int>(50,200);
                float r_ = random<float>(10,100);
                _c->dC(r_, kaku_);
                _c->dS(length_,kaku_);
            }
            break;
        case 2:
            for(i=0;i<6;i++){
                int kaku_ = i%2 ? random<int>(-75, -30):random<int>(0, 30);
                int length_ = random<int>(50,200);
                float r_ = random<float>(50,150);
                _c->dC(r_, kaku_);
                _c->dS(length_,kaku_);
            }
            break;
        case 3:
            _c->dS(Vec2(300,0));
             flg->setGlobalZOrder(OBJ_LAYER_LV1-1);
             flg->setPosition(_c->getTergetPt());
             flg->setRotation(_c->getCalc()->nomlKaku(Vec2::ZERO,_c->getTargetDir()));
             _c->addChild(flg);
            _c->dS(Vec2(200,0));
            _c->dS(Vec2(0,100));
            break;
        default:
            return;
            break;
    }
    _c->madePhysiceBody();
}

void CourceManager::madeCourcePtn7(CourceMaker* _c,int ind){
    auto flg = Flg::create();
    int i = 0;
    _c->drawStart(getTergetPt(),getTargetDir());
    switch (ind) {
        case 0:
            _c->dS(600,0);
            setStart(_c);
            _c->dC(500, -10);
            _c->dS(200,-10);
            break;
        case 1:
            for(i=0;i<10;i++){
                int kaku_ = i%2 ? random<int>(-75, -30):random<int>(-20, 20);
                int length_ = random<int>(50,200);
                float r_ = random<float>(10,100);
//                _c->drawBySmoothCurve(r_, kaku_);
                _c->dS(length_,kaku_);
            }
            break;
        case 2:
            for(i=0;i<10;i++){
                int kaku_ = i%2 ? random<int>(-75, -30):random<int>(-20, 20);
                int length_ = random<int>(50,200);
                float r_ = random<float>(50,150);
//                _c->drawBySmoothCurve(r_, kaku_);
                _c->dS(length_,kaku_);
            }
            break;
        case 3:
            _c->dS(Vec2(300,0));
             flg->setGlobalZOrder(OBJ_LAYER_LV1-1);
             flg->setPosition(_c->getTergetPt());
             flg->setRotation(_c->getCalc()->nomlKaku(Vec2::ZERO,_c->getTargetDir()));
             _c->addChild(flg);
            _c->dS(Vec2(200,0));
            _c->dS(Vec2(0,100));
            break;
        default:
            return;
            break;
    }
    _c->madePhysiceBody();
}

void CourceManager::madeCourcePtn8(CourceMaker* _c,int ind){
    auto flg = Flg::create();
    int i = 0;
    _c->drawStart(getTergetPt(),getTargetDir());
    switch (ind) {
        case 0:
            _c->dS(600,0);
            setStart(_c);
            _c->dC(500, -10);
            _c->dS(200,-10);
            break;
        case 1:
            _c->_dirkaku = -10;
            for(i=0;i<10;i++){
                
                _c->dC(30, -60);
                _c->dC(30, 50);
            }

            break;
        case 2:
            for(i=0;i<4;i++){
                _c->dC(Vec2(100,-10), 90);
                _c->dS(100,-10);
            }
            break;
        case 3:
            _c->dS(Vec2(300,0));
             flg->setGlobalZOrder(OBJ_LAYER_LV1-1);
             flg->setPosition(_c->getTergetPt());
             flg->setRotation(_c->getCalc()->nomlKaku(Vec2::ZERO,_c->getTargetDir()));
             _c->addChild(flg);
            _c->dS(Vec2(200,0));
            _c->dS(Vec2(0,100));
            break;
        default:
            return;
            break;
    }
    _c->madePhysiceBody();
}

void CourceManager::madeCourcePtn9(CourceMaker* _c,int ind){
    auto flg = Flg::create();
    int i = 0;
    _c->drawStart(getTergetPt(),getTargetDir());
    switch (ind) {
        case 0:
            _c->dS(600,0);
            setStart(_c);
            _c->dC(500, -10);
            _c->dS(200,-10);
            break;
        case 1:
            for(i=0;i<10;i++){
                _c->dS(Vec2(0,-20));
                _c->dS(Vec2(80,0));
            }
            _c->dS(Vec2(100,0));
            break;
        case 2:
            for(i=0;i<10;i++){
                _c->dS(Vec2(0,20));
                _c->dS(Vec2(80,0));
            }
            break;
        case 3:
            _c->dS(Vec2(300,0));
             flg->setGlobalZOrder(OBJ_LAYER_LV1-1);
             flg->setPosition(_c->getTergetPt());
             flg->setRotation(_c->getCalc()->nomlKaku(Vec2::ZERO,_c->getTargetDir()));
             _c->addChild(flg);
            _c->dS(Vec2(200,0));
            _c->dS(Vec2(0,100));
            break;
        default:
            return;
            break;
    }
    _c->madePhysiceBody();
}

void CourceManager::madeCourcePtn10(CourceMaker* _c,int ind){
    auto flg = Flg::create();
    int i = 0;
    _c->drawStart(getTergetPt(),getTargetDir());
    switch (ind) {
        case 0:
            _c->dS(600,0);
            setStart(_c);
            _c->dC(300, -45);
            _c->dS(1000, -45);
            break;
        case 1:
            _c->dC(240,300);
            _c->dS(Vec2(0,-100));
            _c->dS(Vec2(60,0));
            _c->dS(Vec2(0,50));
            _c->dS(Vec2(170,0));
            flg->setGlobalZOrder(OBJ_LAYER_LV1-1);
            flg->setPosition(_c->getTergetPt());
            flg->setRotation(_c->getCalc()->nomlKaku(Vec2::ZERO,_c->getTargetDir()));
            _c->addChild(flg);
            _c->dS(Vec2(50,0));
            _c->dS(Vec2(0,50));
            break;
        case 2:
            break;
        case 3:

        default:
            return;
            break;
    }
    _c->madePhysiceBody();
}

void CourceManager::madeCourcePtn11(CourceMaker* _c,int ind){
    auto flg = Flg::create();
    int i = 0;
    _c->drawStart(getTergetPt(),getTargetDir());
    switch (ind) {
        case 0:
            _c->dS(600,0);
            setStart(_c);
            _c->dS(Vec2(300,-3));
            break;
        case 1:
            for(i=0;i<3;i++){
                _c->dS(200, -20);
                _c->dS(20, 70);
                _c->dS(100, -20);
                _c->dC(50, 50);
                _c->dS(Vec2(0, -100));
                _c->dS(Vec2(50, 0));
                _c->dS(Vec2(0, 130));
            }
            break;
        case 2:
            _c->dS(20, 0);
            _c->dC(100,-100);
            _c->dS(100,-100);
            break;
        case 3:
            _c->dS(Vec2(300,0));
             flg->setGlobalZOrder(OBJ_LAYER_LV1-1);
             flg->setPosition(_c->getTergetPt());
             flg->setRotation(_c->getCalc()->nomlKaku(Vec2::ZERO,_c->getTargetDir()));
             _c->addChild(flg);
            _c->dS(Vec2(200,0));
            _c->dS(Vec2(0,100));
            break;
        default:
            return;
            break;
    }
    _c->madePhysiceBody();
}

void CourceManager::madeCourcePtn12(CourceMaker* _c,int ind){
    auto flg = Flg::create();
    int i = 0;
    _c->drawStart(getTergetPt(),getTargetDir());
    switch (ind) {
        case 0:
            _c->dS(600,0);
            setStart(_c);
            _c->dS(100,0);
            break;
        case 1:
            cPtn00(_c);
            cPtn01(_c);
            cPtn02(_c);
            cPtn03(_c);
            cPtn04(_c);
            break;
        case 2:
            cPtn05(_c);
            cPtn06(_c);
            cPtn07(_c);
            cPtn08(_c);
            cPtn09(_c);
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
    auto flg = Flg::create();
    int i = 0;
    _c->drawStart(getTergetPt(),getTargetDir());
    switch (ind) {
        case 0:
            _c->dS(600,0);
            setStart(_c);
            _c->dS(100,-5);
            break;
        case 1:
            cPtn10(_c);
            cPtn11(_c);
            cPtn12(_c);
            cPtn13(_c);
            cPtn14(_c);
            break;
        case 2:
            cPtn15(_c);
            cPtn16(_c);
            cPtn17(_c);
            cPtn18(_c);
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

void CourceManager::madeCourcePtn14(CourceMaker* _c,int ind){
    auto flg = Flg::create();
    int i = 0;
    _c->drawStart(getTergetPt(),getTargetDir());
    switch (ind) {
        case 0:
            _c->dS(600,0);
            setStart(_c);
            _c->dS(100,-15);
            break;
        case 1:
            cPtn20(_c);
            cPtn21(_c);
            cPtn22(_c);
            cPtn23(_c);
            cPtn24(_c);
            break;
        case 2:
            cPtn25(_c);
            cPtn26(_c);
            cPtn27(_c);
            cPtn28(_c);
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


void CourceManager::madeCourcePtn15(CourceMaker* _c,int ind){
    auto flg = Flg::create();
    int i = 0;
    _c->drawStart(getTergetPt(),getTargetDir());
    switch (ind) {
        case 0:
            _c->dS(600,0);
            setStart(_c);
            _c->dS(100,-15);
            break;
        case 1:
            cPtn39(_c);
            cPtn39(_c);
            cPtn32(_c);
            cPtn33(_c);
            cPtn34(_c);
            break;
        case 2:
            cPtn35(_c);
            cPtn36(_c);
            cPtn37(_c);
            cPtn38(_c);
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


void CourceManager::madeCourcePtn16(CourceMaker* _c,int ind){
    auto flg = Flg::create();
    int i = 0;
    _c->drawStart(getTergetPt(),getTargetDir());
    switch (ind) {
        case 0:
            _c->dS(600,0);
            setStart(_c);
            _c->dS(100,-15);
            break;
        case 1:
            cPtn47(_c);
            cPtn47(_c);
            cPtn42(_c);
            cPtn43(_c);
            cPtn44(_c);
            break;
        case 2:
            cPtn45(_c);
            cPtn46(_c);
            cPtn47(_c);
            cPtn48(_c);
            cPtn49(_c);
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
    auto flg = Flg::create();
    int i = 0;
    _c->drawStart(getTergetPt(),getTargetDir());
    switch (ind) {
        case 0:
            _c->dS(600,0);
            setStart(_c);
            _c->dS(Vec2(300,-3));
            break;
        case 1:
            _c->dC(50, -45);
            _c->dS(1000, -45);
            _c->dC(240,89);
            _c->dS(100, 105);


            break;
        case 2:
            _c->dS(100, 105);
            _c->dS(100, 130);
//            _c->drawByStraight(60, 145);
            _c->dS(-130, 0);
            _c->dS(Vec2(-150,0));
            _c->dS(Vec2(0,-180));
            _c->dS(Vec2(20,0));
            flg->setGlobalZOrder(OBJ_LAYER_LV1-1);
            flg->setPosition(_c->getTergetPt());
            flg->setRotation(_c->getCalc()->nomlKaku(Vec2::ZERO,_c->getTargetDir()));
            _c->addChild(flg);
            _c->dS(Vec2(150,0));
            _c->dS(Vec2(0,50));
            break;
        case 3:

        default:
            return;
            break;
    }
    _c->madePhysiceBody();
}

void CourceManager::madeCourcePtn18(CourceMaker* _c,int ind){
    auto flg = Flg::create();
    int i = 0;
    _c->drawStart(getTergetPt(),getTargetDir());
    switch (ind) {
        case 0:
            _c->dS(600,0);
            setStart(_c);
            _c->dS(Vec2(300,-3));
            break;
        case 1:
            _c->dC(50, -45);
            _c->dS(1000, -45);
            _c->dC(240,89);
            _c->dS(100, 105);


            break;
        case 2:
            _c->dS(100, 105);
            _c->dS(100, 130);
//            _c->drawByStraight(60, 145);
            _c->dS(-130, 0);
            _c->dS(Vec2(-150,0));
            _c->dS(Vec2(0,-180));
            _c->dS(Vec2(20,0));
            flg->setGlobalZOrder(OBJ_LAYER_LV1-1);
            flg->setPosition(_c->getTergetPt());
            flg->setRotation(_c->getCalc()->nomlKaku(Vec2::ZERO,_c->getTargetDir()));
            _c->addChild(flg);
            _c->dS(Vec2(150,0));
            _c->dS(Vec2(0,50));
            break;
        case 3:

        default:
            return;
            break;
    }
    _c->madePhysiceBody();
}

void CourceManager::madeCourcePtn19(CourceMaker* _c,int ind){
    auto flg = Flg::create();
    int i = 0;
    _c->drawStart(getTergetPt(),getTargetDir());
    switch (ind) {
        case 0:
            _c->dS(600,0);
            setStart(_c);
            _c->dS(Vec2(300,-3));
            break;
        case 1:
            _c->dC(50, -45);
            _c->dS(1000, -45);
            _c->dC(240,89);
            _c->dS(100, 105);


            break;
        case 2:
            _c->dS(100, 105);
            _c->dS(100, 130);
//            _c->drawByStraight(60, 145);
            _c->dS(-130, 0);
            _c->dS(Vec2(-150,0));
            _c->dS(Vec2(0,-180));
            _c->dS(Vec2(20,0));
            flg->setGlobalZOrder(OBJ_LAYER_LV1-1);
            flg->setPosition(_c->getTergetPt());
            flg->setRotation(_c->getCalc()->nomlKaku(Vec2::ZERO,_c->getTargetDir()));
            _c->addChild(flg);
            _c->dS(Vec2(150,0));
            _c->dS(Vec2(0,50));
            break;
        case 3:

        default:
            return;
            break;
    }
    _c->madePhysiceBody();
}

void CourceManager::madeCourcePtn20(CourceMaker* _c,int ind){
    auto flg = Flg::create();
    int i = 0;
    _c->drawStart(getTergetPt(),getTargetDir());
    switch (ind) {
        case 0:
            _c->dS(600,0);
            setStart(_c);
            _c->dS(Vec2(300,-3));
            break;
        case 1:
            _c->dC(50, -45);
            _c->dS(1000, -45);
            _c->dC(240,89);
            _c->dS(100, 105);


            break;
        case 2:
            _c->dS(100, 105);
            _c->dS(100, 130);
//            _c->drawByStraight(60, 145);
            _c->dS(-130, 0);
            _c->dS(Vec2(-150,0));
            _c->dS(Vec2(0,-180));
            _c->dS(Vec2(20,0));
            flg->setGlobalZOrder(OBJ_LAYER_LV1-1);
            flg->setPosition(_c->getTergetPt());
            flg->setRotation(_c->getCalc()->nomlKaku(Vec2::ZERO,_c->getTargetDir()));
            _c->addChild(flg);
            _c->dS(Vec2(150,0));
            _c->dS(Vec2(0,50));
            break;
        case 3:

        default:
            return;
            break;
    }
    _c->madePhysiceBody();
}

void CourceManager::checkAndMadeCourceForDebug(Vec2 chPt){
    if(chPt.x > (getStartPt().x + 80) || !courceIndex){
        _dirkaku = courceIndex%2 ? getCourceMakerA()->_dirkaku : getCourceMakerB()->_dirkaku;
        switch (selStg) {
            case 0:
                madeCourcePtnForTitle(courceIndex%2 ? getCourceMakerB() : getCourceMakerA(),courceIndex);
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


// 滑らかな波波
void CourceManager::cPtn00(CourceMaker* _c){
    setComment("cPtn00",_c);
    auto kaku = _c->_dirkaku;
    for(int i=0;i<4;i++){
        _c->dC(80,-5+kaku);
        _c->dC(80,5 + kaku);
    }
    _c->dC(80,kaku);
}

// 滑らかな波波
void CourceManager::cPtn01(CourceMaker* _c){
    setComment("cPtn01",_c);
    auto kaku = _c->_dirkaku;
    for(int i=0;i<4;i++){
        _c->dC(80,-25+kaku);
        _c->dC(80,20 + kaku);
    }
    _c->dC(80,kaku);
}

// 滑らかな波波
void CourceManager::cPtn02(CourceMaker* _c){
    setComment("cPtn02",_c);
    auto kaku = _c->_dirkaku;
    for(int i=0;i<4;i++){
        _c->dC(80,-40+kaku);
        _c->dC(80,20+kaku);
    }
    _c->dC(80,kaku);
}

// 滑らかな波波
void CourceManager::cPtn03(CourceMaker* _c){
    setComment("cPtn03",_c);
    auto kaku = _c->_dirkaku;
    for(int i=0;i<4;i++){
        _c->dC(80,-50+kaku);
        _c->dC(80,45+kaku);
    }
    _c->dC(80,kaku);
}

// 滑らかな波波
void CourceManager::cPtn04(CourceMaker* _c){
    setComment("cPtn04",_c);
    auto kaku = _c->_dirkaku;
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
    setComment("cPtn05",_c);
    auto kaku = _c->_dirkaku;
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
    auto kaku = _c->_dirkaku;
    _c->dC(50,-70+kaku);
    _c->dC(50,5+kaku);
    _c->dC(50,-70+kaku);
    _c->dC(50,5+kaku);
    _c->dC(50,-70+kaku);
    _c->dC(50,kaku);
}

// 滑らかな波波
void CourceManager::cPtn07(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(300,-70+kaku);
    _c->dC(80,5+kaku);
    _c->dC(50,-70+kaku);
    _c->dC(100,kaku);
}

// comment
void CourceManager::cPtn08(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(90,-45+kaku);
    _c->dC(150,5+kaku);
    _c->dC(130,-70+kaku);
    _c->dC(50,5+kaku);
    _c->dC(50,-30+kaku);
    _c->dC(50,kaku);
}

// 滑らかな波波
void CourceManager::cPtn09(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(90,-45+kaku);
    _c->dC(150,5+kaku);
    _c->dC(130,-45+kaku);
    _c->dC(50,5+kaku);
    _c->dC(90,-90+kaku);
    _c->dC(50,kaku);
}

// カクカク
void CourceManager::cPtn10(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dS(30,-10+kaku);
    _c->dS(30,kaku);
    _c->dS(30,-10+kaku);
    _c->dS(30,kaku);
    _c->dS(30,-10+kaku);
    _c->dS(30,kaku);
}

// カクカク
void CourceManager::cPtn11(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dS(80,-30+kaku);
    _c->dS(30,kaku);
    _c->dS(80,-30+kaku);
    _c->dS(30,kaku);
    _c->dS(80,-30+kaku);
    _c->dS(30,kaku);
}

// カクカク
void CourceManager::cPtn12(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dS(100,-45+kaku);
    _c->dS(50,kaku);
    _c->dS(100,-45+kaku);
    _c->dS(50,kaku);
    _c->dS(100,-45+kaku);
    _c->dS(50,kaku);
}

// カクカク
void CourceManager::cPtn13(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dS(100,-70+kaku);
    _c->dS(100,kaku);
    _c->dS(80,5+kaku);
    _c->dS(70,kaku);
}

// カクカク
void CourceManager::cPtn14(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
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
    auto kaku = _c->_dirkaku;
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
    auto kaku = _c->_dirkaku;
    _c->dS(50,-70+kaku);
    _c->dS(50,5+kaku);
    _c->dS(50,-70+kaku);
    _c->dS(50,5+kaku);
    _c->dS(50,-70+kaku);
    _c->dS(50,5+kaku);
}

// カクカク
void CourceManager::cPtn17(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dS(300,-70+kaku);
    _c->dS(80,5+kaku);
    _c->dS(50,-70+kaku);
    _c->dS(100,5+kaku);
}

// カクカク
void CourceManager::cPtn18(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dS(90,-45+kaku);
    _c->dS(150,5+kaku);
    _c->dS(130,-70+kaku);
    _c->dS(50,5+kaku);
    _c->dS(50,-30+kaku);
    _c->dS(50,5+kaku);
}

// カクカク
void CourceManager::cPtn19(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dS(90,-45+kaku);
    _c->dS(150,5+kaku);
    _c->dS(130,-45+kaku);
    _c->dS(50,5+kaku);
    _c->dS(90,-90+kaku);
    _c->dS(50,kaku);
}

// 凸
void CourceManager::cPtn20(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    for(int i=0;i<3;i++){
        _c->dS(50,kaku);
        _c->dS(0,90+kaku);
        _c->dC(10,-90 + kaku);
        _c->dS(20,kaku);
    }
}

// 凸
void CourceManager::cPtn21(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    for(int i=0;i<3;i++){
        _c->dS(50,kaku);
        _c->dS(0,90+kaku);
        _c->dC(20,-90 + kaku);
        _c->dS(40,kaku);
    }
}

// 凸
void CourceManager::cPtn22(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    for(int i=0;i<2;i++){
        _c->dS(100,kaku);
        _c->dS(0,90+kaku);
        _c->dC(30,-90 + kaku);
        _c->dS(80,kaku);
    }
}

// 凸
void CourceManager::cPtn23(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    for(int i=0;i<1;i++){
        _c->dS(200,kaku);
        _c->dS(0,90+kaku);
        _c->dC(10,-90 + kaku);
        _c->dS(80,kaku);
    }
}

// 凸
void CourceManager::cPtn24(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
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
    auto kaku = _c->_dirkaku;
    for(int i=0;i<3;i++){
        _c->dS(50,kaku);
        _c->dS(0,-90+kaku);
        _c->dC(10,90 + kaku);
        _c->dS(20,kaku);
    }
}

// 凹
void CourceManager::cPtn26(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    for(int i=0;i<3;i++){
        _c->dS(50,kaku);
        _c->dS(0,-90+kaku);
        _c->dC(20,90 + kaku);
        _c->dS(40,kaku);
    }
}

// 凹
void CourceManager::cPtn27(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    for(int i=0;i<2;i++){
        _c->dS(100,kaku);
        _c->dS(0,-90+kaku);
        _c->dC(30,90 + kaku);
        _c->dS(80,kaku);
    }
}

// 凹
void CourceManager::cPtn28(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
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
    auto kaku = _c->_dirkaku;
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
    auto kaku = _c->_dirkaku;
    _c->dC(30,0);
    _c->dS(80,0);
    for(int i=0;i<5;i++){
        _c->dS(20,-90);
        _c->dS(40,0);
    }
    _c->dS(80,0);
}

// 段差下り
void CourceManager::cPtn31(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,0);
    _c->dS(80,0);
    for(int i=0;i<5;i++){
        _c->dS(40,-90);
        _c->dS(40,0);
    }
    _c->dS(80,0);
}

// 段差下り
void CourceManager::cPtn32(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,0);
    _c->dS(80,0);
    for(int i=0;i<3;i++){
        _c->dS(60,-90);
        _c->dS(50,0);
    }
    _c->dS(80,0);
}

// 段差下り
void CourceManager::cPtn33(CourceMaker* _c){
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
    auto kaku = _c->_dirkaku;
    _c->dS(50,-5);
    for(int i=0;i<4;i++){
        _c->dS(30,90);
        _c->dS(50,-5);
    }
    _c->dS(80,0);
}

// 段差上り
void CourceManager::cPtn39(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dS(100,0);
    _c->dC(30,70);
    _c->dS(30,-90);
    _c->dS(30,0);
    _c->dS(60,90);
    _c->dS(150,0);
}

// 富士山
void CourceManager::cPtn40(CourceMaker* _c){
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
    auto kaku = _c->_dirkaku;
    _c->dS(10,kaku);
    _c->dC(100,75);
    _c->dS(100,0);
    _c->dC(100,0);
    _c->dS(100,0);
}

// 富士山
void CourceManager::cPtn43(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dS(10,kaku);
    _c->dC(40,85);
    _c->dS(50,0);
    _c->dC(40,0);
    _c->dS(100,0);
}

// 角富士山
void CourceManager::cPtn44(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dS(80,kaku);
    _c->dS(80,kaku + 45);
    _c->dS(80,-90);
    _c->dS(50,0);
    _c->dS(80,90);
    _c->dC(80,kaku);
}

// 段差＋ジャンプ穴
void CourceManager::cPtn45(CourceMaker* _c){
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
    auto kaku = _c->_dirkaku;
    _c->dS(100, 0);
    _c->dS(100, -90);
    _c->dS(70, 0);
    _c->dS(100, 90);
    _c->dS(50, 0);
}

// 穴ジャンプ
void CourceManager::cPtn47(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(200, -50);
    _c->dS(100, -90);
    _c->dS(60, 0);
    _c->dS(120, 90);
    _c->dS(50, 0);
}

// comment
void CourceManager::cPtn48(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn49(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn50(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn51(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn52(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn53(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn54(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn55(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn56(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn57(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn58(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn59(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn60(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn61(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn62(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
}

// comment
void CourceManager::cPtn63(CourceMaker* _c){
    auto kaku = _c->_dirkaku;
    _c->dC(30,-10+kaku);
    _c->dC(30,kaku);
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
