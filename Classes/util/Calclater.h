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
    CREATE_FUNC(Calclater);
//    static Calclater* create();
    bool init();
    void update(float dt);
    void onEnterTransitionDidFinish();
    
    // 反時計のRadian0-2piをSprite用の角度に変換する。時計回り0-360°
    float chgKaku(float degree);
    float chgKaku(Vec2 pt);
        
    // 時計周りの角度0-360度をVec2用のRadian0-2Πに変換する。反時計回り　Vec2用
    float chgRad(float kaku);
    float chgRad(Vec2 pt);
    
    // pt11→pt2のベクトルの反時計のRadian0-2piで出力
    float nomlRad(Vec2 pt1, Vec2 pt2);
    
    // pt方向の標準角度をベクトルの反時計のRadian0-2piで出力
    float nomlRad(Vec2 pt);
    
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
    
    // // A→Bまで回転するための角度、leftFlg 左回り
    float diffRadA2B(Vec2 A, Vec2 B, bool leftFlg);
    
    // 親が所属する座標系でのポジションを算出
    Vec2 getParentNodePosition(Node* nd);
    
    // 変換系
    // 指定したラジアン分回転する。反時計回り
    Vec2 rotByRad(Vec2 pt,float rad);
    // 指定したradPtのラジアン分回転する。反時計回り
    Vec2 rotByRad(Vec2 pt,Vec2 radPt);
    // 指定した角度分回転する。時計回り
    Vec2 rotByKaku(Vec2 pt,float kaku);
    // 同じ方向で指定した長さに変換する。
    Vec2 chgLength(Vec2 pt,float length);

    // 同じ方向の標準ベクトルを算出
    Vec2 nomalizeVec2(Vec2 pt);
    
    // nodeの標準方向ベクトルを取得
    Vec2 getNodeDict(Node* nd);
    
    // 対象物が進行方向の左側にあるのか確認する。
    bool chkLeft(Vec2 pt, Vec2 dst,Vec2 chkPt);
    
    // 複雑な座標の移動,変換系
    // destPtに追従する。
    Vec2 chasePt(Vec2 destPt,Vec2& chasePt,float velo,float dt);
    Vec2 chasePt(Vec2 destPt,Vec2& chasePt,float length);
    
    // ptX をx軸と見立てた時のptの位置を計算
    Vec2 cordinaneX(Vec2 ptX, Vec2 pt);
    
    // 2線分の交点を返す。
    Vec2 getCrossPointLineA2B(Vec2 a1, Vec2 a2,Vec2 b1, Vec2 b2);
    
    // 指定の線分に対して対照のポイントを変える。
    Vec2 getMirrorPointLineA(Vec2 a1, Vec2 a2,Vec2 pt);
    
};

#endif
