#ifndef __COLORCHANGER_H__
#define __COLORCHANGER_H__

#include "cocos2d.h"
USING_NS_CC;

class ColorChanger: public Ref {
protected:
    ColorChanger();
    virtual ~ColorChanger();
    float r_ = 101;
    float g_ = 255;
    float b_ = 227;
    
    float h_ = 0;
    float s_ = 0;
    float v_ = 0;
    
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
    
    //色相h,彩度ｓ、明度vを指定して、色を変更する。
    void SetColor(float h,float s,float v);
    //彩度ｓ、明度vを指定して、色相をランダムに変更する。
    void ChgColorRnd(float s,float v);
    //現在の彩度ｓ、明度vで色相をランダムに変更する。
    void ChgColorRnd();
    
};

#endif
