#include "ImovileAd.h"
#include "IMobileCocos2dxModule.h"

ImovileAd::ImovileAd() {
}

ImovileAd::~ImovileAd() {

	IMobileCocos2dxModule::removeObserver(this, IMobileCocos2dxModule::DID_CLICK, IMOBILE_TEXTPOPUP_SID);
	IMobileCocos2dxModule::removeObserver(this, IMobileCocos2dxModule::DID_CLICK, IMOBILE_FULLSCREENAD_SID);
	IMobileCocos2dxModule::removeObserver(this, IMobileCocos2dxModule::DID_SHOW, IMOBILE_TEXTPOPUP_SID);
	IMobileCocos2dxModule::removeObserver(this, IMobileCocos2dxModule::DID_SHOW, IMOBILE_FULLSCREENAD_SID);
	IMobileCocos2dxModule::removeObserver(this, IMobileCocos2dxModule::DID_CLOSE, IMOBILE_FULLSCREENAD_SID);
	IMobileCocos2dxModule::removeObserver(this, IMobileCocos2dxModule::DID_FAIL, IMOBILE_FULLSCREENAD_SID);

}

bool ImovileAd::init() {

//特に何もしない。

	return true;

}

void ImovileAd::FstSet() {
	//ゲーム開始時に一回のみ実行する。
	//imobile広告表示
	//広告の取得、表示処理

//	// トップアイコンの設定
//	IMobileCocos2dxModule::registerSpotInline(IMOBILE_ICON_PID,
//	IMOBILE_ICON_MID, IMOBILE_ICON_SID);
//	// アイコン表示パラメータを作成します
//	IMobileCocos2dxModuleIconParams iconParams;
//	iconParams.iconTitleEnable = false;
//	int adViewId_top = IMobileCocos2dxModule::show(IMOBILE_ICON_SID,
//			IMobileCocos2dxModule::ICON, IMobileCocos2dxModule::CENTER,
//			IMobileCocos2dxModule::TOP, iconParams);
//	UserDefault::getInstance()->setIntegerForKey("AD_ICON_TOP", adViewId_top);
//	IMobileCocos2dxModule::setVisibility(adViewId_top, false);
//
//	// ダウンアイコンの設定
//	IMobileCocos2dxModule::registerSpotInline(IMOBILE_ICON_PID2,
//	IMOBILE_ICON_MID2, IMOBILE_ICON_SID2);
//	int adViewId_down = IMobileCocos2dxModule::show(IMOBILE_ICON_SID2,
//			IMobileCocos2dxModule::ICON, IMobileCocos2dxModule::CENTER,
//			IMobileCocos2dxModule::BOTTOM, iconParams);
//	UserDefault::getInstance()->setIntegerForKey("AD_ICON_DOWN", adViewId_down);
//	IMobileCocos2dxModule::setVisibility(adViewId_down, false);
//
//
//    // 中間アイコンの設定
//    IMobileCocos2dxModule::registerSpotInline(IMOBILE_ICON_PID3, IMOBILE_ICON_MID3, IMOBILE_ICON_SID3);
//    int adViewId_mid = IMobileCocos2dxModule::show(IMOBILE_ICON_SID, IMobileCocos2dxModule::ICON,
//					        IMobileCocos2dxModule::CENTER, IMobileCocos2dxModule::MIDDLE, iconParams);
//	UserDefault::getInstance()->setIntegerForKey("AD_ICON_MID", adViewId_mid);
//	IMobileCocos2dxModule::setVisibility(adViewId_mid, false);

	// フルスクリーンインステ
	IMobileCocos2dxModule::registerSpotFullScreen(IMOBILE_FULLSCREENAD_PID,
	IMOBILE_FULLSCREENAD_MID, IMOBILE_FULLSCREENAD_SID);

	instFlg = true;
	// テキストポップアップ
	IMobileCocos2dxModule::registerSpotFullScreen(IMOBILE_TEXTPOPUP_PID,
	IMOBILE_TEXTPOPUP_MID, IMOBILE_TEXTPOPUP_SID);
	txtFlg = true;

	// 下部バナー、"AD_BANNER"
	IMobileCocos2dxModule::registerSpotInline(IMOBILE_BANNER_PID, IMOBILE_BANNER_MID, IMOBILE_BANNER_SID);
	int adViewId_banar = IMobileCocos2dxModule::show(IMOBILE_BANNER_SID, IMobileCocos2dxModule::BANNER,
			IMobileCocos2dxModule::CENTER, IMobileCocos2dxModule::BOTTOM);
	UserDefault::getInstance()->setIntegerForKey("AD_BANNER", adViewId_banar);
	IMobileCocos2dxModule::setVisibility(adViewId_banar, false);

	// 上部バナー、"AD_BANNER2"
	IMobileCocos2dxModule::registerSpotInline(IMOBILE_BANNER_PID2, IMOBILE_BANNER_MID2, IMOBILE_BANNER_SID2);
	int adViewId_banar2 = IMobileCocos2dxModule::show(IMOBILE_BANNER_SID2, IMobileCocos2dxModule::BANNER,
			IMobileCocos2dxModule::CENTER, IMobileCocos2dxModule::TOP);
	UserDefault::getInstance()->setIntegerForKey("AD_BANNER2", adViewId_banar2);
	IMobileCocos2dxModule::setVisibility(adViewId_banar2, false);

	UserDefault::getInstance()->setIntegerForKey("INST_CNT", 0);

}

