#ifndef __nekozyaradon__MainScene__
#define __nekozyaradon__MainScene__

#include "Sprite2.h"
#include "Kiraru.h"
//#include "KiraruPool.h"
#include "GameScene.h"
#include "ModalLayer.h"
#include "cocos2d.h"
#include "ParticleSystemPool.h"
#include "NParticleSystemQuad.h"
#include "Item.h"
#include "ItemPool.h"
#include "GameDeta.h"
#include "Dot.h"
#include "Bike.h"
#include "ParticleSystemPool.h"
#include "SpritePool.h"
USING_NS_CC;
class MainScene: public GameScene {
protected:
	MainScene();
	virtual ~MainScene();
	bool init() override;
	bool updateFlg;

	//bool kiraSetFlg=false;

//	cocos2d::Vec2 _point1;
//	cocos2d::Vec2 _point2;

private:

	cocos2d::Size winSize;
	Vec2 ctPt;

	cocos2d::Vec2 madeRndPos();
	cocos2d::Vec2 madeRndPosOuter();

	bool start_ = false;
	bool stop_ = false;
	float restTime_ = 0;

	float kiraInt = 2; //綺羅を表示するインターバル
	float kiraInt_ = 0; //綺羅を表示するインターバル

	int CourceLevel = 1;
	int courceCnt_ = 0;
	int courceCnt = 9;

	bool inWinSize(cocos2d::Vec2 x);

	bool fstFlg = true; //各条件で初めにやる処理
	enum class GameState {

		//
		READY, //ゲーム開始の処理
		PLAY, //プレイ中。
		GAMEOVER, //ゲームオーバーの処理
		GAMECLEAR, //ゲームクリヤーの処理
		PAUSE //ポーズ中
	};
	void onReady(float dt);
	void onPlay(float dt);
	void onGameOver(float dt);
	void onGameClear(float dt);
	void onPause(float dt);
	void ShowResult();

	enum class AttackState {

		A, B, C, D, E, F, G, H, I, J, K, L, M, N

	};

	void MadeCource(int Lvl);

	void MadeKabe();

	bool gameOverFlg = false; //ゲームオーバーのフラグ
	bool pauseFlg = false; //ポーズ中かどうか？
	void SetControll0(); //初期のタッチイベントをセットする。

	void SetTouchListener(); //jaraのタッチイベントをセットする。
	void SetContactListener(); //jaraとネコのコンタクトリスナーをセットする。
	void onScoreUp();
	void setAction(AttackState x);
	int _actturn;

public:
	cocos2d::Vec2 _point1;
	cocos2d::Vec2 _point2;
	static cocos2d::Scene* createScene();
	void update(float dt);CREATE_FUNC(MainScene)
	;CC_SYNTHESIZE_RETAIN(cocos2d::Sprite*,_backGround,BackGround)
	;CC_SYNTHESIZE_RETAIN(Sprite2*,_table,Table)
	;CC_SYNTHESIZE_RETAIN(cocos2d::Sprite*,_yoi,Yoi)
	;CC_SYNTHESIZE_RETAIN(cocos2d::Sprite*,_hazime,Hazime)
	;CC_SYNTHESIZE_RETAIN(cocos2d::Label*,_scoreLabel,ScoreLabel)
	;CC_SYNTHESIZE_RETAIN(cocos2d::Label*,_bestLabel,BestLabel)
	;CC_SYNTHESIZE_RETAIN(cocos2d::Label*,_speedLabel,SpeedLabel)
	;CC_SYNTHESIZE_RETAIN(cocos2d::Label*,_coinLabel,CoinLabel)
	;CC_SYNTHESIZE_RETAIN(cocos2d::Label*,_msgLabel,MsgLabel)
	;CC_SYNTHESIZE_RETAIN(cocos2d::Sprite*,_asobikata,Asobikata) //遊び方表示用スプライト
	;CC_SYNTHESIZE_RETAIN(ParticleSystemPool*,_kiraBon,KiraBon)
	;CC_SYNTHESIZE_RETAIN(Node*,_waku,Waku)
	;CC_SYNTHESIZE_RETAIN(PhysicsBody*,_wakuBody,WakuBody)
//	;CC_SYNTHESIZE_RETAIN(KiraruPool*,_kiraruPool,KiraruPool)
	;CC_SYNTHESIZE_RETAIN(Dot*,_dot,Dot)
	;CC_SYNTHESIZE_RETAIN(Dot*,_dot2,Dot2)
	;CC_SYNTHESIZE_RETAIN(Item*,_sFlg,SFlg)
	;CC_SYNTHESIZE_RETAIN(Item*,_gFlg,GFlg)
	;CC_SYNTHESIZE_RETAIN(GameDeta*,_gameDeta,GameDeta)
	;

CC_SYNTHESIZE(cocos2d::PhysicsWorld*,_world,World)
	;CC_SYNTHESIZE(int,_playScore,Score)
	;CC_SYNTHESIZE(int,_bestScore,BestScore)
	;CC_SYNTHESIZE(int,_level,Level)
	;CC_SYNTHESIZE(GameState,_state,State)
	;CC_SYNTHESIZE(AttackState,_attackState,AttackState)
	;CC_SYNTHESIZE(bool,_attackFlg,AttackFlg)
	;CC_SYNTHESIZE_RETAIN(EventListenerTouchOneByOne*, _touchlistener,TouchListenner)
	;CC_SYNTHESIZE_RETAIN(EventListenerPhysicsContact*, _contactlistener,ContactListenner)
	;

