//
//  IMobileCocos2dxModule.h
//
//  Copyright (c) 2014 i-mobile. All rights reserved.
//

#ifndef __IMobileCocos2dxModule__
#define __IMobileCocos2dxModule__


#include "cocos2d.h"

// アイコン表示パラメータ
struct IMobileCocos2dxModuleIconParams {
    
    // アイコン表示個数
    // Android      (初期値 : 4)
    // iOS          (初期値 : 1)
    // iOSでは表示個数が１個に固定され、変更はできません
    int iconNumber;
    
    // アイコン広告画像表示パラメータ
    // アイコン広告表示レイアウトサイズ(初期値 : 画面の最大幅)
    int iconViewLayoutWidth;
    // アイコン広告サイズ
    int iconSize;
    
    // アイコン広告タイトル表示パラメータ
    // アイコン広告タイトル表示有無(初期値 : true)
    bool iconTitleEnable;
    // アイコンタイトルフォントサイズ
    int iconTitleFontSize;
    // アイコンタイトルフォントカラー(初期値 : 白[#FFFFFF])
    const char *iconTitleFontColor;
    // アイコン広告画像とタイトルの間隔
    int iconTitleOffset;
    
    // アイコン広告タイトル影表示パラメータ
    // アイコン広告タイトル影の有無(初期値 : true)
    bool iconTitleShadowEnable;
    // アイコン広告タイトル影の色(初期値 : 黒[#000000])
    const char *iconTitleShadowColor;
    // アイコン広告タイトル影の位置X(初期値 : 1)
    int iconTitleShadowDx;
    // アイコン広告タイトル影の位置Y(初期値 : 1)
    int iconTitleShadowDy;
    
    // コンストラクタ
    IMobileCocos2dxModuleIconParams() {
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
        iconNumber = 4;
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
        iconNumber = 1;
#endif
        iconViewLayoutWidth = -1;
        iconSize = -1;
        iconTitleEnable = true;
        iconTitleFontSize = -1;
        iconTitleFontColor = "#FFFFFF";
        iconTitleOffset = -1;
        iconTitleShadowEnable = true;
        iconTitleShadowColor = "#000000";
        iconTitleShadowDx = -1;
        iconTitleShadowDy = -1;
    }
    
};
// Native広告取得用パラメータオブジェクト
struct IMobileCocos2dxModuleNativeAdParams {
    int requestAdCount = 1;
    bool nativeAdImageLoadFlag = true;
};

// Native広告取得オブジェクト
class IMobileCocos2dxNativeAdObject : public cocos2d::Ref{
private:
    int adViewId;                   // AdViewID(getNativeAdData()呼び出し時に付番される番号) ネイティブ広告が格納されている配列を取得するために使用
    int rawNativeObjectArrayIndex;  // ネイティブ広告が格納されている取得位置(iOSの場合は配列のインデックス、Androidの場合はNativeAdRawData(C++オブジェクト)の取得開始位置)
    
    // コンストラクタ
    IMobileCocos2dxNativeAdObject(){};
    // 初期化
    bool init(int adViewId, int arrayIndex) {
        this->adViewId = adViewId;
        this->rawNativeObjectArrayIndex = arrayIndex;
        return true;
    }
public:
    // Create
    static IMobileCocos2dxNativeAdObject* create(int adViewId, int arrayIndex) {
        IMobileCocos2dxNativeAdObject* pRet = new IMobileCocos2dxNativeAdObject();
        if (pRet && pRet->init(adViewId, arrayIndex)) {
            pRet->autorelease();
            return pRet;
        } else {
            delete pRet;
            pRet = nullptr;
            return nullptr;
        }
    };
    
    /// ネイティブ広告取得Getter(このクラスには実体は持たず、実体はiOSの場合はObjCのオブジェクト、Androidの場合はNativeAdRawData(C++オブジェクト) が持つ
    cocos2d::Texture2D* getAdTexture2d();
    const char* getAdTitle();
    const char* getAdDescription();
    const char* getAdSponsored();
    cocos2d::CallFunc* getAdClickEvent();   // クリックイベントを返す
    void onClickNativeAd();                 // クリックイベントを実行する(これは事実上、getAdClickEvent()を取得して実行しているのと同義)
};

// 広告を保持する配列を保持するためのクラス(Native -> Cococs2dxに返すときにRef*継承していないクラスは返せないため、そのラッパー)
class IMobileCocos2dxNativeAds : public cocos2d::Ref{
private:
    int count = 0;
    cocos2d::Vector<IMobileCocos2dxNativeAdObject *>* nativeAdObjectArray;
    IMobileCocos2dxNativeAds(){};
    ~IMobileCocos2dxNativeAds(){
        CC_SAFE_DELETE(nativeAdObjectArray);
    };
    bool init(cocos2d::Vector<IMobileCocos2dxNativeAdObject *>* nativeAdObjectArray) {
        this->nativeAdObjectArray = nativeAdObjectArray;
        return true;
    };
public:
    static IMobileCocos2dxNativeAds* create(cocos2d::Vector<IMobileCocos2dxNativeAdObject *>* nativeObjectArray){
        IMobileCocos2dxNativeAds* pRet = new IMobileCocos2dxNativeAds();
        if (pRet && pRet->init(nativeObjectArray)) {
            pRet->autorelease();
            return pRet;
        } else {
            delete pRet;
            pRet = nullptr;
            return nullptr;
        }
    };
    
    IMobileCocos2dxNativeAdObject* getNativeAdObject(){
        if(hasNext()){
            IMobileCocos2dxNativeAdObject* obj = nativeAdObjectArray->at(count);
            count++;
            return obj;
        }
        return nullptr;
    };
    
