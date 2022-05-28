#ifndef __neomeiro__TestScene__
#define __neomeiro__TestScene__

#include "cocos2d.h"
#include "ImovileAd.h"
#include "Slider.h"
USING_NS_CC;
class TestScene: public cocos2d::Layer {
protected:
	TestScene();
	virtual ~TestScene();
	bool init() override;

public:
	cocos2d::Vec2 _point1;
	cocos2d::Vec2 _point2;
	static cocos2d::Scene* createScene();CREATE_FUNC(TestScene)
	;
	void SetPrm();
	int index = 0;
	void SetPrm(int index_);
	void GetPrm(int index_);

	void update(float dt);
	void SetTouchListenner();
	void onEnterTransitionDidFinish() override;CC_SYNTHESIZE_RETAIN(Sprite*,_productTitle,ProductTitle)
	;CC_SYNTHESIZE_RETAIN(Slider*,_slider,Slider)
	;CC_SYNTHESIZE_RETAIN(Slider*,_slider2,Slider2)
	;CC_SYNTHESIZE_RETAIN(Slider*,_slider3,Slider3)
	;CC_SYNTHESIZE_RETAIN(Slider*,_slider4,Slider4)
	;CC_SYNTHESIZE_RETAIN(Slider*,_slider5,Slider5)
	;CC_SYNTHESIZE_RETAIN(Slider*,_slider6,Slider6)
	;CC_SYNTHESIZE_RETAIN(Slider*,_slider7,Slider7)
	;CC_SYNTHESIZE_RETAIN(Slider*,_slider8,Slider8)
	;CC_SYNTHESIZE_RETAIN(Slider*,_slider9,Slider9)
	;CC_SYNTHESIZE_RETAIN(Slider*,_slider10,Slider10)
	;CC_SYNTHESIZE_RETAIN(Slider*,_slider11,Slider11)
	;CC_SYNTHESIZE_RETAIN(Slider*,_slider12,Slider12)

	;
	cocos2d::Vector<Slider*> _touchSpritepool;

CC_SYNTHESIZE_RETAIN(EventListenerTouchOneByOne*, _touchlistener,TouchListenner)
	;	//debug用
CC_SYNTHESIZE_RETAIN(cocos2d::MenuItemImage*,_prmBtn,PrmBtn)
	;CC_SYNTHESIZE_RETAIN(cocos2d::Menu*,_menuPrm,MenuPrm)
	;CC_SYNTHESIZE_RETAIN(cocos2d::MenuItemImage*,_plusBtn,PlusBtn)
	;CC_SYNTHESIZE_RETAIN(cocos2d::Menu*,_plusMenu,PlusMenu)
	;CC_SYNTHESIZE_RETAIN(cocos2d::MenuItemImage*,_minusBtn,MinusBtn)
	;CC_SYNTHESIZE_RETAIN(cocos2d::Menu*,_minusMenu,MinusMenu)
	;CC_SYNTHESIZE_RETAIN(cocos2d::Label*,_indexLavel,IndexLavel)
	;
};

#endif // __HELLOWORLD_SCENE_H__
