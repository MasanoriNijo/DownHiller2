#include "CourceManager.h"

CourceManager::CourceManager():
_courceMakerA(NULL), _courceMakerB(NULL), _courceMakerSel(NULL), _startFlg(NULL), _goalFlg(NULL),_stagePrm(NULL),
_gurd(NULL),_gurdBody(NULL),_colorChanger(NULL)
{}

CourceManager::~CourceManager() {
    CC_SAFE_RELEASE_NULL(_courceMakerA);
    CC_SAFE_RELEASE_NULL(_courceMakerB);
    CC_SAFE_RELEASE_NULL(_courceMakerSel);
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
        getStagePrm()->setTymeLimit(60);
        if(getStagePrm()->getStageNumber() == 0){
            getStagePrm()->setCommnent(
                                       "ここからは、\n"
                                       "実際に操作して、\n"
                                       "ゴールを目指そう!\n"
                                       );
        }
        return;
    }else{
        getStagePrm()->setTymeLimit(genTimeLimit(getStagePrm()->getStageNumber()));
        getStagePrm()->setCommnent(genComment(getStagePrm()->getStageNumber()));
        return;
    }
}

std::string CourceManager::genComment(int courceNo){
    switch (courceNo) {
        case -1:
            return
            "ここからは、\n"
            "実際に操作して、\n"
            "ゴールを目指そう!\n";
            break;
        case 0:
            return
            "ゆるやかな凹凸のある坂道1\n"
            "しゃがんで前にスワイプすると\n"
            "ダッシュできるよ！";
            break;
        case 1:
            return
            "ゆるやかな凹凸のある坂道2\n"
            "左右にスワイプして\n"
            "姿勢を制御しよう！";;
            break;
        case 2:
            return
            "ゆるやかな凹凸のある坂道3\n"
            "制限時間内のゴールしよう！\n"
            "スピードが落ちたらダッシュしよう！\n";
            break;
        case 3:
            return
            "ゆるやかな凹凸のある坂道3\n"
            "制限時間内のゴールしよう！\n"
            "スピードをキープするのがコツだよ！\n";
            break;
        case 4:
            return
            "小さなコブのある道1\n"
            "コブはしゃがんだ状態で\n"
            "上に素早くスワイプして\n"
            "ジャンプで飛び越えよう！";
            break;
        case 5:
            return
            "小さなコブのある道\n"
            "制限時間内のゴールしよう！\n";
            break;
        case 6:
            return
            "凹凸のある急な坂道1\n"
            "スピードが出過ぎたら\n"
            "左下に重心を移動して\n"
            "ブレーキをかけよう！";
            break;
        case 7:
            return
            "凹凸のある急な坂道2\n"
            "スピードが出過ぎたら\n"
            "左下に重心を移動して\n"
            "ブレーキをかけよう！";
            break;
        case 8:
            return
            "凹凸のある急な坂道3\n"
            "制限時間内のゴールしよう！\n";
            break;
        case 9:
            return
            "平地ジャンプ台1\n"
            "ダッシュで加速して\n"
            "ジャンプ台\n"
            "で飛び越えよう！";
            break;
        case 10:
            return
            "平地ジャンプ台2\n"
            "ダッシュで加速して\n"
            "ジャンプ台\n"
            "で飛び越えよう！";
            break;
        case 11:
            return
            "平地ジャンプ台3\n"
            "スピードを保って\n"
            "連続して\n"
            "飛び越えよう！";
            break;
        case 12:
            return
            "平地ジャンプ台4\n"
            "制限時間内で\n"
            "ゴールしよう！";
            break;
        case 13:
            return
            "平地ジャンプ台5\n"
            "制限時間内で\n"
            "ゴールしよう！";
            break;
        case 14:
            return
            "自然な激しい坂道1\n"
            "前転しないように\n"
            "姿勢を制御しよう！";
            break;
        case 15:
            return
            "自然な激しい坂道2\n"
            "制限時間内で\n"
            "ゴールしよう！";
            break;
        case 16:
            return
            "バンプトラック1\n"
            "下りRで後輪を\n"
            "プッシュしよう！\n"
            "スピードにのるぞ！";
            break;
        case 17:
            return
            "バンプトラック2\n"
            "下りRで後輪を\n"
            "プッシュしよう！\n"
            "スピードにのるぞ！";
            break;
        case 18:
            return
            "階段下り1\n"
            "前転に注意！";
            break;
        case 19:
            return
            "階段下り2\n"
            "前転に注意！";
            break;
        case 20:
            return
            "階段下り3\n"
            "制限時間内で\n"
            "ゴールしよう！";
            break;
        case 21:
            return
            "コメントを記入";
            break;
        case 22:
            return
            "コメントを記入";
            break;
        case 23:
            return
            "コメントを記入";
            break;
        case 24:
            return
            "コメントを記入";
            break;
        case 25:
            return
            "コメントを記入";
            break;
        case 26:
            return
            "コメントを記入";
            break;
        case 27:
            return
            "コメントを記入";
            break;
        case 28:
            return
            "コメントを記入";
            break;
        case 29:
            return
            "コメントを記入";
            break;
        case 30:
            return
            "バンプトラック3\n"
            "制限時間に\n"
            "ゴールしよう！\n";
            break;
        case 31:
            return
            "コメントを記入";
            break;
        case 32:
            return
            "コメントを記入";
            break;
        case 33:
            return
            "コメントを記入";
            break;
        case 34:
            return
            "コメントを記入";
            break;
        case 35:
            return
            "コメントを記入";
            break;
        case 36:
            return
            "コメントを記入";
            break;
        case 37:
            return
            "コメントを記入";
            break;
        case 38:
            return
            "コメントを記入";
            break;
        case 39:
            return
            "コメントを記入";
            break;
        case 40:
            return
            "コメントを記入";
            break;
        case 41:
            return
            "コメントを記入";
            break;
        case 42:
            return
            "コメントを記入";
            break;
        case 43:
            return
            "コメントを記入";
            break;
        case 44:
            return
            "コメントを記入";
            break;
        case 45:
            return
            "コメントを記入";
            break;
        case 46:
            return
            "コメントを記入";
            break;
        case 47:
            return
            "コメントを記入";
            break;
        case 48:
            return
            "コメントを記入";
            break;
        case 49:
            return
            "コメントを記入";
            break;
        case 50:
            return
            "コメントを記入";
            break;
        case 51:
            return
            "コメントを記入";
            break;
        case 52:
            return
            "コメントを記入";
            break;
        case 53:
            return
            "コメントを記入";
            break;
        case 54:
            return
            "コメントを記入";
            break;
        case 55:
            return
            "コメントを記入";
            break;
        case 56:
            return
            "コメントを記入";
            break;
        case 57:
            return
            "コメントを記入";
            break;
        case 58:
            return
            "コメントを記入";
            break;
        case 59:
            return
            "コメントを記入";
            break;
        case 60:
            return
            "コメントを記入";
            break;
        case 61:
            return
            "コメントを記入";
            break;
        case 62:
            return
            "コメントを記入";
            break;
        case 63:
            return
            "コメントを記入";
            break;
        case 64:
            return
            "コメントを記入";
            break;
        case 65:
            return
            "コメントを記入";
            break;
        case 66:
            return
            "コメントを記入";
            break;
        case 67:
            return
            "コメントを記入";
            break;
        case 68:
            return
            "コメントを記入";
            break;
        case 69:
            return
            "コメントを記入";
            break;
        case 70:
            return
            "コメントを記入";
            break;
        case 71:
            return
            "コメントを記入";
            break;
        case 72:
            return
            "コメントを記入";
            break;
        case 73:
            return
            "コメントを記入";
            break;
        case 74:
            return
            "コメントを記入";
            break;
        case 75:
            return
            "コメントを記入";
            break;
        case 76:
            return
            "コメントを記入";
            break;
        case 77:
            return
            "コメントを記入";
            break;
        case 78:
            return
            "コメントを記入";
            break;
        case 79:
            return
            "コメントを記入";
            break;
        case 80:
            return
            "コメントを記入";
            break;
        case 81:
            return
            "コメントを記入";
            break;
        case 82:
            return
            "コメントを記入";
            break;
        case 83:
            return
            "コメントを記入";
            break;
        case 84:
            return
            "コメントを記入";
            break;
        case 85:
            return
            "コメントを記入";
            break;
        case 86:
            return
            "コメントを記入";
            break;
        case 87:
            return
            "コメントを記入";
            break;
        case 88:
            return
            "コメントを記入";
            break;
        case 89:
            return
            "コメントを記入";
            break;
        case 90:
            return
            "コメントを記入";
            break;
        case 91:
            return
            "コメントを記入";
            break;
        case 92:
            return
            "コメントを記入";
            break;
        case 93:
            return
            "コメントを記入";
            break;
        case 94:
            return
            "コメントを記入";
            break;
        case 95:
            return
            "コメントを記入";
            break;
        case 96:
            return
            "コメントを記入";
            break;
        case 97:
            return
            "コメントを記入";
            break;
        case 98:
            return
            "コメントを記入";
            break;
        case 99:
            return
            "コメントを記入";
            break;
        default:
            return "ステージ:" + ST_INT(courceNo);
            break;
    }
}

