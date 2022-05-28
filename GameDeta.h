#ifndef __piyopiyo__GameDeta__
#define __piyopiyo__GameDeta__

#include "cocos2d.h"
#include "Dot.h"
class GameDeta: public cocos2d::Ref {

	GameDeta();
	virtual ~GameDeta();

public:
	static GameDeta* create();
	//CREATE_FUNC(GameDeta);

	//現在選択のコースナンバーをセットする。
	void SetSelectCource(int No_);
	int GetSelectCource();

	//現在クリヤした最大の数
	void SetClearCource(int No_);
	int GetClearCource();


	//SetDebug
	void SetDebug(bool flg_);
	bool GetDebug();

	//ニューダウンヒラ―用
	void MadeCourceAsobikata(Dot* dot_, int courceNo); //遊び方のときのコースを作成
	void MadeCourceTitle(Dot* dot_, int courceNo); //タイトルのときのコースを作成
	void MadeCourceFromCourceNo(Dot* dot_, int courceNo); //コースナンバーからコースを作成
	void MadeCourceFromCourceNo_debug(Dot* dot_, int courceNo); //デバックコースを作成
	void MadeCourceFromTxt(Dot* dot_, int lvl, std::string st_); //ctxt exp 0_1_8_100
	void MadeCourceFromRnd(Dot* dot_,  int lvl_, int cCnt); //cnt_コースカウント数
	void MadeCource(Dot* dot_, int cNo, int lvl, int cnt); //

	void SetDrawPosition(); //現在の全コースのポイント情報を取得する。
	Vec2 dotDrawPt[5000]; //シェープ作成用のドット。
	int dotDrawCnt = 0;

	int MaxCourceLevel=31;
	int GetSelectCourceNo(); //現在セットされているコースNo
	int GetSelectCourceLength(); //現在セットされているコースNoの長さ

	void RndMadeCource(Dot* dot_, int lvl, int cnt);

	void ReadDetaFromString(Dot* dot_, std::string st_);
	void ReadDeta(Dot* dot_, int cx_, int cy_); //テキストデータからコースを作成する
	void ReadDeta2(Dot* dot_, int cx_, int cy_); //あらかじめ作成済みのコースデータから作成。高速化
	void ReadDeta2(Dot* dot_, int cx_, int cy_,bool cFlg,bool nFlg); //あらかじめ作成済みのコースデータから作成。高速化コースフラグと、番号フラグ
	void ReadDeta2_Prepare(Dot* dot_);
	void ReadDeta2_Prepare(Dot* dot_, int cx_, int cy_); //あらかじめコースデータを配列に作成。


	int cLvl = 0; //コース難易

	int CNos[50];//コースナンバー


	int dotPointNo_ = 0;
	int dotPointNo[50];
	Vec2 dotPoints[30000]; //シェープ作成用のドット。
	int dotShapeNo_=0;
	int dotShapeNo[50];
	Vec2 dotShapes[30000]; //シェープのドット。

	void ReadDetaFromFile(Dot* dot_, int cx_, int cy_);
	void ReadDetaFromAssetFile(Dot* dot_, int cx_, int cy_);

	void WriteDeta(Dot* dot_, int cx_, int cy_);
	void WriteDetaToFile(Dot* dot_, int cx_, int cy_); //外部ファイルへ書き込み

	float getStageTime(int x);//現在の最高クリヤタイム
	float getClearTime(int x);//基準クリヤータイム
	int getStageCoin(int x);//現在取得しているコイン数
	int getTotlCoin(int x);//コース番号ｘまでのトータルコイン数を取得
	int getTotlCoin();//最大コース数までののトータルコイン数を取得


	void setStageTime(int x, float y);
	void setStageCoin(int x, int y);
	int JudgeCoinGet(int cNo,float time_);//cNoをtime_でクリヤした時に、前回よりいくらコインをゲットしたか登録及び出力。
	bool JudgeClearTime(int cNo,float time_);	//記録更新の登録および判定


	int GetMaxGazeCnt();//コインの取得数に応じて最大のゲージ数を変化させる。


    std::string GetCourceDeta(int x, int y);
	void SetCourceDeta(int x, int y, std::string st);

	bool init();
protected:

};

#endif /* defined(__androidtest__EnemyPool__) */
