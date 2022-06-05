#ifndef __TESTPHYSICSSCENE_H__
#define __TESTPHYSICSSCENE_H__

#include "scene/base/GameScene.h"
#include "util/TouchEventHelper.h"
#include "cocos2d.h"
USING_NS_CC;

class TestPhysicsScene: public GameScene {
protected:
  TestPhysicsScene();
  virtual ~TestPhysicsScene();
  bool init() override;

public:
  CREATE_FUNC(TestPhysicsScene);
  static Scene* createScene();
    CC_SYNTHESIZE_RETAIN(Label*,_gameTitle,GameTitle);
    CC_SYNTHESIZE_RETAIN(DrawNode*,_baseLine,BaseLine);
    CC_SYNTHESIZE_RETAIN(DrawNode*,_ball,Ball);
    CC_SYNTHESIZE_RETAIN(MenuItemImage*,_btn1,Btn1);
    CC_SYNTHESIZE_RETAIN(MenuItemImage*,_btn2,Btn2);
    CC_SYNTHESIZE_RETAIN(MenuItemImage*,_btn3,Btn3);
    CC_SYNTHESIZE_RETAIN(MenuItemImage*,_btn4,Btn4);
    CC_SYNTHESIZE_RETAIN(Menu*,_menu,Menu);
    CC_SYNTHESIZE_RETAIN(TouchEventHelper*,_touch,Touch);
    
    void update(float dt) override;
    void onEnterTransitionDidFinish() override;
    
    Vec2 pt1;
    Vec2 pt2;
    Vec2 pt3;
    Vec2 pt4;
    Vec2 pt5;
    Vec2 points[4];
};

#endif
