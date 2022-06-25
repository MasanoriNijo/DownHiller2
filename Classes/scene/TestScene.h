#ifndef __TESTSCENE_H__
#define __TESTSCENE_H__

#include "scene/base/GameScene.h"
#include "util/TouchEventHelper.h"
#include "item/base/Sprite2.h"
#include "util/LineMaker.h"
#include "util/CourceMaker.h"
#include "item/StraightLine.h"
#include "item/CurveLine.h"
#include "item/ScrollNode.h"
#include "cocos2d.h"
USING_NS_CC;

class TestScene: public GameScene {
protected:
    TestScene();
    virtual ~TestScene();
    bool init() override;
    
public:
    CREATE_FUNC(TestScene);
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
    CC_SYNTHESIZE_RETAIN(Sprite2*,_pt1,Pt1);
    CC_SYNTHESIZE_RETAIN(Sprite2*,_pt2,Pt2);
    CC_SYNTHESIZE_RETAIN(Sprite2*,_pt3,Pt3);
    CC_SYNTHESIZE_RETAIN(Sprite2*,_pt4,Pt4);
    CC_SYNTHESIZE_RETAIN(Sprite2*,_pt5,Pt5);
    CC_SYNTHESIZE_RETAIN(Node*,_touchObj,TouchObj);
    CC_SYNTHESIZE_RETAIN(LineMaker*,_lineMaker,LineMaker);
    CC_SYNTHESIZE_RETAIN(StraightLine*,_stLine,StLine);
    CC_SYNTHESIZE_RETAIN(CurveLine*,_cvLine,CvLine);
    CC_SYNTHESIZE_RETAIN(CourceMaker*,_courceMaker,CourceMaker);
    CC_SYNTHESIZE_RETAIN(ScrollNode*,_scrollNode,ScrollNode);
    void update(float dt) override;
    void onEnterTransitionDidFinish() override;
};

#endif
