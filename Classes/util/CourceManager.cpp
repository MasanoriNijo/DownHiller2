#include "CourceManager.h"

CourceManager::CourceManager():
_courceMakerA(NULL), _courceMakerB(NULL), _flg(NULL)
{}

CourceManager::~CourceManager() {
	CC_SAFE_RELEASE_NULL(_courceMakerA);
	CC_SAFE_RELEASE_NULL(_courceMakerB);
    CC_SAFE_RELEASE_NULL(_flg);
}

bool CourceManager::init() {
    setCourceMakerA(CourceMaker::create());
    setCourceMakerB(CourceMaker::create());
    setStartPt(FIRST_COURCE_BASE_POINT);
    setTergetPt(FIRST_COURCE_BASE_POINT);
    setStartDir(Vec2::ZERO);
    setTargetDir(Vec2::ZERO);
  return true;
}

void CourceManager::onEnterTransitionDidFinish() {
  // todo
}

void CourceManager::update(float dt) {
  // todo
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
            _cmaker->drawByStraight(Vec2(2000,1));
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

void CourceManager::madeCourcePtn2(CourceMaker* _cmaker,int ind){
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

void CourceManager::madeCourcePtn3(CourceMaker* _cmaker,int ind){
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

std::string CourceManager::getStgComment(int stg){
    std::string head = "クリア条件\n";
    switch (stg) {
        case 1:
            return head +
            "ゴールすること。";
            break;
        case 2:
            return head +
            "ゴールすること。";
            break;
        case 3:
            return head +
            "制限時間内に、\n"
            "ゴールすること。";
            break;
        case 4:
            return head +
            "ゴールすること。";
            break;
        case 5:
            return head +
            "ゴールすること。";
            break;
        case 6:
            return head +
            "ゴールすること。";
            break;
        case 7:
            return head +
            "ゴールすること。";
            break;
        default:
            break;
    }
    
    
    
}
/** パラメータサンプル
setCourceMakerA(CourceMaker::create());
getCourceMakerA();
setCourceMakerB(CourceMaker::create());
getCourceMakerB();
*/
