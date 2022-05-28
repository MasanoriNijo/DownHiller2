#ifndef __downhiller__Dot___
#define __downhiller__Dot___

#include "ChrPrm.h"
#include "cocos2d.h"
#include "ParticleSystemPool.h"
#include "Dot.h"
#include "cocos2d.h"
#include "SpritePool.h"

USING_NS_CC;
//#include <vector>       // ヘッダファイルインクルード
//using namespace std;
class Dot: public cocos2d::Sprite {
protected:

	Dot();
	virtual ~Dot();

	bool init() override;

	bool initWithFile(const std::string& filename);
	//ParticleSystemPool* _playerBack;

private:

	Size winSize;
	Size frameSize;

public:
	CREATE_FUNC(Dot)
	static Dot* create(const std::string& filename);

	Vec2 cPt_;
	int size_ = 4; //四角の一辺の長さの1/2
	int dspCnt = 0; //ドットスプライトの描写数
	Vec2 dotPoints[200]; //シェープ作成用のドット。
	int dpCnt = 0;
	Vec2 dShape[200]; //シェープのドット。
	int dsCnt = 0;

	Vec2 SetPt; //前回セットしたポイント
	Vec2 SetPt2; //前回セットしたポイント2

	Vec2 fstPt;//最初のポイント
	Vec2 lstPt;//最後のポイント

	float mrad2_ = 0;

	void JumpCource(Vec2 pt); //ptの穴を作成

	void StartLine();
	void GoalLine();

	void FadeIn_Dot(float delay_, float tm_);
	void FadeOut_Dot(float delay_, float tm_);

	void RecPos(); //SetPt2,mrad2_に保持する。

	PhysicsMaterial material0_ = PHYSICSBODY_MATERIAL_DEFAULT; //端部の状態
	PhysicsMaterial material1_ = PHYSICSBODY_MATERIAL_DEFAULT; //直線部の状態

	enum class DotState {
		START, COURCE, GOAL
	};CC_SYNTHESIZE(DotState,_DotState,DotState)
	;
	bool updateFlg = false;
	float speed_; //落ちるスピード
	float speed2_; //フェイント時のスピード

	void update(float dt) override;
	void SetUpdateListenner(std::function<void(Dot*, float)> onUpDateListener);
	void Rnd1();
	void Rnd2();
	void Rnd3();
	void Action1();
	void Action2();
	void Action3();
	void Action4();

	void AddDot(Vec2 pt_, bool spFlg);
	void AddDot(Vec2 pt_);
	void SetShape();
	void SetShape2();
	void ResetDot();

	void rndMade(int prm1, int prm2);
	void rndMade2();
	void rndMade3();
	void rndMade(int prm1, int prm2, int prm3, int cnt_);

	//コースパターン
	int cNo = 0; //コース番号を保持
	int cLvl = 0; //コース難易度を保持
	void ShowCourceName(int cNo);
	void ShowCourceOrder(int No, int MaxNo); //残り5/9と表示
	void CPtn1();
	void CPtn2();
	void CPtn3();
	void CPtn4();
	void CPtn5();
	void CPtn6();
	void CPtn7();
	void CPtn8();
	void CPtn9();
	void CPtn10();
	void CPtn11();
	void CPtn12();
	void CPtn13();
	void CPtn14();
	void CPtn15();
	void CPtn16();
	void CPtn17();
	void CPtn18();
	void CPtn19();
	void CPtn20();
	void CPtn21();
	void CPtn22();
	void CPtn23();
	void CPtn24();
	void CPtn25();
	void CPtn26();
	void CPtn27();
	void CPtn28();
	void CPtn29();
	void CPtn30();
	void CPtn31();
	void CPtn32();
	void CPtn33();
	void CPtn34();
	void CPtn35();
	void CPtn36();
	void CPtn37();
	void CPtn38();
	void CPtn39();
	void CPtn40();
	void CPtn41();
	void CPtn42();
	void CPtn43();
	void CPtn44();
	void CPtn45();
	void CPtn46();
	void CPtn47();
	void CPtn48();
	void CPtn49();
	void CPtn50();
	void CPtn51();
	void CPtn52();
	void CPtn53();
	void CPtn54();
	void CPtn55();
	void CPtn56();
	void CPtn57();
	void CPtn58();
	void CPtn59();
	void CPtn60();
	void CPtn61();
	void CPtn62();
	void CPtn63();
	void CPtn64();
	void CPtn65();
	void CPtn66();
	void CPtn67();
	void CPtn68();
	void CPtn69();
	void CPtn70();
	void CPtn71();
	void CPtn72();
	void CPtn73();
	void CPtn74();
	void CPtn75();
	void CPtn76();
	void CPtn77();
	void CPtn78();
	void CPtn79();
	void CPtn80();
	void CPtn81();
	void CPtn82();
	void CPtn83();
	void CPtn84();
	void CPtn85();
	void CPtn86();
	void CPtn87();
	void CPtn88();
	void CPtn89();
	void CPtn90();
	void CPtn91();
	void CPtn92();
	void CPtn93();
	void CPtn94();
	void CPtn95();
	void CPtn96();
	void CPtn97();
	void CPtn98();
	void CPtn99();

