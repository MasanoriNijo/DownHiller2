#ifndef __COURCEMANAGER_H__
#define __COURCEMANAGER_H__

#include "util/CourceMaker.h"
#include "util/StagePrm.h"
#include "util/ColorChanger.h"
#include "item/Flg.h"
#include "cocos2d.h"
USING_NS_CC;

class CourceManager: public Ref {
protected:
    CourceManager();
    virtual ~CourceManager();

private:
    void _setStagePrm();
    
public:
    CREATE_FUNC(CourceManager);
    bool init();
    CC_SYNTHESIZE_RETAIN(CourceMaker*,_courceMakerA,CourceMakerA);
    CC_SYNTHESIZE_RETAIN(CourceMaker*,_courceMakerB,CourceMakerB);
    CC_SYNTHESIZE_RETAIN(CourceMaker*,_courceMakerSel,CourceMakerSel);
    CC_SYNTHESIZE_RETAIN(Flg*,_startFlg,StartFlg);
    CC_SYNTHESIZE_RETAIN(Flg*,_goalFlg,GoalFlg);
    CC_SYNTHESIZE_RETAIN(StagePrm*,_stagePrm,StagePrm);
    CC_SYNTHESIZE_RETAIN(Node*,_gurd,Gurd);
    CC_SYNTHESIZE_RETAIN(PhysicsBody*,_gurdBody,GurdBody);
    CC_SYNTHESIZE_RETAIN(ColorChanger*,_colorChanger,ColorChanger);
    CC_SYNTHESIZE(Vec2,_strPt,StartPt);
    CC_SYNTHESIZE(Vec2,_strDir,StartDir);
    CC_SYNTHESIZE(Vec2,_trgPt,TergetPt);
    CC_SYNTHESIZE(Vec2,_trgDir,TargetDir);
    float _dirkaku = 0;// 現在のdirPtの角度
    
    void update(float dt);
    void onEnterTransitionDidFinish();
    void checkAndMadeCource(Vec2 chPt);
    void setStartAndTargetFromCource(CourceMaker* _cmaker);
    bool togle = false;
    int selStg = 0;
    int courceIndex = 0;
    Vec2 FIRST_COURCE_BASE_POINT = Vec2(-530,-12);
    
    void setForTitle();
    void madeCourcePtnForTitle(CourceMaker* _cmaker,int ind);
    
    void setStart(CourceMaker* _c);
    bool _isSetStart = false;
    void setGoal(CourceMaker* _c);
    bool _isSetGoal = false;
    
    // debug用
    bool _isDebugComment = true;
    void setComment(std::string st, CourceMaker* _c);
    
    std::string genComment(int courceNo);
    int genTimeLimit(int courceNo);
    
    void cPtnStart(CourceMaker* _c);
    void cPtnGoal(CourceMaker* _c);
    
