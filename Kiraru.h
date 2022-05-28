#ifndef __nekozyaradon__Kiraru___
#define __nekozyaradon__Kiraru___

#include "Kiraru.h"
#include "ChrPrm.h"
#include "cocos2d.h"
#include "ParticleSystemPool.h"
#include "cocos2d.h"
USING_NS_CC;
//#include <vector>       // ヘッダファイルインクルード
//using namespace std;
class Kiraru: public cocos2d::Sprite {
protected:

	Kiraru();
	virtual ~Kiraru();

	bool init() override;
	bool initWithTexture(Texture2D *texture) override;
	bool initWithTexture_NoBound(Texture2D *texture);
	//ParticleSystemPool* _playerBack;

private:

	Size winSize;
	Size frameSize;
	Vec2 cPt_;

	Vec2 Pt1_; //一時★よう

	int size_ = 4; //四角の一辺の長さの1/2

public:

	const int zyaraCatg = 1 << 0;
	const int handCatg = 1 << 1;
	const int pointCatg = 1 << 2;
	const int dmgCatg = 1 << 3;
	const int nikuCatg = 1 << 4;
	const int kabeCatg = 1 << 5;

	PhysicsMaterial material_ = PHYSICSBODY_MATERIAL_DEFAULT; //端部の状態

	enum class KiraruState {
		A, B, C, D, E, F, G
	};
	float delFlg = false;
	bool updateFlg = false;
	float speed_; //落ちるスピード
	float speed2_; //フェイント時のスピード

	void update(float dt) override;
	void SetUpdateListenner(
			std::function<void(Kiraru*, float)> onUpDateListener);
	void ClearKiraru();
	void DelKiraru();
	void ShowKiraru();
	void ShowKiraru(Vec2 pt_);
	void SetKiraruState(KiraruState ks);
	void SetKiraruStateRnd(); //ランダムに切らるをセット

	Vec2 TargetPt_; //これに引き寄せられるように動く。
	float ChgInterval = 3; //ターゲットポジションが変わる頻度
	float ChgInterval_; //ターゲットポジションが変わる頻度現在地
	Vec2 Force_;
	float MaxF = 60;
	float MaxV = 60;

	float Lifetime = 3;
	float Lifetime_;

	void Rnd1();
	void Rnd2();
	void Rnd3();
	void Action1();
	void Action2();
	void Action3();
	void Action4();

	static Kiraru* createWithTexture(Texture2D *texture);
	static Kiraru* createWithTexture_NoBound(Texture2D *texture); //バウンドしない系
	CREATE_FUNC(Kiraru)
	;CC_SYNTHESIZE(KiraruState,_KiraruState,KiraruState)
	;
	;CC_SYNTHESIZE_RETAIN(cocos2d::PhysicsBody *,_body,Body)
	;CC_SYNTHESIZE(cocos2d::Vector<cocos2d::SpriteFrame *>,_pointFrame,PointFrame)
	;
	std::function<void(Kiraru*, float)> onUpDateListener;
	std::function<void(Kiraru*)> onFinishListener;
};

#endif // __HELLOWORLD_SCENE_H__
