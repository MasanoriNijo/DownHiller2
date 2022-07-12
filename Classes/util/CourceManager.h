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
    CC_SYNTHESIZE_RETAIN(Flg*,_flg,Flg);
    CC_SYNTHESIZE_RETAIN(StagePrm*,_stagePrm,StagePrm);
    CC_SYNTHESIZE_RETAIN(Node*,_gurd,Gurd);
    CC_SYNTHESIZE_RETAIN(PhysicsBody*,_gurdBody,GurdBody);
    CC_SYNTHESIZE_RETAIN(ColorChanger*,_colorChanger,ColorChanger);
    CC_SYNTHESIZE(Vec2,_strPt,StartPt);
    CC_SYNTHESIZE(Vec2,_strDir,StartDir);
    CC_SYNTHESIZE(Vec2,_trgPt,TergetPt);
    CC_SYNTHESIZE(Vec2,_trgDir,TargetDir);
    
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
};

#endif
