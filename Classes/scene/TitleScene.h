#ifndef __TITLESCENE_H__
#define __TITLESCENE_H__

#include "scene/base/GameScene.h"
#include "cocos2d.h"
USING_NS_CC;

class TitleScene: public GameScene {
protected:
    TitleScene();
    virtual ~TitleScene();
    bool init() override;
    
public:
    CREATE_FUNC(TitleScene);
    static Scene* createScene();
    CC_SYNTHESIZE_RETAIN(Sprite*,_productTitler,ProductTitle);
    void update(float dt) override;
    void onEnterTransitionDidFinish() override;
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
};

#endif
