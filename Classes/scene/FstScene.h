#ifndef __FSTSCENE_H__
#define __FSTSCENE_H__

#include "ad/ImovileAd.h"
#include "scene/base/GameScene.h"
#include "util/Const.h"
#include "cocos2d.h"
USING_NS_CC;

/**
最初に表示させるロゴ表示
*/
class FstScene: public Scene {
protected:
    FstScene();
    virtual ~FstScene();
    bool init() override;
public:
    static cocos2d::Scene* createScene();
    CREATE_FUNC(FstScene);
    void update(float dt) override;
    void onEnterTransitionDidFinish() override;
    CC_SYNTHESIZE_RETAIN(Sprite*,_productTitle,ProductTitle);
    CC_SYNTHESIZE_RETAIN(ImovileAd*,_ad,AD);
};

#endif
