#include "ColorChanger.h"

ColorChanger::ColorChanger():_opacity(255){}

ColorChanger::~ColorChanger(){}

ColorChanger* ColorChanger::create() {
    auto cc = new ColorChanger;
    if (cc && cc->init()) {
        cc->autorelease();
        return cc;
    } else {
        CC_SAFE_DELETE(cc);
        return nullptr;
    }
}

bool ColorChanger::init() {
    return true;
}

float ColorChanger::getG(){
    return this->g_;
}

float ColorChanger::getB(){
    return this->b_;
}

float ColorChanger::getH(){
    return this->h_;
}

float ColorChanger::getS(){
    return this->s_;
}

float ColorChanger::getV(){
    return this->v_;
}

Color4B ColorChanger::getColor4B(){
    return Color4B(this->r_,this->g_,this->b_,this->_opacity);
}

void ColorChanger::SetColor(float h, float s, float v) {
    
    this->h_ = h;
    this->s_ = s;
    this->v_ = v;
    
    h = h/360;
    s = s/100;
    v = v/100;
    
    float r = v;
    float g = v;
    float b = v;
    if (s > 0.0f) {
        h *= 6.0f;
        int i = (int) h;
        float f = h - (float) i;
        switch (i) {
            default:
            case 0:
                g *= 1 - s * (1 - f);
                b *= 1 - s;
                break;
            case 1:
                r *= 1 - s * f;
                b *= 1 - s;
                break;
            case 2:
                r *= 1 - s;
                b *= 1 - s * (1 - f);
                break;
            case 3:
                r *= 1 - s;
                g *= 1 - s * f;
                break;
            case 4:
                r *= 1 - s * (1 - f);
                g *= 1 - s;
                break;
            case 5:
                g *= 1 - s;
                b *= 1 - s * f;
                break;
        }
    }
    
    this->r_ = r * 255;
    this->g_ = g * 255;
    this->b_ = b * 255;
    
}

void ColorChanger::ChgColorRnd(float s, float v) {
    int rndh_ = arc4random() % static_cast<int>(360);
    this->SetColor(rndh_, s, v);
}

void ColorChanger::ChgColorRnd() {
    int rndh_ = arc4random() % static_cast<int>(255);
    float h_ = (float) rndh_ / (float) 255;
    this->SetColor(h_, this->s_, this->v_);
}

float ColorChanger::getR(){
    return this->r_;
}

void ColorChanger::transitonScene(Node* nd,Scene* transScene){
    auto transition_ = CallFuncN::create([transScene](Node* node_) {
        auto transition=TransitionCrossFade::create(0.5,transScene);
        auto cnt = ST_INT(transScene->getReferenceCount());
        Director::getInstance()->replaceScene(transition);
    });
    nd->runAction(transition_);
}

/** パラメータサンプル
 this->setLC(LayerColor::create());
 this->getLC();
 */
