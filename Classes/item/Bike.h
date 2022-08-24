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
    void _positionSyncToWheel(float dt);
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
    
    // debug
    CC_SYNTHESIZE_RETAIN(Label*,_bikeDebug,BikeDebug);
    
    // 前後車輪を親シーンに設置した後、親シーンから呼ぶ
    void SetPhysicsPrm();
    
    // タッチイベントをセットする
    void setTouchEvent();
    void removeTouchEvent();
    // 画面の操作の情報を受け取る。
    Vec2 touchPt1;// ひとつ前のタッチ位置
    Vec2 touchPt2;// 最新のタッチ位置
    void touchOn(Vec2 pt);
    void swaip(Vec2 pt);
    void touchOff(Vec2 pt);
    
    // スタート時に、Bikeの位置まで画面スクロール用
    float sceneChaseAjustSpeed = 400;
    float sceneChaseAjustFlg = false;
    
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
    
    // AutoFlg Onの場合、debugPointにweightPtが追従する。
    bool autoFlg = false;
    void autoSosa(float dt,Vec2 pt);
    
    // riderアクション weightPtの位置により、画像差し替える。
    // riderのフレームサイズ
    Size frameSize;
    float riderActionSpan = 1.5;
    void riderImageAction();
    
    // bikeの制御不能をある程度制限する。
    void _bikeBehaviorControl();
    // 重心速度
    Vec2 centerObjVelo;
    float maxCenterObjVelo = 200;
    // 重心回転速度Rホイール
    Vec2 centerObjRotVelo;
    float maxCenterObjRotVelo = 40;
    
    enum class BikeState {READY, NOML, BREAK, GOAL, BIG, BALUNE, SCOPE, ALLOW, SLIDE, STOP, JUMP, JUMP2};
    CC_SYNTHESIZE(BikeState,_BikeState,BikeState);
    
    // bikeの前後輪の接地状態
    bool fWheelTouched;
    Vec2 fWheelTouchPt;
    bool rWheelTouched;
    Vec2 rWheelTouchPt;
    
    // bikeへのアクション
    bool jump(float lvl);
    bool lift(float lvl);// 使用しない
    void werry(float lvl);
    void dush(float lvl);
    void stop();

    float weeryPow = 2.0;
    float maxRotSpeed = 15;
    float dushPow = 6;
    float maxDushSpeed = 60;
    float maxRJumpSpeed = 20;
    float maxFRJumpSpeed = 15;
    float maxFJumpSpeed = 5;

    // 挙動に影響するパラメータ
    // 重心に追随する速度
    float chaseVelo = 30;
    
    // wheel最大速度
    float maxWheelVelo = 200;
    
    // 画面スクロール関連
    Vec2 sceneOffset = Vec2(60,-20);
    
    // title表示用
    void setForDisplay();
    
};

#endif
