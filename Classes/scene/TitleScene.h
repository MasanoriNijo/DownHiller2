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
    CC_SYNTHESIZE_RETAIN(Sprite*,_gameTitle,GameTitle);
    CC_SYNTHESIZE_RETAIN(MenuItemImage*,_startBtn,StartBtn);
    CC_SYNTHESIZE_RETAIN(MenuItemImage*,_howtoBtn,HowToBtn);
    CC_SYNTHESIZE_RETAIN(MenuItemImage*,_resultBtn,ResultBtn);
    CC_SYNTHESIZE_RETAIN(Menu*,_menu,Menu);
    void update(float dt) override;
    void onEnterTransitionDidFinish() override;
};

#endif
