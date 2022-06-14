#ifndef __BIKE_H__
#define __BIKE_H__

#include "item/base/Sprite2.h"
#include "cmath"
#include "cocos2d.h"
USING_NS_CC;

class Bike: public Sprite2 {
protected:
    Bike();
    virtual ~Bike();
    
    const int BikeCatg = 1 << 0;
    const int enemyCatg = 1 << 1;
    const int courceCatg = 1 << 2;
    const int itemCatg = 1 << 3;
    const int boundCatg = 1 << 4;
    const int Bike_FRAME_COUNT = 2;
    
private:
    // ホイールに物理情報を付与する。
    void _addPhysicsToWheel(Sprite* _wheel);
    // 前後輪とBikeの位置を同調する。
    void _positionSyncToWheel();
    
    // タッチイベントをセットする
    void _setTouchEvent();
    
    //　操作の状態で、アクションを決める。
    void _judeAction(float dt);
    
public:
    static Bike* create();
    bool init() override;
    CC_SYNTHESIZE_RETAIN(Sprite*,_rider,Rider);
    CC_SYNTHESIZE_RETAIN(Sprite*,_fWheel,Fwheel);
    CC_SYNTHESIZE_RETAIN(Sprite*,_rWheel,Rwheel);
    CC_SYNTHESIZE_RETAIN(Sprite*,_sceneChasePt,SceneChasePt);
    CC_SYNTHESIZE(PhysicsJointDistance*,_frJoint,FRJoint);
    void update(float dt) override;
    void onEnterTransitionDidFinish() override;
    
    // 前後車輪を親シーンに設置した後、親シーンから呼ぶ
    void SetJoint();
    
    // 画面の操作の情報を受け取る。
    Vec2 touchPt1;// ひとつ前のタッチ位置
    Vec2 touchPt2;// 最新のタッチ位置
    void touchOn(Vec2 pt);
    void swaip(Vec2 pt);
    void touchOff(Vec2 pt);
    
    // bikeの画像中心
    Vec2 bikeCenterPt;
    
    // bikeのアンカーポイント　後輪の中心軸がアンカーポイントになる様に設定する。
    Vec2 bikeAnchorPt;
    
    // wheelBase
    float wheelBase = 32;
    
    // riderの重心ポイント（画面操作により、移動し、移動の仕方によりジャンプ、ウイリーなどのアクションをさせる。）
    Vec2 weightPt;
    // 重心ポイントを追従するポイント
    Vec2 chasePt;
    
    // riderアクション weightPtの位置により、画像差し替える。
    // riderのフレームサイズ
    Size frameSize;
    float riderActionSpan = 5;
    void riderImageAction();
    
    // bikeの制御不能をある程度制限する。
    void _bikeBehaviorControl();
    
    enum class BikeState {READY, NOML, BREAK, GOAL, BIG, BALUNE, SCOPE, ALLOW, SLIDE, STOP, JUMP, JUMP2};
    CC_SYNTHESIZE(BikeState,_BikeState,BikeState);
    
    // bikeの前後輪の接地状態
    bool fWheelTouched;
    Vec2 fWheelTouchPt;
    bool rWheelTouched;
    Vec2 rWheelTouchPt;
    
    // bikeへのアクション
    bool jump(float lvl);
    void werry(float lvl);
    void dush(float lvl);
    void stop();
    float frJumpPow = 0.2;
    float fJumpPow = 0.5;
    float rJumpPow = 1;
    float weeryPow = 0.25;
    float dushPow = 1;
    float maxJumpSpeed = 30;
    float maxRotSpeed = 30;
    // 挙動に影響するパラメータ
    // 重心に追随する速度
    float chaseVelo = 100;
    
    // wheel最大速度
    float maxWheelVelo = 200;
    
    // 画面スクロール関連
    Vec2 sceneOffset = Vec2(60,-20);
    
};

#endif
