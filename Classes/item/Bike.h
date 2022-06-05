#ifndef __BikeBike__Bike__
#define __BikeBike__Bike__

#include "cocos2d.h"
#include "ChrPrm.h"
#include "Sprite2.h"
USING_NS_CC;

class Bike: public Sprite2 {
protected:

	const int BikeCatg = 1 << 0;
	const int enemyCatg = 1 << 1;
	const int courceCatg = 1 << 2;
	const int itemCatg = 1 << 3;
	const int boundCatg = 1 << 4;
	const int Bike_FRAME_COUNT = 2;

	Bike();
	virtual ~Bike();

	bool init() override;
	bool initB();
	//Player _player;

private:

public:

	void SetPositionBike(Vec2 pt_);


	static Bike* createB(); //Ｂタイプ［本体がライダーのセット）
	Size winSize;
	void SetJointB(cocos2d::PhysicsWorld* PW); //Bタイプのジョイント
	void SetJointC(cocos2d::PhysicsWorld* PW); //Cタイプのジョイント
	;CC_SYNTHESIZE_RETAIN(cocos2d::Sprite *,_fWheel,FWheel) //前輪ホイールイメージ
	;CC_SYNTHESIZE_RETAIN(cocos2d::Sprite *,_rWheel,RWheel)
	;CC_SYNTHESIZE_RETAIN(cocos2d::Node *,_fWheelA,FWheelA) //前輪ホイール接触感知用
	;CC_SYNTHESIZE_RETAIN(cocos2d::Node *,_rWheelA,RWheelA)
	;CC_SYNTHESIZE_RETAIN(cocos2d::Sprite *,_pedaru,Pedaru)
	; //後輪ホイールイメージ

	enum class BikeState {
		READY, NOML, BREAK, GOAL, BIG, BALUNE, SCOPE, ALLOW, SLIDE, STOP, JUMP, JUMP2
	};
	;CC_SYNTHESIZE(BikeState,_BikeState,BikeState)
	;

	enum class SiseiState {
		MM, MD, MU, BM, BD, BU, FM, FD, FU
	};

	void FadeInBike(float delay,float dt);
	void FadeOutBike(float delay,float dt);
	void SetOpacityBike(int opc);


	bool deadFlg_ = false; //miss
	bool goalFlg_ = false; //ゴールをした場合
	void SetTouch(bool flg); //タイヤが接地しているか確認用
	bool setTouchFlg = false;

	void SetPause();

	void FJump(Vec2 pt_); //前輪リフト用
	void RJump(Vec2 pt_); //後輪リフト用
	void FJump3(Vec2 pt_); //前輪リフト用
	void RJump3(Vec2 pt_); //後輪リフト用
	void FJump2(Vec2 pt_); //前輪リフト用
	void RJump2(Vec2 pt_, bool backFlg); //後輪リフト用

	void JumpAction(Node* nd, Vec2 dct_, float dt);

	float FjumpPow = 0.5f; //前後輪の力の配分
	float RjumpPow = 0.5f;
	float maxVelo_k = 1.0; //最大ジャンプ速度の係数
	float MaxVelo = 70; //最大ジャンプ速度
	float MaxRotVelo = 100;
	float kDush_ = 1.0f; //前進の操作感度係数
	float kRot_ = 1.5f; //回転の操作感度係数
	float kJump_ = 100.0f; //ジャンプのの操作感度係数

	Vec2 dFJumpPt; //前輪のジャンプ速度
	Vec2 dRJumpPt; //後輪のジャンプ速度
	Vec2 dFRotPt; //前輪の回転速度
	Vec2 dRRotPt; //後輪の回転速度


	void KokiKoki(float dt); //ペダルをこぐ
	void KokiKoki0(); //ペダルをこぐ	アクションのみ
	float KokiVeｌo = 5; //コキコキ時の最大速度
	bool kokiOn = false; //コキコキ起動フラグ
	bool kokiOn_ = false; //コキコキ実行フラグ
	int koma_ = 0;

	int kokiCnt = 3; //2度目のタップでこぎはじめ
	int kokiCnt_ = 0; //2度目のタップでこぎはじめ
	float KokiPow = 0.2f; //人漕ぎの力
	float KokiTime = 0.4f; //タップ時間
	float KokiTime_ = 0;

