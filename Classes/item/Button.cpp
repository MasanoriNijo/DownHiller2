#include "Button.h"

Button::Button():
_calc(NULL), _title(NULL), _c1(NULL), _c2(NULL), _c3(NULL), _c4(NULL), _t1(NULL), _t2(NULL), _t3(NULL), _t4(NULL)
{}

Button::~Button() {
    CC_SAFE_RELEASE_NULL(_calc);
    CC_SAFE_RELEASE_NULL(_title);
    CC_SAFE_RELEASE_NULL(_c1);
    CC_SAFE_RELEASE_NULL(_c2);
    CC_SAFE_RELEASE_NULL(_c3);
    CC_SAFE_RELEASE_NULL(_c4);
    CC_SAFE_RELEASE_NULL(_t1);
    CC_SAFE_RELEASE_NULL(_t2);
    CC_SAFE_RELEASE_NULL(_t3);
    CC_SAFE_RELEASE_NULL(_t4);
}

Button* Button::create() {
    auto obj = new Button;
    if (obj && obj->init()) {
        obj->autorelease();
        return obj;
    } else {
        CC_SAFE_DELETE(obj);
        return nullptr;
    }
}

bool Button::init() {
    
    if(!Label::initWithTTF("", "irohamaru.ttf", 12)){
        return false;
    }
//    enableBold();
//    enableOutline(Color4B::WHITE,1);
    setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    setCalc(Calclater::create());

    setC1(Sprite::create("btn_curve.png"));
    setC2(Sprite::createWithTexture(getC1()->getTexture()));
    setC3(Sprite::createWithTexture(getC1()->getTexture()));
    setC4(Sprite::createWithTexture(getC1()->getTexture()));
    setT1(Sprite::create("btn_line.png"));
    setT2(Sprite::createWithTexture(getT1()->getTexture()));
    setT3(Sprite::createWithTexture(getT1()->getTexture()));
    setT4(Sprite::createWithTexture(getT1()->getTexture()));
    
    getC1()->setAnchorPoint(Vec2(0,1));
    getC2()->setAnchorPoint(Vec2(0,1));
    getC3()->setAnchorPoint(Vec2(0,1));
    getC4()->setAnchorPoint(Vec2(0,1));
    
    getT1()->setAnchorPoint(Vec2(0,1));
    getT2()->setAnchorPoint(Vec2(0,1));
    getT3()->setAnchorPoint(Vec2(0,1));
    getT4()->setAnchorPoint(Vec2(0,1));
    
    return true;
}

void Button::update(float dt) {
    // todo
}

void Button::setButton(Size size, std::string st){
    setString(st);
    Size size_ = getContentSize();
    Vec2 ctPt = Vec2(size_.width/2,size_.height/2);
    size_.width += _offset*2;
    size_.height += _offset*2;
    
    if(size_.width>size.width){
        size.width = size_.width;
    }
    
    if(size_.height>size.height){
        size.height = size_.height;
    }
    
    float w = size.width;
    float h = size.height;
    float cl = getC1()->getContentSize().width;
    float tl = getT1()->getContentSize().width;
    getC1()->setPosition(Vec2(-w/2,h/2)+ctPt);
    getC2()->setRotation(90);
    getC2()->setPosition(Vec2(w/2,h/2)+ctPt);
    getC3()->setRotation(180);
    getC3()->setPosition(Vec2(w/2,-h/2)+ctPt);
    getC4()->setRotation(270);
    getC4()->setPosition(Vec2(-w/2,-h/2)+ctPt);
    addChild(getC1());
    addChild(getC2());
    addChild(getC3());
    addChild(getC4());
    
    getT1()->setScaleX((w-2*cl)/tl);
    getT1()->setPosition(Vec2(-w/2+cl,h/2)+ctPt);
    getT2()->setScaleX((h-2*cl)/tl);
    getT2()->setRotation(90);
    getT2()->setPosition(Vec2(w/2,h/2-cl)+ctPt);
    getT3()->setScaleX((w-2*cl)/tl);
    getT3()->setRotation(180);
    getT3()->setPosition(Vec2(w/2-cl,-h/2)+ctPt);
    getT4()->setScaleX((h-2*cl)/tl);
    getT4()->setRotation(270);
    getT4()->setPosition(Vec2(-w/2,-h/2+cl)+ctPt);
    
    addChild(getT1());
    addChild(getT2());
    addChild(getT3());
    addChild(getT4());    
}

void Button::setButtonColor(Color3B color){
    Color4B color4b_= Color4B(color);
    setTextColor(color4b_);
    getC1()->setColor(color);
    getC2()->setColor(color);
    getC3()->setColor(color);
    getC4()->setColor(color);
    getT1()->setColor(color);
    getT2()->setColor(color);
    getT3()->setColor(color);
    getT4()->setColor(color);
}
/** パラメータサンプル
 setCalc(Calclater::create());
 getCalc();
 setTitle(Label::create());
 getTitle();
 setC1(Sprite::create());
 getC1();
 setC2(Sprite::create());
 getC2();
 setC3(Sprite::create());
 getC3();
 setC4(Sprite::create());
 getC4();
 sett1(Sprite::create());
 gett1();
 sett2(Sprite::create());
 gett2();
 sett3(Sprite::create());
 gett3();
 sett4(Sprite::create());
 gett4();
 */
