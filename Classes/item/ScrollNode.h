#ifndef __SCROLLNODE_H__
#define __SCROLLNODE_H__

#include "util/Calclater.h"
#include "util/TouchEventHelper.h"
#include "cocos2d.h"
USING_NS_CC;

class ScrollNode: public Node {
protected:
    ScrollNode();
    virtual ~ScrollNode();
    
public:
    static ScrollNode* create();
    bool init() override;
    CC_SYNTHESIZE_RETAIN(Calclater*,_calc,Calc);
    CC_SYNTHESIZE_RETAIN(TouchEventHelper*,_touch,Touch);

    void update(float dt) override;
    void setTouchEvent();
    bool _touched;
    Vec2 _touchPt;
    Vec2 _beforeTouchPt;
    Vec2 scrollSpeed;
    float dumpSpeedRate = 50;
    float minSpeed = 10;
    
    enum class ScrollType{
        VERTICAL,
        HORIZONTAL
    };
    CC_SYNTHESIZE(ScrollType,_scrollType,ScrollType);
    
    CC_SYNTHESIZE(int,_scrollPos,ScrollPos);
    CC_SYNTHESIZE(int,_scrollWidth,ScrollWidth);
    
//    bool _touched = false;
    
};

#endif
