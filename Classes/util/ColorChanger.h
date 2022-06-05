#ifndef __COLORCHANGER_H__
#define __COLORCHANGER_H__

#include "util/Const.h"
#include "cocos2d.h"
USING_NS_CC;

class ColorChanger: public Ref {
protected:
    ColorChanger();
    virtual ~ColorChanger();
    float r_ = 0;
    float g_ = 0;
    float b_ = 0;
    
    float h_ = DEFAULT_COLOR_H;
    float s_ = DEFAULT_COLOR_S;
    float v_ = DEFAULT_COLOR_V;
    
public:
    static ColorChanger* create();
    bool init();
    
    // RGB系カラーを取得する 0-255
    float getR();
    float getG();
    float getB();
    
    // HSV系カラーを取得する H:0-360 S,V:0-100
    float getH();
    float getS();
    float getV();
    
    // 透過度
    CC_SYNTHESIZE(int,_opacity,Opacity);
    
    // Color4Bを出力する
    Color4B getColor4B();
    
    //色相h,彩度ｓ、明度vを指定して、色を変更する。
    void SetColor(float h,float s,float v);
    //彩度ｓ、明度vを指定して、色相をランダムに変更する。
    void ChgColorRnd(float s,float v);
    //現在の彩度ｓ、明度vで色相をランダムに変更する。
    void ChgColorRnd();
    
    void transitonScene(Node* nd,Scene* transScene);
    
};

#endif
