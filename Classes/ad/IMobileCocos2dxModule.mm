//
//  IMobileCocos2dxModule.mm
//
//  Copyright (c) 2014 i-mobile. All rights reserved.
//

#include "IMobileCocos2dxModule.h"


#import "CCEAGLView-ios.h"
#import <foundation/Foundation.h>
#import <uikit/UIKit.h>
#import "ImobileSdkAds/ImobileSdkAds.h"

// スポットデータ
@interface IMobileCocos2dxModuleSpotData  : NSObject
    // パブリッシャーID
    @property (nonatomic,copy) NSString *publisherId;
    // メディアID
    @property (nonatomic,copy) NSString *mediaId;
@end

@implementation IMobileCocos2dxModuleSpotData
@end

#pragma mark - クラス変数
// adViewId管理用
static int adViewIdCounter = 100000;
static NSMutableDictionary *adViewIdDictionary = [NSMutableDictionary dictionary];
// スポット情報管理(インラインの場合のみ使用)
static NSMutableDictionary *spots = [NSMutableDictionary dictionary];
// ObjCから受け取ったNativeAdObjectを保持するDictionary(Key:AdViewID Value:ObjCから取得したNativeAdObjectを保持するArray)
static NSMutableDictionary *objCNativeAdObjectDatas = [NSMutableDictionary dictionary];
// 受信用デリゲート(ObjCNativeAdRecieveDelegate)を保持するDictionary
static NSMutableDictionary *objCNativeAdRecieveDelegates = [NSMutableDictionary dictionary];

#pragma mark - 内部メソッド(プロトタイプ宣言)
// char* から NSString に変換します
static NSString* charToNSString(const char *value);

// 広告の表示領域を返します(表示位置パラメータ指定)
static CGRect getAdRect(IMobileCocos2dxModule::AdAlignPosition adAlignPosition, IMobileCocos2dxModule::AdValignPosition adValignPosition, IMobileCocos2dxModule::AdType adType, IMobileCocos2dxModuleIconParams iconParams, bool sizeAdjust);
// 広告サイズを取得します
static CGSize getAdSize(IMobileCocos2dxModule::AdType adType, IMobileCocos2dxModuleIconParams iconParams,bool sizeajust);
// サイズ調整後の広告サイズを取得します
static CGSize getAdjustedAdSize(CGSize originalSize, bool sizeAdjust, IMobileCocos2dxModule::AdType adType);
// 登録オブザーバ名の取得
static const char* getObserverEntryName(IMobileCocos2dxModule::AdNotficationType adNotficationType, NSString *spotId);
// 通常の通知を処理します
static void normalNotification(IMobileCocos2dxModule::AdNotficationType adNotficationType, NSString *spotId);
// 異常系の通知を処理します
static void abnormalNotification(IMobileCocos2dxModule::AdNotficationType adNotficationType, NSString *spotId, NSString *reason);
// showメソッドの実装
static int showImpl(const char *spotId, IMobileCocos2dxModule::AdType adType, float x, float y, IMobileCocos2dxModuleIconParams iconParams, bool sizeAdjust);

#pragma mark - 広告状態通知デリゲート
// 広告状態取得用のデリゲート
@interface IMobileCocos2dxModuleDelegate : NSObject<IMobileSdkAdsDelegate>
@end

@implementation IMobileCocos2dxModuleDelegate
//広告の表示が準備完了した際に呼ばれます
- (void)imobileSdkAdsSpot:(NSString *)spotId didReadyWithValue:(ImobileSdkAdsReadyResult)value {
    normalNotification(IMobileCocos2dxModule::AdNotficationType::DID_READY, spotId);
}

//広告の表示要求があった際に、準備が完了していない場合に呼ばれます
- (void)imobileSdkAdsSpotIsNotReady:(NSString *)spotId {
    normalNotification(IMobileCocos2dxModule::AdNotficationType::DID_READY, spotId);
}

//広告クリックした際に呼ばれます
- (void)imobileSdkAdsSpotDidClick:(NSString *)spotId {
    normalNotification(IMobileCocos2dxModule::AdNotficationType::DID_CLICK, spotId);
}

//広告を閉じた際に呼ばれます(広告の表示がスキップされた場合も呼ばれます)
- (void)imobileSdkAdsSpotDidClose:(NSString *)spotId {
    normalNotification(IMobileCocos2dxModule::AdNotficationType::DID_CLOSE, spotId);
}

//広告が表示された際に呼ばれます
- (void)imobileSdkAdsSpotDidShow:(NSString *)spotId {
    normalNotification(IMobileCocos2dxModule::AdNotficationType::DID_SHOW, spotId);
}

