#ifndef __LINEMAKER_H__
#define __LINEMAKER_H__

#include "util/Const.h"
#include "cocos2d.h"
USING_NS_CC;

class LineMaker: public Ref {
protected:
    LineMaker();
    virtual ~LineMaker();
    
public:
    static LineMaker* create();
    bool init() override;
    CC_SYNTHESIZE_RETAIN(Sprite2*,_pt,Pt);
    CC_SYNTHESIZE_RETAIN(CalcLater*,_calc,Calc);
    void update(float dt) override;
    void onEnterTransitionDidFinish() override;
    
    Vec2 _wrkPt; //現在の先頭のポイント
    Vec2 SetPt2; //前回セットしたポイント2
    
    Vec2 trgPt1; //ターゲットポイント；
    Vec2 trgPt2; //ターゲットポイント；
    
    Vec2 _linePts[200]; //シェープ作成用のドット。
    int _linePtCnt = 0;
    // 可視化したライン
    Vector<Sprite*> _dotSprites;
    int _dotSpriteCnt = 0;
    
    void addLinePts(Vec2 pt_);
    
    
    // 図形を描く
    void madeCurve(int w, int h, float endRad);
    Vec2 moveSin(float r, float w, float rad1, int dl, float endrad);
};

#endif
