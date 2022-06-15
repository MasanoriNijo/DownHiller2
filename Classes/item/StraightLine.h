#ifndef __STRAIGHTLINE_H__
#define __STRAIGHTLINE_H__

#include "item/base/Sprite2.h"
#include "cmath"
#include "cocos2d.h"
USING_NS_CC;

class StraightLine: public Sprite2 {
protected:
    StraightLine();
    virtual ~StraightLine();
    
public:
    static StraightLine* create();
    bool init() override;
    CC_SYNTHESIZE_RETAIN(Sprite*,_fDot,FDot);
    CC_SYNTHESIZE_RETAIN(Sprite*,_rDot,RDot);
    CC_SYNTHESIZE(Vec2,_wrkPt,WorkPt);
    CC_SYNTHESIZE(Vec2,_wrkDir,WorkDir);
    CC_SYNTHESIZE(Vec2,_trgPt,TergetPt);
    CC_SYNTHESIZE(Vec2,_trgDir,TargetDir);
    void update(float dt) override;
    void onEnterTransitionDidFinish() override;
    
    float _length;
    void drawLine(Vec2 pt1, Vec2 pt2);
};

#endif