//広告の取得を失敗した際に呼ばれます
- (void)imobileSdkAdsSpot:(NSString *)spotId didFailWithValue:(ImobileSdkAdsFailResult)value {
    NSString *reason;
    switch (value) {
        case ImobileSdkAdsFailResult::IMOBILESDKADS_ERROR_PARAM:
            reason = @"PARAM";
            break;
        case ImobileSdkAdsFailResult::IMOBILESDKADS_ERROR_AUTHORITY:
            reason = @"AUTHORITY";
            break;
        case ImobileSdkAdsFailResult::IMOBILESDKADS_ERROR_RESPONSE:
            reason = @"RESPONSE";
            break;
        case ImobileSdkAdsFailResult::IMOBILESDKADS_ERROR_NETWORK_NOT_READY:
            reason = @"NETWORK_NOT_READY";
            break;
        case ImobileSdkAdsFailResult::IMOBILESDKADS_ERROR_NETWORK:
            reason = @"NETWORK";
            break;
        case ImobileSdkAdsFailResult::IMOBILESDKADS_ERROR_UNKNOWN:
            reason = @"UNKNOWN";
            break;
        case ImobileSdkAdsFailResult::IMOBILESDKADS_ERROR_AD_NOT_READY:
            reason = @"AD_NOT_READY";
            break;
        case ImobileSdkAdsFailResult::IMOBILESDKADS_ERROR_NOT_FOUND:
            reason = @"NOT_DELIVERY_AD";
            break;
        case ImobileSdkAdsFailResult::IMOBILESDKADS_ERROR_SHOW_TIMEOUT:
            reason = @"TIMEOUT";
            break;
        default:
            reason = @"UNKNOWN";
            break;
    }
   
    abnormalNotification(IMobileCocos2dxModule::AdNotficationType::DID_FAIL, spotId, reason);
}

@end
#pragma mark - objCのspotのdelegateを中継するデリゲート
// Notificationをspotidごとに設定しているためstaticで共通にして問題ない
static IMobileCocos2dxModuleDelegate* cocos2dxModuleDelegate = [[IMobileCocos2dxModuleDelegate alloc] init];
#pragma mark - ネイティブ広告処理用クラス(受信用クラス　内部クラス)
//static NSDictionaryeAdReciveNotificationObservers = new NSDictionary;

// ネイティブ広告の受信完了通知用のデリゲートクラス
@interface ObjCNativeAdRecieveDelegate : NSObject<IMobileSdkAdsDelegate>

@property (nonatomic) int adViewId;
@property (nonatomic) int adImageGetCount;
@property (nonatomic) BOOL isNativeImageLoad;

- (id)initWithAdViewId:(int)adViewId;
@end

@implementation ObjCNativeAdRecieveDelegate

- (id)initWithAdViewId:(int)adViewId {
    self = [super init];
    
    if (self) {
        self.adViewId = adViewId;
    }
    return self;
}

// ネイティブ広告の受信完了
- (void)onNativeAdDataReciveCompleted:(NSString *)spotId nativeArray:(NSArray *)objCNativeObjectArray{
    
    // ObjCから受け取ったNativeAdObjectを保持するDictionary(Key:AdViewID Value:ObjCから取得したNativeAdObjectを保持するArray)に、
    // 受け取った「nativeArray」を、「AdViewId」をKeyにして登録する
    // 以前に同一AdViewIDで取得したデータは新しく受け取った「nativeArray」で上書きされる(これにより、リフレッシュ時のメモリーリークを回避する)
    [objCNativeAdObjectDatas setObject:[objCNativeObjectArray autorelease] forKey:[NSNumber numberWithInt:self.adViewId]];

    // Cocos2dx用Native広告オブジェクト保持用配列(objCNativeAdObjectDatasのKeyとValue(Array)のIndexのみ持つ)
    cocos2d::Vector<IMobileCocos2dxNativeAdObject *>* cocos2dxNativeAdObjectArray = new cocos2d::Vector<IMobileCocos2dxNativeAdObject *>();

    // 画像取得カウントを初期化
    self.adImageGetCount = 0;
    
    
    if (self.isNativeImageLoad) {
        // 画像の取得を行う場合
//        for (int nativeObjectArrayIndex = 0; nativeObjectArrayIndex < objCNativeObjectArray.count; nativeObjectArrayIndex++) {
//            // 画像データの取得
//            [[objCNativeObjectArray objectAtIndex:nativeObjectArrayIndex] getAdImageCompleteHandler:^(UIImage *objCLoadimg) {
//                // IMobileCocos2dxNativeAdObject の作成
//                IMobileCocos2dxNativeAdObject *nativeAdObject = IMobileCocos2dxNativeAdObject::create(self.adViewId, nativeObjectArrayIndex);
//                // cocos2dxのAPPに送る配列に作成したcocos2dxNativeAdObjectを追加する
//                cocos2dxNativeAdObjectArray->Vector::pushBack(nativeAdObject);
//                // nativeObjectArrayの件数分、画像が取得できた時点で、APP側に取得完了通知を実行
//                @synchronized(self) {
//                    self.adImageGetCount++;
//                    if (self.adImageGetCount == objCNativeObjectArray.count) {
//                        IMobileCocos2dxNativeAds* nativeAds = IMobileCocos2dxNativeAds::create(cocos2dxNativeAdObjectArray);
//                        __CFNotificationCenter::getInstance()->postNotification([[NSString stringWithFormat:@"IMOBILE_SDK_ADS_SPOT_DID_NATIVEAD_READY_%d", self.adViewId] UTF8String], nativeAds);
//                    }
//                }
//            }];
//        }
    } else {
        // 画像の取得を行わない場合
//        for (int nativeObjectArrayIndex = 0; nativeObjectArrayIndex < objCNativeObjectArray.count; nativeObjectArrayIndex++) {
//            // IMobileCocos2dxNativeAdObject の作成
//            IMobileCocos2dxNativeAdObject *nativeAdObject = IMobileCocos2dxNativeAdObject::create(self.adViewId, nativeObjectArrayIndex);
//            // cocos2dxのAPPに送る配列に作成したcocos2dxNativeAdObjectを追加する
//            cocos2dxNativeAdObjectArray->Vector::pushBack(nativeAdObject);
//            // nativeObjectArrayの件数分、画像が取得できた時点で、APP側に取得完了通知を実行
//            IMobileCocos2dxNativeAds* nativeAds = IMobileCocos2dxNativeAds::create(cocos2dxNativeAdObjectArray);
//            cocos2d::CCNotificationCenter::getInstance()->postNotification([[NSString stringWithFormat:@"IMOBILE_SDK_ADS_SPOT_DID_NATIVEAD_READY_%d", self.adViewId] UTF8String], nativeAds);
//        }
    }
}
@end

