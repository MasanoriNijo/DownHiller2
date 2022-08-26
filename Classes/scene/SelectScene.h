#ifndef __SELECTSCENE_H__
#define __SELECTSCENE_H__

#include "scene/base/GameScene.h"
#include "util/TouchEventHelper.h"
#include "util/CourceManager.h"
#include "item/base/Sprite2.h"
#include "item/ScrollNode.h"
#include "item/Bike.h"
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
    CC_SYNTHESIZE_RETAIN(Menu*,_menu2,Menu2);
    CC_SYNTHESIZE_RETAIN(Menu*,_menu3,Menu3);
    CC_SYNTHESIZE_RETAIN(Menu*,_menu4,Menu4);
    CC_SYNTHESIZE_RETAIN(Menu*,_menu5,Menu5);
    CC_SYNTHESIZE_RETAIN(Menu*,_menu6,Menu6);
    CC_SYNTHESIZE_RETAIN(Menu*,_menu7,Menu7);
    CC_SYNTHESIZE_RETAIN(Menu*,_menu8,Menu8);
    CC_SYNTHESIZE_RETAIN(TouchEventHelper*,_touch,Touch);
    CC_SYNTHESIZE_RETAIN(ScrollNode*,_scrollNode,ScrollNode);
    CC_SYNTHESIZE_RETAIN(CourceManager*,_courceManager,CourceManager);
    CC_SYNTHESIZE_RETAIN(Bike*,_bike,Bike);
    void update(float dt) override;
    void onEnterTransitionDidFinish() override;
    void _arrangeBtns();
    void _arrangeBtnsForDebug();
    MenuItemSprite* genStageBtn(int i);
    MenuItemSprite* genCourceBtn(int i);
    
};

#endif
