#ifndef __TITLESCENE_H__
#define __TITLESCENE_H__

#include "scene/base/GameScene.h"
#include "item/Button.h"
#include "item/Bike.h"
#include "util/CourceManager.h"

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
    CC_SYNTHESIZE_RETAIN(CourceManager*,_courceManager,CourceManager);
    CC_SYNTHESIZE_RETAIN(Bike*,_bike,Bike);
    CC_SYNTHESIZE_RETAIN(EventListenerPhysicsContact*, _contactlistener,ContactListenner);
    
    void demo();
    
    void setContactListener();
    void _onContactBegin(PhysicsContact& contact, PhysicsShape* ps);
    void _onContactPostSolve(PhysicsContact& contact, PhysicsShape* ps);
    void _onContactSeparate(PhysicsContact& contact, PhysicsShape* ps);
    
    void update(float dt) override;
    void onEnterTransitionDidFinish() override;
};

#endif