IMobileCocos2dxModule::IMobileCocos2dxModule(){
}

#pragma mark - ネイティブ広告処理用クラス(ネイティブデータの取得、保持用クラス　[cocos2dxのAPP から、ObjCのNativeAdObjectにアクセスするクラス])
#pragma mark - IMobileCocos2dxNativeObjectの実装
// ObjCから受け取ったNativeAdObjectを保持するDictionary(Key:AdViewID Value:ObjCから取得したNativeAdObjectを保持するArray)から
// IMobileCocos2dxNativeAdObjectが保持する、adViewIdとObjCNativeObjectArrayIndexに合致するNativeAdObject(ObjC)を取得する
ImobileSdkAdsNativeObject* getObjCNativeObjectFromObjCNativeAdObjectDatas(int adViewId, int ObjCNativeObjectArrayIndex) {
    return [[objCNativeAdObjectDatas objectForKey:[NSNumber numberWithInt:adViewId]] objectAtIndex:ObjCNativeObjectArrayIndex];
}

//　画像取得
cocos2d::Texture2D* IMobileCocos2dxNativeAdObject::getAdTexture2d() {

    // 画像の取得と cocos2d::Texture2D へのコンバート
    NSData *objCImageData = UIImagePNGRepresentation(getObjCNativeObjectFromObjCNativeAdObjectDatas(this->adViewId, this->rawNativeObjectArrayIndex).getAdImage);
    NSUInteger objCDataLength = [objCImageData length];
    Byte *objCByteData = (Byte*)malloc(objCDataLength);
    memcpy(objCByteData, [objCImageData bytes], objCDataLength);
    cocos2d::Image *cocos2dxImage = new cocos2d::Image();
    cocos2dxImage->initWithImageData(objCByteData, objCImageData.length);
    free(objCByteData);
    cocos2d::Texture2D *texture2d = new cocos2d::Texture2D();
    texture2d->autorelease();
    texture2d->initWithImage(cocos2dxImage);
    cocos2dxImage->release();
    
    return texture2d;
}

//　タイトル取得
const char* IMobileCocos2dxNativeAdObject::getAdTitle() {
    return [getObjCNativeObjectFromObjCNativeAdObjectDatas(this->adViewId, this->rawNativeObjectArrayIndex).getAdTitle UTF8String];
}

//　本文取得
const char* IMobileCocos2dxNativeAdObject::getAdDescription() {
    return [getObjCNativeObjectFromObjCNativeAdObjectDatas(this->adViewId, this->rawNativeObjectArrayIndex).getAdDescription UTF8String];
}

//　スポンサード取得
const char* IMobileCocos2dxNativeAdObject::getAdSponsored() {
    return [getObjCNativeObjectFromObjCNativeAdObjectDatas(this->adViewId, this->rawNativeObjectArrayIndex).getAdSponsored UTF8String];
}

// クリックイベント実行
void IMobileCocos2dxNativeAdObject::onClickNativeAd() {
    // クリックイベントを呼ぶ
    [getObjCNativeObjectFromObjCNativeAdObjectDatas(this->adViewId, this->rawNativeObjectArrayIndex) sendClick];
}

