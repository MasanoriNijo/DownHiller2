#ifndef __LINEMAKER_H__
#define __LINEMAKER_H__

#include "util/Const.h"
#include "util/Calclater.h"
#include "item/base/Sprite2.h"
#include "cocos2d.h"
USING_NS_CC;

class LineMaker: public Ref {
protected:
    LineMaker();
    virtual ~LineMaker();
    
public:
    static LineMaker* create();
    bool init();
    CC_SYNTHESIZE_RETAIN(Sprite2*,_pt,Pt);
    CC_SYNTHESIZE_RETAIN(Calclater*,_calc,Calc);
    CC_SYNTHESIZE_RETAIN(Node*,_field,Field);
    CC_SYNTHESIZE(Vec2,_wrkPt,WorkPt);
    CC_SYNTHESIZE(Vec2,_wrkDir,WorkDir);
    CC_SYNTHESIZE(Vec2,_trgPt,TergetPt);
    CC_SYNTHESIZE(Vec2,_trgDir,TargetDir);
    void update(float dt);
    void onEnterTransitionDidFinish();
    
    void madeCircleLine();
    Vec2 ptA;
    Vec2 ptA_wrk;
    Vec2 ptA_trg;
    
    
    // PhysicsBodyのポリゴン生成用
    Vec2 _linePts[2000];
    int _linePtCnt = 0;
    float porigonPich = 20;
    
    // 可視化したラインを保持
    Vector<Sprite*> _dotSprites;
    int _dotSpriteCnt = 0;
    
    void addLinePts(Vec2 pt_);
    

};

#endif
