#ifndef __neomeiro__SelTag__
#define __neomeiro__SelTag__

#include "cocos2d.h"
#include "MainScene.h"
#include "Dot.h"
#include "GameDeta.h"
#include "SpritePool.h"
USING_NS_CC;

class SelTag: public cocos2d::Sprite {
protected:
	SelTag();
	virtual ~SelTag();
	bool init() override;

private:
public:

	Size wakuSize;
	Vec2 ctPt;

	int Level_ = 1; //現在選択のレベル

	void SetLevel(int i);
	void DrawCource(int level); //コースを描く。
	void DrawCource2(int level); //DrawNodeでコースを描く。
	;CC_SYNTHESIZE_RETAIN(cocos2d::CCSpriteBatchNode*, _bachNode,BachNode)
	;CC_SYNTHESIZE(cocos2d::Vector<Sprite*>,_cMember,CMember)
	;




	bool Lock_; //ステージが解放されているかどうか

	void SetLock(bool lok_); //ロックするしない。


	int coinCnt_=50;
	void ShowCoin();//ｺｲﾝを表示する。
	void ShowCoin2();//ｺｲﾝを表示する。
	void ClearCoin();//ｺｲﾝを非表示する。

	void SetMemoText(std::string txt_);
	void SetLockText(std::string txt_);
	bool SelectTag(Vec2 pt_); //タッチしているかチェック

	Vec2 _point1;
	Vec2 _point2;
	bool touchFlg_; //タッチしたかどうか？
	void TouchOn(Vec2 pt);
	void Swaip(Vec2 pt1, Vec2 pt2);
	void TouchOff();

	enum class SelState {
		LOCK, UNLOCK
	};
	;CC_SYNTHESIZE(SelState,_selState,SelState)
	;

	cocos2d::Size frameSize;
	void update(float dt) override;

	CREATE_FUNC(SelTag)
	//コイン関係
	;CC_SYNTHESIZE_RETAIN(SpritePool*,_coin,Coin)
	;

	;CC_SYNTHESIZE_RETAIN(Dot*, _dot,Dot)
	;CC_SYNTHESIZE_RETAIN(DrawNode*, _drawNode,DrawNode)
	;CC_SYNTHESIZE_RETAIN(RenderTexture*, _rdTx,RdTx)
	;CC_SYNTHESIZE_RETAIN(GameDeta*, _gameDeta,GameDeta)
	;CC_SYNTHESIZE_RETAIN(cocos2d::Label*, _lvlLabel,LvlLabel)
	;CC_SYNTHESIZE_RETAIN(Sprite*, _kagi,Kagi)
	;CC_SYNTHESIZE_RETAIN(Sprite*, _selWaku,SelWaku) //セレクト時の色のついた枠
	;CC_SYNTHESIZE_RETAIN(cocos2d::Label*,_selMemo,SelMemo)
	;CC_SYNTHESIZE_RETAIN(cocos2d::Label*,_lokMemo,LokMemo)
	;CC_SYNTHESIZE_RETAIN(MenuItemImage*, _selBtn,SelBtn)
	;CC_SYNTHESIZE_RETAIN(Menu*, _menu,Menu)
	;
};
#endif // __HELLOWORLD_SCENE_H__