// クリックイベント取得
cocos2d::CallFunc* IMobileCocos2dxNativeAdObject::getAdClickEvent() {
    int adViewId = this->adViewId;
    int rawNativeObjectArrayIndex = this->rawNativeObjectArrayIndex;
    cocos2d::CallFunc *clickFunc =  cocos2d::CallFunc::create([adViewId, rawNativeObjectArrayIndex](){
        // クリックイベントを呼ぶ
        [getObjCNativeObjectFromObjCNativeAdObjectDatas(adViewId, rawNativeObjectArrayIndex) sendClick];
    });
    
    return clickFunc;
}

#pragma mark - IMobileCocos2dxModule本体
// スポット登録(全画面)を行います
void IMobileCocos2dxModule::registerSpotFullScreen(const char *publisherId, const char *mediaId, const char *spotId) {
    // スポットの登録
    [ImobileSdkAds registerWithPublisherID:charToNSString(publisherId) MediaID:charToNSString(mediaId) SpotID:charToNSString(spotId)];
    // デリゲート設定
    [ImobileSdkAds setSpotDelegate:charToNSString(spotId) delegate:(id<IMobileSdkAdsDelegate>)cocos2dxModuleDelegate];
    // 広告取得開始
    [ImobileSdkAds startBySpotID:charToNSString(spotId)];
}

// スポット登録(インライン)を行います
void IMobileCocos2dxModule::registerSpotInline(const char *publisherId, const char *mediaId, const char *spotId) {
    IMobileCocos2dxModuleSpotData *spotData = [spots objectForKey:charToNSString(spotId)];
    if (!spotData) {
        spotData = [[IMobileCocos2dxModuleSpotData alloc] init];
        spotData.publisherId = charToNSString(publisherId);
        spotData.mediaId = charToNSString(mediaId);
        
        [spots setObject:spotData forKey:charToNSString(spotId)];
    }
}

// 全画面広告表示を行います
void IMobileCocos2dxModule::show(const char *spotId) {
    [ImobileSdkAds showBySpotID:charToNSString(spotId)];
}

// インライン広告表示(座標指定)を行います
int IMobileCocos2dxModule::show(const char *spotId, IMobileCocos2dxModule::AdType adType, float x, float y) {
    IMobileCocos2dxModuleIconParams iconParams;
    return showImpl(spotId, adType, x, y, iconParams, false);
}

// インライン広告表示(表示位置パラメータ指定)を行います
int IMobileCocos2dxModule::show(const char *spotId, IMobileCocos2dxModule::AdType adType, IMobileCocos2dxModule::AdAlignPosition adAlignPosition, IMobileCocos2dxModule::AdValignPosition adValignPosition) {
    IMobileCocos2dxModuleIconParams iconParams;
    // 表示位置パラメータを座標に変換してから呼び出し
    CGRect adRect = getAdRect(adAlignPosition, adValignPosition, adType, iconParams, false);
    return showImpl(spotId, adType, adRect.origin.x, adRect.origin.y, iconParams, false);
}

// インライン広告表示(表示位置パラメータ指定、表示サイズ自動調節)を行います
int IMobileCocos2dxModule::show(const char* spotId, IMobileCocos2dxModule::AdType adType, IMobileCocos2dxModule::AdAlignPosition adAlignPosition, IMobileCocos2dxModule::AdValignPosition adValignPosition, bool sizeAdjust){
    IMobileCocos2dxModuleIconParams iconParams;
    // 表示位置パラメータを座標に変換してから呼び出し
    CGRect adRect = getAdRect(adAlignPosition, adValignPosition, adType, iconParams, sizeAdjust);
    return showImpl(spotId, adType, adRect.origin.x, adRect.origin.y, iconParams, sizeAdjust);
}

// インライン広告表示(表示位置パラメータ指定、アイコン表示パラメータ指定)を行います
int IMobileCocos2dxModule::show(const char *spotId, IMobileCocos2dxModule::AdType adType, IMobileCocos2dxModule::AdAlignPosition adAlignPosition, IMobileCocos2dxModule::AdValignPosition adValignPosition, IMobileCocos2dxModuleIconParams iconParams) {
    // 表示位置パラメータを座標に変換してから呼び出し
    CGRect adRect = getAdRect(adAlignPosition, adValignPosition, adType, iconParams, false);
    return showImpl(spotId, adType, adRect.origin.x, adRect.origin.y, iconParams, false);
}

// インライン広告表示(座標指定、アイコン表示パラメータ指定)を行います
int IMobileCocos2dxModule::show(const char *spotId, IMobileCocos2dxModule::AdType adType, float x, float y, IMobileCocos2dxModuleIconParams iconParams) {
    return showImpl(spotId, adType, x, y, iconParams,false);
}