    void madeCourcePtn0(CourceMaker* _cmaker,int ind);
    void madeCourcePtn1(CourceMaker* _cmaker,int ind);
    void madeCourcePtn2(CourceMaker* _cmaker,int ind);
    void madeCourcePtn3(CourceMaker* _cmaker,int ind);
    void madeCourcePtn4(CourceMaker* _cmaker,int ind);
    void madeCourcePtn5(CourceMaker* _cmaker,int ind);
    void madeCourcePtn6(CourceMaker* _cmaker,int ind);
    void madeCourcePtn7(CourceMaker* _cmaker,int ind);
    void madeCourcePtn8(CourceMaker* _cmaker,int ind);
    void madeCourcePtn9(CourceMaker* _cmaker,int ind);
    void madeCourcePtn10(CourceMaker* _cmaker,int ind);
    void madeCourcePtn11(CourceMaker* _cmaker,int ind);
    void madeCourcePtn12(CourceMaker* _cmaker,int ind);
    void madeCourcePtn13(CourceMaker* _cmaker,int ind);
    void madeCourcePtn14(CourceMaker* _cmaker,int ind);
    void madeCourcePtn15(CourceMaker* _cmaker,int ind);
    void madeCourcePtn16(CourceMaker* _cmaker,int ind);
    void madeCourcePtn17(CourceMaker* _cmaker,int ind);
    void madeCourcePtn18(CourceMaker* _cmaker,int ind);
    void madeCourcePtn19(CourceMaker* _cmaker,int ind);
    void madeCourcePtn20(CourceMaker* _cmaker,int ind);
    void madeCourcePtn21(CourceMaker* _cmaker,int ind);
    
    
    void checkAndMadeCourceForTraining(Vec2 chPt);
    void cPtn00(CourceMaker* _c);
    void cPtn01(CourceMaker* _c);
    void cPtn02(CourceMaker* _c);
    void cPtn03(CourceMaker* _c);
    void cPtn04(CourceMaker* _c);
    void cPtn05(CourceMaker* _c);
    void cPtn06(CourceMaker* _c);
    void cPtn07(CourceMaker* _c);
    void cPtn08(CourceMaker* _c);
    void cPtn09(CourceMaker* _c);
    void cPtn10(CourceMaker* _c);
    void cPtn11(CourceMaker* _c);
    void cPtn12(CourceMaker* _c);
    void cPtn13(CourceMaker* _c);
    void cPtn14(CourceMaker* _c);
    void cPtn15(CourceMaker* _c);
    void cPtn16(CourceMaker* _c);
    void cPtn17(CourceMaker* _c);
    void cPtn18(CourceMaker* _c);
    void cPtn19(CourceMaker* _c);
    void cPtn20(CourceMaker* _c);
    void cPtn21(CourceMaker* _c);
    void cPtn22(CourceMaker* _c);
    void cPtn23(CourceMaker* _c);
    void cPtn24(CourceMaker* _c);
    void cPtn25(CourceMaker* _c);
    void cPtn26(CourceMaker* _c);
    void cPtn27(CourceMaker* _c);
    void cPtn28(CourceMaker* _c);
    void cPtn29(CourceMaker* _c);
    void cPtn30(CourceMaker* _c);
    void cPtn31(CourceMaker* _c);
    void cPtn32(CourceMaker* _c);
    void cPtn33(CourceMaker* _c);
    void cPtn34(CourceMaker* _c);
    void cPtn35(CourceMaker* _c);
    void cPtn36(CourceMaker* _c);
    void cPtn37(CourceMaker* _c);
    void cPtn38(CourceMaker* _c);
    void cPtn39(CourceMaker* _c);
    void cPtn40(CourceMaker* _c);
    void cPtn41(CourceMaker* _c);
    void cPtn42(CourceMaker* _c);
    void cPtn43(CourceMaker* _c);
    void cPtn44(CourceMaker* _c);
    void cPtn45(CourceMaker* _c);
    void cPtn46(CourceMaker* _c);
    void cPtn47(CourceMaker* _c);
    void cPtn48(CourceMaker* _c);
    void cPtn49(CourceMaker* _c);
    void cPtn50(CourceMaker* _c);
    void cPtn51(CourceMaker* _c);
    void cPtn52(CourceMaker* _c);
    void cPtn53(CourceMaker* _c);
    void cPtn54(CourceMaker* _c);
    void cPtn55(CourceMaker* _c);
    void cPtn56(CourceMaker* _c);
    void cPtn57(CourceMaker* _c);
    void cPtn58(CourceMaker* _c);
    void cPtn59(CourceMaker* _c);
    void cPtn60(CourceMaker* _c);
    void cPtn61(CourceMaker* _c);
    void cPtn62(CourceMaker* _c);
    void cPtn63(CourceMaker* _c);
    void cPtn64(CourceMaker* _c);
    void cPtn65(CourceMaker* _c);
    void cPtn66(CourceMaker* _c);
    void cPtn67(CourceMaker* _c);
    void cPtn68(CourceMaker* _c);
    void cPtn69(CourceMaker* _c);
    void cPtn70(CourceMaker* _c);
    void cPtn71(CourceMaker* _c);
    void cPtn72(CourceMaker* _c);
    void cPtn73(CourceMaker* _c);
    void cPtn74(CourceMaker* _c);
    void cPtn75(CourceMaker* _c);
    void cPtn76(CourceMaker* _c);
    void cPtn77(CourceMaker* _c);
    void cPtn78(CourceMaker* _c);
    void cPtn79(CourceMaker* _c);
    void cPtn80(CourceMaker* _c);
    void cPtn81(CourceMaker* _c);
    void cPtn82(CourceMaker* _c);
    void cPtn83(CourceMaker* _c);
    void cPtn84(CourceMaker* _c);
    void cPtn85(CourceMaker* _c);
    void cPtn86(CourceMaker* _c);
    void cPtn87(CourceMaker* _c);
    void cPtn88(CourceMaker* _c);
    void cPtn89(CourceMaker* _c);
    void cPtn90(CourceMaker* _c);
    void cPtn91(CourceMaker* _c);
    void cPtn92(CourceMaker* _c);
    void cPtn93(CourceMaker* _c);
    void cPtn94(CourceMaker* _c);
    void cPtn95(CourceMaker* _c);
    void cPtn96(CourceMaker* _c);
    void cPtn97(CourceMaker* _c);
    void cPtn98(CourceMaker* _c);
    void cPtn99(CourceMaker* _c);
    void cPtn100(CourceMaker* _c);
    void cPtn101(CourceMaker* _c);
    void cPtn102(CourceMaker* _c);
    void cPtn103(CourceMaker* _c);
    void cPtn104(CourceMaker* _c);
    void cPtn105(CourceMaker* _c);
    void cPtn106(CourceMaker* _c);
    void cPtn107(CourceMaker* _c);
    void cPtn108(CourceMaker* _c);
    void cPtn109(CourceMaker* _c);
    void cPtn110(CourceMaker* _c);
    void cPtn111(CourceMaker* _c);
    void cPtn112(CourceMaker* _c);
    void cPtn113(CourceMaker* _c);
    void cPtn114(CourceMaker* _c);
    void cPtn115(CourceMaker* _c);
    void cPtn116(CourceMaker* _c);
    void cPtn117(CourceMaker* _c);
    void cPtn118(CourceMaker* _c);
    void cPtn119(CourceMaker* _c);
    void cPtn120(CourceMaker* _c);
    void cPtn121(CourceMaker* _c);
    void cPtn122(CourceMaker* _c);
    void cPtn123(CourceMaker* _c);
    
};

#endif
