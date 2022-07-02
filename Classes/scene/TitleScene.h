#ifndef __TITLESCENE_H__
#define __TITLESCENE_H__

#include "scene/base/GameScene.h"
#include "item/Button.h"

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
    CC_SYNTHESIZE_RETAIN(Label*,_gameTitle,GameTitle);
    CC_SYNTHESIZE_RETAIN(Label*,_gameTitle2,GameTitle2);
    CC_SYNTHESIZE_RETAIN(Label*,_gameTitle3,GameTitle3);
    CC_SYNTHESIZE_RETAIN(MenuItemSprite*,_startBtn,StartBtn);
    CC_SYNTHESIZE_RETAIN(MenuItemSprite*,_howtoBtn,HowToBtn);
    CC_SYNTHESIZE_RETAIN(MenuItemSprite*,_resultBtn,ResultBtn);
    CC_SYNTHESIZE_RETAIN(Menu*,_menu,Menu);
    void update(float dt) override;
    void onEnterTransitionDidFinish() override;
};

#endif