// showメソッドの実装
static int showImpl(const char *spotId, IMobileCocos2dxModule::AdType adType, float x, float y, IMobileCocos2dxModuleIconParams iconParams, bool sizeAdjust) {
    
    int adViewId = adViewIdCounter++;

    if (IMobileCocos2dxModule::AdType::ICON != adType) {
        CGSize adSize = getAdSize(adType, iconParams, sizeAdjust);
        UIView *adContainerView = [[UIView alloc] initWithFrame:CGRectMake(x, y, adSize.width, adSize.height)];
        UIWindow *mainWindow = [[UIApplication sharedApplication].windows objectAtIndex:0];
        [mainWindow.rootViewController.view addSubview:adContainerView];
        
        // スポット情報の取得
        NSString *spotIdString = charToNSString(spotId);
        IMobileCocos2dxModuleSpotData *spotData = [spots objectForKey:spotIdString];
        // スポットの登録
        [ImobileSdkAds registerWithPublisherID:spotData.publisherId MediaID:spotData.mediaId SpotID:spotIdString];
        // デリゲート設定
        [ImobileSdkAds setSpotDelegate:charToNSString(spotId) delegate:(id<IMobileSdkAdsDelegate>)cocos2dxModuleDelegate];
        // 広告取得開始
        [ImobileSdkAds startBySpotID:spotIdString];
        // バナー広告表示
        [ImobileSdkAds showBySpotID:spotIdString View:adContainerView SizeAdjust:sizeAdjust];
        
        [adViewIdDictionary setObject:adContainerView forKey:[NSString stringWithFormat:@"%d", adViewId]];
    }
    
    return adViewId;
}

// 広告Viewの表示／非表示を指定します
void IMobileCocos2dxModule::setVisibility(const int adViewId, bool visible) {
    UIView *adContainerView = [adViewIdDictionary objectForKey:[NSString stringWithFormat:@"%d", adViewId]];
    adContainerView.hidden = !visible;
}

// 広告状態通知用のオブザーバを登録します
void IMobileCocos2dxModule::addObserver(cocos2d::Ref *target, IMobileCocos2dxModule::AdNotficationType adNotficationType, const char *spotId, cocos2d::SEL_CallFuncO selector) {
//    __CFNotificationCenter::getInstance()->addObserver(target, selector, getObserverEntryName(adNotficationType, charToNSString(spotId)), NULL);
}

// 広告状態通知用のオブザーバを登録します
void addObserverForReciveNativeAd(cocos2d::Ref *target, int adViewId, const char *spotId, cocos2d::SEL_CallFuncO selector) {
//    __CFNotificationCenter::getInstance()->addObserver(target, selector, [[NSString stringWithFormat:@"IMOBILE_SDK_ADS_SPOT_DID_NATIVEAD_READY_%d", adViewId] UTF8String], NULL);
}

// 広告状態通知用のオブザーバを削除します
void IMobileCocos2dxModule::removeObserver(cocos2d::Ref *target, IMobileCocos2dxModule::AdNotficationType adNotficationType, const char *spotId) {
//	cocos2d::CCNotificationCenter::getInstance()->removeObserver(target, getObserverEntryName(adNotficationType, charToNSString(spotId)));
}

// 指定のRefに登録されているすべてのObserverを削除する
void IMobileCocos2dxModule::removeAllObservers(cocos2d::Ref *target, const char *spotId) {
    const AdNotficationType allAdNotficationType[] = {DID_READY, DID_SHOW, DID_CLICK, DID_CLOSE, DID_FAIL};
    for (const auto type : allAdNotficationType) {
//        __CFNotificationCenter::getInstance()->removeObserver(target, getObserverEntryName(type, charToNSString(spotId)));
    }
}

// ネイティブ広告の読み込み開始します
int IMobileCocos2dxModule::getNativeAdData(const char *spotId, cocos2d::Ref *target, cocos2d::SEL_CallFuncO selector, IMobileCocos2dxModuleNativeAdParams *params){

    // AdViewIDの取得
    int adViewId = adViewIdCounter++;

    // ネイティブ広告
//    NSDictionaryeAdReciveNotificationObservers->setObject(target, adViewId);

    // スポット情報の取得
    NSString *spotIdString = charToNSString(spotId);
    IMobileCocos2dxModuleSpotData *spotData = [spots objectForKey:spotIdString];
    
    // スポットの登録
    [ImobileSdkAds registerWithPublisherID:spotData.publisherId MediaID:spotData.mediaId SpotID:spotIdString];
    // 広告取得開始
    [ImobileSdkAds startBySpotID:spotIdString];
    
    // ObjCからの受信用クラス作成
    ObjCNativeAdRecieveDelegate *delegate = [[[ObjCNativeAdRecieveDelegate alloc] initWithAdViewId:adViewId] autorelease];
    [objCNativeAdRecieveDelegates setObject:delegate forKey:[NSNumber numberWithInt:adViewId]];
    
    // ImobileSdkAdsNativeParamsの作成
    ImobileSdkAdsNativeParams* objCNativeAdParams = [[[ImobileSdkAdsNativeParams alloc] init] autorelease];
    if (params != nullptr) {
        // 画像読み込みフラグ
        objCNativeAdParams.nativeImageGetFlag = params->nativeAdImageLoadFlag;
        delegate.isNativeImageLoad = params->nativeAdImageLoadFlag;   // 画像の読み込みフラグをObjCからの受信用クラスに保存
        // 広告要求件数
        objCNativeAdParams.requestAdCount = params->requestAdCount;
    } else {
        delegate.isNativeImageLoad = YES;
    }
    
    // 読み込み開始
    UIWindow *mainWindow = [[UIApplication sharedApplication].windows objectAtIndex:0];
    UIView *adContainerView =  [[[UIView alloc] init] autorelease];
    adContainerView.tag = adViewId; // 破棄用にtagにadViewIdを設定する
    [mainWindow.rootViewController.view addSubview:adContainerView];
    
    [ImobileSdkAds getNativeAdData:spotIdString View:adContainerView Params:objCNativeAdParams Delegate:delegate];
    // 広告受信後のAPPへのコールバックをAdViewIDをキーにオブサーバに登録する
    addObserverForReciveNativeAd(target, adViewId, spotId, selector);
    
    return adViewId;
}

