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

void CourceManager::setStartAndTargetDromCource(CourceMaker* _cmaker){
    setStartPt(_cmaker->getStartPt());
    setStartDir(_cmaker->getStartDir());
    setTergetPt(_cmaker->getTergetPt());
    setTargetDir(_cmaker->getTargetDir());
}

void CourceManager::checkAndMadeCource(Vec2 chPt){
    if(chPt.x > (getStartPt().x + 100) || !courceIndex){
        switch (courceIndex) {
            case 0:
                madeCourcePtn1(getCourceMakerA());
                setStartAndTargetDromCource(getCourceMakerA());
                break;
            case 1:
                madeCourcePtn2(getCourceMakerB());
                setStartAndTargetDromCource(getCourceMakerB());
                break;
            case 2:
                madeCourcePtn3(getCourceMakerA());
                setStartAndTargetDromCource(getCourceMakerA());
                break;
            case 3:
                madeCourcePtn4(getCourceMakerB());
                setStartAndTargetDromCource(getCourceMakerB());
                break;
            default:
                break;
        }
        courceIndex ++;
    }
}

void CourceManager::madeCourcePtn1(CourceMaker* _cmaker){
    _cmaker->drawStart(getTergetPt(),getTargetDir());
    _cmaker->drawByStraight(Vec2(0,-1));
    _cmaker->drawByStraight(Vec2(200,0));
    for(int i = 0;i<2;i++){
        _cmaker->drawBySmoothCurve(20,-40);
        _cmaker->drawBySmoothCurve(50,60);
        _cmaker->drawBySmoothCurve(50,-60);
        _cmaker->drawBySmoothCurve(20,0);
        _cmaker->drawByStraight(Vec2(90,0));
    }
    for(int i = 0;i<8;i++){
        _cmaker->drawByStraight(Vec2(0,-20));
        _cmaker->drawByStraight(Vec2(80,0));
    }
    _cmaker->drawByStraight(Vec2(90,0));
    _cmaker->madePhysiceBody();
}

void CourceManager::madeCourcePtn2(CourceMaker* _cmaker){
   _cmaker->drawStart(getTergetPt(),getTargetDir());
   _cmaker->drawByStraight(Vec2(0,-100));
   _cmaker->drawByStraight(Vec2(200,0));
    for(int i = 0;i<2;i++){
       _cmaker->drawBySmoothCurve(Vec2(50,20));
       _cmaker->drawBySmoothCurve(Vec2(80,-50));
       _cmaker->drawBySmoothCurve(Vec2(100,50));
       _cmaker->drawBySmoothCurve(Vec2(100,-80));
       _cmaker->drawBySmoothCurve(Vec2(130,100));
       _cmaker->drawByStraight(Vec2(300,0));
       _cmaker->drawByStraight(Vec2(0,-50));
       _cmaker->drawByStraight(Vec2(90,0));
       _cmaker->drawByCurve(Vec2(240,-30), -50);
       _cmaker->drawByStraight(Vec2(0,-50));
       _cmaker->drawByStraight(Vec2(90,0));
    }
   _cmaker->drawByStraight(Vec2(90,0));

   _cmaker->madePhysiceBody();
}

void CourceManager::madeCourcePtn3(CourceMaker* _cmaker){
    _cmaker->drawStart(getTergetPt(),getTargetDir());
    _cmaker->drawByStraight(Vec2(0,-100));
    _cmaker->drawByStraight(Vec2(200,0));
     for(int i = 0;i<2;i++){
        _cmaker->drawBySmoothCurve(Vec2(50,20));
        _cmaker->drawBySmoothCurve(Vec2(80,-50));
        _cmaker->drawBySmoothCurve(Vec2(100,50));
        _cmaker->drawBySmoothCurve(Vec2(100,-80));
        _cmaker->drawBySmoothCurve(Vec2(130,100));
        _cmaker->drawByStraight(Vec2(300,0));
        _cmaker->drawByStraight(Vec2(0,-50));
        _cmaker->drawByStraight(Vec2(90,0));
        _cmaker->drawByCurve(Vec2(240,-30), -50);
        _cmaker->drawByStraight(Vec2(0,-50));
        _cmaker->drawByStraight(Vec2(90,0));
     }
    _cmaker->drawByStraight(Vec2(90,0));
    _cmaker->madePhysiceBody();
}

void CourceManager::madeCourcePtn4(CourceMaker* _cmaker){
    _cmaker->drawStart(getTergetPt(),getTargetDir());
    _cmaker->drawByStraight(Vec2(0,-100));
    _cmaker->drawByStraight(Vec2(200,0));
     for(int i = 0;i<2;i++){
        _cmaker->drawBySmoothCurve(Vec2(50,20));
        _cmaker->drawBySmoothCurve(Vec2(80,-50));
        _cmaker->drawBySmoothCurve(Vec2(100,50));
        _cmaker->drawBySmoothCurve(Vec2(100,-80));
        _cmaker->drawBySmoothCurve(Vec2(130,100));
        _cmaker->drawByStraight(Vec2(300,0));
        _cmaker->drawByStraight(Vec2(0,-50));
        _cmaker->drawByStraight(Vec2(90,0));
        _cmaker->drawByCurve(Vec2(240,-30), -50);
        _cmaker->drawByStraight(Vec2(0,-50));
        _cmaker->drawByStraight(Vec2(90,0));
     }
    _cmaker->drawByStraight(Vec2(90,0));
     auto flg = Flg::create();
     flg->setGlobalZOrder(OBJ_LAYER_TOP);
     flg->setPosition(_cmaker->getTergetPt());
     flg->setRotation(_cmaker->getCalc()->nomlKaku(Vec2::ZERO,_cmaker->getTargetDir()));
     _cmaker->addChild(flg);
    _cmaker->drawByStraight(Vec2(90,0));
    _cmaker->drawByStraight(Vec2(0,100));
    _cmaker->madePhysiceBody();
}
/** パラメータサンプル
setCourceMakerA(CourceMaker::create());
getCourceMakerA();
setCourceMakerB(CourceMaker::create());
getCourceMakerB();
*/
