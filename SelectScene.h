#ifndef __downhiller__SelectScene__
#define __downhiller__SelectScene__

#include "cocos2d.h"
#include "ParticleSystemPool.h"
#include "SelTag.h"
#include "ImovileAd.h"
#include "Dot.h"
#include "GameDeta.h"
#include "SpritePool.h"
#include "GameScene.h"

USING_NS_CC;
class SelectScene: public GameScene {
protected:
	SelectScene();
	virtual ~SelectScene();
	bool init() override;
private:

	cocos2d::Size winSize;
	Vec2 ctPt;

public:

	int SetPitch = 800; //セットのピッチ
	int MaxLevl = 0;

	int ColorInd=0;

	void SetBeforeCource(int no_); //前回選択したコースにする。

	void DrawCource(int level); //コースを描く。
	void DrawCource2(int level); //DrawNodeでコースを描く。
	void DrawCource3(int level, bool rstFlg); //おまけコースＭａｘＬｅｖｅｌを書き換えるかどうか？
	;CC_SYNTHESIZE_RETAIN(cocos2d::CCSpriteBatchNode*, _bachNode,BachNode)
	;CC_SYNTHESIZE_RETAIN(DrawNode*, _drawNode,DrawNode)
	;CC_SYNTHESIZE(cocos2d::Vector<Sprite*>,_cMember,CMember)
	;

	enum class SelState {
		TAP, SWAIP, SCROLL, STOP
	};
	;CC_SYNTHESIZE(SelState,_selState,SelState)
	;
	bool fstFlg = true; //各条件で初めにやる処理
	void onTap(float dt);
	void onSwaip(float dt);
	void onScroll(float dt);
	void onStop(float dt);

	int w = 46;
	int d = 1; //���H�摜�̗]��
	std::vector<int> mIndexs;
	cocos2d::Vec2 _point1;
	cocos2d::Vec2 _point2;
	cocos2d::Vec2 _point2_before;
	static cocos2d::Scene* createScene();

	void SetTouchListener(); //タッチイベントをセットする。

	;CC_SYNTHESIZE_RETAIN(cocos2d::Touch*,_fstTch,FstTch)
	; //wタッチを禁止
	int moveLeftX = 0;
	int moveRightX = -680; //-1100
	int moveTopY = 3000;
	int moveDownY = 0; //-1100

	float moveVelo = 0;
	float MaxmoveVelo = 8000;
	int beforePt = 0;
	bool tch_ = false;
	bool fstSet_ = false; //タッチ後最初にセットする。
	int Y;

	;CC_SYNTHESIZE_RETAIN(Dot*, _dot,Dot)
	;CC_SYNTHESIZE_RETAIN(GameDeta*, _gameDeta,GameDeta)

	;CC_SYNTHESIZE(cocos2d::Vector<SelTag*>,_selTags,SelTags)
	void update(float dt);CREATE_FUNC(SelectScene)
	;CC_SYNTHESIZE_RETAIN(cocos2d::Sprite*,_backGround,BackGround)
	;CC_SYNTHESIZE_RETAIN(cocos2d::Sprite*,_backGround2,BackGround2)
	;CC_SYNTHESIZE_RETAIN(cocos2d::Sprite*,_selectStage,SelectStage)
	;CC_SYNTHESIZE_RETAIN(Sprite2*,_baseNode,BaseNode)
	; //スクロール用ノードすべてをこれに張り付け

	//コイン関係
	;CC_SYNTHESIZE_RETAIN(SpritePool*,_coin,Coin)
	;


	;CC_SYNTHESIZE_RETAIN(cocos2d::Label*,_stageLabel,StageLabel)
	;CC_SYNTHESIZE(int,_level,Level)
	;CC_SYNTHESIZE_RETAIN(cocos2d::ParallaxNode *, _nomove1,noMove1)
	;CC_SYNTHESIZE_RETAIN(cocos2d::ParallaxNode *, _nomove2,noMove2)
	;CC_SYNTHESIZE_RETAIN(cocos2d::ParallaxNode *, _nomove3,noMove3)
	;
	void setUpdateAction(std::function<void(SelectScene*, float dt)> action);
	void onEnterTransitionDidFinish() override;
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event);
	std::function<void(SelectScene*, float)> onUpDateListener;
	std::function<void(SelectScene*)> onsecUpDateListener;CC_SYNTHESIZE_RETAIN(EventListenerTouchOneByOne*, _touchListener,TouchListenner)

	;CC_SYNTHESIZE_RETAIN(SelTag*,_sel1,Sel1)
	;CC_SYNTHESIZE_RETAIN(SelTag*,_sel2,Sel2)
	;CC_SYNTHESIZE_RETAIN(SelTag*,_sel3,Sel3)
	;CC_SYNTHESIZE_RETAIN(SelTag*,_sel4,Sel4) //現在選択のセルタグ
	;CC_SYNTHESIZE_RETAIN(SelTag*,_sel5,Sel5)
	;CC_SYNTHESIZE_RETAIN(SelTag*,_sel6,Sel6)
	;CC_SYNTHESIZE_RETAIN(SelTag*,_sel7,Sel7)

	;CC_SYNTHESIZE_RETAIN(Sprite*,_selYaziTop,SelYaziTop)
	;CC_SYNTHESIZE_RETAIN(Sprite*,_selYaziDown,SelYaziDown)
	;CC_SYNTHESIZE_RETAIN(Sprite*,_stg,Stg)
	;CC_SYNTHESIZE_RETAIN(ImovileAd*,_ad,AD)
	;

	//debug用
CC_SYNTHESIZE_RETAIN(cocos2d::MenuItemImage*,_prmBtn,PrmBtn)
	;CC_SYNTHESIZE_RETAIN(cocos2d::Menu*,_menuPrm,MenuPrm)
	;

};

#endif // __HELLOWORLD_SCENE_H__
