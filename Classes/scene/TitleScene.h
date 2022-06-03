#ifndef __gamebase__TitleScene__
#define __gamebase__TitleScene__

#include "scene/base/GameScene.h"
#include "cocos2d.h"
USING_NS_CC;

class TitleScene: public GameScene {
protected:
	TitleScene();
	virtual ~TitleScene();
	bool init() override;

public:
	static cocos2d::Scene* createScene();
    CREATE_FUNC(TitleScene);

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


    void update(float dt) override;
	void onReady(float dt);
	void onPlay(float dt);
	void onWilly(float dt);
	void onJump(float dt);
	void onSpeed(float dt);
	void onWillyJump(float dt);
	void onStop(float dt);
	void onAuto(float dt);

	bool sosaPt(Vec2 pt, float velo, float dt);

	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event);
	void SetCource();
	void onEnterTransitionDidFinish() override;

	void openRankPark();
	void sendRankParkScore(int value);
	void tweet();
	Vec2 wheelFstPt;//ビックホイールの最初の場所

    CC_SYNTHESIZE_RETAIN(Node*,_waku,Waku);
    CC_SYNTHESIZE_RETAIN(PhysicsBody*,_wakuBody,WakuBody);

//	void SetTouchListener(); //タッチイベントをセットする。
	void SetContactListener(); //コンタクトリスナーをセットする。
    CC_SYNTHESIZE_RETAIN(EventListenerTouchOneByOne*, _touchlistener,TouchListenner);
    CC_SYNTHESIZE_RETAIN(EventListenerPhysicsContact*, _contactlistener,ContactListenner);

};

#endif // __HELLOWORLD_SCENE_H__