	//ポーズ表示用
CC_SYNTHESIZE_RETAIN(cocos2d::Sprite*,_pauseWaku,PauseWaku)
	;CC_SYNTHESIZE_RETAIN(ModalLayer *, _modal1,Modal1)
	;

	void BtnSet(Menu* mn, Vec2 pt);

	//ゲージ
	void SetGazi(Vec2 pt);
	void GaziAtai(int x);
	;CC_SYNTHESIZE_RETAIN(cocos2d::Sprite*,_gaziA,GaziA)
	;CC_SYNTHESIZE_RETAIN(cocos2d::Sprite*,_gaziB,GaziB)
	;

	//コイン関係
	;CC_SYNTHESIZE_RETAIN(SpritePool*,_coin,Coin)
	;
	int fstCoinCnt_;
	int getCoinA; //リザルト表示の変数
	int getCoin_;
	//ボール操作ボタン
//	;CC_SYNTHESIZE_RETAIN(MenuItemImage*, _jumpB,JumpB) //
//	;CC_SYNTHESIZE_RETAIN(MenuItemImage*, _rotB,RotB) //
//	;CC_SYNTHESIZE_RETAIN(MenuItemImage*, _stopB,StopB) //
//	;CC_SYNTHESIZE_RETAIN(Menu*, _menuJ,MenuJ) //
//	;CC_SYNTHESIZE_RETAIN(Menu*, _menuR,MenuR) //
//	;CC_SYNTHESIZE_RETAIN(Menu*, _menuS,MenuS) //

	//各種ボタンめにゅー
	;CC_SYNTHESIZE_RETAIN(MenuItemImage*, _pause,Pause) //ポーズボタン
	;CC_SYNTHESIZE_RETAIN(Menu*, _menuC,MenuC) //ポーズボタン用
	;CC_SYNTHESIZE_RETAIN(MenuItemImage*, _reTry,ReTry) //もう一度
	;CC_SYNTHESIZE_RETAIN(MenuItemImage*, _saikai,Saikai) //再開
	;CC_SYNTHESIZE_RETAIN(MenuItemImage*, _modoru,Modoru) //めにゅーにもどる
	;CC_SYNTHESIZE_RETAIN(MenuItemImage*, _nextStg,NextStg) //次のステージ
	;CC_SYNTHESIZE_RETAIN(Menu*, _menuA,MenuA) //ポーズ時のメニュー
	;CC_SYNTHESIZE_RETAIN(Menu*, _menuB,MenuB) //ゲームオーバー時のめにゅうー

	//リザルト表示用
	;CC_SYNTHESIZE_RETAIN(cocos2d::Sprite*,_gameOver,GameOver)
	;CC_SYNTHESIZE_RETAIN(cocos2d::Sprite*,_resultWaku,ResultWaku)
	;CC_SYNTHESIZE_RETAIN(ModalLayer *, _modal2,Modal2)
	;CC_SYNTHESIZE_RETAIN(cocos2d::Sprite*,_result,Result)
	;CC_SYNTHESIZE_RETAIN(cocos2d::Label*,_resultLabel,ResultLabel)
	;CC_SYNTHESIZE_RETAIN(cocos2d::Label*, _lvlLabel,LvlLabel)
	;CC_SYNTHESIZE_RETAIN(cocos2d::Sprite*,_shogoLabel,ShogoLabel)
	;CC_SYNTHESIZE_RETAIN(cocos2d::Touch*,_fstTch,FstTch)
	;CC_SYNTHESIZE_RETAIN(cocos2d::ParallaxNode *, _nomove1,noMove1)
//	;CC_SYNTHESIZE_RETAIN(cocos2d::ParallaxNode *, _nomove2,noMove2)
	;CC_SYNTHESIZE_RETAIN(cocos2d::ParallaxNode *, _nomove3,noMove3)
	;

CC_SYNTHESIZE_RETAIN(Bike*,_ball,Ball)
	;
//	CC_SYNTHESIZE_RETAIN(Bike*,_bike,Ball);
	//CC_SYNTHESIZE_RETAIN(Piyo*,_ball,Ball);
CC_SYNTHESIZE_RETAIN(ItemPool*,_itemPool,ItemPool)

	;

	//CC_SYNTHESIZE(cocos2d::Vec2, _point1,Point1);
	//CC_SYNTHESIZE(cocos2d::Vec2, _point2,Point2);
	void onEnterTransitionDidFinish() override;
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event);
	std::function<void(MainScene*, float dt)> onUpDateListener;

};

#endif // __HELLOWORLD_SCENE_H__
