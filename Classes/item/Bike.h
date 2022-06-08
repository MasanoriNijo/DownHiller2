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
    
public:
    static Bike* create();
    bool init() override;
    CC_SYNTHESIZE_RETAIN(Sprite*,_rider,Rider);
    CC_SYNTHESIZE_RETAIN(Sprite*,_fWheel,Fwheel);
    CC_SYNTHESIZE_RETAIN(Sprite*,_rWheel,Rwheel);
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
    // riderアクション weightPtの位置により、画像差し替える。
    // riderのフレームサイズ
    Size frameSize;
    float riderActionSpan = 5;
    void riderImageAction();
    
    enum class BikeState {READY, NOML, BREAK, GOAL, BIG, BALUNE, SCOPE, ALLOW, SLIDE, STOP, JUMP, JUMP2};
    CC_SYNTHESIZE(BikeState,_BikeState,BikeState);
    
    // bikeの操作
    bool fWheelTouched;
    Vec2 fWheelTouchPt;
    bool rWheelTouched;
    Vec2 rWheelTouchPt;
    void fWheelUp(float pow);
    void fWheeldown(float pow);
    void fWheelJump(float pow);
    void rWheelUp(float pow);
    void rWheeldown(float pow);
    void rWheelJump(float pow);

};

#endif
