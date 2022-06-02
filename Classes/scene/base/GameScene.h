#ifndef __gamebase__GameScene__
#define __gamebase__GameScene__

#include "ad/ImovileAd.h"
#include "util/Const.h"
#include "cocos2d.h"
USING_NS_CC;

class GameScene: public Layer {
protected:
	GameScene();
	virtual ~GameScene();
	bool init() override;

public:
	static cocos2d::Scene* createScene();
    CREATE_FUNC(GameScene);

    Vec2 ctPt;
    cocos2d::Size winSize;

	void ChgRGBFromHSV(float h, float s, float v);
	float r = 101;
	float g = 255;
	float b = 227;

	float h_ = 0;
	float s_ = 0;
	float v_ = 0;

	void GetRGBFromHSV(float h, float s, float v);
	int KAKU = 0;
	float R = 0;
	float G = 0;
	float B = 0;
	void ChgColor(float h,float s,float v);//色相h,彩度ｓ、明度vを指定して、色を変更する。
	void ChgColorRnd(float s,float v);//彩度ｓ、明度vを指定して、色相をランダムに変更する。
	void ChgBeforeColor();//前回保存された色にする。

    CC_SYNTHESIZE_RETAIN(LayerColor*,_layerColor,LayerColor);
    CC_SYNTHESIZE_RETAIN(ImovileAd*,_ad,AD);

};

#endif // __HELLOWORLD_SCENE_H__
