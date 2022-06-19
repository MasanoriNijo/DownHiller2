#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "ad/ImovileAd.h"
#include "util/Const.h"
#include "util/ColorChanger.h"
#include "util/Calclater.h"
#include "audio/include/AudioEngine.h"
#include "scene/base/TransitionScene.h"
#include "cocos2d.h"
USING_NS_CC;

class GameScene:public Layer {
protected:
    GameScene();
    virtual ~GameScene();
    bool init() override;
    
public:
    CREATE_FUNC(GameScene);
    static Scene* createScene();
    static Scene* createPhysicsScene();
    CC_SYNTHESIZE_RETAIN(LayerColor*,_backColor,BackColor);
    CC_SYNTHESIZE_RETAIN(ImovileAd*,_ad,AD);
    CC_SYNTHESIZE_RETAIN(ColorChanger*,_colorChanger,ColorChanger);
    CC_SYNTHESIZE_RETAIN(Calclater*,_calc,Calc);
    CC_SYNTHESIZE_RETAIN(DrawNode*,_debugLine,DebugLine);
    CC_SYNTHESIZE_RETAIN(Label*,_debugMemo,DebugMemo);
    CC_SYNTHESIZE_RETAIN(ParallaxNode*,_noMoveLayer,NoMoveLayer);
    // 画面のセンターの位置
    Vec2 ctPt;
    
    // 画面のサイズ
    Size winSize;
    
    // defaultのバックカラーをセット
    void setBackGroundColor();
    
    // 指定のバックカラーをセット
    void setBackGroundColor(float h, float s, float v);
    
    // ゲームの状態遷移
    bool fstStCnge = true; //各条件で初めにやる処理
    enum class GameState {
        READY, //ゲーム開始の処理
        PLAY, //プレイ中
        CLEAR,//ゲームクリヤ
        MISS, //ミス失敗
    };
    CC_SYNTHESIZE(GameState,_gameState,GameState);
    
    void update(float dt) override;
    void onEnterTransitionDidFinish() override;
    void onExit() override;
    // 画面遷移
    void transitonScene(Scene* scene);
    
    // 指定の位置にスプライトをセットする。固定レイヤーにセット
    void mountNode(Node* sp, Vec2 pt, float lvl);
    
    // 指定の位置にスプライトをセットする。固定レイヤーにセット
    void mountScroleNode(Node* sp, Vec2 pt, float lvl);
    
    // Debug用のラインを描写する。
    void drawDebugLine();
    
    // 画面のサイズ関連を取得する.
    // 実際の画面サイズ
     // Getting a real display size.
    float getScreenWidth();
    float getScreenHeight();
    
    // 設計上の画面サイズ
    // Getting a design size.
    float getDesignWidth();
    float getDesignHeight();
    
};
#endif
