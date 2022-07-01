#include "Modal.h"

Modal::Modal():
_calc(NULL), _title(NULL), _c1(NULL), _c2(NULL), _c3(NULL), _c4(NULL),
_t1(NULL), _t2(NULL), _t3(NULL), _t4(NULL), _base(NULL)
{}

Modal::~Modal() {
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
    CC_SAFE_RELEASE_NULL(_base);
}

Modal* Modal::create() {
    auto obj = new Modal;
    if (obj && obj->init()) {
        obj->autorelease();
        return obj;
    } else {
        CC_SAFE_DELETE(obj);
        return nullptr;
    }
}

bool Modal::init() {
    
    if(!Node::create()){
        return false;
    }
//    enableBold();
//    enableOutline(Color4B::WHITE,1);
    setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    setCalc(Calclater::create());
    setGlobalZOrder(OBJ_LAYER_TOP);

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
    
    setBase(Sprite::create("btn_base.png"));
    getBase()->setGlobalZOrder(OBJ_LAYER_TOP-1);
    
    return true;
}

void Modal::update(float dt) {
    // todo
}

void Modal::setModal(Size size, std::string st){
    
    modalSize = size;
    ctPt = Vec2(size.width/2,size.height/2);
    setTitle(Label::createWithTTF(st, "irohamaru.ttf", 12));
    getTitle()->setPosition(Vec2(0,ctPt.y-getTitle()->getContentSize().height));
    getTitle()->setGlobalZOrder(OBJ_LAYER_TOP);
    addChild(getTitle());
        
    float w = size.width;
    float h = size.height;
    float cl = getC1()->getContentSize().width;
    float tl = getT1()->getContentSize().width;
    getC1()->setPosition(Vec2(-w/2,h/2));
    getC2()->setRotation(90);
    getC2()->setPosition(Vec2(w/2,h/2));
    getC3()->setRotation(180);
    getC3()->setPosition(Vec2(w/2,-h/2));
    getC4()->setRotation(270);
    getC4()->setPosition(Vec2(-w/2,-h/2));
    addChild(getC1());
    addChild(getC2());
    addChild(getC3());
    addChild(getC4());
    
    getT1()->setScaleX((w-2*cl)/tl);
    getT1()->setPosition(Vec2(-w/2+cl,h/2));
    getT2()->setScaleX((h-2*cl)/tl);
    getT2()->setRotation(90);
    getT2()->setPosition(Vec2(w/2,h/2-cl));
    getT3()->setScaleX((w-2*cl)/tl);
    getT3()->setRotation(180);
    getT3()->setPosition(Vec2(w/2-cl,-h/2));
    getT4()->setScaleX((h-2*cl)/tl);
    getT4()->setRotation(270);
    getT4()->setPosition(Vec2(-w/2,-h/2+cl));
    
    addChild(getT1());
    addChild(getT2());
    addChild(getT3());
    addChild(getT4());
    
    getBase()->Node::setScaleX((w-2*cl)/getBase()->getContentSize().width);
    getBase()->Node::setScaleY((h-2*cl)/getBase()->getContentSize().height);
    getBase()->setPosition(Vec2(getContentSize().width/2,getContentSize().height/2));
    addChild(getBase());
}

void Modal::setModalColor(Color3B color){
    Color4B color4b_= Color4B(color);
    getTitle()->setTextColor(color4b_);
    getC1()->setColor(color);
    getC2()->setColor(color);
    getC3()->setColor(color);
    getC4()->setColor(color);
    getT1()->setColor(color);
    getT2()->setColor(color);
    getT3()->setColor(color);
    getT4()->setColor(color);
    getBase()->setColor(color);
}

void Modal::setModalOpacity(float opa){
    getTitle()->setOpacity(opa);
    getC1()->setOpacity(opa);
    getC2()->setOpacity(opa);
    getC3()->setOpacity(opa);
    getC4()->setOpacity(opa);
    getT1()->setOpacity(opa);
    getT2()->setOpacity(opa);
    getT3()->setOpacity(opa);
    getT4()->setOpacity(opa);
    getBase()->setOpacity(opa);
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
