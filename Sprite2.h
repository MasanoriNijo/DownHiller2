/*
 * Sprite2.h
 *
 *  Created on: 2017/03/05
 *      Author: m.nijo
 */

#ifndef SPRITE2_H_
#define SPRITE2_H_
#include "cocos2d.h"
#include "math.h"
USING_NS_CC;
class Sprite2: public cocos2d::Sprite {

protected:

	Sprite2();
	virtual ~Sprite2();

private:

public:

	Vec2 pt_; //計算用変数
	Vec2 pt2_; //計算用変数
	Vec2 pt3_; //計算用変数
	float x_;
	float x2_;
	float x3_;
	bool a_;
	bool b_;
	bool c_;

	cocos2d::Vec2 _point1;
	cocos2d::Vec2 _point2;

	void setVisible(bool flg) override;
	static Sprite2* create();
	static Sprite2* create(const std::string& filename);
	static Sprite2* createWithTexture(Texture2D *texture);
	static Sprite2* createWithTexture(Texture2D *texture, Rect rct_);

//tapを判定
	bool GetTouch(Vec2 pt_); //画像内であったら真

	//ピン止めするように回転する
	void SetRot(float kaku_);
	void SetPos(Vec2 pt_);
	void SetRotPos(float kaku_, Vec2 pt_);

	void update(float dt);CC_SYNTHESIZE(std::function<void(Sprite2*,float dt)> ,_updateListener,UpDateListener)
	;

//操作方法をセット
	void SetMoveTypeA(float velo_);
	float _velo = 0;
	bool _trnLeft = false;
	bool _trnRight = false;
	void SetMoveTypeB(float velo_);
	//pointボデイを作成する。
	void MadePoint();
	void ShowPoint(bool flg);
	void SetPointPos(Vec2 pt);
	bool pointFlg; //ポイントフラグ
	void DelShow(); //エフェクトで消える。
	void DelShow(Vec2 pt_); //エフェクトで消える。

	//ピン止めするように回転する.親ノードの親ノードに所属している場合
	void SetRot2(float kaku_);
	void SetPos2(Vec2 pt_);
	void SetRotPos2(float kaku_, Vec2 pt_);

	Vec2 GetLocalPt(Vec2 pt_); //親ノードのポイントをローカルポイントに変換する。

	//角度を変換する0-2Π(Vec2用反時計）、0-360°(sprite用時計回り）

	float ChaseRad(float rad1_, float rad2_, float velo_, float dt); //rad1_へ向かって、rad2_から回転する。

	float ChgKaku(float degree);
	float ChgRad(float kaku);
	float NomlKaku(float kaku);
	float NomlRad(float rad);
	bool BetweenKaku(float x, float min_, float max_);
	bool BetweenRad(float x, float min_, float max_);

	float GetRad(); //現在のラジアンを取得

	bool chsFlg; //追従が完了したかどうか？

	float GetNaisei(Vec2 A, Vec2 B);

	float ChaseA(float A, float chaser_, float v_, float dt);
	Vec2 ChaseA(Vec2 A, Vec2 chaser_, float v_, float dt);
	void ChaseA(Vec2 A, float v_, float dt); //自身が追いかける。
	bool ChaseA(float dt);
	Vec2 AutoPt;
	float AutoV;

//移動予測して追う
	float ChaseB(float A, float vA, float chaser_, float v_, float dt);
	Vec2 ChaseB(Vec2 A, Vec2 vA, Vec2 chaser_, float v_, float dt);
	//ランダムに移動
	Vec2 rndR_; //ランダム回転半径
	float rndrad_; //ランダム回転速度ラジアン
	float ChaseC(float A, float chaser_, float v_, float dt);
	Vec2 ChaseC(Vec2 A, Vec2 chaser_, float v_, float dt);

	//ピン止めするように回転する.親ノードの親ノードの親ノードに所属している場合
	void SetRot3(float kaku_);
	void SetPos3(Vec2 pt_);
	void SetRotPos3(float kaku_, Vec2 pt_);
	;CC_SYNTHESIZE_RETAIN(cocos2d::Sprite*,_parentSp,ParentSp)
	; //想定するペアレンツノード
CC_SYNTHESIZE(Vec2,_pinPt,PinPt)
	; //ピン止め位置
CC_SYNTHESIZE(Vec2,_ctPt,CtPt)
	; //スプライト内のピン位置
CC_SYNTHESIZE_RETAIN(cocos2d::PhysicsBody *,_body,Body)
	;CC_SYNTHESIZE_RETAIN(cocos2d::Sprite*,_point,Point)
	;CC_SYNTHESIZE(cocos2d::Vector<cocos2d::SpriteFrame *>,_pointFrame,PointFrame)
	;

};

#endif /* SPRITE2_H_ */
