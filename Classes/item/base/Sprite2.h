#ifndef __SPRITE2_H__
#define __SPRITE2_H__

#include "util/Calclater.h"
#include "util/TouchEventHelper.h"
#include "math.h"
#include "cocos/editor-support/cocostudio/SimpleAudioEngine.h"
#include "cocos2d.h"
USING_NS_CC;

class Sprite2: public Sprite {
    
protected:
    Sprite2();
    virtual ~Sprite2();
    
private:
    
public:
    void setVisible(bool flg) override;
    static Sprite2* create();
    static Sprite2* create(const std::string& filename);
    static Sprite2* createWithTexture(Texture2D *texture);
    static Sprite2* createWithTexture(Texture2D *texture, Rect rct_);
    
    bool initWithFile(const std::string& filename) override;
    bool initWithTexture(Texture2D *texture) override;
    
    //想定するペアレンツノード
    CC_SYNTHESIZE_RETAIN(Sprite*,_parentSprite,ParentSprite);
    CC_SYNTHESIZE_RETAIN(PhysicsBody*,_body,Body);
    CC_SYNTHESIZE_RETAIN(Sprite*,_debugPt,DebugPt);
    CC_SYNTHESIZE_RETAIN(Calclater*,_calc,Calc);
    CC_SYNTHESIZE_RETAIN(TouchEventHelper*,_touch,Touch);
    //ピン止め位置
    CC_SYNTHESIZE(Vec2,_pinPt,PinPt);
    //スプライト内のピン位置
    CC_SYNTHESIZE(Vec2,_ctPt,CtPt);
    CC_SYNTHESIZE(cocos2d::Vector<cocos2d::SpriteFrame *>,_pointFrame,PointFrame);
    CC_SYNTHESIZE(std::function<void(Sprite2*,float dt)> ,_updateListener,UpDateListener)
    
    void update(float dt) override;
    
    // 新規追加関数
    
    // 画面のセンターの位置
    Vec2 ctPt;
    
    // 画面のサイズ
    Size winSize;
        
    // 標準的なタッチリスナーを設定する。
    void setDefaultTouchEvent();
    bool _touched;
    Vec2 _touchPt;
    Vec2 _localTouchPt;
    
    // 効果音をセットする。
    void setSoundEffect(const char* filePath);
    void callSoundEffect(const char* filePath);
    
    // 新規追加ここまで
    
    Vec2 pt_; //計算用変数
    Vec2 pt2_; //計算用変数
    Vec2 pt3_; //計算用変数
    float x_;
    float x2_;
    float x3_;
    bool a_;
    bool b_;
    bool c_;
    
    Vec2 _point1;
    Vec2 _point2;
    
    //tapを判定
    bool GetTouch(Vec2 pt_); //画像内であったら真
    
    //ピン止めするように回転する
    void SetRot(float kaku_);
    void SetPos(Vec2 pt_);
    void SetRotPos(float kaku_, Vec2 pt_);
    
    //操作方法をセット
    void SetMoveTypeA(float velo_);
    void SetMoveTypeB(float velo_);
    float _velo = 0;
    bool _trnLeft = false;
    bool _trnRight = false;

    //pointボデイを作成する。
    void MadePoint();
    void ShowPoint(bool flg);
    void SetPointPos(Vec2 pt);
    //ポイントフラグ
    bool pointFlg;
    //エフェクトで消える。
    void DelShow();
    
    //エフェクトで消える。
    void DelShow(Vec2 pt_);
    
    //親ノードのポイントをローカルポイントに変換する。
    Vec2 GetLocalPt(Vec2 pt_);
    
    //rad1_へ向かって、rad2_から回転する。
    float ChaseRad(float rad1_, float rad2_, float velo_, float dt);
    
    //現在のラジアンを取得
    float GetRad();
    //追従が完了したかどうか？
    bool chsFlg;

    // オート操作系
    float ChaseA(float A, float chaser_, float v_, float dt);
    Vec2 ChaseA(Vec2 A, Vec2 chaser_, float v_, float dt);
    void ChaseA(Vec2 A, float v_, float dt);
    //自身が追いかける。
    bool ChaseA(float dt);
    Vec2 AutoPt;
    float AutoV;
    
    //移動予測して追う
    float ChaseB(float A, float vA, float chaser_, float v_, float dt);
    Vec2 ChaseB(Vec2 A, Vec2 vA, Vec2 chaser_, float v_, float dt);
    //ランダムに移動
    //ランダム回転半径
    Vec2 rndR_;
    //ランダム回転速度ラジアン
    float rndrad_;
    float ChaseC(float A, float chaser_, float v_, float dt);
    Vec2 ChaseC(Vec2 A, Vec2 chaser_, float v_, float dt);
    
    //ピン止めするように回転する.親ノードの親ノードに所属している場合
    void SetRot2(float kaku_);
    void SetPos2(Vec2 pt_);
    void SetRotPos2(float kaku_, Vec2 pt_);
    
    //ピン止めするように回転する.親ノードの親ノードの親ノードに所属している場合
    void SetRot3(float kaku_);
    void SetPos3(Vec2 pt_);
    void SetRotPos3(float kaku_, Vec2 pt_);
    
};

#endif /* SPRITE2_H_ */