    ssize_t getAdNum(){
        return nativeAdObjectArray->size();
    };
    
    bool hasNext(){
        return count < nativeAdObjectArray->size();
    };
};

// モジュール本体
class IMobileCocos2dxModule {
private:
    // コンストラクタ(隠蔽)
    IMobileCocos2dxModule();
public:
    
    // 定数群
    // 広告の向き
    enum AdOrientation {
        AUTO,      // 自動判別
        PORTRAIT,  // ポートレート固定
        LANDSCAPE, // ランドスケープ固定
    };
    
    // 広告の表示位置(横)
    enum AdAlignPosition {
        LEFT,
        CENTER,
        RIGHT
    };
    
    // 広告の表示位置(縦)
    enum AdValignPosition {
        BOTTOM,
        MIDDLE,
        TOP
    };
    
    // 広告の種類
    enum AdType {
        ICON,
        BANNER,
        BIG_BANNER,
        MEDIUM_RECTANGLE,
        TABLET_BANNER,      // iPad Only
        TABLET_BIG_BANNER,  // iPad Only
        BIG_RECTANGLE,      // iPad Only
        SKYSCRAPER,         // iPad Only
        WIDE_SKYSCRAPER,    // iPad Only
        SQUARE,             // iPad Only
        SMALL_SQUARE,       // iPad Only
        HALFPAGE            // iPad Only
    };
    
    // WindowLevel (iOS Only)
    enum AdWindowLevel {
        NORMAL,
        ALERT,
        STATUS_BAR
    };
    
    // 通知の種類
    enum AdNotficationType {
        DID_READY,	// 広告準備完了
        DID_FAIL,	// 広告取得失敗
        DID_SHOW,	// 広告表示完了
        DID_CLICK,	// 広告クリック
        DID_CLOSE,	// 広告表示終了
    };
    
    //共通
    // 全画面広告のスポットを登録します
    static void registerSpotFullScreen(const char* publisherId, const char *mediaId, const char* spotId);
    // インライン広告のスポットを登録します
    static void registerSpotInline(const char* publisherId, const char *mediaId, const char* spotId);
    // 全画面広告を表示します
    static void show(const char* spotId);
    // インライン広告を表示します(座標指定)
    static int show(const char* spotId, IMobileCocos2dxModule::AdType adType, float x, float y);
    // インライン広告を表示します(座標指定、表示サイズ自動調節）
    static int show(const char* spotId, IMobileCocos2dxModule::AdType adType, float x, float y, bool sizeAdjust);
    // インライン広告を表示します(座標指定、アイコン表示パラメータ指定)
    static int show(const char* spotId, IMobileCocos2dxModule::AdType adType, float x, float y, IMobileCocos2dxModuleIconParams iconParams);
    // インライン広告を表示します(表示位置パラメータ指定)
    static int show(const char* spotId, IMobileCocos2dxModule::AdType adType, IMobileCocos2dxModule::AdAlignPosition adAlignPosition, IMobileCocos2dxModule::AdValignPosition adValignPosition);
    // インライン広告を表示します(表示位置パラメータ指定、表示サイズ自動調節)
    static int show(const char* spotId, IMobileCocos2dxModule::AdType adType, IMobileCocos2dxModule::AdAlignPosition adAlignPosition, IMobileCocos2dxModule::AdValignPosition adValignPosition, bool sizeAdjust);
    // インライン広告を表示します(表示位置パラメータ指定、アイコン表示パラメータ指定)
    static int show(const char* spotId, IMobileCocos2dxModule::AdType adType, IMobileCocos2dxModule::AdAlignPosition adAlignPosition, IMobileCocos2dxModule::AdValignPosition adValignPosition, IMobileCocos2dxModuleIconParams iconParams);
    // ネイティブ広告の読み込み開始します
    static int getNativeAdData(const char *spotId, cocos2d::Ref *target, cocos2d::SEL_CallFuncO selector, IMobileCocos2dxModuleNativeAdParams *params = nullptr);
    // ネイティブ広告のコールバックを削除します
    static void removeNativeAdCallback(int adViewId);
    // 広告Viewの表示／非表示を指定します
    static void setVisibility(const int adViewId, bool visible);
    // 広告状態通知用のオブザーバを登録します
    static void addObserver(cocos2d::Ref *target, IMobileCocos2dxModule::AdNotficationType adNotficationType, const char *spotId, cocos2d::SEL_CallFuncO selector);
    // 広告状態通知用のオブザーバを削除します
    static void removeObserver(cocos2d::Ref *target, IMobileCocos2dxModule::AdNotficationType adNotficationType, const char *spotId);
    // 広告状態通知用のオブザーバをすべて削除します
    static void removeAllObservers(cocos2d::Ref *target, const char *spotId);
    // 端末の物理解像度の取得を行います
    static cocos2d::Size getDisplaySize();
    
    // 広告が表示される向きを指定します
    // 初期値：AUTO
    static void setAdOrientation(AdOrientation orientation);
    // オフスクリーンウインドウのウインドウレベルを設定します(iOS Only)
    static void setOffscreenWindowLevel(AdWindowLevel windowLevel);
    
    // 広告スポットの取得を停止します
    static void stop(const char *spotId);
    // 全ての広告スポットの取得を停止します
    static void stopAll();
    // 全ての広告スポットの取得を開始します
    static void startAll();
    // テストモードの設定をします
    static void setTestMode(bool testFlag);
};

#endif
