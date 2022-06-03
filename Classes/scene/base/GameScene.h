#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "ad/ImovileAd.h"
#include "util/Const.h"
#include "util/ColorChanger.h"
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
    CC_SYNTHESIZE_RETAIN(LayerColor*,_backColor,BackColor);
    CC_SYNTHESIZE_RETAIN(ImovileAd*,_ad,AD);
    CC_SYNTHESIZE_RETAIN(ColorChanger*,_colorChanger,ColorChanger);
    
    // 画面のセンターの位置
    Vec2 ctPt;
    
    // 画面のサイズ
    Size winSize;
    
    // defaultのバックカラーをセット
    void setBackGroundColor();
    
    // 指定のバックカラーをセット
    void setBackGroundColor(float h, float s, float v);
    
    void update(float dt) override;
    void onEnterTransitionDidFinish() override;
};
#endif
