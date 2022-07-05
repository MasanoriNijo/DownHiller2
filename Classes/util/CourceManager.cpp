#include "CourceManager.h"

CourceManager::CourceManager():
_courceMakerA(NULL), _courceMakerB(NULL), _flg(NULL),_stagePrm(NULL)
{}

CourceManager::~CourceManager() {
	CC_SAFE_RELEASE_NULL(_courceMakerA);
	CC_SAFE_RELEASE_NULL(_courceMakerB);
    CC_SAFE_RELEASE_NULL(_flg);
    CC_SAFE_RELEASE_NULL(_stagePrm);
}

bool CourceManager::init() {
    setCourceMakerA(CourceMaker::create());
    setCourceMakerB(CourceMaker::create());
    setStartPt(FIRST_COURCE_BASE_POINT);
    setTergetPt(FIRST_COURCE_BASE_POINT);
    setStartDir(Vec2::ZERO);
    setTargetDir(Vec2::ZERO);
    _setStagePrm();
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
                                       "コブを乗り越えて、\n"
                                       "10秒以内に、\n"
                                       "ゴールすること。"
                                       );
            getStagePrm()->setTymeLimit(10);
            break;
        case 5:
            getStagePrm()->setCommnent(head+
                                       "コブを乗り越えて、\n"
                                       "10秒以内に、\n"
                                       "ゴールすること。"
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
            default:
                break;
        }
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
            _cmaker->drawByStraight(Vec2(800,-10));
            break;
        case 1:
            for(i=0;i<3;i++){
                _cmaker->drawBySmoothCurve(100, 10);
                _cmaker->drawBySmoothCurve(100, -30);
                _cmaker->drawBySmoothCurve(100, 0);
                _cmaker->drawByStraight(200, 0);
            }
            break;
        case 2:
            for(i=0;i<3;i++){
                _cmaker->drawBySmoothCurve(100, -30);
                _cmaker->drawBySmoothCurve(60, 10);
                _cmaker->drawBySmoothCurve(100, 0);
                _cmaker->drawByStraight(200, -10);
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
            _cmaker->drawBySmoothCurve(500,-40);
            _cmaker->drawBySmoothCurve(100,10);
            _cmaker->drawBySmoothCurve(240,-60);
            _cmaker->drawBySmoothCurve(20,0);
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
            _cmaker->drawByStraight(Vec2(5000,-1));
            break;
        case 1:
            _cmaker->drawBySmoothCurve(200,-40);
            _cmaker->drawBySmoothCurve(100,-10);
            _cmaker->drawBySmoothCurve(140,10);
            _cmaker->drawBySmoothCurve(20,0);
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

/** パラメータサンプル
setCourceMakerA(CourceMaker::create());
getCourceMakerA();
setCourceMakerB(CourceMaker::create());
getCourceMakerB();
*/
