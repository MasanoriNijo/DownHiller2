#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "ad/ImovileAd.h"
#include "util/Const.h"
#include "util/Lang.h"
#include "util/ColorChanger.h"
#include "util/Calclater.h"
#include "item/Button.h"
#include "audio/include/AudioEngine.h"
#include "cocos/editor-support/cocostudio/SimpleAudioEngine.h"
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
    CC_SYNTHESIZE_RETAIN(LayerGradient*,_backGradientColor,BackGradientColor);
    CC_SYNTHESIZE_RETAIN(ImovileAd*,_ad,AD);
    CC_SYNTHESIZE_RETAIN(ColorChanger*,_colorChanger,ColorChanger);
    CC_SYNTHESIZE_RETAIN(Calclater*,_calc,Calc);
    CC_SYNTHESIZE_RETAIN(DrawNode*,_debugLine,DebugLine);
    CC_SYNTHESIZE_RETAIN(Label*,_debugMemo,DebugMemo);
    CC_SYNTHESIZE_RETAIN(Label*,_gameAnounce,GameAnounce);
    CC_SYNTHESIZE_RETAIN(ParallaxNode*,_noMoveLayer,NoMoveLayer);
    // 画面のセンターの位置
    Vec2 ctPt;
    
    // 画面のサイズ
    Size winSize;
    
    // defaultのバックカラーをセット
    void setBackGroundColor();
    
    // defaultのバックカラーをセット
    void setBackGradientGroundColor();
    
    // 指定のバックカラーをセット
    void setBackGroundColor(float h, float s, float v);
    
    // 指定のバックカラーをセット
    void setBackGradientGroundColor(float h, float s, float v, float h2, float s2, float v2);
    
    // ゲームの状態遷移
    bool fstStCnge = false; //各条件で初めにやる処理
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
    
    // 指定の位置にスプライトをセットする。通常のレイヤーにセット
    void mountScroleNode(Node* sp, Vec2 pt, float lvl);
    
    // Debug用のラインを描写する。
    void drawDebugLine();
    
    // ゲーム進行上のアナウンスを行う。例：game start,よーいドン,,,
    void showGameAnnounce(std::string st,Vec2 pt);
    void showGameAnnounce(std::string st,Vec2 pt, const std::function<void()> &endFunc);
    
    // 各種Item生成
    MenuItemSprite* generateMenuItemSprite(const ccMenuCallback& callback, Size size,std::string st,
                                           Color3B color_,Color3B color2_, bool isBlink);
    // timer
    bool tmFlg = false;
    float tm_;
    void startTime();
    void stopTime();
    std::string getTime();
    
    // 音関連
    void setBGM(const char* filePath);
    void startBGM(const char* filePath);
    void stopBGM(const char* filePath);
    void setSoundEffect(const char* filePath);
    void callSoundEffect(const char* filePath);
    
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
