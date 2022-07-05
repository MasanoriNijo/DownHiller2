#include "CourceManager.h"

CourceManager::CourceManager():
_courceMakerA(NULL), _courceMakerB(NULL), _flg(NULL),_stagePrm(NULL),
_gurd(NULL),_gurdBody(NULL)
{}

CourceManager::~CourceManager() {
	CC_SAFE_RELEASE_NULL(_courceMakerA);
	CC_SAFE_RELEASE_NULL(_courceMakerB);
    CC_SAFE_RELEASE_NULL(_flg);
    CC_SAFE_RELEASE_NULL(_stagePrm);
    CC_SAFE_RELEASE_NULL(_gurd);
    CC_SAFE_RELEASE_NULL(_gurdBody);
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
    setGurdBody(PhysicsBody::createEdgeSegment(Vec2(0,0), Vec2(0,100)));
    getGurdBody()->setDynamic(false);
    getGurdBody()->setCollisionBitmask(CT_ALL);
    getGurd()->setPhysicsBody(getGurdBody());
    
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
            getStagePrm()->setCommnent(head+
                                       "実際に操作してみて、\n"
                                       "ゴールを目指そう！"
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
                                       "コブを乗り越えて、\n"
                                       "10秒以内に、\n"
                                       "ゴールすること。"
                                       );
            getStagePrm()->setTymeLimit(10);
            break;
        case 7:
            getStagePrm()->setCommnent(head+
                                       "コブを乗り越えて、\n"
                                       "10秒以内に、\n"
                                       "ゴールすること。"
                                       );
            getStagePrm()->setTymeLimit(10);
            break;
        default:
            break;
    }
}

void CourceManager::setStartAndTargetFromCource(CourceMaker* _cmaker){
    setStartPt(_cmaker->getStartPt());
    setStartDir(_cmaker->getStartDir());
    setTergetPt(_cmaker->getTergetPt());
    setTargetDir(_cmaker->getTargetDir());
}

void CourceManager::checkAndMadeCource(Vec2 chPt){
    int stg = UserDefault::getInstance()->getIntegerForKey(UDF_INT_SELECTED_STAGE,1);
    if(chPt.x > (getStartPt().x + 100) || !courceIndex){
        switch (stg) {
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
                madeCourcePtn5(courceIndex%2 ? getCourceMakerB() : getCourceMakerA(),courceIndex);
                break;
            case 7:
                madeCourcePtn5(courceIndex%2 ? getCourceMakerB() : getCourceMakerA(),courceIndex);
                break;
            case 8:
                madeCourcePtn5(courceIndex%2 ? getCourceMakerB() : getCourceMakerA(),courceIndex);
                break;
            case 9:
                madeCourcePtn4(courceIndex%2 ? getCourceMakerB() : getCourceMakerA(),courceIndex);
                break;
            case 10:
                madeCourcePtn4(courceIndex%2 ? getCourceMakerB() : getCourceMakerA(),courceIndex);
                break;
            case 11:
                madeCourcePtn4(courceIndex%2 ? getCourceMakerB() : getCourceMakerA(),courceIndex);
                break;
            case 12:
                madeCourcePtn4(courceIndex%2 ? getCourceMakerB() : getCourceMakerA(),courceIndex);
                break;
            case 13:
                madeCourcePtn4(courceIndex%2 ? getCourceMakerB() : getCourceMakerA(),courceIndex);
                break;
            case 14:
                madeCourcePtn4(courceIndex%2 ? getCourceMakerB() : getCourceMakerA(),courceIndex);
                break;
            case 15:
                madeCourcePtn4(courceIndex%2 ? getCourceMakerB() : getCourceMakerA(),courceIndex);
                break;
            case 16:
                madeCourcePtn4(courceIndex%2 ? getCourceMakerB() : getCourceMakerA(),courceIndex);
                break;
            case 17:
                madeCourcePtn4(courceIndex%2 ? getCourceMakerB() : getCourceMakerA(),courceIndex);
                break;
            case 18:
                madeCourcePtn4(courceIndex%2 ? getCourceMakerB() : getCourceMakerA(),courceIndex);
                break;
            case 19:
                madeCourcePtn4(courceIndex%2 ? getCourceMakerB() : getCourceMakerA(),courceIndex);
                break;
            case 20:
                madeCourcePtn4(courceIndex%2 ? getCourceMakerB() : getCourceMakerA(),courceIndex);
                break;
            case 21:
                madeCourcePtn4(courceIndex%2 ? getCourceMakerB() : getCourceMakerA(),courceIndex);
                break;
            default:
                break;
        }
        getGurd()->setPosition(getStartPt());
        setStartAndTargetFromCource(courceIndex%2 ? getCourceMakerB() : getCourceMakerA());
        courceIndex ++;
    }
}

