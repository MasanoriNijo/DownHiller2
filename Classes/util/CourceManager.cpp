#include "CourceManager.h"

CourceManager::CourceManager():
_courceMakerA(NULL), _courceMakerB(NULL), _flg(NULL),_stagePrm(NULL),
_gurd(NULL),_gurdBody(NULL),_colorChanger(NULL)
{}

CourceManager::~CourceManager() {
	CC_SAFE_RELEASE_NULL(_courceMakerA);
	CC_SAFE_RELEASE_NULL(_courceMakerB);
    CC_SAFE_RELEASE_NULL(_flg);
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

void CourceManager::madeCourcePtnForTitle(CourceMaker* _c,int ind){
    auto flg = Flg::create();
    int i = 0;
    _c->drawStart(getTergetPt(),getTargetDir());
    ind = ind % 4;
    switch (ind) {
        case 0:
            _c->dS(800,-5);
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
             flg->setGlobalZOrder(OBJ_LAYER_TOP);
             flg->setPosition(_c->getTergetPt());
             flg->setRotation(_c->getCalc()->nomlKaku(Vec2::ZERO,_c->getTargetDir()));
             _c->addChild(flg);
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
            _c->dS(3000,-1);
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
             flg->setGlobalZOrder(OBJ_LAYER_TOP);
             flg->setPosition(_c->getTergetPt());
             flg->setRotation(_c->getCalc()->nomlKaku(Vec2::ZERO,_c->getTargetDir()));
             _c->addChild(flg);
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
             flg->setGlobalZOrder(OBJ_LAYER_TOP);
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
            _c->dS(50,-10);
            break;
        case 1:
            for(i=0;i<4;i++){
            _c->dC(Vec2(30,0), -90);
            _c->dS(Vec2(200,0));
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
             flg->setGlobalZOrder(OBJ_LAYER_TOP);
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
             flg->setGlobalZOrder(OBJ_LAYER_TOP);
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
            _c->dS(Vec2(0,100));
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
             flg->setGlobalZOrder(OBJ_LAYER_TOP);
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
            _c->dS(Vec2(0,100));
            _c->dS(Vec2(0,-100));
            _c->dS(100,0);
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
             flg->setGlobalZOrder(OBJ_LAYER_TOP);
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
            _c->dS(Vec2(0,100));
            _c->dS(Vec2(0,-100));
            _c->dS(100,0);
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
             flg->setGlobalZOrder(OBJ_LAYER_TOP);
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
            _c->dS(Vec2(0,100));
            _c->dS(Vec2(0,-100));
            _c->dS(100,0);
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
             flg->setGlobalZOrder(OBJ_LAYER_TOP);
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
            _c->dS(Vec2(0,100));
            _c->dS(Vec2(0,-100));
            _c->dS(100,0);
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
             flg->setGlobalZOrder(OBJ_LAYER_TOP);
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
            _c->dS(Vec2(0,100));
            _c->dS(Vec2(0,-100));
            _c->dS(300,-3);
            _c->dC(300, -45);
            _c->dS(1000, -45);
            break;
        case 1:
            _c->dC(240,300);
            _c->dS(Vec2(0,-100));
            _c->dS(Vec2(60,0));
            _c->dS(Vec2(0,50));
            _c->dS(Vec2(170,0));
            flg->setGlobalZOrder(OBJ_LAYER_TOP);
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
            _c->dS(Vec2(0,100));
            _c->dS(Vec2(0,-100));
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
             flg->setGlobalZOrder(OBJ_LAYER_TOP);
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
            _c->dS(Vec2(0,100));
            _c->dS(Vec2(0,-100));
            _c->dS(Vec2(300,-3));
            break;
        case 1:
            for(i=0;i<3;i++){
                _c->dS(200, -10);
                _c->dC(80, 50);
                _c->dS(150, -10);
                _c->dS(1, -70);
                _c->dC(80, -10);
            }
            break;
        case 2:
            for(i=0;i<8;i++){
                _c->dS(1, 85);
                _c->dC(10, -94);
                _c->dS(200, -5);
            }
            break;
        case 3:
            _c->dS(Vec2(300,0));
             flg->setGlobalZOrder(OBJ_LAYER_TOP);
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

void CourceManager::madeCourcePtn13(CourceMaker* _c,int ind){
    auto flg = Flg::create();
    int i = 0;
    _c->drawStart(getTergetPt(),getTargetDir());
    switch (ind) {
        case 0:
//            _c->drawByStraight(Vec2(0,100));
//            _c->drawByStraight(Vec2(0,-100));
            _c->dS(50,0);
            _c->dS(50,20);
            _c->dS(50,-20);
            _c->dS(50,20);
            _c->dS(50,-20);
            _c->dS(50,0);
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
            flg->setGlobalZOrder(OBJ_LAYER_TOP);
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

void CourceManager::madeCourcePtn14(CourceMaker* _c,int ind){
    auto flg = Flg::create();
    int i = 0;
    _c->drawStart(getTergetPt(),getTargetDir());
    switch (ind) {
        case 0:
            _c->dS(Vec2(0,100));
            _c->dS(Vec2(0,-100));
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
            flg->setGlobalZOrder(OBJ_LAYER_TOP);
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


void CourceManager::madeCourcePtn15(CourceMaker* _c,int ind){
    auto flg = Flg::create();
    int i = 0;
    _c->drawStart(getTergetPt(),getTargetDir());
    switch (ind) {
        case 0:
            _c->dS(Vec2(0,100));
            _c->dS(Vec2(0,-100));
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
            flg->setGlobalZOrder(OBJ_LAYER_TOP);
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


void CourceManager::madeCourcePtn16(CourceMaker* _c,int ind){
    auto flg = Flg::create();
    int i = 0;
    _c->drawStart(getTergetPt(),getTargetDir());
    switch (ind) {
        case 0:
            _c->dS(Vec2(0,100));
            _c->dS(Vec2(0,-100));
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
            flg->setGlobalZOrder(OBJ_LAYER_TOP);
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

void CourceManager::madeCourcePtn17(CourceMaker* _c,int ind){
    auto flg = Flg::create();
    int i = 0;
    _c->drawStart(getTergetPt(),getTargetDir());
    switch (ind) {
        case 0:
            _c->dS(Vec2(0,100));
            _c->dS(Vec2(0,-100));
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
            flg->setGlobalZOrder(OBJ_LAYER_TOP);
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
            _c->dS(Vec2(0,100));
            _c->dS(Vec2(0,-100));
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
            flg->setGlobalZOrder(OBJ_LAYER_TOP);
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
            _c->dS(Vec2(0,100));
            _c->dS(Vec2(0,-100));
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
            flg->setGlobalZOrder(OBJ_LAYER_TOP);
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
            _c->dS(Vec2(0,100));
            _c->dS(Vec2(0,-100));
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
            flg->setGlobalZOrder(OBJ_LAYER_TOP);
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
/** パラメータサンプル
setCourceMakerA(CourceMaker::create());
getCourceMakerA();
setCourceMakerB(CourceMaker::create());
getCourceMakerB();
*/