	int rndState = 0; //0;初期、1：生成中、2：完成
	Vec2 madePt;
	float mrad_ = 0;
	int w = 10; //一移動距離

	void madeKobu(int w, int h); //幅ｗ、高さhのコブ、穴を作る。
	void madeKobuR(int R, float upFlg_); //半径Ｒのコブ、穴を作る。

	void madeDansa(int w, int h, float endRad); //幅ｗ、高さhのサインカーブを作る。
	void madeDansa(int w, int h); //幅ｗ、高さhのコブを作る。
	Vec2 trgPt1; //ターゲットポイント；
	Vec2 trgPt2; //ターゲットポイント；
	Vec2 SinLength(float r, float w, float rad1, int dl); //１周期幅：w、半径ｒのSinで、現在rad1の位置から、dlだけ遠い位置の点を算出する。
	Vec2 SinLength(float r, float w, float rad1, int dl, float endrad); //１周期幅：w、半径ｒのSinで、現在rad1の位置から、dlだけ遠い位置の点を算出する。

	void madeMaru(float drad, float endrad);
	void madeMaruR(int R, float endrad); //半径Ｒでの丸を描く

	void madeMaruR_k(int R, float endkaku); //半径Ｒでの丸を描く,角度指定
	void madeMaruR_k( float fstkaku,int R, float endkaku); //半径Ｒでの丸を描く,角度指定
	void Masugu_k(int dL, float kaku); //傾きを指定して真っ直ぐ


	Vec2 MaruLength(float drad, int dl, float endrad);

	void Masugu(int dL); //真っ直ぐ,直前の傾きで延長
	void Masugu(int dL, float mrad_); //傾きを指定して真っ直ぐ

	float rad2;

	void SetShape(Vec2 shape_[], int k); //四角の連続
	void SetShape2(Vec2 shape_[], int k); //サークルボデイで試すが×
	void SetShape3(Vec2 shape_[], int k); //四角どうしでつながった状態

	bool SikakuChk(Vec2 pt1, Vec2 pt2, Vec2 pt3, Vec2 pt4); //時計回りの凸四角かどうか判定。

	void SetTchPt(); //タッチポイント用をセット



//CC_SYNTHESIZE_RETAIN(SpritePool *,_dotG,dotG)
	;
	cocos2d::Vector<Sprite*> _dotG;//ドットを保持する
	;
	;CC_SYNTHESIZE_RETAIN(cocos2d::PhysicsBody *,_body,Body) //エッジチェーンのライン
	;CC_SYNTHESIZE_RETAIN(cocos2d::PhysicsBody *,_body2,Body2) //はじめの丸つながりを滑らかにする
	;CC_SYNTHESIZE_RETAIN(cocos2d::Label*,_cLabel,CLabel)
	std::function<void(Dot*, float)> onUpDateListener;
	std::function<void(Dot*)> onFinishListener;

//	cocos2d::Vector<Sprite*> _dotp;

};

#endif // __HELLOWORLD_SCENE_H__
