
#ifndef __gamebase__RankScene__
#define __gamebase__RankScene__

#include "cocos2d.h"
#include "GameScene.h"
#include "GameDeta.h"
#include "Dot.h"
#include "Bike.h"
#include "SpritePool.h"

USING_NS_CC;
class RankScene: public GameScene {
protected:
	RankScene();
	virtual ~RankScene();
	bool init() override;

public:
	static cocos2d::Scene* createScene();CREATE_FUNC(RankScene)
	;

	cocos2d::Vec2 _point1;
	cocos2d::Vec2 _point2;

	int CourceLevel = 1;
	int courceCnt_ = 0;
	int courceCnt = 9;

	bool sFstFlg = true;
	float stime = 0; //終了時間
	float stime_ = 0;

	int sosaCnt2_ = 0;
	int sosaCnt2 = 0;

	int sosaCnt_ = 0;
	int sosaCnt = 0;

	bool fstFlg = true; //各条件で初めにやる処理
	enum class GameState {
		//
		READY, //ゲーム開始の処理
		PLAY, //プレイ中。

	};
	;CC_SYNTHESIZE(GameState,_state,State)
	;
	void update(float dt);
	void onReady(float dt);
	void onPlay(float dt);

	bool sosaPt(Vec2 pt, float velo, float dt);

	void openRankPark();
	void sendRankParkScore(int value);


	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event);
	void onEnterTransitionDidFinish() override;

	CC_SYNTHESIZE_RETAIN(GameDeta*, _gameDeta,GameDeta)
	;
	;CC_SYNTHESIZE_RETAIN(Sprite*,_bigWheel,BigWheel)
	;CC_SYNTHESIZE_RETAIN(Dot*,_dot,Dot)
	;CC_SYNTHESIZE_RETAIN(Dot*,_dot2,Dot2)
	;CC_SYNTHESIZE_RETAIN(Bike*,_bike,Bike)
	;CC_SYNTHESIZE_RETAIN(SpritePool*,_wines,Wines)
	;CC_SYNTHESIZE_RETAIN(SpritePool*,_coins,Coins)

	;CC_SYNTHESIZE_RETAIN(Node*,_waku,Waku)
	;CC_SYNTHESIZE_RETAIN(PhysicsBody*,_wakuBody,WakuBody)

	;CC_SYNTHESIZE_RETAIN(cocos2d::ParallaxNode *, _nomove1,noMove1)
	;CC_SYNTHESIZE_RETAIN(cocos2d::ParallaxNode *, _nomove2,noMove2)
	;
	;CC_SYNTHESIZE_RETAIN(DrawNode*, _drawNode,DrawNode)
	;CC_SYNTHESIZE_RETAIN(cocos2d::Label*,_resultLabel,ResultLabel);

	void SetTouchListener(); //jaraのタッチイベントをセットする。
	void SetContactListener(); //jaraとネコのコンタクトリスナーをセットする。
	;CC_SYNTHESIZE_RETAIN(EventListenerTouchOneByOne*, _touchlistener,TouchListenner)
	;CC_SYNTHESIZE_RETAIN(EventListenerPhysicsContact*, _contactlistener,ContactListenner)
	;

};

#endif // __HELLOWORLD_SCENE_H__