void CourceManager::madeCourcePtn1(CourceMaker* _cmaker,int ind){
    auto flg = Flg::create();
    int i = 0;
    _cmaker->drawStart(getTergetPt(),getTargetDir());
    switch (ind) {
        case 0:
            _cmaker->drawByStraight(Vec2(0,100));
            _cmaker->drawByStraight(Vec2(0,-100));
            _cmaker->drawByStraight(Vec2(1000,-10));
            break;
        case 1:
                _cmaker->drawBySmoothCurve(30, 10);
                _cmaker->drawByStraight(200, 10);
                _cmaker->drawBySmoothCurve(30, -10);
                _cmaker->drawBySmoothCurve(100, 10);
                _cmaker->drawByStraight(500, 0);
            break;
        case 2:
            for(i=0;i<3;i++){
                _cmaker->drawBySmoothCurve(100, -30);
                _cmaker->drawByStraight(100, -30);
                _cmaker->drawBySmoothCurve(60, 10);
                _cmaker->drawByStraight(400, 0);
            }
            break;
        case 3:
            _cmaker->drawByStraight(Vec2(90,0));
             flg->setGlobalZOrder(OBJ_LAYER_TOP);
             flg->setPosition(_cmaker->getTergetPt());
             flg->setRotation(_cmaker->getCalc()->nomlKaku(Vec2::ZERO,_cmaker->getTargetDir()));
             _cmaker->addChild(flg);
            _cmaker->drawByStraight(Vec2(200,0));
            _cmaker->drawByStraight(Vec2(0,100));
            break;
        default:
            return;
            break;
    }
    _cmaker->madePhysiceBody();
}

void CourceManager::madeCourcePtn2(CourceMaker* _cmaker,int ind){
    auto flg = Flg::create();
    int i = 0;
    _cmaker->drawStart(getTergetPt(),getTargetDir());
    switch (ind) {
        case 0:
            _cmaker->drawByStraight(Vec2(0,100));
            _cmaker->drawByStraight(Vec2(0,-100));
            _cmaker->drawByStraight(Vec2(400,-1));
            break;
        case 1:
            _cmaker->drawBySmoothCurve(120,60);
            _cmaker->drawBySmoothCurve(100,10);
            _cmaker->drawByStraight(Vec2(200,-90));
            break;
        case 2:
            for(i=0;i<4;i++){
                _cmaker->drawByStraight(Vec2(0,-50));
                _cmaker->drawByStraight(Vec2(60,0));
            }
            break;
        case 3:
            _cmaker->drawByStraight(Vec2(90,0));
             flg->setGlobalZOrder(OBJ_LAYER_TOP);
             flg->setPosition(_cmaker->getTergetPt());
             flg->setRotation(_cmaker->getCalc()->nomlKaku(Vec2::ZERO,_cmaker->getTargetDir()));
             _cmaker->addChild(flg);
            _cmaker->drawByStraight(Vec2(200,0));
            _cmaker->drawByStraight(Vec2(0,100));
            break;
        default:
            return;
            break;
    }
    _cmaker->madePhysiceBody();
}

