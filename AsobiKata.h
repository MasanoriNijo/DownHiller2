#ifndef __gamebase__AsobiKata__
#define __gamebase__AsobiKata__

#include "cocos2d.h"
#include "Sprite2.h"
#include "Kiraru.h"
#include "KiraruPool.h"
#include "GameScene.h"
#include "ModalLayer.h"
#include "ParticleSystemPool.h"
#include "NParticleSystemQuad.h"
#include "Item.h"
#include "ItemPool.h"
#include "GameDeta.h"
#include "Dot.h"
#include "Bike.h"
#include "ParticleSystemPool.h"
class AsobiKata: public GameScene {
protected:
	AsobiKata();
	virtual ~AsobiKata();
	bool init() override;

public:
	cocos2d::Vec2 _point1;
	cocos2d::Vec2 _point2;

	int CourceLevel=1;
	int courceCnt_ = 0;
	int courceCnt = 9;


	bool sFstFlg=true;
	float stime=0;//終了時間
	float stime_=0;

	int sosaCnt2_=0;
	int sosaCnt2=0;

	int sosaCnt_=0;
	int sosaCnt=0;
	bool sosaJump(float dt);
	bool sosaWilyUp(float dt);
	bool sosaWilyDown(float dt);
	bool sosaKoki(float dt);
	bool sosaPt(Vec2 pt,float velo, float dt);

	void SetWinPos(Sprite* sp,Vec2 pt_);//window枠位置での表示

	void Fdi();//説明のフェードイン
	void Fdo();//説明のフェードアウト

	static cocos2d::Scene* createScene();CREATE_FUNC(AsobiKata)
	;
	void update(float dt);CC_SYNTHESIZE(cocos2d::PhysicsWorld*,_world,World)
	;
	;CC_SYNTHESIZE_RETAIN(cocos2d::Sprite*,_backGround,BackGround)
	;CC_SYNTHESIZE_RETAIN(cocos2d::Label*,_setumeiLabel,SetumeiLabel)
	;CC_SYNTHESIZE_RETAIN(cocos2d::Label*,_setumeiLabel2,SetumeiLabel2)
	;CC_SYNTHESIZE_RETAIN(cocos2d::Sprite*,_yubi,Yubi)
	;CC_SYNTHESIZE_RETAIN(Dot*,_dot,Dot)
	;CC_SYNTHESIZE_RETAIN(Dot*,_dot2,Dot2)
	;CC_SYNTHESIZE_RETAIN(Bike*,_bike,Bike)
	;CC_SYNTHESIZE_RETAIN(GameDeta*,_gameDeta,GameDeta)
	;CC_SYNTHESIZE_RETAIN(cocos2d::ParallaxNode *, _nomove1,noMove1)
	;CC_SYNTHESIZE_RETAIN(cocos2d::ParallaxNode *, _nomove2,noMove2)
	;CC_SYNTHESIZE_RETAIN(Menu*, _menuA,MenuA) //ポーズ時のメニュー
	;CC_SYNTHESIZE_RETAIN(MenuItemImage*, _startBtn,StartBtn) //再開
	;CC_SYNTHESIZE_RETAIN(MenuItemImage*, _modoruBtn,ModoruBtn)
	;CC_SYNTHESIZE_RETAIN(cocos2d::Touch*,_fstTch,FstTch)
	;
	bool fstFlg = true; //各条件で初めにやる処理
	enum class GameState {
		//
		READY, //ゲーム開始の処理
		PLAY, //プレイ中。
		WILLY,//ウイリー
		JUMP,//ジャンプ
		SPEED,//スピード操作
		WILLYJUMP,//スピード操作
		STOP,//スピード操作
		AUTOSOSA//オート操作
	};
	;CC_SYNTHESIZE(GameState,_state,State)

	void onReady(float dt);
	void onPlay(float dt);
	void onWilly(float dt);
	void onJump(float dt);
	void onSpeed(float dt);
	void onWillyJump(float dt);
	void onStop(float dt);
	void onAuto(float dt);

	void SetTouchListener(); //jaraのタッチイベントをセットする。
	void SetContactListener(); //jaraとネコのコンタクトリスナーをセットする。
	;CC_SYNTHESIZE_RETAIN(EventListenerTouchOneByOne*, _touchlistener,TouchListenner)
	;CC_SYNTHESIZE_RETAIN(EventListenerPhysicsContact*, _contactlistener,ContactListenner)
	;

	void onEnterTransitionDidFinish() override;
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event);

};

#endif // __HELLOWORLD_SCENE_H__
