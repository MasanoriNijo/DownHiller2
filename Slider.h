#ifndef __neomeiro__Slider__
#define __neomeiro__Slider__

#include "cocos2d.h"

USING_NS_CC;

class Slider: public cocos2d::Sprite {
protected:
	Slider();
	virtual ~Slider();
	bool init() override;

private:
public:

	int MinValue = 0;
	int MaxValue = 100;
	int Value_ = 0;
	int varLength = 100;

	void SetNamaeTag(std::string namae_);

	bool selFlg; //スライダーをタッチしたかどうか？
	bool selFlg2; //枠をタッチしたかどうか？
	void SlideMove(cocos2d::Vec2 pt); //スライダーを指定の位置に動かす。
	void SlideMove(int _atai); //スライダーを動かす。

	bool SelectTumami(cocos2d::Vec2 pt_); //つまみを選択しているかどうかチェック。

	bool SelectPlusBtn(cocos2d::Vec2 pt_); //pulusBtnを選択しているかどうかチェック。
	bool plusFlg=false; //スライダーをタッチしたかどうか？
	bool SelectMinusBtn(cocos2d::Vec2 pt_); //minusBtnを選択しているかどうかチェック。
	bool minusFlg=false; //スライダーをタッチしたかどうか？
	void TchOff();//タッチパラメータを初期化
	Vec2 GetLocalPt(Vec2 pt);//ペアレントノードでの座標点を、このローカル座標に変換する。

	float TchTime=1.0f;//
	float tchTime_;
	float AddTime=0.2f;
	float addTime_;

	void AddAtai(int x);//値を増減する

//	void AddChildSub();//通常のaddChildとセットで使用

	int touchID;//現在タッチされているID

	bool moveFlg;
	cocos2d::Size frameSize;
	void update(float dt) override;

	CREATE_FUNC(Slider)
	;CC_SYNTHESIZE_RETAIN(Sprite*, _memori,Memori)
	;CC_SYNTHESIZE_RETAIN(Sprite*, _tumami,Tumami)
	;CC_SYNTHESIZE_RETAIN(MenuItemImage*, _plusBtn,PlusBtn)
	;CC_SYNTHESIZE_RETAIN(MenuItemImage*, _minusBtn,MinusBtn)
	;CC_SYNTHESIZE_RETAIN(Sprite*, _plusBtnImg,PlusBtnImg)
	;CC_SYNTHESIZE_RETAIN(Sprite*, _minusBtnImg,MinusBtnImg)
	;CC_SYNTHESIZE_RETAIN(Menu*, _menu1,Menu1)
	;CC_SYNTHESIZE_RETAIN(Menu*, _menu2,Menu2)
	;CC_SYNTHESIZE_RETAIN(cocos2d::Label*,_atai,Atai)
	;CC_SYNTHESIZE_RETAIN(cocos2d::Label*,_namae,Namae)
	;CC_SYNTHESIZE_RETAIN(cocos2d::Label*,_namae1,Namae1)
	;CC_SYNTHESIZE_RETAIN(cocos2d::Label*,_namae2,Namae2)




};
#endif // __HELLOWORLD_SCENE_H__