void CourceManager::madeCourcePtn3(CourceMaker* _cmaker,int ind){
    auto flg = Flg::create();
    int i = 0;
    _cmaker->drawStart(getTergetPt(),getTargetDir());
    switch (ind) {
        case 0:
            _cmaker->drawByStraight(Vec2(0,100));
            _cmaker->drawByStraight(Vec2(0,-100));
            _cmaker->drawByStraight(Vec2(300,-1));
            break;
        case 1:
            for(i=0;i<4;i++){
            _cmaker->drawByCurve(Vec2(30,0), -90);
            _cmaker->drawByStraight(Vec2(200,0));
            }
            break;
        case 2:
            for(i=0;i<4;i++){
                _cmaker->drawByStraight(Vec2(0,-50));
                _cmaker->drawByStraight(Vec2(60,0));
            }
            break;
        case 3:
            _cmaker->drawByStraight(Vec2(90,0));
             flg->setGlobalZOrder(OBJ_LAYER_TOP);
             flg->setPosition(_cmaker->getTergetPt());
             flg->setRotation(_cmaker->getCalc()->nomlKaku(Vec2::ZERO,_cmaker->getTargetDir()));
             _cmaker->addChild(flg);
            _cmaker->drawByStraight(Vec2(200,0));
            _cmaker->drawByStraight(Vec2(0,100));
            break;
        default:
            return;
            break;
    }
    _cmaker->madePhysiceBody();
}

void CourceManager::madeCourcePtn4(CourceMaker* _cmaker,int ind){
    auto flg = Flg::create();
    int i = 0;
    _cmaker->drawStart(getTergetPt(),getTargetDir());
    switch (ind) {
        case 0:
            _cmaker->drawByStraight(Vec2(0,100));
            _cmaker->drawByStraight(Vec2(0,-100));
            _cmaker->drawByStraight(Vec2(200,-3));
            break;
        case 1:
            for(i=0;i<4;i++){
                _cmaker->drawBySmoothCurve(50, -70);
                _cmaker->drawByStraight(100, -70);
                _cmaker->drawBySmoothCurve(50, 70);
                _cmaker->drawByStraight(100, 70);
                _cmaker->drawBySmoothCurve(50, 0);
                _cmaker->drawByStraight(100, 0);
                
            }
            break;
        case 2:
            for(i=0;i<4;i++){
                _cmaker->drawByStraight(Vec2(0,-50));
                _cmaker->drawByStraight(Vec2(60,0));
            }
            break;
        case 3:
            _cmaker->drawByStraight(Vec2(90,0));
             flg->setGlobalZOrder(OBJ_LAYER_TOP);
             flg->setPosition(_cmaker->getTergetPt());
             flg->setRotation(_cmaker->getCalc()->nomlKaku(Vec2::ZERO,_cmaker->getTargetDir()));
             _cmaker->addChild(flg);
            _cmaker->drawByStraight(Vec2(200,0));
            _cmaker->drawByStraight(Vec2(0,100));
            break;
        default:
            return;
            break;
    }
    _cmaker->madePhysiceBody();
}

void CourceManager::madeCourcePtn5(CourceMaker* _cmaker,int ind){
    auto flg = Flg::create();
    int i = 0;
    _cmaker->drawStart(getTergetPt(),getTargetDir());
    switch (ind) {
        case 0:
            _cmaker->drawByStraight(Vec2(0,100));
            _cmaker->drawByStraight(Vec2(0,-100));
            _cmaker->drawByStraight(Vec2(300,-3));
            break;
        case 1:
                _cmaker->drawBySmoothCurve(50, -70);
                _cmaker->drawByStraight(600, -70);
                _cmaker->drawBySmoothCurve(80, 70);
                _cmaker->drawByStraight(50, 70);
                _cmaker->drawBySmoothCurve(20, 0);
                _cmaker->drawByStraight(100, 0);
            break;
        case 2:
                _cmaker->drawByStraight(Vec2(0,80));
                _cmaker->drawByStraight(Vec2(380,0));
            break;
        case 3:
            _cmaker->drawByStraight(Vec2(90,0));
             flg->setGlobalZOrder(OBJ_LAYER_TOP);
             flg->setPosition(_cmaker->getTergetPt());
             flg->setRotation(_cmaker->getCalc()->nomlKaku(Vec2::ZERO,_cmaker->getTargetDir()));
             _cmaker->addChild(flg);
            _cmaker->drawByStraight(Vec2(200,0));
            _cmaker->drawByStraight(Vec2(0,100));
            break;
        default:
            return;
            break;
    }
    _cmaker->madePhysiceBody();
}

/** パラメータサンプル
setCourceMakerA(CourceMaker::create());
getCourceMakerA();
setCourceMakerB(CourceMaker::create());
getCourceMakerB();
*/
