#ifndef __neomeiro__FstScene__
#define __neomeiro__FstScene__

#include "cocos2d.h"

USING_NS_CC;
class FstScene: public cocos2d::Scene {
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
    CC_SYNTHESIZE_RETAIN(Label*,_label,Label);
};

#endif // __HELLOWORLD_SCENE_H__
