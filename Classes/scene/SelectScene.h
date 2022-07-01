#ifndef __SELECTSCENE_H__
#define __SELECTSCENE_H__

#include "scene/base/GameScene.h"
#include "util/TouchEventHelper.h"
#include "item/base/Sprite2.h"
#include "item/ScrollNode.h"
#include "cocos2d.h"
USING_NS_CC;

class SelectScene: public GameScene {
protected:
    SelectScene();
    virtual ~SelectScene();
    bool init() override;
    
public:
    CREATE_FUNC(SelectScene);
    static Scene* createScene();
    CC_SYNTHESIZE_RETAIN(Label*,_gameTitle,GameTitle);
    CC_SYNTHESIZE_RETAIN(MenuItemSprite*,_btn1,Btn1);
    CC_SYNTHESIZE_RETAIN(MenuItemSprite*,_btn2,Btn2);
    CC_SYNTHESIZE_RETAIN(Menu*,_menu,Menu);
    CC_SYNTHESIZE_RETAIN(TouchEventHelper*,_touch,Touch);
    CC_SYNTHESIZE_RETAIN(ScrollNode*,_scrollNode,ScrollNode);
    void update(float dt) override;
    void onEnterTransitionDidFinish() override;
    void _arrangeBtns();
    MenuItemSprite* genStageBtn(int i);
};

#endif