// 広告取得通知オブサーバの削除とWebView(ObjC)の破棄
void IMobileCocos2dxModule::removeNativeAdCallback(int adViewId){
    // 広告取得通知オブサーバの削除
//    __CFNotificationCenter::getInstance()->removeObserver(nativeAdReciveNotificationObservers->objectForKey(adViewId), [[NSString stringWithFormat:@"IMOBILE_SDK_ADS_SPOT_DID_NATIVEAD_READY_%d", adViewId] UTF8String]);
//    NSDictionaryeAdReciveNotificationObservers->removeObjectForKey(adViewId);

    // 不要なオブジェクトの破棄
    // 広告View
    UIWindow *mainWindow = [[UIApplication sharedApplication].windows objectAtIndex:0];
    [[mainWindow.rootViewController.view viewWithTag:adViewId] removeFromSuperview];
    // 破棄したオブジェクトをNativeAdObjectを管理しているリストから削除する
    [objCNativeAdObjectDatas removeObjectForKey:[NSNumber numberWithInt:adViewId]];
    [objCNativeAdRecieveDelegates removeObjectForKey:[NSNumber numberWithInt:adViewId]];
}


// 端末の物理解像度の取得を行います
cocos2d::Size IMobileCocos2dxModule::getDisplaySize(){
    CCEAGLView *eaglView = (CCEAGLView*) cocos2d::Director::getInstance()->getOpenGLView()->getEAGLView();
    cocos2d::Size screenSize = cocos2d::Size(eaglView.bounds.size.width,eaglView.bounds.size.height);
    
    return screenSize;
}

// 広告が表示される向きの設定を設定します
// 初期値：AUTO
void IMobileCocos2dxModule::setAdOrientation(IMobileCocos2dxModule::AdOrientation orientation) {
    switch (orientation) {
        case IMobileCocos2dxModule::AdOrientation::AUTO:
            [ImobileSdkAds setAdOrientation:IMOBILESDKADS_AD_ORIENTATION_AUTO];
            break;
        case IMobileCocos2dxModule::AdOrientation::PORTRAIT:
            [ImobileSdkAds setAdOrientation:IMOBILESDKADS_AD_ORIENTATION_PORTRAIT];
            break;
        case IMobileCocos2dxModule::LANDSCAPE:
            [ImobileSdkAds setAdOrientation:IMOBILESDKADS_AD_ORIENTATION_LANDSCAPE];
            break;
        default:
            [ImobileSdkAds setAdOrientation:IMOBILESDKADS_AD_ORIENTATION_AUTO];
            break;
    }
}

// オフスクリーンウインドウのウインドウレベルを設定します
void IMobileCocos2dxModule::setOffscreenWindowLevel(AdWindowLevel windowLevel) {
    switch (windowLevel) {
        case IMobileCocos2dxModule::AdWindowLevel::NORMAL:
            //[ImobileSdkAds setOffscreenWindowLevel:UIWindowLevelNormal];
            break;
        case IMobileCocos2dxModule::AdWindowLevel::ALERT:
            //[ImobileSdkAds setOffscreenWindowLevel:UIWindowLevelAlert];
            break;
        case IMobileCocos2dxModule::AdWindowLevel::STATUS_BAR:
            //[ImobileSdkAds setOffscreenWindowLevel:UIWindowLevelStatusBar];
            break;
        default:
            //[ImobileSdkAds setOffscreenWindowLevel:UIWindowLevelAlert];
            break;
    }
}

// 広告スポットの取得を停止します
void IMobileCocos2dxModule::stop(const char *spotId) {
    [ImobileSdkAds stopBySpotID:charToNSString(spotId)];
}

// 全ての広告スポットの取得を停止します
void IMobileCocos2dxModule::stopAll() {
    [ImobileSdkAds stop];
}