void ImovileAd::AdShow(bool top_, bool down_, bool mid_, bool txt_, bool inst_, bool top2_) {
//広告の表示操作する。
//広告を表示する
	IMobileCocos2dxModule::setVisibility(UserDefault::getInstance()->getIntegerForKey("AD_BANNER2"), top_);
	IMobileCocos2dxModule::setVisibility(UserDefault::getInstance()->getIntegerForKey("AD_BANNER"), down_);
//	IMobileCocos2dxModule::setVisibility(
//			UserDefault::getInstance()->getIntegerForKey("AD_ICON_MID"), mid_);
//
//	IMobileCocos2dxModule::setVisibility(
//			UserDefault::getInstance()->getIntegerForKey("AD_BANNER"), top2_);

	if (txt_ && txtFlg) {
		IMobileCocos2dxModule::show(IMOBILE_TEXTPOPUP_SID);
	}
	if (inst_ && instFlg) {
		IMobileCocos2dxModule::show(IMOBILE_FULLSCREENAD_SID);
	}

}

void ImovileAd::AdShow(float dt) {

}

void ImovileAd::SetObserver() {

	// 広告が表示された際に呼び出される処理の登録
	IMobileCocos2dxModule::addObserver(this, IMobileCocos2dxModule::DID_SHOW,
	IMOBILE_TEXTPOPUP_SID, callfuncO_selector(ImovileAd::AdShowAction));

	// 広告がクリックされた際に呼び出される処理の登録
	IMobileCocos2dxModule::addObserver(this, IMobileCocos2dxModule::DID_CLICK,
	IMOBILE_TEXTPOPUP_SID, callfuncO_selector(ImovileAd::AdClickAction));

	// 広告が表示された際に呼び出される処理の登録
	IMobileCocos2dxModule::addObserver(this, IMobileCocos2dxModule::DID_SHOW,
	IMOBILE_FULLSCREENAD_SID, callfuncO_selector(ImovileAd::AdShowAction));

	// 広告がクリックされた際に呼び出される処理の登録
	IMobileCocos2dxModule::addObserver(this, IMobileCocos2dxModule::DID_CLICK,
	IMOBILE_FULLSCREENAD_SID, callfuncO_selector(ImovileAd::AdClickAction));

}

void ImovileAd::AdShowAction(Ref* psender) {
	this->adShowFlg = true;
}
void ImovileAd::AdClickAction(Ref* psender) {
	this->adClickFlg = true;
}
void ImovileAd::AdCloseAction(Ref* psender) {
	const char *str3 = "ImovileAd::AdCloseAction";
	log("%s", str3);
	this->setAdCloseFlg(true);

}
void ImovileAd::InstCountShow(int cnt_) {
	//指定カウントごとにインステを表示。//広告が閉じられるまでループする。
	int x = UserDefault::getInstance()->getIntegerForKey("INST_CNT", 0);

	x++;

	const char *str2 = "ImovileAd::InstCountShow_1";
	log("%s", str2);

	if (x > cnt_) {

		UserDefault::getInstance()->setIntegerForKey("INST_CNT", 0);
//		if (instFlg) {

		const char *str3 = "ImovileAd::InstCountShow_2";
		log("%s", str3);

		this->setAdCloseFlg(false);
		// 広告が閉じられた際に呼び出される処理の登録
		IMobileCocos2dxModule::addObserver(this, IMobileCocos2dxModule::DID_CLOSE,
		IMOBILE_FULLSCREENAD_SID, callfuncO_selector(ImovileAd::AdCloseAction));
		IMobileCocos2dxModule::addObserver(this, IMobileCocos2dxModule::DID_FAIL,
		IMOBILE_FULLSCREENAD_SID, callfuncO_selector(ImovileAd::AdCloseAction));

		IMobileCocos2dxModule::registerSpotFullScreen(IMOBILE_FULLSCREENAD_PID,
		IMOBILE_FULLSCREENAD_MID, IMOBILE_FULLSCREENAD_SID);
		IMobileCocos2dxModule::show(IMOBILE_FULLSCREENAD_SID);


		while (true) {
			if(this->getAdCloseFlg()){
				break;
			}
		}

//		}
	} else {
		const char *str4 = "ImovileAd::InstCountShow_3";
		log("%s", str4);
		UserDefault::getInstance()->setIntegerForKey("INST_CNT", x);
	}

}