int CourceManager::genTimeLimit(int courceNo){
    switch (courceNo) {
        case 0:
            return 0;
            break;
        case 1:
            return 0;
            break;
        case 2:
            return 25;
            break;
        case 3:
            return 25;
            break;
        case 4:
            return 0;
            break;
        case 5:
            return 18;
            break;
        case 6:
            return 0;
            break;
        case 7:
            return 0;
            break;
        case 8:
            return 18;
            break;
        case 9:
            return 0;
            break;
        case 10:
            return 0;
            break;
        case 11:
            return 0;
            break;
        case 12:
            return 28;
            break;
        case 13:
            return 26;
            break;
        case 14:
            return 0;
            break;
        case 15:
            return 15;
            break;
        case 16:
            return 0;
            break;
        case 17:
            return 0;
            break;
        case 18:
            return 0;
            break;
        case 19:
            return 0;
            break;
        case 20:
            return 35;
            break;
        case 21:
            return 0;
            break;
        case 22:
            return 0;
            break;
        case 23:
            return 0;
            break;
        case 24:
            return 0;
            break;
        case 25:
            return 0;
            break;
        case 26:
            return 0;
            break;
        case 27:
            return 0;
            break;
        case 28:
            return 0;
            break;
        case 29:
            return 0;
            break;
        case 30:
            return 25;
            break;
        case 31:
            return 0;
            break;
        case 32:
            return 0;
            break;
        case 33:
            return 0;
            break;
        case 34:
            return 0;
            break;
        case 35:
            return 0;
            break;
        case 36:
            return 0;
            break;
        case 37:
            return 0;
            break;
        case 38:
            return 0;
            break;
        case 39:
            return 0;
            break;
        case 40:
            return 0;
            break;
        case 41:
            return 0;
            break;
        case 42:
            return 0;
            break;
        case 43:
            return 0;
            break;
        case 44:
            return 0;
            break;
        case 45:
            return 0;
            break;
        case 46:
            return 0;
            break;
        case 47:
            return 0;
            break;
        case 48:
            return 0;
            break;
        case 49:
            return 0;
            break;
        case 50:
            return 0;
            break;
        case 51:
            return 0;
            break;
        case 52:
            return 0;
            break;
        case 53:
            return 0;
            break;
        case 54:
            return 0;
            break;
        case 55:
            return 0;
            break;
        case 56:
            return 0;
            break;
        case 57:
            return 0;
            break;
        case 58:
            return 0;
            break;
        case 59:
            return 0;
            break;
        case 60:
            return 0;
            break;
        case 61:
            return 0;
            break;
        case 62:
            return 0;
            break;
        case 63:
            return 0;
            break;
        case 64:
            return 0;
            break;
        case 65:
            return 0;
            break;
        case 66:
            return 0;
            break;
        case 67:
            return 0;
            break;
        case 68:
            return 0;
            break;
        case 69:
            return 0;
            break;
        case 70:
            return 0;
            break;
        case 71:
            return 0;
            break;
        case 72:
            return 0;
            break;
        case 73:
            return 0;
            break;
        case 74:
            return 0;
            break;
        case 75:
            return 0;
            break;
        case 76:
            return 0;
            break;
        case 77:
            return 0;
            break;
        case 78:
            return 0;
            break;
        case 79:
            return 0;
            break;
        case 80:
            return 0;
            break;
        case 81:
            return 0;
            break;
        case 82:
            return 0;
            break;
        case 83:
            return 0;
            break;
        case 84:
            return 0;
            break;
        case 85:
            return 0;
            break;
        case 86:
            return 0;
            break;
        case 87:
            return 0;
            break;
        case 88:
            return 0;
            break;
        case 89:
            return 0;
            break;
        case 90:
            return 0;
            break;
        case 91:
            return 0;
            break;
        case 92:
            return 0;
            break;
        case 93:
            return 0;
            break;
        case 94:
            return 0;
            break;
        case 95:
            return 0;
            break;
        case 96:
            return 0;
            break;
        case 97:
            return 0;
            break;
        case 98:
            return 0;
            break;
        case 99:
            return 0;
            break;
        default:
            return 0;
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
    
    if(getCourceMakerSel() != NULL && getCourceMakerSel()->_madeInd < 2){
        getCourceMakerSel()->madePhysiceBodyGradualy();
        return;
    }
    
    if(UserDefault::getInstance()->getBoolForKey(UDF_BOOL_DEBUG_STAGE, false)){
        checkAndMadeCourceForTraining(chPt);
        return;
    }
    
    if(chPt.x > (getStartPt().x + 200) || !courceIndex){
        _dirkaku = courceIndex%2 ? getCourceMakerA()->_dirkaku : getCourceMakerB()->_dirkaku;
        setCourceMakerSel(courceIndex%2 ? getCourceMakerB() : getCourceMakerA());
        getCourceMakerSel()->drawStart(getTergetPt(),getTargetDir());
        getCourceMakerSel()->_dirkaku = _dirkaku;
        
        switch (selStg) {
            case -1:
                madeCourcePtnForTitle(getCourceMakerSel(),courceIndex);
                break;
            case 0: // howto画面用
                madeCourcePtn0(getCourceMakerSel(),courceIndex);
                break;
            case 1:
                madeCourcePtn1(getCourceMakerSel(),courceIndex);
                break;
            case 2:
                madeCourcePtn2(getCourceMakerSel(),courceIndex);
                break;
            case 3:
                madeCourcePtn3(getCourceMakerSel(),courceIndex);
                break;
            case 4:
                madeCourcePtn4(getCourceMakerSel(),courceIndex);
                break;
            case 5:
                madeCourcePtn5(getCourceMakerSel(),courceIndex);
                break;
            case 6:
                madeCourcePtn6(getCourceMakerSel(),courceIndex);
                break;
            case 7:
                madeCourcePtn7(getCourceMakerSel(),courceIndex);
                break;
            case 8:
                madeCourcePtn8(getCourceMakerSel(),courceIndex);
                break;
            case 9:
                madeCourcePtn9(getCourceMakerSel(),courceIndex);
                break;
            case 10:
                madeCourcePtn10(getCourceMakerSel(),courceIndex);
                break;
            case 11:
                madeCourcePtn11(getCourceMakerSel(),courceIndex);
                break;
            case 12:
                madeCourcePtn12(getCourceMakerSel(),courceIndex);
                break;
            case 13:
                madeCourcePtn13(getCourceMakerSel(),courceIndex);
                break;
            case 14:
                madeCourcePtn14(getCourceMakerSel(),courceIndex);
                break;
            case 15:
                madeCourcePtn15(getCourceMakerSel(),courceIndex);
                break;
            case 16:
                madeCourcePtn16(getCourceMakerSel(),courceIndex);
                break;
            case 17:
                madeCourcePtn17(getCourceMakerSel(),courceIndex);
                break;
            case 18:
                madeCourcePtn18(getCourceMakerSel(),courceIndex);
                break;
            case 19:
                madeCourcePtn19(getCourceMakerSel(),courceIndex);
                break;
            case 20:
                madeCourcePtn20(getCourceMakerSel(),courceIndex);
                break;
            case 21:
                madeCourcePtn20(getCourceMakerSel(),courceIndex);
                break;
            default:
                break;
        }
        getGurd()->setPosition(getStartPt());
        setStartAndTargetFromCource(getCourceMakerSel());
        getCourceMakerSel()->_madeInd = 0;
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

void CourceManager::cPtnStart(CourceMaker* _c){
    _c->dS(615,0);
    setStart(_c);
    _c->dC(300,-20);
}

void CourceManager::cPtnGoal(CourceMaker* _c){
    _c->dS(200,0);
    setGoal(_c);
    _c->dS(1000,0);
    _c->dS(100,90);
}

void CourceManager::madeCourcePtnForTitle(CourceMaker* _c,int ind){
    auto flg = Flg::create();
    int i = 0;
    _c->drawStart(getTergetPt(),getTargetDir());
    ind = ind % 4;
    switch (ind) {
        case 0:
            _c->dS(40,-90);
            cPtnStart(_c);
            break;
        case 1:
            for(i=0;i<16;i++){
                int kaku_ = random<int>(0, 1) ? random<int>(-70, -30):random<int>(-5, 0);
                int length_ = random<int>(0, 1) ? random<int>(50, 100):random<int>(100, 200);
                float r_ = random<float>(100,400);
                if(random<int>(0, 1)){
                    _c->dC(r_, kaku_);
                }else{
                    _c->dS(length_,kaku_);
                }
            }
            break;
        case 2:
            for(i=0;i<16;i++){
                int kaku_ = random<int>(0, 1) ? random<int>(-50, -30):random<int>(-5, 0);
                int length_ = random<int>(0, 1) ? random<int>(100, 300):random<int>(100, 200);
                float r_ = random<float>(100,400);
                if(random<int>(0, 1)){
                    _c->dC(r_, kaku_);
                }else{
                    _c->dS(length_,kaku_);
                }
            }
            break;
        case 3:
            cPtnGoal(_c);
            break;
        default:
            cPtnGoal(_c);
            return;
            break;
    }
}

void CourceManager::madeCourcePtn0(CourceMaker* _c,int ind){
    auto flg = Flg::create();
    int i = 0;
    _c->drawStart(getTergetPt(),getTargetDir());
    switch (ind) {
        case 0:
            _c->dS(500,0);
            _c->dS(115,-1);
            setStart(_c);
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
            setGoal(_c);
            _c->dS(Vec2(1000,0));
            _c->dS(Vec2(0,100));
            break;
        default:
            return;
            break;
    }
    
}

void CourceManager::madeCourcePtn1(CourceMaker* _c,int ind){
    auto flg = Flg::create();
    int i = 0;
    _c->drawStart(getTergetPt(),getTargetDir());
    switch (ind) {
        case 0:
            cPtnStart(_c);
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
            cPtnGoal(_c);
            break;
        default:
            return;
            break;
    }
    
}

void CourceManager::madeCourcePtn2(CourceMaker* _c,int ind){
    int i = 0;
    _c->drawStart(getTergetPt(),getTargetDir());
    switch (ind) {
        case 0:
            cPtnStart(_c);
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
            cPtnGoal(_c);
            break;
        default:
            return;
            break;
    }
    
}

void CourceManager::madeCourcePtn3(CourceMaker* _c,int ind){
    int i = 0;
    _c->drawStart(getTergetPt(),getTargetDir());
    switch (ind) {
        case 0:
            cPtnStart(_c);
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
            cPtnGoal(_c);
            break;
        default:
            return;
            break;
    }
    
}

void CourceManager::madeCourcePtn4(CourceMaker* _c,int ind){
    int i = 0;
    _c->drawStart(getTergetPt(),getTargetDir());
    switch (ind) {
        case 0:
            cPtnStart(_c);
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
            cPtnGoal(_c);
            break;
        default:
            return;
            break;
    }
    
}

void CourceManager::madeCourcePtn5(CourceMaker* _c,int ind){
    int i = 0;
    _c->drawStart(getTergetPt(),getTargetDir());
    switch (ind) {
        case 0:
            cPtnStart(_c);
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
            cPtnGoal(_c);
            break;
        default:
            return;
            break;
    }
    
}

void CourceManager::madeCourcePtn6(CourceMaker* _c,int ind){
    int i = 0;
    _c->drawStart(getTergetPt(),getTargetDir());
    switch (ind) {
        case 0:
            cPtnStart(_c);
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
            cPtnGoal(_c);
            break;
        default:
            return;
            break;
    }
    
}

void CourceManager::madeCourcePtn7(CourceMaker* _c,int ind){
    int i = 0;
    _c->drawStart(getTergetPt(),getTargetDir());
    switch (ind) {
        case 0:
            cPtnStart(_c);
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
            cPtnGoal(_c);
            break;
        default:
            return;
            break;
    }
    
}

void CourceManager::madeCourcePtn8(CourceMaker* _c,int ind){
    int i = 0;
    _c->drawStart(getTergetPt(),getTargetDir());
    switch (ind) {
        case 0:
            cPtnStart(_c);
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
            cPtnGoal(_c);
            break;
        default:
            return;
            break;
    }
    
}

void CourceManager::madeCourcePtn9(CourceMaker* _c,int ind){
    int i = 0;
    _c->drawStart(getTergetPt(),getTargetDir());
    switch (ind) {
        case 0:
            cPtnStart(_c);
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
            cPtnGoal(_c);
            break;
        default:
            return;
            break;
    }
    
}

void CourceManager::madeCourcePtn10(CourceMaker* _c,int ind){
    int i = 0;
    _c->drawStart(getTergetPt(),getTargetDir());
    switch (ind) {
        case 0:
            cPtnStart(_c);
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
            cPtnGoal(_c);
            break;
        default:
            return;
            break;
    }
    
}

void CourceManager::madeCourcePtn11(CourceMaker* _c,int ind){
    int i = 0;
    _c->drawStart(getTergetPt(),getTargetDir());
    switch (ind) {
        case 0:
            cPtnStart(_c);
            break;
        case 1:
            cPtn20(_c);
            cPtn39(_c);
            break;
        case 2:
            cPtn52(_c);
            cPtn25(_c);
            break;
        case 3:
            cPtnGoal(_c);
            break;
        default:
            return;
            break;
    }
    
}

void CourceManager::madeCourcePtn12(CourceMaker* _c,int ind){
    int i = 0;
    _c->drawStart(getTergetPt(),getTargetDir());
    switch (ind) {
        case 0:
            cPtnStart(_c);
            break;
        case 1:
            cPtn00(_c);
            cPtn53(_c);
            break;
        case 2:
            cPtn50(_c);
            cPtn39(_c);
            break;
        case 3:
            cPtnGoal(_c);
            break;
        default:
            return;
            break;
    }
    
}

void CourceManager::madeCourcePtn13(CourceMaker* _c,int ind){
    int i = 0;
    _c->drawStart(getTergetPt(),getTargetDir());
    switch (ind) {
        case 0:
            cPtnStart(_c);
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
            cPtnGoal(_c);
            break;
        default:
            return;
            break;
    }
    
}

void CourceManager::madeCourcePtn14(CourceMaker* _c,int ind){
    int i = 0;
    _c->drawStart(getTergetPt(),getTargetDir());
    switch (ind) {
        case 0:
            cPtnStart(_c);
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
            cPtnGoal(_c);
            break;
        default:
            return;
            break;
    }
    
}


void CourceManager::madeCourcePtn15(CourceMaker* _c,int ind){
    int i = 0;
    _c->drawStart(getTergetPt(),getTargetDir());
    switch (ind) {
        case 0:
            cPtnStart(_c);
            break;
        case 1:
            cPtn07(_c);
            cPtn54(_c);
            break;
        case 2:
            cPtn58(_c);
            cPtn34(_c);
            break;
        case 3:
            cPtnGoal(_c);
            break;
        default:
            return;
            break;
    }
    
}


void CourceManager::madeCourcePtn16(CourceMaker* _c,int ind){
    int i = 0;
    _c->drawStart(getTergetPt(),getTargetDir());
    switch (ind) {
        case 0:
            cPtnStart(_c);
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
            cPtnGoal(_c);
            break;
        default:
            return;
            break;
    }
    
}

void CourceManager::madeCourcePtn17(CourceMaker* _c,int ind){
    int i = 0;
    _c->drawStart(getTergetPt(),getTargetDir());
    switch (ind) {
        case 0:
            cPtnStart(_c);
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
            cPtnGoal(_c);
            break;
        default:
            return;
            break;
    }
    
}

void CourceManager::madeCourcePtn18(CourceMaker* _c,int ind){
    int i = 0;
    _c->drawStart(getTergetPt(),getTargetDir());
    switch (ind) {
        case 0:
            cPtnStart(_c);
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
            cPtnGoal(_c);
            break;
        default:
            return;
            break;
    }
    
}

void CourceManager::madeCourcePtn19(CourceMaker* _c,int ind){
    int i = 0;
    _c->drawStart(getTergetPt(),getTargetDir());
    switch (ind) {
        case 0:
            cPtnStart(_c);
            break;
        case 1:
            cPtn14(_c);
            cPtn54(_c);
            break;
        case 2:
            cPtn62(_c);
            cPtn26(_c);
            break;
        case 3:
            cPtnGoal(_c);
            break;
        default:
            return;
            break;
    }
    
}

void CourceManager::madeCourcePtn20(CourceMaker* _c,int ind){
    int i = 0;
    _c->drawStart(getTergetPt(),getTargetDir());
    switch (ind) {
        case 0:
            cPtnStart(_c);
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
            cPtnGoal(_c);
            break;
        default:
            return;
            break;
    }
    
}

void CourceManager::checkAndMadeCourceForTraining(Vec2 chPt){
    if(chPt.x > (getStartPt().x + 200) || !courceIndex){
        _dirkaku = courceIndex%2 ? getCourceMakerA()->_dirkaku : getCourceMakerB()->_dirkaku;
        _dirkaku = courceIndex%2 ? getCourceMakerA()->_dirkaku : getCourceMakerB()->_dirkaku;
        setCourceMakerSel(courceIndex%2 ? getCourceMakerB() : getCourceMakerA());
        getCourceMakerSel()->drawStart(getTergetPt(),getTargetDir());
        getCourceMakerSel()->_dirkaku = _dirkaku;
        
        switch (courceIndex) {
                
            case 0:
                getCourceMakerSel()->dS(615,0);
                setStart(getCourceMakerSel());
                getCourceMakerSel()->dC(250,-20);
                break;
            case 1:
            case 2:
                switch (selStg) {
                    case -1: // howto画面用
                        cPtn123(getCourceMakerSel());
                        break;
                    case 0:
                        cPtn00(getCourceMakerSel());
                        break;
                    case 1:
                        cPtn01(getCourceMakerSel());
                        break;
                    case 2:
                        cPtn02(getCourceMakerSel());
                        break;
                    case 3:
                        cPtn03(getCourceMakerSel());
                        break;
                    case 4:
                        cPtn04(getCourceMakerSel());
                        break;
                    case 5:
                        cPtn05(getCourceMakerSel());
                        break;
                    case 6:
                        cPtn06(getCourceMakerSel());
                        break;
                    case 7:
                        cPtn07(getCourceMakerSel());
                        break;
                    case 8:
                        cPtn08(getCourceMakerSel());
                        break;
                    case 9:
                        cPtn09(getCourceMakerSel());
                        break;
                    case 10:
                        cPtn10(getCourceMakerSel());
                        break;
                    case 11:
                        cPtn11(getCourceMakerSel());
                        break;
                    case 12:
                        cPtn12(getCourceMakerSel());
                        break;
                    case 13:
                        cPtn13(getCourceMakerSel());
                        break;
                    case 14:
                        cPtn14(getCourceMakerSel());
                        break;
                    case 15:
                        cPtn15(getCourceMakerSel());
                        break;
                    case 16:
                        cPtn16(getCourceMakerSel());
                        break;
                    case 17:
                        cPtn17(getCourceMakerSel());
                        break;
                    case 18:
                        cPtn18(getCourceMakerSel());
                        break;
                    case 19:
                        cPtn19(getCourceMakerSel());
                        break;
                    case 20:
                        cPtn20(getCourceMakerSel());
                        break;
                    case 21:
                        cPtn21(getCourceMakerSel());
                        break;
                    case 22:
                        cPtn22(getCourceMakerSel());
                        break;
                    case 23:
                        cPtn23(getCourceMakerSel());
                        break;
                    case 24:
                        cPtn24(getCourceMakerSel());
                        break;
                    case 25:
                        cPtn25(getCourceMakerSel());
                        break;
                    case 26:
                        cPtn26(getCourceMakerSel());
                        break;
                    case 27:
                        cPtn27(getCourceMakerSel());
                        break;
                    case 28:
                        cPtn28(getCourceMakerSel());
                        break;
                    case 29:
                        cPtn29(getCourceMakerSel());
                        break;
                    case 30:
                        cPtn30(getCourceMakerSel());
                        break;
                    case 31:
                        cPtn31(getCourceMakerSel());
                        break;
                    case 32:
                        cPtn32(getCourceMakerSel());
                        break;
                    case 33:
                        cPtn33(getCourceMakerSel());
                        break;
                    case 34:
                        cPtn34(getCourceMakerSel());
                        break;
                    case 35:
                        cPtn35(getCourceMakerSel());
                        break;
                    case 36:
                        cPtn36(getCourceMakerSel());
                        break;
                    case 37:
                        cPtn37(getCourceMakerSel());
                        break;
                    case 38:
                        cPtn38(getCourceMakerSel());
                        break;
                    case 39:
                        cPtn39(getCourceMakerSel());
                        break;
                    case 40:
                        cPtn40(getCourceMakerSel());
                        break;
                    case 41:
                        cPtn41(getCourceMakerSel());
                        break;
                    case 42:
                        cPtn42(getCourceMakerSel());
                        break;
                    case 43:
                        cPtn43(getCourceMakerSel());
                        break;
                    case 44:
                        cPtn44(getCourceMakerSel());
                        break;
                    case 45:
                        cPtn45(getCourceMakerSel());
                        break;
                    case 46:
                        cPtn46(getCourceMakerSel());
                        break;
                    case 47:
                        cPtn47(getCourceMakerSel());
                        break;
                    case 48:
                        cPtn48(getCourceMakerSel());
                        break;
                    case 49:
                        cPtn49(getCourceMakerSel());
                        break;
                    case 50:
                        cPtn50(getCourceMakerSel());
                        break;
                    case 51:
                        cPtn51(getCourceMakerSel());
                        break;
                    case 52:
                        cPtn52(getCourceMakerSel());
                        break;
                    case 53:
                        cPtn53(getCourceMakerSel());
                        break;
                    case 54:
                        cPtn54(getCourceMakerSel());
                        break;
                    case 55:
                        cPtn55(getCourceMakerSel());
                        break;
                    case 56:
                        cPtn56(getCourceMakerSel());
                        break;
                    case 57:
                        cPtn57(getCourceMakerSel());
                        break;
                    case 58:
                        cPtn58(getCourceMakerSel());
                        break;
                    case 59:
                        cPtn59(getCourceMakerSel());
                        break;
                    case 60:
                        cPtn60(getCourceMakerSel());
                        break;
                    case 61:
                        cPtn61(getCourceMakerSel());
                        break;
                    case 62:
                        cPtn62(getCourceMakerSel());
                        break;
                    case 63:
                        cPtn63(getCourceMakerSel());
                        break;
                    case 64:
                        cPtn64(getCourceMakerSel());
                        break;
                    case 65:
                        cPtn65(getCourceMakerSel());
                        break;
                    case 66:
                        cPtn66(getCourceMakerSel());
                        break;
                    case 67:
                        cPtn67(getCourceMakerSel());
                        break;
                    case 68:
                        cPtn68(getCourceMakerSel());
                        break;
                    case 69:
                        cPtn69(getCourceMakerSel());
                        break;
                    case 70:
                        cPtn70(getCourceMakerSel());
                        break;
                    case 71:
                        cPtn71(getCourceMakerSel());
                        break;
                    case 72:
                        cPtn72(getCourceMakerSel());
                        break;
                    case 73:
                        cPtn73(getCourceMakerSel());
                        break;
                    case 74:
                        cPtn74(getCourceMakerSel());
                        break;
                    case 75:
                        cPtn75(getCourceMakerSel());
                        break;
                    case 76:
                        cPtn76(getCourceMakerSel());
                        break;
                    case 77:
                        cPtn77(getCourceMakerSel());
                        break;
                    case 78:
                        cPtn78(getCourceMakerSel());
                        break;
                    case 79:
                        cPtn79(getCourceMakerSel());
                        break;
                    case 80:
                        cPtn80(getCourceMakerSel());
                        break;
                    case 81:
                        cPtn81(getCourceMakerSel());
                        break;
                    case 82:
                        cPtn82(getCourceMakerSel());
                        break;
                    case 83:
                        cPtn83(getCourceMakerSel());
                        break;
                    case 84:
                        cPtn84(getCourceMakerSel());
                        break;
                    case 85:
                        cPtn85(getCourceMakerSel());
                        break;
                    case 86:
                        cPtn86(getCourceMakerSel());
                        break;
                    case 87:
                        cPtn87(getCourceMakerSel());
                        break;
                    case 88:
                        cPtn88(getCourceMakerSel());
                        break;
                    case 89:
                        cPtn89(getCourceMakerSel());
                        break;
                    case 90:
                        cPtn90(getCourceMakerSel());
                        break;
                    case 91:
                        cPtn91(getCourceMakerSel());
                        break;
                    case 92:
                        cPtn92(getCourceMakerSel());
                        break;
                    case 93:
                        cPtn93(getCourceMakerSel());
                        break;
                    case 94:
                        cPtn94(getCourceMakerSel());
                        break;
                    case 95:
                        cPtn95(getCourceMakerSel());
                        break;
                    case 96:
                        cPtn96(getCourceMakerSel());
                        break;
                    case 97:
                        cPtn97(getCourceMakerSel());
                        break;
                    case 98:
                        cPtn98(getCourceMakerSel());
                        break;
                    case 99:
                        cPtn99(getCourceMakerSel());
                        break;
                    case 100:
                        
                        cPtn100(getCourceMakerSel());
                        break;
                    case 101:
                        cPtn101(getCourceMakerSel());
                        break;
                    case 102:
                        cPtn102(getCourceMakerSel());
                        break;
                    case 103:
                        cPtn103(getCourceMakerSel());
                        break;
                    case 104:
                        cPtn104(getCourceMakerSel());
                        break;
                    case 105:
                        cPtn105(getCourceMakerSel());
                        break;
                    case 106:
                        cPtn106(getCourceMakerSel());
                        break;
                    case 107:
                        cPtn107(getCourceMakerSel());
                        break;
                    case 108:
                        cPtn108(getCourceMakerSel());
                        break;
                    case 109:
                        cPtn109(getCourceMakerSel());
                        break;
                    case 110:
                        cPtn110(getCourceMakerSel());
                        break;
                    case 111:
                        cPtn111(getCourceMakerSel());
                        break;
                    case 112:
                        cPtn112(getCourceMakerSel());
                        break;
                    case 113:
                        cPtn113(getCourceMakerSel());
                        break;
                    case 114:
                        cPtn114(getCourceMakerSel());
                        break;
                    case 115:
                        cPtn115(getCourceMakerSel());
                        break;
                    case 116:
                        cPtn116(getCourceMakerSel());
                        break;
                    case 117:
                        cPtn117(getCourceMakerSel());
                        break;
                    case 118:
                        cPtn118(getCourceMakerSel());
                        break;
                    case 119:
                        cPtn119(getCourceMakerSel());
                        break;
                    case 120:
                        cPtn120(getCourceMakerSel());
                        break;
                    case 121:
                        cPtn121(getCourceMakerSel());
                        break;
                    case 122:
                        cPtn122(getCourceMakerSel());
                        break;
                    case 123:
                        cPtn123(getCourceMakerSel());
                        break;
                }
                break;
            case 3:
                getCourceMakerSel()->dS(300,0);
                setGoal(getCourceMakerSel());
                getCourceMakerSel()->dS(1000,0);
                getCourceMakerSel()->dS(100,90);
                break;
            default:
                return;
        }
        getGurd()->setPosition(getStartPt());
        setStartAndTargetFromCource(courceIndex%2 ? getCourceMakerB() : getCourceMakerA());
        getCourceMakerSel()->_madeInd = 0;
        courceIndex ++;
    }
}


// 滑らかな波波
void CourceManager::cPtn00(CourceMaker* _c){
//    setComment("c00",_c);
    auto kaku = 8;
    _c->dC(200, kaku);
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
//    setComment("c01",_c);
    auto kaku = 5;
    _c->dC(200, kaku);
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
//    setComment("c02",_c);
    auto kaku = 2;
    _c->dC(200, kaku);
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
//    setComment("c03",_c);
    auto kaku = -13;
    _c->dC(200, kaku);
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

// 小さなコブのある坂道1
void CourceManager::cPtn04(CourceMaker* _c){
//    setComment("c04",_c);
    auto kaku = -15;
    _c->dC(200, kaku);
    _c->dS(200, kaku);
    for(int i = 0; i<3; i++){
        _c->dS(150, kaku);
        _c->dS(8,90+kaku);
        _c->dS(8,kaku);
        _c->dS(8,-90+kaku);
        _c->dS(150, kaku);
    }
}

// 小さなコブのある道
void CourceManager::cPtn05(CourceMaker* _c){
    auto kaku = -15;
    _c->dC(200, kaku);
    _c->dS(200, kaku);
    if(courceIndex == 1){
    for(int i = 0; i<3; i++){
        _c->dS(150, kaku);
        _c->dS(8,90+kaku);
        _c->dS(8,kaku);
        _c->dS(8,-90+kaku);
        _c->dS(150, kaku);
    }
    }else{
        kaku = 0;
        for(int i = 0; i<3; i++){
            _c->dS(150, kaku);
            _c->dS(8,90+kaku);
            _c->dS(8,kaku);
            _c->dS(8,-90+kaku);
            _c->dS(150, kaku);
        }
    }
    
}

// 凹凸のある急な坂道
void CourceManager::cPtn06(CourceMaker* _c){
//    setComment("c06",_c);
    auto kaku = 0;
    _c->dC(200, kaku);
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

// 凹凸のある急な坂道2
void CourceManager::cPtn07(CourceMaker* _c){
//    setComment("c07",_c);
    auto kaku = 0;
    _c->dC(200, kaku);
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

// 凹凸のある急な坂道3
void CourceManager::cPtn08(CourceMaker* _c){
//    setComment("c08",_c);
    auto kaku = -5;
    _c->dC(200, kaku);
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

// 平地ジャンプ台1
void CourceManager::cPtn09(CourceMaker* _c){
//    setComment("c09",_c);
    auto kaku = 0;
    for(int i = 0; i<3; i++){
        _c->dC(200, kaku);
        _c->dS(300,  kaku);
        _c->dC(30,45 +kaku );
        _c->dS(50, 45 +kaku);
        _c->dS(50, kaku);
        _c->dS(30, 90 +kaku);
        _c->dS(200, kaku);
    }
}

// 平地ジャンプ台2
void CourceManager::cPtn10(CourceMaker* _c){
//    setComment("c10",_c);
    auto kaku = 0;
    for(int i = 0; i<3; i++){
        _c->dC(200, kaku);
        _c->dS(300,  kaku);
        _c->dC(80,45 +kaku );
        _c->dS(50, 45 +kaku);
        _c->dS(80, -90 + kaku);
        _c->dS(90, kaku);
        _c->dS(90, 90 + kaku);
        _c->dS(200, kaku);
    }
}

// 平地ジャンプ台3
void CourceManager::cPtn11(CourceMaker* _c){
//    setComment("c11",_c);
    auto kaku = 0;
    _c->dC(200, kaku);
    for(int i = 0; i<3; i++){
        _c->dC(100, -65 + kaku);
        _c->dC(200, kaku);
        _c->dS(50,  kaku);
        _c->dC(30,45 +kaku );
        _c->dS(50, 45 +kaku);
        _c->dS(50, kaku);
        _c->dS(30, 90 +kaku);
        _c->dS(30, kaku);
    }
}

// 平地ジャンプ台4
void CourceManager::cPtn12(CourceMaker* _c){
    //    setComment("c12",_c);
    auto kaku = -15;
    for(int i = 0; i<3; i++){
        _c->dC(200, kaku);
        _c->dS(300, kaku);
        _c->dC(30,45 + kaku);
        _c->dS(50, 45 + kaku);
        _c->dS(60, -90);
        _c->dS(90, 0);
        _c->dS(90, 90);
        _c->dS(200, kaku);
    }
}

// 平地ジャンプ台5
void CourceManager::cPtn13(CourceMaker* _c){
    //    setComment("c13",_c);
    auto kaku = 0;
//    _c->dC(200, kaku);
    for(int i = 0; i<3; i++){
        _c->dC(100, -65 + kaku);
        _c->dC(200, kaku);
        _c->dS(50,  kaku);
        _c->dC(30,45 +kaku );
        _c->dS(50, 45 +kaku);
        _c->dS(50, kaku);
        _c->dS(30, 90 +kaku);
        _c->dS(30, kaku);
    }
}

// 自然な激しい坂道1
void CourceManager::cPtn14(CourceMaker* _c){
//    setComment("c14",_c);
    auto kaku = 0;
    _c->dC(200, kaku);
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

// 自然な激しい坂道2
void CourceManager::cPtn15(CourceMaker* _c){
//    setComment("c15",_c);
    auto kaku = 0;
    _c->dC(200, kaku);
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

// バンプトラック1
void CourceManager::cPtn16(CourceMaker* _c){
//    setComment("c16",_c);
    auto kaku = 0;
    auto kaku1 = -45;
    auto kaku2 = 45;
    
    for(int i=0; i<10; i++){
        _c->dC(120, kaku1 + kaku);
        _c->dS(20, kaku1 + kaku);
        _c->dC(80, kaku);
        _c->dC(120, kaku2 + kaku);
    }
}

// バンプトラック2
void CourceManager::cPtn17(CourceMaker* _c){
//    setComment("c17",_c);
    auto kaku = 0;
    auto kaku1 = -45;
    auto kaku2 = 45;
    
    for(int i=0; i<10; i++){
        _c->dC(100, kaku1 + kaku);
        _c->dS(20, kaku1 + kaku);
        _c->dC(60, kaku);
        _c->dC(100, kaku2 + kaku);
    }
}

// 階段下り1
void CourceManager::cPtn18(CourceMaker* _c){
//    setComment("c18",_c);
    auto kaku = 0;
    auto kaku1 = -90;
    auto kaku2 = 45;
    _c->dC(100, kaku);
    for(int i=0; i<10; i++){
        _c->dS(100, kaku);
        _c->dS(40, kaku1 + kaku);
    }
}

// 階段下り2
void CourceManager::cPtn19(CourceMaker* _c){
//    setComment("c19",_c);
    auto kaku = 0;
    auto kaku1 = -90;
    auto kaku2 = 45;
    _c->dC(100, kaku);
    for(int i=0; i<10; i++){
        _c->dS(100, kaku);
        _c->dS(10, kaku2 + kaku);
        _c->dS(80, kaku1 + kaku);
    }
}

// 階段下り3
void CourceManager::cPtn20(CourceMaker* _c){
//    setComment("c20",_c);
    auto kaku = 0;
    auto kaku1 = -50;
    auto kaku2 = 45;
    _c->dC(100, kaku);
    for(int i=0; i<4; i++){
        _c->dS(100, kaku);
        _c->dS(30, kaku1 + kaku);
        _c->dS(0, -90 + kaku);
        _c->dC(100, kaku2 + kaku);
    }
}

// 波波と凸
void CourceManager::cPtn21(CourceMaker* _c){
    setComment("c21",_c);
    auto kaku = -8;
    _c->dC(200, kaku);
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
    
    bufKaku = -27 + kaku;
    _c->dS(100,bufKaku);
    _c->dS(0,90 + bufKaku);
    _c->dC(10,-90 + bufKaku);
    _c->dS(0, bufKaku);
    
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
    _c->dC(200, kaku);
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
    auto kaku = -6;
    _c->dC(200, kaku);
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
    auto kaku = -7;
    _c->dC(200, kaku);
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
    auto kaku = -6;
    _c->dC(200, kaku);
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
    _c->dC(200, kaku);
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
    auto kaku = -7;
    _c->dC(200, kaku);
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
    _c->dC(200, kaku);
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
    _c->dC(200, kaku);
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

// バンプトラック3
void CourceManager::cPtn30(CourceMaker* _c){
    setComment("c30",_c);
    auto kaku = 0;
    auto kaku1 = -45;
    auto kaku2 = 45;
    
    for(int i=0; i<10; i++){
        _c->dC(100, kaku1 + kaku);
        _c->dS(20, kaku1 + kaku);
        _c->dC(60, kaku);
        _c->dC(100, kaku2 + kaku);
    }
    
}

// 細かい段差
void CourceManager::cPtn31(CourceMaker* _c){
    setComment("c31",_c);
    auto kaku = -14;
    _c->dC(200, kaku);
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
    _c->dC(200, kaku);
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
    _c->dC(200, kaku);
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
    _c->dC(200, kaku);
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
    _c->dC(200, kaku);
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
    _c->dC(200, kaku);
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
    _c->dC(200, kaku);
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
    _c->dC(200, kaku);
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
    _c->dC(200, kaku);
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
    _c->dC(200, kaku);
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
    _c->dC(200, kaku);
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
    _c->dC(200, kaku);
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
    _c->dC(200, kaku);
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
    _c->dC(200, kaku);
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
    _c->dC(200, kaku);
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
    _c->dC(200, kaku);
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
    _c->dC(200, kaku);
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
    _c->dC(200, kaku);
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
    _c->dC(200, kaku);
    
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
    _c->dC(200, kaku);
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
    _c->dC(200, kaku);
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
    _c->dC(200, kaku);
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
    _c->dC(200, kaku);
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
    _c->dC(200, kaku);
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
    _c->dC(200, kaku);
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
    _c->dC(200,0);
    _c->dS(100,0);
    for(int i=0;i<3;i++){
        _c->dS(100,-90);
        _c->dS(80,0);
        _c->dS(100,90);
        _c->dS(70,0);
    }
    _c->dS(30,kaku);
}

// スーパー幅跳び
void CourceManager::cPtn61(CourceMaker* _c){
    setComment("c61",_c);
    auto kaku = _c->_dirkaku;
    _c->dC(200, kaku);
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
    _c->dC(200, kaku);
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
    _c->dC(300,-45);
    _c->dS(400,-45);
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
    _c->dC(200, kaku);
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

// howTo画面
void CourceManager::cPtn123(CourceMaker* _c){
    auto kaku = -1;
    _c->dC(300,-1);
    _c->dC(100,30);
    _c->dC(100,0);
    _c->dS(500,0);
    _c->dC(100,-30);
    _c->dS(100,-30);
    _c->dC(200,0);
}
/** パラメータサンプル
 setCourceMakerA(CourceMaker::create());
 getCourceMakerA();
 setCourceMakerB(CourceMaker::create());
 getCourceMakerB();
 */