// 全ての広告スポットの取得を開始します
void IMobileCocos2dxModule::startAll() {
    [ImobileSdkAds start];
}

// テストモードの設定をします
void IMobileCocos2dxModule::setTestMode(bool testFlag) {
    [ImobileSdkAds setTestMode:testFlag];
}


#pragma mark - 内部メソッド(実装)

//  const char * から NSString に変換する
static NSString* charToNSString(const char *value){
    return [NSString stringWithCString:value encoding:NSUTF8StringEncoding];
}

/// 広告の表示領域を返します(表示位置パラメータ指定)
static CGRect getAdRect(IMobileCocos2dxModule::AdAlignPosition adAlignPosition, IMobileCocos2dxModule::AdValignPosition adValignPosition, IMobileCocos2dxModule::AdType adType, IMobileCocos2dxModuleIconParams iconParams, bool sizeAdjust){
    
    // デバイスの物理サイズを取得
    //    cocos2d::Size screenSize = cocos2d::Director::getInstance()->getWinSize();
    // デバイスの論理サイズを取得
    CCEAGLView *eaglView = (CCEAGLView*) cocos2d::Director::getInstance()->getOpenGLView()->getEAGLView();
    CGSize screenSize = eaglView.bounds.size;
    
    int x = 0;
    int y = 0;
    
    // 広告サイズを取得
    CGSize adSize = getAdSize(adType, iconParams, sizeAdjust);
    // X座標の取得
    int screenWidth = screenSize.width;
    switch (adAlignPosition) {
        case IMobileCocos2dxModule::AdAlignPosition::LEFT:
            x = 0;
            break;
        case IMobileCocos2dxModule::AdAlignPosition::CENTER:
            x = screenWidth - adSize.width;
            if(x != 0) {
                x = x / 2;
            }
            break;
        case IMobileCocos2dxModule::AdAlignPosition::RIGHT:
            x = screenWidth - adSize.width;
            break;
    }
    // Y座標の取得
    int screenHeight = screenSize.height;
    switch (adValignPosition) {
        case IMobileCocos2dxModule::AdValignPosition::TOP:
            y = 0;
            break;
        case IMobileCocos2dxModule::AdValignPosition::MIDDLE:
            y = (screenHeight / 2) - (adSize.height / 2);
            break;
        case IMobileCocos2dxModule::AdValignPosition::BOTTOM:
            y = screenHeight - adSize.height;
            break;
    }
    
    return CGRectMake(x, y, adSize.width, adSize.height);
}

// 広告サイズを取得
static CGSize getAdSize(IMobileCocos2dxModule::AdType adType, IMobileCocos2dxModuleIconParams iconParams,bool sizeAdjsut){

	CGSize adSize;
	switch (adType) {
        case IMobileCocos2dxModule::AdType::BANNER:
            adSize = getAdjustedAdSize(CGSizeMake(320, 50), sizeAdjsut, IMobileCocos2dxModule::AdType::BANNER);
            break;
        case IMobileCocos2dxModule::AdType::BIG_BANNER:
            adSize = getAdjustedAdSize(CGSizeMake(320, 100), sizeAdjsut, IMobileCocos2dxModule::AdType::BIG_BANNER);
            break;
		case IMobileCocos2dxModule::AdType::TABLET_BANNER:
			adSize = CGSizeMake(468,60);
			break;
		case IMobileCocos2dxModule::AdType::TABLET_BIG_BANNER:
			adSize = CGSizeMake(728,90);
			break;
        case IMobileCocos2dxModule::AdType::MEDIUM_RECTANGLE:
            adSize = getAdjustedAdSize(CGSizeMake(300, 250), sizeAdjsut, IMobileCocos2dxModule::AdType::MEDIUM_RECTANGLE);
            break;
		case IMobileCocos2dxModule::AdType::BIG_RECTANGLE:
			adSize = CGSizeMake(336,280);
			break;
		case IMobileCocos2dxModule::AdType::SKYSCRAPER:
			adSize = CGSizeMake(120,600);
			break;
		case IMobileCocos2dxModule::AdType::WIDE_SKYSCRAPER:
			adSize = CGSizeMake(160,600);
			break;
		case IMobileCocos2dxModule::AdType::SQUARE:
			adSize = CGSizeMake(250,250);
			break;
		case IMobileCocos2dxModule::AdType::SMALL_SQUARE:
			adSize = CGSizeMake(200,200);
			break;
		case IMobileCocos2dxModule::AdType::HALFPAGE:
			adSize = CGSizeMake(300,600);
			break;
        case IMobileCocos2dxModule::AdType::ICON:
            int iconMinimumWidth = 47;          // アイコン一つあたりの最小サイズ
            int iconAdTitleReserveSpace = 3;    // タイトル表示エリアの予備マージン
            
            // アイコン広告の表示サイズをアイコンパラメータから計算して求める
            int iconAdWidth = 0;
            int iconAdHeight = 0;
            // デバイスの論理サイズを取得
            CCEAGLView *eaglView = (CCEAGLView*) cocos2d::Director::getInstance()->getOpenGLView()->getEAGLView();
            CGSize screenSize = eaglView.bounds.size;
            // 幅を計算する
            int minWidth = screenSize.width > screenSize.height ? screenSize.height : screenSize.width;
            if (iconParams.iconViewLayoutWidth > 0) {
                iconAdWidth = iconParams.iconViewLayoutWidth;
            } else {
                iconAdWidth =  minWidth;
            }
            // 高さを計算する
            // アイコン一つあたりの幅を計算
            int iconImageWidth = 0;
            if (iconParams.iconSize > 0) {
                iconImageWidth  = fmax(iconParams.iconSize, iconMinimumWidth);
            } else {
                iconImageWidth = iconMinimumWidth;
            }
            
            // 高さの取得
            if (!iconParams.iconTitleEnable) {
                iconAdHeight = iconImageWidth;
            } else {
                int iconTitleOffset = (iconParams.iconTitleOffset > 0) ? iconParams.iconTitleOffset : 4;
                int iconTitleFontSize = (iconParams.iconTitleFontSize > 0) ? fmax(iconParams.iconTitleFontSize, 8) : 10;
                int iconTitleShadowDy = (iconParams.iconTitleShadowEnable) ? iconParams.iconTitleShadowDy : 0;
                
                // タイトルが一行に収まるか計算
                iconAdHeight = iconImageWidth + iconTitleOffset + iconTitleFontSize * 2 + iconTitleShadowDy + iconAdTitleReserveSpace;
            }
            adSize = CGSizeMake(iconAdWidth, iconAdHeight);
            break;
    }
	return adSize;
}