	void FForce(Vec2 pt_); //前輪荷重用
	void RForce(Vec2 pt_); //後輪荷重用

	void AirRot(Vec2 rotvelo); //空中での回転制御
	void SaveRotaion(); //MaxRotVelo以内になるように回転制御
	void ControlVelo2(Vec2 rotvelo, float dt); //回転ジャンプ同時制御



	void ControlVelo(Vec2 rotvelo, Vec2 jumpVelo, float dt); //回転ジャンプ同時制御
	Vec2 ptF;//前輪速度計算用
	Vec2 ptR;//後輪速度計算用
	Vec2 ptFR;//重心速度計算用
	Vec2 ptFR_;	//後輪から前輪方向の自転車の姿勢ベクトル
	Vec2 ptFRN_;	//後輪から前輪方向から90度回転したもの。

	void contFRot();//F回転
	void contRRot();//F回転
	void contDush();//前進
	float dushTime=0.5f;
	float dushTime_=0;//ダッシュカウント回復用変数
	int dushCnt=30;//最大ダッシュカウント数。
	int dushCnt_=30;//ダッシュカウント変数。
	void contJump();//ジャンプ


	void ControlVelo2(Vec2 rotvelo, Vec2 jumpVelo, float dt); //回転ジャンプ同時制御
	void ControlVelo3(Vec2 rotvelo, Vec2 jumpVelo, float dt); //回転ジャンプ同時制御
	int cntVelo_ = 0;
	int cntVelo = 10; //ジャンプ処理を飛ばす回数
	float jtime_; //ジャンプ無効時間
	float jtime = 0.3f; //ジャンプ無効時間

	Vec2 AirPt; //計算用変数

	Vec2 FtchPt; //前輪の接地TAG：11
	Vec2 FnmlPt; //前輪の接地法線
	bool FtchFlg; //前輪が設置しているか？
	Vec2 RtchPt; //後輪の接地TAG：12
	Vec2 RnmlPt; //後輪の接地法線

	Vec2 FRnmlPt; //接地法線合算

	bool RtchFlg; //後輪が設置しているか？
	Vec2 JumpPt; //ジャンプ用
	Vec2 RotPt; //ローテーション用
	Vec2 MovePt; //ローテーション用

	float veloDump = 0;

	float wheelRotDump_ = 0.001f; //通常の車輪回転ダンピング
	float wheelStopDump_ = 1.5f; //stop時回転ダンピング

	float kazeDump0 = 0; //姿勢による空気抵抗
	float kazeDump1 = 0.02f; //姿勢による空気抵抗
	float kazeDump2 = 0.08f; //姿勢による空気抵抗

	float WheelVelo0 = 400; //ホイールの最大速度
	float WheelVelo1 = 380; //ホイールの最大速度
	float WheelVelo2 = 360; //ホイールの最大速度

	//操作系

	float spd_ = 0; //スピード表示
	Vec2 beforePos_;

	Vec2 sosaPt; //操作ポイント
	Vec2 sosaPt_; //ひとつ前の操作ポイント
	Vec2 sosaVelo; //操作速度

	int sosaLength = 24; //姿勢が変わる状態のの画面上単位ピクセル
	int dbGPtSpeed_ = 800; //デバックポイントの追従スピード
	int swaipLength = 5; //スワイプアクションをするための距離。

	float rot_; //回転制御用

	float setchPow = 100;

	;CC_SYNTHESIZE(SiseiState,_SiseiState,SiseiState)
	;CC_SYNTHESIZE(SiseiState,_SiseiStateA,SiseiStateA) //前回の状態を保持
	;
	void SetSisei(Vec2 pt_); //ptの位置で、姿勢を変化。
	void SetSiseiState(SiseiState sis);

	//ボタン操作系

	bool leftSwaip_ = false; //最後にどちら方向にスワイプしたか？

	void JumpBtn(bool on_);
	void RotBtn(bool on_);
	void StopBtn(bool on_);

