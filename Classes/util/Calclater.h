#ifndef __CALCLATER_H__
#define __CALCLATER_H__

#include "util/Const.h"
#include "cocos2d.h"
USING_NS_CC;

class Calclater: public Ref {
protected:
    Calclater();
    virtual ~Calclater();
    
public:
    static Calclater* create();
    bool init();
    void update(float dt);
    void onEnterTransitionDidFinish();
    
    // 反時計のRadian0-2piをSprite用の角度に変換する。時計回り0-360°
    float chgKaku(float degree);
        
    // 時計周りの角度0-360度をVec2用のRadian0-2Πに変換する。反時計回り　Vec2用
    float chgRad(float kaku);
    
    // pt11→pt2のベクトルの反時計のRadian0-2piで出力
    float nomlRad(Vec2 pt1, Vec2 pt2);
    
    // 角度を0-360の間にする。
    float nomlKaku(float kaku);
    
    // pt11→pt2のベクトルの反時計のRadian0-2piをSprite用の角度に変換する。時計回り0-360°
    float nomlKaku(Vec2 pt1, Vec2 pt2);
    
    // radianを0-2piの間にする。
    float nomlRad(float rad);
    
    // 指定の角度の間にあるかどうか？
    bool betweenKaku(float x, float min_, float max_);
    
    // 指定のradianの間にあるかどうか？
    bool betweenRad(float x, float min_, float max_);
    
    // 内積を算出
    float getDot(Vec2 A, Vec2 B);
    
    // 親が所属する座標系でのポジションを算出
    Vec2 getParentNodePosition(Node* nd);
    
};

#endif

