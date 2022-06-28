#ifndef __GAMESTAGE_H__
#define __GAMESTAGE_H__

#include "scene/base/GameScene.h"
#include "util/TouchEventHelper.h"
#include "util/LineMaker.h"
#include "util/CourceMaker.h"
#include "util/CourceManager.h"
#include "item/CurveLine.h"
#include "item/Bike.h"
#include "item/Flg.h"
#include "item/StraightLine.h"
#include "cocos2d.h"
USING_NS_CC;

class GameStage: public GameScene {
protected:
    GameStage();
    virtual ~GameStage();
    bool init() override;

public:
    CREATE_FUNC(GameStage);
    static Scene* createScene();
    CC_SYNTHESIZE_RETAIN(Label*,_gameTitle,GameTitle);
    CC_SYNTHESIZE_RETAIN(MenuItemImage*,_btn1,Btn1);
    CC_SYNTHESIZE_RETAIN(MenuItemImage*,_btn2,Btn2);
    CC_SYNTHESIZE_RETAIN(MenuItemImage*,_btn3,Btn3);
    CC_SYNTHESIZE_RETAIN(MenuItemImage*,_btn4,Btn4);
    CC_SYNTHESIZE_RETAIN(Menu*,_menu,Menu);
    CC_SYNTHESIZE_RETAIN(TouchEventHelper*,_touch,Touch);
    CC_SYNTHESIZE_RETAIN(Bike*,_bike,Bike);
    CC_SYNTHESIZE_RETAIN(EventListenerPhysicsContact*, _contactlistener,ContactListenner);
    CC_SYNTHESIZE_RETAIN(CourceMaker*,_courceMaker,CourceMaker);
    CC_SYNTHESIZE_RETAIN(CourceManager*,_courceManager,CourceManager);
    
    void update(float dt) override;
    void onEnterTransitionDidFinish() override;
    
    // 接触感知リスナー
    void setContactListener();
    void _onContactBegin(PhysicsContact& contact, PhysicsShape* ps);
    void _onContactPostSolve(PhysicsContact& contact, PhysicsShape* ps);
    void _onContactSeparate(PhysicsContact& contact, PhysicsShape* ps);
    
    // geme状態遷移
    void onReady();
    void onPlay();
    void onClear();
    void onMiss();
    Vec2 missPt;
    
    // サンプルコース
    void courceA();
    void courceB();
    void courceC();
};

#endif