	bool fstFlg = true; //各条件で初めにやる処理
	bool updateFlg;
	void onReady(float dt);
	void onNoml(float dt);
	void onNoml2(float dt);	//姿勢によりダンピングを顕著に、スワイプで前進後退
	void onBreak(float dt);

	void onBig(float dt);
	float baluneTime = 0.2f; //画面をタップしてからバルーンに変化するまでの時間
	float baluneTime_ = 0;
	void onBalune(float dt);
	void onScope(float dt);
	void onJump(float dt);
	void onJump2(float dt);
	float maxSpeed = 50;
	float maxRotSpeed = 1.5f;

//	float nomlSpeed=50;
//	float nomlRotSpeed=1.5f;
//	float jumpSpeed=50;
//	float jumpRotSpeed=1.5f;

	float allowSpeed = 50;
	void onAllow(float dt);
	void onSlide(float dt);

	void onStop(float dt);
	Vec2 stopPt;
	float stopFlg = false;

	float stopTime = 0.3f;
	float stopTime_ = 0;

	//画面操作を入力
	bool touchFlg = false;
	void TouchOn(Vec2 pt);
	void Swaip(Vec2 pt1, Vec2 pt2);
	void TouchOff();

	//chaser
	Vec2 chPt = Vec2(180, -200); //画面のオフセットVec2(150, -100)

	//スワイプ操作
	bool swaipFlg_; //スワイプ操作起動フラグ
	bool swaipFlg; //スワイプが完了したかどうか？
	bool swaipFlg1To2; //2段ジャンプ認識フラグ
	bool swaipFlg2_; //2段ジャンプ起動フラグ
	bool swaipFlg2; //2段ジャンプスワイプが完了したかどうか？
	float swaipPow = 50000; //スワイプした方向にインパルス
	float swaipSpeed = 150; //スワイプした方向にspeed

	//wクリック感知用
	bool wClickFlg = false;
	bool tch2Flg = false;
	float wClickTime = 0.2f;
	float wClickTime_ = 0;

	void Action1(); //ジャンプ時のアクション
	void Action2(); //ストップ時のアクション

	//アクション

	bool leftFlg = false;
	bool rightFlg = false;

	//ボタン位置
	Rect jumpBtn = Rect(0, 160, 480, 160);
	Rect leftBtn = Rect(0, 0, 160, 160);
	Rect rightBtn = Rect(320, 0, 160, 160);
	Rect stopBtn = Rect(160, 0, 160, 160);

	bool zimenFlg; //膨らんだボールが地面にタッチしているか？
	bool zimenFlg2; //ボール本体が地面にタッチしているか？

	float dump_Nomal = 0.3f;
	float dump_Jump = 0;
	float dump_Slide = 0;

	void Jump(float dt); //ノーマルの状態のときジャンプする。
	void Jump2(float dt); //ノーマルの状態のときジャンプする。
	Vec2 _contPt; //コンタクト中のポイント
	bool jumpFlg = false;
	bool jumpFlg2 = false;
	bool jumpingFlg2 = false;

	bool jumpFlg_ = false; //ジャンプ起動フラグ
//	float jumpPow = 50000;
	float jumpSpeed = 110;

	Vec2 jumpPt; //実操作
	Vec2 jumpPt1; //実操作
	Vec2 jumpPt2; //実操作
	Vec2 jumpPt_; //追従
	bool JumpSosaFlg = false;
	bool JumpSosaFinFlg = false; //ジャンプ操作完了

	int jumpSosa = 200; //ジャンプ捜査範囲

	float jumpTime = 0.8f;
	float jumpTime_ = 0;

	void Dosn(float dt); //ジャンプ中にボタンを離すとドスンと落ちる
	bool dosnFlg = false;
	bool jumpingFlg = false;
	float dosnVelo = 0;

	void BaluneMove(float dt);
	float BaluneVelo = 60000;
	float baluneMoveTime = 1.5f; //バルーンの滞空時間
	float baluneMoveTime_ = 0;

	void Slide(float dt); //縮んでいるときに地面と接触するとスライドする。
	bool slideFlg = false;
	bool slideFlg_ = false;
	float slidePow = 150;
	float slideTime = 0.3f;
	float slideTime_ = 0;

	bool moveFlg;
	bool chk1;
	bool chk2;
	int cnt1;
	int cnt2;