// サイズ調整後の広告サイズを取得します
static CGSize getAdjustedAdSize(CGSize originalSize, bool sizeAdjust, IMobileCocos2dxModule::AdType adType)
{
    if (!sizeAdjust) {
        return originalSize;
    }
    
    int screenWidth = 0;
    int screenHeight = 0;
    // デバイスの論理サイズを取得
    CCEAGLView *eaglView = (CCEAGLView*) cocos2d::Director::getInstance()->getOpenGLView()->getEAGLView();
    screenWidth =  eaglView.bounds.size.width;
    screenHeight =  eaglView.bounds.size.height;
    
    // スクリーンの小さい方を横幅として取得を行う
    screenWidth = (screenWidth < screenHeight) ? screenWidth : screenHeight;
    
    int adjustedWidth = (adType == IMobileCocos2dxModule::AdType::MEDIUM_RECTANGLE) ? screenWidth - 20 : screenWidth;
    int adjustedHeight = (int)round(originalSize.height * (double)adjustedWidth / (double)originalSize.width);
    
    return CGSizeMake(adjustedWidth, adjustedHeight);
}

// 登録オブザーバ名の取得
static const char* getObserverEntryName(IMobileCocos2dxModule::AdNotficationType adNotficationType, NSString *spotId) {

	// オブザーバ登録名の作成
    NSString *observerEntryString;
	switch (adNotficationType) {
		case IMobileCocos2dxModule::AdNotficationType::DID_READY:
            observerEntryString = [NSString stringWithFormat:@"IMOBILE_SDK_ADS_SPOT_DID_READY_%@", spotId];
			break;
		case IMobileCocos2dxModule::AdNotficationType::DID_FAIL:
            observerEntryString = [NSString stringWithFormat:@"IMOBILE_SDK_ADS_SPOT_DID_FAIL_%@", spotId];
			break;
		case IMobileCocos2dxModule::AdNotficationType::DID_SHOW:
            observerEntryString = [NSString stringWithFormat:@"IMOBILE_SDK_ADS_SPOT_DID_SHOW_%@", spotId];
			break;
		case IMobileCocos2dxModule::AdNotficationType::DID_CLICK:
            observerEntryString = [NSString stringWithFormat:@"IMOBILE_SDK_ADS_SPOT_DID_CLICK_%@", spotId];
			break;
		case IMobileCocos2dxModule::AdNotficationType::DID_CLOSE:
            observerEntryString = [NSString stringWithFormat:@"IMOBILE_SDK_ADS_SPOT_DID_CLOSE_%@", spotId];
			break;
	}
	return [observerEntryString UTF8String];
}

// 通常の通知を処理します
static void normalNotification(IMobileCocos2dxModule::AdNotficationType adNotficationType, NSString *spotId) {
//    __CFNotificationCenter::getInstance()->postNotification(getObserverEntryName(adNotficationType, spotId), NULL);
}

// 異常系の通知を処理します
static void abnormalNotification(IMobileCocos2dxModule::AdNotficationType adNotficationType, NSString *spotId,  NSString *reason) {
//    NSString *value = ([reason UTF8String]);
//    __CFNotificationCenter::getInstance()->postNotification(getObserverEntryName(adNotficationType, spotId) , &value);
}

