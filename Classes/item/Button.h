#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "util/Calclater.h"
#include "cocos2d.h"
USING_NS_CC;

class Button: public Label {
protected:
    Button();
    virtual ~Button();
    
public:
    static Button* create();
    bool init() override;
    CC_SYNTHESIZE_RETAIN(Calclater*,_calc,Calc);
    CC_SYNTHESIZE_RETAIN(Label*,_title,Title);
    CC_SYNTHESIZE_RETAIN(Sprite*,_c1,C1);
    CC_SYNTHESIZE_RETAIN(Sprite*,_c2,C2);
    CC_SYNTHESIZE_RETAIN(Sprite*,_c3,C3);
    CC_SYNTHESIZE_RETAIN(Sprite*,_c4,C4);
    CC_SYNTHESIZE_RETAIN(Sprite*,_t1,T1);
    CC_SYNTHESIZE_RETAIN(Sprite*,_t2,T2);
    CC_SYNTHESIZE_RETAIN(Sprite*,_t3,T3);
    CC_SYNTHESIZE_RETAIN(Sprite*,_t4,T4);
    CC_SYNTHESIZE_RETAIN(Sprite*,_base,Base);
    void update(float dt) override;
    
    float _offset = 1;
    void setButton(Size size, std::string st);
    void setButtonColor(Color3B color);
};

#endif
