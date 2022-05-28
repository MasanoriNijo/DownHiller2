#ifndef __piyopiyo__Item__
#define __piyopiyo__Item__
#include "cocos2d.h"
#include "ChrPrm.h"
USING_NS_CC;

class Item: public cocos2d::Node {
protected:


	Item();
	virtual ~Item();
	bool init() override;
private:
public:
	enum class ItemState {
		GATE1, GATE2, GATE3, GATE4, GATE5, MARUTA1, MARUTA2, ISHI1, ISHI2,START,GOAL
	};
	int _madeNo; //���ԁB

	Size winSize;


	Vec2 SetPt;//セットポイントアイテム自身のセットポイント位置
	void SetPoint(Vec2 pt_,float rad);//指定のポイントpt_に、SetPtと回転rad

	int _lifePoint;
	int _scorePoint;
	std::string _itemName;

	bool fstTch=false;
	bool endTch=false;

	Vec2 fstPt;//最初にタッチした点
	Vec2 lstPt;//最後にタッチした点


	void FadeIn(float dt,float s);
	void FadeOut(float dt,float s);

	bool delFlg;
	bool PassChk();
	bool moveFlg;
	cocos2d::Size frameSize;
	void update(float dt) override;
	void setUpdateAction(std::function<void(Item*,float dt)> action);
	void ResetItem();
	void Fin();
	std::function<void(Item*,float dt)> onUpDateListener;
	std::function<void(Item*)> onFinishListener;
	std::function<void(Item*)> onContactListener;
	Vec2 GetImgPosition(); //現在のimgの親ノード上のポジションを返す。
	void setRndState();
	void setRndState(int _Lvl);
	void SetState(ItemState x);

	void Action1();
	void Action2();
	void Action3();
	void Action4();CREATE_FUNC(Item)

	;CC_SYNTHESIZE(ItemState,_itemState,ItemState) //アイテムステート
	;CC_SYNTHESIZE_RETAIN(cocos2d::Sprite *,_img,Img) //実際の画像
	;CC_SYNTHESIZE_RETAIN(cocos2d::Sprite *,_img2,Img2) //実際の画像
	;CC_SYNTHESIZE_RETAIN(cocos2d::Texture2D *,_txter1,Txter1) //実際のtexture
	;CC_SYNTHESIZE_RETAIN(cocos2d::Texture2D *,_txter2,Txter2) //実際のtexture
	;CC_SYNTHESIZE_RETAIN(cocos2d::Texture2D *,_txter3,Txter3) //実際のtexture
	;CC_SYNTHESIZE_RETAIN(cocos2d::Texture2D *,_txter4,Txter4) //実際のtexture
	;CC_SYNTHESIZE_RETAIN(cocos2d::Texture2D *,_txter5,Txter5) //実際のtexture
	;CC_SYNTHESIZE_RETAIN(cocos2d::Texture2D *,_txter6,Txter6) //実際のtexture

	;CC_SYNTHESIZE_RETAIN(cocos2d::PhysicsBody *,_body,Body)
	;CC_SYNTHESIZE_RETAIN(cocos2d::PhysicsBody *,_body2,Body2)
	;CC_SYNTHESIZE_RETAIN(cocos2d::PhysicsBody *,_body3,Body3)
	;CC_SYNTHESIZE_RETAIN(cocos2d::PhysicsBody *,_body4,Body4)
	;

};
#endif // __HELLOWORLD_SCENE_H__
