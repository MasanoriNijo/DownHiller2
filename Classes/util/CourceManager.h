#ifndef __COURCEMANAGER_H__
#define __COURCEMANAGER_H__

#include "util/CourceMaker.h"
#include "item/Flg.h"
#include "cocos2d.h"
USING_NS_CC;

class CourceManager: public Ref {
protected:
    CourceManager();
    virtual ~CourceManager();
    
public:
    CREATE_FUNC(CourceManager);
    bool init();
    CC_SYNTHESIZE_RETAIN(CourceMaker*,_courceMakerA,CourceMakerA);
    CC_SYNTHESIZE_RETAIN(CourceMaker*,_courceMakerB,CourceMakerB);
    CC_SYNTHESIZE_RETAIN(Flg*,_flg,Flg);
    CC_SYNTHESIZE(Vec2,_strPt,StartPt);
    CC_SYNTHESIZE(Vec2,_strDir,StartDir);
    CC_SYNTHESIZE(Vec2,_trgPt,TergetPt);
    CC_SYNTHESIZE(Vec2,_trgDir,TargetDir);
    void update(float dt);
    void onEnterTransitionDidFinish();
    void checkAndMadeCource(Vec2 chPt);
    void setStartAndTargetFromCource(CourceMaker* _cmaker);
    bool togle = false;
    int courceIndex = 0;
    Vec2 FIRST_COURCE_BASE_POINT = Vec2(-30,-12);
    
    void madeCourcePtn1(CourceMaker* _cmaker,int ind);
    void madeCourcePtn2(CourceMaker* _cmaker,int ind);
    void madeCourcePtn3(CourceMaker* _cmaker,int ind);
    void madeCourcePtn4(CourceMaker* _cmaker,int ind);
};

#endif