	int lifePoint;

	cocos2d::Size frameSize;

	void Jump2();
	void Jump3();

	void update(float dt) override;

	void Action3();
	void Action4();

	void SetJoint(cocos2d::PhysicsWorld* PW); //addChild�̌�Ɏ��s

	void ReSetJoint(); //addChild�̌�Ɏ��s
	std::function<void(Bike*)> onUpDateListener;
	std::function<void(Bike*)> onFinishListener;
	std::function<void(Bike*)> onContactListener;
	void setUpdateAction(std::function<void(Bike*)> action);
	void setContactAction(std::function<void(Bike*)> action);
	void Fin();

	void AccellMove(Acceleration* acc);
	void AccellMove(Vec2 dctpt);

	void sameBody2();

	CREATE_FUNC(Bike)

	;CC_SYNTHESIZE_RETAIN(Sprite *,_pointDbg,PointDbg) //debugポイント
	Vec2 dbGPt; //デバッグポイントを処理する
	Vec2 dbGPt_; //前回のデバッグポイント
	Vec2 dbGPtv; //移動速度

	Vec2 dbGPta; //加速度
	float dgGPtb = 60; //ばね力
	float dgGPtz = 0.01f; //減衰
	int dbGptv_max = 50; //最大離脱範囲
	void Boyon(Vec2 pt_); //ptの位置で、形状を変える。

	;CC_SYNTHESIZE_RETAIN(cocos2d::PhysicsBody *,_body,Body) //前輪
	;CC_SYNTHESIZE_RETAIN(cocos2d::PhysicsBody *,_body2,Body2) //後輪
	;CC_SYNTHESIZE_RETAIN(cocos2d::PhysicsBody *,_body4,Body4) //前輪タッチ確認用
	;CC_SYNTHESIZE_RETAIN(cocos2d::PhysicsBody *,_body5,Body5) //後輪タッチ確認用
	;CC_SYNTHESIZE_RETAIN(cocos2d::PhysicsBody *,_body6,Body6) //バイク
	;CC_SYNTHESIZE_RETAIN(cocos2d::PhysicsBody *,_body3,Body3) //rider
	;CC_SYNTHESIZE_RETAIN(cocos2d::Sprite *,_dmy0,Dmy0)
	;CC_SYNTHESIZE_RETAIN(cocos2d::Sprite *,_gan,Gan)//ぶつかりアクション
	Vec2 ganPt_;
	Vec2 ganNml;
	;CC_SYNTHESIZE(cocos2d::PhysicsJointDistance *,_joint0,Joint0)
	;CC_SYNTHESIZE(cocos2d::PhysicsJointPin *,_joint1,Joint1)
	;CC_SYNTHESIZE(cocos2d::PhysicsJointPin *,_joint2,Joint2)
	;CC_SYNTHESIZE_RETAIN(cocos2d::Sprite *,_BikeImg,BikeImg) //バイクのイメージ用
	;CC_SYNTHESIZE_RETAIN(cocos2d::Node *,_chaser,Chaser)
	;CC_SYNTHESIZE_RETAIN(cocos2d::Node *,_tchNode,TchNode) //接触しているノード
	Vec2 ntchPt_; //接触したノード

	;CC_SYNTHESIZE(bool,_updateFlg,UpDateFlg)
	;CC_SYNTHESIZE(int,_level,Level)
	;CC_SYNTHESIZE(Vec2,_cntPt,CntPt)
	;CC_SYNTHESIZE(cocos2d::Vector<cocos2d::SpriteFrame *>,_koki1,Koki1)
	;CC_SYNTHESIZE(cocos2d::Vector<cocos2d::SpriteFrame *>,_nobi1,Nobi1)
	;CC_SYNTHESIZE(cocos2d::Vector<cocos2d::SpriteFrame *>,_nobi2,Nobi2)
	;CC_SYNTHESIZE(cocos2d::Vector<cocos2d::SpriteFrame *>,_nobi3,Nobi3)
	;CC_SYNTHESIZE(cocos2d::Vector<cocos2d::SpriteFrame *>,_nobi4,Nobi4)

};

#endif // __HELLOWORLD_SCENE_H__
