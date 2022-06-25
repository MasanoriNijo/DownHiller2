#ifndef __COURCEMAKER_H__
#define __COURCEMAKER_H__

#include "util/Calclater.h"
#include "cocos2d.h"
USING_NS_CC;

class CourceMaker: public Node {
protected:
    CourceMaker();
    virtual ~CourceMaker();
    
public:
    CREATE_FUNC(CourceMaker);
//    static CourceMaker* create();
    bool init() override;
    CC_SYNTHESIZE_RETAIN(Calclater*,_calc,Calc);
    CC_SYNTHESIZE_RETAIN(SpriteBatchNode*,_dot,Dot);
    CC_SYNTHESIZE_RETAIN(SpriteBatchNode*,_straight,Straight);
    CC_SYNTHESIZE_RETAIN(SpriteBatchNode*,_mark,Mark);
    CC_SYNTHESIZE_RETAIN(SpriteBatchNode*,_curveA,CurveA);
    CC_SYNTHESIZE_RETAIN(SpriteBatchNode*,_curveB,CurveB);
    CC_SYNTHESIZE_RETAIN(SpriteBatchNode*,_curveC,CurveC);
    CC_SYNTHESIZE_RETAIN(SpriteBatchNode*,_curveD,CurveD);
    CC_SYNTHESIZE_RETAIN(SpriteBatchNode*,_curveE,CurveE);
    CC_SYNTHESIZE_RETAIN(SpriteBatchNode*,_curveF,CurveF);
    CC_SYNTHESIZE_RETAIN(PhysicsBody*,_courceBody,CourceBody);
    CC_SYNTHESIZE(Vector<Sprite*>,_member,Member);
//    CC_SYNTHESIZE(Vector<Vec2>,_polygonPts,PolygonPts);
    CC_SYNTHESIZE(Vec2,_wrkPt,WorkPt);
    CC_SYNTHESIZE(Vec2,_wrkDir,WorkDir);
    CC_SYNTHESIZE(Vec2,_trgPt,TergetPt);
    CC_SYNTHESIZE(Vec2,_trgDir,TargetDir);
    void update(float dt) override;
    void onEnterTransitionDidFinish() override;
    
    // 元の直線の長さ
    float _length;
    
    // 円弧を描写する際のピッチ
    float _drawPitch = 3;
    
    // markを追加する場合のピッチ
    bool markSetflg = true;
    float _markPitch = 80;
    float _remindMarkPitch = 0;
    
    // アクション関連
    void drawStart(Vec2 pt_, Vec2 dir_);
    // 現ポイントから、指定の方向に直線を描く。
    void drawByStraight(Vec2 dpt_);
    // 現ポイントの方向から滑らかに、前方にdx,横にdy進んだポイントにつながる曲線を描く。
    void drawBySmoothCurve(Vec2 dirPt_);
    // 現ポイントから、指定のポイントが、終点になるように、指定した角度左（−90 - 90度）右円弧を描く。
    void drawByCurve(Vec2 dpt_,float kaku);    
    // 現ポイントから、指定した角度3（0 - 360度）で直線を描く。
    void drawByStraight(float length, float kaku);
    
    void drawTo(Vec2 pt_, Vec2 dir_);
    // 現状の設定値で描く
    void calcCurve(float r_);
    // start pt1,dir1 から goal pt2,dir2 に繋がる半径 r_ のカーブを描く
    void calcCurve(Vec2 pt1,Vec2 dir1, Vec2 pt2, Vec2 dir2 ,float r_);
    
    // 描写関連
    void addStraightLine(Vec2 pt1_, Vec2 pt2_);
    void addDot(Vec2 pt_);
    void addCurveA(Vec2 pt_, Vec2 dir_);
    void addMarkStraight(Vec2 pt_,Vec2 dir_);
    void addMarkCurve(Vec2 curveCenterPt,Vec2 fstPt,float rad);
    
    // 物理関連
    // physicsbody用
    void addPolygonPts(Vec2 pt_);
    // PhysicsBodyのポリゴン生成用
    Vec2 _polygonPts[2000];
    int _polygonPtCnt = 0;
    float _polygonPitch = 10;
    
    void madePhysiceBody();
    
    void madePhysiceBody(Node* field);
    
};

#endif
