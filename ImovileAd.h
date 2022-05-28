#ifndef __neomeiro__ImovileAd__
#define __neomeiro__ImovileAd__
#include "cocos2d.h"




USING_NS_CC;

////トップのアイコン、SHOWID="AD_ICON_TOP"
//#define IMOBILE_ICON_PID 	"34243"
//#define IMOBILE_ICON_MID 	"306001"
//#define IMOBILE_ICON_SID 	"1021496"
//
////下のアイコン、SHOWID="AD_ICON_DOWN"
//#define IMOBILE_ICON_PID2 	"34243"
//#define IMOBILE_ICON_MID2 	"306001"
//#define IMOBILE_ICON_SID2 	"1040050"
//
////真ん中のアイコン、SHOWID="AD_ICON_MID"
//#define IMOBILE_ICON_PID3 	"34243"
//#define IMOBILE_ICON_MID3 	"306001"
//#define IMOBILE_ICON_SID3 	"1384470"

//フルスクリーンのインステSHOWID="FULL_INST"
#define IMOBILE_FULLSCREENAD_PID 	"34243"
#define IMOBILE_FULLSCREENAD_MID 	"461430"
#define IMOBILE_FULLSCREENAD_SID 	"1515545"

//テキストポプアップ、SHOWID="AD_TEXT"
#define IMOBILE_TEXTPOPUP_PID 	"34243"
#define IMOBILE_TEXTPOPUP_MID 	"461430"
#define IMOBILE_TEXTPOPUP_SID 	"1515546"

//下部バナー、"AD_BANNER"
#define IMOBILE_BANNER_PID 	"34243"
#define IMOBILE_BANNER_MID 	"461430"
#define IMOBILE_BANNER_SID 	"1515544"

//上部バナー、"AD_BANNER2"
#define IMOBILE_BANNER_PID2  "34243"
#define IMOBILE_BANNER_MID2  "461430"
#define IMOBILE_BANNER_SID2  "1515548"


class ImovileAd: public cocos2d::Ref {
protected:

	ImovileAd();
	virtual ~ImovileAd();
	bool init();

private:

public:

	bool adShowFlg=false;//一回でも広告が表示（広告が機能）しているかどうか？
	bool adClickFlg=false;//一回でも広告をクリックしたかどうか？
//	bool adCloseFlg=false;//一回でも広告をクリックしたかどうか？
	CC_SYNTHESIZE(bool,_adCloseFlg,AdCloseFlg);


	void FstSet();//ゲーム開始時に一回のみ実行する。
	bool txtFlg=false;
	bool instFlg=false;


	void SetObserver();

	void AdShowAction(Ref* psender);
	void AdClickAction(Ref* psender);
	void AdCloseAction(Ref* psender);

	void AdOpenMainScene(Ref* psender);
	void AdOpenSelectScene(Ref* psender);
	void AdOpenTitleScene(Ref* psender);

	CREATE_FUNC(ImovileAd);
	void AdShow(bool top_, bool down_, bool mid_, bool txt_,bool inst_,bool top2_);
	void AdShow(float dt);
	void InstCountShow(int cnt_);//指定カウントごとにインステを表示。閉じられたらメインループを抜ける。


};

#endif // __HELLOWORLD_SCENE_H__
