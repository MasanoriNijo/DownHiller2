#ifndef __CURVELINE_H__
#define __CURVELINE_H__

#include "item/base/Sprite2.h"
#include "item/StraightLine.h"
#include "cmath"
#include "cocos2d.h"
USING_NS_CC;

class CurveLine: public Sprite2 {
protected:
    CurveLine();
    virtual ~CurveLine();
    
public:
    static CurveLine* create();
    bool init() override;
    
    CC_SYNTHESIZE_RETAIN(StraightLine*,_straightA,StraightA);
    CC_SYNTHESIZE_RETAIN(StraightLine*,_straightB,StraightB);
    CC_SYNTHESIZE_RETAIN(SpriteBatchNode*,_dot,Dot);
    CC_SYNTHESIZE_RETAIN(Sprite*,_curveA,CurveA);
    CC_SYNTHESIZE_RETAIN(Sprite*,_curveB,CurveB);
    CC_SYNTHESIZE_RETAIN(Sprite*,_curveC,CurveC);
    CC_SYNTHESIZE_RETAIN(Sprite*,_curveD,CurveD);
    CC_SYNTHESIZE_RETAIN(Sprite*,_curveE,CurveE);
    CC_SYNTHESIZE_RETAIN(Sprite*,_curveF,CurveF);
    CC_SYNTHESIZE(Vec2,_wrkPt,WorkPt);
    CC_SYNTHESIZE(Vec2,_wrkDir,WorkDir);
    CC_SYNTHESIZE(Vec2,_trgPt,TergetPt);
    CC_SYNTHESIZE(Vec2,_trgDir,TargetDir);
    void update(float dt) override;
    void onEnterTransitionDidFinish() override;
    
    Vector<Sprite*> _pool;
    float _length;
    // start pt1,dir1 から goal pt2,dir2 に繋がる半径 r_ のカーブを描く
    void drawCurve(Vec2 pt1,Vec2 dir1, Vec2 pt2, Vec2 dir2 ,float r_);
    
};

#endif
